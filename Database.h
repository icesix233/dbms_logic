#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "TableClass.h"
using namespace std;

class Database
{
public:
	// ��ȡ���������
	int numOfTable = 0;
	// ���ݿ�����֣������ڴ洢·����
	string name;

	vector<TableClass> Tables;
	vector<string> nameOfTables;

	Database();
	Database(string _name);

	// ��ȡ�ļ��еı�
	void readTables();
	// �������Ϣ���޸ĵ��ļ�
	void saveTables();

	// ������ΪTableName�ı�
	void createTable(string TableName, int _colNum, vector<string> _colName, vector<string> _colType);
	// ��ȡ��_TableIndex����Ķ���ʵ��
	TableClass getTable(int _TableClassIndex);
	// ��ȡ����Ϊ_name�ı�Ķ���ʵ��
	TableClass getTable(string _name);
	// ��ȡ��_TableIndex���������
	string getNameOfTable(int _TableClassIndex);

	// ɾ������Ϊ_name�ı�
	void deleteTable(string _name);

private:
	// ɾ����_TableIndex����
	void deleteTable(int _TableClassIndex);
};

