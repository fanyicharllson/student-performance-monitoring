/*
 * ============================================================
 *  FILE: SystemManager.cpp
 *  PURPOSE: Main controller — menus, user interaction, coordination
 * ============================================================
 */

#include "SystemManager.h"
#include "PerformanceAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <limits>    // For numeric_limits — used in input clearing
#include <algorithm> // For find_if
using namespace std;

// Constructor: load data and set up a default admin
SystemManager::SystemManager()
    : fileManager("data/"), currentAdmin(nullptr), isRunning(true) {

    loadData();  // Load saved students, courses, grades from files

    // Create a hardcoded admin account for demonstration
    // In a real system, admins would be stored in a file too
    currentAdmin = new Admin("ADMIN001", "System Admin", "admin@ictu.cm",
                             "Computer Science", "admin123");
}

SystemManager::~SystemManager() {
    saveData();           // Auto-save everything on exit
    delete currentAdmin;  // Free heap memory (we used 'new' in constructor)
}

// ---- MAIN RUN LOOP ----
void SystemManager::run() {
    printHeader("AI-Based Student Performance Monitoring System");
    cout << "Welcome! Please login to continue.\n" << endl;

    // Require admin login before anything else
    if (!adminLogin()) {
        cout << "Login failed. Exiting..." << endl;
        return;
    }

    // Main application loop
    while (isRunning) {
        showMainMenu();

        int choice = getValidInt(0, 5);
        switch (choice) {
            case 1: showStudentMenu(); break;
            case 2: showCourseMenu();  break;
            case 3: showReportMenu();  break;
            case 4:
                printHeader("All Students");
                listAllStudents();
                break;
            case 0:
                cout << "\nSaving data and exiting... Goodbye!\n" << endl;
                isRunning = false;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    }
}

// ---- MENUS ----

void SystemManager::showMainMenu() {
    printSeparator();
    cout << "  MAIN MENU" << endl;
    printSeparator();
    cout << "  1. Student Management" << endl;
    cout << "  2. Course Management"  << endl;
    cout << "  3. Reports & Analysis" << endl;
    cout << "  4. List All Students"  << endl;
    cout << "  0. Exit"               << endl;
    printSeparator();
    cout << "Enter choice: ";
}

void SystemManager::showStudentMenu() {
    bool back = false;
    while (!back) {
        printSeparator('-');
        cout << "  STUDENT MANAGEMENT" << endl;
        printSeparator('-');
        cout << "  1. Add Student"        << endl;
        cout << "  2. Remove Student"     << endl;
        cout << "  3. Search Student"     << endl;
        cout << "  4. Update Student"     << endl;
        cout << "  5. Add Grade to Student" << endl;
        cout << "  6. View Student Grades"  << endl;
        cout << "  0. Back"              << endl;
        printSeparator('-');
        cout << "Enter choice: ";

        int choice = getValidInt(0, 6);
        switch (choice) {
            case 1: addStudent();          break;
            case 2: removeStudent();       break;
            case 3: searchStudent();       break;
            case 4: updateStudent();       break;
            case 5: addGradeToStudent();   break;
            case 6: viewStudentGrades();   break;
            case 0: back = true;           break;
        }
    }
}

void SystemManager::showReportMenu() {
    bool back = false;
    while (!back) {
        printSeparator('-');
        cout << "  REPORTS & AI ANALYSIS" << endl;
        printSeparator('-');
        cout << "  1. Individual Student Report"  << endl;
        cout << "  2. Full Class Report"          << endl;
        cout << "  3. At-Risk Students"           << endl;
        cout << "  4. Class Statistics Summary"   << endl;
        cout << "  0. Back"                       << endl;
        printSeparator('-');
        cout << "Enter choice: ";

        int choice = getValidInt(0, 4);
        switch (choice) {
            case 1: viewStudentReport();    break;
            case 2: viewClassReport();      break;
            case 3: viewAtRiskStudents();   break;
            case 4: viewClassStatistics();  break;
            case 0: back = true;            break;
        }
    }
}

void SystemManager::showCourseMenu() {
    bool back = false;
    while (!back) {
        printSeparator('-');
        cout << "  COURSE MANAGEMENT" << endl;
        printSeparator('-');
        cout << "  1. Add Course"   << endl;
        cout << "  2. List Courses" << endl;
        cout << "  0. Back"         << endl;
        printSeparator('-');
        cout << "Enter choice: ";

        int choice = getValidInt(0, 2);
        switch (choice) {
            case 1: addCourse();    break;
            case 2: listCourses();  break;
            case 0: back = true;    break;
        }
    }
}

// ---- AUTHENTICATION ----

bool SystemManager::adminLogin() {
    cout << "Admin ID   : ";
    string id;
    getline(cin, id);

    cout << "Access Code: ";
    string code;
    getline(cin, code);

    // Check against the hardcoded admin
    if (currentAdmin && currentAdmin->getId() == id && currentAdmin->verifyCode(code)) {
        cout << "\n✅ Login successful! Welcome, " << currentAdmin->getName() << ".\n" << endl;
        return true;
    }

    cout << "\n❌ Invalid credentials." << endl;
    return false;
}

// ---- STUDENT OPERATIONS ----

void SystemManager::addStudent() {
    printHeader("Add New Student");

    string id = getValidString("Enter Student ID (e.g., STU001): ");
    if (studentExists(id)) {
        cout << "ERROR: Student ID '" << id << "' already exists." << endl;
        return;
    }

    string name  = getValidString("Enter Full Name: ");
    string email = getValidString("Enter Email: ");
    string dept  = getValidString("Enter Department (e.g., Computer Science): ");
    string level = getValidString("Enter Level (e.g., Level 200): ");
    string year  = getValidString("Enter Enrollment Year (e.g., 2023): ");

    students.emplace_back(id, name, email, dept, level, year);
    saveData();  // Save immediately after adding

    cout << "\n✅ Student '" << name << "' added successfully!" << endl;
}

void SystemManager::removeStudent() {
    printHeader("Remove Student");
    string id = getValidString("Enter Student ID to remove: ");

    // Find and remove the student using a lambda (anonymous function)
    auto it = find_if(students.begin(), students.end(),
                      [&id](const Student& s) { return s.getId() == id; });

    if (it == students.end()) {
        cout << "ERROR: Student with ID '" << id << "' not found." << endl;
        return;
    }

    cout << "Removing: " << it->getName() << endl;
    cout << "Are you sure? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore();  // Clear newline from buffer

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(it);
        saveData();
        cout << "✅ Student removed." << endl;
    } else {
        cout << "Operation cancelled." << endl;
    }
}

void SystemManager::searchStudent() {
    printHeader("Search Student");
    string query = getValidString("Enter Student ID or Name to search: ");

    bool found = false;
    for (const Student& s : students) {
        // Case-insensitive partial match on name or exact match on ID
        if (s.getId() == query || s.getName().find(query) != string::npos) {
            s.displayInfo();
            found = true;
        }
    }

    if (!found) cout << "No student found matching '" << query << "'." << endl;
}

void SystemManager::listAllStudents() {
    if (students.empty()) {
        cout << "No students registered yet." << endl;
        return;
    }

    cout << left
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(20) << "Department"
         << setw(12) << "Level"
         << setw(8)  << "GPA"
         << "Status" << endl;
    printSeparator('-');

    for (const Student& s : students) {
        s.displayInfo();  // Calls Student's overridden version (polymorphism)
    }
    cout << "\nTotal: " << students.size() << " student(s)" << endl;
}

void SystemManager::updateStudent() {
    printHeader("Update Student Info");
    string id = getValidString("Enter Student ID to update: ");

    Student* s = findStudentById(id);
    if (!s) { cout << "Student not found." << endl; return; }

    cout << "Updating: " << s->getName() << endl;
    cout << "New name (press Enter to skip): ";
    string name;
    getline(cin, name);
    if (!name.empty()) s->setName(name);

    cout << "New email (press Enter to skip): ";
    string email;
    getline(cin, email);
    if (!email.empty()) s->setEmail(email);

    cout << "New department (press Enter to skip): ";
    string dept;
    getline(cin, dept);
    if (!dept.empty()) s->setDepartment(dept);

    saveData();
    cout << "✅ Student updated." << endl;
}

// ---- GRADE OPERATIONS ----

void SystemManager::addGradeToStudent() {
    printHeader("Add Grade to Student");

    string studentId = getValidString("Enter Student ID: ");
    Student* s = findStudentById(studentId);
    if (!s) { cout << "Student not found." << endl; return; }

    if (courses.empty()) {
        cout << "No courses available. Please add courses first." << endl;
        return;
    }

    listCourses();
    string courseCode = getValidString("Enter Course Code: ");
    Course* c = findCourseByCode(courseCode);
    if (!c) { cout << "Course not found." << endl; return; }

    cout << "Enter Score (0 - 100): ";
    double score = getValidScore();

    string semester = getValidString("Enter Semester (e.g., 2024-SEM1): ");

    s->addGrade(Grade(*c, score, semester));
    saveData();

    cout << "✅ Grade added successfully for " << s->getName() << endl;
}

void SystemManager::viewStudentGrades() {
    string id = getValidString("Enter Student ID: ");
    Student* s = findStudentById(id);
    if (!s) { cout << "Student not found." << endl; return; }
    s->displayAcademicReport();
}

// ---- COURSE OPERATIONS ----

void SystemManager::addCourse() {
    printHeader("Add New Course");
    string code = getValidString("Enter Course Code (e.g., CS301): ");
    string name = getValidString("Enter Course Name: ");
    cout << "Enter Credit Hours (1-6): ";
    int credits = getValidInt(1, 6);

    courses.emplace_back(code, name, credits);
    saveData();
    cout << "✅ Course added." << endl;
}

void SystemManager::listCourses() {
    printHeader("Course Catalog");
    if (courses.empty()) { cout << "No courses added yet." << endl; return; }

    cout << left << setw(10) << "Code" << setw(40) << "Name" << "Credits" << endl;
    printSeparator('-');
    for (const Course& c : courses) c.displayInfo();
}

// ---- REPORTS ----

void SystemManager::viewStudentReport() {
    string id = getValidString("Enter Student ID: ");
    Student* s = findStudentById(id);
    if (!s) { cout << "Student not found." << endl; return; }
    PerformanceAnalyzer::generateStudentReport(*s);
}

void SystemManager::viewClassReport() {
    PerformanceAnalyzer::generateClassReport(students);
}

void SystemManager::viewAtRiskStudents() {
    printHeader("At-Risk Students");
    bool anyFound = false;
    for (const Student& s : students) {
        if (PerformanceAnalyzer::isAtRisk(s)) {
            s.displayInfo();
            cout << "  → " << s.getRecommendation() << "\n" << endl;
            anyFound = true;
        }
    }
    if (!anyFound) cout << "✅ No at-risk students detected." << endl;
}

void SystemManager::viewClassStatistics() {
    PerformanceAnalyzer::printClassStatistics(students);
}

// ---- HELPERS ----

Student* SystemManager::findStudentById(const string& id) {
    for (Student& s : students) {
        if (s.getId() == id) return &s;
    }
    return nullptr;  // Not found
}

Course* SystemManager::findCourseByCode(const string& code) {
    for (Course& c : courses) {
        if (c.getCourseCode() == code) return &c;
    }
    return nullptr;
}

bool SystemManager::studentExists(const string& id) const {
    for (const Student& s : students) {
        if (s.getId() == id) return true;
    }
    return false;
}

double SystemManager::getValidScore() {
    double score;
    while (true) {
        cin >> score;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cin.fail() || score < 0.0 || score > 100.0) {
            cin.clear();  // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid score. Enter a value between 0 and 100: ";
        } else break;
    }
    return score;
}

int SystemManager::getValidInt(int min, int max) {
    int value;
    while (true) {
        cin >> value;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number (" << min << "-" << max << "): ";
        } else break;
    }
    return value;
}

string SystemManager::getValidString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) break;
        cout << "Input cannot be empty." << endl;
    }
    return value;
}

void SystemManager::printSeparator(char c, int length) const {
    cout << string(length, c) << endl;  // Repeat char 'length' times
}

void SystemManager::printHeader(const string& title) const {
    cout << "\n";
    printSeparator();
    cout << "  " << title << endl;
    printSeparator();
}

void SystemManager::loadData() {
    students = fileManager.loadStudents();
    courses  = fileManager.loadCourses();
    fileManager.loadGrades(students, courses);
}

void SystemManager::saveData() {
    fileManager.saveStudents(students);
    fileManager.saveCourses(courses);
    fileManager.saveGrades(students);
}
