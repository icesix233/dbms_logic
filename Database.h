#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "TableClass.h"
using namespace std;

class Database
{
public:
	// 获取表的总数量
	int numOfTable = 0;
	// 数据库的名字，将用于存储路径等
	string name;

	vector<TableClass> Tables;
	vector<string> nameOfTables;

	Database();
	Database(string _name);

	// 读取文件中的表
	void readTables();
	// 保存表信息的修改到文件
	void saveTables();

	// 创建名为TableName的表
	void createTable(string TableName, int _colNum, vector<string> _colName, vector<string> _colType);
	// 获取第_TableIndex个表的对象实例
	TableClass getTable(int _TableClassIndex);
	// 获取名字为_name的表的对象实例
	TableClass getTable(string _name);
	// 获取第_TableIndex个表的名字
	string getNameOfTable(int _TableClassIndex);

	// 删除名字为_name的表
	void deleteTable(string _name);

private:
	// 删除第_TableIndex个表
	void deleteTable(int _TableClassIndex);
};

