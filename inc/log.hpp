/*
 * log.hpp
 */

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <fstream>
#include <string>
#include <chrono>

enum LogLevel{None=0, Debug=1, Info=2, Warning=3, Error=4, Fatal=5};

class Log {
public:
	struct Entry {
		std::chrono::system_clock::time_point timestamp;
		LogLevel severity;
		std::string message;
		std::string sender;

		friend std::ostream& operator<<(std::ostream&, const Entry&);
	};

	static Entry makeEntry(std::string, LogLevel, std::string);
	static Entry makeEntry(Entry, std::string);

	Log(std::string, std::string, LogLevel=LogLevel::Info);
	Log(std::string, std::string, Log*, LogLevel=LogLevel::Info);
	virtual ~Log();

	void setParent(Log*);

	void setMinLevel(LogLevel);
	LogLevel getMinLevel() const;

	void log(std::string);
	void log(std::string, LogLevel);
	void log(std::string, LogLevel, std::string);

	friend void operator<<(Log&, const std::string&);
	friend void operator<<(Log&, const Entry&);

private:
	void writeEntry(Entry);

	std::string name;
	std::ofstream logfile;

	LogLevel level;

	Log *parent;

	LogLevel minimumLevel;
};

#endif
