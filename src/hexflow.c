/** @file hexflow.cpp
 * Hexflow is a command line utitlity that outputs javascript files used as
 * scripts by the MQTTfx tool to send command sequesnces that we call flows 
 * to the hexbot robot via MQTT messages and an MQTT broker.   
 * 
 * # Getting started
 * To get your C envionment up and running in Visual Studio Code please
 * check out the link for 
 * [MacOsx](https://code.visualstudio.com/docs/cpp/config-clang-mac)]or this 
 * link for [Windows](https://code.visualstudio.com/docs/cpp/config-mingw).
 * 
 * # Building
 * To build this code open the project in Visual Studio Code (see readme file
 * for this project regarding speccial Windows considerations runing VSC) and 
 * press the hot key combination to trigger a build. For OSX users this is 
 * SHIFT + COMMAND + B, for Windows users this is SHIFT + CONTROL + B. 
 * 
 * # Running the program
 * To run this program go into a terminal shell and type ./hexflow
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Macros.
#define DEBUG // Pre-processor identifyer. Uncomment to make a debug build.
#ifdef DEBUG // Debug print macro that does nothing if debug is commented out.
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...) do {} while (0)
#endif

// Global variables.
bool rCode; // Program return code. 
const int requireArgCnt = 3; // Num arguments required (not counting file name).
const int MAX_FNAME_LEN = 30; // Max size of a file name.
const int ecNO_ERR = 0; // Error code = OK.
const int ecTOO_FEW_ARG = 1; // Error code = too few cmd line arguments given.
const int ecNO_SCRIPT_FILE_NAME = 2; // Error code = no script file provided.
struct parameters
{
   char inputTemplateFile[MAX_FNAME_LEN]; // Template file has basic MQTTfx script logic.
   char inputScriptFile[MAX_FNAME_LEN]; // Hand written flows that control leg moevements.
   char robotName[MAX_FNAME_LEN]; // Name of the robot to target with the script.
   char outputFileName[MAX_FNAME_LEN]; // Script file to create that will be run by MQTTfx. 
   char debugSetting[MAX_FNAME_LEN]; // Used to control trace verbosity.
} params; // Global structure of app control variables. 

/**
 * @brief Display the application help message.
 * @param null. 
 * @return null.
 ******************************************************************************/
void displayHelpMessage()
{
   printf("<displayHelpMessage> ------------\n");
   printf("<displayHelpMessage> hexflow help\n");
   printf("<displayHelpMessage> ------------\n");
   printf("<displayHelpMessage> Hexflow is a native c binary application that requires ");
   printf("<displayHelpMessage> you to provide three command line arguments.\n");
   printf("<displayHelpMessage> Calling format: ./hexflow <botName> <input_movement> <output_script>\n");
   printf("<displayHelpMessage> Where:\n");
   printf("<displayHelpMessage>    <botName> is the name assigned to the target hexbot.\n");
   printf("<displayHelpMessage>    <input_movement> is an input file containing the moves we want to make.\n");
   printf("<displayHelpMessage>    <output_script> is the resulting script to be run by MQTTfx.\n");
} // displayHelpMessage()

/**
 * @brief Display the command line arguments passed into the application.
 * @param argc Number of argument passed.
 * @param argv array of char arrays containing the name of the application as 
 * well as any other command line parameters.
 * @return null.
 ******************************************************************************/
int displayArgs(int argc, char** argv)
{
   const int fileNameCnt = 1;
   int argCount = argc - fileNameCnt; // Ignore first argument (file name).
   if(argCount < requireArgCnt)
   {
      printf("<displayArgs> ERROR - Too few command line arguments were provided. Expecting %d. Got %d.\n", requireArgCnt, argCount);
      for(int i = 1; i < argc; ++i)
      {
         DEBUG_PRINTF("<displayArgs> ... %d) = %s\n", i, argv[i]);
      } // for
      displayHelpMessage();
      return(ecTOO_FEW_ARG); 
   } // if
   return(0);
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
 * @brief Validate command line arguments. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all environment variables.
 * @return One of the predefined global error codes.
 ******************************************************************************/
int valCmdLne(int argc, char** argv, char **env_var_ptr) 
{
   int rtn = 0;
   const int fname = 1; // Movement file name should be first arg.
   strcpy(params.inputTemplateFile, "template.txt"); // Hard code template file name.
   rtn = displayArgs(argc, argv);
   if(rtn > 0) return(rtn);
   
   if(access(argv[fname], F_OK) != 0) // Check if script file name exists.
   {
      printf("<valCmdLne> ERROR - script file %s not found.\n", argv[fname]);
      return(ecNO_SCRIPT_FILE_NAME);
   } 
   return(ecNO_ERR);
} // main()

/**
 * @brief Main function where execution begins. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all environment variables.
 * @return appExitCode which contains the app exit code (0 = OK, non 0 = error).
 ******************************************************************************/
int main(int argc, char** argv, char **env_var_ptr) 
{
   int rtn = valCmdLne(argc, argv, env_var_ptr);
   if(rtn != ecNO_ERR) // End program is there are issues with provided args. 
   {
      return rtn;
   } // if
   return(ecNO_ERR);
} // main()

/*
   char str1[80]; // First string
   char str2[80]; // Second string
   const char dlmtr[] = " "; // Delimiter character
   char *prsPnt; // Pointer used to parse string
   int cnt = 0;
   strcpy(str1, "one two three four");
   strcat(str1, " five six seven");
   printf("Split this up: %s\n", str1);
   prsPnt = strtok(str1, dlmtr);
   while(prsPnt != NULL)
   {
      cnt++;
      printf("%d) %s\n", cnt, prsPnt);
      prsPnt = strtok(NULL, dlmtr);
   } // while
*/
