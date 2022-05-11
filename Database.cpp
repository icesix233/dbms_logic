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

void Database::createTableClass(string TableClassName, int _colNum, vector<string> _colName, vector<string> _colType) {
	TableClass newTableClass(_colNum, _colName, _colType);
	TableClasss.push_back(newTableClass);
	nameOfTableClasss.push_back(TableClassName);
	numOfTableClass++;
}

TableClass Database::getTableClass(int _TableClassIndex) {
	return TableClasss[_TableClassIndex];
}

TableClass Database::getTableClass(string _name)
{
	for (int i = 0; i < numOfTableClass; i++) {
		if (nameOfTableClasss[i] == _name)
			return TableClasss[i];
	}
	return TableClasss[0];
}

string Database::getNameOfTableClass(int _TableClassIndex) {
	return nameOfTableClasss[_TableClassIndex];
}

void Database::deleteTableClass(string _name)
{
	int i;
	for (i = 0; i < numOfTableClass; i++) {
		if (nameOfTableClasss[i] == _name)
			break;
	}
	deleteTableClass(i);
}

void Database::deleteTableClass(int _TableClassIndex)
{
	vector<TableClass> newTableClasss;
	newTableClasss.assign(TableClasss.begin(), TableClasss.begin()+_TableClassIndex);
	for (int i = _TableClassIndex + 1; i < numOfTableClass; i++) {
		newTableClasss.push_back(TableClasss[i]);
	}
	TableClasss = newTableClasss;
	numOfTableClass--;
}

int Database::getNumOfTableClass()
{
	return numOfTableClass;
}
