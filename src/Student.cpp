/*
 * ============================================================
 *  FILE: Student.cpp
 *  PURPOSE: Implementation of the Student class
 *           Student inherits from User and adds academic data
 * ============================================================
 */

#include "Student.h"
#include <iostream>
#include <iomanip>
#include <numeric>   // For accumulate() — sums a vector
using namespace std;

// Constructor: call the parent (User) constructor first,
// then initialize Student-specific fields
Student::Student(const string& id, const string& name, const string& email,
                 const string& dept, const string& level, const string& year)
    : User(id, name, email),   // ← calling parent constructor
      department(dept), level(level), enrollmentYear(year) {}

void Student::addGrade(const Grade& grade) {
    // Add a grade entry to this student's grade list
    grades.push_back(grade);
}

bool Student::removeGrade(const string& courseCode) {
    // Loop through grades and remove the one matching the course code
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        if (it->getCourse().getCourseCode() == courseCode) {
            grades.erase(it);  // Remove from vector
            return true;       // Success
        }
    }
    return false;  // Not found
}

double Student::calculateAverage() const {
    if (grades.empty()) return 0.0;

    // Sum all scores using a loop
    double total = 0.0;
    for (const Grade& g : grades) {
        total += g.getScore();
    }
    return total / grades.size();   // Return mean average
}

double Student::calculateGPA() const {
    /*
     * Convert average score to GPA on a 20-point scale.
     * This mimics many Francophone African university systems.
     * Adjust scale to match ICTU's exact policy.
     */
    double avg = calculateAverage();
    if (avg >= 80) return 18.0 + (avg - 80) * 0.1;  // 18–20
    if (avg >= 70) return 16.0 + (avg - 70) * 0.2;  // 16–18
    if (avg >= 60) return 14.0 + (avg - 60) * 0.2;  // 14–16
    if (avg >= 50) return 10.0 + (avg - 50) * 0.4;  // 10–14
    if (avg >= 40) return  7.0 + (avg - 40) * 0.3;  //  7–10
    return avg * 0.175;                               //  0–7
}

PerformanceStatus Student::getPerformanceStatus() const {
    /*
     * RULE-BASED CLASSIFICATION (the "AI" logic):
     * These rules classify the student into a performance tier.
     * This is essentially a decision tree / expert system rule set.
     */
    double gpa = calculateGPA();
    if (gpa >= 16.0) return PerformanceStatus::EXCELLENT;
    if (gpa >= 14.0) return PerformanceStatus::GOOD;
    if (gpa >= 10.0) return PerformanceStatus::AVERAGE;
    if (gpa  >= 7.0) return PerformanceStatus::AT_RISK;
    return PerformanceStatus::FAILING;
}

string Student::getStatusString() const {
    // Convert enum to human-readable string
    switch (getPerformanceStatus()) {
        case PerformanceStatus::EXCELLENT: return "EXCELLENT";
        case PerformanceStatus::GOOD:      return "GOOD";
        case PerformanceStatus::AVERAGE:   return "AVERAGE";
        case PerformanceStatus::AT_RISK:   return "AT RISK";
        case PerformanceStatus::FAILING:   return "FAILING";
        default: return "UNKNOWN";
    }
}

string Student::getRecommendation() const {
    switch (getPerformanceStatus()) {
        case PerformanceStatus::EXCELLENT:
            return "Outstanding performance! Keep it up and consider mentoring peers.";
        case PerformanceStatus::GOOD:
            return "Good work! Focus on weak subjects to push toward excellence.";
        case PerformanceStatus::AVERAGE:
            return "Meeting minimum requirements. Increase study hours and seek help early.";
        case PerformanceStatus::AT_RISK:
            return "WARNING: GPA below safe threshold. Immediate academic counseling recommended.";
        case PerformanceStatus::FAILING:
            return "URGENT: Student is failing. Intervention required. Contact lecturer immediately.";
        default:
            return "No recommendation available.";
    }
}

/*
 * POLYMORPHISM IN ACTION:
 * This is the overridden version of User::displayInfo().
 * When we call displayInfo() on a User* pointer that actually
 * holds a Student, THIS function runs — not User's version.
 * That is runtime polymorphism via virtual functions.
 */
void Student::displayInfo() const {
    cout << left
         << setw(12) << getId()
         << setw(25) << getName()
         << setw(20) << getDepartment()
         << setw(12) << getLevel()
         << setw(8)  << fixed << setprecision(2) << calculateGPA()
         << getStatusString()
         << endl;
}

void Student::displayAcademicReport() const {
    cout << "\n========================================" << endl;
    cout << "       ACADEMIC REPORT" << endl;
    cout << "========================================" << endl;
    cout << "Student ID  : " << getId()           << endl;
    cout << "Name        : " << getName()          << endl;
    cout << "Email       : " << getEmail()         << endl;
    cout << "Department  : " << department         << endl;
    cout << "Level       : " << level              << endl;
    cout << "Enroll Year : " << enrollmentYear     << endl;
    cout << "----------------------------------------" << endl;

    if (grades.empty()) {
        cout << "No grades recorded yet." << endl;
    } else {
        cout << left
             << setw(10) << "Code"
             << setw(35) << "Course"
             << setw(10) << "Score"
             << setw(5)  << "Grade"
             << "Semester" << endl;
        cout << "----------------------------------------" << endl;

        // Display each grade
        for (const Grade& g : grades) {
            g.displayGrade();
        }

        cout << "----------------------------------------" << endl;
        cout << fixed << setprecision(2);
        cout << "Average Score : " << calculateAverage() << " / 100" << endl;
        cout << "GPA           : " << calculateGPA()     << " / 20"  << endl;
        cout << "Status        : " << getStatusString()             << endl;
    }

    cout << "========================================" << endl;
    cout << "RECOMMENDATION:" << endl;
    cout << getRecommendation() << endl;
    cout << "========================================\n" << endl;
}
