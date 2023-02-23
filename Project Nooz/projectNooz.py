"""
Importing important modules including those required for Auth0
"""
import json
import sqlite3
from os import environ as env
from urllib.parse import quote_plus, urlencode

from authlib.integrations.flask_client import OAuth
from dotenv import find_dotenv, load_dotenv
from flask import Flask, redirect, render_template, session, url_for

app = Flask(__name__)

ENV_FILE = find_dotenv()
if ENV_FILE:
    load_dotenv(ENV_FILE)

app = Flask(__name__)
app.secret_key = env.get("APP_SECRET_KEY")


oauth = OAuth(app)

oauth.register(
    "auth0",
    client_id=env.get("AUTH0_CLIENT_ID"),
    client_secret=env.get("AUTH0_CLIENT_SECRET"),
    client_kwargs={
        "scope": "openid profile email",
    },
    server_metadata_url=f"https://{env.get('AUTH0_DOMAIN')}/.well-known/openid-configuration",
)


@app.route("/")
def home():
    """
    Homepage route that shows the login button
    """
    return render_template(
        "home.html",
        session=session.get("user"),
        pretty=json.dumps(session.get("user"), indent=4),
    )


@app.route("/login")
def login():
    """
    Login route that redirects to Auth0
    """
    return oauth.auth0.authorize_redirect(
        redirect_uri=url_for("callback", _external=True)
    )


@app.route("/callback", methods=["GET", "POST"])
def callback():
    """
    Callback route that handles the response from Auth0 and redirects to the stories route
    """
    token = oauth.auth0.authorize_access_token()
    session["user"] = token
    return redirect("/stories")


@app.route("/stories")
def stories():
    """
    Stories route that shows the stories and its information
    """
    try:
        con = sqlite3.connect("/home/azureuser/projectNooz/news.db")
        cur = con.cursor()
        stories_list = []
        for row in cur.execute("SELECT title, url, user, submission_date, news_id FROM topStories"):
            stories_list.append(row)
        stories_list.reverse()

    except sqlite3.Error as error:
        return "<h1 style='color:blue'> Error with SQLite </h1>" + str(error)

    finally:
        if con:
            con.close()
            return render_template(
                "stories.html", session=session.get("user"), stories=stories_list
            )


@app.route("/admin")
def admin():
    """
    Admin route that shows the admin page, only accessible to admins defined in the html
    """
    votes_con = sqlite3.connect("/home/azureuser/projectNooz/likedislike.db")
    votes_cur = votes_con.cursor()

    voted_stories = []
    for row in votes_cur.execute("SELECT * FROM vote"):
        voted_stories.append(row)

    votes_con.close()

    return render_template(
        "admin.html", session=session.get("user"), votedStories=voted_stories
    )

@app.route("/profile")
def profile():
    """
    Profile route that shows the profile page
    """
    return render_template("profile.html", session=session.get("user"))

@app.route("/delete/<news_id>")
def delete(news_id):
    """
    Delete route that deletes a story from the database. Takes in a news_id as a parameter
    """
    votes_con = sqlite3.connect("/home/azureuser/projectNooz/likedislike.db")
    votes_cur = votes_con.cursor()

    votes_cur.execute("DELETE FROM vote WHERE news_id = ?", (news_id,))
    votes_con.commit()

    votes_con.close()

    # DELETES FROM STORIES TABLE ALSO
    stories_con = sqlite3.connect("/home/azureuser/projectNooz/news.db")
    stories_cur = stories_con.cursor()

    stories_cur.execute("DELETE FROM topStories WHERE news_id = ?", (news_id,))
    stories_con.commit()

    stories_con.close()

    return redirect("/admin")


@app.route("/logout")
def logout():
    """
    Logout route that clears the session and redirects to the homepage
    """
    session.clear()
    return redirect(
        "https://"
        + env.get("AUTH0_DOMAIN")
        + "/v2/logout?"
        + urlencode(
            {
                "returnTo": url_for("home", _external=True),
                "client_id": env.get("AUTH0_CLIENT_ID"),
            },
            quote_via=quote_plus,
        )
    )


@app.route("/like/<news_id>/<title>/<user>")
def like(news_id, title, user):
    """
    Like route that adds a like to the database.
    Takes in a news_id, title, and user as parameter to send to the database
    """
    try:
        con = sqlite3.connect("/home/azureuser/projectNooz/likedislike.db")
        cur = con.cursor()
        cur.execute(
            "SELECT news_id, user, like_or_dislike FROM vote WHERE news_id = ?",
            (news_id,),
        )
        dup_check = cur.fetchall()
        if len(dup_check) != 0:
            cur.execute(
                "DELETE FROM vote WHERE news_id = ? AND user = ?", (news_id, user)
            )
            con.commit()

        sql_input = (news_id, title, user, 1)
        cur.execute(
            """INSERT INTO vote(news_id, title, user, like_or_dislike) VALUES (?,?,?,?);""",
            sql_input,
        )
        con.commit()

    except sqlite3.Error as error:
        return error
    finally:
        if con:
            con.close()
            return redirect("/stories")


@app.route("/dislike/<news_id>/<title>/<user>")
def dislike(news_id, title, user):
    """
    Dislike route that adds a dislike to the database.
    Takes in a news_id, title, and user as parameter to query the database
    """
    try:
        con = sqlite3.connect("/home/azureuser/projectNooz/likedislike.db")
        cur = con.cursor()
        cur.execute("SELECT news_id, user FROM vote WHERE news_id = ?", (news_id,))
        dup_check = cur.fetchall()
        if len(dup_check) != 0:
            cur.execute(
                "DELETE FROM vote WHERE news_id = ? AND user = ?", (news_id, user)
            )
            con.commit()
        sql_input = (news_id, title, user, 0)
        cur.execute(
            """INSERT INTO vote(news_id,title,user,like_or_dislike) VALUES(?,?,?,?)""",
            sql_input,
        )
        con.commit()

    except sqlite3.Error as error:
        return error

    finally:
        if con:
            con.close()
            return redirect("/stories")


if __name__ == "__main__":
    app.run()
