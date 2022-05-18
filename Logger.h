#pragma once
#include "json.h"
#include <string>
using namespace std;

// Logger 单例模式，通过get_instance获取唯一的实例
class Logger
{
public:
    string logPath = "./data/log.json";

    void writeStringToLog(string user, string message);

    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static Logger& get_instance();
private:
    Logger();
};

