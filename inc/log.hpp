/*
 * log.hpp
 */

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <fstream>
#include <string>
#include <chrono>

enum LogType{None, Debug, Info, Warning, Error, Fatal};
class Log {
public:
	struct Entry {
		std::chrono::system_clock::time_point timestamp;
		LogType severity;
		std::string message;
		std::string sender;

		friend std::ostream& operator<<(std::ostream&, const Entry&);
	};

	static Entry makeEntry(std::string, LogType, std::string);
	static Entry makeEntry(Entry, std::string);

	Log(std::string, std::string);
	Log(std::string, std::string, Log*);
	virtual ~Log();

	void setParent(Log*);

	void log(std::string);
	void log(std::string, LogType);
	void log(std::string, LogType, std::string);

	friend void operator<<(Log&, const std::string&);
	friend void operator<<(Log&, const Entry&);

private:
	void writeEntry(Entry);

	std::string name;
	std::ofstream logfile;

	Log *parent;
};

#endif
