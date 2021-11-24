#include "hexflow.h"

using namespace std; // Scope identifiers like functions and variables etc. 

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