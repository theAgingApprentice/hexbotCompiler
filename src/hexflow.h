#ifndef HEXFLOW_H // Start of macro to prevent file being included multiple times.
#define HEXFLOW_H // Variable to prevent file being included multiple times.

#include <iostream> // C++ standard library. Stream support.
//#include <stdio.h> 
// #include <vector> // C++ standard library. Dynamic array suppport.
// #include <string> // Handy character array tools.
bool appActive = true; // Flag controlling ending of execution of the app.
const int mainMenuActive = 1; // Numerical reference to main menu.
const int systemMenuActive = 2; // Numerical reference to system menu.
int currMenu = mainMenuActive; // State machine tracking current active menu.
const int ecNO_ERR = 0; // OK app exit code.
const int ecMENU_UNKNOWN = 1; // App exit code for falling through main loop menuing system.
const int ecUNKNOWN_ERR = 99; // App exit code for unknown error. 
int appExitCode = ecUNKNOWN_ERR; // Track app exit code.

#endif // End of macro to prevent file being included mutiple times. 