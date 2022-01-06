/*
 * log.cpp
 */

#include "log.hpp"

Log Engine::log = Log("Master", "./logs/master.log");

Log::Log(std::string name, std::string logfile) {
	this->name = name;
	this->logfile.open(logfile, std::ios::out | std::ios::app);
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
