#include "Logger.h"
#include "json.h"
#include <string>
#include "other.h"
#include "date.h"
using namespace std;

void Logger::writeStringToLog(string user, string database, string oprtype, string message)
{
    Json::Value root;
    root["user"] = user;
    root["time"] = date::format("%F %T", std::chrono::system_clock::now());
    root["system"] = "windows";
    Json::Value log;
    log["database"] = database;
    log["opr type"] = oprtype;
    log["message"] = message;
    root["log"] = log;
    writeJsonFileOfAppend(logPath, root);
}

Logger::~Logger() {
    //cout << "destructor called!" << std::endl;
}

Logger::Logger() {
    //cout << "constructor called!" << std::endl;
}

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}