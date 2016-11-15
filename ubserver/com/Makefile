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

## used headers  file path
INCLUDE_PATH := -I/usr/include -I/usr/local/include -I/usr/local/mysql/include -I/usr/include/mysql

## used include librarys file path
LIBRARY_PATH := -L/usr/local/mysql/lib
#-pthread

## need libs, add at here
LIBS := -pthread -lmysqlclient

DEFS := -DDEBUG

## get all librarys
CFLAGS += $(DEFS)

## get all include path
CFLAGS += $(INCLUDE_PATH)

## get all library path
CFLAGS += $(LIBRARY_PATH)

## get all librarys
CFLAGS += $(LIBS)

build:
	$(CC) -c $(CFLAGS) $(SRCS)

clean:
	$(RM) $(OBJS) $(TARGET)

