/*
 * log.hpp
 */

#include <fstream>
#include <string>
#include <chrono>

class Log {
public:
	struct Entry {
		std::chrono::system_clock::time_point timestamp;
		enum LogType{None, Debug, Info, Warning, Error, Fatal} severity;
		std::string message;
		std::string sender;

		friend std::ostream& operator<<(std::ostream&, const Entry&);
	};

	Log(std::string, std::string);
	virtual ~Log();

	void setParent(Log*);

	void log(std::string);
	void log(std::string, Entry::LogType);
	void log(std::string, Entry::LogType, std::string);

private:
	void writeEntry(Entry);

	std::string name;
	std::ofstream logfile;

	Log *parent;
};

namespace Engine {
	extern Log log;
};
