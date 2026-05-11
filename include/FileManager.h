#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

/*
 * ============================================================
 *  FILE: FileManager.h
 *  PURPOSE: Handles saving and loading data to/from files.
 *           This gives the system PERSISTENT STORAGE —
 *           data survives after the program closes.
 *
 *  OOP CONCEPT USED:
 *    - Encapsulation: All file I/O logic is in one place
 *    - Single Responsibility: Only handles reading/writing
 *
 *  FILE FORMAT: Simple pipe-delimited text files (easy to read)
 *    students.txt  — student records
 *    courses.txt   — course catalog
 *    grades.txt    — grade records (linked by student ID + course code)
 * ============================================================
 */

#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"
using namespace std;

class FileManager {
private:
    string dataDirectory;   // Path to the data folder

public:
    // Constructor — sets the data directory path
    explicit FileManager(const string& dataDir = "data/");

    // ---- Student File Operations ----

    // Save all students to students.txt
    bool saveStudents(const vector<Student>& students);

    // Load all students from students.txt
    vector<Student> loadStudents();

    // ---- Course File Operations ----

    // Save all courses to courses.txt
    bool saveCourses(const vector<Course>& courses);

    // Load all courses from courses.txt
    vector<Course> loadCourses();

    // ---- Grade File Operations ----

    // Save all grades linked to students
    bool saveGrades(const vector<Student>& students);

    // Load grades and attach them to matching students
    bool loadGrades(vector<Student>& students, const vector<Course>& courses);

    // ---- Utility ----

    // Check if a file exists
    bool fileExists(const string& filename) const;

    // Create the data directory if it doesn't exist
    void ensureDataDirectoryExists() const;

    // Get full path to a file in the data directory
    string getFilePath(const string& filename) const;
};

#endif // FILE_MANAGER_H
