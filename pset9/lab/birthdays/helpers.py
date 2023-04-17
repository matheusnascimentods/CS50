from flask import render_template
import datetime

def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code

def checkDate(month, day):

    if month == 2:
            max_days = 29

    elif month in [4, 6, 9, 11]:
        max_days = 30

    else:
        max_days = 31

    if day > max_days:
        return False

    return True

