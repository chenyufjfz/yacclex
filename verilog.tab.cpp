
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "verilog.y"

    #include <stdio.h>
    #include "parse_misc.h"
    #include "FileParse.h"
    #define YYDEBUG 1
    void yyerror(char *);
    int yylex(void); 
    extern FileParse * my_parse;
    AlwaysBlock *current_block =NULL;
    Statement * current_top_name_block =NULL;
    
    #define YYRHSLOC(Rhs, K) ((Rhs)[K])
    #define YYLLOC_DEFAULT(Current, Rhs, N)                             \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
          (Current).begin_pos    = YYRHSLOC (Rhs, 1).begin_pos;         \
          (Current).end_pos      = YYRHSLOC (Rhs, N).end_pos;           \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
          (Current).begin_pos    = (Current).end_pos     =              \
            YYRHSLOC (Rhs, 0).end_pos;                                  \
        }                                                               \
    while (0)


/* Line 189 of yacc.c  */
#line 109 "verilog.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 36 "verilog.y"

    Element * emt;
    Expression *exp;
    Statement *smt;
    State *state;
    Assign * assign;
    Variable * var;
    int value;



/* Line 214 of yacc.c  */
#line 241 "verilog.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 266 "verilog.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2822

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  111
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  252
/* YYNRULES -- Number of states.  */
#define YYNSTATES  594

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   107,     2,   103,     2,    95,    88,     2,
      98,    99,    93,    91,   100,    92,   110,    94,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,    97,
      89,   102,    90,    84,   101,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   104,     2,   105,    87,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,    86,   109,   106,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    96
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    14,    17,    20,
      22,    26,    31,    35,    39,    46,    48,    50,    54,    57,
      58,    60,    64,    66,    67,    70,    72,    78,    85,    92,
      94,    96,    99,   106,   107,   116,   117,   131,   135,   138,
     146,   155,   159,   163,   177,   185,   193,   197,   203,   207,
     211,   215,   219,   221,   222,   224,   225,   227,   228,   234,
     236,   239,   242,   245,   248,   251,   254,   258,   262,   266,
     270,   274,   278,   282,   286,   290,   294,   298,   302,   306,
     310,   314,   318,   322,   326,   330,   334,   338,   342,   346,
     350,   356,   358,   360,   362,   364,   368,   375,   379,   384,
     389,   391,   393,   396,   400,   402,   404,   405,   407,   411,
     416,   423,   425,   429,   432,   433,   435,   441,   448,   450,
     452,   454,   456,   457,   459,   463,   465,   469,   472,   476,
     479,   481,   485,   489,   491,   493,   495,   502,   507,   511,
     514,   518,   525,   528,   533,   537,   541,   544,   550,   557,
     564,   571,   577,   585,   599,   605,   608,   611,   617,   622,
     628,   634,   639,   645,   651,   657,   663,   666,   672,   677,
     680,   683,   685,   688,   690,   694,   695,   702,   705,   710,
     714,   718,   724,   732,   738,   745,   750,   756,   763,   765,
     767,   769,   771,   772,   774,   777,   780,   782,   786,   790,
     793,   798,   800,   802,   810,   812,   814,   816,   817,   820,
     825,   827,   831,   834,   837,   839,   841,   845,   849,   851,
     855,   857,   858,   860,   861,   864,   866,   868,   870,   877,
     884,   891,   896,   901,   906,   908,   911,   913,   914,   916,
     919,   921,   923,   925,   929,   935,   937,   939,   944,   949,
     953,   955,   961
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     112,     0,    -1,   113,    -1,   116,    -1,   115,    -1,   114,
      -1,   113,   116,    -1,   113,   115,    -1,   113,   114,    -1,
      58,    -1,    36,     1,    43,    -1,    36,     3,   130,    43,
      -1,    36,     3,    43,    -1,    78,     3,    43,    -1,   117,
       3,   118,    97,   120,    46,    -1,    66,    -1,    65,    -1,
      98,   119,    99,    -1,    98,    99,    -1,    -1,     3,    -1,
     119,   100,     3,    -1,   121,    -1,    -1,   121,   122,    -1,
     122,    -1,    82,   126,   127,   136,    97,    -1,   140,   141,
     126,   127,   142,    97,    -1,    69,    72,   126,   127,     3,
      97,    -1,   125,    -1,   115,    -1,    27,   150,    -1,    27,
      30,    85,     3,     1,    41,    -1,    -1,    27,    30,    85,
       3,   123,   162,   152,    41,    -1,    -1,    27,    30,    85,
       5,   101,    98,   163,     3,    99,    97,   124,   152,    41,
      -1,    28,   169,    97,    -1,    59,   149,    -1,    77,   171,
       3,    97,   172,   148,    48,    -1,    54,   171,   176,     3,
      97,   177,   149,    44,    -1,    55,   120,    45,    -1,    56,
     142,    97,    -1,    50,    98,     3,   102,   130,    97,   130,
      97,     3,   102,   130,    99,   179,    -1,    57,    98,   130,
      99,   180,    40,   179,    -1,     3,   103,    98,   134,    99,
     181,    97,    -1,     3,   181,    97,    -1,    72,   126,   127,
     143,    97,    -1,    62,   143,    97,    -1,    70,   145,    97,
      -1,    64,   145,    97,    -1,    49,   142,    97,    -1,    75,
      -1,    -1,   129,    -1,    -1,    72,    -1,    -1,   104,   130,
      85,   130,   105,    -1,   131,    -1,    92,   131,    -1,   106,
     131,    -1,    88,   131,    -1,   107,   131,    -1,    86,   131,
      -1,    87,   131,    -1,   106,    88,   131,    -1,   106,    86,
     131,    -1,   106,    87,   131,    -1,   130,    87,   130,    -1,
     130,    93,   130,    -1,   130,    94,   130,    -1,   130,    95,
     130,    -1,   130,    91,   130,    -1,   130,    92,   130,    -1,
     130,    88,   130,    -1,   130,    86,   130,    -1,   130,    89,
     130,    -1,   130,    90,   130,    -1,   130,    18,   130,    -1,
     130,    19,   130,    -1,   130,    20,   130,    -1,   130,    14,
     130,    -1,   130,    16,   130,    -1,   130,    11,   130,    -1,
     130,    12,   130,    -1,   130,    15,   130,    -1,   130,    17,
     130,    -1,   130,    21,   130,    -1,   130,    22,   130,    -1,
     130,    84,   130,    85,   130,    -1,   132,    -1,     7,    -1,
       8,    -1,   135,    -1,   108,   133,   109,    -1,   108,   130,
     108,   133,   109,   109,    -1,    98,   130,    99,    -1,   135,
      98,   133,    99,    -1,     6,    98,   133,    99,    -1,     9,
      -1,    10,    -1,    10,     9,    -1,   133,   100,   130,    -1,
     130,    -1,   133,    -1,    -1,     3,    -1,   135,   110,     3,
      -1,   135,   104,   130,   105,    -1,   135,   104,   130,    85,
     130,   105,    -1,   137,    -1,   136,   100,   137,    -1,     3,
     138,    -1,    -1,   139,    -1,   104,   130,    85,   130,   105,
      -1,   139,   104,   130,    85,   130,   105,    -1,    61,    -1,
      69,    -1,    60,    -1,    82,    -1,    -1,     3,    -1,   142,
     100,     3,    -1,   144,    -1,   143,   100,   144,    -1,     3,
     138,    -1,   126,   127,   146,    -1,    62,   146,    -1,   147,
      -1,   146,   100,   147,    -1,     3,   102,   130,    -1,   149,
      -1,    97,    -1,   150,    -1,    30,    85,     3,   156,   151,
      41,    -1,    30,    85,     3,    41,    -1,    30,   151,    41,
      -1,    30,    41,    -1,    53,   151,    63,    -1,    53,    85,
       3,   156,   151,    63,    -1,    53,    63,    -1,    53,    85,
       3,    63,    -1,    38,   135,    97,    -1,    26,   135,    97,
      -1,    52,   149,    -1,    74,    98,   130,    99,   149,    -1,
      31,    98,   130,    99,   158,    42,    -1,    32,    98,   130,
      99,   158,    42,    -1,    33,    98,   130,    99,   158,    42,
      -1,    57,    98,   130,    99,   148,    -1,    57,    98,   130,
      99,   148,    40,   148,    -1,    50,    98,   168,   102,   130,
      97,   130,    97,   168,   102,   130,    99,   149,    -1,    81,
      98,   130,    99,   149,    -1,   160,   148,    -1,   165,   148,
      -1,   101,    98,    93,    99,   148,    -1,   168,    11,   130,
      97,    -1,   168,    11,   160,   130,    97,    -1,   168,    11,
     165,   130,    97,    -1,   168,   102,   130,    97,    -1,   168,
     102,   160,   130,    97,    -1,   168,   102,   165,   130,    97,
      -1,    80,    98,   130,    99,   148,    -1,     6,    98,   134,
      99,    97,    -1,     6,    97,    -1,   135,    98,   133,    99,
      97,    -1,   135,    98,    99,    97,    -1,     1,    97,    -1,
     151,   149,    -1,   149,    -1,   152,   153,    -1,   153,    -1,
      30,   152,    41,    -1,    -1,    30,    85,     3,   154,   152,
      41,    -1,    30,    41,    -1,    30,    85,     3,    41,    -1,
      38,     3,    97,    -1,    26,     3,    97,    -1,    57,    98,
     130,    99,   155,    -1,    57,    98,   130,    99,   155,    40,
     155,    -1,    81,    98,   130,    99,   155,    -1,    81,    98,
     130,    99,    39,   155,    -1,     3,    11,   130,    97,    -1,
       3,    11,   160,   130,    97,    -1,   101,    98,     3,    99,
      97,   164,    -1,   162,    -1,   153,    -1,    97,    -1,   157,
      -1,    -1,   125,    -1,   157,   125,    -1,   158,   159,    -1,
     159,    -1,   133,    85,   148,    -1,    35,    85,   148,    -1,
     103,   161,    -1,   103,    98,   130,    99,    -1,    10,    -1,
       3,    -1,   101,    98,    71,     3,    99,    97,   164,    -1,
      71,    -1,    67,    -1,     4,    -1,    -1,   101,   135,    -1,
     101,    98,   166,    99,    -1,   167,    -1,   166,    68,   167,
      -1,    71,   130,    -1,    67,   130,    -1,   130,    -1,   135,
      -1,   108,   133,   109,    -1,   169,   100,   170,    -1,   170,
      -1,   168,   102,   130,    -1,    29,    -1,    -1,   173,    -1,
      -1,   173,   174,    -1,   174,    -1,   125,    -1,   175,    -1,
      61,   128,   126,   127,   142,    97,    -1,    69,   128,   126,
     127,   142,    97,    -1,    60,   128,   126,   127,   142,    97,
      -1,    61,    62,   142,    97,    -1,    69,    62,   142,    97,
      -1,    60,    62,   142,    97,    -1,   129,    -1,    75,   129,
      -1,    62,    -1,    -1,   178,    -1,   177,   178,    -1,   175,
      -1,   125,    -1,   122,    -1,    30,   120,    41,    -1,    30,
      85,     3,   120,    41,    -1,   179,    -1,    97,    -1,     3,
      98,   134,    99,    -1,     3,    98,   182,    99,    -1,   182,
     100,   183,    -1,   183,    -1,   110,     3,    98,   130,    99,
      -1,   110,     3,    98,    99,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    99,   100,   101,   102,   106,   110,   117,
     121,   124,   128,   132,   138,   147,   148,   151,   154,   157,
     161,   162,   166,   167,   171,   175,   179,   194,   211,   219,
     220,   221,   224,   228,   228,   241,   241,   254,   257,   260,
     263,   266,   269,   272,   275,   279,   282,   288,   303,   318,
     321,   324,   345,   346,   350,   351,   355,   356,   360,   364,
     365,   369,   373,   377,   381,   385,   389,   393,   397,   401,
     406,   411,   416,   421,   426,   431,   436,   441,   446,   451,
     456,   461,   466,   471,   476,   481,   486,   491,   496,   501,
     506,   515,   518,   521,   522,   533,   537,   541,   546,   550,
     556,   557,   558,   562,   567,   571,   572,   578,   579,   580,
     581,   585,   586,   593,   604,   605,   609,   610,   614,   615,
     616,   620,   621,   625,   626,   633,   634,   641,   652,   653,
     657,   658,   662,   666,   667,   671,   672,   673,   677,   678,
     683,   684,   685,   686,   687,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   708,   709,   710,   711,   712,
     716,   717,   721,   722,   726,   730,   730,   738,   739,   740,
     744,   748,   753,   759,   764,   769,   774,   779,   790,   794,
     795,   799,   800,   804,   805,   809,   810,   814,   815,   819,
     820,   824,   825,   829,   839,   840,   843,   844,   848,   849,
     853,   854,   858,   859,   860,   864,   865,   869,   870,   874,
     878,   879,   883,   884,   888,   889,   893,   894,   898,   899,
     900,   901,   902,   903,   907,   908,   909,   910,   914,   915,
     919,   920,   924,   925,   926,   930,   931,   935,   936,   940,
     941,   945,   946
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STATENAME",
  "K_ASYNC_RESET", "SYSTEM_IDENTIFIER", "DEFINE_IDENTIFIER", "STRING",
  "BASED_NUMBER", "DEC_NUMBER", "K_LE", "K_GE", "K_EG", "K_EQ", "K_NE",
  "K_CEQ", "K_CNE", "K_LS", "K_RS", "K_RSS", "K_LOR", "K_LAND", "K_NAND",
  "K_NOR", "K_NXOR", "K_TRIGGER", "K_always", "K_assign", "K_automatic",
  "K_begin", "K_case", "K_casex", "K_casez", "K_deassign", "K_default",
  "K_define", "K_defparam", "K_disable", "K_dowhile", "K_else", "K_end",
  "K_endcase", "K_enddefine", "K_endfunction", "K_endgenerate",
  "K_endmodule", "K_endspecify", "K_endtask", "K_event", "K_for",
  "K_force", "K_forever", "K_fork", "K_function", "K_generate", "K_genvar",
  "K_if", "K_include", "K_initial", "K_inout", "K_input", "K_integer",
  "K_join", "K_localparam", "K_macromodule", "K_module", "K_negedge",
  "K_or", "K_output", "K_parameter", "K_posedge", "K_reg", "K_release",
  "K_repeat", "K_signed", "K_specify", "K_task", "K_undef", "K_unsigned",
  "K_wait", "K_while", "K_wire", "less_than_K_else", "'?'", "':'", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UNARY_PREC", "';'", "'('", "')'", "','", "'@'", "'='", "'#'", "'['",
  "']'", "'~'", "'!'", "'{'", "'}'", "'.'", "$accept", "main",
  "source_file", "include_item", "define_item", "module", "module_start",
  "module_port_list_opt", "list_of_ports", "module_item_list_opt",
  "module_item_list", "module_item", "$@1", "$@2", "block_item_decl",
  "signed_opt", "range_opt", "reg_opt", "range", "expression",
  "expr_primary", "number", "expression_list_proper",
  "expression_list_with_nuls", "hierarchy_identifier", "net_variable_list",
  "net_variable", "dimensions_opt", "dimensions", "port_type",
  "net_type_opt", "list_of_identifiers", "register_variable_list",
  "register_variable", "parameter_assign_decl", "parameter_assign_list",
  "parameter_assign", "statement_or_null", "statement",
  "statement_wo_name_block", "statement_list", "statement_syn_list",
  "statement_syn", "@3", "statement_syn_or_null", "block_item_decls_opt",
  "block_item_decls", "case_items", "case_item", "delay1",
  "delay_value_simple", "wait_cycle", "pos_or_neg_edge",
  "statename_or_null", "event_control", "event_expression_list",
  "event_expression", "lpvalue", "cont_assign_list", "cont_assign",
  "automatic_opt", "task_item_list_opt", "task_item_list", "task_item",
  "task_port_item", "function_range_or_type_opt", "function_item_list",
  "function_item", "generate_block", "generate_block_opt", "gate_instance",
  "port_name_list", "port_name", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    63,    58,   124,    94,    38,    60,
      62,    43,    45,    42,    47,    37,   339,    59,    40,    41,
      44,    64,    61,    35,    91,    93,   126,    33,   123,   125,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   111,   112,   113,   113,   113,   113,   113,   113,   114,
     115,   115,   115,   115,   116,   117,   117,   118,   118,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   123,   122,   124,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   125,   125,   125,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   132,   132,   133,   133,   134,   134,   135,   135,   135,
     135,   136,   136,   137,   138,   138,   139,   139,   140,   140,
     140,   141,   141,   142,   142,   143,   143,   144,   145,   145,
     146,   146,   147,   148,   148,   149,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     151,   151,   152,   152,   153,   154,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   167,   168,   168,   169,   169,   170,
     171,   171,   172,   172,   173,   173,   174,   174,   175,   175,
     175,   175,   175,   175,   176,   176,   176,   176,   177,   177,
     178,   178,   179,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     2,     2,     1,
       3,     4,     3,     3,     6,     1,     1,     3,     2,     0,
       1,     3,     1,     0,     2,     1,     5,     6,     6,     1,
       1,     2,     6,     0,     8,     0,    13,     3,     2,     7,
       8,     3,     3,    13,     7,     7,     3,     5,     3,     3,
       3,     3,     1,     0,     1,     0,     1,     0,     5,     1,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     1,     1,     1,     1,     3,     6,     3,     4,     4,
       1,     1,     2,     3,     1,     1,     0,     1,     3,     4,
       6,     1,     3,     2,     0,     1,     5,     6,     1,     1,
       1,     1,     0,     1,     3,     1,     3,     2,     3,     2,
       1,     3,     3,     1,     1,     1,     6,     4,     3,     2,
       3,     6,     2,     4,     3,     3,     2,     5,     6,     6,
       6,     5,     7,    13,     5,     2,     2,     5,     4,     5,
       5,     4,     5,     5,     5,     5,     2,     5,     4,     2,
       2,     1,     2,     1,     3,     0,     6,     2,     4,     3,
       3,     5,     7,     5,     6,     4,     5,     6,     1,     1,
       1,     1,     0,     1,     2,     2,     1,     3,     3,     2,
       4,     1,     1,     7,     1,     1,     1,     0,     2,     4,
       1,     3,     2,     2,     1,     1,     3,     3,     1,     3,
       1,     0,     1,     0,     2,     1,     1,     1,     6,     6,
       6,     4,     4,     4,     1,     2,     1,     0,     1,     2,
       1,     1,     1,     3,     5,     1,     1,     4,     4,     3,
       1,     5,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     9,    16,    15,     0,     0,     2,     5,     4,
       3,     0,     0,     0,     0,     1,     8,     7,     6,    19,
      10,   107,     0,    92,    93,   100,   101,    12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    91,    94,
      13,     0,     0,     0,   102,    64,    65,    62,    60,     0,
       0,     0,     0,    61,    63,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    18,     0,    23,   104,     0,    97,
      67,    68,    66,     0,     0,    95,    84,    85,    82,    86,
      83,    87,    79,    80,    81,    88,    89,     0,    76,    69,
      75,    77,    78,    73,    74,    70,    71,    72,     0,     0,
     108,    17,     0,     0,     0,     0,     0,     0,   221,    23,
       0,     0,     0,   120,   118,     0,    53,   119,    53,    53,
     221,    53,    30,     0,    22,    25,    29,   122,    99,     0,
     103,     0,    98,     0,   109,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,    31,     0,
       0,     0,   215,     0,     0,   218,   123,     0,     0,   220,
     237,     0,     0,     0,     0,    38,   135,   114,     0,   125,
       0,    52,    55,     0,    53,     0,    55,     0,    55,    14,
      24,   121,    53,     0,    90,     0,   106,   106,    46,   169,
     166,   106,     0,   139,     0,   171,     0,     0,     0,     0,
       0,     0,   146,   142,     0,     0,     0,     0,     0,     0,
       0,   208,   202,   201,     0,   199,     0,     0,   134,   155,
     133,   156,     0,     0,     0,    37,     0,    51,     0,     0,
     236,     0,     0,   234,     0,    41,    42,     0,     0,     0,
     127,   115,    48,     0,     0,   129,   130,     0,    54,    50,
      55,    49,     0,     0,     0,    55,    96,   110,     0,   105,
       0,     0,   250,     0,     0,   145,     0,     0,   138,   170,
       0,     0,     0,   144,     0,   192,   140,     0,     0,     0,
       0,     0,     0,     0,   214,     0,   210,     0,   216,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   219,   217,
     124,     0,   235,     0,     0,     0,   192,     0,     0,   126,
       0,     0,   128,     0,     0,   223,   114,     0,   111,     0,
       0,   247,   248,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   143,   193,     0,   191,     0,     0,     0,
       0,   213,   212,     0,     0,   209,   200,   168,     0,     0,
     158,     0,     0,   161,     0,     0,     0,     0,     0,    23,
     246,   242,   245,     0,   137,     0,     0,     0,   132,   131,
       0,    47,    57,    57,    57,   226,     0,   222,   225,   227,
     113,    26,     0,     0,     0,   249,     0,   165,    32,     0,
       0,     0,     0,     0,     0,   196,     0,     0,     0,     0,
     194,   151,   147,   164,   154,   157,   211,   167,   159,   160,
     162,   163,     0,     0,   241,   240,     0,   238,     0,     0,
       0,     0,     0,     0,    28,     0,    56,    53,     0,    53,
       0,    53,     0,   224,   112,    27,   252,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   173,   188,
     205,   204,     0,     0,     0,   148,   195,   149,   150,     0,
     141,     0,     0,    58,     0,   239,    23,   243,    44,   136,
     116,     0,     0,    55,     0,    55,     0,    55,    39,   251,
       0,     0,     0,   177,     0,     0,     0,     0,     0,     0,
      34,   172,     0,   198,   197,     0,   152,     0,    40,     0,
     117,   233,     0,   231,     0,   232,     0,     0,     0,     0,
     180,   175,   174,   179,     0,     0,     0,     0,     0,     0,
     244,     0,     0,     0,     0,   185,     0,   178,     0,     0,
       0,     0,    35,     0,     0,   230,   228,   229,   207,   186,
       0,   190,   189,   181,     0,   183,   207,     0,     0,     0,
     206,   203,   176,     0,   184,   187,     0,     0,     0,   182,
      36,     0,    43,   153
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,   142,    10,    11,    42,    85,   143,
     144,   145,   357,   577,   146,   202,   277,   457,   278,    87,
      37,    38,   423,   290,    39,   347,   348,   270,   271,   147,
     212,   187,   198,   199,   203,   275,   276,   249,   250,   196,
     226,   477,   478,   558,   573,   365,   366,   424,   425,   179,
     245,   479,   482,   581,   180,   315,   316,   181,   184,   185,
     190,   406,   407,   408,   409,   264,   446,   447,   392,   393,
     158,   291,   292
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -463
static const yytype_int16 yypact[] =
{
      86,   349,  -463,  -463,  -463,    90,   103,    86,  -463,  -463,
    -463,   133,    82,  1187,   152,  -463,  -463,  -463,  -463,   112,
    -463,  -463,   120,  -463,  -463,  -463,    97,  -463,    21,    21,
      21,    21,  1313,   175,    21,  1313,  2408,  -463,  -463,    49,
    -463,    12,   138,  1313,  -463,  -463,  -463,  -463,  -463,  1613,
      21,    21,    21,  -463,  -463,  1372,   -68,  1313,  1313,  1313,
    1313,  1313,  1313,  1313,  1313,  1313,  1313,  1313,  -463,  1313,
    1313,  1313,  1313,  1313,  1313,  1313,  1313,  1313,  1313,  1313,
    1313,  1313,   250,  -463,  -463,    87,  2740,  2547,   159,  -463,
    -463,  -463,  -463,  1313,  1313,  -463,   462,   462,   579,   579,
     579,   579,   151,   151,   151,  2559,  1398,  2420,  2571,  2581,
    2591,   462,   462,   242,   242,  -463,  -463,  -463,   170,  1411,
    -463,  -463,   272,    10,   868,     8,   288,   205,   283,  2740,
     288,   226,   913,  -463,  -463,   325,    22,   258,    22,   267,
     283,   267,  -463,   292,  2740,  -463,  -463,   269,  -463,    63,
    2547,  1313,  -463,  1313,  -463,  -463,   255,   260,   266,   275,
     189,   366,   486,   286,   294,   300,   366,   306,   913,   543,
     311,   314,   321,   324,    23,     6,  1313,    93,  -463,   649,
     649,    28,    92,   280,    -2,  -463,  -463,    60,   424,  -463,
      13,   387,   122,  1313,   604,  -463,  -463,   330,   136,  -463,
     430,  -463,   335,   344,   267,   345,   335,   441,   335,  -463,
    -463,  -463,   267,   336,  2547,  1431,   921,  1313,  -463,  -463,
    -463,  1313,    31,  -463,    37,  -463,   687,  1313,  1313,  1313,
      52,     8,  -463,  -463,   445,   748,  1313,  1313,  1313,  1313,
     971,    92,  -463,  -463,  1313,  -463,    79,  1200,  -463,  -463,
    -463,  -463,   994,   994,  1313,  -463,     8,  -463,   446,   348,
    -463,   335,  1313,  -463,   448,  -463,  -463,  1627,   449,  1313,
    -463,   352,  -463,   325,   358,   353,  -463,   430,  -463,  -463,
     335,  -463,   325,   364,   460,   335,  -463,  -463,   461,   368,
     371,   196,  -463,   373,   374,  -463,    19,   377,  -463,  -463,
    1713,  1727,  1741,  -463,   381,   284,  -463,  1755,  1769,  1855,
    1869,  1313,  1313,   385,  2547,   -30,  -463,  1883,  -463,   391,
     279,    34,  2039,  1313,  1313,  2051,  1313,  1313,  2547,  -463,
    -463,  1313,  -463,  2438,   393,  1504,   128,  2450,  1313,  -463,
    1313,   430,   353,   490,   150,   327,   330,   154,  -463,   288,
     396,  -463,  -463,   386,   492,   400,   458,   399,   403,  1226,
    1226,  1226,  1313,  -463,  -463,   913,   351,   649,   913,   649,
     913,  2547,  2547,   649,  1027,  -463,  -463,  -463,   406,  1027,
    -463,  2138,  2150,  -463,  2162,  2174,  2186,  1313,   327,  2664,
    -463,  -463,  -463,   467,  -463,   913,  1313,  2462,  2547,  -463,
     412,  -463,    40,    96,    99,  -463,   649,   327,  -463,  -463,
    -463,  -463,   460,   155,  1249,  -463,   414,  -463,  -463,   416,
     390,   141,   435,    39,  1064,  -463,  1081,  1139,  2198,   807,
    -463,   475,  -463,  -463,  -463,  -463,  -463,  -463,  -463,  -463,
    -463,  -463,  1313,  1457,  -463,  -463,   405,  -463,   518,   481,
    2702,   852,  1573,  1313,  -463,   288,  -463,   267,   288,   267,
     288,   267,   477,  -463,  -463,  -463,  -463,  1897,  -463,   452,
     517,   526,   329,   528,   434,   436,   437,   264,  -463,  -463,
    -463,  -463,   537,   649,   649,  -463,  -463,  -463,  -463,  1313,
    -463,   649,  2285,  -463,   497,  -463,  2740,  -463,  -463,  -463,
    -463,  1593,   160,   335,   171,   335,   177,   335,  -463,  -463,
     539,  1274,   450,  -463,   547,   507,   455,  1313,  1313,    11,
    -463,  -463,   459,  -463,  -463,  2297,  -463,   556,  -463,   520,
    -463,  -463,   288,  -463,   288,  -463,   288,   463,  2309,  1313,
    -463,   522,  -463,  -463,  1911,  1997,   469,   473,     8,   470,
    -463,   185,   200,   222,   480,  -463,  2321,  -463,   390,   263,
     191,   482,  -463,   476,  1313,  -463,  -463,  -463,   576,  -463,
     761,  -463,  -463,   542,   263,  -463,   576,   390,  1313,  2011,
    -463,  -463,  -463,   263,  -463,  -463,   766,  2025,  2702,  -463,
    -463,   913,  -463,  -463
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -463,  -463,  -463,   577,    67,   578,  -463,  -463,  -463,  -125,
    -463,  -142,  -463,  -463,  -218,  -118,  -130,   -23,  -172,   -13,
     907,  -463,   -10,    -8,   -89,  -463,   174,   237,  -463,  -463,
    -463,  -129,   310,   328,   464,   326,   268,  -168,   -61,   487,
    -161,  -462,  -460,  -463,  -429,   276,  -463,    57,  -251,  -246,
    -463,   247,  -463,    38,   172,  -463,   239,  -122,  -463,   359,
     478,  -463,  -463,   209,  -354,  -463,  -463,   173,  -445,  -463,
     271,  -463,   273
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -34
static const yytype_int16 yytable[] =
{
      36,   192,   210,   183,   191,   498,   323,   326,   235,   242,
     515,    21,   251,   156,   546,    83,   243,   521,   263,    49,
     356,   206,    55,   208,    21,    56,    21,    22,    23,    24,
      25,    26,    94,    88,   445,   177,   182,    21,   374,   252,
     296,    95,   297,   177,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   521,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,     9,   119,   375,
     118,   195,   222,   177,    17,   260,   282,   230,   284,   177,
     177,   150,   510,   149,   200,   241,   280,   364,   261,   332,
     177,   177,   445,    14,   285,   255,   570,   201,   256,   572,
     572,   225,   455,    15,   244,   177,    44,   232,   225,   304,
     521,    84,   456,   157,   572,   586,   176,   262,   364,    32,
     -33,   240,     1,   572,   484,    20,   521,   405,   295,    35,
     253,   575,   379,   225,   183,    81,    19,   177,   214,    94,
     215,    82,   182,   592,     2,   584,   177,    80,   430,   303,
     343,     3,     4,    81,   589,   349,    81,   257,   458,    82,
     258,   460,    82,    94,     5,   299,   246,   182,   456,   394,
     444,   456,   213,   486,   299,   486,   486,   126,    21,    94,
     267,    22,    23,    24,    25,    26,   121,   122,   318,   405,
     135,   247,   136,   391,   470,    40,    81,    81,   138,   431,
     139,   433,    82,    82,   429,   435,   289,   289,   480,   293,
      41,   289,   481,   294,   300,   301,   302,   471,    43,   266,
     413,   472,   258,   307,   308,   309,   310,   314,   444,   473,
     574,   317,   241,   272,   451,    86,   273,   320,   462,   322,
     325,   328,    75,    76,    77,    78,    79,   401,   474,   333,
     273,   411,   465,   120,   412,   258,   337,   531,   148,    94,
     258,    50,    51,    52,   449,   539,   470,   470,   533,   152,
      94,   258,   475,    32,   535,   155,   177,   258,   177,   177,
     177,   177,   565,    35,   177,   258,   220,   221,   571,   471,
     471,   186,   476,   472,   472,   352,   353,   566,   371,   372,
     258,   473,   473,   188,   225,   520,   177,   432,   391,   434,
     381,   382,   189,   384,   385,   523,   524,   177,   386,   567,
     474,   474,   258,   526,   193,   397,   502,   398,   197,   504,
     204,   506,   470,   126,   225,    77,    78,    79,   209,   503,
     177,   505,   201,   507,   475,   475,   135,   363,   136,   428,
      12,   211,    13,   216,   138,   471,   139,   177,   217,   472,
     571,   314,   177,   218,   476,   476,   314,   473,   299,    21,
     513,   529,   219,   532,   443,   534,   126,   536,   378,    94,
     459,   461,   254,   452,   227,   494,   474,   402,   403,   135,
     299,   136,   228,   470,   177,   177,   404,   138,   229,   139,
     126,   467,   177,   551,   231,   552,   159,   553,    21,   236,
     475,   160,   237,   135,   514,   136,   471,   426,   427,   238,
     472,   138,   239,   139,   324,   327,   563,   259,   473,   492,
     476,   161,   265,   274,   269,   194,   163,   164,   165,   262,
     501,   279,   281,   166,   283,   286,   391,   474,   305,   330,
     331,   334,   336,   341,   126,   167,   338,   168,   169,   182,
     340,   345,   170,   346,   350,   402,   403,   135,    94,   136,
     351,   475,   354,   355,   404,   138,   525,   139,   358,   171,
      63,    64,    65,   362,   373,   172,   173,   159,   377,    21,
     388,   476,   160,   400,   414,   156,   288,   417,   538,   418,
     419,   421,   177,   437,   544,   545,   174,   450,   175,   454,
     470,   468,   161,   176,   469,   491,   194,   163,   164,   165,
     483,   496,   497,   510,   166,   508,   556,   223,   511,   512,
     593,   516,   517,   471,   518,   519,   167,   472,   168,   169,
     522,   528,   537,   170,   159,   473,    21,   540,   542,   160,
     541,   579,   543,    75,    76,    77,    78,    79,   547,   549,
     171,   550,   554,   557,   474,   587,   172,   173,   561,   161,
     562,   224,   564,   194,   163,   164,   165,   568,   578,   576,
     580,   166,   583,   410,    16,    18,   464,   174,   475,   175,
      57,    58,   344,   167,   176,   168,   169,    63,    64,    65,
     170,   339,   205,   342,   420,   159,   233,    21,   476,   399,
     160,   178,   395,   436,   585,   329,   463,   171,   207,   495,
       0,     0,     0,   172,   173,   416,   415,     0,   234,     0,
     161,     0,     0,     0,   194,   163,   164,   165,     0,     0,
       0,     0,   166,     0,   174,   223,   175,     0,     0,     0,
     159,   176,    21,     0,   167,   160,   168,   169,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,   161,     0,     0,   171,   194,
     163,   164,   165,     0,   172,   173,     0,   166,   159,   268,
      21,     0,     0,   160,     0,     0,     0,     0,     0,   167,
       0,   168,   169,     0,     0,   174,   170,   175,     0,     0,
       0,     0,   176,   161,     0,     0,     0,   194,   163,   164,
     165,     0,     0,   171,     0,   166,     0,     0,   298,   172,
     173,     0,     0,     0,     0,     0,     0,   167,     0,   168,
     169,     0,     0,     0,   170,     0,   248,     0,     0,   159,
     174,    21,   175,     0,   160,     0,     0,   176,     0,     0,
       0,   171,     0,     0,   470,     0,     0,   172,   173,   470,
       0,     0,     0,     0,   161,     0,     0,     0,   194,   163,
     164,   165,     0,     0,     0,     0,   166,   471,   174,     0,
     175,   472,   471,     0,     0,   176,   472,     0,   167,   473,
     168,   169,   582,     0,   473,   170,     0,   590,   159,     0,
      21,   306,     0,   160,     0,     0,     0,     0,   474,     0,
       0,     0,   171,   474,     0,     0,     0,     0,   172,   173,
       0,     0,     0,   161,     0,     0,     0,   194,   163,   164,
     165,     0,   475,     0,     0,   166,     0,   475,     0,   174,
       0,   175,     0,   159,     0,    21,   176,   167,   160,   168,
     169,     0,   476,     0,   170,     0,     0,   476,     0,   159,
     490,    21,     0,     0,   160,     0,     0,     0,   161,     0,
       0,   171,   194,   163,   164,   165,     0,   172,   173,     0,
     166,     0,     0,   499,   161,     0,     0,     0,   162,   163,
     164,   165,   167,     0,   168,   169,   166,     0,   174,   170,
     175,     0,     0,     0,   159,   176,    21,     0,   167,   160,
     168,   169,     0,     0,    21,   170,   171,    22,    23,    24,
      25,    26,   172,   173,     0,    45,    46,    47,    48,   161,
      53,    54,   171,   194,   163,   164,   165,     0,   172,   173,
       0,   166,     0,   174,     0,   175,     0,    90,    91,    92,
     176,     0,     0,   167,     0,   168,   169,     0,     0,   174,
     170,   175,     0,     0,    21,     0,   176,    22,    23,    24,
      25,    26,     0,     0,     0,     0,     0,   171,     0,     0,
       0,     0,     0,   172,   173,     0,     0,    21,     0,     0,
      22,    23,    24,    25,    26,     0,     0,    28,    29,    30,
       0,     0,     0,    31,   174,     0,   175,     0,     0,    32,
       0,   176,     0,     0,     0,     0,     0,    33,    34,    35,
      21,   288,     0,    22,    23,    24,    25,    26,   311,     0,
       0,     0,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,    31,   313,     0,     0,    21,     0,    32,
      22,    23,    24,    25,    26,     0,     0,    33,    34,    35,
      28,    29,    30,     0,    21,     0,    31,    22,    23,    24,
      25,    26,    32,     0,   311,   321,     0,   175,   312,   422,
      33,    34,    35,     0,     0,     0,   485,     0,     0,     0,
       0,     0,     0,    28,    29,    30,   422,     0,     0,    31,
       0,     0,     0,   487,     0,    32,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,     0,     0,     0,     0,
       0,     0,    21,     0,     0,    22,    23,    24,    25,    26,
      28,    29,    30,     0,     0,     0,    31,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,    28,    29,    30,
      33,    34,    35,    31,   422,     0,     0,     0,     0,    32,
       0,   488,     0,     0,     0,     0,     0,    33,    34,    35,
      21,     0,     0,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,    21,     0,     0,    22,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,     0,    21,
      27,    31,    22,    23,    24,    25,    26,    32,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,     0,     0,
       0,     0,    21,     0,     0,    22,    23,    24,    25,    26,
       0,   422,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,    30,     0,    21,     0,    31,
      22,    23,    24,    25,    26,    32,    28,    29,    30,     0,
       0,     0,    31,    33,    34,    35,     0,     0,    32,   319,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     0,
       0,     0,    28,    29,    30,     0,    21,     0,    31,    22,
      23,    24,    25,    26,    32,     0,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    28,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,    32,   466,     0,
       0,     0,     0,     0,     0,    33,    34,    35,     0,     0,
      28,    29,    30,     0,     0,     0,    31,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,   175,     0,     0,
      33,    34,    35,    57,    58,     0,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,    28,
      29,    30,     0,     0,     0,    31,     0,     0,     0,    57,
      58,    32,    59,    60,    61,    62,    63,    64,    65,    33,
      34,    35,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    69,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      93,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,     0,    69,   153,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,   123,     0,     0,
       0,     0,     0,     0,     0,    69,   154,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
       0,   124,   125,     0,   389,     0,   287,     0,     0,     0,
       1,    69,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,   126,   127,     0,     0,     0,   128,   129,
     130,   131,   493,   132,   133,   134,   135,     0,   136,     0,
       0,     0,     0,   137,   138,     0,   139,     0,     0,     0,
       0,   140,     5,     0,    57,    58,   141,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,   390,     0,     0,    57,    58,     0,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,     0,     0,     0,     0,    69,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,     0,     0,     0,     0,     0,     0,    69,   500,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,     0,     0,     0,     0,     0,     0,    69,   530,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    69,    89,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,    57,    58,   335,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    57,    58,     0,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      57,    58,     0,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,     0,    69,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    69,   359,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    69,   360,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,    69,
     361,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,    69,   367,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     0,    57,    58,   368,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      57,    58,     0,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     0,     0,    57,    58,     0,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,    69,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,    69,   369,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    69,   370,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    69,   376,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    69,   509,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,    57,    58,
     559,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    57,    58,     0,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      57,    58,     0,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,    69,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    69,   560,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,    69,
     588,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,    69,   591,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    69,   380,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,   383,    57,
      58,     0,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    57,    58,     0,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    57,    58,     0,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    57,    58,     0,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    57,    58,     0,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    57,
      58,     0,    59,    60,    61,    62,    63,    64,    65,    66,
      67,     0,    69,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    69,   438,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    69,   439,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    69,   440,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      69,   441,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    69,   442,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,     0,   489,    57,    58,     0,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      57,    58,     0,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    69,   527,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    69,   548,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    69,   555,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,   569,    57,
      58,     0,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    57,    58,     0,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     0,     0,     0,     0,     0,     0,    57,
      58,    68,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    57,    58,     0,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    57,    58,     0,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     0,     0,     0,     0,     0,
       0,     0,    69,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    69,   151,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,     0,    69,   387,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    69,   396,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    69,   453,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    57,    58,
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      57,    58,     0,    59,    60,    61,    62,    63,    64,    65,
       0,    67,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    77,    78,    79,   123,     0,    72,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
       0,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,     0,   126,   127,     0,     0,     0,   128,   129,
     130,   131,     0,   132,   133,   134,   135,     0,   136,   124,
     125,     0,   389,   137,   138,     0,   139,     0,     1,     0,
       0,   140,     5,   123,     0,     0,   141,     0,     0,   448,
       0,   126,   127,     0,     0,     0,   128,   129,   130,   131,
       0,   132,   133,   134,   135,     0,   136,   124,   125,     0,
       0,   137,   138,     0,   139,     0,     1,     0,     0,   140,
       5,     0,     0,     0,   141,     0,     0,     0,     0,   126,
     127,     0,     0,     0,   128,   129,   130,   131,     0,   132,
     133,   134,   135,     0,   136,     0,     0,     0,     0,   137,
     138,     0,   139,     0,     0,     0,     0,   140,     5,     0,
       0,     0,   141
};

static const yytype_int16 yycheck[] =
{
      13,   130,   144,   125,   129,   450,   252,   253,   169,     3,
     472,     3,   180,     3,     3,     3,    10,   477,   190,    32,
       1,   139,    35,   141,     3,    35,     3,     6,     7,     8,
       9,    10,   100,    43,   388,   124,   125,     3,    68,    11,
       3,   109,     5,   132,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,   515,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,    81,    99,
      80,   132,   161,   162,     7,    62,   206,   166,   208,   168,
     169,    94,    71,    93,    62,   174,   204,   305,    75,   261,
     179,   180,   446,     3,   212,    97,   558,    75,   100,   559,
     560,   162,    62,     0,    98,   194,     9,   168,   169,   231,
     570,    99,    72,   103,   574,   577,   108,   104,   336,    98,
     101,    98,    36,   583,    85,    43,   586,   345,    97,   108,
     102,   560,    98,   194,   256,   104,     3,   226,   151,   100,
     153,   110,   231,   588,    58,   574,   235,    98,   366,    97,
     280,    65,    66,   104,   583,   285,   104,    97,    62,   110,
     100,    62,   110,   100,    78,   226,   176,   256,    72,    41,
     388,    72,   109,   424,   235,   426,   427,    49,     3,   100,
     193,     6,     7,     8,     9,    10,    99,   100,   109,   407,
      62,    98,    64,   335,     3,    43,   104,   104,    70,   367,
      72,   369,   110,   110,   365,   373,   216,   217,    67,   217,
      98,   221,    71,   221,   227,   228,   229,    26,    98,    97,
     349,    30,   100,   236,   237,   238,   239,   240,   446,    38,
      39,   244,   321,    97,   395,    97,   100,   247,   406,   252,
     253,   254,    91,    92,    93,    94,    95,    97,    57,   262,
     100,    97,    97,     3,   100,   100,   269,    97,    99,   100,
     100,    86,    87,    88,   389,   511,     3,     3,    97,    99,
     100,   100,    81,    98,    97,     3,   365,   100,   367,   368,
     369,   370,    97,   108,   373,   100,    97,    98,    97,    26,
      26,     3,   101,    30,    30,    99,   100,    97,   311,   312,
     100,    38,    38,    98,   365,    41,   395,   368,   450,   370,
     323,   324,    29,   326,   327,   483,   484,   406,   331,    97,
      57,    57,   100,   491,    98,   338,   455,   340,     3,   458,
      72,   460,     3,    49,   395,    93,    94,    95,    46,   457,
     429,   459,    75,   461,    81,    81,    62,    63,    64,   362,
       1,    82,     3,    98,    70,    26,    72,   446,    98,    30,
      97,   374,   451,    97,   101,   101,   379,    38,   429,     3,
      41,   496,    97,   503,   387,   505,    49,   507,    99,   100,
     403,   404,   102,   396,    98,   446,    57,    60,    61,    62,
     451,    64,    98,     3,   483,   484,    69,    70,    98,    72,
      49,   414,   491,   532,    98,   534,     1,   536,     3,    98,
      81,     6,    98,    62,    85,    64,    26,   360,   361,    98,
      30,    70,    98,    72,   252,   253,   548,     3,    38,   442,
     101,    26,    45,     3,   104,    30,    31,    32,    33,   104,
     453,    97,    97,    38,     3,   109,   588,    57,     3,     3,
     102,     3,     3,   100,    49,    50,   104,    52,    53,   548,
     102,    97,    57,     3,     3,    60,    61,    62,   100,    64,
      99,    81,    99,    99,    69,    70,   489,    72,   101,    74,
      18,    19,    20,   102,    99,    80,    81,     1,    97,     3,
      97,   101,     6,     3,    98,     3,   110,    97,   511,    41,
     101,    98,   591,    97,   517,   518,   101,    40,   103,    97,
       3,    97,    26,   108,    98,    40,    30,    31,    32,    33,
      85,     3,    41,    71,    38,    48,   539,    41,    11,     3,
     591,     3,    98,    26,    98,    98,    50,    30,    52,    53,
       3,    44,     3,    57,     1,    38,     3,    97,    41,     6,
       3,   564,    97,    91,    92,    93,    94,    95,    99,     3,
      74,    41,    99,    41,    57,   578,    80,    81,    99,    26,
      97,    85,   102,    30,    31,    32,    33,    97,   102,    97,
       4,    38,    40,   346,     7,     7,   412,   101,    81,   103,
      11,    12,   282,    50,   108,    52,    53,    18,    19,    20,
      57,   273,   138,   277,   357,     1,    63,     3,   101,   341,
       6,   124,   336,   374,   576,   256,   407,    74,   140,   446,
      -1,    -1,    -1,    80,    81,   354,   353,    -1,    85,    -1,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    -1,   101,    41,   103,    -1,    -1,    -1,
       1,   108,     3,    -1,    50,     6,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    26,    -1,    -1,    74,    30,
      31,    32,    33,    -1,    80,    81,    -1,    38,     1,    85,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    52,    53,    -1,    -1,   101,    57,   103,    -1,    -1,
      -1,    -1,   108,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    74,    -1,    38,    -1,    -1,    41,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    52,
      53,    -1,    -1,    -1,    57,    -1,    97,    -1,    -1,     1,
     101,     3,   103,    -1,     6,    -1,    -1,   108,    -1,    -1,
      -1,    74,    -1,    -1,     3,    -1,    -1,    80,    81,     3,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    38,    26,   101,    -1,
     103,    30,    26,    -1,    -1,   108,    30,    -1,    50,    38,
      52,    53,    41,    -1,    38,    57,    -1,    41,     1,    -1,
       3,    63,    -1,     6,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    74,    57,    -1,    -1,    -1,    -1,    80,    81,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    81,    -1,    -1,    38,    -1,    81,    -1,   101,
      -1,   103,    -1,     1,    -1,     3,   108,    50,     6,    52,
      53,    -1,   101,    -1,    57,    -1,    -1,   101,    -1,     1,
      63,     3,    -1,    -1,     6,    -1,    -1,    -1,    26,    -1,
      -1,    74,    30,    31,    32,    33,    -1,    80,    81,    -1,
      38,    -1,    -1,    41,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    50,    -1,    52,    53,    38,    -1,   101,    57,
     103,    -1,    -1,    -1,     1,   108,     3,    -1,    50,     6,
      52,    53,    -1,    -1,     3,    57,    74,     6,     7,     8,
       9,    10,    80,    81,    -1,    28,    29,    30,    31,    26,
      33,    34,    74,    30,    31,    32,    33,    -1,    80,    81,
      -1,    38,    -1,   101,    -1,   103,    -1,    50,    51,    52,
     108,    -1,    -1,    50,    -1,    52,    53,    -1,    -1,   101,
      57,   103,    -1,    -1,     3,    -1,   108,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,     3,    -1,    -1,
       6,     7,     8,     9,    10,    -1,    -1,    86,    87,    88,
      -1,    -1,    -1,    92,   101,    -1,   103,    -1,    -1,    98,
      -1,   108,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
       3,   110,    -1,     6,     7,     8,     9,    10,    67,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      -1,    -1,    -1,    92,    93,    -1,    -1,     3,    -1,    98,
       6,     7,     8,     9,    10,    -1,    -1,   106,   107,   108,
      86,    87,    88,    -1,     3,    -1,    92,     6,     7,     8,
       9,    10,    98,    -1,    67,   101,    -1,   103,    71,    35,
     106,   107,   108,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    35,    -1,    -1,    92,
      -1,    -1,    -1,    42,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,     6,     7,     8,     9,    10,
      86,    87,    88,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    86,    87,    88,
     106,   107,   108,    92,    35,    -1,    -1,    -1,    -1,    98,
      -1,    42,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
       3,    -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    -1,     3,
      43,    92,     6,     7,     8,     9,    10,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,    -1,    -1,
      -1,    -1,     3,    -1,    -1,     6,     7,     8,     9,    10,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    -1,     3,    -1,    92,
       6,     7,     8,     9,    10,    98,    86,    87,    88,    -1,
      -1,    -1,    92,   106,   107,   108,    -1,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,    -1,
      -1,    -1,    86,    87,    88,    -1,     3,    -1,    92,     6,
       7,     8,     9,    10,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,    86,    87,    88,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,    -1,    -1,
      86,    87,    88,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,    -1,    -1,
     106,   107,   108,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    86,
      87,    88,    -1,    -1,    -1,    92,    -1,    -1,    -1,    11,
      12,    98,    14,    15,    16,    17,    18,    19,    20,   106,
     107,   108,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    84,    -1,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
     108,    -1,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,   105,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      -1,    27,    28,    -1,    30,    -1,   105,    -1,    -1,    -1,
      36,    84,    -1,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,   105,    59,    60,    61,    62,    -1,    64,    -1,
      -1,    -1,    -1,    69,    70,    -1,    72,    -1,    -1,    -1,
      -1,    77,    78,    -1,    11,    12,    82,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    97,    -1,    -1,    11,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,   105,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,   105,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    84,    99,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    11,    12,    99,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    11,    12,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    84,    -1,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    84,    99,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    -1,    84,    99,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    84,
      99,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    84,    99,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    -1,    11,    12,    99,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    11,    12,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    84,    99,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    -1,    -1,    84,    99,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    84,    99,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    -1,    84,    99,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    11,    12,
      99,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    11,    12,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    -1,    84,    99,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    84,
      99,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    84,    99,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    84,    97,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    97,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    11,    12,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    84,    -1,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    84,    97,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    84,    97,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    84,    97,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      84,    97,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    84,    97,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    97,    11,    12,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    84,    97,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    84,    97,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    84,    97,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    97,    11,
      12,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      12,    43,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      -1,    22,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    -1,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    -1,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     3,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    27,
      28,    -1,    30,    69,    70,    -1,    72,    -1,    36,    -1,
      -1,    77,    78,     3,    -1,    -1,    82,    -1,    -1,    85,
      -1,    49,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    -1,    64,    27,    28,    -1,
      -1,    69,    70,    -1,    72,    -1,    36,    -1,    -1,    77,
      78,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    -1,    -1,    -1,    -1,    69,
      70,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,    -1,
      -1,    -1,    82
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    58,    65,    66,    78,   112,   113,   114,   115,
     116,   117,     1,     3,     3,     0,   114,   115,   116,     3,
      43,     3,     6,     7,     8,     9,    10,    43,    86,    87,
      88,    92,    98,   106,   107,   108,   130,   131,   132,   135,
      43,    98,   118,    98,     9,   131,   131,   131,   131,   130,
      86,    87,    88,   131,   131,   130,   133,    11,    12,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    43,    84,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      98,   104,   110,     3,    99,   119,    97,   130,   133,    99,
     131,   131,   131,   108,   100,   109,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   133,   130,
       3,    99,   100,     3,    27,    28,    49,    50,    54,    55,
      56,    57,    59,    60,    61,    62,    64,    69,    70,    72,
      77,    82,   115,   120,   121,   122,   125,   140,    99,   133,
     130,    85,    99,    85,   105,     3,     3,   103,   181,     1,
       6,    26,    30,    31,    32,    33,    38,    50,    52,    53,
      57,    74,    80,    81,   101,   103,   108,   135,   150,   160,
     165,   168,   135,   168,   169,   170,     3,   142,    98,    29,
     171,   120,   142,    98,    30,   149,   150,     3,   143,   144,
      62,    75,   126,   145,    72,   145,   126,   171,   126,    46,
     122,    82,   141,   109,   130,   130,    98,    98,    97,    97,
      97,    98,   135,    41,    85,   149,   151,    98,    98,    98,
     135,    98,   149,    63,    85,   151,    98,    98,    98,    98,
      98,   135,     3,    10,    98,   161,   133,    98,    97,   148,
     149,   148,    11,   102,   102,    97,   100,    97,   100,     3,
      62,    75,   104,   129,   176,    45,    97,   130,    85,   104,
     138,   139,    97,   100,     3,   146,   147,   127,   129,    97,
     126,    97,   127,     3,   127,   126,   109,   105,   110,   133,
     134,   182,   183,   134,   134,    97,     3,     5,    41,   149,
     130,   130,   130,    97,   168,     3,    63,   130,   130,   130,
     130,    67,    71,    93,   130,   166,   167,   130,   109,    99,
     133,   101,   130,   160,   165,   130,   160,   165,   130,   170,
       3,   102,   129,   130,     3,    99,     3,   130,   104,   144,
     102,   100,   146,   127,   143,    97,     3,   136,   137,   127,
       3,    99,    99,   100,    99,    99,     1,   123,   101,    99,
      99,    99,   102,    63,   125,   156,   157,    99,    99,    99,
      99,   130,   130,    99,    68,    99,    99,    97,    99,    98,
      97,   130,   130,    97,   130,   130,   130,    85,    97,    30,
      97,   122,   179,   180,    41,   156,    85,   130,   130,   147,
       3,    97,    60,    61,    69,   125,   172,   173,   174,   175,
     138,    97,   100,   142,    98,   183,   181,    97,    41,   101,
     162,    98,    35,   133,   158,   159,   158,   158,   130,   151,
     125,   148,   149,   148,   149,   148,   167,    97,    97,    97,
      97,    97,    97,   130,   125,   175,   177,   178,    85,   120,
      40,   151,   130,    85,    97,    62,    72,   128,    62,   128,
      62,   128,   148,   174,   137,    97,    99,   130,    97,    98,
       3,    26,    30,    38,    57,    81,   101,   152,   153,   162,
      67,    71,   163,    85,    85,    42,   159,    42,    42,    97,
      63,    40,   130,   105,   149,   178,     3,    41,   179,    41,
     105,   130,   142,   126,   142,   126,   142,   126,    48,    99,
      71,    11,     3,    41,    85,   152,     3,    98,    98,    98,
      41,   153,     3,   148,   148,   130,   148,    97,    44,   120,
     105,    97,   127,    97,   127,    97,   127,     3,   130,   160,
      97,     3,    41,    97,   130,   130,     3,    99,    97,     3,
      41,   142,   142,   142,    99,    97,   130,    41,   154,    99,
      99,    99,    97,   168,   102,    97,    97,    97,    97,    97,
     152,    97,   153,   155,    39,   155,    97,   124,   102,   130,
       4,   164,    41,    40,   155,   164,   152,   130,    99,   155,
      41,    99,   179,   149
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 91 "verilog.y"
    {
				int prop =(yyvsp[(1) - (1)].emt)->get_prop();
				prop |=ELEMENT_FIRST_CHILD;
				(yyvsp[(1) - (1)].emt)->set_prop(prop);
				my_parse->output((yyvsp[(1) - (1)].emt));
			;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 99 "verilog.y"
    {(yyval.emt) = (yyvsp[(1) - (1)].emt);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 100 "verilog.y"
    {(yyval.emt) = (yyvsp[(1) - (1)].emt);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 101 "verilog.y"
    {(yyval.emt) = (yyvsp[(1) - (1)].emt);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 102 "verilog.y"
    { 
        		my_parse->append((yyvsp[(1) - (2)].emt), (yyvsp[(2) - (2)].emt));
        		(yyval.emt) = (yyvsp[(1) - (2)].emt);
        	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 106 "verilog.y"
    {
        		my_parse->append((yyvsp[(1) - (2)].emt), (yyvsp[(2) - (2)].emt));
        		(yyval.emt) = (yyvsp[(1) - (2)].emt);
        	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 110 "verilog.y"
    {
        		my_parse->append((yyvsp[(1) - (2)].emt), (yyvsp[(2) - (2)].emt));
        		(yyval.emt) = (yyvsp[(1) - (2)].emt);
        	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 117 "verilog.y"
    {
				(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
			;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 121 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 124 "verilog.y"
    { 
        		my_parse->add_define((yyvsp[(2) - (4)].emt)->get_text().c_str()); 
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
            ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 128 "verilog.y"
    { 
        		my_parse->add_define((yyvsp[(2) - (3)].emt)->get_text().c_str());
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 132 "verilog.y"
    { 
        		my_parse->del_define((yyvsp[(2) - (3)].emt)->get_text().c_str()); 
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 138 "verilog.y"
    {
				(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_MODULE, 0);				
				my_parse->born((yyval.emt), (yyvsp[(2) - (6)].emt));
				my_parse->born((yyval.emt), (yyvsp[(3) - (6)].emt));
				my_parse->born((yyval.emt), (yyvsp[(5) - (6)].emt));
			;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 148 "verilog.y"
    {printf("don't support macromodule at line %d", (yyloc).first_line); exit(1);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 151 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 154 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 157 "verilog.y"
    {(yyval.emt) = NULL;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 166 "verilog.y"
    {(yyval.emt) = (yyvsp[(1) - (1)].emt);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 167 "verilog.y"
    {(yyval.emt) = NULL;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 171 "verilog.y"
    {
        		my_parse->append((yyvsp[(1) - (2)].emt), (yyvsp[(2) - (2)].emt));
        		(yyval.emt) = (yyvsp[(1) - (2)].emt);
        	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 175 "verilog.y"
    {(yyval.emt) = (yyvsp[(1) - (1)].emt);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 179 "verilog.y"
    {
        		int prop;
        		Element * b, *e;
        		
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = (yyvsp[(2) - (5)].value) | (yyvsp[(3) - (5)].value);        		
        		b = (yyvsp[(4) - (5)].emt);
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born((yyval.emt), b);
        	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 194 "verilog.y"
    {
        		Element * b, *e;
        		Variable * vb, *v;
        		int prop;
        		
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = (yyvsp[(1) - (6)].value) | (yyvsp[(3) - (6)].value) | (yyvsp[(4) - (6)].value);        		
        		b = (yyvsp[(5) - (6)].emt);        		
        		LOOP_LEVEL(b, e) {
        			v = my_parse->variable_new(e, prop);
        			if (b==e)
        				vb = v;
        			else
        				my_parse->append(vb, v);
        		}
        		my_parse->born((yyval.emt), vb);
        	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 211 "verilog.y"
    {
        		int prop;
        		Variable * v;
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | VAR_OUTPUT | (yyvsp[(3) - (6)].value) | (yyvsp[(4) - (6)].value);
        		v = my_parse->variable_new((yyvsp[(5) - (6)].emt), prop);
        		my_parse->born((yyval.emt), v);
        	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 219 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 220 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 221 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 224 "verilog.y"
    {
        		printf("translate block must start with @");
        		exit(1);
        	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 228 "verilog.y"
    {        		
        		current_block = my_parse->ablock_new(0, 0, 0, (yyvsp[(4) - (4)].emt)->get_text(), 0); 
        		current_top_name_block = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born(current_top_name_block, (yyvsp[(4) - (4)].emt));
          	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 233 "verilog.y"
    {
        		current_block->set_pos((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.emt) =current_block;
        		current_top_name_block->set_pos((yylsp[(2) - (8)]).begin_pos, (yyloc).end_pos, (yylsp[(2) - (8)]).first_line);        		
        		my_parse->append((yyvsp[(6) - (8)].state), (yyvsp[(7) - (8)].smt));
        		my_parse->born(current_top_name_block, (yyvsp[(6) - (8)].state));
        		my_parse->born((yyval.emt), current_top_name_block);        		
        	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 241 "verilog.y"
    {        		
        		current_block = my_parse->ablock_new(0, 0, 0, (yyvsp[(4) - (10)].emt)->get_text(), (yyvsp[(7) - (10)].value));
        		current_block->put_clk((yyvsp[(8) - (10)].emt)->get_text());
        		current_top_name_block = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born(current_top_name_block, (yyvsp[(4) - (10)].emt));
        	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 247 "verilog.y"
    {
          		current_block->set_pos((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.emt) =current_block;
        		current_top_name_block->set_pos((yylsp[(2) - (13)]).begin_pos, (yyloc).end_pos, (yylsp[(2) - (13)]).first_line);
        		my_parse->born(current_top_name_block, (yyvsp[(12) - (13)].smt));
        		my_parse->born((yyval.emt), current_top_name_block);        		
        	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 254 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 257 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 260 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 263 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 266 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 269 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 272 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 275 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 279 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 282 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);        		
        	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 288 "verilog.y"
    {
        		int prop;
        		Element * b, *e;
        		
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | (yyvsp[(2) - (5)].value) | (yyvsp[(3) - (5)].value);        		
        		b = (yyvsp[(4) - (5)].emt);
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born((yyval.emt), b);
        	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 303 "verilog.y"
    {
        		int prop;
        		Element * b, *e;
        		
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | VAR_RANGE | VAR_SIGNED;        		
        		b = e = (yyvsp[(2) - (3)].emt);
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born((yyval.emt), b);
        	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 318 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 321 "verilog.y"
    {
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
            ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 324 "verilog.y"
    {
        		Element * b, *e;
        		Variable * vb, *v;
        		int prop;
        		
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_EVENT;        		
        		b = (yyvsp[(2) - (3)].emt);        		
        		LOOP_LEVEL(b, e) {
        			v = my_parse->variable_new(e, prop);
        			if (b==e)
        				vb = v;
        			else
        				my_parse->append(vb, v);
        		}
        		my_parse->born((yyval.emt), vb);
        	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 345 "verilog.y"
    {(yyval.value) =VAR_SIGNED;;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 346 "verilog.y"
    {(yyval.value) =0;;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 350 "verilog.y"
    {(yyval.value) =VAR_RANGE;;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 351 "verilog.y"
    {(yyval.value) =0;;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 355 "verilog.y"
    {(yyval.value) =VAR_REG;;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 356 "verilog.y"
    {(yyval.value) =0;;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 364 "verilog.y"
    {(yyval.exp) =(yyvsp[(1) - (1)].exp);}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 365 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 369 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 373 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 377 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::NOT);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 381 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 385 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (2)].exp));
        	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 389 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 393 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 397 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 401 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 406 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 411 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 416 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 421 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 426 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 431 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 436 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 441 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::LESS);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 446 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::BIG);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 451 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 456 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 461 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 466 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::EQU);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 471 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 476 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::LESSEQU);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 481 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::BIGEQU);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 486 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::NEQ);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 491 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 496 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 501 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 506 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (5)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (5)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(5) - (5)].exp));
        	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 515 "verilog.y"
    {
        		(yyval.exp)=my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::NUMBER);
        	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 518 "verilog.y"
    {
        		(yyval.exp)=my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::NUMBER);
        	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 521 "verilog.y"
    {(yyval.exp)=NULL;;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 522 "verilog.y"
    {
        		string vname =my_parse->get_text((yyloc).begin_pos, (yyloc).end_pos);
        		Variable *v =my_parse->variable_lookup(vname);
        		if (vname.find('.', 0) == string::npos && v!=NULL) { //not found '.'
        			(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::VAR);
        			(yyval.exp)->insert_var(v);
        		} else { //found '.'
        			(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Expression::VAR); //not support hierarchy variable
        		}
        	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 533 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (3)].exp));
        	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 537 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);        		
        		(yyval.exp)->merge_expression((yyvsp[(4) - (6)].exp));
        	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 541 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(2) - (3)].exp));
        	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 546 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(3) - (4)].exp));
        	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 550 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(3) - (4)].exp));
        	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 562 "verilog.y"
    {
        		(yyval.exp) = my_parse->expression_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		(yyval.exp)->merge_expression((yyvsp[(1) - (3)].exp));
        		(yyval.exp)->merge_expression((yyvsp[(3) - (3)].exp));
        	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 567 "verilog.y"
    {(yyval.exp)=(yyvsp[(1) - (1)].exp);;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 571 "verilog.y"
    {(yyval.exp)=(yyvsp[(1) - (1)].exp);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 572 "verilog.y"
    {(yyval.exp)=NULL;;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 585 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 586 "verilog.y"
    {
        		(yyval.emt) =(yyvsp[(1) - (3)].emt);
        		my_parse->append((yyval.emt), (yyvsp[(3) - (3)].emt));
        	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 593 "verilog.y"
    {
        		Variable *v;
        		int range;
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		range = (yyvsp[(2) - (2)].value);
        		v  = my_parse->variable_new((yyvsp[(1) - (2)].emt), range);
				my_parse->born((yyval.emt), v);
			;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 604 "verilog.y"
    {(yyval.value)=0;;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 605 "verilog.y"
    {(yyval.value)=VAR_RANGE;;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 614 "verilog.y"
    {(yyval.value)=VAR_INPUT;;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 615 "verilog.y"
    {(yyval.value)=VAR_OUTPUT;;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 616 "verilog.y"
    {(yyval.value)=VAR_INPUT | VAR_OUTPUT;;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 625 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 626 "verilog.y"
    {
        		(yyval.emt) = (yyvsp[(1) - (3)].emt);
        		my_parse->append((yyval.emt), (yyvsp[(3) - (3)].emt));
        	;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 633 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 634 "verilog.y"
    {
        		(yyval.emt) = (yyvsp[(1) - (3)].emt);
        		my_parse->append((yyval.emt), (yyvsp[(3) - (3)].emt));
        	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 641 "verilog.y"
    {
        		Variable *v;
        		int range;
        		(yyval.emt) = my_parse->element_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Element::ELEMENT_NORMAL, 0);
        		range = (yyvsp[(2) - (2)].value);
        		v  = my_parse->variable_new((yyvsp[(1) - (2)].emt), range | VAR_REG);
				my_parse->born((yyval.emt), v);
			;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 721 "verilog.y"
    { my_parse->append((yyvsp[(1) - (2)].smt),(yyvsp[(2) - (2)].smt)); (yyval.smt)=(yyvsp[(1) - (2)].smt);;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 722 "verilog.y"
    {(yyval.smt)=(yyvsp[(1) - (1)].smt); ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 726 "verilog.y"
    {
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::BEGINEND);
        		my_parse->born((yyval.smt), (yyvsp[(2) - (3)].smt));        		
        	;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 730 "verilog.y"
    {
        		(yyval.smt) = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born((yyval.smt), (yyvsp[(3) - (3)].emt));
        	;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 733 "verilog.y"
    {
        		(yyval.smt) = (yyvsp[(4) - (6)].smt);
        		(yyval.smt)->set_pos((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
        		my_parse->born((yyval.smt), (yyvsp[(5) - (6)].smt));
        	;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 738 "verilog.y"
    { (yyval.smt) = NULL; ;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 739 "verilog.y"
    { (yyval.smt) = NULL; ;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 740 "verilog.y"
    {
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::DISABLE);
        		my_parse->born((yyval.smt), (yyvsp[(2) - (3)].emt));
        	;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 744 "verilog.y"
    {
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::TRIGGURE_EVENT);
        		my_parse->born((yyval.smt), (yyvsp[(2) - (3)].emt));
        	;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 748 "verilog.y"
    {
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::IF);
        		my_parse->born((yyval.smt), (yyvsp[(3) - (5)].exp));
        		my_parse->born((yyval.smt), (yyvsp[(5) - (5)].smt));        		
        	;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 753 "verilog.y"
    {
    			(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::IFELSE);
    			my_parse->born((yyval.smt), (yyvsp[(3) - (7)].exp));
    			my_parse->born((yyval.smt), (yyvsp[(5) - (7)].smt));
    			my_parse->born((yyval.smt), (yyvsp[(7) - (7)].smt));
        	;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 759 "verilog.y"
    {        		
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::WHILE);
        		my_parse->born((yyval.smt), (yyvsp[(3) - (5)].exp));
        		my_parse->born((yyval.smt), (yyvsp[(5) - (5)].smt));
        	;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 764 "verilog.y"
    {        		
        		(yyval.smt) = my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::DOWHILE);
        		my_parse->born((yyval.smt), (yyvsp[(3) - (6)].exp));
        		my_parse->born((yyval.smt), (yyvsp[(6) - (6)].smt));
        	;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 769 "verilog.y"
    {
        		(yyval.smt) = my_parse->assign_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
	        	my_parse->born((yyval.smt), (yyvsp[(1) - (4)].emt));
	        	my_parse->born((yyval.smt), (yyvsp[(3) - (4)].exp));	        	
        	;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 774 "verilog.y"
    {
        		(yyval.smt) = my_parse->assign_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line);
	        	my_parse->born((yyval.smt), (yyvsp[(1) - (5)].emt));
	        	my_parse->born((yyval.smt), (yyvsp[(4) - (5)].exp));	        	
        	;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 779 "verilog.y"
    {
				(yyval.smt) =my_parse->statement_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, Statement::WAIT_EVENT);	        		
				State * st;
				if ((yyvsp[(6) - (6)].emt)==NULL)
					st = my_parse->state_new(0, 0, 0, "");
				else
					st = my_parse->state_new(0, 0, 0, (yyvsp[(6) - (6)].emt)->get_text());
									
				my_parse->born((yyval.smt), (yyvsp[(3) - (6)].emt));
				my_parse->born((yyval.smt), st);				
			;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 790 "verilog.y"
    {(yyval.smt) =(yyvsp[(1) - (1)].state);;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 794 "verilog.y"
    {(yyval.smt)=(yyvsp[(1) - (1)].smt);;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 795 "verilog.y"
    {(yyval.smt)=NULL;;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 799 "verilog.y"
    {(yyval.emt)=(yyvsp[(1) - (1)].emt);;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 800 "verilog.y"
    {(yyval.emt)=NULL;;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 829 "verilog.y"
    {									
        		if ((yyvsp[(7) - (7)].emt)==NULL)
        			(yyval.state) = my_parse->state_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, "");
        		else
        			(yyval.state) = my_parse->state_new((yyloc).begin_pos, (yyloc).end_pos, (yyloc).first_line, (yyvsp[(7) - (7)].emt)->get_text());	
        		my_parse->born((yyval.state), (yyvsp[(4) - (7)].emt));	        		
			;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 839 "verilog.y"
    { (yyval.value) =0; ;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 840 "verilog.y"
    { (yyval.value) =1; ;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 843 "verilog.y"
    { (yyval.emt) =(yyvsp[(1) - (1)].emt);;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 844 "verilog.y"
    {(yyval.emt) =NULL; ;}
    break;



/* Line 1455 of yacc.c  */
#line 3844 "verilog.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 948 "verilog.y"


void yyerror(char *s) {
    fprintf(stderr, "%d.%d-%d.%d %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, s);
}



