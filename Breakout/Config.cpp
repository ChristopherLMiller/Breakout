#include "Config.h"


// Function: Config()
// Purpose: default constructor
// Inputs: none
// Outputs: none
Config::Config()
{
	m_fileName = "config.cfg";
}

// Function: Config(std::string)
// Purpose: constructor with passed input
// Inputs: std::string filename - the name of the config file
// Outputs: none
Config::Config(std::string filename)
{
	m_fileName = filename;
}

// Function: getString(std::string)
// Purpose: retrieve string value for the key specified
// Inputs: std::string key - key to lookup
// Outputs: std::string - value returned if found
std::string Config::getString(std::string key)
{
	if (!fileExists())
	{
		return "";
	}
	else
	{
		// create the file object
		std::ifstream file;
		file.open(getFileName());
		std::string line;

		// loop the file reading a line at a time to look for the value we are after
		while (!file.eof())
		{
			std::getline(file, line);

			// split out the delimiter ':' so we can get the key and value
			std::string fileKey = line.substr(0, line.find(":"));

			// if keys match return the value
			toLowerCase(key);
			toLowerCase(fileKey);
			if (key == fileKey)
			{
				file.close();
				return line.substr(line.find(":") + 1);
			}
		}

		// we reached this point, they key wasn't found so return 0
		file.close();
		return "";
	}
}

// Function: getInt(std::string)
// Purpose: retrieve value for the key specified
// Inputs: std::string key - key to lookup
// Outputs: int - value returned if found
int Config::getInt(std::string key)
{
	if (!fileExists())
	{
		return 0;
	}
	else
	{
		// we are gonna cheat and call getString, then convert taht value and return it
		std::string value = getString(key);
		return atoi(value.c_str());
	}
}


// Function: getBool(std::string)
// Purpose: get boolean value from config
// Inputs: std::string key - key to lookup
// Outputs: boolean value - value found
bool Config::getBool(std::string key)
{
	if (!fileExists())
	{
		return false;
	}
	else
	{
		std::string value = getString(key);
		if (value == "true")
			return true;
		else
			return false;
	}
}


// Function: setInt(std::string, int)
// Purpose: set config key to the value specified
// Inputs: std::string key - key to set
//		   int - value to set
// Outputs: bool success - if setting of the value was successful
bool Config::setInt(std::string key, int value)
{
	// first check if the file exists
	if (fileExists())
	{
		// now check if the key exists we are looking for
		if (keyExists(key))
		{
			// now make sure we aren't wasting time trying to update a value that hasn't changed
			if (getInt(key) == value)
				return true;

			// it does, update the file entry
			std::vector<std::string> entries;

			// open the file
			std::ifstream file;
			file.open(m_fileName, std::ios_base::in);
			std::string line;

			// loop the file
			while (!file.eof())
			{
				std::getline(file, line);

				std::string fileKey = line.substr(0, line.find(":"));
				toLowerCase(key);
				toLowerCase(fileKey);
				if (fileKey == key)
				{
					// concatenate the new value to the key and push back
					entries.push_back(key + ":" + std::to_string(value));
				}
				else
				{
					entries.push_back(line);
				}
			}
			file.close();

			// at this point all entries are in the vector and the value being updated has been dealt with as well
			std::ofstream outfile;
			outfile.open(m_fileName, std::ios_base::trunc);

			// loop again putting all records back into the file
			for (int i = 0; (unsigned)i < entries.size(); i++)
			{
				outfile << entries[i] << std::endl;
			}
			outfile.close();

			// last step, lets verify entry was written fine and updated, just in case
			int doubleCheck = getInt(key);
			if (doubleCheck == value)
				return true;
			else
				return false;
		}
		else
		{
			// key doesn't exist, lets add it to the file with the specified value
			std::ofstream file;
			file.open(m_fileName, std::ios_base::app);
			file << key << ":" << value << std::endl;
			file.close();

			// verify value was written
			if (keyExists(key))
				return true;
			else
				return false;
		}
	}
	else
	{
		// file doesn't exist at all, this make it super easy to add the key
		std::ofstream file;
		file.open(m_fileName, std::ios_base::app);
		file << key << ":" << value << std::endl;
		file.close();

		// verify value was written
		if (keyExists(key))
			return true;
		else
			return false;
	}
}

// Function: setString(std::string, int)
// Purpose: set config key to the value specified
// Inputs: std::String key - key to set
//		   std::string value - value to set to
// Outputs: bool - if setting of the value was a success
bool Config::setString(std::string key, std::string value)
{
	// first check if the file exists
	if (fileExists())
	{
		// now check if the key exists we are looking for
		if (keyExists(key))
		{
			// make sure value isn't the same thing if so lets skip this bitch
			if (getString(key) == value)
				return true;

			// it does, update the file entry
			std::vector<std::string> entries;

			// open the file
			std::ifstream file;
			file.open(m_fileName, std::ios_base::in);
			std::string line;

			// loop the file
			while (!file.eof())
			{
				std::getline(file, line);

				std::string fileKey = line.substr(0, line.find(":"));
				toLowerCase(key);
				toLowerCase(fileKey);
				if (fileKey == key)
				{
					// concatenate the new value to the key and push back
					entries.push_back(key + ":" + value);
				}
				else
				{
					entries.push_back(line);
				}
			}
			file.close();

			// at this point all entries are in the vector and the value being updated has been dealt with as well
			std::ofstream outfile;
			outfile.open(m_fileName, std::ios_base::trunc);

			// loop again putting all records back into the file
			for (int i = 0; (unsigned)i < entries.size(); i++)
			{
				outfile << entries[i] << std::endl;
			}
			outfile.close();

			// last step, lets verify entry was written fine and updated, just in case
			std::string doubleCheck = getString(key);
			if (doubleCheck == value)
				return true;
			else
				return false;
		}
		else
		{
			// key doesn't exist, lets add it to the file with the specified value
			std::ofstream file;
			file.open(m_fileName, std::ios_base::app);
			file << key << ":" << value << std::endl;
			file.close();

			// verify value was written
			if (keyExists(key))
				return true;
			else
				return false;
		}
	}
	else
	{
		// file doesn't exist at all, this make it super easy to add the key
		std::ofstream file;
		file.open(m_fileName, std::ios_base::app);
		file << key << ":" << value << std::endl;
		file.close();

		// verify value was written
		if (keyExists(key))
			return true;
		else
			return false;
	}
}

// Function: setBool(std::string, bool)
// Purpose: set boolean value in config
// Inputs: std::string key - key to set
//         bool value - value to set
// Outputs: bool success - if setting passed
bool Config::setBool(std::string key, bool value)
{
	// first check if the file exists
	if (fileExists())
	{
		// now check if the key exists we are looking for
		if (keyExists(key))
		{
			// make sure value isn't the same thing if so lets skip this bitch
			if (getBool(key) == value)
				return true;

			// it does, update the file entry
			std::vector<std::string> entries;

			// open the file
			std::ifstream file;
			file.open(m_fileName, std::ios_base::in);
			std::string line;

			// loop the file
			while (!file.eof())
			{
				std::getline(file, line);

				std::string fileKey = line.substr(0, line.find(":"));
				toLowerCase(key);
				toLowerCase(fileKey);
				if (fileKey == key)
				{
					// concatenate the new value to the key and push back
					if (value == true)
						entries.push_back(key + ":" + "true");
					else
						entries.push_back(key + ":" + "false");
				}
				else
				{
					entries.push_back(line);
				}
			}
			file.close();

			// at this point all entries are in the vector and the value being updated has been dealt with as well
			std::ofstream outfile;
			outfile.open(m_fileName, std::ios_base::trunc);

			// loop again putting all records back into the file
			for (int i = 0; (unsigned)i < entries.size(); i++)
			{
				outfile << entries[i] << std::endl;
			}
			outfile.close();

			// last step, lets verify entry was written fine and updated, just in case
			bool doubleCheck = getBool(key);
			if (doubleCheck == value)
				return true;
			else
				return false;
		}
		else
		{
			// key doesn't exist, lets add it to the file with the specified value
			std::ofstream file;
			file.open(m_fileName, std::ios_base::app);
			if (value)
				file << key << ":true" << std::endl;
			else
				file << key << ":false" << std::endl;
			file.close();

			// verify value was written
			if (keyExists(key))
				return true;
			else
				return false;
		}
	}
	else
	{
		// file doesn't exist at all, this make it super easy to add the key
		std::ofstream file;
		file.open(m_fileName, std::ios_base::app);
		file << key << ":" << value << std::endl;
		file.close();

		// verify value was written
		if (keyExists(key))
			return true;
		else
			return false;
	}
}
// Function: fileExits()
// Purpose: see if the file actually exists
// Inputs: none
// Outputs: bool exists - whether file exists or not
bool Config::fileExists()
{
	std::ifstream file;
	file.open(m_fileName);
	if (file)
		return true;
	else
		return false;
}

// Function: getFileName()
// Purpose: get the filename
// Inputs: none
// Outputs: std::string filename - name of the file
std::string Config::getFileName()
{
	return m_fileName;
}

// Function: createFile()
// Purpose: create the file
// Inputs: none
// Outputs: bool created - if creating file passes
bool Config::createFile()
{
	// make sure file doesn't exist first
	if (fileExists())
	{
		return true;
	}
	else
	{
		// create an empty file
		std::fstream file;
		file.open(m_fileName, std::ios_base::out);
		file.close();

		// verify file exists
		if (fileExists())
			return true;
		else
			return false;
	}
}

// Function: keyExists(std::string)
// Purpose: see if the specified key exists in the file
// InputS: std::string key - key to lookup
// Outputs: bool exists - if key was found
bool Config::keyExists(std::string key)
{
	if (fileExists())
	{
		std::ifstream file;
		file.open(m_fileName);

		// loop through the values
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			std::string fileKey = line.substr(0, line.find(":"));
			toLowerCase(key);
			toLowerCase(fileKey);
			if (key == fileKey)
			{
				file.close();
				return true;
			}
		}

		file.close();
		return false;
	}
	else
	{
		return false;
	}
}

// Function: toLowercase(std::string&)
// Purpose: convert referenced string to lowercase
// Input: string - string to convert
// Outputs: none
void Config::toLowerCase(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);
}
