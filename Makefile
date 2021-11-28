CCFLAGS = -Wall -Wno-unused-function -std=c99 -g -Wdiv-by-zero #-fsanitize=address COMMENTED FOR VALGRIND USAGE
YLFLAGS = -lfl
MACYLFLAGS = -ll
SRC_FOLDER = .

PARSER_OBJ = gcan.o lex.yy.o y.tab.o
PROGRAM_OBJ = program aux.c
OBJ = lex.yy.c y.tab.c y.tab.h

all: parser
parser:
	lex $(SRC_FOLDER)/lang.l
	yacc -d $(SRC_FOLDER)/lang.y
	$(CC) $(CCFLAGS) $(SRC_FOLDER)/ast.c $(SRC_FOLDER)/ast_to_c.c $(SRC_FOLDER)/var_validator.c lex.yy.c y.tab.c $(SRC_FOLDER)/gcan.c $(YLFLAGS) -o gcan
	rm -rf $(OBJ)

clean: 
	rm -rf $(PARSER_OBJ) $(PROGRAM_OBJ) $(OBJ) gcan


PHONY = all clean
