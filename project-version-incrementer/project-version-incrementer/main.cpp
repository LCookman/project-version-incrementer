#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <crtdbg.h>

#include "WindowsProcessController.h"
#include "LinuxProcessController.h"
#include "PviException.h"
#include "ConfigurationHandler.h"

#define NUM_ARGS 5
#define GIT_SUBSTRING ".git/hooks"

#ifdef _WIN32
#include <direct.h>
#include <process.h>
#define cwd _getcwd
#define pvi_exec _execv
#define MAX_PATHNAME FILENAME_MAX
#define BUILDER "WINDOWS"
#else
#include <unistd.h>
#define cwd getcwd
#define pvi_exec execv
#define MAX_PATHNAME PATH_MAX
#define BUILDER "OTHER"
#endif

/*
* This script will search the entire git directory starting at root for 
* the given file or all files that match the given file name or wild 
* card string. If a file or many files are found fitting the correct file 
* name given, then the script will loop through the files looking for the 
* keyword to increment.
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
* If any errors are encountered within program execution program will
* cease execution and prompt the user if they would like to continue the
* current git action or stop the current action to fix the error.
*
* Flags: argv[6+] house the flags.
* There are currenltly no flags -- This will change in the future.
*/

/*
* TYPEDEF KeyIncMap - The specific map that outlines a string to int (key, value) pair.
*/
typedef std::unordered_map<std::string, int> KeyIncMap;

/*
* Function Prototypes
*/
KeyIncMap* MapKeywordToIncrement (std::string, std::string);
std::vector<std::string>* ParseMultipleArgs (std::string);
IProcessController* ProcessOSTypeBuilder ();

/*****************************************************************************
Function:	      main

Description:      The main function of the project version incrementer program.

Parameters:       multiArgs - The arguments to parse apart.

Return            A pointer to the new vector of strings parsed apart.
*****************************************************************************/
int main (int argc, char* argv[])
{
	// Memory Management
	_CrtDumpMemoryLeaks ();
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char *testFileName = new char[FILENAME_MAX];
	char answer;

	std::cout << "The CWD is: " << cwd (testFileName, MAX_PATHNAME);

	if (argc < NUM_ARGS)
	{
		std::cout << std::endl << "Not Enough Arguments. Would you like"
			"to continue the commit without incrementing versions? (y, n)";

		do {
		  std::cin >> answer;
		  std::cout << "Would you like to continue the commit without incrementing versions? (y, n)";
		} while (answer != 'y' && answer != 'n');


		// Figure out if returning 1 or 0 from a program can be used from the bash script.
		if (answer == 'y')
		{

		}

		std::cout << "Error Not Enough Arguments: ./pvi [filename or regex]" 
			"[keyword] [map keyword] [map value increment] [flags]";
		return EXIT_FAILURE;
	}

	IProcessController *pProcessControl = ProcessOSTypeBuilder ();
	KeyIncMap *pKeyMap = nullptr;

	std::string fileString (argv[1]);
	std::string keywordString (argv[2]);

	std::vector<std::string> *pFiles = ParseMultipleArgs (fileString);
	std::vector<std::string> *pKeywords = ParseMultipleArgs (keywordString);

	// May not need these
	const char *cmdArgs[] = { " " };

	


	// This line prints the command input at the command line.
	// std::cout << argv[0] << " " << fileName << " " << keyword << " " << mapKeywords << " " << incValues << std::endl;
	cwd (testFileName, MAX_PATHNAME);
	std::cout << testFileName << std::endl;
	//std::cout << cwd << std::endl;

	pvi_exec ("ls", cmdArgs);

	try
	{
		pKeyMap = MapKeywordToIncrement (argv[3], argv[4]);
	}
	catch (const char* message)
	{
		std::cerr << message << std::endl;
	}

	delete pKeyMap;
	return EXIT_SUCCESS;
}


/*****************************************************************************
Function:	      ParseMultipleArgs

Description:      This function will parse any multiple arguments into a 
					single vector

Parameters:       multiArgs - The arguments to parse apart.

Return            A pointer to the new vector of strings parsed apart.
*****************************************************************************/
std::vector<std::string>* ParseMultipleArgs (std::string multiArgs)
{
	char* token = nullptr;
	char* context = nullptr;
	char delimiters[] = ",";
	char* cstrArgs = new char[multiArgs.size () + 1] ();
	std::vector<std::string> *pStrArgs = new std::vector<std::string>;

	strncpy_s (cstrArgs, multiArgs.size () + 1, multiArgs.c_str (), multiArgs.size ());

	token = strtok_s (cstrArgs, delimiters, &context);
	while (token != nullptr)
	{
		pStrArgs->push_back (token);
		token = strtok_s (nullptr, delimiters, &context);
	}

	delete cstrArgs;
	return pStrArgs;
}

/*****************************************************************************
Function:	      MapKeywordToIncrement

Description:      This function will create a map of the stated keywords to
					their values in which to increment.

Parameters:       keys - The keywords to map to a value
				  values - The values in which to assign to each key

Return            pKeyMap - A pointer to the new map of (keys, values)
*****************************************************************************/
KeyIncMap* MapKeywordToIncrement (std::string keys, std::string values)
{
	KeyIncMap *pKeyMap = new KeyIncMap;
	std::vector<std::string> *pVecKeys = ParseMultipleArgs (keys);
	std::vector<std::string> *pVecValues = ParseMultipleArgs (values);

	if (pVecKeys->size () != pVecKeys->size ())
	{
		// Throw Error String [Not Ideal, but works for this script]
		throw new PviException ("Mapping: Key to Value pair mismatch! Map keywords and value "
			"increments need to have same number of keys as values.");
	}

	// Map the keys to values of all mappings.
	for (int i = 0; i < pVecKeys->size (); i++)
	{
		pKeyMap->insert (KeyIncMap::value_type (pVecKeys->at (i), stoi (pVecValues->at (i))));
	}

	// Deallocate the vectors
	delete pVecKeys;
	delete pVecValues;

	return pKeyMap;
}


/*****************************************************************************
Function:					ProcessOSTypeBuilder

Description:      This is a builder function for a Process Controller class

Parameters:       None

Return            A pointer to the new instantiated Process Controller.
*****************************************************************************/
IProcessController* ProcessOSTypeBuilder ()
{
	IProcessController *pTempControllerPtr;
	std::vector<std::string> temp;

	if ("WINDOWS" == BUILDER)
	{
		pTempControllerPtr = new WindowsProcessController (temp);
	}
	else
	{
		pTempControllerPtr = new LinuxProcessController (temp);
	}

	return pTempControllerPtr;
}