// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "GrammarParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 67 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );
        
    void parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
    , Function* function
    )
    {
        bool is_static = false;
        bool is_symbolic = false;
        bool is_controlled = false;
        
        for( const auto& attribute_name : attribute_names )
        {
            if( attribute_name == "static" )
            {
                if( is_static )
                {
                    driver.error
                    ( loc
                    , "`static` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfStatic
                    );
                    break;
                }
                else
                {
                    is_static = true;
                }
            }
            else if( attribute_name == "symbolic" )
            {
                if( is_symbolic )
                {
                    driver.error
                    ( loc
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                    break;
                }
                else
                {
                    is_symbolic = true;
                }
            }
            else if( attribute_name == "controlled" )
            {
                if( is_controlled )
                {
                    driver.error
                    ( loc
                    , "`controlled` attribute can only be used once per function"
                      , libcasm_fe::Codes::FunctionAttributeMultipleUseOfControlled
                    );
                    break;
                }
                else
                {
                    is_controlled = true;
                }
            }
            else
            {
                driver.error
                ( loc
                , "`"+attribute_name+"` is no valid function attribute, only static, symbolic and controlled are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }
        }
        if( is_static && is_controlled )
        {
            driver.error
            ( loc
            , "attributes `controlled` and `static` are mutually exclusive"
            , libcasm_fe::Codes::FunctionAttributeControlledAndStaticIsInvalid
            );
        }
        
        function->is_static = is_static;
        function->is_symbolic = is_symbolic;
    }

    static Function* createProgramFunction( yy::location& location )
    {
        auto argTypes = { new Type( TypeType::AGENT ) };
        auto retType = new Type( TypeType::RULEREF );
        return new Function( "program", location, argTypes, retType );
    }

#line 147 "GrammarParser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 233 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 83: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.move< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        value.move< std::vector<UpdateNode*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 83: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.copy< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        value.copy< std::vector<UpdateNode*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 55 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 873 "GrammarParser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 83: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        yylhs.value.build< AtomNode* > ();
        break;

      case 118: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 137: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 133: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 89: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 110: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 147: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 141: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 87: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 109: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 142: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 146: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 145: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 111: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 84: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 135: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 123: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 94: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        yylhs.value.build< std::vector<UpdateNode*> > ();
        break;

      case 134: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 122: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& filepath = driver.get_filename();
      
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      
      const std::string& filename_without_extension
          = filename.substr( 0, filename.rfind( "." ) );
      
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, filename_without_extension );
  }
#line 1183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::OPTION );
  }
#line 1209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode( yylhs.location, yystack_[0].value.as< Enum* > () );
  }
#line 1217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new FunctionDefNode( yylhs.location, yystack_[0].value.as< Function* > () );

      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto node = new FunctionDefNode( yylhs.location, yystack_[4].value.as< Function* > () );

      auto initializers = yystack_[1].value.as< std::vector<UpdateNode*> > ();
      for (auto initializer : initializers) {
          initializer->func->name = yystack_[4].value.as< Function* > ()->name;
      }
      node->setInitializers( initializers );

      try
      {
          driver.add( yystack_[4].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[4].value.as< Function* > ();
      }

      yylhs.value.as< AstNode* > () = node;
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Function* > ()->binding_offsets = std::move( driver.binding_offsets );
      driver.binding_offsets.clear();
      
      yylhs.value.as< AstNode* > () = new DerivedDefNode( yylhs.location, yystack_[0].value.as< Function* > () );
      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
      // TODO: check, we trust bison to pass only RuleNodes up
      
      try
      {
          driver.add( reinterpret_cast< RuleNode* >( yystack_[0].value.as< AstNode* > () ) );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
#line 1335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
    auto program = createProgramFunction( yylhs.location );
    try
    {
        driver.add( program );
    }
    catch( const Exception& e )
    {
        driver.error
        ( yylhs.location
        , "multiple definition of 'init' node"
        , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
        );
    }

    // create initial update: program(self) := @identifier
    auto args = new std::vector< ExpressionBase* >;
    args->push_back( new SelfAtom( yylhs.location ) );
    auto programAtom = new FunctionAtom( yylhs.location, program->name, args );
    auto update = new UpdateNode( yylhs.location, programAtom, new RuleAtom( yylhs.location , yystack_[0].value.as< std::string > () ) );

    auto programDef = new FunctionDefNode( yylhs.location, program );
    programDef->setInitializers( { update } );
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, programDef );
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
    auto program = createProgramFunction( yylhs.location );
    try
    {
        driver.add( program );
    }
    catch( const Exception& e )
    {
        driver.error
        ( yylhs.location
        , "multiple definition of 'init' node"
        , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
        );
    }

    // initializer updates don't have function names -> apply the correct name
    auto initializers = yystack_[1].value.as< std::vector<UpdateNode*> > ();
    for (auto initializer : initializers) {
        initializer->func->name = program->name;
    }

    auto programDef = new FunctionDefNode( yylhs.location, program );
    programDef->setInitializers( initializers );
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, programDef );
  }
#line 1395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
      try
      {
          driver.function_table.add(yylhs.value.as< Enum* > ());
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
      }
      for( const std::string& name : yystack_[1].value.as< std::vector<std::string> > () )
      {
          if( yylhs.value.as< Enum* > ()->add_enum_element(name) )
          {
              try
              {
                  driver.function_table.add_enum_element( name, yylhs.value.as< Enum* > () );
              }
              catch( const Exception& e )
              {
                  driver.error
                  ( e.getLocations()
                  , e.what()
                  , e.getErrorCode()
                  );
              }
          }
          else
          {
              driver.error
              ( yylhs.location
              , "name '"
                + name
                + "' already used in enum"
              );
          }
      }
  }
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
      parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > (), function);
      yylhs.value.as< Function* > () = function;
  }
#line 1501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1582 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[0].value.as< std::string > () );
      
      // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
      //               or maybe we should check everything in the typecheckpass?
      if( yystack_[0].value.as< std::string > ().compare( "Bit" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "missing bit-size for Bit type 'Bit(<bitsize>)'"
          , libcasm_fe::Codes::TypeBitSyntaxError
          );
      }
      else if( yystack_[0].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[0].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }      
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > () );
      yylhs.value.as< Type* > ()->bitsize = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->bitsize <= 0 || yylhs.value.as< Type* > ()->bitsize > 256 )
      {
          driver.error
          ( yylhs.location
          , "invalid bit-size for Bit type, must between 1 <= x <= 256"
          , libcasm_fe::Codes::TypeBitSizeIsInvalid
          );
      }
  }
#line 1685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > () );

      if( yystack_[3].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }
      // TODO: FUTURE: PPA: better and generic type checking in the type check pass
      else if( yystack_[3].value.as< std::string > ().compare( "Tuple" ) != 0 )
      {
          driver.error
          ( yylhs.location
          , "unknown type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnknown
          );
      }      
  }
#line 1711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[5].value.as< std::string > () );
      yylhs.value.as< Type* > ()->subrange_start = yystack_[3].value.as< IntegerAtom* > ()->val_;
      yylhs.value.as< Type* > ()->subrange_end = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->subrange_start >= yylhs.value.as< Type* > ()->subrange_end )
      {
          driver.error
          ( yylhs.location
          , "start of subrange must be smaller than the end"
          , libcasm_fe::Codes::TypeIntegerRangedInvalidInterval
          );
      }
  }
#line 1729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[0].value.as< std::vector<UpdateNode*> > ());
  }
#line 1762 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[1].value.as< std::vector<UpdateNode*> > ());
  }
#line 1770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[2].value.as< std::vector<UpdateNode*> > ());
      yylhs.value.as< std::vector<UpdateNode*> > ().push_back(yystack_[0].value.as< UpdateNode* > ());
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = { yystack_[0].value.as< UpdateNode* > () };
  }
#line 1787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "" );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto args = new std::vector< ExpressionBase* >;
      args->push_back(yystack_[2].value.as< ExpressionBase* > ());

      auto function = new FunctionAtom( yylhs.location, "", args );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "", yystack_[3].value.as< std::vector<ExpressionBase*>* > () );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1841 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (),
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1898 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1914 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1922 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1962 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1970 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1978 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 2003 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 2011 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1067 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1075 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1089 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1093 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1097 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1101 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new UnaryExpression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( Builtin::isBuiltin( yystack_[3].value.as< std::string > () ) )
      {
          yylhs.value.as< BaseFunctionAtom* > () = new BuiltinAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
      else
      {
          yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
  }
#line 2270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1223 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1228 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1303 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1315 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1347 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1355 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM )
      {
          yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () ), yystack_[0].value.as< ExpressionBase* > () );
      }
      else
      {
          driver.error
          ( yylhs.location
          , "can only use functions for updates but '"
            + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()
            + "` is a '"
            + type_to_str( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ )
          );
      }
  }
#line 2614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1503 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1543 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2778 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );      
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot push to builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PushNode* > () = new PushNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () ) );
      }
  }
#line 2868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop to builtin '" + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop from builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PopNode* > () = new PopNode
          ( yylhs.location
          , reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () )
          , reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () )
          );
      }
  }
#line 2891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2907 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2911 "GrammarParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -293;

  const signed char Parser::yytable_ninf_ = -107;

  const short int
  Parser::yypact_[] =
  {
      24,  -293,    30,   247,  -293,    33,   -35,    -2,    20,    25,
     -42,   247,  -293,  -293,  -293,  -293,  -293,   102,  -293,   661,
    -293,   -21,   156,    86,     8,    50,    90,  -293,   118,  -293,
    -293,  -293,  -293,   682,    68,   112,   682,   619,   111,  -293,
    -293,  -293,  -293,   153,   155,   147,  -293,   -30,  -293,  -293,
    -293,  -293,  -293,  -293,  -293,  -293,  -293,  -293,   754,  -293,
     136,   682,   -34,   138,   165,   170,   435,   -31,  -293,   172,
     174,   -46,  -293,   661,   682,  -293,  -293,    46,    79,   682,
    -293,  -293,  -293,    16,    16,   682,  -293,  -293,  -293,   186,
     182,   783,  -293,   191,   794,  -293,   640,  -293,   661,   682,
     682,   682,   682,   682,   682,   682,   682,   682,   682,   682,
     703,   682,   682,   682,   169,   921,    84,   198,  -293,   207,
     204,   215,   219,    50,    50,    76,  -293,   435,   435,   682,
     682,   682,  -293,  -293,   194,   195,   435,   -32,   682,   682,
     682,   199,   682,   200,   435,   435,   -26,   201,  -293,  -293,
    -293,  -293,  -293,  -293,  -293,  -293,  -293,  -293,  -293,  -293,
    -293,  -293,  -293,  -293,  -293,  -293,  -293,  -293,     5,   224,
     205,   208,   138,   218,   226,   235,   783,   823,   852,   225,
     682,  -293,  -293,   682,  -293,   242,   921,  -293,   949,   575,
     960,   115,   197,   415,   164,   135,  -293,   237,    17,  -293,
     979,   103,   234,  -293,   682,   138,   138,   152,   228,   -37,
     682,   248,   251,   435,   170,  -293,  -293,  -293,   297,   324,
     921,   921,   921,   168,   290,  -293,   682,   268,   556,   586,
     921,   682,   725,   283,   366,   393,   682,   170,   435,    11,
      90,  -293,  -293,   138,   138,  -293,  -293,  -293,   703,   921,
     881,  -293,   921,   275,  -293,   682,   138,  -293,   -14,   -14,
     265,   276,    51,   921,  -293,   261,  -293,  -293,  -293,  -293,
    -293,  -293,   138,   682,   910,   682,   435,   279,   921,   200,
     200,  -293,  -293,   921,    96,  -293,   170,   435,  -293,  -293,
    -293,  -293,  -293,   682,   921,   280,   138,  -293,  -293,   -14,
     258,   682,   296,   511,   298,   301,   326,   537,  -293,  -293,
     435,   144,  -293,   921,   682,  -293,   304,  -293,   453,  -293,
     435,   682,  -293,   435,  -293,  -293,  -293,  -293,  -293,  -293,
    -293,   305,   537,   299,  -293,   435,   921,  -293,   435,   682,
    -293,   311,  -293,  -293,  -293,   435,  -293,  -293,   482,  -293,
    -293,   435,  -293
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    11,     6,     7,    10,     8,    12,     0,
      13,     0,     0,     0,     0,     0,     0,     4,     0,    64,
      67,    69,    68,     0,     0,     0,     0,     0,     0,    76,
      73,    79,    61,   106,     0,    47,    50,   105,    55,    65,
      66,    60,    70,    71,    72,    59,    63,    62,     0,    54,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
      26,     0,    24,     0,     0,   105,   104,     0,     0,     0,
      74,    77,    80,     0,     0,     0,    81,    75,    78,     0,
      86,    89,    85,     0,    89,    82,     0,    14,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,    32,    36,     0,
      33,    40,     0,     0,     0,     0,   120,     0,     0,     0,
       0,   144,   145,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,     0,   111,   113,
     112,   122,   123,   124,   125,   127,   126,   128,   129,   130,
     109,   110,   131,   132,   133,   134,   135,   136,     0,     0,
       0,    25,     0,     0,    39,     0,     0,     0,     0,     0,
      87,    56,    84,     0,   107,     0,    89,    49,   103,   101,
     102,    90,    91,    96,    97,    98,    92,    93,    94,    52,
      95,    99,   100,    15,     0,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,   139,   140,   169,     0,     0,
     141,   142,   143,     0,     0,   179,     0,   163,     0,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,    29,     0,    38,     9,    57,    58,     0,    88,
       0,   108,    19,     0,    31,     0,     0,    35,     0,     0,
      46,     0,     0,    21,    16,     0,   116,   119,   165,   168,
     167,   172,     0,     0,     0,     0,     0,     0,   147,     0,
       0,   166,   164,   148,     0,   114,     0,     0,    23,    30,
      37,    53,    83,     0,    17,     0,    45,    42,    41,     0,
       0,     0,     0,     0,   161,     0,   170,     0,   176,   177,
       0,     0,   115,    22,     0,    44,     0,   121,     0,   174,
       0,     0,   162,     0,   153,   154,   158,   155,   156,   157,
     159,     0,   151,     0,   117,     0,    20,    43,     0,     0,
     178,     0,   171,   149,   150,     0,   118,   173,     0,   160,
     152,     0,   175
  };

  const short int
  Parser::yypgoto_[] =
  {
    -293,  -293,  -293,  -293,   353,  -293,  -293,  -293,  -293,  -293,
      62,  -293,   125,   158,   300,  -293,   124,   -47,    73,   302,
    -293,   273,    10,  -293,  -292,  -283,  -221,   -27,    55,   -24,
    -293,  -293,  -293,   -36,  -293,   -33,   -43,   -64,  -200,  -293,
    -232,   159,   -60,  -104,  -293,  -293,  -293,  -293,  -293,  -293,
    -293,  -293,    40,  -293,  -293,  -293,  -293,  -293,    -4,  -293,
    -293,  -293,  -293,  -293,  -293,  -293,  -293
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      69,    70,    72,   118,   119,   120,   173,   174,   261,    44,
      45,    46,    75,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    89,    90,    58,    59,   215,   149,    18,
     125,   126,   216,   217,   151,   152,   153,   154,   155,   156,
     157,   158,   331,   332,   333,   159,   160,   161,   218,   162,
     163,   301,   339,   164,   165,   166,   167
  };

  const short int
  Parser::yytable_[] =
  {
      76,    93,   148,    91,    94,   284,   150,    80,    87,    25,
      82,   258,   259,   266,   237,   327,   122,    65,   116,   226,
     286,   168,   172,   147,   328,    96,   -51,     1,   115,    47,
       4,   -51,   225,   121,   258,   259,    60,    26,   285,    40,
     327,   176,   121,  -106,    21,   117,   177,   227,   117,   328,
      80,    87,   178,    82,   311,   238,    80,    87,    66,    67,
     185,   287,    40,   186,    83,    84,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,    22,   200,   201,
     202,   107,   108,    47,   147,   147,   329,   312,    19,    81,
      88,    39,    40,   147,    77,    78,   220,   221,   222,    23,
     233,   147,   147,   298,    24,   228,   229,   230,    47,   232,
     334,   329,    20,    28,   269,   269,    77,    78,   299,    79,
     199,    39,    40,    41,   219,   242,   213,    83,    84,    68,
     269,   269,    81,    88,   204,   346,    64,   214,    81,    88,
     234,   235,   205,    39,    40,    41,   310,   249,    71,   148,
     250,   102,   103,   150,    39,    40,    86,   214,   253,   254,
      83,    84,   260,    85,   103,   105,   106,   107,   108,   109,
     147,   252,   306,    73,   148,   147,   147,   263,   150,   107,
     108,   109,   262,   102,   103,   211,   212,    39,    40,    86,
      95,   147,   147,   274,   335,   147,   289,   105,   278,   107,
     108,   109,   255,   283,    96,   214,    61,    62,    98,   295,
     256,    97,   102,   103,    63,   114,   340,   121,   271,   342,
     123,   124,   294,   148,   170,   302,   272,   150,   107,   108,
     109,    80,    87,   147,   347,   171,   308,   309,   179,   305,
     303,   350,   186,   180,   147,   182,   148,   352,   203,   260,
     150,     5,     6,     7,     8,     9,   206,    10,   291,   207,
     313,   107,   108,   109,   330,   208,   209,   147,   318,   210,
     236,   148,   316,   223,   224,   150,   239,   147,   231,    43,
     147,   336,   102,   103,   240,   341,   243,   241,   186,   330,
     244,   245,   147,   248,   251,   147,   105,   106,   107,   108,
     109,   107,   147,   265,   264,   112,   348,   117,   147,   127,
     268,   128,   273,   129,   130,   131,   132,   133,   134,   275,
     135,   136,   280,   137,   138,   293,   296,   139,   297,   300,
     314,   140,   141,   142,   307,   143,   127,   317,   128,   270,
     129,   130,   131,   132,   133,   134,   319,   135,   136,   321,
     137,   138,   144,   322,   139,   323,   337,   345,   140,   141,
     142,   343,   143,   349,    27,   288,   257,   169,   290,   315,
     145,   187,   344,   267,     0,   175,   146,     0,   127,   144,
     128,     0,   129,   130,   131,   132,   133,   134,     0,   135,
     136,     0,   137,   138,     0,     0,   139,   145,     0,     0,
     140,   141,   142,   146,   143,   127,     0,   128,     0,   129,
     130,   131,   132,   133,   134,     0,   135,   136,     0,   137,
     138,   144,   281,   139,     0,     0,     0,   140,   141,   142,
       0,   143,     0,     0,     0,     0,     0,     0,     0,   145,
       0,     0,     0,     0,     0,   146,     0,   127,   144,   128,
       0,   129,   130,   131,   132,   133,   134,     0,   135,   136,
       0,   137,   138,   102,   103,   139,   145,   282,     0,   140,
     141,   142,   146,   143,     0,   338,     0,   105,   106,   107,
     108,   109,     0,     0,     0,   111,   112,   113,     0,     0,
     144,     0,     0,     0,     0,     0,     0,    99,   100,   101,
       0,   102,   103,   104,   351,     0,     0,     0,   145,     0,
       0,     0,     0,     0,   146,   105,   106,   107,   108,   109,
       0,     0,     0,   111,   112,   113,    99,   100,   101,     0,
     102,   103,   104,     0,     0,     0,   320,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,     0,
       0,     0,   111,   112,   113,    99,   100,   101,     0,   102,
     103,   104,     0,     0,     0,     0,     0,     0,     0,   324,
       0,     0,     0,   105,   106,   107,   108,   109,    30,    31,
      32,   111,   112,   113,   276,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   325,     0,     0,     0,
      99,   100,   101,     0,   102,   103,   104,     0,     0,     0,
       0,     0,    39,    40,    41,   326,    43,   277,   105,   106,
     107,   108,   109,   102,   103,   104,   111,   112,   113,     0,
      99,   100,   101,     0,   102,   103,   104,   105,   106,   107,
     108,   109,     0,     0,     0,   111,   112,   113,   105,   106,
     107,   108,   109,     0,     0,     0,   111,   112,   113,    29,
      30,    31,    32,     0,     0,     0,    33,    34,    35,     0,
      74,     0,    37,    92,     0,     0,     0,     0,     0,    38,
      29,    30,    31,    32,     0,     0,     0,    33,    34,    35,
       0,    74,   184,    37,    39,    40,    41,    42,    43,     0,
      38,    29,    30,    31,    32,     0,     0,     0,    33,    34,
      35,     0,    36,     0,    37,    39,    40,    41,    42,    43,
       0,    38,    29,    30,    31,    32,     0,     0,     0,    33,
      34,    35,     0,    74,     0,    37,    39,    40,    41,    42,
      43,     0,    38,    29,    30,    31,    32,     0,     0,     0,
       0,    34,    35,     0,    74,     0,    37,    39,    40,    41,
      42,    43,   279,    38,     0,     0,     0,     0,     0,    99,
     100,   101,     0,   102,   103,   104,     0,     0,    39,    40,
      41,    42,    43,     0,     0,     0,     0,   105,   106,   107,
     108,   109,     0,     0,     0,   111,   112,   113,    99,   100,
     101,     0,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,     0,   110,     0,   111,   112,   113,    99,   100,   101,
       0,   102,   103,   104,     0,   181,     0,     0,    99,   100,
     101,     0,   102,   103,   104,   105,   106,   107,   108,   109,
       0,     0,     0,   111,   112,   113,   105,   106,   107,   108,
     109,   183,     0,     0,   111,   112,   113,    99,   100,   101,
       0,   102,   103,   104,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
       0,     0,     0,   111,   112,   113,    99,   100,   101,     0,
     102,   103,   104,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,     0,
       0,     0,   111,   112,   113,    99,   100,   101,     0,   102,
     103,   104,     0,     0,     0,   292,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,     0,     0,
       0,   111,   112,   113,    99,   100,   101,     0,   102,   103,
     104,     0,   304,     0,     0,    99,   100,   101,     0,   102,
     103,   104,   105,   106,   107,   108,   109,     0,     0,     0,
     111,   112,   113,   105,   106,   107,   108,   109,     0,     0,
       0,   111,   112,   113,   100,   101,     0,   102,   103,   104,
       0,     0,     0,     0,     0,   100,     0,     0,   102,   103,
     104,   105,   106,   107,   108,   109,     0,     0,     0,   111,
     112,   113,   105,   106,   107,   108,   109,   102,   103,     0,
     111,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,     0,     0,     0,     0,
     112,   113
  };

  const short int
  Parser::yycheck_[] =
  {
      33,    37,    66,    36,    37,   237,    66,    34,    35,    51,
      34,    48,    49,   213,     9,   307,    63,     9,    52,    51,
       9,    52,    68,    66,   307,    51,    56,     3,    61,    19,
       0,    61,   136,    79,    48,    49,    57,    79,   238,    76,
     332,    74,    79,    69,    79,    79,    79,    79,    79,   332,
      77,    78,    85,    77,   286,    50,    83,    84,    50,    51,
      96,    50,    76,    96,    48,    49,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    79,   111,   112,
     113,    64,    65,    73,   127,   128,   307,   287,    55,    34,
      35,    75,    76,   136,    48,    49,   129,   130,   131,    79,
     143,   144,   145,    52,    79,   138,   139,   140,    98,   142,
     310,   332,    79,    11,   218,   219,    48,    49,    67,    51,
     110,    75,    76,    77,   128,   172,    50,    48,    49,    79,
     234,   235,    77,    78,    50,   335,    50,    61,    83,    84,
     144,   145,    58,    75,    76,    77,    50,   180,    58,   213,
     183,    48,    49,   213,    75,    76,    77,    61,   205,   206,
      48,    49,   209,    51,    49,    62,    63,    64,    65,    66,
     213,   204,   276,    55,   238,   218,   219,   210,   238,    64,
      65,    66,   209,    48,    49,   123,   124,    75,    76,    77,
      79,   234,   235,   226,    50,   238,   243,    62,   231,    64,
      65,    66,    50,   236,    51,    61,    50,    51,    61,   256,
      58,    56,    48,    49,    58,    79,   320,    79,    50,   323,
      55,    51,   255,   287,    52,   272,    58,   287,    64,    65,
      66,   258,   259,   276,   338,    61,   279,   280,    52,   275,
     273,   345,   275,    61,   287,    54,   310,   351,    79,   296,
     310,     4,     5,     6,     7,     8,    58,    10,   248,    52,
     293,    64,    65,    66,   307,    61,    51,   310,   301,    50,
      69,   335,   299,    79,    79,   335,    52,   320,    79,    79,
     323,   314,    48,    49,    79,   321,    68,    79,   321,   332,
      64,    56,   335,    68,    52,   338,    62,    63,    64,    65,
      66,    64,   345,    52,    56,    71,   339,    79,   351,    12,
      13,    14,    22,    16,    17,    18,    19,    20,    21,    51,
      23,    24,    39,    26,    27,    50,    61,    30,    52,    68,
      50,    34,    35,    36,    55,    38,    12,    79,    14,    15,
      16,    17,    18,    19,    20,    21,    50,    23,    24,    51,
      26,    27,    55,    52,    30,    29,    52,    58,    34,    35,
      36,    56,    38,    52,    11,   240,   208,    67,   244,   296,
      73,    98,   332,   214,    -1,    73,    79,    -1,    12,    55,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    73,    -1,    -1,
      34,    35,    36,    79,    38,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    -1,    26,
      27,    55,    56,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    12,    55,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    48,    49,    30,    73,    74,    -1,    34,
      35,    36,    79,    38,    -1,    22,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      -1,    48,    49,    50,    22,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    79,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    41,    42,
      43,    70,    71,    72,    28,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      44,    45,    46,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    31,    62,    63,
      64,    65,    66,    48,    49,    50,    70,    71,    72,    -1,
      44,    45,    46,    -1,    48,    49,    50,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    48,    49,    -1,
      51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    52,    53,    75,    76,    77,    78,    79,    -1,
      60,    40,    41,    42,    43,    -1,    -1,    -1,    47,    48,
      49,    -1,    51,    -1,    53,    75,    76,    77,    78,    79,
      -1,    60,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      48,    49,    -1,    51,    -1,    53,    75,    76,    77,    78,
      79,    -1,    60,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    -1,    53,    75,    76,    77,
      78,    79,    37,    60,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    -1,    48,    49,    50,    -1,    -1,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    44,    45,
      46,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    68,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    -1,    52,    -1,    -1,    44,    45,
      46,    -1,    48,    49,    50,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    62,    63,    64,    65,
      66,    67,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    44,    45,    46,    -1,    48,    49,
      50,    -1,    52,    -1,    -1,    44,    45,    46,    -1,    48,
      49,    50,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    45,    46,    -1,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,
      50,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    62,    63,    64,    65,    66,    48,    49,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    83,    84,     0,     4,     5,     6,     7,     8,
      10,    85,    86,    87,    88,    89,    90,    91,   121,    55,
      79,    79,    79,    79,    79,    51,    79,    86,    11,    40,
      41,    42,    43,    47,    48,    49,    51,    53,    60,    75,
      76,    77,    78,    79,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   117,   118,
      57,    50,    51,    58,    50,     9,    50,    51,    79,    92,
      93,    58,    94,    55,    51,   104,   117,    48,    49,    51,
     109,   110,   111,    48,    49,    51,    77,   109,   110,   115,
     116,   117,    54,   115,   117,    79,    51,    56,    61,    44,
      45,    46,    48,    49,    50,    62,    63,    64,    65,    66,
      68,    70,    71,    72,    79,   117,    52,    79,    95,    96,
      97,    79,    99,    55,    51,   122,   123,    12,    14,    16,
      17,    18,    19,    20,    21,    23,    24,    26,    27,    30,
      34,    35,    36,    38,    55,    73,    79,   118,   119,   120,
     124,   126,   127,   128,   129,   130,   131,   132,   133,   137,
     138,   139,   141,   142,   145,   146,   147,   148,    52,    96,
      52,    61,    68,    98,    99,   101,   117,   117,   117,    52,
      61,    52,    54,    67,    52,   115,   117,   103,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   104,
     117,   117,   117,    79,    50,    58,    58,    52,    61,    51,
      50,    92,    92,    50,    61,   119,   124,   125,   140,   140,
     117,   117,   117,    79,    79,   125,    51,    79,   117,   117,
     117,    79,   117,   118,   140,   140,    69,     9,    50,    52,
      79,    79,    99,    68,    64,    56,    52,    52,    68,   117,
     117,    52,   117,    99,    99,    50,    58,    95,    48,    49,
      99,   100,   109,   117,    56,    52,   120,   123,    13,   125,
      15,    50,    58,    22,   117,    51,    28,    31,   117,    37,
      39,    56,    74,   117,   122,   120,     9,    50,    94,    99,
      98,   104,    54,    50,   117,    99,    61,    52,    52,    67,
      68,   143,    99,   117,    52,   115,   125,    55,   118,   118,
      50,   122,   120,   117,    50,   100,   109,    79,   117,    50,
      25,    51,    52,    29,    32,    59,    78,   106,   107,   108,
     118,   134,   135,   136,   120,    50,   117,    52,    22,   144,
     125,   115,   125,    56,   134,    58,   120,   125,   117,    52,
     125,    22,   125
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    88,    89,    90,    90,    90,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   122,
     122,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   127,   128,   128,   129,   130,   131,   132,   133,
     134,   134,   135,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   143,   142,   144,   142,   145,   146,   147,   148
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     1,     1,     1,     5,
       1,     1,     1,     2,     4,     5,     6,     7,     4,     6,
       9,     6,     8,     6,     3,     2,     1,     3,     1,     3,
       4,     3,     1,     1,     2,     3,     1,     3,     2,     1,
       1,     4,     4,     6,     3,     2,     1,     1,     2,     3,
       1,     1,     3,     5,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     5,     3,     2,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     3,     4,     1,
       1,     1,     1,     4,     6,     7,     6,     8,     9,     3,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     2,     3,     3,     6,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       7,     4,     5,     2,     3,     3,     3,     3,     2,     1,
       4,     6,     0,     7,     0,     9,     4,     4,     6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"", "\"impossible\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"endcase\"", "\"print\"", "\"debug\"", "\"push\"",
  "\"into\"", "\"pop\"", "\"from\"", "\"self\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"+\"", "\"-\"",
  "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"floating\"", "\"integer\"", "\"rational\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX", "DERIVED_SYNTAX",
  "FUNCTION_DEFINITION", "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA",
  "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA",
  "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX", "TYPE_SYNTAX_LIST",
  "INITIALIZER_LIST", "INITIALIZER_LIST_NO_COMMA", "INITIALIZER", "ATOM",
  "VALUE", "UNDEFINED", "BOOLEAN", "NUMBER", "INTEGER_NUMBER",
  "FLOATING_NUMBER", "RATIONAL_NUMBER", "RULEREF", "NUMBER_RANGE",
  "LISTCONST", "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
  "FUNCTION_SYNTAX", "SCOPE", "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "SIMPLE_STMT", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "PRINT_SYNTAX", "DEBUG_SYNTAX",
  "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL",
  "CASE_VALUE", "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS",
  "IFTHENELSE", "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX",
  "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   349,   349,   357,   372,   377,   386,   390,   394,   415,
     444,   467,   471,   496,   522,   552,   557,   604,   609,   613,
     617,   621,   625,   633,   639,   646,   650,   658,   663,   672,
     678,   686,   692,   703,   707,   715,   720,   728,   733,   738,
     746,   769,   782,   804,   822,   827,   831,   839,   843,   851,
     856,   864,   869,   877,   886,   890,   894,   898,   902,   911,
     915,   919,   923,   927,   931,   935,   939,   947,   955,   959,
     967,   971,   975,   983,   987,   991,  1000,  1004,  1008,  1017,
    1021,  1025,  1034,  1042,  1050,  1054,  1062,  1066,  1074,  1079,
    1088,  1092,  1096,  1100,  1104,  1108,  1112,  1116,  1120,  1124,
    1128,  1132,  1136,  1140,  1144,  1148,  1156,  1160,  1164,  1179,
    1183,  1191,  1195,  1205,  1209,  1213,  1217,  1222,  1227,  1236,
    1241,  1250,  1258,  1262,  1266,  1270,  1274,  1278,  1282,  1286,
    1290,  1294,  1298,  1302,  1306,  1310,  1314,  1318,  1322,  1342,
    1346,  1354,  1362,  1370,  1374,  1390,  1398,  1406,  1414,  1435,
    1443,  1448,  1457,  1465,  1469,  1474,  1478,  1482,  1486,  1490,
    1498,  1502,  1506,  1510,  1518,  1522,  1530,  1534,  1542,  1547,
    1556,  1560,  1570,  1569,  1587,  1586,  1607,  1622,  1645,  1655
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 3680 "GrammarParser.cpp" // lalr1.cc:1167
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void yy::Parser::error
( const location_type& l
, const std::string& m
)
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );
        
        driver.error
        ( yy::location( yy::position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        );
    }
    else
    {
        driver.error( l, m, libcasm_fe::Codes::SyntaxError );
    }
}


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
