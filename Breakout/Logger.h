#ifndef __LOGGER_H
#define __LOGGER_H

#include <string>
#include <fstream>
#include <time.h>

class Logger
{
public:
	Logger();
	Logger(std::string filename);

	// warning messages
	template <typename T>
	void warning(T message);

	// error messages
	template <typename T>
	void error(T message);

	// info messages
	template <typename T>
	void info(T message);

private:
	std::string m_fileName;

	// get the current date and time
	const std::string currentDateTime();
};

template <typename T>
void Logger::warning(T message)
{
	std::ofstream log_file(m_fileName, std::ios_base::out | std::ios_base::app);
	log_file << "[Warning] " << currentDateTime() << ": " << message << std::endl;
	log_file.close();
}

template <typename T>
void Logger::error(T message)
{
	std::ofstream log_file(m_fileName, std::ios_base::out | std::ios_base::app);
	log_file << "[Error] " << currentDateTime() << ": " << message << std::endl;
	log_file.close();
}

template <typename T>
void Logger::info(T message)
{
	std::ofstream log_file(m_fileName, std::ios_base::out | std::ios_base::app);
	log_file << "[Info] " << currentDateTime() << ": " << message << std::endl;
	log_file.close();
}

#endif