# 🎓 AI-Based Student Performance Monitoring System

> A fully functional console-based application built with **C++17** and **OOP principles**,  
> designed to track, analyze, and predict student academic performance.

---

## 📋 Table of Contents

1. [Purpose & Features](#purpose--features)
2. [OOP Design Concepts](#oop-design-concepts)
3. [Class Diagram (UML)](#class-diagram-uml)
4. [System Flowchart](#system-flowchart)
5. [Project Structure](#project-structure)
6. [Setup & Build Instructions](#setup--build-instructions)
7. [Cross-Platform Notes](#cross-platform-notes)
8. [Sample Test Data](#sample-test-data)
9. [Usage Guide](#usage-guide)
10. [AI Classification Logic](#ai-classification-logic)

---

## Purpose & Features

### Purpose
This system helps academic institutions monitor student performance, identify at-risk students early, and provide data-driven recommendations — all using rule-based AI classification built with C++ OOP.

### Core Features
- ✅ **Student Management** — Add, remove, search, update student records
- ✅ **Course Management** — Maintain a course catalog with credit hours
- ✅ **Grade Recording** — Assign grades per course per semester
- ✅ **AI Performance Analysis** — Classify students: Excellent / Good / Average / At-Risk / Failing
- ✅ **Trend Detection** — Detect if performance is improving, declining, or stable
- ✅ **Class Reports** — Full class overview and statistics
- ✅ **At-Risk Alerts** — Identify students needing intervention
- ✅ **File Persistence** — All data saved and restored across sessions
- ✅ **Secure Login** — Admin authentication before system access

---

## OOP Design Concepts

| Concept | Where It's Applied |
|---|---|
| **Abstraction** | `User` is an abstract class with a pure virtual function |
| **Inheritance** | `Student` and `Admin` both inherit from `User` |
| **Polymorphism** | `displayInfo()` behaves differently for Student vs Admin |
| **Encapsulation** | All class fields are `private`, accessed via getters/setters |
| **Composition** | `Student` HAS-A list of `Grade` objects; `SystemManager` HAS-A `FileManager` |

---

## Class Diagram (UML)

```
+---------------------------+
|          User             |   ← Abstract Base Class
|---------------------------|
| - id: string              |
| - name: string            |
| - email: string           |
|---------------------------|
| + getId(): string         |
| + getName(): string       |
| + getEmail(): string      |
| + displayInfo(): void  *  |   ← Pure virtual (abstract)
| + getRole(): string       |
+---------------------------+
           △
           |  (Inheritance)
     ______|________
    |               |
    ▼               ▼
+-------------------+    +-------------------+
|     Student       |    |      Admin        |
|-------------------|    |-------------------|
| - department      |    | - department      |
| - level           |    | - adminCode       |
| - enrollmentYear  |    |-------------------|
| - grades: Grade[] |    | + verifyCode()    |
|-------------------|    | + displayInfo() ◀ |  Override
| + addGrade()      |    +-------------------+
| + calculateGPA()  |
| + getStatus()     |
| + displayInfo() ◀ |    ← Overrides User's version
+-------------------+
        |
        | (Composition — Student HAS-A Grade[])
        ▼
+-------------------+
|       Grade       |
|-------------------|
| - course: Course  |   ← Composition (Grade HAS-A Course)
| - score: double   |
| - letterGrade     |
| - semester        |
|-------------------|
| + getScore()      |
| + displayGrade()  |
+-------------------+
        |
        | (Composition)
        ▼
+-------------------+
|      Course       |
|-------------------|
| - courseCode      |
| - courseName      |
| - creditHours     |
|-------------------|
| + displayInfo()   |
+-------------------+

+-----------------------------+
|    PerformanceAnalyzer      |   ← AI Engine (static methods)
|-----------------------------|
| + generateStudentReport()   |
| + generateClassReport()     |
| + detectTrend()             |
| + isAtRisk()                |
| + printClassStatistics()    |
+-----------------------------+

+-----------------------------+
|       FileManager           |   ← Persistence Layer
|-----------------------------|
| - dataDirectory: string     |
|-----------------------------|
| + saveStudents()            |
| + loadStudents()            |
| + saveGrades()              |
| + loadGrades()              |
+-----------------------------+

+-----------------------------+
|      SystemManager          |   ← Main Controller (Composition)
|-----------------------------|
| - students: Student[]       |   HAS-A
| - courses: Course[]         |   HAS-A
| - fileManager: FileManager  |   HAS-A
| - currentAdmin: Admin*      |   HAS-A
|-----------------------------|
| + run()                     |
+-----------------------------+
```

---

## System Flowchart

```
START
  │
  ▼
┌─────────────────────┐
│   Admin Login       │──── FAIL ──→ EXIT
└─────────────────────┘
          │ SUCCESS
          ▼
┌─────────────────────┐
│     MAIN MENU       │
└─────────────────────┘
     │       │       │
     ▼       ▼       ▼
 Student   Course  Reports
  Mgmt     Mgmt   & Analysis
     │               │
     ▼               ▼
 Add/Remove      ┌─────────────────┐
 Search/Update   │ Select Student  │
     │           └────────┬────────┘
     ▼                    │
 Add Grade ───────────────┘
     │
     ▼
┌────────────────────────────────┐
│   PerformanceAnalyzer (AI)     │
│                                │
│  Calculate Average & GPA       │
│         │                      │
│   GPA >= 16 → EXCELLENT        │
│   GPA >= 14 → GOOD             │
│   GPA >= 10 → AVERAGE          │
│   GPA >=  7 → AT RISK  ──────→ ALERT
│   GPA <   7 → FAILING  ──────→ URGENT ALERT
│                                │
│  Detect Trend (2-half compare) │
│   Improving / Declining / Stable│
└────────────────────────────────┘
          │
          ▼
   Generate Report + Recommendation
          │
          ▼
   Save to File ──→ LOOP BACK TO MENU
          │
          ▼
         EXIT
```

---

## Project Structure

```
student-performance/
├── include/                  # Header files (.h)
│   ├── User.h                # Abstract base class
│   ├── Student.h             # Inherits User
│   ├── Admin.h               # Inherits User
│   ├── Course.h              # Course entity
│   ├── Grade.h               # Grade entity (Composition)
│   ├── PerformanceAnalyzer.h # AI analysis engine
│   ├── FileManager.h         # File I/O handler
│   └── SystemManager.h       # Main controller
│
├── src/                      # Implementation files (.cpp)
│   ├── main.cpp              # Entry point
│   ├── User.cpp
│   ├── Student.cpp
│   ├── Admin.cpp
│   ├── Course.cpp
│   ├── Grade.cpp
│   ├── PerformanceAnalyzer.cpp
│   ├── FileManager.cpp
│   └── SystemManager.cpp
│
├── data/                     # Persistent data files
│   ├── students.txt          # Student records
│   ├── courses.txt           # Course catalog
│   └── grades.txt            # Grade records
│
├── Makefile                  # Build configuration
└── README.md                 # This file
```

---

## Setup & Build Instructions

### Prerequisites

| Tool | Version | Purpose |
|------|---------|---------|
| g++ (GCC) | 7.0+ | C++ compiler |
| make | any | Build automation |

---

### 🐧 Linux / macOS

```bash
# 1. Clone the repository
git clone https://github.com/[yourname]/student-performance-monitor.git
cd student-performance-monitor

# 2. Build the project
make

# 3. Run the application
./student_monitor
```

To clean build files:
```bash
make clean
```

---

### 🪟 Windows (Using MinGW + VS Code)

**Step 1: Install MinGW-w64**
- Download from: https://www.mingw-w64.org/
- During install, select: `x86_64`, `posix`, `seh`
- Add `C:\mingw64\bin` to your **System PATH**

**Step 2: Verify installation**
```cmd
g++ --version
mingw32-make --version
```

**Step 3: Clone and build**
```cmd
git clone https://github.com/[yourname]/student-performance-monitor.git
cd student-performance-monitor
mingw32-make
student_monitor.exe
```

**Alternative — Build manually (no make):**
```cmd
g++ -std=c++17 -Iinclude src/*.cpp -o student_monitor
student_monitor.exe
```

---

### 🖥️ VS Code Setup

1. Install extensions:
   - **C/C++** (Microsoft)
   - **C/C++ Extension Pack**
   - **Code Runner** (optional)

2. Open the project folder in VS Code
3. Press `Ctrl + ` ` ` to open terminal
4. Run `make` (Linux/Mac) or `mingw32-make` (Windows)

---

## Cross-Platform Notes

| Feature | Linux/macOS | Windows |
|---------|-------------|---------|
| Compiler | `g++` | `g++` via MinGW |
| Build | `make` | `mingw32-make` |
| Run | `./student_monitor` | `./student_monitor.exe` |
| Directory creation | `mkdir()` POSIX | `_mkdir()` Win32 |
| File paths | Forward slash `/` | Both `/` and `\` work |

> **Note:** The `FileManager.cpp` uses `#ifdef _WIN32` to handle the  
> platform-specific directory creation function automatically.  
> No code changes needed when switching OS.

---

## Sample Test Data

Pre-loaded sample data is in the `data/` folder:

### `data/students.txt`
```
STU001|Alice Mbarga|alice.mbarga@ictu.cm|Computer Science|Level 200|2023
STU002|Jean-Paul Fotso|jeanpaul.fotso@ictu.cm|Computer Science|Level 300|2022
...
```

### `data/courses.txt`
```
CS101|Introduction to Programming|3
CS201|Data Structures & Algorithms|3
...
```

### `data/grades.txt`
```
STU001|CS101|78|2024-SEM1
STU002|CS301|48|2024-SEM1
...
```

> The system automatically loads these files on startup.  
> Any changes made in the application are saved back to these files.

---

## Usage Guide

### Default Admin Credentials
```
Admin ID   : ADMIN001
Access Code: admin123
```

### Quick Start Flow

1. Login with admin credentials
2. Go to **Course Management** → Add courses (or use pre-loaded ones)
3. Go to **Student Management** → Add students (or use pre-loaded ones)
4. Go to **Student Management** → Add Grade to Student
5. Go to **Reports & AI Analysis** → View Individual Report
6. Select **At-Risk Students** to see who needs help

---

## AI Classification Logic

The system uses a **rule-based expert system** — a core AI technique:

```
GPA Calculation:
  Average Score → mapped to GPA on a 20-point scale

Classification Rules:
  GPA >= 16.0  →  EXCELLENT   →  "Outstanding. Consider scholarships."
  GPA >= 14.0  →  GOOD        →  "Focus on weak subjects."
  GPA >= 10.0  →  AVERAGE     →  "Increase study hours."
  GPA >=  7.0  →  AT RISK     →  "Academic counseling needed."
  GPA  <  7.0  →  FAILING     →  "URGENT: Lecturer intervention required."

Trend Detection:
  Split grades into two halves (chronological order)
  Compare average of first half vs second half:
    Diff > +5  →  Improving
    Diff < -5  →  Declining
    Otherwise  →  Stable
```

*Built as part of ICT University OOP Final Project — C++17*
