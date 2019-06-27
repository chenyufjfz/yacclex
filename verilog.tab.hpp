
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
     IDENTIFIER = 258,
     STATENAME = 259,
     K_ASYNC_RESET = 260,
     SYSTEM_IDENTIFIER = 261,
     DEFINE_IDENTIFIER = 262,
     STRING = 263,
     BASED_NUMBER = 264,
     DEC_NUMBER = 265,
     K_LE = 266,
     K_GE = 267,
     K_EG = 268,
     K_EQ = 269,
     K_NE = 270,
     K_CEQ = 271,
     K_CNE = 272,
     K_LS = 273,
     K_RS = 274,
     K_RSS = 275,
     K_LOR = 276,
     K_LAND = 277,
     K_NAND = 278,
     K_NOR = 279,
     K_NXOR = 280,
     K_TRIGGER = 281,
     K_always = 282,
     K_assign = 283,
     K_automatic = 284,
     K_begin = 285,
     K_case = 286,
     K_casex = 287,
     K_casez = 288,
     K_deassign = 289,
     K_default = 290,
     K_define = 291,
     K_defparam = 292,
     K_disable = 293,
     K_dowhile = 294,
     K_else = 295,
     K_end = 296,
     K_endcase = 297,
     K_enddefine = 298,
     K_endfunction = 299,
     K_endgenerate = 300,
     K_endmodule = 301,
     K_endspecify = 302,
     K_endtask = 303,
     K_event = 304,
     K_for = 305,
     K_force = 306,
     K_forever = 307,
     K_fork = 308,
     K_function = 309,
     K_generate = 310,
     K_genvar = 311,
     K_if = 312,
     K_include = 313,
     K_initial = 314,
     K_inout = 315,
     K_input = 316,
     K_integer = 317,
     K_join = 318,
     K_localparam = 319,
     K_macromodule = 320,
     K_module = 321,
     K_negedge = 322,
     K_or = 323,
     K_output = 324,
     K_parameter = 325,
     K_posedge = 326,
     K_reg = 327,
     K_release = 328,
     K_repeat = 329,
     K_signed = 330,
     K_specify = 331,
     K_task = 332,
     K_undef = 333,
     K_unsigned = 334,
     K_wait = 335,
     K_while = 336,
     K_wire = 337,
     less_than_K_else = 338,
     UNARY_PREC = 339
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 36 "verilog.y"

    Element * emt;
    Expression *exp;
    Statement *smt;
    State *state;
    Assign * assign;
    Variable * var;
    int value;



/* Line 1676 of yacc.c  */
#line 148 "verilog.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

