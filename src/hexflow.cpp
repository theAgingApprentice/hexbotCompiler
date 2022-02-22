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
 * To build this code open the project in Visual Studio Code (see readme file
 * for this project regarding speccial Windows considerations runing VSC) and 
 * press the hot key combination to trigger a build. For OSX users this is 
 * SHIFT + COMMAND + B, for Windows users this is SHIFT + CONTROL + B. 
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
 * @brief Display the application help message.
 * @param null. 
 * @return null.
 ******************************************************************************/
void displayHelpMessage()
{
   printf("<displayHelpMessage> \n------------\n");
   printf("<displayHelpMessage> hexflow help\n");
   printf("<displayHelpMessage> ------------\n");
   printf("<displayHelpMessage> Hexflow is a native c++ binary application that requires\n");
   printf("<displayHelpMessage> you to provide at least three command line arguments.\n");
   printf("<displayHelpMessage> Calling format: ./hexflow <botName> <input_template> <output_script>\n\n");
   printf("<displayHelpMessage> Where:\n");
   printf("<displayHelpMessage> <botName> is the name assigned to the target hexbot.\n");
   printf("<displayHelpMessage> <input_template> is an inut file containing the moves we want to make.\n");
   printf("<displayHelpMessage> <output_scrit> is the resulting script to be run by MQTTfx.\n");
} // displayHelpMessage()

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
 * @brief Send a test message to the MQTT broker.
 * @param null.
 * @return null.
 ******************************************************************************/
void sendMqttMessage()
{
   printf("<sendMqttMessage> This feature is not yet implemented.\n");
} // sendMqttMessage()

/**
 * @brief Append user input to file.
 * @param null.
 * @return null.
 ******************************************************************************/
void appendText()
{
   const int maxUserInputSize = 80; // Max num characters in one line of file.
   char appendInput[maxUserInputSize]; // Hold user input.
   char fileName[maxFileNameSize] = "test.txt";
   printf("<appendText> Please enter text and press ENTER: ");
   cin.clear(); // Clears the error flag on cin.
   cin.ignore(maxFileNameSize, '\n'); // Ignore all content of cin up to first '\n' character.  
   cin.getline(appendInput, maxUserInputSize);    
   printf("<appendText> Appending %s to file %s.\n", appendInput, fileName);
   ofstream a_file(fileName, ios::app); // Opens file for appending data.
   a_file << appendInput << '\n'; // Appends data to file. Add new line to end.
   a_file.close(); // Close the file stream explicitly.
   return;
} // appendText()

/**
 * @brief Display content of file to terminal.
 * @param argv Array of character strings containing each command line argument.
 * @return null.
 ******************************************************************************/
void displayFile(char** argv)
{
   char fileName[maxFileNameSize] = "test.txt";
   const int maxFileLineSize = 80; // Max num characters in one line of file.
   char lineFromFile[maxFileLineSize]; // Hold input from file.  
   int lineCount = 0; // Enumerate lines of file.
   fstream myFile; // Reference to file input.
//   printf("<displayFile> Content of file %s:\n", fileName);
   printf("<displayFile> Content of file %s:\n", argv[2]);
   myFile.open(fileName, ios::in); // Open file for reading.
   if(myFile.is_open()) //Check whether the file is open.
   {   
      while(myFile.getline(lineFromFile, maxFileLineSize))
      {
         lineCount ++;
         printf("<displayFile> %d) %s.\n", lineCount, lineFromFile);         
      } // while    
      myFile.close(); // Close the file object.
   } // if
   else // Cannot open file.
   {
      printf("<displayFile> Could not open file.\n");
   } // else
   return;
} // displayFile()

/**
 * @brief See if the named file exists. 
 * @param checkFile Pointer to character array containing the file name.
 * @return TRUE if the file exists. FALSE if it does not.
 ******************************************************************************/
bool checkFile(char *checkFile)
{
   fstream inFile; 
   inFile.open(checkFile);
   if(inFile.is_open()) 
   {
      printf("<checkFile> Filename %s found.\n", checkFile); 
      return true;     
   } // if
   else 
   {
      printf("<checkFile> Filename %s not found.\n", checkFile);  
      return false;    
   } // else      
} // checkFile()

/**
 * @brief Parse an array of characters from a line of the script file. 
 * @param lineToParse A character array Pointer to character array containing the file name.
 * @return TRUE if syntax is good. FALSE if syntax is bad.
 ******************************************************************************/
bool parseScriptLine(char *line)
{
   string lineToParse(line);
   std::string s = lineToParse;
   std::string delimiter = " ";
   size_t pos = 0;
   std::string token;
   int index = 0;
   int MaxNumElements = 10;
   string lineElements[MaxNumElements];
   while((pos = s.find(delimiter)) != std::string::npos) 
   {
      token = s.substr(0, pos);
//      std::cout << token << std::endl;
      lineElements[index] = token;
      index ++;
      s.erase(0, pos + delimiter.length());
   }
//   std::cout << s << std::endl; 
   token = s;
   lineElements[index] = token; 

   for(int x = 0; x<= index; x++)
   {
      printf("<parseScriptFile> Element %d = %s\n", x, lineElements[x].c_str());      
   } // for
   return true;
} // parseScriptLine()

/**
 * @brief Read through MQTT script file. 
 * @param scriptFile Pointer to character array containing the file name.
 * @return TRUE if no errors were encountered. FALSE if errors are.
 ******************************************************************************/
bool processScriptFile(char *scriptFile)
{
   const int maxFileLineSize = 80; // Max num characters in one line of file.
   char lineFromFile[maxFileLineSize]; // Hold input from file.  
   int lineCount = 0; // Enumerate lines of file.
   fstream myFile; // Reference to file input.
   printf("<processScriptFile> Content of file %s:\n", scriptFile);
   myFile.open(scriptFile, ios::in); // Open file for reading.
   if(myFile.is_open()) //Check whether the file is open.
   {   
      while(myFile.getline(lineFromFile, maxFileLineSize))
      {
         lineCount ++;
         printf("<processScriptFile> %d) %s.\n", lineCount, lineFromFile); 
         bool rtn = parseScriptLine(lineFromFile);        
      } // while    
      myFile.close(); // Close the file object.
   } // if
   else // Cannot open file.
   {
      printf("<processScriptFile> Could not open file.\n");
      return false;
   } // else
   return true;
} // processScriptFile()

/**
 * @brief Main function where execution begins. 
 * @param argc Count of all command line elements including the program name.
 * @param argv Array of character strings containing each command line argument.
 * @param env_var_ptr Array of characters containing all environment variables.
 * @return appExitCode which contains the app exit code (0 = OK, non 0 = error).
 ******************************************************************************/
int main(int argc, char** argv, char **env_var_ptr)
{
   char inputFileName[30];
   char robotName[30];
   char outputFileName[30];
   bool isValidInputFileName;

   if(argc < 4)
   {
      printf("<main> You have not provided enough command line parameters.\n");
      displayArgs(argc, argv);
      displayHelpMessage();
      return ecNO_FILE_NAME; 
   } // if

   strcpy(robotName, argv[1]);
   printf("<main> Robot name provided = %s\n", robotName);      
   strcpy(inputFileName, argv[2]);
   printf("<main> MQTT template file name provided = %s\n", inputFileName);      
   strcpy(outputFileName, argv[3]);
   printf("<main> MQTTfx file name provided = %s\n", outputFileName);      

   isValidInputFileName = checkFile(inputFileName);
   if(isValidInputFileName)
   {
      bool rtn = processScriptFile(inputFileName);
      if(rtn == false)
      {
         return ecNO_BAD_MQTT_SCRIPT_FILE;
      } // if
   } // if
   else
   {
      printf("<main> MQTT template file name cannot be found.\n");      
      displayHelpMessage();
      return ecNOT_VALID_FILE_NAME; 
   } // else

   printf("<main> Program ending without any errors.\n");
   return ecNO_ERR;
} // main()