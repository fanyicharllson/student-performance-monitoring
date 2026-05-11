#ifndef PERFORMANCE_ANALYZER_H
#define PERFORMANCE_ANALYZER_H

/*
 * ============================================================
 *  FILE: PerformanceAnalyzer.h
 *  PURPOSE: The "AI" engine of the system.
 *           Analyzes student data, detects risk, and generates
 *           recommendations and reports.
 *
 *  OOP CONCEPT USED:
 *    - Encapsulation: Analysis logic is encapsulated here
 *    - Composition: The system HAS-A PerformanceAnalyzer
 *    - Single Responsibility: This class ONLY does analysis
 *
 *  "AI" APPROACH:
 *    Rule-based classification — we define rules like:
 *      IF average < 50 THEN status = FAILING
 *      IF trend is declining THEN flag = AT_RISK
 *    This is the standard approach for expert systems in C++
 * ============================================================
 */

#include <string>
#include <vector>
#include "Student.h"
using namespace std;

class PerformanceAnalyzer {
public:
    /*
     * Analyze a single student and print a full report.
     * This is the main "AI" function.
     */
    static void generateStudentReport(const Student& student);

    /*
     * Analyze ALL students and find who is at risk.
     * Prints a summary list of students needing attention.
     */
    static void generateClassReport(const vector<Student>& students);

    /*
     * Detect performance trend:
     * Compares first half of grades vs second half.
     * Returns: "Improving", "Declining", "Stable"
     */
    static string detectTrend(const Student& student);

    /*
     * Generate a recommendation message based on status.
     */
    static string getRecommendation(PerformanceStatus status, double gpa);

    /*
     * Risk detection — returns true if student needs urgent attention.
     */
    static bool isAtRisk(const Student& student);

    /*
     * Calculate class statistics: average GPA, highest, lowest.
     */
    static void printClassStatistics(const vector<Student>& students);
};

#endif // PERFORMANCE_ANALYZER_H
