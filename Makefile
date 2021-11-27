CCFLAGS = -Wall -Wno-unused-function -std=c99 -g -Wdiv-by-zero #-fsanitize=address COMMENTED FOR VALGRIND USAGE
YLFLAGS = -lfl
MACYLFLAGS = -ll
SRC_FOLDER = .

all: parser

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
	$(CC) $(CCFLAGS) $(SRC_FOLDER)/ast.c $(SRC_FOLDER)/ast_to_c.c $(SRC_FOLDER)/var_validator.c lex.yy.c y.tab.c $(SRC_FOLDER)/gcan.c $(MACYLFLAGS) -o gcan
	rm -rf $(OBJ)

clean: 
	rm -rf $(PARSER_OBJ) $(PROGRAM_OBJ) $(OBJ) gcan


PHONY = all clean
