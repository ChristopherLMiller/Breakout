#ifndef __CONFIG_H
#define __CONFIG_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Logger.h"

class Config
{
public:
	Config();        // default constructor
	Config(std::string filename);        // constructor supplying config file name

	// get config key values
	int getInt(std::string key);
	std::string getString(std::string key);
	bool getBool(std::string key);
	// TODO: add types as needed

	// set config key values
	bool setInt(std::string key, int value);
	bool setString(std::string key, std::string value);
	bool setBool(std::string key, bool value);
	// TODO: add types as needed

	bool fileExists();
	bool createFile();
	std::string getFileName();
	bool keyExists(std::string key);
	void toLowerCase(std::string &str);

private:
	std::string m_fileName;        // filename
};

#endif