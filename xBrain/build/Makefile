CC = gcc
CPP = g++
RM = rm
MKDIR = mkdir
CFLAGS = -Wall -std=gnu99 
CPPFLAGS = -Wall -std=c++11  
LDFLAGS = -lpthread
DIR_OBJS = ../objs_c
DIR_OBJS_CPP = ../objs_cpp
DIR_EXEC = ../exec

DIRS := $(DIR_OBJS) $(DIR_EXEC) $(DIR_OBJS_CPP)
EXEC = xBrain 
SRCS = $(wildcard ../Cpp/*.c)
NODIR_SRCS_C = $(notdir $(SRCS))
OBJS = $(patsubst %.c,%.o, $(SRCS))
tmp = $(notdir $(OBJS))
OBJS := $(addprefix $(DIR_OBJS)/,$(tmp))
C_OBJS_NO_DIR = $(notdir $(OBJS))

SRCS_CPP = $(wildcard ../Cpp/*.cpp)
NODIR_SRCS_CPP = $(notdir $(SRCS_CPP))
OBJS_CPP = $(patsubst %.cpp,%.o, $(SRCS_CPP))
tmp_cpp = $(notdir $(OBJS_CPP))
OBJS_CPP := $(addprefix $(DIR_OBJS_CPP)/,$(tmp_cpp))


EXEC := $(addprefix $(DIR_EXEC)/,$(EXEC))

# dirs and targets
all: $(DIRS) $(EXEC)
#all: $(DIRS) 
$(DIRS):
	$(MKDIR) $@
$(EXEC):$(OBJS) $(OBJS_CPP)
	echo "trigger"
	$(CXX) -o $@ $^ $(LDFLAGS)

$(DIR_OBJS)/%.o:../Cpp/%.c 
#	echo "compiler"
#	echo -e "yilai:"$^ "mubiao:" $@
	$(CC) $(CFLAGS)  -o $@ -c $^ $(CFLAGS)

$(DIR_OBJS_CPP)/%.o:../Cpp/%.cpp
#	echo "compiler"
#	echo -e "yilai:"$^ "mubiao:" $@
	$(CXX)  -o $@ -c $^ $(CPPFLAGS)

clean:
	$(RM) -rf  $(DIRS) $(EXEC)
	$(RM) -rf ../source/*.o

.PHONY: show
show:
	@echo  "src:" $(SRCS)
	@echo  "src_cpp:" $(SRCS_CPP)
	@echo "objs:"$(OBJS)
	@echo "DIR_OBJS:"$(DIR_OBJS)
	@echo  "tmp:" $(tmp)
	@echo "c_objs_no_dir" $(C_OBJS_NO_DIR)

.PHONY: all clean

