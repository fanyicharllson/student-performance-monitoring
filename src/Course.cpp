/*
 * ============================================================
 *  FILE: Course.cpp
 *  PURPOSE: Implementation of the Course class
 * ============================================================
 */

#include "Course.h"
#include <iostream>
#include <iomanip>  // For setw() — controls column width in output
using namespace std;

// Constructor
Course::Course(const string& code, const string& name, int credits)
    : courseCode(code), courseName(name), creditHours(credits) {}

void Course::displayInfo() const {
    // left — left-align text; setw(N) — reserve N characters width
    cout << left
         << setw(10) << courseCode
         << setw(40) << courseName
         << setw(5)  << creditHours << " credit(s)"
         << endl;
}
