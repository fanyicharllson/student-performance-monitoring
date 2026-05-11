#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

/*
 * ============================================================
 *  FILE: SystemManager.h
 *  PURPOSE: The main controller of the entire system.
 *           Manages the menu, coordinates between all classes,
 *           and handles the application lifecycle.
 *
 *  OOP CONCEPT USED:
 *    - Composition: SystemManager HAS-A FileManager,
 *      HAS-A vector of Students, HAS-A vector of Courses
 *    - Encapsulation: Internal state hidden, public interface
 *      only exposes run()
 *
 *  DESIGN PATTERN: Controller — this class coordinates
 *    all other classes without doing too much itself.
 * ============================================================
 */

#include <vector>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Admin.h"
#include "FileManager.h"
using namespace std;

class SystemManager {
private:
    vector<Student> students;   // All students in the system (Composition)
    vector<Course>  courses;    // Course catalog (Composition)
    FileManager     fileManager; // File persistence handler (Composition)
    Admin*          currentAdmin; // Currently logged-in admin (nullptr if none)
    bool            isRunning;   // Controls the main loop

public:
    // Constructor — initializes the system and loads saved data
    SystemManager();

    // Destructor — saves data before exit
    ~SystemManager();

    // === MAIN ENTRY POINT ===
    // Call this to start the application — shows the main menu
    void run();

private:
    // ---- Menu Displays ----
    void showMainMenu();
    void showStudentMenu();
    void showReportMenu();
    void showCourseMenu();

    // ---- Authentication ----
    bool adminLogin();

    // ---- Student Operations ----
    void addStudent();
    void removeStudent();
    void searchStudent();
    void listAllStudents();
    void updateStudent();

    // ---- Grade Operations ----
    void addGradeToStudent();
    void viewStudentGrades();

    // ---- Course Operations ----
    void addCourse();
    void listCourses();

    // ---- Report & Analysis Operations ----
    void viewStudentReport();
    void viewClassReport();
    void viewAtRiskStudents();
    void viewClassStatistics();

    // ---- Helper Utilities ----

    // Find a student by ID — returns pointer or nullptr if not found
    Student* findStudentById(const string& id);

    // Find a course by code — returns pointer or nullptr if not found
    Course* findCourseByCode(const string& code);

    // Check if a student ID already exists
    bool studentExists(const string& id) const;

    // Input validation helpers
    double  getValidScore();         // Get a score between 0 and 100
    int     getValidInt(int min, int max); // Get an integer in range
    string  getValidString(const string& prompt); // Get non-empty string

    // Display a separator line for cleaner UI
    void printSeparator(char c = '=', int length = 60) const;
    void printHeader(const string& title) const;

    // Load all data from files on startup
    void loadData();

    // Save all data to files
    void saveData();
};

#endif // SYSTEM_MANAGER_H
