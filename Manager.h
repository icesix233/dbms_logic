#pragma once
#include <fstream>
#include "Database.h"
using namespace std;

// Manager 单例模式，通过get_instance获取唯一的实例
class Manager
{
public:
    // 文件流
    ofstream database_info_output;
    ifstream database_info_input;

    // 当前打开的数据库
    Database database_on;
    // 已有的数据库列表（字符串）
    vector<string> databases;

    // 创建数据库（实例化database例）
    void createDatabase(string _name);
    // 读取文件中的数据库列表
    void readDatabase();
    // 保存数据库更改
    void saveDatabase();
    // 打开数据库（文件寻找和database_on的赋值），返回true成功，false找不到
    bool openDatabase(string _name);
    // 删除数据库（文件中同样删除）
    void deleteDatabase(string _name);

    ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    static Manager& get_instance();
private:
    Manager();
};