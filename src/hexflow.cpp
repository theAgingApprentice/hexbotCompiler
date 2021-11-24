/** @file hexflow.cpp
 * A command line utility for making Hexbot flows.
 * Hexflow is a command line utitlity that outputs flows that can be used to 
 * issue leg movement commands to the  hexbot robot via MQTT messages.   
 * 
 * # Getting started
 * To get your C++ envionment up and running in Visual Studio Code please
 * check out the link for 
 * [MacOsx](https://code.visualstudio.com/docs/cpp/config-clang-mac)]or this 
 * link for [Windows](https://code.visualstudio.com/docs/cpp/config-mingw).
 * 
 * # Building
 * To build this code open the project in Visual Studio Code and perss
 * SHIFT + COMMAND + B. 
 * 
 * # Running the program
 * To run this program go into a terminal shell and type ./hexflow
 ******************************************************************************/
#include "hexflow.h"

using namespace std; // Scope identifiers like functions and variables etc. 

/**
 * @brief Main function where execution begins. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all ebvironment variables.
 * @return 0 unconditionally.
 ******************************************************************************/
int main(int argc, char** argv, char **env_var_ptr)
{
   printf("<main> hexflow is a program that creates flows for hexbot legs.\n");
   printf("<main> Program name is %s\n", argv[0]);
   printf("<main> Number of arguments supplied is %d\n", argc);
   printf("<main> Comand line arguments:\n");
   for(int i = 0; i < argc; ++i)
   {
      printf("<main> ... arg[%d] = %s\n", i, argv[i]);
   } // for
   printf("<main> Available environment variables:\n");
   int i = 0;
   while(*env_var_ptr != NULL) 
   {
      i++;
      printf("<main> ... %d = %s\n",i, *(env_var_ptr++));
   } // while
   return 0;
} // main()