#pragma once
#include <fstream>
#include "Database.h"
using namespace std;

// Manager ����ģʽ��ͨ��get_instance��ȡΨһ��ʵ��
class Manager
{
public:
    // �ļ���
    ofstream database_info_output;
    ifstream database_info_input;

    // ��ǰ�򿪵����ݿ�
    Database database_on;
    // ���е����ݿ��б��ַ�����
    vector<string> databases;

    // �������ݿ⣨ʵ����database����
    void createDatabase(string _name);
    // ��ȡ�ļ��е����ݿ��б�
    void readDatabase();
    // �������ݿ����
    void saveDatabase();
    // �����ݿ⣨�ļ�Ѱ�Һ�database_on�ĸ�ֵ��������true�ɹ���false�Ҳ���
    bool openDatabase(string _name);
    // ɾ�����ݿ⣨�ļ���ͬ��ɾ����
    void deleteDatabase(string _name);

    ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    static Manager& get_instance();
private:
    Manager();
};