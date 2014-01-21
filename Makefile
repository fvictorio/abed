CC = g++
LINKER = g++ -o
CFLAGS = -c -g -Wall
LFLAGS = 

INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib

CPP_EXT = .cpp
OBJ_EXT = .o

CPP_FILES = $(wildcard $(LIB_DIR)/*$(CPP_EXT))
OBJ_FILES = $(subst $(LIB_DIR),$(OBJ_DIR),$(subst $(CPP_EXT),$(OBJ_EXT),$(CPP_FILES)))

$(OBJ_DIR)/%$(OBJ_EXT) : $(LIB_DIR)/%$(CPP_EXT)
	$(CC) $(CFLAGS) $< -o $@

all : $(OBJ_FILES)
