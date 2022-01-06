/*
 * log.cpp
 */

#include "log.hpp"

#include "utils.hpp"

using std::chrono::system_clock;

//Must construct in-place because ofstream is non-copyable
Log Engine::log{"Master", "./logs/master.log"};

Log::Log(std::string name, std::string logfile) {
	this->name = name;
	Utils::create_directories(logfile.substr(0, logfile.rfind("/")));
	this->logfile.open(logfile, std::ios::out | std::ios::app);
};

Log::~Log() {
	this->logfile.close();
};

void Log::setParent(Log *parent) {
	this->parent = parent;
};

void Log::log(std::string message) {
	this->log(message, Log::LogType::Info, "");
};

void Log::log(std::string message, Log::LogType severity) {
	this->log(message, severity, "");
};

void Log::log(std::string message, Log::LogType severity, std::string sender) {
	Entry entry{system_clock::now(), severity, message, ""};

	this->writeEntry(entry);
};

void Log::writeEntry(Entry entry) {
};
