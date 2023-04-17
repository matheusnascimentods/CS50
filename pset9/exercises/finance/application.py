import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']

    transactions = db.execute("SELECT symbol, name, price, SUM(shares) FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    stocks = db.execute("SELECT SUM(price * shares) as total FROM transactions WHERE user_id = ?", user_id)[0]['total']

    if not stocks:
        return render_template("index.html", cash=cash, transactions=transactions, usd=usd, total=cash)

    else:
        return render_template("index.html", cash=cash, transactions=transactions, usd=usd, total=stocks + cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Obter informações do usuário e das ações
        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Verificar se as informações de entrada são válidas
        if not symbol or not shares:
            return apology("MISSING SYMBOL OR SHARES")

        try:
            shares = int(shares)
        except ValueError:
            return apology("Shares must be a positive integer.")

        if shares <= 0:
            return apology("Shares must be a positive integer.")

        stock = lookup(symbol)
        if not stock:
            return apology("INVALID SYMBOL")

        # Obter informações da ação
        price = stock['price']
        name = stock['name']

        # Verificar se o usuário tem dinheiro suficiente para comprar as ações
        total = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash'] - price * shares
        if total < 0:
            return apology("CAN'T AFFORD")

        # Inserir informações da transação no banco de dados
        db.execute("INSERT INTO transactions(user_id, name, shares, price, symbol, type) VALUES (?, ?, ?, ?, ?, ?)", user_id, name, shares, price, symbol, 'buy')
        db.execute("UPDATE users SET cash = ? WHERE id = ?", total, user_id)

        return redirect("/")

    elif request.method == "GET":

        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY time", session["user_id"])
    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username").lower():
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username").lower())

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Missing symbol")

        result = lookup(symbol)

        if not result:
            return apology("Invalid symbol")

        return render_template("quoted.html", stock=result, usd=usd)

@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "POST":
        username = request.form.get("username").lower()
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("USERNAME IS REQUIRED")

        if not password or not confirmation:
            return apology("PASSWORD AND CONFIRMATION IS REQUIRED")

        if password != confirmation:
            return apology("PASSWORDS DO NOT MATCH")

        select = db.execute("SELECT username FROM users WHERE username = ?", username)
        if select:
            return apology("USER ALREADY EXISTS")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        return redirect("/login")

    elif request.method == "GET":
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares < 1:
            return apology("negative shares are invalid ")


        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]['shares']

        if shares_owned < shares:
            return apology("você não tem tantas ações")

        transaction_price = lookup(symbol)['price']
        transaction_name = lookup(symbol)['name']
        cash = transaction_price * shares

        db.execute("INSERT INTO transactions(user_id, name, shares, price, symbol, type) VALUES (?, ?, ?, ?, ?, ?)", user_id, transaction_name, -shares, transaction_price, symbol, 'sell')
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash, user_id)

        return redirect("/")

    elif request.method == "GET":

        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

        return render_template("sell.html", symbols=symbols)

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():

    if request.method == "POST":

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not password or not confirmation:
            return apology("PASSWORD AND CONFIRMATION IS REQUIRED")

        if password != confirmation:
            return apology("PASSWORDS DO NOT MATCH")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(password), session["user_id"])
        return redirect("/logout")

    elif request.method == "GET":

        return render_template("password.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
