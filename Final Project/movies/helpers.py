import os
import requests
import urllib.parse
from cs50 import SQL

from flask import redirect, render_template, request, session
from functools import wraps

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


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function

def get_popular_movies():

    movies = []
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://api.themoviedb.org/3/movie/popular?api_key={api_key}&language=en-US&page=1"
        response = requests.get(url)
        response.raise_for_status()

    except requests.RequestException:
        return None

    response = response.json()["results"]

    for item in response:

        movie = {
            "title": item["title"],
            "poster": f"https://image.tmdb.org/t/p/original{item['poster_path']}"
        }

        movies.append(movie)

    return movies

def serach_movie(title):

    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://api.themoviedb.org/3/search/movie?api_key={api_key}&language=en-US&query={title}&page=1"
        response = requests.get(url)
        response.raise_for_status()

    except requests.RequestException:
        return None

    response = response.json()["results"]
    result = []

    for item in response:

        movie = {
            "title": item["title"],
            "poster": f"https://image.tmdb.org/t/p/original{item['poster_path']}",
            "movie_id": item["id"]
        }

        result.append(movie)

    return result

def movie_details(movie_id):

    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://api.themoviedb.org/3/movie/{movie_id}?api_key={api_key}&language=en-US"
        response = requests.get(url)
        response.raise_for_status()

    except requests.RequestException:
        return None

    response = response.json()
    movie = {
        'title': response['title'],
        'poster': response['poster_path'],
        'description': response['overview'],
        'code': response["id"]
    }

    return movie