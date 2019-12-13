CC = gcc
CPP = g++
CXX = g++
RM = rm
MKDIR = mkdir
INC_PATH = -I./xFile
CFLAGS = -c -Wall -std=gnu99  
CPPFLAGS = -c -Wall -std=c++11  
LDFLAGS = -lpthread
DIR_OBJS = ../objs_c
DIR_OBJS_CPP = ../objs_cpp
DIR_EXEC = ../exec

VPATH = .:./xFile
TARGET = ../exec/Brain

SRC_PATH = ../Cpp
DIRS = $(shell find $(SRC_PATH) -maxdepth 4 -type d)
SRC_CPP += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
SRC_C +=   $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS_CPP = $(patsubst %.cpp, %.o, $(SRC_CPP))
OBJS_C   = $(patsubst %.c, %.o, $(SRC_C))

all: $(TARGET) 
$(TARGET): $(OBJS_CPP)  $(OBJS_C)  
	$(CXX) $^ -o $@ $(LDFLAGS)
	echo Create $(TARGET) Success.
$(OBJS_CPP):%.o : %.cpp  
	$(CXX) $(CPPFLAGS) $< -o $@   
          
$(OBJS_C):%.o : %.c  
	$(CC) $(CFLAGS) $< -o $@    

show:
	echo $(DIRS)
	echo $(OBJS_C)
	echo $(OBJS_CPP)
.PHONY : clean  
clean:  
	rm  $(TARGET) $(OBJS_CPP)  $(OBJS_C) 
