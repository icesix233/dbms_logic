#include <iostream>
#include <vector>
#include "Table.h"
#include "Database.h"
using namespace std;

Table table;

void createTableByInput();

int main()
{
	// 创建数据库并使用其中一个表
	Database database;
	database.createTable("Student");
	table = database.getTable("Student");

	// 通过输入创建一个表并输入测试数据
	createTableByInput();

	cout << " 修改第1行内容为 999,John,8.8 " << endl;
	vector<string> newrow = { "999","John","8.8" };
	table.changeRow(1, newrow);
	table.printTable();

	cout << " 获取第1行第0列的数据 " << endl;
	cout << table.getRow(1)[0] << endl;;

	cout << " 查找ID为999的数据的NAME项 " << endl;
	int _index = table.getRowIndex(0, "999");
	cout << table.getRow(_index)[1] << endl;
}

void createTableByInput() {
	// 输入存储数据
	int colNum;
	vector<string> colName, colType;

	// 测试创建表
	cout << "输入插入表的列数： ";
	cin >> colNum;
	for (int i = 0; i < colNum; i++) {
		cout << "输入第 " << i + 1 << " 列的列名: ";
		string name;
		cin >> name;
		colName.push_back(name);

		cout << "输入第 " << i + 1 << " 列的数据类型: ";
		string _type;
		cin >> _type;
		colType.push_back(_type);
	}
	cout << endl;

	table.createTable(colNum, colName, colType);

	table.printTable();

	// 测试插入表内容
	int insertRowCount;
	cout << "输入插入几行： ";
	cin >> insertRowCount;
	for (int i = 0; i < insertRowCount; i++) {
		cout << "输入插入的第" << i + 1 << "行的数据：" << endl;
		vector<string> thisRow;
		string s;
		for (int j = 0; j < colNum; j++) {
			cin >> s;
			thisRow.push_back(s);
		}
		table.insertRow(thisRow);
	}
	table.printTable();
}