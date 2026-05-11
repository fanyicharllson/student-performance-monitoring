/*
 * ============================================================
 *  FILE: User.cpp
 *  PURPOSE: Implementation of the User base class
 * ============================================================
 */

#include "User.h"
#include <iostream>
using namespace std;

// Constructor — uses an initializer list to set private fields
// This is the preferred C++ way (more efficient than assignment in body)
User::User(const string& id, const string& name, const string& email)
    : id(id), name(name), email(email) {
    // Body intentionally empty — all initialization done above
}
