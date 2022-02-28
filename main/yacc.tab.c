/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

#include <stdio.h>
#include <stdbool.h>
#include "../aux/symbol_tabler.h"
#include "../aux/stacker.h"

void yyerror(const char*, ...);
int yylex();
void interpret(Node* root);

//tell the interpreter to enter a new scope
void enterScope();
//tell te interpreter to exit the current scope
void exitScope();
//tell the interpreter to enter a new block
void enterBlock();
//tell the interpreter to exit the current block
void exitBlock();
//tell the interpreter to enter a declaration
void enterDeclaration();
//tell the interpreter to enter a function call
void enterCall();
//tell the interpreter to exit the current function call
void exitCall();

//returns a pointer to an element of an array
void* getPointerToArrayElement(Node* root, int print_errors);

//prints from prinqueue variable
void fprintQueue();
//add to the printqueue variable
void addPrintQueue(const char* format, ...);


//this is the stack for the stack machiene
CallStack* callStack;
//this is the symbol table
CallStackUnit* symbolTable;
//true if we are inside a function, else false
bool callingFunction=false;
//true if return exists, else false
int returnExists=0;
//true if the program is running, else false
bool running=false;
//true if an error occured, else false
bool errorOccured=false;
//true if we consider declaration errors
bool printDeclarationErrors=true;
//stuff that will be printed is stored here
char* printQueue;
//true if in global scope
bool inGlobalScope = false;
//true if assigning
bool assigning = false;
//node that will be returned
Node* returnNodePointer=NULL;
//node that stores global declarations
NodeDeclarationBlock globalDeclarations;
//node that stores declarations in the current scope
NodeDeclarationBlock* currentDeclarations;
//node that stores the current function call
NodeBlock currentFunctionCall;
//the stack with nodes
Stack stack;
//the stack with array size
Stack currentArraySize;

extern int line_number;

FILE* sym_file;
extern FILE* yyin;


#line 144 "yacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BLOB = 258,
    MAIN = 259,
    CONST = 260,
    INT = 261,
    FLOAT = 262,
    CHAR = 263,
    STRING = 264,
    BOOL = 265,
    VOID = 266,
    IF = 267,
    THEN = 268,
    ELSE = 269,
    ELIF = 270,
    WHILE = 271,
    FUNCDEF = 272,
    EVAL = 273,
    PRINT = 274,
    RETURN = 275,
    LESSEQUAL = 276,
    GREATEREQUAL = 277,
    NOTEQUAL = 278,
    EQUAL = 279,
    ANDL = 280,
    ORL = 281,
    VARDEF = 282,
    LIST = 283,
    FUNCALL = 284,
    CONSTANT_INT = 285,
    VAR = 286,
    CONSTANT_STRING = 287,
    CONSTANT_CHAR = 288,
    CONSTANT_FLOAT = 289,
    CONSTANT_BOOL = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 76 "yacc.y"

    int intValue;
    char* stringValue;
    float floatValue;
    int boolValue;
    char charValue;
    int typeValue;
    struct Node* node;

#line 242 "yacc.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

#define YYUNDEFTOK  2
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    42,     2,     2,
      47,    48,    40,    39,    44,    38,    52,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      37,    45,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   124,   125,   126,   127,   131,   132,   136,
     140,   144,   149,   154,   158,   163,   171,   172,   173,   174,
     175,   176,   180,   181,   185,   211,   241,   245,   253,   257,
     264,   265,   266,   267,   271,   276,   280,   284,   288,   292,
     296,   297,   302,   305,   306,   307,   308,   309,   310,   314,
     323,   331,   340,   347,   357,   360,   366,   377,   391,   395,
     396,   400,   406,   412,   418,   424,   430,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   447,   448,
     449,   450,   451,   452,   453,   454,   458,   459,   460,   464,
     465,   466,   470,   471,   475,   478,   493
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BLOB", "MAIN", "CONST", "INT", "FLOAT",
  "CHAR", "STRING", "BOOL", "VOID", "IF", "THEN", "ELSE", "ELIF", "WHILE",
  "FUNCDEF", "EVAL", "PRINT", "RETURN", "LESSEQUAL", "GREATEREQUAL",
  "NOTEQUAL", "EQUAL", "ANDL", "ORL", "VARDEF", "LIST", "FUNCALL",
  "CONSTANT_INT", "VAR", "CONSTANT_STRING", "CONSTANT_CHAR",
  "CONSTANT_FLOAT", "CONSTANT_BOOL", "'>'", "'<'", "'-'", "'+'", "'*'",
  "'/'", "'%'", "';'", "','", "'='", "']'", "'('", "')'", "'{'", "'}'",
  "'['", "'.'", "$accept", "app", "globalDeclarations", "declaration",
  "var_declaration", "variable_list", "type_name", "type", "function",
  "funcdef", "parameters", "function_parameters", "blob_declarations",
  "blob", "block", "lbrace", "rbrace", "compound_statement", "statement",
  "variable", "array_access", "lsquare", "array_size", "array_size_access",
  "function_call", "funcall", "actual_parameters", "expression",
  "condition", "if", "elif", "while", "print", "return", "eval", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    62,    60,    45,    43,
      42,    47,    37,    59,    44,    61,    93,    40,    41,   123,
     125,    91,    46
};
# endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -92,    32,    16,   -92,   -15,   -28,   -92,   -92,   -92,   308,
     -92,   326,   -92,    12,   -92,   -92,   -92,   332,   -92,   -92,
     -92,   -92,   -92,   -92,    24,   332,   -92,    51,    21,    75,
      24,    55,    47,    -7,   -92,    79,   -92,   -92,    -4,    99,
     108,   109,   127,    -5,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,    -5,   -92,   -92,   -92,   -92,    38,   114,   -92,    93,
     205,   -92,   -92,   -92,   132,   141,   143,    53,   136,    -5,
     -92,    49,     1,   -28,   159,   -92,   -92,    -5,    -5,    -5,
      -5,    77,   -92,   259,   112,    -5,   -92,    87,   138,    -5,
     156,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,   -92,   -92,   -92,   -92,   -92,   153,
     259,   180,   167,   -28,   183,     9,   -92,   -92,   259,   175,
     176,   196,   140,   -92,   228,   -92,   -92,   171,   181,   193,
     259,   236,   110,   306,   306,   306,   306,   288,   266,   306,
     306,    71,    71,   -92,   -92,   -92,   -92,    35,   136,    -5,
     -92,   -92,   326,   -92,   242,     2,    -5,   -92,   -92,   166,
     -92,   -92,   -92,    10,   259,   226,   -92,   153,   259,   232,
     -28,   -28,   -92,   168,   248,   259,    -5,   -92,   -92,    73,
     -92,    86,   -92,   -92,   259,   -92,   -28,   239,   -92,   -92,
      -5,   245,   281,   -28,   117,   -28,   -92,   -92
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,     0,     0,    26,     9,     3,     0,
       4,     0,     5,     0,    36,     2,    39,     0,    16,    17,
      18,    19,    20,    21,     0,     0,    23,     0,     0,     0,
       0,     0,    11,     0,    22,     0,    32,    33,     0,     0,
       0,     0,     0,     0,    58,    61,    49,    65,    62,    64,
      63,     0,    37,    47,    35,    38,    66,    77,    76,     0,
       0,    74,    43,    44,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,    30,    31,     0,     0,     0,
       0,    66,    77,    95,     0,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,    45,    48,    46,     7,     0,
      13,     0,    10,     0,     0,     0,    24,    34,     0,    74,
      74,     0,     0,    75,     0,    67,    68,    61,     0,     0,
      55,     0,     0,    80,    81,    82,    83,    84,    85,    79,
      78,    70,    69,    71,    72,    73,    53,     0,     0,     0,
      25,    29,     0,    27,     0,     0,     0,    94,    41,     0,
      50,    42,    57,     0,    60,     0,    15,     0,    12,     0,
       0,     0,    93,     0,    61,    54,     0,    56,    52,     0,
      28,    86,    92,    96,    59,    14,     0,     0,    88,    87,
       0,    74,     0,     0,    89,     0,    91,    90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   -92,     6,   -92,   290,    22,   -68,    50,   -92,
     -92,   -92,   -92,   -92,   -72,   -92,   -92,   -92,   -92,   -12,
     292,   -63,   -91,   -92,   235,   -92,   -92,   -29,   -75,   -92,
     129,   -92,   -92,   -92,   -92
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    33,    26,    27,    10,    11,
      73,   115,    38,    12,    15,    16,    54,    29,    55,    81,
      82,    88,   128,   129,    58,    59,   163,   118,    61,    62,
     188,    63,    64,    65,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,   116,   119,   120,   114,   109,    25,    18,    19,    20,
      21,    22,    23,     6,    83,   171,    13,    56,   147,     4,
       5,    14,    84,     7,    44,    45,    46,    47,    48,    49,
      50,    24,     3,     6,    36,    53,    70,    71,     6,    30,
     110,   150,    51,     7,    75,   172,    74,    34,     7,   113,
     121,   122,    31,   152,   176,    32,   124,   153,   177,   130,
     131,    28,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   125,   179,   111,    37,   165,
     112,   166,    35,    85,   169,   167,    68,    39,    76,    86,
      87,    40,    69,    41,    42,    43,   108,    71,   181,   182,
     186,   187,     7,   164,    44,    45,    46,    47,    48,    49,
      50,   101,   102,   103,   189,   191,    44,   165,    46,   185,
     168,   194,    51,   197,    90,    52,    72,   173,    86,    87,
     175,   195,   187,    91,    92,    93,    94,    95,    96,    44,
      45,    46,    47,    48,    49,    50,    77,   184,    97,    98,
      99,   100,   101,   102,   103,    78,    79,    51,   162,    89,
     123,    91,    92,    93,    94,    95,    96,    44,   127,    46,
      47,    48,    49,    50,    80,   105,    97,    98,    99,   100,
     101,   102,   103,   146,   106,    51,   107,    86,   157,    91,
      92,    93,    94,    95,    96,    44,   174,    46,    47,    48,
      49,    50,   117,   132,    97,    98,    99,   100,   101,   102,
     103,   148,   149,    51,   151,   -53,   183,    91,    92,    93,
      94,    95,    96,   154,   155,   159,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   160,
     156,    97,    98,    99,   100,   101,   102,   103,   104,    91,
      92,    93,    94,    95,    96,   170,   178,    91,    92,    93,
      94,    95,    96,   180,    97,    98,    99,   100,   101,   102,
     103,   158,    97,    98,    99,   100,   101,   102,   103,   161,
      91,    92,    93,    94,    95,    96,   190,    91,    92,    93,
      94,    95,   -52,   192,   193,    97,    98,    99,   100,   101,
     102,   103,    97,    98,    99,   100,   101,   102,   103,    91,
      92,    93,    94,    17,    18,    19,    20,    21,    22,    23,
      67,    57,   126,   196,    97,    98,    99,   100,   101,   102,
     103,    25,    18,    19,    20,    21,    22,    23,    18,    19,
      20,    21,    22,    23,    99,   100,   101,   102,   103
};

static const yytype_uint8 yycheck[] =
{
      29,    73,    77,    78,    72,    68,     5,     6,     7,     8,
       9,    10,    11,    17,    43,    13,    31,    29,   109,     3,
       4,    49,    51,    27,    29,    30,    31,    32,    33,    34,
      35,     9,     0,    17,    28,    29,    43,    44,    17,    17,
      69,   113,    47,    27,    38,    43,    50,    25,    27,    48,
      79,    80,    28,    44,    44,    31,    85,    48,    48,    88,
      89,    49,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    87,   167,    28,    28,    44,
      31,    46,    31,    45,   152,   148,    31,    12,    38,    51,
      52,    16,    45,    18,    19,    20,    43,    44,   170,   171,
      14,    15,    27,   132,    29,    30,    31,    32,    33,    34,
      35,    40,    41,    42,   186,   190,    29,    44,    31,    46,
     149,   193,    47,   195,    31,    50,    47,   156,    51,    52,
     159,    14,    15,    21,    22,    23,    24,    25,    26,    29,
      30,    31,    32,    33,    34,    35,    47,   176,    36,    37,
      38,    39,    40,    41,    42,    47,    47,    47,    48,    45,
      48,    21,    22,    23,    24,    25,    26,    29,    30,    31,
      32,    33,    34,    35,    47,    43,    36,    37,    38,    39,
      40,    41,    42,    30,    43,    47,    43,    51,    48,    21,
      22,    23,    24,    25,    26,    29,    30,    31,    32,    33,
      34,    35,    43,    47,    36,    37,    38,    39,    40,    41,
      42,    31,    45,    47,    31,    44,    48,    21,    22,    23,
      24,    25,    26,    48,    48,    44,    21,    22,    23,    24,
      25,    26,    36,    37,    38,    39,    40,    41,    42,    46,
      44,    36,    37,    38,    39,    40,    41,    42,    43,    21,
      22,    23,    24,    25,    26,    13,    30,    21,    22,    23,
      24,    25,    26,    31,    36,    37,    38,    39,    40,    41,
      42,    43,    36,    37,    38,    39,    40,    41,    42,    43,
      21,    22,    23,    24,    25,    26,    47,    21,    22,    23,
      24,    25,    44,    48,    13,    36,    37,    38,    39,    40,
      41,    42,    36,    37,    38,    39,    40,    41,    42,    21,
      22,    23,    24,     5,     6,     7,     8,     9,    10,    11,
      30,    29,    87,   194,    36,    37,    38,    39,    40,    41,
      42,     5,     6,     7,     8,     9,    10,    11,     6,     7,
       8,     9,    10,    11,    38,    39,    40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,     0,     3,     4,    17,    27,    56,    57,
      61,    62,    66,    31,    49,    67,    68,     5,     6,     7,
       8,     9,    10,    11,    59,     5,    59,    60,    49,    70,
      59,    28,    31,    58,    59,    31,    56,    61,    65,    12,
      16,    18,    19,    20,    29,    30,    31,    32,    33,    34,
      35,    47,    50,    56,    69,    71,    72,    73,    77,    78,
      80,    81,    82,    84,    85,    86,    87,    58,    31,    45,
      43,    44,    47,    63,    50,    56,    61,    47,    47,    47,
      47,    72,    73,    80,    80,    45,    51,    52,    74,    45,
      31,    21,    22,    23,    24,    25,    26,    36,    37,    38,
      39,    40,    41,    42,    43,    43,    43,    43,    43,    74,
      80,    28,    31,    48,    60,    64,    67,    43,    80,    81,
      81,    80,    80,    48,    80,    72,    77,    30,    75,    76,
      80,    80,    47,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    30,    75,    31,    45,
      67,    31,    44,    48,    48,    48,    44,    48,    43,    44,
      46,    43,    48,    79,    80,    44,    46,    74,    80,    60,
      13,    13,    43,    80,    30,    80,    44,    48,    30,    75,
      31,    67,    67,    48,    80,    46,    14,    15,    83,    67,
      47,    81,    48,    13,    67,    14,    83,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    56,    56,    57,
      58,    58,    58,    58,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    63,    64,    64,
      65,    65,    65,    65,    66,    67,    68,    69,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      73,    74,    75,    75,    76,    76,    77,    77,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    82,    83,
      83,    83,    84,    84,    85,    86,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     2,     2,     0,     5,     4,     1,
       3,     1,     5,     3,     7,     5,     1,     1,     1,     1,
       1,     1,     2,     1,     5,     6,     1,     3,     4,     2,
       2,     2,     1,     1,     6,     3,     1,     1,     2,     0,
       2,     4,     4,     1,     1,     2,     2,     1,     2,     1,
       4,     1,     3,     1,     3,     1,     5,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     6,     8,     7,     6,
       8,     7,     6,     5,     4,     2,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 106 "yacc.y"
                                    { 
                                            exitScope(); 
                                            enterScope(); 
                                            Node* glob_decl = declarationBlockNode(&globalDeclarations);
                                            running = 1;
                                            interpret(glob_decl);
                                            interpret((yyvsp[0].node)); 
                                            inGlobalScope = true;
                                            exitScope(); 
                                            inGlobalScope = false;
                                            if (!errorOccured){
                                                printf("\n");
                                                fprintQueue();
                                            }
                                        }
#line 1597 "yacc.tab.c"
    break;

  case 3:
#line 124 "yacc.y"
                                   { addDeclarationToBlock(&globalDeclarations,(yyvsp[0].node)); }
#line 1603 "yacc.tab.c"
    break;

  case 4:
#line 125 "yacc.y"
                                   { addDeclarationToBlock(&globalDeclarations,(yyvsp[0].node)); }
#line 1609 "yacc.tab.c"
    break;

  case 5:
#line 126 "yacc.y"
                                { addDeclarationToBlock(&globalDeclarations,(yyvsp[0].node)); }
#line 1615 "yacc.tab.c"
    break;

  case 7:
#line 131 "yacc.y"
                                                       { (yyval.node) = declarationBlockNode(currentDeclarations); setVariableType((yyvsp[-2].typeValue),(yyval.node),1); interpret((yyval.node)); }
#line 1621 "yacc.tab.c"
    break;

  case 8:
#line 132 "yacc.y"
                                                   { (yyval.node) = declarationBlockNode(currentDeclarations); setVariableType((yyvsp[-2].typeValue),(yyval.node),0); interpret((yyval.node)); }
#line 1627 "yacc.tab.c"
    break;

  case 9:
#line 136 "yacc.y"
           { enterDeclaration(); }
#line 1633 "yacc.tab.c"
    break;

  case 10:
#line 140 "yacc.y"
                            {
                                Node* decl_node = declarationNode(INVALID_T,(yyvsp[0].stringValue),NULL);
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
#line 1642 "yacc.tab.c"
    break;

  case 11:
#line 144 "yacc.y"
                            {
                                Node* decl_node = declarationNode(INVALID_T,(yyvsp[0].stringValue),NULL);
                                addDeclarationToBlock(currentDeclarations,decl_node);

                            }
#line 1652 "yacc.tab.c"
    break;

  case 12:
#line 150 "yacc.y"
                            {
                                Node* decl_node = declarationNode(INVALID_T,(yyvsp[-2].stringValue),(yyvsp[0].node));
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
#line 1661 "yacc.tab.c"
    break;

  case 13:
#line 154 "yacc.y"
                            {
                                Node* decl_node = declarationNode(INVALID_T,(yyvsp[-2].stringValue),(yyvsp[0].node));
                                addDeclarationToBlock(currentDeclarations,decl_node);
                            }
#line 1670 "yacc.tab.c"
    break;

  case 14:
#line 158 "yacc.y"
                                                        {
                                                                    Node* decl_node = declarationNode(INVALID_T, (yyvsp[-3].stringValue), blockNode(topStack(&currentArraySize)));
                                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                                    popStack(&currentArraySize); 
                                                                }
#line 1680 "yacc.tab.c"
    break;

  case 15:
#line 163 "yacc.y"
                                                        { 
                                                                    Node* decl_node = declarationNode(INVALID_T, (yyvsp[-3].stringValue), blockNode(topStack(&currentArraySize)));
                                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                                    popStack(&currentArraySize); 
                                                                }
#line 1690 "yacc.tab.c"
    break;

  case 16:
#line 171 "yacc.y"
        { (yyval.typeValue) = INT_T;}
#line 1696 "yacc.tab.c"
    break;

  case 17:
#line 172 "yacc.y"
            { (yyval.typeValue) = FLOAT_T; }
#line 1702 "yacc.tab.c"
    break;

  case 18:
#line 173 "yacc.y"
           { (yyval.typeValue) = CHAR_T; }
#line 1708 "yacc.tab.c"
    break;

  case 19:
#line 174 "yacc.y"
             { (yyval.typeValue) = STRING_T; }
#line 1714 "yacc.tab.c"
    break;

  case 20:
#line 175 "yacc.y"
           { (yyval.typeValue) = BOOL_T; }
#line 1720 "yacc.tab.c"
    break;

  case 21:
#line 176 "yacc.y"
           { (yyval.typeValue) = STATEMENT_T; }
#line 1726 "yacc.tab.c"
    break;

  case 22:
#line 180 "yacc.y"
                    { (yyval.typeValue) = (yyvsp[0].typeValue); }
#line 1732 "yacc.tab.c"
    break;

  case 23:
#line 181 "yacc.y"
                { (yyval.typeValue) = (yyvsp[0].typeValue); }
#line 1738 "yacc.tab.c"
    break;

  case 24:
#line 185 "yacc.y"
                                                          {
                                                                        exitScope();
                                                                        exitCall();
                                                                        callingFunction = 0;
                                                                        if (returnExists && (yyvsp[-3].typeValue) == STATEMENT_T)
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("Cannot return from void function.");
                                                                        }
                                                                        else if (!returnExists && (yyvsp[-3].typeValue) != STATEMENT_T)
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("No return from non-void function");
                                                                        }
                                                                        else if (returnExists - 1 != (yyvsp[-3].typeValue))
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("Incompatible return type %s expected %s",getTypeName(returnExists-1),getTypeName((yyvsp[-3].typeValue)));
                                                                        }
                                                                        else
                                                                        {
                                                                            (yyval.node) = functionNode((yyvsp[-3].typeValue),(yyvsp[-2].stringValue),(yyvsp[-1].node),(yyvsp[0].node));
                                                                            interpret((yyval.node));
                                                                        }
                                                                        returnExists = 0;
                                                                    }
#line 1769 "yacc.tab.c"
    break;

  case 25:
#line 211 "yacc.y"
                                                          {
                                                                        exitScope();
                                                                        exitCall();callingFunction = 0;
                                                                        if (returnExists && (yyvsp[-4].typeValue) == STATEMENT_T)
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("Cannot return from void function.");
                                                                        }
                                                                        else if (!returnExists && (yyvsp[-4].typeValue) != STATEMENT_T)
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("No return from non-void function");
                                                                        }
                                                                        else if (returnExists - 1 != (yyvsp[-4].typeValue))
                                                                        {
                                                                            (yyval.node) = NULL;
                                                                            yyerror("Incompatible return type %s expected %s",getTypeName(returnExists-1),getTypeName((yyvsp[-4].typeValue)));
                                                                        }
                                                                        else
                                                                        {
                                                                            Node* parameters = declarationBlockNode(currentDeclarations);
                                                                            parameters->node.decl_block_node.size=0;
                                                                            (yyval.node) = functionNode((yyvsp[-4].typeValue),(yyvsp[-3].stringValue),parameters,(yyvsp[0].node));
                                                                            interpret((yyval.node));
                                                                        }
                                                                        returnExists = 0;
                                                                    }
#line 1801 "yacc.tab.c"
    break;

  case 26:
#line 241 "yacc.y"
            { enterCall(); enterScope(); enterDeclaration(); callingFunction=1; returnExists=0; }
#line 1807 "yacc.tab.c"
    break;

  case 27:
#line 245 "yacc.y"
                                {
                                    Node* parameters = declarationBlockNode(currentDeclarations); 
                                    interpret(parameters);
                                    (yyval.node) = parameters;
                                }
#line 1817 "yacc.tab.c"
    break;

  case 28:
#line 253 "yacc.y"
                                                { 
                                                    Node* decl_node = declarationNode((yyvsp[-1].typeValue),(yyvsp[0].stringValue),NULL);
                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                }
#line 1826 "yacc.tab.c"
    break;

  case 29:
#line 257 "yacc.y"
                                                { 
                                                    Node* decl_node = declarationNode((yyvsp[-1].typeValue),(yyvsp[0].stringValue),NULL);
                                                    addDeclarationToBlock(currentDeclarations,decl_node);
                                                }
#line 1835 "yacc.tab.c"
    break;

  case 34:
#line 271 "yacc.y"
                                                  { (yyval.node) = NULL; }
#line 1841 "yacc.tab.c"
    break;

  case 35:
#line 276 "yacc.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1847 "yacc.tab.c"
    break;

  case 36:
#line 280 "yacc.y"
        { enterBlock(); }
#line 1853 "yacc.tab.c"
    break;

  case 37:
#line 284 "yacc.y"
        { exitBlock(); }
#line 1859 "yacc.tab.c"
    break;

  case 38:
#line 288 "yacc.y"
                                 { 
                                    addStatementToBlock(topStack(&stack),(yyvsp[0].node));
                                    (yyval.node) = blockNode(topStack(&stack));
                                 }
#line 1868 "yacc.tab.c"
    break;

  case 40:
#line 296 "yacc.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1874 "yacc.tab.c"
    break;

  case 41:
#line 297 "yacc.y"
                                        { 
                                            Node* var = varNode((yyvsp[-3].stringValue),getSymbolFromCallstackUnit(symbolTable,(yyvsp[-3].stringValue)));
                                            Node* expression = (yyvsp[-1].node);
                                            (yyval.node) = assignmentNode(var,expression);
                                        }
#line 1884 "yacc.tab.c"
    break;

  case 42:
#line 302 "yacc.y"
                                        {
                                            (yyval.node) = assignmentNode((yyvsp[-3].node), (yyvsp[-1].node));
                                        }
#line 1892 "yacc.tab.c"
    break;

  case 43:
#line 305 "yacc.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1898 "yacc.tab.c"
    break;

  case 44:
#line 306 "yacc.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1904 "yacc.tab.c"
    break;

  case 45:
#line 307 "yacc.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1910 "yacc.tab.c"
    break;

  case 46:
#line 308 "yacc.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1916 "yacc.tab.c"
    break;

  case 47:
#line 309 "yacc.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1922 "yacc.tab.c"
    break;

  case 48:
#line 310 "yacc.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1928 "yacc.tab.c"
    break;

  case 49:
#line 314 "yacc.y"
        { 
            (yyval.stringValue) = (yyvsp[0].stringValue);
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,(yyvsp[0].stringValue));
            if (sym == NULL)
                yyerror("Undeclared variable %s",(yyvsp[0].stringValue));
        }
#line 1939 "yacc.tab.c"
    break;

  case 50:
#line 323 "yacc.y"
                                                            {
                                                                Symbol *sym = getSymbolFromCallstackUnit(symbolTable, (yyvsp[-3].stringValue));
                                                                (yyval.node) = arrayAccessNode((yyvsp[-3].stringValue), topStack(&currentArraySize), sym->value.array_v.type);
                                                                popStack(&currentArraySize); 
                                                            }
#line 1949 "yacc.tab.c"
    break;

  case 51:
#line 331 "yacc.y"
                                                            { 
                                                                NodeBlock *new_block = (NodeBlock*)malloc(sizeof(NodeBlock));
                                                                initializeBlock(new_block);
                                                                pushStack(&currentArraySize, new_block); 
                                                            }
#line 1959 "yacc.tab.c"
    break;

  case 52:
#line 340 "yacc.y"
                                                               {   
                                                                Symbol sym;
                                                                sym.type = INT_T;
                                                                sym.value.int_v = (yyvsp[0].intValue);
                                                                Node* size = constNode(&sym);
                                                                addStatementToBlock(topStack(&currentArraySize), size);
                                                            }
#line 1971 "yacc.tab.c"
    break;

  case 53:
#line 347 "yacc.y"
                                                               {
                                                                Symbol sym;
                                                                sym.type = INT_T;
                                                                sym.value.int_v = (yyvsp[0].intValue);
                                                                Node* size = constNode(&sym);
                                                                addStatementToBlock(topStack(&currentArraySize), size);
                                                            }
#line 1983 "yacc.tab.c"
    break;

  case 54:
#line 357 "yacc.y"
                                                            {   
                                                                addStatementToBlock(topStack(&currentArraySize), (yyvsp[0].node));
                                                            }
#line 1991 "yacc.tab.c"
    break;

  case 55:
#line 360 "yacc.y"
                                                            {
                                                                addStatementToBlock(topStack(&currentArraySize), (yyvsp[0].node));
                                                            }
#line 1999 "yacc.tab.c"
    break;

  case 56:
#line 366 "yacc.y"
                                                     {
                                                        char* signature = createFuncCallSignature((yyvsp[-3].stringValue),blockNode(&currentFunctionCall));
                                                        Symbol* sym = getSymbolFromCallstackUnit(symbolTable,signature);
                                                        if (sym == NULL)
                                                        {
                                                            yyerror("No function with signature %s declared",signature);
                                                            (yyval.node) = NULL;
                                                        }
                                                        else
                                                            (yyval.node) = functionCallNode(signature,blockNode(&currentFunctionCall),sym->value.function_v->node.function_node.type);
                                                    }
#line 2015 "yacc.tab.c"
    break;

  case 57:
#line 377 "yacc.y"
                                                     {
                                                        char* signature = createFuncCallSignature((yyvsp[-2].stringValue),blockNode(&currentFunctionCall));
                                                        Symbol* sym = getSymbolFromCallstackUnit(symbolTable,signature);
                                                        if (sym == NULL)
                                                        {
                                                            yyerror("No function with signature %s declared",signature);
                                                            (yyval.node) = NULL;
                                                        }
                                                        else
                                                            (yyval.node) = functionCallNode(signature,blockNode(&currentFunctionCall),sym->value.function_v->node.function_node.type);
                                                    }
#line 2031 "yacc.tab.c"
    break;

  case 58:
#line 391 "yacc.y"
                                                     { initializeBlock(&currentFunctionCall); }
#line 2037 "yacc.tab.c"
    break;

  case 59:
#line 395 "yacc.y"
                                                    { addStatementToBlock(&currentFunctionCall, (yyvsp[0].node)); }
#line 2043 "yacc.tab.c"
    break;

  case 60:
#line 396 "yacc.y"
                                                    { addStatementToBlock(&currentFunctionCall, (yyvsp[0].node)); }
#line 2049 "yacc.tab.c"
    break;

  case 61:
#line 400 "yacc.y"
                                       {
                                        Symbol sym;
                                        sym.type = INT_T;
                                        sym.value.int_v = (yyvsp[0].intValue);
                                        (yyval.node) = constNode(&sym);
                                    }
#line 2060 "yacc.tab.c"
    break;

  case 62:
#line 406 "yacc.y"
                                       {
                                        Symbol sym;
                                        sym.type = CHAR_T;
                                        sym.value.char_v = (yyvsp[0].charValue);
                                        (yyval.node) = constNode(&sym);
                                    }
#line 2071 "yacc.tab.c"
    break;

  case 63:
#line 412 "yacc.y"
                                       {
                                        Symbol sym;
                                        sym.type = BOOL_T;
                                        sym.value.bool_v = (yyvsp[0].boolValue);
                                        (yyval.node) = constNode(&sym);
                                    }
#line 2082 "yacc.tab.c"
    break;

  case 64:
#line 418 "yacc.y"
                                       {
                                        Symbol sym;
                                        sym.type = FLOAT_T;
                                        sym.value.float_v = (yyvsp[0].floatValue);
                                        (yyval.node) = constNode(&sym);
                                    }
#line 2093 "yacc.tab.c"
    break;

  case 65:
#line 424 "yacc.y"
                                       {
                                        Symbol sym;
                                        sym.type = STRING_T;
                                        sym.value.string_v = (yyvsp[0].stringValue);
                                        (yyval.node) = constNode(&sym);
                                    }
#line 2104 "yacc.tab.c"
    break;

  case 66:
#line 430 "yacc.y"
                                    {
                                        (yyval.node) = varNode((yyvsp[0].stringValue),getSymbolFromCallstackUnit(symbolTable,(yyvsp[0].stringValue)));
                                    }
#line 2112 "yacc.tab.c"
    break;

  case 67:
#line 433 "yacc.y"
                                    { (yyval.node) = NULL; }
#line 2118 "yacc.tab.c"
    break;

  case 68:
#line 434 "yacc.y"
                                    { (yyval.node) = NULL; }
#line 2124 "yacc.tab.c"
    break;

  case 69:
#line 435 "yacc.y"
                                    { (yyval.node) = binaryOpNode(ADD,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2130 "yacc.tab.c"
    break;

  case 70:
#line 436 "yacc.y"
                                    { (yyval.node) = binaryOpNode(SUB,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2136 "yacc.tab.c"
    break;

  case 71:
#line 437 "yacc.y"
                                    { (yyval.node) = binaryOpNode(MUL,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2142 "yacc.tab.c"
    break;

  case 72:
#line 438 "yacc.y"
                                    { (yyval.node) = binaryOpNode(DIV,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2148 "yacc.tab.c"
    break;

  case 73:
#line 439 "yacc.y"
                                    { (yyval.node) = binaryOpNode(MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2154 "yacc.tab.c"
    break;

  case 74:
#line 440 "yacc.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 2160 "yacc.tab.c"
    break;

  case 75:
#line 441 "yacc.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 2166 "yacc.tab.c"
    break;

  case 76:
#line 442 "yacc.y"
                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2172 "yacc.tab.c"
    break;

  case 77:
#line 443 "yacc.y"
                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2178 "yacc.tab.c"
    break;

  case 78:
#line 447 "yacc.y"
                                  { (yyval.node) = binaryOpNode(LESS,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2184 "yacc.tab.c"
    break;

  case 79:
#line 448 "yacc.y"
                                    { (yyval.node) = binaryOpNode(GREATER,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2190 "yacc.tab.c"
    break;

  case 80:
#line 449 "yacc.y"
                                           { (yyval.node) = binaryOpNode(LEQ,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2196 "yacc.tab.c"
    break;

  case 81:
#line 450 "yacc.y"
                                              { (yyval.node) = binaryOpNode(GEQ,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2202 "yacc.tab.c"
    break;

  case 82:
#line 451 "yacc.y"
                                          { (yyval.node) = binaryOpNode(NEQ,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2208 "yacc.tab.c"
    break;

  case 83:
#line 452 "yacc.y"
                                       { (yyval.node) = binaryOpNode(EQQ,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2214 "yacc.tab.c"
    break;

  case 84:
#line 453 "yacc.y"
                                     { (yyval.node) = binaryOpNode(AND,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2220 "yacc.tab.c"
    break;

  case 85:
#line 454 "yacc.y"
                                     { (yyval.node) = binaryOpNode(OR,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2226 "yacc.tab.c"
    break;

  case 86:
#line 458 "yacc.y"
                                                    { (yyval.node) = ifNode((yyvsp[-3].node),(yyvsp[0].node),NULL); }
#line 2232 "yacc.tab.c"
    break;

  case 87:
#line 459 "yacc.y"
                                                    { (yyval.node) = ifNode((yyvsp[-5].node),(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2238 "yacc.tab.c"
    break;

  case 88:
#line 460 "yacc.y"
                                                    { (yyval.node) = ifNode((yyvsp[-4].node),(yyvsp[-1].node),(yyvsp[0].node)); }
#line 2244 "yacc.tab.c"
    break;

  case 89:
#line 464 "yacc.y"
                                                      { (yyval.node) = ifNode((yyvsp[-3].node),(yyvsp[0].node),NULL); }
#line 2250 "yacc.tab.c"
    break;

  case 90:
#line 465 "yacc.y"
                                                      { (yyval.node) = ifNode((yyvsp[-5].node),(yyvsp[-2].node),(yyvsp[0].node)); }
#line 2256 "yacc.tab.c"
    break;

  case 91:
#line 466 "yacc.y"
                                                      { (yyval.node) = ifNode((yyvsp[-4].node),(yyvsp[-1].node),(yyvsp[0].node)); }
#line 2262 "yacc.tab.c"
    break;

  case 92:
#line 470 "yacc.y"
                                              { (yyval.node) = whileNode((yyvsp[-3].node),(yyvsp[0].node)); }
#line 2268 "yacc.tab.c"
    break;

  case 93:
#line 471 "yacc.y"
                                            { (yyval.node) = whileNode((yyvsp[-2].node),NULL); }
#line 2274 "yacc.tab.c"
    break;

  case 94:
#line 475 "yacc.y"
                                            { (yyval.node) = printNode((yyvsp[-1].node)); }
#line 2280 "yacc.tab.c"
    break;

  case 95:
#line 478 "yacc.y"
                        { 
                            if (callingFunction)
                            {
                                (yyval.node) = returnNode((yyvsp[0].node));
                                returnExists = 1 + (yyvsp[0].node)->value_type;
                            }
                            else
                            {
                                (yyval.node) = NULL;
                                yyerror("Cannot return. Not in a function.");
                            }
                        }
#line 2297 "yacc.tab.c"
    break;

  case 96:
#line 493 "yacc.y"
                                            { 
                                                Node *left = (yyvsp[-3].node);
                                                Node *right = (yyvsp[-1].node);
                                                if(left->value_type != STRING_T){
                                                    (yyval.node) = NULL;
                                                    yyerror("Left must be a string");
                                                }
                                                (yyval.node) = duoprintNode((yyvsp[-3].node), (yyvsp[-1].node));
                                            }
#line 2311 "yacc.tab.c"
    break;


#line 2315 "yacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 504 "yacc.y"


void yyerror(const char* format, ...)
{
    errorOccured=1;
    va_list arglist;

    if (!running)
        fprintf(stderr,"Error at line %d:\n",line_number);
    else
        fprintf(stderr,"Error at running:\n");

    va_start(arglist,format);
    vfprintf(stderr,format,arglist);
    va_end(arglist);

    fprintf(stderr,"\n");
}


void enterBlock()
{
    enterScope();
    NodeBlock* new_block = (NodeBlock*)malloc(sizeof(NodeBlock));
    initializeBlock(new_block);
    pushStack(&stack,new_block);
}

void exitBlock()
{
    exitScope();
    popStack(&stack);
}

void enterScope()
{
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
    {
        fprintf(sym_file,"\t");
    }
    if (inGlobalScope)
        fprintf(sym_file,"Entered global scope\n");
    else if (running)
        fprintf(sym_file,"Entered new scope\n");
    HashTable* scopeTable = (HashTable*)malloc(sizeof(HashTable));
    initializeHashTable(scopeTable);
    pushCallstackUnit(symbolTable, scopeTable);
}

void exitScope()
{
    free(popCallstackUnit(symbolTable));
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (inGlobalScope)
        fprintf(sym_file,"Exited global scope\n");
    else if (running)
        fprintf(sym_file,"Exited scope\n");
}

void enterDeclaration()
{
    currentDeclarations = (NodeDeclarationBlock*)malloc(sizeof(NodeDeclarationBlock));
    initializeDeclarationBlock(currentDeclarations);
}

void enterCall()
{
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (running)
        fprintf(sym_file,"Entered new call\n");
    CallStackUnit* newSymbolTable = (CallStackUnit*)malloc(sizeof(CallStackUnit));
    initializeCallstackUnit(newSymbolTable);
    pushCallstackUnit(newSymbolTable,topCallstack(callStack)->stack[0]);
    pushCallstack(callStack,newSymbolTable);
    symbolTable = newSymbolTable;
}

void exitCall()
{
    free(popCallstack(callStack));
    symbolTable = topCallstack(callStack);
    int scopeDepth = symbolTable->size-1;
    int callFrameIndex = callStack->size-1;
    for (int i=0;running && i<scopeDepth+callFrameIndex;i++)
        fprintf(sym_file,"\t");
    if (running)
        fprintf(sym_file,"Exited call\n");
}

void* getPointerToArrayElement(Node* root, int print_errors)
{
    interpret(root->node.array_access_node.index);
    Symbol *sym = getSymbolFromCallstackUnit(symbolTable, root->node.array_access_node.name);


    int bad = 0;
    if (sym == NULL)
    {
        if(print_errors == 1)
            yyerror("Undeclared variable %s",root->node.array_access_node.name);
        return NULL;
    }
    else if (!sym->initialized && !assigning)
    {
        if(print_errors == 1)
            yyerror("Unitialized variable %s",root->node.array_access_node.name);
        return NULL;
    }
    else if(sym->value.array_v.dimensions - 1 != root->node.array_access_node.index->node.block_node.size)
    {
        if(print_errors == 1)
            yyerror("Wrong index count, %s has %d dimensions, tried only with %d", root->node.array_access_node.name, sym->value.array_v.dimensions-1, root->node.array_access_node.index->node.block_node.size);
        bad = 1;
        return NULL;
    }
    else
    {
        int size = sym->value.array_v.dimensions - 1;
        int product = 1;
        for(int i = 0; i < size; ++i)
        {
            if(root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v >= sym->value.array_v.size[i])
            {
                if(print_errors == 1)
                    yyerror("Index out of bounds, %d > %d", root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v, sym->value.array_v.size[i] - 1);
                bad = 1;
                return NULL;
            }
            else if(root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v < 0)
            {
                if(print_errors == 1)
                    yyerror("Negative index, %d", root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v, sym->value.array_v.size[i] - 1);
                bad = 1;
                return NULL;
            }
            else
            {
                product *= sym->value.array_v.size[i];
            }
        }
        if(bad == 0)
        {
            int distance = 0;
            for(int i = 0; i < size; ++i)
            {
                product /= sym->value.array_v.size[i];
                distance += (product * root->node.array_access_node.index->node.block_node.statements[i]->interpret_result.int_v);
            }
            if (assigning)
                sym->initialized = 1;
            switch(sym->value.array_v.type)
            {
                case INT_T:
                {
                    return (int*)(sym->value.array_v.value) + distance;
                }
                case CHAR_T:
                {
                    return (char*)(sym->value.array_v.value) + distance;
                }
                case BOOL_T:
                {
                    return (int*)(sym->value.array_v.value) + distance;
                }
                case FLOAT_T:
                {
                    return (float*)(sym->value.array_v.value) + distance;
                }
                case STRING_T:
                {
                    return (char**)(sym->value.array_v.value) + distance;
                }
            }
        }
    }
    return NULL;
}

void fprintQueue()
{
    if (printQueue != NULL)
        printf("%s",printQueue);
}

void addPrintQueue(const char* format, ...)
{
    char message[256];
    va_list arglist;

    va_start(arglist,format);
    vsprintf(message,format,arglist);
    int size = strlen(message)+1;
    if (printQueue == NULL)
    {
        printQueue = (char*)malloc(size);
        strcpy(printQueue,message);
    }
    else
    {
        int length = strlen(printQueue);
        printQueue = (char*)realloc(printQueue,length+size);
        strcat(printQueue,message);
    }
    
    va_end(arglist);
}

void interpret(struct Node* root)
{
    if (!root)
    {
        return;
    }

    if (root->value_type == INVALID_T)
    {
        return;
    }

    if (returnNodePointer != NULL)
    {
        return;
    }
    switch (root->type)
    {
        case VAR_N:
        {
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,root->node.var_node.name);
            if (sym == NULL)
                yyerror("Undeclared variable %s",root->node.var_node.name);
            else if (!sym->initialized && !assigning)
                yyerror("Variable not initialized %s",root->node.var_node.name);
            else
            {
                switch (root->value_type)
                {
                    case INT_T: root->interpret_result.int_v = sym->value.int_v; break;
                    case FLOAT_T: root->interpret_result.float_v = sym->value.float_v; break;
                    case BOOL_T: root->interpret_result.bool_v = sym->value.bool_v; break;
                    case CHAR_T: root->interpret_result.char_v = sym->value.char_v; break;
                    case STRING_T: root->interpret_result.string_v = sym->value.string_v; break;
                }
            }
            break;
        }
        case CONST_N:
        {   
            switch (root->value_type)
            {
                case INT_T: root->interpret_result.int_v = root->node.const_node.value.value.int_v; break;
                case FLOAT_T: root->interpret_result.float_v = root->node.const_node.value.value.float_v; break;
                case BOOL_T: root->interpret_result.bool_v = root->node.const_node.value.value.bool_v; break;
                case CHAR_T: root->interpret_result.char_v = root->node.const_node.value.value.char_v; break;
                case STRING_T: root->interpret_result.string_v = strdup(root->node.const_node.value.value.string_v); break;
            }
            break;
        }
        case OP_N:
        {
            for(int i = 0; i < root->node.op_node.size; ++i)
            {
                interpret(root->node.op_node.operands[i]);
            }
            if (root->value_type == INT_T)
            {
                {
                    int left = root->node.op_node.operands[0]->interpret_result.int_v;
                    int right = root->node.op_node.operands[1]->interpret_result.int_v;
                    int result = 0;
                    switch (root->node.op_node.op)
                    {
                        case ADD: result = left + right; break;
                        case SUB: result = left - right; break;
                        case MUL: result = left * right; break;
                        case DIV: result = left / right; break;
                        case MOD: result = left % right; break;
                        case LESS: result = left < right; break;
                        case GREATER: result = left > right; break;
                        case LEQ: result = left <= right; break;
                        case GEQ: result = left >= right; break;
                        case EQQ: result = left == right; break;
                        case NEQ: result = left != right; break;
                        case AND: result = left && right; break;
                        case OR: result = left || right; break;
                    }
                    root->interpret_result.int_v = result;
                }
            }
            else if (root->value_type == FLOAT_T)
            {
                {
                    float left = root->node.op_node.operands[0]->interpret_result.float_v;
                    float right = root->node.op_node.operands[1]->interpret_result.float_v;
                    float result = 0;
                    switch (root->node.op_node.op)
                    {
                        case ADD: result = left + right; break;
                        case SUB: result = left - right; break;
                        case MUL: result = left * right; break;
                        case DIV: result = left / right; break;
                        case LESS: result = left < right; break;
                        case GREATER: result = left > right; break;
                        case LEQ: result = left <= right; break;
                        case GEQ: result = left >= right; break;
                        case EQQ: result = left == right; break;
                        case NEQ: result = left != right; break;
                        case AND: result = left && right; break;
                        case OR: result = left || right; break;
                    }
                    root->interpret_result.float_v = result;
                }
            }
            else if (root->value_type == BOOL_T)
            {
                int left = root->node.op_node.operands[0]->interpret_result.bool_v;
                int right = root->node.op_node.operands[1]->interpret_result.bool_v;
                int result = 0;
                switch (root->node.op_node.op)
                {
                    case ADD: result = (left + right) != 0; break;
                    case SUB: result = (left - right) != 0; break;
                    case MUL: result = (left * right) != 0; break;
                    case DIV: result = (left / right) != 0; break;
                    case LESS: result = left < right; break;
                    case GREATER: result = left > right; break;
                    case LEQ: result = left <= right; break;
                    case GEQ: result = left >= right; break;
                    case EQQ: result = left == right; break;
                    case NEQ: result = left != right; break;
                    case AND: result = left && right; break;
                    case OR: result = left || right; break;
                }
                root->interpret_result.bool_v = result;
            }
            else if (root->value_type == CHAR_T) 
            {
                char left = root->node.op_node.operands[0]->interpret_result.char_v;
                char right = root->node.op_node.operands[1]->interpret_result.char_v;
                char result = 0;
                switch (root->node.op_node.op)
                {
                    case ADD: result = left + right; break;
                    case SUB: result = left - right; break;
                    case MUL: result = left * right; break;
                    case DIV: result = left / !right; break;
                    case LESS: result = left < right; break;
                    case GREATER: result = left > right; break;
                    case LEQ: result = left <= right; break;
                    case GEQ: result = left >= right; break;
                    case EQQ: result = left == right; break;
                    case NEQ: result = left != right; break;
                    case AND: result = left && right; break;
                    case OR: result = left || right; break;
                }
                root->interpret_result.char_v = result;
            }
            break;
        }
        case BLOCK_N:
        {
            enterScope();
            for (int i=0;i<root->node.block_node.size;i++)
                interpret(root->node.block_node.statements[i]);
            exitScope();
            break;
        }
        case IF_N:
        {
            interpret(root->node.if_node.condition);
            if (root->node.if_node.condition->interpret_result.int_v)
            {
                interpret(root->node.if_node.if_block);
            }
            else
            {
                interpret(root->node.if_node.else_block);
            }
            break;
        }
        case WHILE_N:
            interpret(root->node.while_node.condition);
            while (root->node.while_node.condition->interpret_result.int_v)
            {
                interpret(root->node.while_node.block);
                interpret(root->node.while_node.condition);
            }
            break;
        case ASSGN_N:
        {
            assigning = 1;
            interpret(root->node.assgn_node.var);
            assigning = 0;
            interpret(root->node.assgn_node.expression);
            if(root->node.assgn_node.var->type == VAR_N) 
            {
                Symbol *sym = getSymbolFromCallstackUnit(symbolTable,root->node.assgn_node.var->node.var_node.name);
                
                if(sym->isConstant == 1)
                {
                    yyerror("Cannot assign to constant variable %s.",root->node.assgn_node.var->node.var_node.name);
                    break;
                }
                
                sym->initialized = 1;

                if(root->value_type == STRING_T)
                {
                    sym->value.string_v = root->node.assgn_node.expression->interpret_result.string_v;
                }
                else if(root->value_type == CHAR_T)
                {
                    sym->value.char_v = root->node.assgn_node.expression->interpret_result.char_v;
                }
                else if(root->value_type == FLOAT_T)
                {
                    sym->value.float_v = root->node.assgn_node.expression->interpret_result.float_v;
                }
                else if(root->value_type == BOOL_T)
                {
                    sym->value.bool_v = root->node.assgn_node.expression->interpret_result.bool_v;
                }
                else if(root->value_type == INT_T)
                {
                    sym->value.int_v = root->node.assgn_node.expression->interpret_result.int_v;
                }
            }
            else if(root->node.assgn_node.var->type == ARRAY_ACCESS_N)
            {
                void *p = getPointerToArrayElement(root->node.assgn_node.var, 0);
                if(p != NULL)
                {
                    if(root->value_type == STRING_T)
                    {
                        *((char**)p) = root->node.assgn_node.expression->interpret_result.string_v;
                    }
                    else if(root->value_type == CHAR_T)
                    {
                        *((char*)p) = root->node.assgn_node.expression->interpret_result.char_v;
                    }
                    else if(root->value_type == FLOAT_T)
                    {
                        *((float*)p) = root->node.assgn_node.expression->interpret_result.float_v;
                    }
                    else if(root->value_type == BOOL_T)
                    {
                        *((int*)p) = root->node.assgn_node.expression->interpret_result.bool_v;
                    }
                    else if(root->value_type == INT_T)
                    {
                        *((int*)p) = root->node.assgn_node.expression->interpret_result.int_v;
                    }
                }
            }
            break;
        }
        case PRINT_N:
        {
            interpret(root->node.print_node.expression);
            switch (root->node.print_node.expression->value_type)
            {
                case INT_T:
                    addPrintQueue("%d\n",root->node.print_node.expression->interpret_result.int_v);
                    break;
                case FLOAT_T:
                    addPrintQueue("%f\n",root->node.print_node.expression->interpret_result.float_v);
                    break;
                case BOOL_T:
                    addPrintQueue("%s\n",root->node.print_node.expression->interpret_result.bool_v ? "true" : "false");
                    break;
                case CHAR_T:
                    addPrintQueue("%c\n",root->node.print_node.expression->interpret_result.char_v);
                    break;
                case STRING_T:
                    addPrintQueue("%s\n",root->node.print_node.expression->interpret_result.string_v);
                    break;
            }
            break;
        }
        case DUOPRINT_N:
        {
            interpret(root->node.duoprint_node.expression1);
            addPrintQueue("%s ", root->node.duoprint_node.expression1->interpret_result.string_v);
            interpret(root->node.duoprint_node.expression2);
            switch (root->node.duoprint_node.expression2->value_type)
            {
                case INT_T:
                    addPrintQueue("%d\n",root->node.duoprint_node.expression2->interpret_result.int_v);
                    break;
                case FLOAT_T:
                    addPrintQueue("%f\n",root->node.duoprint_node.expression2->interpret_result.float_v);
                    break;
                case BOOL_T:
                    addPrintQueue("%s\n",root->node.duoprint_node.expression2->interpret_result.bool_v ? "true" : "false");
                    break;
                case CHAR_T:
                    addPrintQueue("%c\n",root->node.duoprint_node.expression2->interpret_result.char_v);
                    break;
                case STRING_T:
                    addPrintQueue("%s\n",root->node.duoprint_node.expression2->interpret_result.string_v);
                    break;
            }
            break;
        }
        case DECLARATION_N:
        {
            Symbol sym;
            sym.type = root->node.declaration_node.type;
            sym.initialized = 0;
            if (root->node.declaration_node.expression != NULL && root->node.declaration_node.expression->type == BLOCK_N)
            {
                int array_dimensions = root->node.declaration_node.expression->node.block_node.size;
                sym.value.array_v.size = malloc(sizeof(int) * array_dimensions);
                sym.value.array_v.dimensions = array_dimensions;
                int allocate = 1;

                for(int i = 0; i < array_dimensions - 1; ++i)
                {
                    allocate *= root->node.declaration_node.expression->node.block_node.statements[i]->node.const_node.value.value.int_v;
                    sym.value.array_v.size[i] = root->node.declaration_node.expression->node.block_node.statements[i]->node.const_node.value.value.int_v;
                }
                switch(root->node.declaration_node.expression->node.block_node.statements[array_dimensions - 1]->node.const_node.value.value.int_v)
                {
                    case INT_T:
                    {
                        sym.value.array_v.type = INT_T;
                        sym.value.array_v.value = malloc(sizeof(int) * allocate);
                        break;
                    }
                    case CHAR_T:
                    {
                        sym.value.array_v.type = CHAR_T;
                        sym.value.array_v.value = malloc(sizeof(char) * allocate);
                        break;
                    }
                    case BOOL_T:
                    {
                        sym.value.array_v.type = BOOL_T;
                        sym.value.array_v.value = malloc(sizeof(int) * allocate);
                        break;
                    }
                    case FLOAT_T:
                    {
                        sym.value.array_v.type = FLOAT_T;
                        sym.value.array_v.value = malloc(sizeof(float) * allocate);
                        break;
                    }
                    case STRING_T:
                    {
                        sym.value.array_v.type = STRING_T;
                        sym.value.array_v.value = malloc(sizeof(char*) * allocate);
                        break;
                    }
                }

                if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name))
                {
                    if (printDeclarationErrors)
                        yyerror("Variable %s already declared",root->node.declaration_node.name);
                }
                else
                {
                    insertHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name,&sym);
                    if (running)
                    {
                        int scope_depth = symbolTable->size-1;
                        int call_frame_index = callStack->size-1;
                        for (int i=0;running && i<scope_depth+call_frame_index;i++)
                            fprintf(sym_file,"\t");
                        fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",root->node.declaration_node.name,getTypeName(sym.type),scope_depth,call_frame_index);
                    }
                }
                break;
            }
            else
            { 
                sym.isConstant = root->node.declaration_node.isConstant;
                if (root->node.declaration_node.expression != NULL)
                {
                    interpret(root->node.declaration_node.expression);
                    sym.initialized = 1;
                    switch (root->node.declaration_node.type)
                    {
                        case INT_T:
                            sym.value.int_v = root->node.declaration_node.expression->interpret_result.int_v;
                            break;
                        case FLOAT_T:
                            sym.value.float_v = root->node.declaration_node.expression->interpret_result.float_v;
                            break;
                        case BOOL_T:
                            sym.value.bool_v = root->node.declaration_node.expression->interpret_result.bool_v;
                            break;
                        case CHAR_T:
                            sym.value.char_v = root->node.declaration_node.expression->interpret_result.char_v;
                            break;
                        case STRING_T:
                            sym.value.string_v = root->node.declaration_node.expression->interpret_result.string_v;
                            break;
                    }
                }
                else
                {
                    if(sym.isConstant == 1)
                    {
                        if (printDeclarationErrors)
                            yyerror("Constant variables need to be initialized.\n");
                        sym.type = INVALID_T;
                        break;
                    }
                    sym.value.int_v = 0;
                }
                if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name))
                {
                    if (printDeclarationErrors)
                        yyerror("Variable %s already declared",root->node.declaration_node.name);
                }
                else
                {
                    insertHashTable(topCallstackUnit(symbolTable),root->node.declaration_node.name,&sym);
                    if (running)
                    {
                        int scope_depth = symbolTable->size-1;
                        int call_frame_index = callStack->size-1;
                        for (int i=0;running && i<scope_depth+call_frame_index;i++)
                            fprintf(sym_file,"\t");
                        fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",root->node.declaration_node.name,getTypeName(sym.type),scope_depth,call_frame_index);
                    }
                }
                break;
            }
        }
	    case DECL_BLOCK_N:
        {
            for (int i=0;i<root->node.decl_block_node.size;i++)
                interpret(root->node.decl_block_node.declarations[i]);
            break;
        }
        case FUNCTION_N:
        {
            Symbol sym;
            sym.type = FUNCTION_T;
            sym.value.function_v = root;
            char* function_name = createFuncSignature(root);
            if (NULL != getSymbolFromHashTable(topCallstackUnit(symbolTable),function_name))
            {
                if (printDeclarationErrors)
                    yyerror("Function %s already declared",function_name);
            }
            else
            {
                insertHashTable(topCallstackUnit(symbolTable),function_name,&sym);
                if (running)
                {
                    int scope_depth = symbolTable->size-1;
                    int call_frame_index = callStack->size-1;
                    for (int i=0;running && i<scope_depth+call_frame_index;i++)
                    {
                        fprintf(sym_file,"\t");
                    }
                    fprintf(sym_file,"Inserted symbol %s of type %s at scope depth %d in call frame %d\n",function_name,getTypeName(sym.type),scope_depth,call_frame_index);
                }
            }
            break;
        }
        case FUNCTION_CALL_N:
        {
            Symbol* sym = getSymbolFromCallstackUnit(symbolTable,root->node.function_call_node.signature);
            if (sym)
            {
                for (int i=0;i<root->node.function_call_node.parameters->node.block_node.size;i++)
                {
                    interpret(root->node.function_call_node.parameters->node.block_node.statements[i]);
                    Node* parameter_vue = expressionResultNode(root->node.function_call_node.parameters->node.block_node.statements[i]);
                    sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression = parameter_vue;
                }
                enterCall();
                enterScope();
                interpret(sym->value.function_v->node.function_node.parameters);
                returnNodePointer = NULL;
                interpret(sym->value.function_v->node.function_node.block);
    
                switch (root->value_type)
                {
                    case INT_T:
                        root->interpret_result.int_v = returnNodePointer->interpret_result.int_v;
                        
                        break;
                    case FLOAT_T:
                        root->interpret_result.float_v = returnNodePointer->interpret_result.float_v;
                        
                        break;
                    case BOOL_T:
                        root->interpret_result.bool_v = returnNodePointer->interpret_result.bool_v;
                        
                        break;
                    case CHAR_T:
                        root->interpret_result.char_v = returnNodePointer->interpret_result.char_v;
                    
                        break;
                    case STRING_T:
                        root->interpret_result.string_v = returnNodePointer->interpret_result.string_v;
                        
                        break;
                }
                returnNodePointer = NULL;
                exitScope();
                exitCall();
                for (int i=0;i<root->node.function_call_node.parameters->node.block_node.size;i++)
                {
                    free(sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression);
                    sym->value.function_v->node.function_node.parameters->node.decl_block_node.declarations[i]->node.declaration_node.expression = NULL;
                }
            }
            break;
        }
        case RETURN_N:
        {
            interpret(root->node.return_node.expression);
            root->interpret_result = root->node.return_node.expression->interpret_result;
            returnNodePointer = root;
            break;
        }
        case ARRAY_ACCESS_N:
        {
            root->interpret_result.ptr_v = NULL;
            Symbol *sym = getSymbolFromCallstackUnit(symbolTable, root->node.array_access_node.name);
            void* ptr = getPointerToArrayElement(root, 1);
            if (ptr == NULL)
            {
                break;
            }
            switch(sym->value.array_v.type)
            {
                case INT_T:
                {
                    root->interpret_result.int_v = *(int*)ptr;
                    break;
                }
                case CHAR_T:
                {
                    root->interpret_result.char_v = *(char*)ptr;
                    break;
                }
                case BOOL_T:
                {
                    root->interpret_result.bool_v = *(int*)ptr;
                    break;
                }
                case FLOAT_T:
                {
                    root->interpret_result.float_v = *(float*)ptr;
                    break;
                }
                case STRING_T:
                {
                    root->interpret_result.string_v = *(char**)ptr;
                    break;
                }
            }

            break;
        }
    }
}

int main(int argc, char* argv[]){
    if(argc > 1)
        yyin = fopen(argv[1], "r");
    else
        return 0;
    sym_file = fopen("symbol_table.txt","w");
    symbolTable = (CallStackUnit*)malloc(sizeof(CallStackUnit));
    callStack = (CallStack*)malloc(sizeof(CallStack));
    initializeCallstack(callStack);
    initializeCallstackUnit(symbolTable);
    pushCallstack(callStack,symbolTable);
    initializeStack(&stack);
    initializeStack(&currentArraySize);
    initializeDeclarationBlock(&globalDeclarations);
    inGlobalScope = true;
    enterScope();
    inGlobalScope = false;
    yyparse();
}




















