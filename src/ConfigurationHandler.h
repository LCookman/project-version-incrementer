#pragma once

#include <unordered_map>
#include <fstream>

#define CONFIG_NAME "pvi.ini"
#define LINE_LENGTH 255

/*
* TYPEDEF ConfigMap - The map that outlines the values in the config file.
*/
typedef std::unordered_map<std::string, std::string> ConfigMap;

/*
* CLASS ConfigurationHandler - Handles all of the configuration operations.
*/
class ConfigurationHandler
{
private:
	std::fstream *mpConfigFile;
	bool mbNewConfig;

public:
	ConfigurationHandler ();
	~ConfigurationHandler ();
	bool InitailizeConfigFile ();
	bool CheckConfigFile ();
	void CreateConfigFile ();
	ConfigMap* ReadConfigurationFile ();
};
