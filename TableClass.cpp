#include "TableClass.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include "Manager.h"
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

void TableClass::insertRow(vector<string> _row) {
	cols.push_back(_row);
	rowNum++;
}

void TableClass::changeRow(int _rowIndex, vector<string> _row) {
	cols[_rowIndex].assign(_row.begin(), _row.end());
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

string TableClass::getPriKey() {
	return colName[priIndex];
}

void TableClass::changePriKey(int _newPriIndex) {
	priIndex = _newPriIndex;
}

void TableClass::changeField(int fieldIndex, string newField)
{
	colName[fieldIndex] = newField;
	saveDataOfDatabase();
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
}

void TableClass::deleteField(int _index)
{
	colName.erase(colName.begin() + _index);
	colType.erase(colType.begin() + _index);
	for (int i = 0; i < rowNum; i++) {
		cols[i].erase(cols[i].begin() + _index);
	}

	colNum--;

	saveDataOfDatabase();
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