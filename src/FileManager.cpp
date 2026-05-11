/*
 * ============================================================
 *  FILE: FileManager.cpp
 *  PURPOSE: File I/O — saves and loads all system data.
 *
 *  FILE FORMAT (pipe-delimited for simplicity):
 *    students.txt : ID|Name|Email|Department|Level|EnrollYear
 *    courses.txt  : Code|Name|Credits
 *    grades.txt   : StudentID|CourseCode|Score|Semester
 * ============================================================
 */

#include "FileManager.h"
#include <fstream>    // For ifstream (read) and ofstream (write)
#include <sstream>    // For stringstream — splits lines by delimiter
#include <iostream>
#ifdef _WIN32
#include <direct.h>   // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir (directory creation)
#endif
using namespace std;

FileManager::FileManager(const string& dataDir) : dataDirectory(dataDir) {
    ensureDataDirectoryExists();
}

void FileManager::ensureDataDirectoryExists() const {
// Cross-platform directory creation
#ifdef _WIN32
    _mkdir(dataDirectory.c_str());      // Windows
#else
    mkdir(dataDirectory.c_str(), 0755); // Linux / macOS
#endif
}

string FileManager::getFilePath(const string& filename) const {
    return dataDirectory + filename;
}

bool FileManager::fileExists(const string& filename) const {
    // Try to open the file — if it opens, it exists
    ifstream f(getFilePath(filename));
    return f.good();
}

// ---- SAVE STUDENTS ----
bool FileManager::saveStudents(const vector<Student>& students) {
    // ofstream opens a file for writing (creates it if not exists)
    ofstream file(getFilePath("students.txt"));
    if (!file.is_open()) {
        cerr << "ERROR: Could not open students.txt for writing." << endl;
        return false;
    }

    // Write each student as one line: field1|field2|field3...
    for (const Student& s : students) {
        file << s.getId()             << "|"
             << s.getName()           << "|"
             << s.getEmail()          << "|"
             << s.getDepartment()     << "|"
             << s.getLevel()          << "|"
             << s.getEnrollmentYear() << "\n";
    }
    file.close();
    return true;
}

// ---- LOAD STUDENTS ----
vector<Student> FileManager::loadStudents() {
    vector<Student> students;

    // ifstream opens a file for reading
    ifstream file(getFilePath("students.txt"));
    if (!file.is_open()) return students;  // Return empty if file doesn't exist

    string line;
    // getline() reads one line at a time
    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip blank lines

        // Use stringstream to split by '|' delimiter
        stringstream ss(line);
        string id, name, email, dept, level, year;

        getline(ss, id,    '|');
        getline(ss, name,  '|');
        getline(ss, email, '|');
        getline(ss, dept,  '|');
        getline(ss, level, '|');
        getline(ss, year,  '|');

        // Construct a Student object and add to list
        students.emplace_back(id, name, email, dept, level, year);
    }
    file.close();
    return students;
}

// ---- SAVE COURSES ----
bool FileManager::saveCourses(const vector<Course>& courses) {
    ofstream file(getFilePath("courses.txt"));
    if (!file.is_open()) {
        cerr << "ERROR: Could not open courses.txt for writing." << endl;
        return false;
    }

    for (const Course& c : courses) {
        file << c.getCourseCode() << "|"
             << c.getCourseName() << "|"
             << c.getCreditHours() << "\n";
    }
    file.close();
    return true;
}

// ---- LOAD COURSES ----
vector<Course> FileManager::loadCourses() {
    vector<Course> courses;
    ifstream file(getFilePath("courses.txt"));
    if (!file.is_open()) return courses;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string code, name, creditsStr;

        getline(ss, code,       '|');
        getline(ss, name,       '|');
        getline(ss, creditsStr, '|');

        // stoi() converts string to integer
        int credits = 0;
        try { credits = stoi(creditsStr); }
        catch (...) { credits = 3; }  // Default to 3 if parse fails

        courses.emplace_back(code, name, credits);
    }
    file.close();
    return courses;
}

// ---- SAVE GRADES ----
bool FileManager::saveGrades(const vector<Student>& students) {
    ofstream file(getFilePath("grades.txt"));
    if (!file.is_open()) {
        cerr << "ERROR: Could not open grades.txt for writing." << endl;
        return false;
    }

    // Each grade is stored as: StudentID|CourseCode|Score|Semester
    for (const Student& s : students) {
        for (const Grade& g : s.getGrades()) {
            file << s.getId()                        << "|"
                 << g.getCourse().getCourseCode()    << "|"
                 << g.getScore()                     << "|"
                 << g.getSemester()                  << "\n";
        }
    }
    file.close();
    return true;
}

// ---- LOAD GRADES ----
bool FileManager::loadGrades(vector<Student>& students, const vector<Course>& courses) {
    ifstream file(getFilePath("grades.txt"));
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string studentId, courseCode, scoreStr, semester;

        getline(ss, studentId,  '|');
        getline(ss, courseCode, '|');
        getline(ss, scoreStr,   '|');
        getline(ss, semester,   '|');

        // Find the matching student
        Student* targetStudent = nullptr;
        for (Student& s : students) {
            if (s.getId() == studentId) {
                targetStudent = &s;
                break;
            }
        }
        if (!targetStudent) continue;  // Student not found — skip

        // Find the matching course
        const Course* targetCourse = nullptr;
        for (const Course& c : courses) {
            if (c.getCourseCode() == courseCode) {
                targetCourse = &c;
                break;
            }
        }
        if (!targetCourse) continue;  // Course not found — skip

        // Parse score
        double score = 0.0;
        try { score = stod(scoreStr); }   // stod() converts string to double
        catch (...) { continue; }

        // Add the grade to the student
        targetStudent->addGrade(Grade(*targetCourse, score, semester));
    }
    file.close();
    return true;
}
