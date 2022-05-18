#ifndef OTHER_H
#define OTHER_H
#include<string>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.h"
using namespace std;

//Json����ʹ��˵��
//Json::Value root;
//root = readJsonFile("checkjson.json");
//��һ��ʹ�÷���get
//ʹ��get������ȡjson�����name��ֵ,�ڶ���������û��nameʱ���ص�ֵ
//string name = root.get("name","null").asString();
//string phone_num = root.get("phone_number","null").asString();
//string car_num = root.get("car_number","null").asString();

const char SPACE = ' ';
const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';
const char COMMA = ',';
const char SEMICOLON = ';';
//�淶���ַ���
string processInput(string input);
//�ж������Ƿ�ƥ��
bool bracetMatch(string input);
//��ȡ�Ӵ�
vector<string> interception(string input);
//vector���±�֮���Ƿ����str�ַ���
bool containsin(int start, int end, string str, vector<string> inputList);
//�õ����±���һ��str���±�
int getIndex(int start, int end, string str, vector<string> inputList);
//������䣬���÷���
//void analyzeInput(vector<string> inputList);
//��json�ļ�
Json::Value readJsonFile(const string fileName);
//�ַ�������json����
Json::Value readJsonFromString(const string mystr);
//��json����д��json�ļ�
void writeJsonFile(const string fileName, const Json::Value root);
//��json������׷����ʽд��json�ļ�
void writeJsonFileOfAppend(const string fileName, const Json::Value root);
//д�ļ�
void writeFileFromString(const string filename, const string body);
//׷����ʽд�ļ�
void writeFileFromStringOfAppend(const string filename, const string body);
#endif // OTHER_H

//ʹ��һ���Ѿ������ݵ�json����
