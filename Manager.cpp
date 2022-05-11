#include "Manager.h"
#include "Database.h"
#include <iostream>
#include <fstream>
using namespace std;

Manager::~Manager() {
    //cout << "destructor called!" << std::endl;
}
Manager& Manager::get_instance() {
    static Manager instance;
    return instance;
}

Manager::Manager() {
    /* 各文件输入输出流设置 */
    //cout << "constructor called!" << std::endl;
}


void Manager::createDatabase(string _name) {
    Database newDatabase(_name);
    databases.push_back(_name);

    // 新建文件夹
    string folderPath = ".\\data\\" + _name;

    string command;
    command = "mkdir " + folderPath;
    system(command.c_str());
}

void Manager::readDatabase()
{
    databases.clear();
    string str;
    database_info_input.open("./data/database_info.txt");
    while (database_info_input >> str) {
        databases.push_back(str);
    }
    database_info_input.close();
}

void Manager::saveDatabase() {
    database_info_output.open("./data/database_info.txt");
    for (auto iter = databases.begin(); iter != databases.end(); iter++) {
        database_info_output << *iter << endl;
    }
    database_info_output.close();
}

bool Manager::openDatabase(string _name) {
    bool found = false;
    for (auto iter = databases.begin(); iter != databases.end(); iter++) {
        if (*iter == _name) {
            found = true;
            Database database(_name);
            database_on = database;
        }
    }
    return found;
}

bool Manager::deleteDatabase(string _name) {
    if (database_on.name == _name) {
        Database database("null");
        database_on = database;
    }

    bool found = false;

    auto iterDel = databases.begin();
    for (auto iter = databases.begin(); iter != databases.end(); iter++) {
        if (*iter == _name) {
            iterDel = iter;
            found = true;
            break;
        }
    }
    if (!found) return false;

    databases.erase(iterDel);

    // 删除文件夹
    string folderPath = ".\\data\\" + _name;

    string command;
    command = "rmdir " + folderPath;
    system(command.c_str());

    return true;
}