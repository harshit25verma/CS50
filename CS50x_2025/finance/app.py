import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # All stocks info of currecnt user
    all_stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session['user_id'])
    # All cash balacne info of the User
    cash = (db.execute("SELECT cash FROM users WHERE id = ?", session['user_id']))
    cash_balance = cash[0]['cash']

    if len(all_stocks) == 0:
        return render_template("index.html", only_cash = "yes", cash_balance=usd(cash_balance))

    else:
        stock_holding_value = 0

        for stock in all_stocks:
            shares = stock['shares']
            price = lookup(stock['symbol'])
            stock_price = price['price']
            stock_holding_value += shares * stock_price



        total_holding_value = cash_balance + stock_holding_value

        return render_template("index.html", all_stocks=all_stocks, stock_holding_value=usd(stock_holding_value), cash_balance=usd(cash_balance), total_holding_value=usd(total_holding_value), stock_price=(stock_price))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        try:
            int(request.form.get("shares"))
        except ValueError:
            return apology("must provide valid shares", 400)
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol", 400)
        if lookup(request.form.get("symbol")) is None:
            return apology("must provide a valid stock symbol", 400)
        # if (request.form.get("shares")).isdigit() == True :
        #     return apology("must provide valide shares", 400)
        if not request.form.get("shares"):
            return apology("must provide valid shares", 400)
        if int(request.form.get("shares")) < 0:
            return apology("must provide valid shares", 400)

        else:

            stock = lookup(request.form.get("symbol"))
            shares = float(request.form.get("shares"))
            required_money = shares * stock['price']
            user_money_fetch = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
            user_money = float(user_money_fetch[0]['cash'])
            user_money_remain = user_money - required_money


            if required_money > user_money or user_money_remain < 0:
                return apology("not enough funds to complete the order")

            else:

                username = db.execute("SELECT username FROM users WHERE id = ?", session['user_id'])

                # Chnage the amount of cash in users table
                db.execute("UPDATE users SET cash = ?", user_money_remain)

                # Make a transaction history of BUY to track
                db.execute("INSERT INTO transactions (date, time, action, stock, symbol, shares, cost, user_id, username) VALUES (DATE(CURRENT_TIMESTAMP), TIME(CURRENT_TIMESTAMP), ?, ?, ?, ?, ?, ?, ?)", "BUY", stock['name'], stock['symbol'], shares, required_money, session['user_id'], username[0]['username'])

                # Updating the stocks table

                # If User and stock symbol exist in the same line, update shares on stocks
                if len(db.execute("SELECT username FROM stocks WHERE user_id = ? AND symbol = ?", session['user_id'], stock['symbol'])) == 1:
                    db.execute("UPDATE stocks SET shares = shares + ? WHERE stocks.symbol = ? AND user_id = ?", shares, stock['symbol'], session['user_id'])

                # If the User does not exist in stocks
                else:
                    db.execute("INSERT INTO stocks (user_id, username, symbol, stock, shares) VALUES (?, ?, ? ,?, ?)", session['user_id'], username[0]['username'], stock['symbol'], stock['name'], shares)

                return redirect("/")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Add funds to your account"""
    if request.method == "POST":
        if not request.form.get("deposit"):
            return apology("no amount added")
        else:
            username = db.execute("SELECT username FROM users where id = ?", session['user_id'])
            deposit_amount = float(request.form.get("deposit"))
            # Add cash to the users table
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", deposit_amount, session['user_id'])
            # Add transaction to the transactions table
            db.execute("INSERT INTO deposits (date, time , action , amount, user_id) VALUES (DATE(CURRENT_TIMESTAMP), TIME(CURRENT_TIMESTAMP), ?, ?, ?)", "DEPOSIT", deposit_amount, session['user_id'], username[0]['username'])
            return redirect("/")
    else:
        return render_template("deposit.html")

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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        stock = lookup(request.form.get("symbol"))
        print(stock)
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol")
        if stock is None :
            return apology("must provide valid stock symbol")
        else:
            return render_template("quoted.html", name=stock['name'], price=usd(stock['price']), symbol=stock['symbol'])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

   # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        tpassword = request.form.get("password")
        cpassword = request.form.get("confirmation")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not tpassword or not cpassword:
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) == 1:
            return apology("username already taken", 400)

        # Ensure Passwords match
        if tpassword != cpassword:
            return apology("password's do not match", 400)
        # if username is in finance:
        #     return apology()
        # if not username or not tpassword or not cpassword:
        #     return apology()
        # if tpassword != cpassword:
        #     return apology()
        hash = generate_password_hash(tpassword)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        return render_template("login.html")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    all_stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session['user_id'])

    if request.method == "POST":

        stock_symbol = request.form.get("symbol")
        shares_ask = float(request.form.get("shares"))
        # if no input of stocks, apology
        if not stock_symbol:
            return apology("must provide a stock symbol")
        if lookup(stock_symbol) is None:
            return apology("must provide a valid stock symbol")
        # if no input of shares, apology
        if not request.form.get("shares"):
            return apology("must provide a no. of shares")
        # if not (request.form.get("shares")).isalpha():
        #     return apology("must provide a valid no. of shares")
        # if request.form.get("shares") < 0:
        #     return apology("must provide a no. of shares")

        stock_info = lookup(stock_symbol)
        share_price = stock_info['price']

        # Go through each row of all_stocks
        for stock in all_stocks:

            # Check if Stock Present, If yes
            if stock_symbol == stock['symbol']:

                # Check if no. of shares available, If yes
                if float(shares_ask) <= float(stock['shares']):

                    # Make a transaction history of SELL to track
                    db.execute("INSERT INTO transactions (date, time, action, stock, symbol, shares, cost, user_id, username) VALUES (DATE(CURRENT_TIMESTAMP), TIME(CURRENT_TIMESTAMP), ?, ?, ?, ?, ?, ?, ?)", "SELL", stock['stock'], stock['symbol'], shares_ask, share_price, session['user_id'], stock['username'])

                    # Remove those shares from the stocks table
                    db.execute("UPDATE stocks SET shares = shares - ? WHERE stocks.symbol = ? AND user_id = ?", shares_ask, stock_symbol, session['user_id'])

                    # Add the sold shares money to the users table
                    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares_ask * share_price, session['user_id'])

                    # IF after removing those shares, there are 0 shares left, remove the row
                    db.execute("DELETE FROM stocks WHERE shares = ? AND user_id = ?", 0.0, session['user_id'])

                    return redirect("/")

                # If no shares available
                else:
                    return apology("not enough shares")

        # If no
        if stock_symbol != stock['symbol']:
            return apology("this stock is not owned")

    else:
        return render_template("sell.html", stock = all_stocks)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    activity = db.execute("SELECT * FROM transactions WHERE user_id = ?", session['user_id'])

    # All cash balacne info of the User
    cash = (db.execute("SELECT cash FROM users WHERE id = ?", session['user_id']))
    cash_balance = cash[0]['cash']

    for act in activity:
        act['cost'] = usd(act['cost'])

    print(activity)
    return render_template("history.html", transactions=activity, cash_balance=cash_balance)
