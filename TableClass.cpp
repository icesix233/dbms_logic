#include "TableClass.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include "Manager.h"
#include "json.h"
#include "other.h"
#include "Logger.h"
using namespace std;

TableClass::TableClass() {
	colNum = 0;
}

TableClass::TableClass(string _name, string _nameOfDatabase, int _colNum, vector<string> _colName, vector<string> _colType) {
	name = _name;
	nameOfDatabase = _nameOfDatabase;
	colNum = _colNum;
	colName.assign(_colName.begin(), _colName.end());
	colType.assign(_colType.begin(), _colType.end());
}

/* TXT版本的文件读取 */
/*
void TableClass::readData()
{
	ifstream table_input;
	string path = "./data/" + nameOfDatabase + "/" + name + "/data.txt";
	table_input.open(path);

	int _rowNum;
	table_input >> _rowNum;
	for (int i = 0; i < _rowNum; i++) {
		string str;
		vector<string> row;
		for (int j = 0; j < colNum; j++) {
			table_input >> str;
			row.push_back(str);
		}
		cols.push_back(row);
		rowNum++;
	}

	table_input.close();
}
*/

void TableClass::readData()
{
	string path = "./data/" + nameOfDatabase + "/" + name + "/data.json";
	Json::Value root = readJsonFile(path);

	cols.clear();
	rowNum = 0;

	// 仅当文件存在时再读取数据
	ifstream infile(path);
	if (infile.good()) {
		rowNum = std::stoi(root["num"].asString());
		for (int i = 0; i < rowNum; i++) {
			string str;
			vector<string> row;
			for (int j = 0; j < colNum; j++) {
				str = root["records"][i][colName[j]].asString();
				row.push_back(str);
			}
			cols.push_back(row);
		}
	}
}

/* TXT版本的文件保存 */
/*
void TableClass::saveData() {
	ofstream table_output;
	string path = "./data/" + nameOfDatabase + "/" + name + "/data.txt";
	table_output.open(path);

	table_output << rowNum << endl;
	for (int i = 0; i < rowNum; i++) {
		for (auto iter = cols[i].begin(); iter != cols[i].end(); iter++) {
			table_output << *iter << " ";
		}
		table_output << endl;
	}

	table_output.close();
}
*/

void TableClass::saveData()
{
	string path = "./data/" + nameOfDatabase + "/" + name + "/data.json";

	Json::Value root;
	root["database"] = nameOfDatabase;
	root["table"] = name;
	root["num"] = rowNum;
	Json::Value records;
	for (int i = 0; i < rowNum; i++) {
		Json::Value thisrecord;
		for (int j = 0; j < colNum; j++) {
			thisrecord[colName[j]] = cols[i][j];
		}
		records[i] = thisrecord;
	}
	root["records"] = records;

	writeJsonFile(path, root);
}

void TableClass::insertRow(vector<string> _row) {
	cols.push_back(_row);
	rowNum++;

	// log
	Logger& logger = Logger::get_instance();
	string s_row = "";
	for (auto iter = _row.begin(); iter != _row.end(); iter++) s_row += (" " + *iter);
	string message = "InsertRow(TABLE NAME:" + name + "ROW:" + s_row + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Insert Row", message);
}

void TableClass::changeRow(int _rowIndex, vector<string> _row) {
	cols[_rowIndex].assign(_row.begin(), _row.end());

	// log
	Logger& logger = Logger::get_instance();
	string s_row = "";
	for (auto iter = _row.begin(); iter != _row.end(); iter++) s_row += (" " + *iter);
	string message = "ChangeRow or InsertData(TABLE NAME:" + name + "ROW:" + s_row + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Change Row or Insert Data", message);
}

void TableClass::changeRow(int _rowIndex, int _colIndex, string newdata) {
	vector<string> newRow;
	newRow.assign(cols[_rowIndex].begin(), cols[_rowIndex].end());
	newRow[_colIndex] = newdata;
	changeRow(_rowIndex, newRow);
}

vector<string> TableClass::getRow(int _rowIndex) {
	return cols[_rowIndex];
}

int TableClass::getRowIndex(int _colIndex, string _data) {
	for (int i = 0; i < rowNum; i++) {
		if (cols[i][_colIndex] == _data)
			return i;
	}
	return 0;
}

void TableClass::deleteRow(int _rowIndex)
{
	rowNum--;
	cols.erase(cols.begin() + _rowIndex);

	// log
	Logger& logger = Logger::get_instance();
	string message = "DeleteRow(TABLE NAME:" + name + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Delete Row", message);
}

void TableClass::deleteRow(int _rowIndex, int _colIndex)
{
	changeRow(_rowIndex, _colIndex, "null");
}

string TableClass::getPriKey() {
	return colName[priIndex];
}

void TableClass::changePriKey(int _newPriIndex) {
	priIndex = _newPriIndex;
}

int TableClass::getIndexFromFieldName(string _name)
{
	int i = 0;
	for (; i < colNum; i++)
		if (colName[i] == _name)
			return i;
	return i;
}

void TableClass::changeField(int fieldIndex, string newField)
{
	colName[fieldIndex] = newField;
	saveDataOfDatabase();

	// log
	Logger& logger = Logger::get_instance();
	string message = "ChangeField(TABLE NAME:" + name + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Change Field", message);
}

void TableClass::addField(int _index, string _field, string _colType)
{
	_index++;
	
	colName.insert(colName.begin() + _index, _field);
	colType.insert(colType.begin() + _index, _colType);

	for (int i = 0; i < rowNum; i++) {
		cols[i].insert(cols[i].begin() + _index, "null");
	}

	colNum++;

	saveDataOfDatabase();

	// log
	Logger& logger = Logger::get_instance();
	string message = "AddField(TABLE NAME:" + name + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Add Field", message);
}

void TableClass::deleteField(int fieldIndex)
{
	colName.erase(colName.begin() + fieldIndex);
	colType.erase(colType.begin() + fieldIndex);
	for (int i = 0; i < rowNum; i++) {
		cols[i].erase(cols[i].begin() + fieldIndex);
	}

	colNum--;

	saveDataOfDatabase();
	
	// log
	Logger& logger = Logger::get_instance();
	string message = "DeleteField(TABLE NAME:" + name + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Delete Field", message);
}

void TableClass::changeTypeOfField(string fieldName, string newtype)
{
	int _index = getIndexFromFieldName(fieldName);
	colType[_index] = newtype;
	saveDataOfDatabase();

	// log
	Logger& logger = Logger::get_instance();
	string message = "ChangeFieldType(TABLE NAME:" + name + ")";
	logger.writeStringToLog("sys", nameOfDatabase, "Change Field Type", message);
}

vector<string> TableClass::getAllFromField(int fieldIndex)
{
	vector<string> data;
	for (int i = 0; i < rowNum; i++) {
		data.push_back(cols[i][fieldIndex]);
	}
	return data;
}

vector<string> TableClass::getFieldOpr(int fieldIndex, string opr, int number, int IndexOfGetField)
{
	vector<string> result;

	if (opr == "=") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) == number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}
	else if (opr == "!=") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) != number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}
	else if (opr == ">") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) > number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}
	else if (opr == ">=") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) >= number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}
	else if (opr == "<") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) < number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}
	else if (opr == "<=") {
		for (int i = 0; i < rowNum; i++) {
			if (stoi(cols[i][fieldIndex]) <= number)
				result.push_back(cols[i][IndexOfGetField]);
		}
	}

	return result;
}

void TableClass::saveDataOfDatabase()
{
	Manager& manager = Manager::get_instance();

	int index = manager.database_on.getIndexOfTable(name);
	manager.database_on.Tables[index] = *this;

	manager.database_on.saveTables();
}


void TableClass::printTable() {
	vector<string>::iterator it;

	cout << endl;
	cout << " |";
	for (it = colName.begin(); it != colName.end(); it++) {
		cout << *it << " | ";
	}
	cout << endl;

	cout << " |";
	for (it = colType.begin(); it != colType.end(); it++) {
		cout << *it << " | ";
	}
	cout << endl;

	for (int i = 0; i < rowNum; i++) {
		cout << " |";
		vector<string> thisRow;
		thisRow.assign(cols[i].begin(), cols[i].end());
		for (it = thisRow.begin(); it != thisRow.end(); it++) {
			cout << *it << " | ";
		}
		cout << endl;
	}
	cout << endl;
}