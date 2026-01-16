from flask import redirect, render_template, session, g
from functools import wraps
import sqlite3

# Database connection
# Database setup
DATABASE = 'adhd-planner.db'
# Helper function to get a database connection
def get_db():
    if "db" not in g:
        g.db = sqlite3.connect(DATABASE)
        g.db.row_factory = sqlite3.Row
    return g.db
# Make the database accessible via 'db' variable
def close_db(exception):
    db = g.pop("db", None)
    if db is not None:
        db.close()

# Login required decorator
def login_required(f):
    """
    Decorate routes to require login.
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function