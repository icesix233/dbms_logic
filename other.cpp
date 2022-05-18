#include "other.h"
#include <algorithm>
#include <regex>
#include <stack>
#include <iostream>
string processInput(string input)
{
    //删除字符串前后的空格
    input.erase(0, input.find_first_not_of(" "));
    input.erase(input.find_last_not_of(" ") + 1);
    //字符串转为小写
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    //将多个空格转化为一个
    regex reg1(R"(( )+)");
    input = regex_replace(input, reg1, "$1");
    //去掉 ( ) , ; 前后空格
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
    //判断括号是否匹配
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
        //遇到空格截取子串
        if (input[i] == SPACE)
        {
            str = input.substr(startIndex, i - startIndex);
            inputList.push_back(str);
            i++;
            startIndex = i;
        }
        else if (input[i] == LEFT_BRACKET || input[i] == RIGHT_BRACKET || input[i] == COMMA) {
            //遇到左右括号和逗号，截取子串后把符号放入括号
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
            //遇到分号，结束
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
    //1.打开文件
    ifstream ifile;
    ifile.open(filename);

    //2.创建json读工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持，不加这句，utf8的中文字符会编程\uxxx

    //3.创建json对象，等会要返回这个对象
    Json::Value root;

    //4.把文件转变为json对象，要用到上面的三个变量,数据写入root
    string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
    if (!ok) {
        cerr << "json解析错误";
    }
    //5.返回存有数据的json，这个json对象已经能用了
    return root;
}


Json::Value readJsonFromString(const string mystr)
{
    //1.创建工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持,不加这句,utf8的中文字符会编程\uxxx
    //2.通过工厂对象创建 json阅读器对象
    unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
    //3.创建json对象
    Json::Value root;
    //4.把字符串转变为json对象,数据写入root
    string strerr;
    bool isok = charread->parse(mystr.c_str(), mystr.c_str() + mystr.size(), &root, &strerr);
    if (!isok || strerr.size() != 0) {
        cerr << "json解析出错";
    }
    //5.返回有数据的json对象,这个json对象已经能用了
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
    //1.写json的工厂对象
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8支持,加这句,utf8的中文字符会编程\uxxx
    //2.把json对象转变为字符串
    string document = Json::writeString(writebuild, root);
    //3.调用前面的写文件函数,写入文件
    writeFileFromString(filename, document);
}


void writeJsonFileOfAppend(const string filename, const Json::Value root) {
    //1.写json的工厂对象
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8支持,加这句,utf8的中文字符会编程\uxxx
    //2.把json对象转变为字符串
    string document = Json::writeString(writebuild, root);
    //3.调用前面的写文件函数,写入文件
    writeFileFromStringOfAppend(filename, document);
}