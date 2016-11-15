//
//  data_query.hpp
//  ServerPlugIn
//
//  Created by MikeRiy on 16/8/2.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "data_query.h"

//class RowItem
void RowItem::toString()
{
    std::cout<<"item ## key="<<key<<", value=%s"<<value<<std::endl;
}

RowItem::~RowItem(){
    
}

RowItem* RowItem::create(char* key, char* value)
{
    auto item = new RowItem;
    item->key = key;
    item->value = value;
    return item;
}

//class DataQuery
DataQuery::DataQuery()
:_row(0)
{}

DataQuery::~DataQuery()
{
    clear();
}

DataQuery::DBList& DataQuery::Next()
{
    DBList *row = new DBList;
    _Vector.push_back(row);
    return *row;
}

    //gets
void DataQuery::row(size_t v)
{
    _row = v;
}

size_t DataQuery::row()
{
    return _row;
}

size_t DataQuery::length()const
{
    return _Vector.size();
}

bool DataQuery::empty()const
{
    return _Vector.empty();
}

bool DataQuery::exceed()const
{
    return _row >= _Vector.size();
}

DataQuery::DBList* DataQuery::current()
{
    if(exceed()) return NULL;
    return _Vector[_row];
}

//当前行的一个结果(健和值)
RowItem* DataQuery::result(size_t index)
{
    if(exceed()) return NULL;
    DBList& row = *current();
    if(index >= row.size()) return NULL;
    return row[index];
}

//当前行的一个结果(匹配key)
RowItem* DataQuery::result(const char* key)
{
    if(exceed()) return NULL;
    //get
    DBList& row = *current();
    for(size_t i = 0; i < row.size(); i++)
    {
        auto item = row[i];
        if(strcmp(key, item->key) == 0)
        {
            return item;
        }
    }
    return NULL;
}

//快捷方式
RowItem* DataQuery::operator[] (const char* key)
{
    return result(key);
}

RowItem* DataQuery::operator[] (size_t index)
{
    return result(index);
}

//匹配当前行
bool DataQuery::match(const char* key, const char* value)
{
    auto item = result(key);
    if(item && strcmp(item->value, value) == 0)
    {
        trace("match ok: row:%ld key = %s, math value = %s", _row, key, value);
        return true;
    }
    trace("match error: row:%ld key = %s, math value = %s", _row, key, value);
    return false;
}

bool DataQuery::match(size_t index, const char* value)
{
    auto item = result(index);
    if(item && strcmp(item->value, value) == 0)
    {
        trace("match ok: row:%ld index = %ld, math value = %s", _row, index, value);
        return true;
    }
    trace("match error: row:%ld index = %ld, math value = %s", _row, index, value);
    return false;
}

void DataQuery::clear()
{
    size_t len = _Vector.size();
    _row = 0;
    if(len > 0)
    {
        for(int i = 0; i < len; i++)
        {
            DBList& row = *_Vector[i];
            for(int j = 0; j < row.size(); j++)
            {
                delete row[j];
            }
            delete _Vector[i];
        }
        _Vector.clear();
    }
}

//查看
void DataQuery::toString()
{
    int length = (int)_Vector.size();
    for(int i = 0; i < length; i++)
    {
        DBList& row = *_Vector[i];
        std::cout<<(i+1)<<" = {"<<std::endl;
        int rowLen = (int)row.size();
        for(int j = 0; j < rowLen; j++)
        {
            RowItem* item = row[j];
            std::cout<<"    key="<<item->key<<", value="<<item->value<<std::endl;
        }
        std::cout<<"};"<<std::endl;
    }
}
