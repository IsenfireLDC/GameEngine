/*
 * log.hpp
 */

#include <fstream>
#include <string>
#include <chrono>

class Log {
public:
	enum LogType{Min, Debug, Info, Warning, Error, Fatal};
	struct Entry {
		std::chrono::system_clock::time_point timestamp;
		LogType severity;
		std::string message;
		std::string sender;
	};

	Log(std::string, std::string);
	virtual ~Log();

	void setParent(Log*);

	void log(std::string);
	void log(std::string, LogType);
	void log(std::string, LogType, std::string);

private:
	void writeEntry(Entry);

	std::string name;
	std::ofstream logfile;

	Log *parent;
};

namespace Engine {
	extern Log log;
};
