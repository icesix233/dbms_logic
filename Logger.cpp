#include "Logger.h"
#include "json.h"
#include <string>
#include "other.h"
#include "date.h"
using namespace std;

void Logger::writeStringToLog(string user, string message)
{
    Json::Value root;
    root["user"] = user;
    root["time"] = date::format("%F %T", std::chrono::system_clock::now());
    root["system"] = "windows";
    root["log"] = message;
    writeJsonFile(logPath, root);
}

Logger::~Logger() {
    //cout << "destructor called!" << std::endl;
}

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}