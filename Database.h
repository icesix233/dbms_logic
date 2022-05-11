#pragma once
#include <vector>
#include <string>
#include "TableClass.h"
using namespace std;

class Database
{
public:
	// ���ݿ�����֣������ڴ洢·����
	string name;

	vector<TableClass> TableClasss;
	vector<string> nameOfTableClasss;

	Database();
	Database(string _name);
	// ������ΪTableClassName�ı�
	void createTableClass(string TableClassName, int _colNum, vector<string> _colName, vector<string> _colType);
	// ��ȡ��_TableClassIndex����Ķ���ʵ��
	TableClass getTableClass(int _TableClassIndex);
	// ��ȡ����Ϊ_name�ı�Ķ���ʵ��
	TableClass getTableClass(string _name);
	// ��ȡ��_TableClassIndex���������
	string getNameOfTableClass(int _TableClassIndex);

	// ɾ������Ϊ_name�ı�
	void deleteTableClass(string _name);
	// ɾ����_TableClassIndex����
	void deleteTableClass(int _TableClassIndex);

	// ��ȡ���������
	int getNumOfTableClass();

private:
	int numOfTableClass = 0;
};

