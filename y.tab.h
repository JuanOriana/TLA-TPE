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
     START = 258,
     EOL = 259,
     FIN = 260,
     COMB = 261,
     PERM = 262,
     MEAN = 263,
     MEDIAN = 264,
     MODE = 265,
     STDEV = 266,
     RANGE = 267,
     QTR1 = 268,
     QTR3 = 269,
     INTER_QTR = 270,
     IN = 271,
     ASSIGN = 272,
     WRITE = 273,
     READ = 274,
     SIZE = 275,
     IF = 276,
     WHILE = 277,
     DO = 278,
     END = 279,
     ELSE = 280,
     SYMBOL_NAME = 281,
     BIN_OP = 282,
     UNI_OP = 283,
     NUMBER = 284,
     STRING = 285,
     BOOLEAN = 286,
     STRING_TYPE = 287,
     NUMBER_TYPE = 288,
     BOOLEAN_TYPE = 289,
     NATURAL = 290
   };
#endif
/* Tokens.  */
#define START 258
#define EOL 259
#define FIN 260
#define COMB 261
#define PERM 262
#define MEAN 263
#define MEDIAN 264
#define MODE 265
#define STDEV 266
#define RANGE 267
#define QTR1 268
#define QTR3 269
#define INTER_QTR 270
#define IN 271
#define ASSIGN 272
#define WRITE 273
#define READ 274
#define SIZE 275
#define IF 276
#define WHILE 277
#define DO 278
#define END 279
#define ELSE 280
#define SYMBOL_NAME 281
#define BIN_OP 282
#define UNI_OP 283
#define NUMBER 284
#define STRING 285
#define BOOLEAN 286
#define STRING_TYPE 287
#define NUMBER_TYPE 288
#define BOOLEAN_TYPE 289
#define NATURAL 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "./lang.y"
{
    char string[1024];
    double number;
    char boolean;
    struct node_t * node;
    struct node_t * list;

}
/* Line 1529 of yacc.c.  */
#line 128 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

