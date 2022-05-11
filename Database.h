#pragma once
#include <vector>
#include <string>
#include "TableClass.h"
using namespace std;

class Database
{
public:
	// 数据库的名字，将用于存储路径等
	string name;

	vector<TableClass> TableClasss;
	vector<string> nameOfTableClasss;

	Database();
	Database(string _name);
	// 创建名为TableClassName的表
	void createTableClass(string TableClassName, int _colNum, vector<string> _colName, vector<string> _colType);
	// 获取第_TableClassIndex个表的对象实例
	TableClass getTableClass(int _TableClassIndex);
	// 获取名字为_name的表的对象实例
	TableClass getTableClass(string _name);
	// 获取第_TableClassIndex个表的名字
	string getNameOfTableClass(int _TableClassIndex);

	// 删除名字为_name的表
	void deleteTableClass(string _name);
	// 删除第_TableClassIndex个表
	void deleteTableClass(int _TableClassIndex);

	// 获取表的总数量
	int getNumOfTableClass();

private:
	int numOfTableClass = 0;
};

