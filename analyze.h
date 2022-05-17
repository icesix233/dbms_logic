#ifndef ANALYZE_H
#define ANALYZE_H
#include <vector>
#include <string>
using namespace std;

extern string DataBaseName;
bool analyzeTo(vector<string> inputList);//分析调用

//设置数据库名(选择在哪个数据库中)  eg. 使用db1数据库-> use db1;
bool useDB(string DBname);
//创建表
bool createTo(vector<string> inputList, int ilen);
bool alterTo(vector<string> inputList, int ilen);
bool dropTo(vector<string> inputList, int ilen);
bool insert(vector<string> inputList, int ilen);
bool deleteTo(vector<string> inputList, int ilen);
bool updateTo(vector<string> inputList, int ilen);
bool selectTo(vector<string> inputList, int ilen);
#endif // ANALYZE_H
