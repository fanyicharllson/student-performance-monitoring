/*
 * ============================================================
 *  FILE: Admin.cpp
 *  PURPOSE: Implementation of the Admin class
 * ============================================================
 */

#include "Admin.h"
#include <iostream>
#include <iomanip>
using namespace std;

Admin::Admin(const string& id, const string& name, const string& email,
             const string& dept, const string& code)
    : User(id, name, email),   // Call parent constructor
      department(dept), adminCode(code) {}

/*
 * POLYMORPHISM: Admin's version of displayInfo()
 * shows different fields than Student's version.
 * Same function name, different behavior — that's polymorphism.
 */
void Admin::displayInfo() const {
    cout << "Admin ID    : " << getId()     << endl;
    cout << "Name        : " << getName()   << endl;
    cout << "Email       : " << getEmail()  << endl;
    cout << "Department  : " << department  << endl;
    cout << "Role        : " << getRole()   << endl;
}
