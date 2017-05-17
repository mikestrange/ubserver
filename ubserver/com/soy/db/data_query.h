//
//  data_query.hpp
//  ServerPlugIn
//
//  Created by MikeRiy on 16/8/2.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef data_query_hpp
#define data_query_hpp

#include <vector>
#include "global.h"
#include "log.h"

//行的一个元素
class RowItem
{
public:
    std::string key;
    std::string value;
    void toString();
    ~RowItem();
public:
    static RowItem* create(char* key, char* value);
};


//数据库读取
class DataQuery
{
public:
    typedef std::vector<RowItem*> DBList;
public:
    DataQuery();
    
    virtual ~DataQuery();
public:
    //当前行
    DBList* Next();
    //gets
public:
    void row(size_t v);
    
    size_t row();
    
    size_t length()const;
    
    bool empty()const;
    
    bool exceed()const;
    
    DBList* current();
    
    //当前行的一个结果(健和值)
    RowItem* result(size_t index);
    
    //当前行的一个结果(匹配key)
    RowItem* result(const char* key);
    
    //快捷方式
    RowItem* operator[] (const char* key);
    
    RowItem* operator[] (size_t index);
    
    //匹配当前行
    bool match(const char* key, const char* value);
    
    bool match(size_t index, const char* value);
    
    void clear();
    
    //查看
    void toString();
    
private:
    std::vector<DBList*> m_vector;
    size_t m_row;
    
};
#endif /* data_query_hpp */
