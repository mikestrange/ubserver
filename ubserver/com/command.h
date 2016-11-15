//
//  command.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef command_h
#define command_h

#include <stdio.h>
//命令
template <class T>
class Command
{
public:
    virtual void OnRespondHandler(T msg)=0;
};

//命令观察
template <class T>
class ComApplyer
{
private:
    Command<T>* command;
public:
    ComApplyer(Command<T>* target)
    :command(target){
        
    };
    
    virtual ~ComApplyer()
    {
        
    }
public:
    void call(T msg)
    {
        command->OnRespondHandler(msg);
    }
    
    bool match(Command<T>* target)
    {
        return command == target;
    }
};

#endif /* command_h */
