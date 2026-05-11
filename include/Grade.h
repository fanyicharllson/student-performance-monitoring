#ifndef GRADE_H
#define GRADE_H

/*
 * ============================================================
 *  FILE: Grade.h
 *  PURPOSE: Represents a grade entry — links a Student to
 *           a Course with a score.
 *
 *  OOP CONCEPT USED:
 *    - Composition: A Student "has-a" collection of Grade objects
 *    - Encapsulation: All fields private, accessed via getters
 * ============================================================
 */

#include <string>
#include "Course.h"
using namespace std;

class Grade {
private:
    Course course;      // The course this grade belongs to (Composition)
    double score;       // Numeric score: 0.0 to 100.0
    string letterGrade; // Computed: A, B, C, D, F
    string semester;    // e.g., "2024-SEM1"

public:
    // Constructor
    Grade(const Course& course, double score, const string& semester);

    // Default constructor (needed when loading from file)
    Grade() : score(0.0), letterGrade("F"), semester("") {}

    // --- Getters ---
    Course getCourse()      const { return course; }
    double getScore()       const { return score; }
    string getLetterGrade() const { return letterGrade; }
    string getSemester()    const { return semester; }

    // --- Setter for score (also auto-updates letter grade) ---
    void setScore(double newScore);

    // Display this grade entry
    void displayGrade() const;

private:
    /*
     * Helper function: converts numeric score to letter grade.
     * Called automatically whenever a score is set.
     * This follows a typical grading scale.
     */
    string computeLetterGrade(double score);
};

#endif // GRADE_H
