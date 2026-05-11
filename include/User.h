#ifndef USER_H
#define USER_H

/*
 * ============================================================
 *  FILE: User.h
 *  PURPOSE: Abstract base class for all system users.
 *           This is the ROOT of our inheritance tree.
 *
 *  OOP CONCEPT USED:
 *    - Abstraction: User is abstract (cannot be created directly)
 *    - Encapsulation: All fields are private, accessed via getters/setters
 *    - Polymorphism: displayInfo() is a pure virtual function —
 *      every subclass (Student, Admin) MUST override it
 * ============================================================
 */

#include <string>
using namespace std;

class User {
private:
    // Private fields — only accessible through getters/setters (Encapsulation)
    string id;
    string name;
    string email;

public:
    // Constructor — initializes a User with basic info
    User(const string& id, const string& name, const string& email);

    // Virtual destructor — important in C++ when using inheritance
    // Without this, derived class destructors may not be called properly
    virtual ~User() {}

    // --- Getters (read-only access to private fields) ---
    string getId()    const { return id; }
    string getName()  const { return name; }
    string getEmail() const { return email; }

    // --- Setters (controlled modification of private fields) ---
    void setName(const string& newName)   { name = newName; }
    void setEmail(const string& newEmail) { email = newEmail; }

    /*
     * PURE VIRTUAL FUNCTION — This makes User an ABSTRACT CLASS.
     * Any class that inherits User MUST implement displayInfo().
     * The "= 0" syntax means "no default implementation provided here."
     */
    virtual void displayInfo() const = 0;

    /*
     * Virtual function with a default implementation.
     * Subclasses CAN override this, but don't have to.
     */
    virtual string getRole() const { return "User"; }
};

#endif // USER_H
