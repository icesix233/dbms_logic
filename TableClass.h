#pragma once
#include <string>
#include <vector>
using namespace std;

class TableClass
{

public:
	string name; // �������
	string nameOfDatabase;  // �������ݿ�����֣������ļ�·����
	int colNum, rowNum = 0;   // colNum ����  rowNum ����
	int priIndex = 0; // ����������ţ�Ĭ������Ϊ��һ��
	vector<string> colName;   // ÿһ�е����֣�ID�������ȣ�
	vector<string> colType;	  // ÿһ�е���������
	vector< vector<string> > cols;  // ���������������

	// Ĭ�Ϲ��캯����һ�㲻��
	TableClass();
	// ���캯������������������Ϊ �������������֣�������������
	TableClass(string _name, string _nameOfDatabase, int _colNum, vector<string> _colName, vector<string> _colType);

	// ���ļ��ж�ȡ�����Ϣ
	void readData();
	// ���ļ��б�������Ϣ
	void saveData();

	// ����һ��
	void insertRow(vector<string> _row);
	// �޸�ĳһ������ (����rowindex��0��ʼ)
	void changeRow(int _rowIndex, vector<string> _row);
	// �޸�ĳһ�еĵ�i������ ������index�������Ǵ�0��ʼ��
	void changeRow(int _rowIndex, int _colIndex, string newdata);
	// ��ȡĳһ������
	vector<string> getRow(int _rowIndex);
	// ��ȡ��_colIndex������Ϊ_data����һ�е��к�
	int getRowIndex(int _colIndex, string _data);
	// ��ӡ�������
	void printTable();

	// ��ȡ������Ϣ
	string getPriKey();
	// ��������������Ϊ����ţ�
	void changePriKey(int _newPriIndex);

private:
	vector<string>::iterator it;
};

