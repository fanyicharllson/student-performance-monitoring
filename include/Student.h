#ifndef STUDENT_H
#define STUDENT_H

/*
 * ============================================================
 *  FILE: Student.h
 *  PURPOSE: Represents a student — INHERITS from User.
 *
 *  OOP CONCEPTS USED:
 *    - Inheritance: Student extends User (Student IS-A User)
 *    - Polymorphism: Overrides displayInfo() and getRole()
 *    - Composition: Student HAS-A vector of Grade objects
 *    - Encapsulation: Private fields, public interface
 * ============================================================
 */

#include <string>
#include <vector>
#include "User.h"
#include "Grade.h"
using namespace std;

// Enum for classification result — clean and readable
enum class PerformanceStatus {
    EXCELLENT,   // GPA >= 16 (ICTU scale)
    GOOD,        // GPA >= 14
    AVERAGE,     // GPA >= 10
    AT_RISK,     // GPA >= 7
    FAILING      // GPA < 7
};

class Student : public User {   // "public User" means Student INHERITS from User
private:
    string department;          // e.g., "Computer Science"
    string level;               // e.g., "Level 300"
    vector<Grade> grades;       // Composition: Student has a list of grades
    string enrollmentYear;      // e.g., "2022"

public:
    // Constructor — calls parent (User) constructor with base info
    Student(const string& id, const string& name, const string& email,
            const string& dept, const string& level, const string& year);

    // Default constructor
    Student() : User("", "", ""), department(""), level(""), enrollmentYear("") {}

    // --- Getters ---
    string getDepartment()    const { return department; }
    string getLevel()         const { return level; }
    string getEnrollmentYear() const { return enrollmentYear; }
    const vector<Grade>& getGrades() const { return grades; }

    // --- Setters ---
    void setDepartment(const string& dept) { department = dept; }
    void setLevel(const string& lvl)      { level = lvl; }

    // Add a grade record to this student
    void addGrade(const Grade& grade);

    // Remove a grade by course code
    bool removeGrade(const string& courseCode);

    // --- Performance Calculations ---
    // Calculate average score across all grades
    double calculateAverage() const;

    // Calculate GPA on a 20-point scale (ICTU style)
    double calculateGPA() const;

    // Get performance classification (the "AI" part)
    PerformanceStatus getPerformanceStatus() const;

    // Get a human-readable string of the status
    string getStatusString() const;

    // Get recommended action based on performance
    string getRecommendation() const;

    /*
     * POLYMORPHISM IN ACTION:
     * This overrides the pure virtual function from User.
     * The "override" keyword confirms this is intentional.
     */
    void displayInfo() const override;

    // Also override getRole() to return "Student"
    string getRole() const override { return "Student"; }

    // Display full academic report
    void displayAcademicReport() const;
};

#endif // STUDENT_H
