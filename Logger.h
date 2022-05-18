#pragma once
#include "json.h"
#include <string>
using namespace std;

// Logger ����ģʽ��ͨ��get_instance��ȡΨһ��ʵ��
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

