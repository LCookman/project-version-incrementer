#include <iostream>

#include "ConfigurationHandler.h"
#include "PviException.h"

/*****************************************************************************
Constructor:			ConfigurationHandler

Description:      Default Constructor for a Configuration Handler.

Parameters:       fileName - The name of the file to assign the file stream to.

Return            None
*****************************************************************************/
ConfigurationHandler::ConfigurationHandler ()
{
	mbNewConfig = false;
	mpConfigFile = new std::fstream (CONFIG_NAME);
}

/*****************************************************************************
Destructor:		  ~ConfigurationHandler

Description:      Default Destructor for a Configuration Handler.

Parameters:       None

Return            None
*****************************************************************************/
ConfigurationHandler::~ConfigurationHandler ()
{
	delete mpConfigFile;
}

/*****************************************************************************
Method:			  InitializeConfigFile

Description:      Construct the configuration file for PVI

Parameters:       None

Return            Whether or not the config file was created successfully
*****************************************************************************/
bool ConfigurationHandler::InitailizeConfigFile ()
{
	// Include try/catch in main
	if (!CheckConfigFile ())
	{
		CreateConfigFile ();
		mbNewConfig = true;
	}
}

/*****************************************************************************
Function:		  CheckConfigFile

Description:      This function will check to see if the config file exists
						in the current working directory

Parameters:       None

Return            True  - If the config file exists.
				  False - If the config file does not exist.
*****************************************************************************/
bool ConfigurationHandler::CheckConfigFile ()
{
	return mpConfigFile->good ();
}

/*****************************************************************************
Function:					CreateConfigFile

Description:      Creates the configuration file if it doesn't already exist.

Parameters:       None

Exceptions:				PviException: Throws the exception if the config cannot 
																	be created.

Return            None
*****************************************************************************/
void ConfigurationHandler::CreateConfigFile ()
{
//	if (!mpConfigFile->good ())
//	{
//		throw new PviException ("Error! Could not create the pvi_config file. Aborting PVI Program!");
//	}

	mpConfigFile->open (CONFIG_NAME);

	// ./pvi [filename or regex] [keyword] [map keyword] [map value increment] [flags]
	*mpConfigFile << "# Command Specific Arguments" << std::endl;
	*mpConfigFile << "# These values modify how the ./pvi command is ran and what it modifies." << std::endl;
	*mpConfigFile << "filename:example.txt" << std::endl;
	*mpConfigFile << "keyword:version" << std::endl;

	// Example Version 1.4.12
	// -k stands for the key to increment
	// -i stands for the number to increment the key by.
	// Commit message example. "This is a commit message -k:minor -i:1" -- After Commit | Version 1.4.13
	// Commit message example. "This is a commit message -k:release -i:1" -- After Commit | Version 2.0.0
	// Commit message example. "This is a commit message -k:major -i:2" -- After Commit | Version 1.6.0
	// Commit message example. "This is a commit message -k:major,minor -i:1,2" -- After Commit | Version 1.5.14
	*mpConfigFile << "map keyword:minor" << std::endl;
	*mpConfigFile << "map value increment:1" << std::endl;

	*mpConfigFile << "# Program Specific Arguments" << std::endl;
	*mpConfigFile << "# These values modify how the program behaves while running." << std::endl;
	*mpConfigFile << "# Mappings should have equal keys to values, if not the program won't work." << std::endl;
	*mpConfigFile << "keys:release,major,minor" << std::endl;

	// Specifies the default increment values per each key listed above. If nothing is specified the value is incremented by 1.
	// Note that the key will only be incremented if specified in the commit message.
	*mpConfigFile << "default_values:0,0,0" << std::endl;

	// Determines if the "filename" config option should accept regular expressions.
	*mpConfigFile << "regex:false" << std::endl;

	// value_reset determines if the values that come after each key should be reset to 0.
	*mpConfigFile << "value_reset:false" << std::endl;

	mpConfigFile->close ();
}

/*****************************************************************************
Function:					ReadConfigurationFile

Description:      This function will read the contents of the config file and
parse them into an unordered_map of strings and return the
mapped config options.

Parameters:       None

Return            The unordered configuration map keys and values.
*****************************************************************************/
ConfigMap* ConfigurationHandler::ReadConfigurationFile ()
{
	ConfigMap *pConfigMapping = new ConfigMap;
	std::string nextLine;
	char *cstrLine;
	char *token;
	char *context;

	if (!mpConfigFile->good ())
	{
		throw new PviException ("Error! Cannot read the configuration file, Aborting PVI Program!");
	}

	mpConfigFile->open (CONFIG_NAME);

	while (!mpConfigFile->eof ())
	{
		*mpConfigFile >> nextLine;

		cstrLine = new char[nextLine.size () + 1] ();
		strncpy_s (cstrLine, nextLine.size () + 1, nextLine.c_str (), nextLine.size () + 1);

		token = strtok_s (cstrLine, ":", &context);
		std::cout << token << std::endl;

		// Create my own class that will have several overloaded functions to
		// unpack the values within the unordered map. So that way I can store several
		// values within the map under a custom class name and interface.

		token = strtok_s (nullptr, ":", &context);
		std::cout << token << std::endl;
	}

	return pConfigMapping;
}
