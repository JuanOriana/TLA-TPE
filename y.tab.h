/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FINAL_EOF = 258,
     DELIMETER = 259,
     CURLY_OPEN = 260,
     CURLY_CLOSE = 261,
     PARENTH_OPEN = 262,
     PARENTH_CLOSE = 263,
     ASSIGN = 264,
     MAIN = 265,
     WRITE = 266,
     READ = 267,
     SIZE = 268,
     PLOT = 269,
     RETURN = 270,
     FINAL = 271,
     IF = 272,
     WHILE = 273,
     ELSE = 274,
     SYMBOL_ID = 275,
     BIN_OP = 276,
     UNI_OP = 277,
     BIN_CV_OP = 278,
     TRI_CV_OP = 279,
     BIN_CV_OP_CHAR = 280,
     UNI_CV_OP = 281,
     QUAD_CV_OP_CHAR = 282,
     INTEGER = 283,
     STRING = 284,
     DOUBLE = 285,
     ASCII = 286,
     STRING_TYPE = 287,
     INTEGER_TYPE = 288,
     DOUBLE_TYPE = 289,
     CANVAS_TYPE = 290,
     NATURAL = 291,
     IN = 292
   };
#endif
/* Tokens.  */
#define FINAL_EOF 258
#define DELIMETER 259
#define CURLY_OPEN 260
#define CURLY_CLOSE 261
#define PARENTH_OPEN 262
#define PARENTH_CLOSE 263
#define ASSIGN 264
#define MAIN 265
#define WRITE 266
#define READ 267
#define SIZE 268
#define PLOT 269
#define RETURN 270
#define FINAL 271
#define IF 272
#define WHILE 273
#define ELSE 274
#define SYMBOL_ID 275
#define BIN_OP 276
#define UNI_OP 277
#define BIN_CV_OP 278
#define TRI_CV_OP 279
#define BIN_CV_OP_CHAR 280
#define UNI_CV_OP 281
#define QUAD_CV_OP_CHAR 282
#define INTEGER 283
#define STRING 284
#define DOUBLE 285
#define ASCII 286
#define STRING_TYPE 287
#define INTEGER_TYPE 288
#define DOUBLE_TYPE 289
#define CANVAS_TYPE 290
#define NATURAL 291
#define IN 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "./lang.y"
{
    char string[1024];
    int integer;
    double floating;
    struct node_t * node;
    struct node_t * list;

}
/* Line 1529 of yacc.c.  */
#line 132 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

