CC = g++
CFLAGS = -Wall -g -std=c++11 # -v
TARGET = main
ROOT   := $(shell pwd)

#这里递归遍历3级子目录
DIRS := $(shell find . -maxdepth 5 -type d)
#这里循环遍历目录的cpp文件
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
#替换文件后缀 ，也可以写成 OBJS = $(FILES:%.cpp=%.o)
OBJS = $(patsubst %.cpp,%.o, $(FILES))

#定义宏
DEF = -DLINUX #-D__cplusplus
## mac/centos
LIB_PATH := -L/usr/local/mysql/lib -L/usr/lib64/mysql/
#链接库文件
LIBS = -lpthread -lm -lstdc++
#头文件路径
INCLUDE_PATH := -I/usr/include -I/usr/local/include -I/usr/local/mysql/include -I/usr/include/mysql -I./com
#add flags 
CFLAGS += $(INCLUDE_PATH)
CFLAGS += $(LIB_PATH)

# Search paths
.cpp.o:
	$(CC) -c $(CFLAGS) $(DEF) $< -o $@
.c.o:
	$(CC) -c $(CFLAGS) $(DEF) $< -o $@
        
main:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
 		
clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)