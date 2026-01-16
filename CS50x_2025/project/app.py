# Import necessary libraries
import os
from flask import Flask, request, redirect, render_template, session, g
from flask_session import Session
from werkzeug.security import generate_password_hash, check_password_hash
from helpers import login_required, get_db, close_db
from datetime import datetime

                            ##--- APPPLICATION SETUP (Done) ---##
# Configure application
app = Flask(__name__)
# Enable auto-reloading of templates during development
app.config['TEMPLATES_AUTO_RELOAD'] = True              
# use stable secret in env or a dev fallback
app.config["SECRET_KEY"] = os.environ.get("SECRET_KEY", "dev-secret")

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Only for development: disable caching
@app.after_request
def after_request(response):
    """Disable caching so template changes show immediately during dev."""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = "0"
    response.headers["Pragma"] = "no-cache"
    return response

# Helper functions for database connection
app.teardown_appcontext(close_db)

                        ##--------------------------------##


                        ##--- WEB ROUTES(WORKING AREA) ---##

# Route for the EXECUTE page
@app.route('/', methods=['GET', 'POST'])
@login_required
def index():
    db = get_db()
    user_id = session["user_id"]

    if request.method == "POST":
        action= request.form.get("action")
        selected_sprint_id = None

        # Task completed
        if action == "done_task":
            db.execute("UPDATE tasks SET completed_status = 1, completed_datetime = ? WHERE id = ? AND user_id = ?",(datetime.now(), request.form["task_id"], user_id))
            db.commit()

        # Undo task completed
        if action == "undo_task":
            db.execute("UPDATE tasks SET completed_status = 0, completed_datetime = 0 WHERE id = ? AND user_id = ?",(request.form["task_id"], user_id))
            db.commit()

        # Subtask completed
        if action == "done_subtask":
            db.execute("UPDATE subtasks SET completed_status = 1, completed_datetime = ? WHERE id = ? AND user_id = ?",(datetime.now(), request.form["subtask_id"], user_id))
            db.commit()
       
        # Undo subtask completed
        if action == "undo_subtask":
            db.execute("UPDATE subtasks SET completed_status = 0, completed_datetime = 0 WHERE id = ? AND user_id = ?",(request.form["subtask_id"], user_id))
            db.commit()
        
        # Select sprint to view
        if action == "select_sprint":
            selected_sprint_id = int(request.form["sprint_id"])

        sprints = db.execute("SELECT * FROM sprints WHERE user_id = ? AND deleted_status = 0 ORDER by id ASC",(user_id,)).fetchall()
        tasks = db.execute("SELECT * FROM tasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC",(user_id,)).fetchall()
        subtasks = db.execute("SELECT * FROM subtasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC",(user_id,)).fetchall()
        break_time = db.execute("SELECT assigned_time FROM break WHERE user_id = ? ORDER BY edited_datetime DESC LIMIT 1",(session["user_id"],)).fetchone()

        return render_template("execute.html", tasks=tasks, sprints=sprints, subtasks=subtasks, selected_sprint_id=selected_sprint_id, break_time=break_time)

    # Load page with values
    sprints = db.execute("SELECT * FROM sprints WHERE user_id = ? AND deleted_status = 0 ORDER by id ASC",(user_id,)).fetchall()
    tasks = db.execute("SELECT * FROM tasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC",(user_id,)).fetchall()
    subtasks = db.execute("SELECT * FROM subtasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC",(user_id,)).fetchall()
    break_time = db.execute("SELECT assigned_time FROM break WHERE user_id = ? ORDER BY edited_datetime DESC LIMIT 1",(session["user_id"],)).fetchone()

    # # Convert rows → dicts
    # sprints = [dict(sprint) for sprint in sprints_db]
    # tasks = [dict(task) for task in tasks_db]
    # subtasks = [dict(subtask) for subtask in subtasks_db]

    # # Attach subtasks
    # for task in tasks:
    #     task["subtasks"] = db.execute("SELECT * FROM subtasks WHERE task_id = ? AND user_id = ?",(task["id"], user_id)).fetchall()

    return render_template("execute.html", tasks=tasks, sprints=sprints, subtasks=subtasks, break_time=break_time)



# Route for the PLAN page
@app.route('/plan', methods=['GET', 'POST'])
@login_required
def plan():
    db = get_db()
    expand_task_id = None

    if request.method == "POST":
        action = request.form.get("action")
        selected_sprint_id = None

        # ADD SPRINT
        if action == "add_sprint":
            db.execute("INSERT INTO sprints (text, added_datetime, completed_status, completed_datetime, deleted_status, deleted_datetime, user_id) VALUES (?,?,?,?,?,?,?)",(request.form.get("sprint_text"), datetime.now(), 0, 0, 0, 0, session["user_id"]))
            db.commit()

        # DELETE SPRINT
        elif action == "delete_sprint":
            db.execute("UPDATE sprints SET deleted_status = 1, deleted_datetime = ? WHERE id = ? AND user_id = ?",(datetime.now(), request.form.get("sprint_id"), session["user_id"]))
            db.commit()

        # ADD TASK
        elif action == "add_task":
            db.execute("INSERT INTO tasks (text, added_datetime, completed_status, completed_datetime, deleted_status, deleted_datetime, sprint_id, user_id) VALUES (?,?,?,?,?,?,?,?)",(request.form.get("task_text"), datetime.now(), 0, 0, 0, 0, request.form.get("sprint_id"), session["user_id"]))
            db.commit()

        # DELETE TASK
        elif action == "delete_task":
            db.execute("UPDATE tasks SET deleted_status = 1, deleted_datetime = ? WHERE id = ? AND user_id = ?",(datetime.now(), request.form.get("task_id"), session["user_id"]))
            db.commit()

        # ADD SUBTASK
        elif action == "add_subtask":
            db.execute("INSERT INTO subtasks (text, added_datetime, completed_status, completed_datetime, deleted_status, deleted_datetime, task_id, user_id) VALUES (?,?,?,?,?,?,?,?)",(request.form.get("subtask_text"), datetime.now(), 0, 0, 0, 0, request.form.get("task_id"), session["user_id"]))
            db.commit()
            expand_task_id = int(request.form.get("task_id"))

        # DELETE SUBTASK
        elif action == "delete_subtask":
            db.execute("UPDATE subtasks SET deleted_status = 1, deleted_datetime = ? WHERE id = ? AND user_id = ?",(datetime.now(), request.form.get("subtask_id"), session["user_id"]))
            db.commit()
            expand_task_id = int(request.form.get("task_id"))

        # SAVE NOTEPAD
        elif action == "save_notes":
            db.execute("DELETE FROM notepad WHERE user_id = ?", (session["user_id"],))
            db.execute("INSERT INTO notepad (user_id, text, edited_datetime) VALUES (?, ?, ?)",(session["user_id"], request.form.get("notes"), datetime.now()))
            db.commit()

        # Select sprint to view
        if action == "select_sprint":
            selected_sprint_id = int(request.form["sprint_id"])
        
        # Add Break
        if action == "assign_time":
            db.execute("INSERT INTO break (assigned_time, edited_datetime, user_id) VALUES (?, ?, ?)", (request.form["assigned_time"], datetime.now(), session["user_id"]))
            db.commit()

        sprints = db.execute("SELECT * FROM sprints WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        tasks = db.execute("SELECT * FROM tasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        subtasks = db.execute("SELECT * FROM subtasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        notes = db.execute("SELECT text FROM notepad WHERE user_id = ?", (session["user_id"],)).fetchone()
        break_time = db.execute("SELECT assigned_time FROM break WHERE user_id = ? ORDER BY edited_datetime DESC LIMIT 1",(session["user_id"],)).fetchone()
        return render_template("plan.html", expand_task_id=expand_task_id, sprints=sprints, tasks=tasks, subtasks=subtasks, notes=notes, selected_sprint_id=selected_sprint_id, break_time=break_time)

    else:
        sprints = db.execute("SELECT * FROM sprints WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        tasks = db.execute("SELECT * FROM tasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        subtasks = db.execute("SELECT * FROM subtasks WHERE user_id = ? AND deleted_status = 0 ORDER BY id ASC", (session["user_id"],)).fetchall()
        notes = db.execute("SELECT text FROM notepad WHERE user_id = ?", (session["user_id"],)).fetchone()
        break_time = db.execute("SELECT assigned_time FROM break WHERE user_id = ? ORDER BY edited_datetime DESC LIMIT 1",(session["user_id"],)).fetchone()
        return render_template("plan.html", expand_task_id=expand_task_id, sprints=sprints, tasks=tasks, subtasks=subtasks, notes=notes, break_time=break_time)

# Route for the LOGIN page
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    else:
        # Handle login logic here (not implemented)
        db = get_db()
        username = request.form.get("username")
        password = request.form.get("password")
        # Fetch user from database
        user_exists = db.execute("SELECT * FROM users WHERE username = ?", (username,)).fetchone()
        if user_exists and check_password_hash(user_exists["hash"], password):
            session["user_id"] = user_exists["id"]
            return redirect('/')
        if not username or not password:
            return redirect('/')
        else:
            return redirect('/')

# Route for the LOGOUT page
@app.route('/logout')
def logout():
    # Clear the session
    session.clear()
    return redirect('/login')

# Route for the REGISTER page
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')
    else:
        # 
        db = get_db()
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")
        # Check if username is taken
        username_taken = db.execute("SELECT * FROM users WHERE username = ?", (username,)).fetchone()
        # Validation checks
        if username_taken:
            return render_template('register.html')
        if password != confirm_password:
            return render_template('register.html')
        if not username or not password:
            return render_template('register.html')
        else:
            # Further registration logic (e.g., hashing password, storing user) goes here
            password_hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", (username, password_hash))
            db.commit()
            return redirect('/login')
        
# 

                        ##--------------------------------##

                        ##---  RUN APPLICATION (Done)  ---##
# Run the application
if __name__ == "__main__":
    # Run directly for development (enables reloader/debug if needed)
    app.run(debug=True, host="0.0.0.0", port=5000, use_reloader=True)

                        ##--------------------------------##