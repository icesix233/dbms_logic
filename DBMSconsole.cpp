#include <iostream>
#include <fstream>
#include <vector>
#include "TableClass.h"
#include "Database.h"
#include "Manager.h"
using namespace std;

Database database;
TableClass tableClass;

void createTableClassByInput();
void changeTableContent();
void testmanager();
void testdatabase();
void testtable();

int main()
{
	/* manger测试 */
	//testmanager();

	/* database测试 */
	//testdatabase();

	/* table测试 */
	testtable();
}

void testmanager() {
	Manager& manager = Manager::get_instance();
	manager.readDatabase();
	bool b = manager.openDatabase("db3");
	cout << "open: " << b << "  " << manager.database_on.name << endl;
	manager.createDatabase("db5");
	bool b2 = manager.openDatabase("db5");
	cout << "open: " << b2 << "  " << manager.database_on.name << endl;
	manager.deleteDatabase("db3");
	manager.saveDatabase();
}

void testdatabase() {
	Manager& manager = Manager::get_instance();
	manager.readDatabase();
	manager.openDatabase("db1");
	manager.database_on.readTables();
	cout << "当前数据库表数：" << manager.database_on.numOfTable << endl;
	cout << "Table: " << manager.database_on.getNameOfTable(0) << endl;
	manager.database_on.getTable(0).printTable();
	cout << "Table: " << manager.database_on.getNameOfTable(1) << endl;
	manager.database_on.getTable(1).printTable();

	vector<string> _colName{ "ID","GRADE" };
	vector<string> _colType{ "NUMBER","FLOAT" };
	manager.database_on.createTable("course", 2, _colName, _colType);
	cout << "Table: " << manager.database_on.getNameOfTable(2) << endl;
	manager.database_on.getTable(2).printTable();
	manager.database_on.deleteTable("teacher");

	manager.database_on.saveTables();
}

void testtable() {
	Manager& manager = Manager::get_instance();
	manager.readDatabase();
	manager.openDatabase("db1");
	manager.database_on.readTables();
	TableClass studentTable = manager.database_on.getTable("student");
	studentTable.readData(); // 读取文件内容
	studentTable.printTable();  // 打印现在的表
	//vector<string> newrow1 = { "001", "Smith", "RJ2005", "3.5" };
	//studentTable.insertRow(newrow1);  // 插入新的一行
	//vector<string> newrow2 = { "002", "Dog", "RJ2222", "3.9" };
	//studentTable.changeRow(1,newrow2); // 修改第二行（序号为1）的内容
	//studentTable.changeRow(0, 1, "NewName");  // 修改第一行，第二列（名字）的内容为NewName
	//studentTable.printTable(); // 打印表

	// 删除字段，同时删除这一列的所有数据
	//studentTable.deleteField(1);

	// 字段操作
	studentTable.changeField(1, "StudentName");  // 将第二列（Name）改为StudentName
	// 在第二列（Name）后增加一列性别。注意增加后所有这列的数据都为空字符串。
	studentTable.addField(1, "GENDER", "string");
	// 修改第二行第三列（性别)为MALE
	studentTable.changeRow(1, 2, "Male");
	// 删除第二行
	studentTable.deleteRow(0);
	studentTable.printTable();

	studentTable.saveData(); // 保存文件内容
}

void changeTableContent() {
	cout << " 修改第1行内容为 999,John,8.8 " << endl;
	vector<string> newrow = { "999","John","8.8" };
	tableClass.changeRow(1, newrow);
	tableClass.printTable();

	cout << " 获取第1行第0列的数据 " << endl;
	cout << tableClass.getRow(1)[0] << endl;

	cout << " 查找ID为999的数据的NAME项 " << endl;
	int _index = tableClass.getRowIndex(0, "999");
	cout << tableClass.getRow(_index)[1] << endl;
}

void createTableClassByInput() {
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

	database.createTable("Student", colNum, colName, colType);
	tableClass = database.getTable("Student");

	tableClass.printTable();

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
		tableClass.insertRow(thisRow);
	}
	tableClass.printTable();
}