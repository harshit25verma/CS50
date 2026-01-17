# CS50x: Introduction to Computer Science

**Harvard University | 2025**

This repository contains all my problem sets and projects completed for CS50x, Harvard University's introduction to computer science and programming.

---

## 📜 Certificate

**Status:** ✅ Completed

I successfully completed all 10 problem sets and the final project, earning my CS50x certificate.

[View Certificate](./CS50x.pdf) | [Verify on CS50](https://cs50.harvard.edu/certificates/9c434534-b6a6-488d-80ee-461c6625c7b4)

---

## 📚 Course Overview

CS50x teaches the fundamentals of computer science and programming, progressing from low-level C to high-level Python, then into web development with SQL, HTML, CSS, JavaScript, and Flask.

**Duration:** 10 weeks (100+ hours)  
**Languages:** C, Python, SQL, HTML/CSS, JavaScript  
**Framework:** Flask  
**Database:** SQLite  

---

## 🗂️ Repository Structure

```
CS50/
├── Week 1: C Basics
│   ├── mario-less/
│   ├── mario-more/
│   ├── cash/
│   ├── credit/
│   └── me/
│
├── Week 2: Arrays
│   ├── scrabble/
│   ├── readability/
│   └── caesar/
│
├── Week 3: Algorithms
│   ├── sort/
│   ├── plurality/
│   └── runoff/
│
├── Week 4: Memory
│   ├── volume/
│   ├── filter-more/
│   └── recover/
│
├── Week 5: Data Structures
│   ├── inheritance/
│   └── speller/
│
├── Week 6: Python
│   ├── sentimental-hello/
│   ├── sentimental-mario-more/
│   ├── sentimental-cash/
│   ├── sentimental-readability/
│   └── dna/
│
├── Week 7: SQL
│   ├── songs/
│   ├── movies/
│   └── fiftyville/
│
├── Week 8: Web
│   ├── trivia/
│   └── homepage/
│
├── Week 9: Flask
│   ├── birthdays/
│   └── finance/
│
└── Week 10: Final Project
    └── project/
```

---

## 🚀 Problem Sets

### Week 1: C Programming Fundamentals
Introduction to C, data types, operators, and control flow.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Mario (Less)](./mario-less) | Print a right-aligned pyramid | C, nested loops |
| [Mario (More)](./mario-more) | Print adjacent pyramids | C, pattern printing |
| [Cash](./cash) | Calculate minimum coins for change | C, greedy algorithms |
| [Credit](./credit) | Validate credit cards using Luhn's algorithm | C, digit manipulation |

**Key Concepts:** Variables, loops, conditionals, functions, command-line arguments

---

### Week 2: Arrays and Strings
Working with arrays, strings, and cryptography.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Scrabble](./scrabble) | Calculate Scrabble word scores | C, arrays, ASCII |
| [Readability](./readability) | Compute text grade level (Coleman-Liau) | C, string parsing |
| [Caesar](./caesar) | Encrypt text using Caesar cipher | C, modular arithmetic |

**Key Concepts:** Arrays, string manipulation, ASCII values, encryption

---

### Week 3: Algorithms
Sorting, searching, and computational complexity.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Sort](./sort) | Identify sorting algorithms by behavior | Algorithm analysis |
| [Plurality](./plurality) | Simulate plurality voting | C, structs, arrays |
| [Runoff](./runoff) | Implement ranked-choice voting | C, 2D arrays, complex logic |

**Key Concepts:** Big O notation, sorting algorithms, data structures, election systems

---

### Week 4: Memory Management
Pointers, memory allocation, and file I/O.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Volume](./volume) | Modify WAV file volume | C, file I/O, binary data |
| [Filter](./filter-more) | Apply image filters (grayscale, blur, edges) | C, pointers, bitmap manipulation |
| [Recover](./recover) | Recover JPEGs from memory card | C, file signatures, forensics |

**Key Concepts:** Pointers, dynamic memory, file handling, image processing

---

### Week 5: Data Structures
Hash tables, tries, and linked lists.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Inheritance](./inheritance) | Simulate genetic inheritance | C, recursion, trees |
| [Speller](./speller) | Build spell-checker with hash table | C, hash tables, optimization |

**Key Concepts:** Hash functions, linked lists, memory management, performance optimization

**Achievement:** Speller processes 140,000+ words efficiently using custom hash table implementation.

---

### Week 6: Python
Transition from C to Python, introduction to high-level programming.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Hello](./sentimental-hello) | Print "hello, world" | Python |
| [Mario](./sentimental-mario-more) | Rebuild Mario in Python | Python |
| [Cash](./sentimental-cash) | Rebuild Cash in Python | Python |
| [Readability](./sentimental-readability) | Rebuild Readability in Python | Python |
| [DNA](./dna) | Match DNA sequences to individuals | Python, CSV parsing |

**Key Concepts:** Python syntax, lists, dictionaries, file I/O, CSV processing

**Insight:** What took 50+ lines in C became 10-15 lines in Python.

---

### Week 7: SQL and Databases
Relational databases and SQL queries.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Songs](./songs) | Query Spotify database | SQL, SQLite |
| [Movies](./movies) | Query IMDb database | SQL, JOINs |
| [Fiftyville](./fiftyville) | Solve mystery using SQL | SQL, complex queries |

**Key Concepts:** SELECT, JOIN, subqueries, database design, relational data

**Highlight:** Solved an entire detective mystery using only SQL queries across multiple tables.

---

### Week 8: Web Development
HTML, CSS, and JavaScript fundamentals.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Trivia](./trivia) | Interactive quiz game | HTML, CSS, JavaScript |
| [Homepage](./homepage) | Multi-page personal website | HTML, CSS, responsive design |

**Key Concepts:** DOM manipulation, event listeners, CSS layouts, responsive design

---

### Week 9: Flask Web Applications
Full-stack web development with Python and Flask.

| Problem | Description | Tech Stack |
|---------|-------------|------------|
| [Birthdays](./birthdays) | Birthday tracking app | Flask, SQLite, Jinja2 |
| [Finance](./finance) | Stock trading simulator | Flask, API integration, sessions |

**Key Concepts:** Routing, sessions, authentication, form handling, API integration, MVC architecture

**Finance Features:**
- User registration and login with password hashing
- Real-time stock price lookup via API
- Buy/sell stocks with validation
- Portfolio tracking and transaction history

---

### Week 10: Final Project
**[ADHD Planner](./project)** - Full-Stack Productivity Application

A sprint-based task management system designed to reduce cognitive overload for people with ADHD by separating planning from execution.

**Features:**
- User authentication with secure sessions
- Sprint creation and management
- Task breakdown into subtasks
- Focused execution mode with timer
- Complete user data isolation

**Tech Stack:** Python, Flask, SQLite, HTML/CSS, JavaScript, Jinja2

**Engineering Challenges Solved:**
- POST/GET flow debugging
- User data isolation and security
- UI state preservation
- Template/JavaScript separation

[View Project Demo](./project/demo.mp4) | [Read Full Documentation](./project/README.md)

---

## 🛠️ Technologies Used

### Programming Languages
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![SQL](https://img.shields.io/badge/SQL-4479A1?style=for-the-badge&logo=postgresql&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)
![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white)

### Frameworks & Libraries
- **Flask** - Python web framework
- **Jinja2** - Template engine
- **SQLite** - Embedded database
- **Bootstrap** - CSS framework (in some projects)

### Tools & Concepts
- Git & GitHub
- Command-line interface
- Debugging with GDB and Valgrind
- Memory management
- Algorithm analysis
- Database design
- Web security (password hashing, SQL injection prevention)

---

## 📊 Skills Gained

### Computer Science Fundamentals
✅ Algorithm design and analysis (Big O notation)  
✅ Data structures (arrays, linked lists, hash tables, tries)  
✅ Memory management and pointers  
✅ Recursion and trees  
✅ Sorting and searching algorithms  

### Software Development
✅ Full-stack web development  
✅ Database design and SQL  
✅ RESTful API integration  
✅ User authentication and sessions  
✅ MVC architecture  
✅ Version control with Git  

### Problem-Solving
✅ Debugging complex systems  
✅ Breaking down large problems  
✅ Edge case handling  
✅ Code optimization  
✅ Testing and validation  

---

## 🎯 Key Takeaways

### Technical Growth
- **From low-level to high-level:** Started with C (pointers, memory) → ended with Flask (full-stack web apps)
- **End-to-end understanding:** Can build applications from database design to user interface
- **Performance mindset:** Learned to think about time/space complexity and optimization

### Problem-Solving Skills
- **Systematic debugging:** Learned to isolate issues and test hypotheses
- **Edge case thinking:** Always consider what could go wrong
- **Documentation matters:** Clear code comments and READMEs save time

### Real-World Applications
Every problem set taught skills used in production:
- Credit card validation (e-commerce)
- Spell-checking (text editors)
- Image filters (photo apps)
- Database queries (business intelligence)
- Web authentication (every website)

---

## 📈 Statistics

- **Total Problems Solved:** 30+
- **Lines of Code Written:** 5,000+
- **Time Invested:** 100+ hours
- **Languages Learned:** 6 (C, Python, SQL, HTML, CSS, JavaScript)
- **Debugging Sessions:** Too many to count 😅

---

## 🏆 Highlights

### Speller Achievement
Built a spell-checker that processes **140,000+ words** with optimized hash table, achieving performance comparable to staff solution.

### Finance Complexity
Implemented complete stock trading platform with:
- Real-time API integration
- Secure authentication
- Transaction management
- Portfolio tracking

### Final Project
Designed and built a full-stack application solving a real-world problem (ADHD task management) from scratch.

---

## 🚀 What's Next

### Immediate Plans
- Deploy Final Project to cloud (AWS/Heroku)
- Migrate to PostgreSQL for production
- Dockerize applications
- Set up CI/CD pipeline

### Learning Goals
- Advanced algorithms and data structures
- System design and architecture
- DevOps and cloud infrastructure
- Modern frontend frameworks (React)
- Microservices architecture

---

## 🤝 Connect With Me

**GitHub:** [harshit25verma](https://github.com/harshit25verma)  
**LinkedIn:** [harshit25verma](https://www.linkedin.com/in/harshit25verma)
**Email:** harshit25verma@outlook.com

---

## 📝 Notes

### For Recruiters
This repository demonstrates:
- Strong computer science fundamentals
- Full-stack development capabilities
- Problem-solving and debugging skills
- Ability to learn new technologies quickly
- Code organization and documentation

### For Students
If you're taking CS50x:
- Don't skip the lectures—they're amazing
- Start problem sets early
- Use the debugger (`debug50`, `valgrind`)
- Don't be afraid to struggle—that's where learning happens
- The Duck Debugger is your friend 🦆

---

## 🙏 Acknowledgments

**Professor David J. Malan** - For making computer science accessible and exciting  
**CS50 Staff** - For the incredible course design and support  
**CS50 Community** - For help, encouragement, and camaraderie  

---

## 📄 License

This repository contains academic work completed for CS50x 2025.

**Academic Honesty:** All code in this repository is my own work, completed in accordance with the [CS50 Academic Honesty policy](https://cs50.harvard.edu/x/2025/honesty/).

---

## ⭐ Course Recommendation

**If you're interested in learning computer science, I highly recommend CS50x.**

It's free, self-paced, and comprehensive. The learning curve is steep, but that's exactly why it works. You'll struggle, debug for hours, and eventually have those amazing "aha!" moments.

By the end, you won't just know how to code—you'll understand how computers think.

**[Enroll in CS50x](https://cs50.harvard.edu/x/)**

---

<div align="center">

🦆 **"This was CS50!"** 🎓

*Made with ❤️ and lots of debugging*

</div>
