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
 * To build this code open the project in Visual Studio Code and press
 * SHIFT + COMMAND + B. 
 * 
 * # Running the program
 * To run this program go into a terminal shell and type ./hexflow
 * 
 * # Notes
 * The include of the hexflow.h file shows up as an error by the linter and it
 * underlines the line as if it is an error. The same goes for the include 
 * iostream.h line in hexflow.h. Despite this the code compiles cleanly and 
 * runs just fine. To avoid confusion about false bugs being underlined the 
 * option to underline include files that are not found has been disabled.
 ******************************************************************************/
#include "hexflow.h"

using namespace std; // Scope identifiers like functions and variables etc. 

/**
 * @brief Display the application welcome message.
 * @details argv[] is an array of character arrays. The first charater array 
 * row argv[0] contains the command that was used to execute this application. 
 * The execute command always has the 2 character prefix "./" and this is 
 * included in the character array argv[0]. We will strip that ugly prefix from 
 * the name in order to make the welcome message cleaner.
 * @param argv array of char arrays containing the name of the application as 
 * well as any other command line parameters.
 * @return null.
 ******************************************************************************/
void displayWelcomeMessage(char** argv)
{
   std::string tmp = argv[0]; // Convert from char array to string.
   int prefixLen = 2; // Length of prefix "./" is 2 characters.
   std::string appName = tmp.substr(prefixLen,tmp.size() - prefixLen);
   printf("<displayWelcomeMessage> Welcome to %s\n", appName.c_str());
   printf("<displayWelcomeMessage> ------------------\n");
   printf("<displayWelcomeMessage> This command line utility generates movement flows for the hexbot robot.\n");
} // displayWelcomeMessage()

/**
 * @brief Display the applications main menu.
 * @param null.
 * @return null.
 ******************************************************************************/
void displayMenu()
{

} // displayMenu()

/**
 * @brief Display the command line arguments passed into the application.
 * @param argc Number of argument passed.
 * @param argv array of char arrays containing the name of the application as 
 * well as any other command line parameters.
 * @return null.
 ******************************************************************************/
void displayArgs(int argc, char** argv)
{
   int argCount = argc - 1; // Ignore first argument. That is the app name.
   if(argCount < 1)
   {
      printf("<displayArgs> No command line arguments were provided.\n");
   } // if
   else
   {
      printf("<displayArgs> Command line argument count is %d.\n", argc);
      for(int i = 1; i < argc; ++i)
      {
         printf("<displayArgs> ... %d) = %s\n", i, argv[i]);
      } // for
   } // else
} // displayArgs()

/**
 * @brief Display the shell environment variables available to this application.
 * @param env_var_ptr pointer to array of environment variables.
 * @return null.
 ******************************************************************************/
void displayEnvVars(char **env_var_ptr)
{
   printf("<displayEnvVars> Available environment variables:\n");
   int i = 0;
   while(*env_var_ptr != NULL) 
   {
      i++;
      printf("<displayEnvVars> ... %d) %s\n",i, *(env_var_ptr++));
   } // while
} // displayEnvVars()

/**
 * @brief Main function where execution begins. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all ebvironment variables.
 * @return 0 unconditionally.
 ******************************************************************************/
int main(int argc, char** argv, char **env_var_ptr)
{
   displayWelcomeMessage(argv);
   displayArgs(argc, argv);
   displayEnvVars(env_var_ptr);
   return 0;
} // main()