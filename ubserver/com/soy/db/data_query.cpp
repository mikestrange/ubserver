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

RowItem::~RowItem()
{
    
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
:m_row(0)
{}

DataQuery::~DataQuery()
{
    clear();
}

DataQuery::DBList* DataQuery::Next()
{
    DBList *v = new DBList;
    m_vector.push_back(v);
    return v;
}

    //gets
void DataQuery::row(size_t v)
{
    m_row = v;
}

size_t DataQuery::row()
{
    return m_row;
}

size_t DataQuery::length()const
{
    return m_vector.size();
}

bool DataQuery::empty()const
{
    return m_vector.empty();
}

bool DataQuery::exceed()const
{
    return m_row >= m_vector.size();
}

DataQuery::DBList* DataQuery::current()
{
    if(exceed()) return NULL;
    return m_vector[m_row];
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
        if(strcmp(key, item->key.c_str()) == 0)
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
    if(item && strcmp(item->value.c_str(), value) == 0)
    {
        return true;
    }
    return false;
}

bool DataQuery::match(size_t index, const char* value)
{
    auto item = result(index);
    if(item && strcmp(item->value.c_str(), value) == 0)
    {
        return true;
    }
    return false;
}

void DataQuery::clear()
{
    int len = (int)m_vector.size();
    m_row = 0;
    if(len > 0)
    {
        for(int i = len - 1; i >= 0; i--)
        {
            DBList& v = *m_vector[i];
            LOG_DEBUG("删除啊->%ld %d", i, v.size());
            for(int j = (int)v.size() - 1; j >= 0; j--)
            {
                delete v[j];
            }
            delete m_vector[i];
        }
        m_vector.clear();
    }
}

//查看
void DataQuery::toString()
{
    size_t length = m_vector.size();
    for(size_t i = 0; i < length; i++)
    {
        DBList& v = *m_vector[i];
        std::cout<<(i+1)<<" = {"<<std::endl;
        size_t rowLen = v.size();
        for(size_t j = 0; j < rowLen; j++)
        {
            RowItem* item = v[j];
            std::cout<<"    key="<<item->key<<", value="<<item->value<<std::endl;
        }
        std::cout<<"};"<<std::endl;
    }
}
