/*
 * log.cpp
 */

#include "log.hpp"

#include "utils.hpp"

#include <ctime>

using std::chrono::system_clock;

//Must construct in-place because ofstream is non-copyable
Log Engine::log{"Master", "./logs/master.log"};

Log::Log(std::string name, std::string logfile) {
	static bool master = true;

	this->name = name;
	Utils::create_directories(logfile.substr(0, logfile.rfind("/")));
	this->logfile.open(logfile, std::ios::out | std::ios::app);

	this->parent = &Engine::log;
	if(master) {
		this->parent = nullptr;
		master = false;
	};
};

Log::~Log() {
	this->logfile.close();
};

void Log::setParent(Log *parent) {
	this->parent = parent;
};

void Log::log(std::string message) {
	this->log(message, Log::Entry::LogType::Info, "");
};

void Log::log(std::string message, Log::Entry::LogType severity) {
	this->log(message, severity, "");
};

void Log::log(std::string message, Log::Entry::LogType severity, std::string sender) {
	Entry entry{system_clock::now(), severity, message, sender};

	this->writeEntry(entry);
};

void Log::writeEntry(Entry entry) {
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
		case Log::Entry::LogType::None:
			os << "None";
			break;
		case Log::Entry::LogType::Debug:
			os << "Debug";
			break;
		case Log::Entry::LogType::Info:
			os << "Info";
			break;
		case Log::Entry::LogType::Warning:
			os << "Warning";
			break;
		case Log::Entry::LogType::Error:
			os << "Error";
			break;
		case Log::Entry::LogType::Fatal:
			os << "Fatal";
			break;
	};

	os << " (" << entry.sender << ") : " << entry.message;

	return os;
};
