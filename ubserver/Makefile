#####################################################################
## file        : test makefile for build current dir .c            ##
## author      : jernymy                                           ##
## date-time   : 05/06/2010                                        ##
#####################################################################

CC      = g++
RM      = rm -rf

## source file path
SRC_PATH   := $(shell pwd)

CFLAGS := -Wall -g -std=c++11

## target exec file name
TARGET     := main

## get all source files
SRCS        := $(wildcard $(SRC_PATH)/*.cpp)

## all .o based on all .c
OBJS        := $(SRCS:.cpp=.o)

#获取com需要的类
SUB_COM_OBJS := $(foreach dir,$(SRC_PATH)/com,$(wildcard $(dir)/*.cpp))

#$(warning  "<<-----begin----->>>") 
#$(warning  $(SUB_OBJS)) 
#$(warning  "<<-----end----->>>") 
## used headers  file path
INCLUDE_PATH := -I/usr/include -I/usr/local/include -I/usr/local/mysql/include -I/usr/include/mysql -I./com

## used include librarys file path
## mac下
LIB_PATH := -L/usr/local/mysql/lib 
## centos下
LIB_PATH += -L/usr/lib64/mysql/
#-pthread

## need libs, add at here
LIBS := -pthread -lmysqlclient

DEFS := -DDEBUG

## get all defined
CFLAGS += $(DEFS)

## get all include path
CFLAGS += $(INCLUDE_PATH)

## get all library path
CFLAGS += $(LIB_PATH)

## get all librarys
#CFLAGS += $(LIBS)

        
all: build

build:
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SUB_COM_OBJS) $(OBJS) $(LIBS)
	
##$(RM) $(OBJS)
	
clean:
	$(RM) $(OBJS) $(TARGET)

