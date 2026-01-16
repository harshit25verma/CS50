# ADHD Planner: A productivity tool for ADHD community
#### Video Demo:  <[URL HERE](https://youtu.be/rpovbp-KzNo?si=-tD9AO_zNUyaszBu)>
#### Description:
**ADHD Planner** is a productivity tool designed specifically for individuals with ADHD, addressing challenges that traditional to-do lists and Pomodoro apps often fail to solve. Rather than treating tasks as isolated items or forcing prolonged focus on single activities, this application introduces a sprint-based system that aligns with how ADHD minds naturally work.

## The Problem with Traditional Productivity Tools

People with ADHD face a unique challenge: it's not just about managing time, but about coordinating multiple tasks within fixed time limits while maintaining engagement. Traditional time blocking helps structure the day, but boredom and the need for variety often lead to task-switching and incomplete work. Conversely, forcing extended focus on a single task frequently results in low productivity when attention inevitably drifts elsewhere.

## The Sprint-Based Solution

The core innovation of this tool is the **Sprint** concept. A sprint is a curated collection of related tasks that can be completed together without breaking focus or momentum. By grouping tasks that share the same location, mindset, or context, users can satisfy their need for stimulation while maintaining productivity.

**Example sprints include:**
- Watching a YouTube video while washing dishes
- Listening to a podcast while cleaning
- Studying on a computer while eating

Tasks requiring similar environments or mental states can be organized into one or two sprints with intentional breaks between them. This approach provides the variety ADHD minds crave while ensuring tasks reach completion rather than being abandoned halfway through.

## Key Features

**Flexible Timer System**: Users control whether to time their sprints and can fully adjust timer durations to suit their needs.

**Hierarchical Task Structure**: The application supports sprints containing tasks, which can be further broken down into subtasks, allowing for granular organization without overwhelming complexity.

**Integrated Notepad**: A free-form notes section enables quick brain-dumping and capturing fleeting thoughts without disrupting workflow.

**Dual-Mode Interface**: The application intentionally separates planning from execution:
- **Plan Mode**: Create or delete sprints, tasks, subtasks, and notes; assign timer values
- **Execute Mode**: Complete tasks/subtasks and control the timer (start, pause, reset)

This separation is crucial—it reduces cognitive load during execution by limiting choices and decisions, helping users stay focused and avoid the paralysis that comes with too many options.

## Technical Implementation

The application is built using:
- **Flask** and **Python** for the backend framework
- **Jinja** for templating
- **SQLite** for data persistence (`adhd-planner.db`)
- **JavaScript** for timer functionality

This technology stack was chosen for its simplicity and effectiveness, allowing the application to remain lightweight while delivering robust functionality.

## Future Development

Several features have been intentionally reserved for future development to keep the initial version focused and functional. Planned enhancements include productivity analytics on the Execute page:
- Number of completed sprints
- Break frequency and duration tracking
- Sprint duration analysis
- Overall productivity trends and patterns

These statistics will help users understand their work patterns and optimize their approach over time.

## Personal Motivation

This tool emerged from lived experience. As someone who personally struggles with ADHD, I built this system to address the real, practical challenges that I—and many others—face with conventional productivity tools. Traditional apps often feel like they were designed for neurotypical brains, expecting sustained focus and linear task completion that simply doesn't match ADHD reality.

**ADHD Planner** acknowledges that our brains work differently and embraces that difference rather than fighting it. My hope is that this tool genuinely helps others navigate their days with less frustration and more accomplishment.# ADHD Planner: A productivity tool for ADHD community
#### Video Demo:  <[URL HERE](https://youtu.be/rpovbp-KzNo?si=-tD9AO_zNUyaszBu)>
#### Description:
**ADHD Planner** is a productivity tool designed specifically for individuals with ADHD, addressing challenges that traditional to-do lipastedpls this now,2:45 AMmarkdown# ADHD Planner: A Productivity Tool for the ADHD Community
#### Video Demo: <[URL HERE](https://youtu.be/rpovbp-KzNo?si=-tD9AO_zNUyaszBu)>
#### Description:

**ADHD Planner** is a productivity tool designed specifically for individuals with ADHD, addressing challenges that traditional to-do lists and Pomodoro apps often fail to solve. Rather than treating tasks as isolated items or forcing prolonged focus on single activities, this application introduces a sprint-based system that aligns with how ADHD minds naturally work.

## The Problem with Traditional Productivity Tools

People with ADHD face a unique challenge: it's not just about managing time, but about coordinating multiple tasks within fixed time limits while maintaining engagement. Traditional time blocking helps structure the day, but boredom and the need for variety often lead to task-switching and incomplete work. Conversely, forcing extended focus on a single task frequently results in low productivity when attention inevitably drifts elsewhere.

## The Sprint-Based Solution

The core innovation of this tool is the **Sprint** concept. A sprint is a curated collection of related tasks that can be completed together without breaking focus or momentum. By grouping tasks that share the same location, mindset, or context, users can satisfy their need for stimulation while maintaining productivity.

**Example sprints include:**
- Watching a YouTube video while washing dishes
- Listening to a podcast while cleaning
- Studying on a computer while eating

Tasks requiring similar environments or mental states can be organized into one or two sprints with intentional breaks between them. This approach provides the variety ADHD minds crave while ensuring tasks reach completion rather than being abandoned halfway through.

## Key Features

**Flexible Timer System**: Users control whether to time their sprints and can fully adjust timer durations to suit their needs.

**Hierarchical Task Structure**: The application supports sprints containing tasks, which can be further broken down into subtasks, allowing for granular organization without overwhelming complexity.

**Integrated Notepad**: A free-form notes section enables quick brain-dumping and capturing fleeting thoughts without disrupting workflow.

**Dual-Mode Interface**: The application intentionally separates planning from execution:
- **Plan Mode**: Create or delete sprints, tasks, subtasks, and notes; assign timer values
- **Execute Mode**: Complete tasks/subtasks and control the timer (start, pause, reset)

This separation is crucial—it reduces cognitive load during execution by limiting choices and decisions, helping users stay focused and avoid the paralysis that comes with too many options.

## Technical Implementation

The application is built using:
- **Flask** and **Python** for the backend framework
- **Jinja** for templating
- **SQLite** for data persistence (`adhd-planner.db`)
- **JavaScript** for timer functionality

This technology stack was chosen for its simplicity and effectiveness, allowing the application to remain lightweight while delivering robust functionality.

### Design Choices

I chose to write everything primarily in Python and Jinja since I was most comfortable with these technologies. While the application relies heavily on the local database—which could potentially be handled faster with JavaScript—Python allowed me to focus on building a working prototype without getting overwhelmed by learning new frameworks.

### User Flow

**Registration (`register.html`)**: The registration page accepts any kind of input but does not allow empty fields. Users must provide a username, password, and password confirmation to create an account. This information is stored in `adhd-planner.db`, where a unique `user_id` is assigned to that username and password combination. After successful registration, users are redirected to the login page.

**Login (`login.html`)**: The login page requires a username and password and continues prompting until correct credentials are entered or non-empty fields are provided. Once successfully logged in, users are taken directly to the Execute page.

**Plan Page (`plan.html`)**: Since the Execute page prompts users to add tasks when none exist, users must navigate to the Plan page to set up their workday. The Plan page is divided into three sections:

1. **Left Section - Sprint Management**: Users can add sprints, tasks, and subtasks within those sprints, and assign custom names to sprints.

2. **Center Section - Active Sprints**: Users can view active sprints, select a sprint to see its tasks, and use a timer interface to assign time values.

3. **Right Section - Notepad**: A notepad allows users to enter and save text by pressing the save button.

All values entered by users—sprints, tasks, subtasks, notepad text, and assigned time—are sent to the database and stored in designated tables with additional metadata that can be used later for monitoring purposes.

**Execute Page (`execute.html`)**: Once users have prepared their workday, they can navigate to the Execute page to see their tasks and subtasks displayed as a open list by default. The timer displays the values assigned on the Plan page and includes Start, Pause, and Reset buttons. The status bar remains consistent across pages, and on the right side, there's a random GIF (which may be replaced with productivity analytics in future versions).

### User Interface Details

The styling includes visual feedback to indicate the currently selected page—the Plan and Execute buttons remain enlarged to show which page is active. Each button also has a hover-over function, except for the logo, which is an image that redirects users to the Execute page.

The timer was built using JavaScript with the help of tutorials and AI assistance. As I continue learning JavaScript, I plan to improve the website and its elements in future iterations.

### Backend Architecture (`app.py`)

Everything in `app.py` is interconnected. The application connects the database to the pages, renders them appropriately, blocks access unless users are logged in, provides specific dictionaries for each page, updates the database accordingly, and returns required values with each user interaction.

### Intentional Restrictions in Execute Mode

On the Execute page, users cannot add or remove tasks, nor can they change the timer values. This creates a deliberate barrier that prevents users from doing extra work to modify their plan during execution. By removing the flexibility that normal to-do list apps provide, the application proves to be more efficient for people with ADHD. The simple function of pressing one button to mark tasks as done or undone is particularly helpful for me as an ADHD person—I can focus on my tasks without getting lost in the UI of typical to-do list or Pomodoro apps.

## Future Development

Several features have been intentionally reserved for future development to keep the initial version focused and functional. Planned enhancements include productivity analytics on the Execute page:
- Number of completed sprints
- Break frequency and duration tracking
- Sprint duration analysis
- Overall productivity trends and patterns

These statistics will help users understand their work patterns and optimize their approach over time.

## Personal Motivation

This tool emerged from lived experience. As someone who personally struggles with ADHD, I built this system to address the real, practical challenges that I—and many others—face with conventional productivity tools. Traditional apps often feel like they were designed for neurotypical brains, expecting sustained focus and linear task completion that simply doesn't match ADHD reality.

**ADHD Planner** acknowledges that our brains work differently and embraces that difference rather than fighting it. My hope is that this tool genuinely helps others navigate their days with less frustration and more accomplishment.