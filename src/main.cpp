/*
 * ============================================================
 *  FILE: main.cpp
 *  PURPOSE: Entry point of the application.
 *           Creates the SystemManager and starts the program.
 *
 *  This is deliberately kept minimal — all logic lives in
 *  the appropriate classes (good OOP practice).
 * ============================================================
 */

#include <iostream>
#include "SystemManager.h"
using namespace std;

int main() {
    /*
     * Create the system manager — this loads all saved data
     * from file and sets up the admin account.
     */
    SystemManager system;

    /*
     * Start the application.
     * run() handles the main menu loop until the user exits.
     */
    system.run();

    return 0;  // 0 means program exited successfully
}
