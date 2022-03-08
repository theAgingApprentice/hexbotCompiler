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
const int ecNO_TEMPLATE_FILE_NAME = 2; // Error code = template file not found.
const int ecNO_SCRIPT_FILE_NAME = 3; // Error code = script file not found.
struct parameters
{
   char inputTemplateFile[MAX_FNAME_LEN]; // Template file has basic MQTTfx script logic.
   char inputScriptFile[MAX_FNAME_LEN]; // Hand written flows that control leg moevements.
   char robotName[MAX_FNAME_LEN]; // Name of the robot to target with the script.
   char outputFileName[MAX_FNAME_LEN]; // Script file to create that will be run by MQTTfx. 
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
 * @brief Check the command line argument count.
 * @param argc Number of arguments passed.
 * @param argv array of char arrays containing the arguments provided on the 
 * command line.
 * @return null.
 ******************************************************************************/
int cntCmdArgs(int argc, char** argv)
{
   const int fileNameCnt = 1; // One of the arguments is the binary name.
   int argCount = argc - fileNameCnt; // Ignore first argument (file name).
   if(argCount < requireArgCnt) // If there is nt enough arguments provided.
   {
      printf("<cntCmdArgs> ERROR - Too few command line arguments were provided. Expecting %d. Got %d.\n", requireArgCnt, argCount);
      for(int i = 1; i < argc; ++i)
      {
         DEBUG_PRINTF("<cntCmdArgs> ... %d) = %s\n", i, argv[i]);
      } // for
      displayHelpMessage();
      return(ecTOO_FEW_ARG); 
   } // if
   return(0);
} // cntCmdArgs()

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
 * @details Can verify if there is the right number of arguments. Can verify 
 * if the hardcoded template file exists. Can verify if the script file exists.
 * When all of these conditions are met then the the program parameter struture
 * is populated. This is a set of global variables accessible withoout needing 
 * to pass them to each function.
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all environment variables.
 * @return One of the predefined global error codes.
 ******************************************************************************/
int valCmdLne(int argc, char** argv, char **env_var_ptr) 
{
   int rtn = 0;
   const int rname = 1; // Robot name should be first arg.
   const int fname = 2; // Movement file should be second arg.
   const int oname = 3; // Output file should be third arg.
   rtn = cntCmdArgs(argc, argv); // Check the count of arguments provided.
   if(rtn > 0) return(rtn); // If the count is too low exit.
   if(access(argv[fname], F_OK) != 0) // Check if script file name exists.
   {
      printf("<valCmdLne> ERROR - script file %s not found.\n", argv[fname]);
      return(ecNO_SCRIPT_FILE_NAME);
   } 
   strcpy(params.inputTemplateFile, "template.txt"); // Hard code template file name.
   if(access(params.inputTemplateFile, F_OK) != 0) // Check if templte file name exists.
   {
      printf("<valCmdLne> ERROR - template file %s not found.\n", params.inputTemplateFile);
      return(ecNO_TEMPLATE_FILE_NAME);
   } 
   strcpy(params.robotName, argv[rname]); // Get robot name.
   strcpy(params.inputScriptFile, argv[fname]); // Get script file name.
   strcpy(params.outputFileName, argv[oname]); // Get output file name.
   DEBUG_PRINTF("<valCmdLne> Hardcoded template file name = %s\n",params.inputTemplateFile);
   DEBUG_PRINTF("<valCmdLne> Command line parameter provided:\n");
   DEBUG_PRINTF("<valCmdLne> ... 1) Robot name = %s\n",params.robotName);
   DEBUG_PRINTF("<valCmdLne> ... 2) Script file name = %s\n",params.inputScriptFile);
   DEBUG_PRINTF("<valCmdLne> ... 3) Output file name = %s\n",params.outputFileName);
   return(ecNO_ERR);
} // main()

/**
 * @brief Control the logic that generates the MQTT output file.
 * @param null.
 * @return status
 ******************************************************************************/
int createMqttFile()
{
   DEBUG_PRINTF("<createMqttFile> This is where the parsing logic goes.\n");
   return(ecNO_ERR);
} // createMqttFile()

/**
 * @brief Main function where execution begins. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all environment variables.
 * @return appExitCode which contains the app exit code (0 = OK, non 0 = error).
 ******************************************************************************/
int main(int argc, char** argv, char **env_var_ptr) 
{
   int rtn; // Temp variable to hod return codes.
   rtn = valCmdLne(argc, argv, env_var_ptr); // Validate command line args.
   if(rtn != ecNO_ERR) // End program is there are issues with provided args. 
   {
      return rtn; // Exit with error code.
   } // if
   rtn = createMqttFile(); // Generate the MQTTfx file.
   return(ecNO_ERR); // Exit with no error code.
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
