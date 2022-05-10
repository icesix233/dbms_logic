#pragma once
#include <vector>
#include <string>
#include "Table.h"
using namespace std;

class Database
{
public:
	vector<Table> tables;
	vector<string> nameOfTables;
	// 创建名为tableName的表
	void createTable(string tableName);
	// 获取第_tableIndex个表的对象实例
	Table getTable(int _tableIndex);
	// 获取名字为_name的表的对象实例
	Table getTable(string _name);
	// 获取第_tableIndex个表的名字
	string getNameOfTable(int _tableIndex);

	// 删除名字为_name的表
	void deleteTable(string _name);
	// 删除第_tableIndex个表
	void deleteTable(int _tableIndex);

	// 获取表的总数量
	int getNumOfTable();

private:
	int numOfTable = 0;
};

