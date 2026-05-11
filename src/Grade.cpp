/*
 * ============================================================
 *  FILE: Grade.cpp
 *  PURPOSE: Implementation of the Grade class
 * ============================================================
 */

#include "Grade.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor — automatically computes the letter grade from score
Grade::Grade(const Course& course, double score, const string& semester)
    : course(course), score(score), semester(semester) {
    // Compute letter grade immediately when Grade is created
    letterGrade = computeLetterGrade(score);
}

void Grade::setScore(double newScore) {
    score = newScore;
    // Recompute letter grade whenever score changes
    letterGrade = computeLetterGrade(newScore);
}

/*
 * Converts a numeric score to a letter grade.
 * Scale used here is a common 100-point academic scale.
 * Adjust thresholds to match ICTU's actual grading policy if needed.
 */
string Grade::computeLetterGrade(double score) {
    if (score >= 80) return "A";   // Excellent
    if (score >= 70) return "B";   // Good
    if (score >= 60) return "C";   // Average
    if (score >= 50) return "D";   // Below average but passing
    return "F";                     // Failing
}

void Grade::displayGrade() const {
    cout << left
         << setw(10) << course.getCourseCode()
         << setw(35) << course.getCourseName()
         << setw(10) << fixed << setprecision(1) << score
         << setw(5)  << letterGrade
         << "  [" << semester << "]"
         << endl;
}
