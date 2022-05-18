#include "analyze.h"
#include "Database.h"
#include "TableClass.h"
#include "Manager.h"
#include "other.h"
#include <iostream>
string DataBaseName = "db1";

bool readsql(string input)
{
    bool flag;
    vector<string> sublist;
    string subsql;
    while (input.find_first_of(";") <= input.size())
    {
        int i = input.find_first_of(";") + 1;
        subsql = input.substr(0, i);
        subsql = processInput(subsql);
        sublist = interception(subsql);
        flag = analyzeTo(sublist);
        if (i >= input.size())
            break;
        else
            input = input.substr(i);
    }
    return true;
}

bool analyzeTo(vector<string> inputList)
{
    int flag = false;
    int ilen = inputList.size();
    if (ilen > 1)
    {
        if (inputList[0] == "use")
        {
            flag = useDB(inputList[1]);
        }
        else if (inputList[0] == "create")
        {
            flag = createTo(inputList, ilen);
        }
        else if (inputList[0] == "alter")
        {
            flag = alterTo(inputList, ilen);
        }
        else if (inputList[0] == "drop")
        {
            flag = dropTo(inputList, ilen);
        }
        else if (inputList[0] == "insert")
        {
            flag = insert(inputList, ilen);
        }
        else if (inputList[0] == "delete")
        {
            flag = deleteTo(inputList, ilen);
        }
        else if (inputList[0] == "update")
        {
            flag = updateTo(inputList, ilen);
        }
        else if (inputList[0] == "select")
        {
            flag = selectTo(inputList, ilen);
        }
    }
    return flag;
}

bool useDB(string DBname)
{
    DataBaseName = DBname;
    return true;
}

bool createTo(vector<string> inputList, int ilen)
{
    int il = 1;
    if (ilen > 2)
    {
        //创建数据库
        if (inputList[il] == "database")
        {
            il++;
            Manager& manager = Manager::get_instance();
            manager.readDatabase();
            if (manager.openDatabase(inputList[il]))//若打开成功证明已经存在，创建失败
            {
                return false;
            }
            else {
                //否则创建
                manager.createDatabase(inputList[il]);
                manager.saveDatabase();
                return true;
            }
        }
        else if (inputList[il] == "table")//创建表
        {
            il++;
            Manager& manager = Manager::get_instance();
            manager.readDatabase();
            manager.openDatabase(DataBaseName);
            manager.database_on.readTables();
            if (manager.database_on.is_in(inputList[il])) {//如果已经存在则创建失败
                return false;
            }
            else {
                //否则创建
                string tName = inputList[il];
                if (inputList[++il] == "(")
                {
                    int start = ++il;
                    int end = ilen - 1;
                    int k = 0;
                    vector<string> _colName;
                    vector<string> _colType;
                    int _colNum = 0;
                    while (il < end) {
                        if (containsin(start, end, ",", inputList))
                            k = getIndex(start, end, ",", inputList);
                        else
                            k = end;
                        if (il <= k)
                        {
                            _colName.push_back(inputList[il]);//列名
                            _colType.push_back(inputList[++il]);//数据类型
                            _colNum++;//列数
                            il++;
                            start = ++il;
                        }
                    }
                    manager.database_on.createTable(tName, _colNum, _colName, _colType);
                    manager.database_on.saveTables();
                    return true;
                }
                else return false;
            }
        }
    }
    else {
        return false;
    }
}

bool alterTo(vector<string> inputList, int ilen)
{
    int il = 1;
    if (inputList[il] == "table")
    {
        Manager& manager = Manager::get_instance();
        manager.readDatabase();
        manager.openDatabase(DataBaseName);
        manager.database_on.readTables();
        if (manager.database_on.is_in(inputList[++il]))
        {
            TableClass altable = manager.database_on.getTable(inputList[il]);
            altable.readData();
            il++;
            if (inputList[il] == "add")
            {
                altable.addField(altable.colNum, inputList[++il], inputList[++il]);
            }
            else if (inputList[il] == "drop" && inputList[il + 1] == "column")
            {
                il = il + 2;
                int dindex = altable.getIndexFromFieldName(inputList[il]);
                altable.deleteField(dindex);
            }
            else if (inputList[il] == "modify")
            {
                altable.changeTypeOfField(inputList[++il], inputList[++il]);
            }
            else if (inputList[il] == "rename" && inputList[il + 1] == "column" && inputList[il + 3] == "to")
            {
                il = il + 2;
                int rindex = altable.getIndexFromFieldName(inputList[il]);
                altable.changeField(rindex, inputList[il + 2]);
            }
            else return false;
            altable.saveData();
            return true;
        }
        else return false;
    }
    else return false;
}

bool dropTo(vector<string> inputList, int ilen)
{
    int il = 1;
    if (ilen > 2)
    {
        if (inputList[il] == "table")
        {
            Manager& manager = Manager::get_instance();
            manager.readDatabase();
            manager.openDatabase(DataBaseName);
            manager.database_on.readTables();
            if (manager.database_on.is_in(inputList[++il]))//若存在则删除
            {
                manager.database_on.deleteTable(inputList[il]);
                manager.database_on.saveTables();
                return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}

bool insert(vector<string> inputList, int ilen)
{
    int il = 1;
    if (ilen > 2)
    {
        Manager& manager = Manager::get_instance();
        manager.readDatabase();
        manager.openDatabase(DataBaseName);
        manager.database_on.readTables();
        if (inputList[il] == "into")
        {
            if (manager.database_on.is_in(inputList[++il]))
            {
                TableClass istable = manager.database_on.getTable(inputList[il]);
                istable.readData();
                if (inputList[il + 1] == "(")
                {
                    il = il + 2;
                    int k = getIndex(il, ilen - 1, ")", inputList);
                    vector<int> colindex;
                    vector<string> newvalue;
                    if ((k - il) / 2 + 1 <= istable.colNum && inputList[k + 1] == "values")
                    {

                        while (il < k)
                        {
                            int vindex = istable.getIndexFromFieldName(inputList[il]);
                            colindex.push_back(vindex);
                            il = il + 2;
                        }
                        il = k + 3;
                        while (il < ilen)
                        {
                            newvalue.push_back(inputList[il]);
                            il = il + 2;
                        }
                        if (newvalue.size() == colindex.size())
                        {
                            vector<string> newrow(istable.colNum, "null");
                            for (int i = 0; i < newvalue.size(); ++i)
                            {
                                newrow[colindex[i]] = newvalue[i];
                            }
                            istable.insertRow(newrow);
                            istable.saveData();
                            return true;
                        }
                        else return false;
                    }
                    else return false;
                }
                else if (inputList[il + 1] == "values")
                {
                    il = il + 3;
                    if (ilen >= il + 2 * istable.colNum)
                    {
                        vector<string> newrow;
                        while (il < ilen)
                        {
                            newrow.push_back(inputList[il]);
                            il = il + 2;
                        }
                        istable.insertRow(newrow);
                        istable.saveData();
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}

bool deleteTo(vector<string> inputList, int ilen)
{
    int il = 1;
    if (inputList[il] == "from")
    {
        Manager& manager = Manager::get_instance();
        manager.readDatabase();
        manager.openDatabase(DataBaseName);
        manager.database_on.readTables();
        if (manager.database_on.is_in(inputList[++il]))
        {
            TableClass deltable = manager.database_on.getTable(inputList[il]);
            if (inputList[il + 1] == "where" && inputList[il + 3] == "=")
            {
                il = il + 2;
                int colindex = deltable.getIndexFromFieldName(inputList[il]);
                il = il + 2;
                int rowindex = deltable.getRowIndex(colindex, inputList[il]);
                deltable.deleteRow(rowindex);
                deltable.saveData();
                return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}

bool updateTo(vector<string> inputList, int ilen)
{
    int il = 1;
    Manager& manager = Manager::get_instance();
    manager.readDatabase();
    manager.openDatabase(DataBaseName);
    manager.database_on.readTables();
    if (manager.database_on.is_in(inputList[il]))
    {
        TableClass uptable = manager.database_on.getTable(inputList[il]);
        if (inputList[il + 1] == "set" && inputList[il + 5] == "where")
        {
            il = il + 2;
            int aftercolindex = uptable.getIndexFromFieldName(inputList[il]);
            il = il + 2;
            string updata = inputList[il];
            il = il + 2;
            int bfcolindex = uptable.getIndexFromFieldName(inputList[il]);
            il = il + 2;
            int rowindex = uptable.getRowIndex(bfcolindex, inputList[il]);
            uptable.changeRow(rowindex, aftercolindex, updata);
            uptable.saveData();
            return true;
        }
        else return false;
    }
    else return false;
}

bool selectTo(vector<string> inputList, int ilen)
{
    int il = 1;
    if (inputList[il] == "*" && inputList[il + 1] == "from")
    {
        il = il + 2;
        Manager& manager = Manager::get_instance();
        manager.readDatabase();
        manager.openDatabase(DataBaseName);
        manager.database_on.readTables();
        if (manager.database_on.is_in(inputList[il]))
        {
            TableClass selecttable = manager.database_on.getTable(inputList[il]);
            selecttable.printTable();
            selecttable.saveData();
            return true;
        }
        else return false;
    }
    else return false;
}
//bool is_in(string tableName)
//{
//    bool in = false;
//    for(int i=0;i<Database::nameOfTables.size();++i)
//    {
//        if(tableName == Database::nameOfTables[i])
//        {
//            in = true;
//            break;
//        }
//    }
//    return in;
//}
