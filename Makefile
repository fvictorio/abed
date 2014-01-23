CC = g++
LINKER = g++
CFLAGS = -c -g -Wall
LFLAGS = 

INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib

CPP_EXT = .cpp
OBJ_EXT = .o
PREREQ_EXT = .P

CPP_FILES = $(wildcard $(LIB_DIR)/*$(CPP_EXT))
OBJ_FILES = $(subst $(LIB_DIR),$(OBJ_DIR),$(subst $(CPP_EXT),$(OBJ_EXT),$(CPP_FILES)))

all : $(OBJ_FILES)

.%$(PREREQ_EXT) : $(LIB_DIR)/%$(CPP_EXT)
	$(CC) -MM $< > $*.d && \
	sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' < $*.d > $@; \
	             rm -f $*.d; \
				 [ -s $@ ] || rm -f $@


$(OBJ_DIR)/%$(OBJ_EXT) : $(LIB_DIR)/%$(CPP_EXT)
	$(CC) $(CFLAGS) $< -o $@

include $(addprefix .,$(notdir $(OBJ_FILES:$(OBJ_EXT)=$(PREREQ_EXT))))

% : %$(OBJ_EXT) ;
