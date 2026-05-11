#ifndef COURSE_H
#define COURSE_H

/*
 * ============================================================
 *  FILE: Course.h
 *  PURPOSE: Represents a course/subject in the system.
 *
 *  OOP CONCEPT USED:
 *    - Encapsulation: All data is private with getters/setters
 *    - Composition: Student "has-a" list of Courses (via Grade)
 * ============================================================
 */

#include <string>
using namespace std;

class Course {
private:
    string courseCode;    // e.g., "CS101"
    string courseName;    // e.g., "Introduction to Programming"
    int creditHours;      // e.g., 3

public:
    // Constructor
    Course(const string& code, const string& name, int credits);

    // Default constructor (needed for file loading)
    Course() : courseCode(""), courseName(""), creditHours(0) {}

    // --- Getters ---
    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
    int    getCreditHours() const { return creditHours; }

    // --- Setters ---
    void setCourseName(const string& name) { courseName = name; }
    void setCreditHours(int credits)       { creditHours = credits; }

    // Display course info to console
    void displayInfo() const;
};

#endif // COURSE_H
