#include "TableClass.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

TableClass::TableClass() {
	colNum = 0;
}

TableClass::TableClass(int _colNum, vector<string> _colName, vector<string> _colType) {
	colNum = _colNum;
	colName.assign(_colName.begin(), _colName.end());
	colType.assign(_colType.begin(), _colType.end());
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

void TableClass::printTableClass() {
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