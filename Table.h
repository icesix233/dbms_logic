#pragma once
#include <string>
#include <vector>
using namespace std;

class Table
{

public:
	int colNum, rowNum = 0;   // colNum 列数  rowNum 行数
	int priIndex = 0; // 主键的列序号，默认主键为第一列
	vector<string> colName;   // 每一列的名字（ID，姓名等）
	vector<string> colType;	  // 每一列的数据类型
	vector< vector<string> > cols;  // 表的所有内容数据

	// 默认构造函数，一般不用
	Table();
	// 构造函数，创建表，参数依次为 列数，各列名字，各列数据类型
	Table(int _colNum, vector<string> _colName, vector<string> _colType);
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
	// 打印表的内容
	void printTable();

	// 获取主键信息
	string getPriKey();
	// 更改主键（参数为列序号）
	void changePriKey(int _newPriIndex);

private:
	vector<string>::iterator it;
};

