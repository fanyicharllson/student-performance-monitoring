/*
 * ============================================================
 *  FILE: PerformanceAnalyzer.cpp
 *  PURPOSE: Implementation of the AI analysis engine.
 *           All static methods — call without creating an object.
 * ============================================================
 */

#include "PerformanceAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <algorithm>  // For min_element, max_element
using namespace std;

void PerformanceAnalyzer::generateStudentReport(const Student& student) {
    // Just delegate to the student's own report method
    student.displayAcademicReport();

    // Add trend analysis on top
    string trend = detectTrend(student);
    cout << "Performance Trend: " << trend << endl;
    cout << "========================================\n" << endl;
}

void PerformanceAnalyzer::generateClassReport(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the system." << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "         CLASS PERFORMANCE REPORT" << endl;
    cout << "========================================" << endl;
    cout << left
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(10) << "Avg Score"
         << setw(8)  << "GPA"
         << "Status" << endl;
    cout << "----------------------------------------" << endl;

    // Loop through all students and display a summary row
    for (const Student& s : students) {
        cout << left
             << setw(12) << s.getId()
             << setw(25) << s.getName()
             << setw(10) << fixed << setprecision(1) << s.calculateAverage()
             << setw(8)  << fixed << setprecision(2) << s.calculateGPA()
             << s.getStatusString()
             << endl;
    }
    cout << "========================================\n" << endl;
}

string PerformanceAnalyzer::detectTrend(const Student& student) {
    const vector<Grade>& grades = student.getGrades();

    // Need at least 2 grades to detect a trend
    if (grades.size() < 2) return "Not enough data";

    // Split grades into two halves and compare averages
    size_t mid = grades.size() / 2;

    double firstHalfAvg  = 0.0;
    double secondHalfAvg = 0.0;

    for (size_t i = 0; i < mid; i++)
        firstHalfAvg += grades[i].getScore();
    firstHalfAvg /= mid;

    for (size_t i = mid; i < grades.size(); i++)
        secondHalfAvg += grades[i].getScore();
    secondHalfAvg /= (grades.size() - mid);

    // Compare halves to determine trend direction
    double diff = secondHalfAvg - firstHalfAvg;
    if (diff >  5.0) return "📈 Improving";
    if (diff < -5.0) return "📉 Declining";
    return "➡️  Stable";
}

string PerformanceAnalyzer::getRecommendation(PerformanceStatus status, double gpa) {
    switch (status) {
        case PerformanceStatus::EXCELLENT:
            return "Outstanding! Consider applying for scholarships or research programs.";
        case PerformanceStatus::GOOD:
            return "Good performance. Identify weak areas to reach Excellence tier.";
        case PerformanceStatus::AVERAGE:
            return "Passing but room for improvement. Form study groups, attend all classes.";
        case PerformanceStatus::AT_RISK:
            return "WARNING: GPA is " + to_string(gpa).substr(0, 4) +
                   ". Academic intervention recommended immediately.";
        case PerformanceStatus::FAILING:
            return "CRITICAL: Student is failing. Must meet with academic advisor urgently.";
        default:
            return "No data available.";
    }
}

bool PerformanceAnalyzer::isAtRisk(const Student& student) {
    // A student is "at risk" if GPA is below 10 (ICTU passing threshold)
    return student.calculateGPA() < 10.0;
}

void PerformanceAnalyzer::printClassStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to analyze." << endl;
        return;
    }

    // Count students per category
    int excellent = 0, good = 0, average = 0, atRisk = 0, failing = 0;
    double totalGPA = 0.0;
    double maxGPA   = 0.0;
    double minGPA   = 20.0;
    string topStudent, weakestStudent;

    for (const Student& s : students) {
        double gpa = s.calculateGPA();
        totalGPA += gpa;

        // Track highest GPA
        if (gpa > maxGPA) { maxGPA = gpa; topStudent = s.getName(); }
        // Track lowest GPA
        if (gpa < minGPA) { minGPA = gpa; weakestStudent = s.getName(); }

        // Count by status
        switch (s.getPerformanceStatus()) {
            case PerformanceStatus::EXCELLENT: excellent++; break;
            case PerformanceStatus::GOOD:      good++;      break;
            case PerformanceStatus::AVERAGE:   average++;   break;
            case PerformanceStatus::AT_RISK:   atRisk++;    break;
            case PerformanceStatus::FAILING:   failing++;   break;
        }
    }

    double classAvgGPA = totalGPA / students.size();

    cout << "\n========================================" << endl;
    cout << "         CLASS STATISTICS SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << fixed << setprecision(2);
    cout << "Total Students  : " << students.size()  << endl;
    cout << "Class Avg GPA   : " << classAvgGPA      << " / 20" << endl;
    cout << "Highest GPA     : " << maxGPA << " (" << topStudent << ")" << endl;
    cout << "Lowest GPA      : " << minGPA << " (" << weakestStudent << ")" << endl;
    cout << "----------------------------------------" << endl;
    cout << "EXCELLENT  : " << excellent << " student(s)" << endl;
    cout << "GOOD       : " << good      << " student(s)" << endl;
    cout << "AVERAGE    : " << average   << " student(s)" << endl;
    cout << "AT RISK    : " << atRisk    << " student(s)" << endl;
    cout << "FAILING    : " << failing   << " student(s)" << endl;
    cout << "========================================\n" << endl;

    // Flag if class is doing poorly overall
    if (classAvgGPA < 10.0) {
        cout << "⚠️  ALERT: Class average GPA is below passing threshold!" << endl;
        cout << "   Consider reviewing teaching methods or providing extra sessions.\n" << endl;
    }
}
