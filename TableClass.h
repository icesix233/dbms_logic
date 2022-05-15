#pragma once
#include <string>
#include <vector>
using namespace std;

class TableClass
{

public:
	string name; // 表的名字
	string nameOfDatabase;  // 所处数据库的名字（用于文件路径）
	int colNum, rowNum = 0;   // colNum 列数  rowNum 行数
	int priIndex = 0; // 主键的列序号，默认主键为第一列
	vector<string> colName;   // 每一列的名字（ID，姓名等）
	vector<string> colType;	  // 每一列的数据类型
	vector< vector<string> > cols;  // 表的所有内容数据

	// 默认构造函数，一般不用
	TableClass();
	// 构造函数，创建表，参数依次为 列数，各列名字，各列数据类型
	TableClass(string _name, string _nameOfDatabase, int _colNum, vector<string> _colName, vector<string> _colType);

	// 从文件中读取表的信息
	void readData();
	// 向文件中保存表的信息
	void saveData();

	// 插入一行
	void insertRow(vector<string> _row);
	// 修改某一行内容 (参数rowindex从0开始)
	void changeRow(int _rowIndex, vector<string> _row);
	// 修改某一行的第i个数据 （两个index参数均是从0开始）
	void changeRow(int _rowIndex, int _colIndex, string newdata);
	// 读取某一行内容
	vector<string> getRow(int _rowIndex);
	// 获取第_colIndex列内容为_data的那一行的行号
	int getRowIndex(int _colIndex, string _data);
	// 删除某一行
	void deleteRow(int _rowIndex);
	// 删除某一行的第i个数据（其实是把这个位置的字符串改为null）
	void deleteRow(int _rowIndex, int _colIndex);
	// 打印表的内容
	void printTable();

	// 获取主键信息
	string getPriKey();
	// 更改主键（参数为列序号）
	void changePriKey(int _newPriIndex);

	// 获取名为_name的字段的index序号
	int getIndexFromFieldName(string _name);
	// 修改字段（fieldIndex是从0开始的）
	void changeField(int fieldIndex, string newField);
	// 增加字段，即增加列，_field为字段名，_colType为数据类型。增加位置：_index列之后
	// 增加字段后，新的字段列数据均为"null"字符串
	void addField(int _index, string _field, string _colType);
	// 删除字段，删除_index列的字段，此列数据也全部删除
	void deleteField(int fieldIndex);

	// 获得某一字段的所有数据
	vector<string> getAllFromField(int fieldIndex);

	/* 应对where关键字的方法 */
	
	// 获取fieldIndex字段下，满足 DATA opreator number为true的所有记录的getField字段的值
	// 例：获取所有年龄大于20的学生名字，参数为 1(age), >, 20, 0(name)，返回值为 {Ben,Alice}
	// operator为 >, <, =, >=, <=, != 其中的一个
	vector<string> getFieldOpr(int fieldIndex, string opreator, int number, int IndexOfGetField);

private:
	vector<string>::iterator it;
	// 从数据库处调用保存，当字段修改后内部方法调用
	// 因为表类无法保存字段。不要主动调用此方法
	void saveDataOfDatabase();
};

