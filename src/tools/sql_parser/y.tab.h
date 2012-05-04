
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     STMT = 258,
     OP = 259,
     ST = 260,
     NSPLIT = 261,
     ST_LIST = 262,
     FM = 263,
     NAME = 264,
     FM_LIST = 265,
     NAME_LIST = 266,
     WH = 267,
     WHSPLIT = 268,
     WH_LIST = 269,
     WHNAME_LIST = 270,
     WHNAME = 271,
     OPERATOR = 272,
     LBORDER = 273,
     RBORDER = 274,
     TERMINATOR = 275,
     NUMBER = 276
   };
#endif
/* Tokens.  */
#define STMT 258
#define OP 259
#define ST 260
#define NSPLIT 261
#define ST_LIST 262
#define FM 263
#define NAME 264
#define FM_LIST 265
#define NAME_LIST 266
#define WH 267
#define WHSPLIT 268
#define WH_LIST 269
#define WHNAME_LIST 270
#define WHNAME 271
#define OPERATOR 272
#define LBORDER 273
#define RBORDER 274
#define TERMINATOR 275
#define NUMBER 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 14 "sql.y"

	SqlNodeType* pNode;



/* Line 1676 of yacc.c  */
#line 100 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


