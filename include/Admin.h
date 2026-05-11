#ifndef ADMIN_H
#define ADMIN_H

/*
 * ============================================================
 *  FILE: Admin.h
 *  PURPOSE: Represents an admin/lecturer — INHERITS from User.
 *           Admin has elevated permissions to manage students.
 *
 *  OOP CONCEPTS USED:
 *    - Inheritance: Admin extends User (Admin IS-A User)
 *    - Polymorphism: Overrides displayInfo() and getRole()
 * ============================================================
 */

#include <string>
#include "User.h"
using namespace std;

class Admin : public User {   // Admin inherits from User
private:
    string department;    // Department the admin manages
    string adminCode;     // Admin access code (simple auth)

public:
    // Constructor
    Admin(const string& id, const string& name, const string& email,
          const string& dept, const string& code);

    // --- Getters ---
    string getDepartment() const { return department; }
    string getAdminCode()  const { return adminCode; }

    // Verify if a given code matches this admin's code
    bool verifyCode(const string& code) const { return adminCode == code; }

    /*
     * POLYMORPHISM: Override displayInfo() from User
     * Admin shows different info than Student
     */
    void displayInfo() const override;

    string getRole() const override { return "Admin"; }
};

#endif // ADMIN_H
