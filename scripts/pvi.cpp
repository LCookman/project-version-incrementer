#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#define NUM_ARGS 5

#ifdef _WIN32
	#include <direct.h>
	#include <process.h>
	#define cwd _getcwd
	#define pvi_exec _execv
#else
	#include <unistd.h>
	#define cwd getcwd
	#define pvi_exec exec
#endif

/*
* This script will search the entire .git directory for the given
* file or all files that match the given file name or wild card string.
* If a file or many files are found fitting the correct file name given, 
* then the script will loop through the files looking for the keyword to
* increment.
*
* 
* Invoking the script.
* ./pvi [filename or regex] [keyword] [map keyword] [map value increment] [flags]
*
* NOTE: Each argument can have multiple values if they are comma seprated
*		without spaces.
*
*		Example: build.gradle,settings.gradle,README.txt
*		Example: major,minor 1,2
*
* Command Example: ./pvi build.gradle version minor 1
* The example command will start the pvi script to search for all of the
* build.gradle files. Once the files are found then each file is searched
* for the given keyword to modify, in this case it's version. The string
* after the keyword specifies which version type to modify being 'minor' in		[I can make this a custom config option. The user can modify these values to map to various names to values]
* this instance. The mapping of values can be specified in the config file.
* Example Version Mapping: [release.major.minor] -> [1.2.12]
* Finally the last value in the command is the value in which to increment
* the given map keyword value by.
* 
* Error Handling [Exceptions]
* If any errors are encountered within the script execution the script will
* cease execution and prompt the user if they would like to continue the
* current git action or stop the current action to fix the error.
*
* Flags: There are currenltly no flags -- This will change in the future.
*/
int main (int argc, char* argv[])
{
	std::fstream modFile;

	// This is the regex string of the file or files to search for.
	std::string regExString;

	// This is the name of the file to search for.
	std::string fileToSearchFor;

	if (argc != NUM_ARGS)
	{
		return EXIT_FAILURE;
	}

	std::cout << "Printing Cmd Line Args" << std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout << "arg" << i << ":" << argv[i] << std::endl;
	}

	std::cout << getCurrentWD << std::endl;

	return EXIT_SUCCESS;
}