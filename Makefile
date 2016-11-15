CC := g++

ROOT := $(shell pwd)

CFLAGS := -Wall -g -std=c++11

TARGET := main  

OBJS = *.o
# 宏定义 
DEFS := -DDEBUG
#路径
INC := -I/usr/include -I/usr/local/include -I./com
#链接库
LIBS := -pthread

#最后添加
CFLAGS += $(DEFS) 
    
%.o:%.cpp  
	$(CC) $(CFLAGS) $(INC) -c $<  
	
$(TARGET):$(OBJS)  
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	$(shell find . -name '*.o' |xargs rm -f) 
	
	
 
