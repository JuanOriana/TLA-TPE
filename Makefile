PHONY = all clean
CCFLAGS = -Wall -Wno-unused-function -std=c99 -g -Wdiv-by-zero #-fsanitize=address -DYYDEBUG=1 
YLFLAGS = -lfl
MACYLFLAGS = -ll
MKDIR_BIN = bin
SRC_FOLDER = .

all: bin parser

PARSER_OBJ = compiler.o lex.yy.o y.tab.o

PROGRAM_OBJ = program temp.c

OBJ = lex.yy.c y.tab.c y.tab.h

GCC_CXXFLAGS = -DMESSAGE='"Compiled with GCC"'
CLANG_CXXFLAGS = -DMESSAGE='"Compiled with Clang"' -Wno-gnu-zero-variadic-macro-arguments
UNKNOWN_CXXFLAGS = -DMESSAGE='"Compiled with an unknown compiler"'

ifeq ($(CC),g++)
  CCFLAGS += $(GCC_CXXFLAGS)
else ifeq ($(CC),clang)
  CCFLAGS += $(CLANG_CXXFLAGS)
else
  CCFLAGS += $(UNKNOWN_CXXFLAGS)
endif

parser:
	lex $(SRC_FOLDER)/lang.l
	yacc -d $(SRC_FOLDER)/lang.y
	$(CC) $(CCFLAGS) $(SRC_FOLDER)/tree.c $(SRC_FOLDER)/var_validator.c lex.yy.c y.tab.c $(SRC_FOLDER)/compiler.c $(MACYLFLAGS) -o $(MKDIR_BIN)/compiler
	rm -rf $(OBJ)

bin: $(shell mkdir -p $(MKDIR_BIN))

clean: 
	rm -rf $(PARSER_OBJ) $(PROGRAM_OBJ) $(OBJ) $(MKDIR_BIN)/compiler
