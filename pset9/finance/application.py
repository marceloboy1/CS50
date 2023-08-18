import os

from datetime import datetime
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
    rows = db.execute(
        "SELECT symbol, companyName, sum(shares) as shares FROM transactions WHERE userId = ? GROUP BY symbol", session["user_id"])
    user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    total = 0

    # add values of price and total, and sum the total of the wallet
    for row in rows:
        print(row)
        row["price"] = lookup(row["symbol"])["price"]
        row["total"] = (row["price"] * row["shares"])
        total += row["total"]
        row["price"] = usd(row["price"])
        row["total"] = usd(row["total"])
    return render_template("index.html", rows=rows, total=usd(total), cash=usd(user[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    '''Buy stocks'''
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))

        # check to see if user type an integer
        if (stock):
            shares = request.form.get("shares")
            if shares.isnumeric():
                now = datetime.now()
                date_time_str = now.strftime("%Y-%m-%d %H:%M:%S")
                transValue = stock["price"] * int(shares)
                row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

                # check to see if user have money
                if transValue > row[0]["cash"]:
                    return apology("You're poor")
                else:

                    # update de DB with new transaction and discount the value from the cash
                    flash('Shares bougth!')
                    db.execute("INSERT INTO transactions (userId, companyName, symbol, shares, price, transacted) VALUES (? , ?, ?, ?, ?, ?)",
                               session["user_id"], stock["name"], stock["symbol"], shares, stock["price"], date_time_str)
                    db.execute("UPDATE users SET cash = cash - ? where id = ?", transValue, session["user_id"])
                    return redirect("/")
            else:
                return apology("Not int!", 400)
        else:
            return apology("Invalid Token", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE userId = ?", session["user_id"])
    for row in rows:
        row["price"] = usd(row["price"])

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        # check if user typed something and make the api request
        if (stock):
            return render_template("quoted.html", name=stock["name"], price=usd(stock["price"]), ticker=stock["symbol"])
        else:
            return apology("Invalid Ticker", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # checks if passwords matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password don't match", 400)

        else:
            # checks if username already exists in DB
            users = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))
            if not users:
                # register user
                flash('User Registred')
                db.execute("INSERT INTO users (username, hash) VALUES (? , ?)", request.form.get("username"),
                           generate_password_hash(request.form.get("password")))
                redirect("/")
            else:
                return apology("Username Taken", 400)
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        # check to see if user typed something
        if (stock):
            now = datetime.now()
            date_time_str = now.strftime("%Y-%m-%d %H:%M:%S")
            transValue = stock["price"] * int(request.form.get("shares"))
            share = int(request.form.get("shares"))
            total = db.execute("SELECT sum(shares) as shares FROM transactions WHERE userId = ? AND symbol = ?",
                               session["user_id"], request.form.get("symbol"))
            # checks to see if user have enough shares to sell
            if share > total[0]["shares"]:
                return apology("Not enough shares")
            else:
                # make the transaction and update the DB
                db.execute("INSERT INTO transactions (userId, companyName, symbol, shares, price, transacted) VALUES (? , ?, ?, -?, ?, ?)",
                           session["user_id"], stock["name"], stock["symbol"], share, stock["price"], date_time_str)
                db.execute("UPDATE users SET cash = cash + ? where id = ?", transValue, session["user_id"])
                flash('Stock sold')
                return redirect("/")
        else:
            return apology("Invalid Token")
    else:
        # render the sell page with a list of stocks in wallet
        stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE userId = ?", session["user_id"])
        print(stocks)
        return render_template("sell.html", stocks=stocks)


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """Change password"""
    if request.method == "POST":

        # Ensure lastPassuwod was submitted
        if not request.form.get("lastPassword"):
            return apology("must provide last password", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        else:
            # checks if correct password
            rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("lastPassword")):
                return apology("Invalid password", 400)
            elif request.form.get("password") != request.form.get("confirmation"):
                return apology("Passwords don't match", 400)
            else:
                # change password in DB
                flash('Password changed')
                db.execute("UPDATE users SET hash = ? WHERE id = ?",
                            generate_password_hash(request.form.get("password")), session["user_id"])
                return redirect("/")
    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)