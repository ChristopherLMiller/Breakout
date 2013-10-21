#include "Logger.h"

// Function: Logger()
// Purpose: default constructor
// Inputs: none
// Outputs: none
Logger::Logger()
{
        m_fileName = "error.txt";
}

// Function: Logger(std::string)
// Purpose: constructor with filename specified
// InputS: std::string filename - filename to use with this logger
// Outputs: none
Logger::Logger(std::string filename)
{
        m_fileName = filename;
}

// Function: currentDateTime
// Purpose: get the current system time and return in string format
// Inputs: none
// Outputs: std::string time - human readable time
#pragma warning(disable: 4996)
const std::string Logger::currentDateTime()
{
        time_t rawtime;
        struct tm * timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        std::string t = asctime(timeinfo);
        t.pop_back();
        return t;
}