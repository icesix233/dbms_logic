#ifndef OTHER_H
#define OTHER_H
#include<string>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.h"
using namespace std;

//Json对象使用说明
//Json::Value root;
//root = readJsonFile("checkjson.json");
//第一种使用方法get
//使用get方法获取json对象的name的值,第二个参数是没有name时返回的值
//string name = root.get("name","null").asString();
//string phone_num = root.get("phone_number","null").asString();
//string car_num = root.get("car_number","null").asString();

const char SPACE = ' ';
const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';
const char COMMA = ',';
const char SEMICOLON = ';';
//规范化字符串
string processInput(string input);
//判断括号是否匹配
bool bracetMatch(string input);
//截取子串
vector<string> interception(string input);
//vector两下标之间是否包含str字符串
bool containsin(int start, int end, string str, vector<string> inputList);
//得到两下标间第一个str的下标
int getIndex(int start, int end, string str, vector<string> inputList);
//分析语句，调用方法
//void analyzeInput(vector<string> inputList);
//读json文件
Json::Value readJsonFile(const string fileName);
//字符串创建json对象
Json::Value readJsonFromString(const string mystr);
//将json对象写入json文件
void writeJsonFile(const string fileName, const Json::Value root);
//将json对象以追加形式写入json文件
void writeJsonFileOfAppend(const string fileName, const Json::Value root);
//写文件
void writeFileFromString(const string filename, const string body);
//追加形式写文件
void writeFileFromStringOfAppend(const string filename, const string body);
#endif // OTHER_H

//使用一个已经有数据的json对象
