/*
 * log.cpp
 */

#include "log.hpp"

#include "utils.hpp"

#include <ctime>

#include "engine.hpp"

using std::chrono::system_clock;

//Must construct in-place because ofstream is non-copyable
Log Engine::log{"Master", "./logs/master.log", nullptr};

/*
 * Creates entry with given message, severity, and sender
 * Sets timestamp to current time
 */
Log::Entry Log::makeEntry(std::string message, LogLevel severity, std::string sender) {
	return Log::Entry{system_clock::now(), severity, message, sender};
};

/*
 * Pulls severity and sender for new Entry from base
 * Replaces message and timestamp with new values
 */
Log::Entry Log::makeEntry(Log::Entry base, std::string message) {
	return Log::makeEntry(message, base.severity, base.sender);
};


Log::Log(std::string name, std::string logfile) : Log(name, logfile, &Engine::log){};

Log::Log(std::string name, std::string logfile, Log *parent) {
	this->name = name;
	Utils::create_directories(logfile.substr(0, logfile.rfind("/")));
	this->logfile.open(logfile, std::ios::out | std::ios::app);

	this->parent = parent;
};

Log::~Log() {
	this->logfile.close();
};

void Log::setParent(Log *parent) {
	this->parent = parent;
};

void Log::setMinLevel(LogLevel level) {
	this->minimumLevel = level;
};

LogLevel Log::getMinLevel() const {
	return this->minimumLevel;
};

void Log::log(std::string message) {
	this->log(message, LogLevel::Info, "Default");
};

void Log::log(std::string message, LogLevel severity) {
	this->log(message, severity, "Default");
};

void Log::log(std::string message, LogLevel severity, std::string sender) {
	if(severity < this->minimumLevel) return;

	Entry entry{system_clock::now(), severity, message, sender};

	this->writeEntry(entry);
};

void Log::writeEntry(Entry entry) {
	if(entry.severity < this->minimumLevel) return;

	this->logfile << entry << std::endl;

	if(this->parent) {
		entry.sender = this->name + ":" + entry.sender;
		this->parent->writeEntry(entry);
	};
};

std::ostream& operator<<(std::ostream &os, const Log::Entry &entry) {
	std::time_t timestamp = system_clock::to_time_t(entry.timestamp);
	std::string str{ctime(&timestamp)};
	str.pop_back();
	os << str << " -- ";

	switch(entry.severity) {
		case LogLevel::None:
			os << "None";
			break;
		case LogLevel::Debug:
			os << "Debug";
			break;
		case LogLevel::Info:
			os << "Info";
			break;
		case LogLevel::Warning:
			os << "Warning";
			break;
		case LogLevel::Error:
			os << "Error";
			break;
		case LogLevel::Fatal:
			os << "Fatal";
			break;
	};

	if(entry.sender.size() > 0)
		os << " (" << entry.sender << ")";

	os << " : " << entry.message;

	return os;
};

void operator<<(Log &log, const std::string &message) {
	log.log(message);
};

void operator<<(Log &log, const Log::Entry &entry) {
	log.writeEntry(entry);
};
