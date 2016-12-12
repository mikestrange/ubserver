//
//  data_bank.h
//  ServerPlugIn
//  1,/usr/local/mysql/include
//  2,/usr/local/mysql/lib
//  3,libmysqld.a libmysqlclient.a
//  4,-lrt -lz -lm
//  Created by MikeRiy on 16/7/30.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "data_bank.h"

DataBank::DataBank()
:isconnected(false)
,port(0)
{

}
    
DataBank::~DataBank()
{
    close();
}

void DataBank::setup(const char* host,
                       const char* user,
                       const char* pswd,
                       const char* table,
                       unsigned int port)
{
    this->host = host;
    this->user = user;
    this->password = pswd;
    this->table = table;
    this->port = port;
}

bool DataBank::connent()
{
    if(isConnected())
    {
        Log::Debug("mysql is connect");
        return true;
    }
    return reconnect();
}

bool DataBank::reconnect()
{
    isconnected = false;
#ifdef MY_SQL
    //初始化
    if(mysql_init(&myCont)==NULL)
    {
        Log::Debug("mysql init error");
        return false;
    };
    //连接数据库
    if(mysql_real_connect(&myCont, host.c_str(), user.c_str(), password.c_str(), table.c_str(), port, NULL, 0))
    {
        isconnected = true;
        //设置编码格式 写入
        mysql_set_character_set(&myCont, "utf8");
        Log::Debug("mysql connect succeed");
    }else{
        mysql_close(&myCont);
        Log::Debug("mysql failed");
    };
#else
    Log::Debug("undefined MY_SQL");
#endif
    return isconnected;
}

void DataBank::close()
{
    if(isConnected())
    {
        isconnected = false;
        #ifdef MY_SQL
        mysql_close(&myCont);
        #endif
        Log::Debug("mysql close ok!");
    }else{
        Log::Debug("mysql close error: is no open");
    }
}

bool DataBank::isConnected()const
{
    return isconnected;
}

bool DataBank::apply(const char* sql)
{
    if(isConnected())
    {
        Log::Debug("mysql = %s", sql);
        int ret = -1;
        #ifdef MY_SQL
            ret = mysql_query(&myCont, sql);
        #endif
        if(ret != 0)
        {
            Log::Warn("mysql apply error ret=%d",ret);
        }
        return ret == 0;
    }
    Log::Warn("mysql apply error: is no open");
    return false;
}

bool DataBank::applyFormat(const char* fm, ...)
{
    STR_FORMAT(1024);
    return apply(buf);
}

bool DataBank::findFormat(DataQuery& query, const char* fm,...)
{
    STR_FORMAT(1024);
    return find(query, buf);
}

bool DataBank::find(DataQuery& query, const char* sql)
{
    //"select * from player"
    #ifdef MY_SQL
    if(apply(sql))
    {
        //保存查询到的数据到result
        MYSQL_RES *result = mysql_store_result(&myCont);
        if(result)
        {
            MYSQL_FIELD *fd;
            std::vector<MYSQL_FIELD*> keys;
            for(int i = 0; (fd = mysql_fetch_field(result)); i++)
            {
                keys.push_back(fd);//fd->name
            }
            int line = mysql_num_fields(result);
            MYSQL_ROW sql_row;
            while((sql_row = mysql_fetch_row(result)))
            {
                DataQuery::DBList &row = query.Next();
                for(int i = 0; i < line; i++)
                {
                    MYSQL_FIELD* field = keys[i];
                    //当前行添加
                    row.push_back(RowItem::create(field->name, sql_row[i]));
                }
            }
            //释放结果资源
            mysql_free_result(result);
            return true;
        }else{
            Log::Warn("mysql find result error");
            return false;
        }
    }
    #endif
    return false;
}
