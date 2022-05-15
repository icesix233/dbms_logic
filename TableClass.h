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
	// ɾ��ĳһ��
	void deleteRow(int _rowIndex);
	// ɾ��ĳһ�еĵ�i�����ݣ���ʵ�ǰ����λ�õ��ַ�����Ϊnull��
	void deleteRow(int _rowIndex, int _colIndex);
	// ��ӡ�������
	void printTable();

	// ��ȡ������Ϣ
	string getPriKey();
	// ��������������Ϊ����ţ�
	void changePriKey(int _newPriIndex);

	// ��ȡ��Ϊ_name���ֶε�index���
	int getIndexFromFieldName(string _name);
	// �޸��ֶΣ�fieldIndex�Ǵ�0��ʼ�ģ�
	void changeField(int fieldIndex, string newField);
	// �����ֶΣ��������У�_fieldΪ�ֶ�����_colTypeΪ�������͡�����λ�ã�_index��֮��
	// �����ֶκ��µ��ֶ������ݾ�Ϊ"null"�ַ���
	void addField(int _index, string _field, string _colType);
	// ɾ���ֶΣ�ɾ��_index�е��ֶΣ���������Ҳȫ��ɾ��
	void deleteField(int fieldIndex);

	// ���ĳһ�ֶε���������
	vector<string> getAllFromField(int fieldIndex);

	/* Ӧ��where�ؼ��ֵķ��� */
	
	// ��ȡfieldIndex�ֶ��£����� DATA opreator numberΪtrue�����м�¼��getField�ֶε�ֵ
	// ������ȡ�����������20��ѧ�����֣�����Ϊ 1(age), >, 20, 0(name)������ֵΪ {Ben,Alice}
	// operatorΪ >, <, =, >=, <=, != ���е�һ��
	vector<string> getFieldOpr(int fieldIndex, string opreator, int number, int IndexOfGetField);

private:
	vector<string>::iterator it;
	// �����ݿ⴦���ñ��棬���ֶ��޸ĺ��ڲ���������
	// ��Ϊ�����޷������ֶΡ���Ҫ�������ô˷���
	void saveDataOfDatabase();
};

