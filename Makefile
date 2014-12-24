CC = g++
LINKER = g++
CFLAGS = -c -g -O2 -fno-inline -Wall -Wfatal-errors -Wno-unused-result
LFLAGS = 

INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin

CPP_EXT = .cpp
INC_EXT = .hpp
OBJ_EXT = .o
PREREQ_EXT = .P

CPP_FILES = $(wildcard $(LIB_DIR)/*$(CPP_EXT))
INC_FILES = $(wildcard $(INC_DIR)/*$(INC_EXT))
OBJ_FILES  = $(subst $(LIB_DIR)/,$(OBJ_DIR)/,$(subst $(CPP_EXT),$(OBJ_EXT),$(CPP_FILES)))

TEST_NAME = main

.PHONY: all depend clean test debug

all : $(OBJ_FILES)

debug :
	@echo $(OBJ_FILES)

test : $(OBJ_FILES)
	$(CC) $(CFLAGS) test/$(TEST_NAME).cpp -o $(OBJ_DIR)/$(TEST_NAME).o
	$(LINKER) $(LFLAGS) $(OBJ_DIR)/$(TEST_NAME).o $(OBJ_FILES) -o bin/$(TEST_NAME)
	bin/$(TEST_NAME)

$(OBJ_DIR)/%$(OBJ_EXT) : $(LIB_DIR)/%$(CPP_EXT)
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm $(OBJ_DIR)/*

depend :
	[ ! -f ./.depend ] || rm ./.depend
	for i in $(notdir $(CPP_FILES)); do \
		$(CC) -MM -MT $(OBJ_DIR)/`echo $$i | sed "s/$(CPP_EXT)/$(OBJ_EXT)/"` $(LIB_DIR)/$$i >> ./.depend; \
	done

include .depend
