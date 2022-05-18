#include "other.h"
#include <algorithm>
#include <regex>
#include <stack>
#include <iostream>
string processInput(string input)
{
    //ɾ���ַ���ǰ��Ŀո�
    input.erase(0, input.find_first_not_of(" "));
    input.erase(input.find_last_not_of(" ") + 1);
    //�ַ���תΪСд
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    //������ո�ת��Ϊһ��
    regex reg1(R"(( )+)");
    input = regex_replace(input, reg1, "$1");
    //ȥ�� ( ) , ; ǰ��ո�
    string::iterator it = input.begin();
    int i = 0;
    while (it != input.end()) {
        if (*it == '(' and *(it - 1) == ' ')
        {
            input.erase(i - 1, 1);
        }
        else if (*it == '(' and *(it + 1) == ' ')
        {
            input.erase(i + 1, 1);
        }
        else if (*it == ')' and *(it - 1) == ' ')
        {
            input.erase(i - 1, 1);
        }
        else if (*it == ')' and *(it + 1) == ' ')
        {
            input.erase(i + 1, 1);
        }
        else if (*it == ',' and *(it - 1) == ' ')
        {
            input.erase(i - 1, 1);
        }
        else if (*it == ',' and *(it + 1) == ' ')
        {
            input.erase(i + 1, 1);
        }
        else if (*it == ';' and *(it - 1) == ' ')
        {
            input.erase(i - 1, 1);
        }
        it++;
        i++;
    }
    //�ж������Ƿ�ƥ��
    if (bracetMatch(input))
    {
        return input;

    }
    else {
        return "error";
    }
}

bool bracetMatch(string input)
{
    stack<string> s;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(') s.push("(");
        else if (input[i] == ')')
        {
            if (s.empty()) return false;
            else s.pop();
        }
    }
    return s.empty();
}

vector<string> interception(string input)
{
    vector<string> inputList;
    string str;
    int startIndex = 0;
    for (int i = 0; i < input.size(); i++)
    {
        //�����ո��ȡ�Ӵ�
        if (input[i] == SPACE)
        {
            str = input.substr(startIndex, i - startIndex);
            inputList.push_back(str);
            i++;
            startIndex = i;
        }
        else if (input[i] == LEFT_BRACKET || input[i] == RIGHT_BRACKET || input[i] == COMMA) {
            //�����������źͶ��ţ���ȡ�Ӵ���ѷ��ŷ�������
            if (startIndex != i)
            {
                str = input.substr(startIndex, i - startIndex);
                inputList.push_back(str);
            }
            str = input.substr(i, 1);
            inputList.push_back(str);
            i++;
            startIndex = i;
        }
        else if (input[i] == SEMICOLON) {
            //�����ֺţ�����
            str = input.substr(startIndex, i - startIndex);
            inputList.push_back(str);
            break;
        }
    }
    return inputList;
    //analyzeInput(inputList);
}

bool containsin(int start, int end, string str, vector<string> inputList)
{
    if (start < inputList.size() && end < inputList.size())
    {
        for (int i = start; i <= end; ++i)
        {
            if (str == inputList[i])
            {
                return true;
            }
        }
    }
    return false;
}

int getIndex(int start, int end, string str, vector<string> inputList)
{
    for (int i = start; i <= end; ++i)
    {
        if (str == inputList[i]) return i;
    }
    return -1;
}

Json::Value readJsonFile(const string  filename)
{
    //1.���ļ�
    ifstream ifile;
    ifile.open(filename);

    //2.����json����������
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8֧�֣�������䣬utf8�������ַ�����\uxxx

    //3.����json���󣬵Ȼ�Ҫ�����������
    Json::Value root;

    //4.���ļ�ת��Ϊjson����Ҫ�õ��������������,����д��root
    string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
    if (!ok) {
        cerr << "json��������";
    }
    //5.���ش������ݵ�json�����json�����Ѿ�������
    return root;
}


Json::Value readJsonFromString(const string mystr)
{
    //1.������������
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8֧��,�������,utf8�������ַ�����\uxxx
    //2.ͨ���������󴴽� json�Ķ�������
    unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
    //3.����json����
    Json::Value root;
    //4.���ַ���ת��Ϊjson����,����д��root
    string strerr;
    bool isok = charread->parse(mystr.c_str(), mystr.c_str() + mystr.size(), &root, &strerr);
    if (!isok || strerr.size() != 0) {
        cerr << "json��������";
    }
    //5.���������ݵ�json����,���json�����Ѿ�������
    return root;
}

void writeFileFromString(const string filename, const string body)
{
    ofstream ofile(filename);
    ofile << body;
    ofile.close();
}

void writeFileFromStringOfAppend(const string filename, const string body)
{
    ofstream ofile(filename, ios::app);
    ofile << body;
    ofile << ",\n";
    ofile.close();
}

void writeJsonFile(const string filename, const Json::Value root) {
    //1.дjson�Ĺ�������
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8֧��,�����,utf8�������ַ�����\uxxx
    //2.��json����ת��Ϊ�ַ���
    string document = Json::writeString(writebuild, root);
    //3.����ǰ���д�ļ�����,д���ļ�
    writeFileFromString(filename, document);
}


void writeJsonFileOfAppend(const string filename, const Json::Value root) {
    //1.дjson�Ĺ�������
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8֧��,�����,utf8�������ַ�����\uxxx
    //2.��json����ת��Ϊ�ַ���
    string document = Json::writeString(writebuild, root);
    //3.����ǰ���д�ļ�����,д���ļ�
    writeFileFromStringOfAppend(filename, document);
}