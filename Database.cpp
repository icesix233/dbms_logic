#include "Database.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include "TableClass.h"
using namespace std;

Database::Database() {
	name = "no name";
}

Database::Database(string _name) {
	name = _name;
}

void Database::readTables() {
	ifstream table_info_input;
	string path = "./data/" + name + "/table_info.txt";
	table_info_input.open(path);
	string str;
	while (table_info_input >> str) {
		string table_name = str;
		int _colNum;
		vector<string> _colName, _colType;
		table_info_input >> _colNum;
		for (int i = 0; i < _colNum; i++) {
			table_info_input >> str;
			_colName.push_back(str);
		}
		for (int i = 0; i < _colNum; i++) {
			table_info_input >> str;
			_colType.push_back(str);
		}
		TableClass newTable(table_name, name, _colNum, _colName, _colType);
		Tables.push_back(newTable);
		nameOfTables.push_back(table_name);
		numOfTable++;
	}
	table_info_input.close();
}

void Database::saveTables() {
	ofstream table_info_output;
	string path = "./data/" + name + "/table_info.txt";
	table_info_output.open(path);

	for (int i = 0; i < numOfTable; i++) {
		table_info_output << nameOfTables[i] << endl;
		table_info_output << Tables[i].colNum << endl;
		for (auto iter = Tables[i].colName.begin(); iter != Tables[i].colName.end(); iter++)
			table_info_output << *iter << " ";
		table_info_output << endl;
		for (auto iter = Tables[i].colType.begin(); iter != Tables[i].colType.end(); iter++)
			table_info_output << *iter << " ";
		table_info_output << endl;
	}

	table_info_output.close();
}

void Database::createTable(string TableClassName, int _colNum, vector<string> _colName, vector<string> _colType) {
	TableClass newTable(TableClassName, name, _colNum, _colName, _colType);
	Tables.push_back(newTable);
	nameOfTables.push_back(TableClassName);
	numOfTable++;

	// 新建文件夹
	string folderPath = ".\\data\\" + name + "\\" + TableClassName;

	string command;
	command = "mkdir " + folderPath;
	system(command.c_str());
}

TableClass Database::getTable(int _TableClassIndex) {
	return Tables[_TableClassIndex];
}

TableClass Database::getTable(string _name)
{
	for (int i = 0; i < numOfTable; i++) {
		if (nameOfTables[i] == _name)
			return Tables[i];
	}
	return Tables[0];
}

string Database::getNameOfTable(int _TableClassIndex) {
	return nameOfTables[_TableClassIndex];
}

void Database::deleteTable(string _name)
{
	int i;
	for (i = 0; i < numOfTable; i++) {
		if (nameOfTables[i] == _name)
			break;
	}
	deleteTable(i);
}

void Database::deleteTable(int _TableIndex)
{
	string nameDel = nameOfTables[_TableIndex];

	vector<TableClass> newTables;
	newTables.assign(Tables.begin(), Tables.begin()+_TableIndex);
	for (int i = _TableIndex + 1; i < numOfTable; i++) {
		newTables.push_back(Tables[i]);
	}
	Tables = newTables;
	numOfTable--;

	// 删除文件夹
	string folderPath = ".\\data\\" + name + "\\" + nameDel;

	string command;
	command = "rmdir " + folderPath;
	system(command.c_str());
}
