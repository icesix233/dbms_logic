#ifndef ANALYZE_H
#define ANALYZE_H
#include <vector>
#include <string>
using namespace std;

extern string DataBaseName;
bool analyzeTo(vector<string> inputList);//��������

//�������ݿ���(ѡ�����ĸ����ݿ���)  eg. ʹ��db1���ݿ�-> use db1;
bool useDB(string DBname);
//������
bool createTo(vector<string> inputList, int ilen);
bool alterTo(vector<string> inputList, int ilen);
bool dropTo(vector<string> inputList, int ilen);
bool insert(vector<string> inputList, int ilen);
bool deleteTo(vector<string> inputList, int ilen);
bool updateTo(vector<string> inputList, int ilen);
bool selectTo(vector<string> inputList, int ilen);
#endif // ANALYZE_H
