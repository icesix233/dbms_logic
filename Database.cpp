#include "Database.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include "Table.h"
using namespace std;

void Database::createTable(string tableName) {
	Table newTable;
	tables.push_back(newTable);
	nameOfTables.push_back(tableName);
	numOfTable++;
}

Table Database::getTable(int _tableIndex) {
	return tables[_tableIndex];
}

Table Database::getTable(string _name)
{
	for (int i = 0; i < numOfTable; i++) {
		if (nameOfTables[i] == _name)
			return tables[i];
	}
	return tables[0];
}

string Database::getNameOfTable(int _tableIndex) {
	return nameOfTables[_tableIndex];
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

void Database::deleteTable(int _tableIndex)
{
	vector<Table> newTables;
	newTables.assign(tables.begin(), tables.begin()+_tableIndex);
	for (int i = _tableIndex + 1; i < numOfTable; i++) {
		newTables.push_back(tables[i]);
	}
	tables = newTables;
	numOfTable--;
}

int Database::getNumOfTable()
{
	return numOfTable;
}
