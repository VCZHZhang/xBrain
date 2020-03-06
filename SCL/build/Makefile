CC := gcc
RM := rm
MKDIR := mkdir
INC_PATH := ../include 
LDFLAGS=
SRC_PATH = ../src
CFLAGS = -c -I $(INC_PATH)
DIRS = $(shell find $(SRC_PATH) -maxdepth 4 -type d)
SRC_C += $(foreach dir, $(DIRS), $(wildcard $(dir)/*c))
OBJS_C = $(patsubst %.c, %.o,$(SRC_C))
TARGET=scl
all:$(TARGET)
scl: $(OBJS_C)
	@echo "xx"
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "Create $@ Success."


$(OBJS_C):%.o:%.c
	echo "开始解析"
	$(CC)  $(CFLAGS) $^ -o $@ 

.PHONY:clean show
clean:
	rm $(TARGET) $(OBJS_C)
show:
	@echo $(OBJS_C)
