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
#line 87 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }

#line 131 "GrammarParser.cpp" // lalr1.cc:413


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

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 217 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      specification (specification_yyarg)
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
      case 175: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 174: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 176: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 147: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 119: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 113: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 104: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 103: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 105: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 127: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 102: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 88: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 96: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 97: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 129: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 177: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 115: // Terms
      case 154: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 153: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 107: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 87: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 164: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 125: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 139: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 130: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 122: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 121: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 144: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 143: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 140: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 142: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 138: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 152: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 99: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 93: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 100: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 111: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 101: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 86: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 151: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 141: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 124: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 131: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 128: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        value.move< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 172: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 173: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 114: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 146: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
        value.move< std::string > (that.value);
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
      case 175: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 174: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 176: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 147: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 110: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 119: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 113: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 104: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 103: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 105: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 127: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 108: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 102: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 88: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 96: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 97: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 129: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 177: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 115: // Terms
      case 154: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 153: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 107: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 87: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 164: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 165: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 109: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 125: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 106: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 139: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 130: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 122: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 121: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 144: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 143: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 140: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 142: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 138: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 152: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 99: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 93: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 100: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 111: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 101: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 86: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 151: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 141: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 124: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 131: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 128: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        value.copy< UpdateRules::Ptr > (that.value);
        break;

      case 98: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 172: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 173: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 114: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 146: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
        value.copy< std::string > (that.value);
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
            symbol_type yylookahead (yylex ());
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
      case 175: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 174: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 176: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 147: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 110: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 119: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 113: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 104: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 103: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 105: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 127: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 108: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 148: // ComposedType
      case 149: // TupleType
      case 150: // RecordType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 126: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 102: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 89: // AttributedDefinition
      case 90: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 88: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 120: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 91: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 96: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 97: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 129: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 116: // Term
      case 117: // SimpleOrClaspedTerm
      case 118: // OperatorExpression
      case 159: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 177: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 115: // Terms
      case 154: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 153: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 107: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 94: // FunctionDefinition
      case 95: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 87: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 164: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 165: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 123: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 109: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 125: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 106: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 139: // ListLiteral
        yylhs.value.build< ListLiteral::Ptr > ();
        break;

      case 130: // Literal
        yylhs.value.build< Literal::Ptr > ();
        break;

      case 122: // LiteralCallExpression
        yylhs.value.build< LiteralCallExpression::Ptr > ();
        break;

      case 121: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 144: // Assignment
        yylhs.value.build< NamedExpression::Ptr > ();
        break;

      case 143: // Assignments
        yylhs.value.build< NamedExpressions::Ptr > ();
        break;

      case 140: // RangeLiteral
        yylhs.value.build< RangeLiteral::Ptr > ();
        break;

      case 142: // RecordLiteral
        yylhs.value.build< RecordLiteral::Ptr > ();
        break;

      case 138: // ReferenceLiteral
        yylhs.value.build< ReferenceLiteral::Ptr > ();
        break;

      case 152: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 99: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 93: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 100: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 111: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 101: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 86: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 151: // TemplateType
        yylhs.value.build< TemplateType::Ptr > ();
        break;

      case 141: // TupleLiteral
        yylhs.value.build< TupleLiteral::Ptr > ();
        break;

      case 124: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 145: // Types
      case 155: // FunctionParameters
      case 156: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 131: // UndefinedLiteral
        yylhs.value.build< UndefLiteral::Ptr > ();
        break;

      case 128: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 112: // UpdateRule
      case 162: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 160: // MaybeInitially
      case 161: // Initializers
      case 163: // MaybeInitializers
        yylhs.value.build< UpdateRules::Ptr > ();
        break;

      case 98: // UsingDefinition
        yylhs.value.build< UsingDefinition::Ptr > ();
        break;

      case 132: // BooleanLiteral
      case 133: // IntegerLiteral
      case 134: // RationalLiteral
      case 135: // DecimalLiteral
      case 136: // BinaryLiteral
      case 137: // StringLiteral
        yylhs.value.build< ValueLiteral::Ptr > ();
        break;

      case 172: // VariableBinding
        yylhs.value.build< VariableBinding::Ptr > ();
        break;

      case 173: // VariableBindings
        yylhs.value.build< VariableBindings::Ptr > ();
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 157: // Parameters
      case 158: // MaybeParameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        yylhs.value.build< VariableDefinitions::Ptr > ();
        break;

      case 114: // WhileRule
        yylhs.value.build< WhileRule::Ptr > ();
        break;

      case 146: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 73: // "binary"
      case 74: // "hexadecimal"
      case 75: // "integer"
      case 76: // "rational"
      case 77: // "decimal"
      case 78: // "string"
      case 79: // "identifier"
        yylhs.value.build< std::string > ();
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
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< UsingDefinition::Ptr > ();
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< VariableDefinitions::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1653 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 508 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< UpdateRules::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
              asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1835 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1843 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1859 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< WhileRule::Ptr > ();
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1895 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1919 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1935 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1951 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1979 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinitions::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2003 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2011 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2019 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2027 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2035 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< CallExpression::Ptr > () );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2131 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2139 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2147 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2155 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2163 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2171 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LiteralCallExpression::Ptr > ();
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Literal::Ptr > ();
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< ValueLiteral::Ptr > () );
  }
#line 2461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< CallExpression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[2].value.as< VariableBindings::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinitions::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< UndefLiteral::Ptr > ();
  }
#line 2525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ValueLiteral::Ptr > ();
  }
#line 2573 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1160 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ReferenceLiteral::Ptr > ();
  }
#line 2581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< ListLiteral::Ptr > ();
  }
#line 2589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RangeLiteral::Ptr > ();
  }
#line 2597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< TupleLiteral::Ptr > ();
  }
#line 2605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Literal::Ptr > () = yystack_[0].value.as< RecordLiteral::Ptr > ();
  }
#line 2613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 2621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1197 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
  }
#line 2639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
  }
#line 2752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1315 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListLiteral::Ptr > () = nullptr;
  }
#line 2768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
  }
#line 2786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as< NamedExpressions::Ptr > () );
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = yystack_[2].value.as< NamedExpressions::Ptr > ();
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as< NamedExpression::Ptr > () );
      yylhs.value.as< NamedExpressions::Ptr > () = assignments;
  }
#line 2814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< TemplateType::Ptr > ();
  }
#line 2866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2898 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Tuple" );
      auto subTypes = yystack_[3].value.as< Types::Ptr > ();
      subTypes->add( yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes );
  }
#line 2917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = Ast::make< Identifier >( yylhs.location, "Record" );
      auto namedSubTypes = yystack_[3].value.as< VariableDefinitions::Ptr > ();
      namedSubTypes->add( yystack_[1].value.as< VariableDefinition::Ptr > () );

      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      auto subTypes = Ast::make< Types >( yylhs.location );
      for( const auto& namedSubType : *namedSubTypes )
      {
          identifiers->add( namedSubType->identifier() );
          subTypes->add( namedSubType->variableType() );
      }

      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, asIdentifierPath( identifier ), subTypes, identifiers );
  }
#line 2937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 3006 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 3014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = parameters;
  }
#line 3042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = yystack_[1].value.as< VariableDefinitions::Ptr > ();
  }
#line 3050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1559 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = nullptr;
  }
#line 3058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1563 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinitions::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 3066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 3074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
  }
#line 3082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[1].value.as< UpdateRules::Ptr > ();
  }
#line 3090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< UpdateRules::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< UpdateRules >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< UpdateRules::Ptr > () = initializers;
  }
#line 3118 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< TupleLiteral::Ptr > ()->expressions() );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = yystack_[0].value.as< UpdateRules::Ptr > ();
  }
#line 3160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRules::Ptr > () = Ast::make< UpdateRules >( yylhs.location );
  }
#line 3168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 3176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 3184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto path = yystack_[2].value.as< IdentifierPath::Ptr > ();
      path->addIdentifier( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = path;
  }
#line 3194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 3219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = variables;
  }
#line 3239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = yystack_[2].value.as< VariableDefinitions::Ptr > ();
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1746 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1754 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as< VariableDefinition::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = yystack_[2].value.as< VariableBindings::Ptr > ();
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as< VariableBinding::Ptr > () );
      yylhs.value.as< VariableBindings::Ptr > () = variableBindings;
  }
#line 3331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[1].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< BasicAttribute::Ptr > ();
  }
#line 3359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[1].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = nullptr;
  }
#line 3375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3391 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3395 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -237;

  const short int Parser::yytable_ninf_ = -170;

  const short int
  Parser::yypact_[] =
  {
      19,  -237,    13,    37,   171,    25,  -237,    -7,  -237,  -237,
      26,     4,    35,  -237,  -237,   -15,    -2,    -2,    -2,    -2,
      -2,   136,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
     184,  -237,  -237,  -237,    -9,    -9,    -9,    26,    -9,  -237,
    -237,  -237,    26,  1523,  1523,  1043,   917,    -2,  -237,  -237,
    -237,  -237,  -237,  -237,  2220,    27,  -237,   -12,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,    30,  -237,  -237,  1509,    41,    10,    87,    10,
      95,    98,  -237,  -237,   120,  -237,  -237,   137,  -237,     3,
      -9,    29,  -237,    32,  1770,    33,  -237,  -237,  -237,   116,
     127,  1982,   111,  -237,   133,   138,  -237,   147,  2016,    41,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    -3,    -1,   980,
    -237,    -2,  -237,  1043,  2220,   132,   130,  -237,   148,     6,
     142,   164,   104,    -3,    -3,    -3,    26,    26,    -9,  -237,
      26,    -9,    26,    26,    26,  -237,    26,  -237,  -237,    -2,
      26,  -237,  -237,    26,    26,  2294,  2288,   524,  2254,    48,
      48,   467,   174,   174,   140,   140,   140,  -237,  2254,   467,
     174,   174,    -3,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,   103,  -237,   -12,   169,  -237,   112,  2220,  -237,  2050,
      26,  1509,  -237,   173,   115,   120,  -237,  -237,    -9,    -3,
       7,  1383,    -3,  -237,  -237,   162,   156,  -237,  2220,  2220,
    -237,  1914,  -237,  1612,  1845,  1948,  2084,  -237,   133,  2220,
    2220,  2118,   168,  -237,   120,   170,  -237,    -3,    26,  -237,
    -237,  -237,   159,  2220,  -237,  -237,  -237,    -9,  -237,   185,
    -237,  -237,   118,  -237,    -9,   587,   655,  -237,    -9,    -9,
      -9,  1383,    26,    26,    26,   723,   791,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
     172,   -16,   180,   195,    -3,    -3,    26,    26,    26,    26,
    -237,  -237,    -3,    -2,    24,   141,   183,  -237,    26,  -237,
      26,  -237,     7,  -237,   236,  -237,  1111,   237,  1179,    39,
      72,    77,  -237,  1808,  1880,  1652,   203,  1247,   182,  1315,
      26,  1383,  -237,   247,  2220,  2220,  2220,  2220,   215,   219,
      -3,  -237,    -3,  2220,  2220,  -237,  -237,  -237,  -237,  -237,
    -237,  1383,    26,    26,  1383,   217,  1383,  -237,  -237,  -237,
    -237,  2220,  -237,   218,   258,  -237,  -237,  -237,   213,  -237,
    1572,  1692,   248,   854,  -237,    26,   222,  -237,  -237,  1383,
      26,  1383,  1383,   224,   225,   226,  -237,  1446,  2152,  2186,
    1509,  -237,  1732,  -237,  -237,  -237,  1383,  1383,  -237,  -237,
    1383,  -237,   228,  1383,  -237,  -237,  -237,  -237,  -237
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   207,     0,   189,   188,
     211,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     3,   206,   210,     0,     0,     0,     0,     0,   131,
     133,   132,     0,     0,     0,     0,     0,     0,   137,   138,
     134,   135,   136,   139,   212,    71,    73,    81,   104,   105,
      82,   106,    72,    74,    75,    76,    77,    78,    83,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   191,   107,   208,   209,   187,    21,   176,     0,   176,
       0,     0,     5,     7,   193,   200,   192,     0,   205,     0,
       0,     0,   195,     0,     0,     0,   103,    84,    85,     0,
       0,    70,     0,   148,   191,     0,   141,     0,    70,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,     0,   108,     0,   183,   129,   186,   182,     0,     0,
       0,     0,     0,     0,   171,     0,     0,     0,     0,   199,
       0,     0,     0,     0,     0,    80,     0,    79,   146,     0,
       0,   143,   142,     0,     0,   100,    98,    99,   102,    86,
      87,    93,    94,    95,    88,    89,    90,    91,   101,    92,
      96,    97,     0,   113,   152,   153,   158,   159,   154,   155,
     156,   157,   111,   109,     0,   167,     0,    70,   190,    70,
       0,     0,    22,     0,     0,     0,   202,   173,     0,     0,
       0,     0,     0,    28,   169,   170,     0,   198,   203,   114,
     204,     0,   194,     0,     0,     0,    69,   147,     0,   149,
      69,     0,     0,   151,   191,     0,   197,   171,     0,   110,
     166,   165,    79,   185,   181,   175,   174,     0,   201,     0,
      25,    27,     0,    23,     0,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    67,   104,     0,     0,     0,     0,     0,     0,     0,
     145,   144,     0,     0,     0,   151,     0,   164,     0,   172,
       0,    15,     0,    24,     0,    42,     0,     0,     0,     0,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,   178,   117,   116,   115,   118,   150,   196,
       0,   162,     0,   184,    16,    26,    65,    63,    41,    61,
      59,     0,     0,     0,     0,     0,     0,    60,    58,    64,
      62,    66,    18,     0,   180,   160,   161,   150,     0,    53,
       0,     0,    44,     0,    68,     0,     0,    19,   163,     0,
       0,     0,     0,     0,     0,     0,    52,     0,     0,     0,
     187,    54,     0,    56,    45,    47,     0,     0,    46,    51,
       0,   177,     0,     0,    48,    49,    50,   179,    55
  };

  const short int
  Parser::yypgoto_[] =
  {
    -237,  -237,  -237,  -237,   254,   249,  -237,  -237,  -237,  -237,
    -237,   -32,  -237,  -237,   246,  -236,  -237,  -237,  -237,  -106,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
     -41,   -10,   -25,  -237,   152,   160,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,   144,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,   -81,  -237,  -237,   114,
      38,   102,  -237,  -237,  -237,  -237,  -237,  -237,  -237,   -69,
    -237,    43,  -237,   206,  -237,  -237,  -237,    73,   -94,   192,
      50,   199,   -26,  -237,  -129,   -23,    44,   145,    40,     2,
      -4,  -237,  -237
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   261,   262,    29,   315,   316,   278,   279,   280,   386,
     387,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     110,   144,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,   112,   113,
     242,   193,   194,   195,   196,   197,   198,   199,   200,   140,
     225,   226,   214,   150,   364,   377,   146,   147,   148,    81,
      82,    95,   101,   245,    96,   102,   217,    98,    99,   100,
       6,    11,    12
  };

  const short int
  Parser::yytable_[] =
  {
      54,    32,     5,     8,   145,   117,    30,   213,   260,     8,
     103,    97,   105,   142,     7,     8,     8,     8,   107,   108,
     216,   157,     1,    30,     8,     8,    32,   104,    31,   139,
     318,     8,   106,   139,    85,   111,   118,    13,     2,   327,
     329,    33,   192,    34,     8,    35,    36,   160,   -81,    37,
     162,   164,    83,     2,     2,   149,    38,   351,   158,   137,
      39,    40,    41,   246,     9,    86,     2,    42,    43,    44,
       9,    45,     2,    46,    50,   139,     9,     9,     9,   340,
      47,   341,   141,    84,   161,     9,     9,   161,   161,   258,
     352,   138,     9,   141,   158,   353,    32,   119,   206,    48,
      49,    50,    51,    52,    53,     9,   129,   130,   131,   132,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   161,   216,   207,
     145,   151,   161,   209,   249,    97,    -2,    14,   232,   153,
      15,    16,    17,    18,    19,    20,   228,   229,   221,   154,
     231,   218,   233,   234,   235,   141,   236,   168,   251,   247,
     239,   256,   165,   240,   241,   248,   169,   173,   311,   222,
     257,   155,    14,   312,   339,    15,    16,    17,    18,    19,
      20,   156,   166,     2,   170,   211,   171,   201,    15,    16,
      17,    18,    19,    20,    10,   172,   290,   210,   212,  -169,
     253,   132,   173,   201,   201,   201,  -169,   219,    87,    88,
      89,    90,    91,   220,    32,   250,   124,   125,     2,   255,
     294,   295,   264,   302,   308,   303,    94,    94,    94,   310,
      94,     2,   129,   130,   131,   132,   138,   114,   307,   331,
     290,   290,   201,   320,   321,    97,   290,   330,   342,   346,
     290,   290,   349,   357,   359,   223,   224,   227,   363,   218,
      32,   365,   323,   324,   325,   366,   373,   375,   376,   201,
     378,   390,   201,   382,   395,    92,   396,   397,   407,    93,
     345,   399,   202,   237,   254,   304,   334,   335,   336,   337,
     306,   290,    94,   290,   243,   152,   402,   201,   343,   159,
     344,   309,   290,   230,   290,     0,   290,     0,   319,   145,
       0,     0,     0,     0,   264,     0,     0,     0,     0,     0,
     361,   259,     0,     0,   293,     0,   290,     0,     0,   290,
     203,   290,     0,   208,     0,   114,     0,     0,     0,     0,
       0,   215,   370,   371,   201,   201,     0,     0,     0,   305,
      94,     0,   201,    94,   290,     0,   290,   290,     0,     0,
       0,   238,     0,   388,     0,   389,     0,     0,     0,     0,
     392,   290,   290,   291,     0,   290,     0,   388,   290,     0,
       0,   292,     0,     0,   244,     0,     0,     0,     0,     0,
     201,     0,   201,     0,     0,     0,   332,   333,     0,     0,
       0,     0,     0,     0,   338,     0,     0,     0,     0,     0,
     215,     0,   263,     0,     0,     0,     0,   291,   291,     0,
       0,     0,     0,   291,     0,   292,   292,   291,   291,     0,
       0,   292,     0,     0,     0,   292,   292,     0,     0,     0,
       0,     0,   367,     0,   368,     0,     0,     0,     0,   215,
       0,     0,     0,     0,     0,     0,   313,     0,     0,     0,
      94,    94,    94,     0,     0,     0,     0,   277,   291,     0,
     291,     0,     0,     0,     0,     0,   292,     0,   292,   291,
       0,   291,     0,   291,     0,     0,     0,   292,     0,   292,
       0,   292,     0,     0,     0,   215,     0,     0,     0,     0,
       0,     0,     0,   291,   263,     0,   291,     0,   291,   124,
     125,   292,     0,     0,   292,     0,   292,   322,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,     0,
       0,   291,     0,   291,   291,     0,   135,   136,     0,   292,
       0,   292,   292,     0,     0,     0,     0,     0,   291,   291,
       0,     0,   291,     0,     0,   291,   292,   292,     0,     0,
     292,   120,   348,   292,   348,     0,   124,   125,   126,     0,
       0,     0,     0,   348,     0,   348,     0,   362,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,   314,     0,
       0,     0,   134,   135,   136,     0,     0,   369,     0,   265,
     372,   266,   374,   267,   268,     8,   269,   270,   271,     0,
     272,     0,     0,   273,     0,     0,     0,     0,     0,     0,
     274,    39,    40,    41,     0,   391,     0,   393,   394,    43,
      44,     0,    45,     0,    46,     0,   275,     0,     0,     0,
       0,    47,   404,   405,     0,     0,   406,     0,     0,   408,
       0,     0,     0,     0,     0,     0,   317,     0,   276,     0,
      48,    49,    50,    51,    52,    53,     9,   265,     0,   266,
       0,   267,   268,     8,   269,   270,   271,     0,   272,     0,
       0,   273,     0,     0,     0,     0,     0,     0,   274,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   275,     0,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   326,     0,   276,     0,    48,    49,
      50,    51,    52,    53,     9,   265,     0,   266,     0,   267,
     268,     8,   269,   270,   271,     0,   272,     0,     0,   273,
       0,     0,     0,     0,     0,     0,   274,    39,    40,    41,
       0,     0,     0,     0,     0,    43,    44,     0,    45,     0,
      46,     0,   275,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,     0,   276,     0,    48,    49,    50,    51,
      52,    53,     9,   265,     0,   266,     0,   267,   268,     8,
     269,   270,   271,     0,   272,     0,     0,   273,     0,     0,
       0,     0,     0,     0,   274,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     275,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   383,     0,     0,     0,     0,
       0,     0,   276,     0,    48,    49,    50,    51,    52,    53,
       9,    34,     8,    35,    36,     0,     0,    37,     0,     0,
       0,     0,   384,     0,    38,     0,     0,     0,    39,    40,
      41,     0,     0,     0,     0,    42,    43,    44,     0,    45,
       0,    46,     0,     0,     0,     0,     0,   385,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,     0,
       0,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53,     9,    34,     8,    35,    36,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,    39,    40,    41,     0,     0,     0,     0,    42,    43,
      44,     0,    45,     0,    46,   116,     0,     0,     0,     0,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,     0,     0,     0,     0,     0,     0,     0,     0,
      48,    49,    50,    51,    52,    53,     9,    34,     8,    35,
      36,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    45,   205,    46,     0,     0,
       0,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,    48,    49,    50,    51,    52,    53,     9,
      34,     8,    35,    36,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,    39,    40,    41,
       0,     0,     0,     0,    42,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    49,    50,    51,
      52,    53,     9,   265,   347,   266,     0,   267,   268,     8,
     269,   270,   271,     0,   272,     0,     0,   273,     0,     0,
       0,     0,     0,     0,   274,    39,    40,    41,     0,     0,
       0,     0,     0,    43,    44,     0,    45,     0,    46,     0,
     275,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,    48,    49,    50,    51,    52,    53,
       9,   265,     0,   266,   350,   267,   268,     8,   269,   270,
     271,     0,   272,     0,     0,   273,     0,     0,     0,     0,
       0,     0,   274,    39,    40,    41,     0,     0,     0,     0,
       0,    43,    44,     0,    45,     0,    46,     0,   275,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     276,     0,    48,    49,    50,    51,    52,    53,     9,   265,
       0,   266,     0,   267,   268,     8,   269,   270,   271,     0,
     272,     0,     0,   273,     0,     0,     0,     0,     0,     0,
     274,    39,    40,    41,     0,     0,     0,     0,     0,    43,
      44,     0,    45,     0,    46,     0,   275,   358,     0,     0,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
      48,    49,    50,    51,    52,    53,     9,   265,     0,   266,
       0,   267,   268,     8,   269,   270,   271,     0,   272,     0,
       0,   273,     0,     0,     0,     0,     0,     0,   274,    39,
      40,    41,     0,     0,     0,     0,     0,    43,    44,     0,
      45,     0,    46,     0,   275,     0,     0,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   276,   360,    48,    49,
      50,    51,    52,    53,     9,   265,     0,   266,     0,   267,
     268,     8,   269,   270,   271,     0,   272,     0,     0,   273,
       0,     0,     0,     0,     0,     0,   274,    39,    40,    41,
       0,     0,     0,     0,     0,    43,    44,     0,    45,     0,
      46,     0,   275,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,    48,    49,    50,    51,
      52,    53,     9,    34,     8,    35,    36,     0,     0,    37,
       0,     0,     0,     0,   384,     0,    38,     0,     0,     0,
      39,    40,    41,     0,     0,     0,     0,    42,    43,    44,
       0,    45,     0,    46,     0,     0,   398,     0,     0,   385,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,    52,    53,     9,    34,     8,    35,    36,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     8,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,   143,     0,    46,    39,    40,    41,
       0,     0,     0,    47,     0,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,    47,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    53,     9,     0,
       0,     0,     0,     0,   379,     0,    48,    49,    50,    51,
      52,    53,     9,   380,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   297,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   356,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   381,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   403,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,   163,     0,     0,     0,   133,     0,
     134,   135,   136,     0,     0,     0,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   354,     0,     0,     0,   133,     0,   134,   135,
     136,     0,     0,     0,     0,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     298,     0,     0,     0,   133,     0,   134,   135,   136,     0,
       0,     0,   120,   121,   122,   123,     0,   124,   125,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   355,     0,     0,
       0,   133,     0,   134,   135,   136,     0,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,   296,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,   299,
     133,     0,   134,   135,   136,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   120,
     121,   122,   123,     0,   124,   125,   126,     0,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,   133,     0,
     134,   135,   136,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,   174,
       0,     0,   133,     0,   134,   135,   136,   120,   121,   122,
     123,     0,   124,   125,   126,     0,   252,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,   123,     0,   124,   125,   126,     0,
     300,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   120,   121,   122,   123,     0,
     124,   125,   126,     0,     0,     0,   301,     0,     0,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   120,
     121,   122,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,     0,   400,     0,     0,     0,     0,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,   133,     0,
     134,   135,   136,   120,   121,   122,   123,     0,   124,   125,
     126,     0,     0,     0,     0,     0,   401,     0,     0,     0,
       0,     0,   127,   128,   129,   130,   131,   132,     0,     0,
       0,     0,   133,     0,   134,   135,   136,   120,   121,   122,
     123,     0,   124,   125,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,     0,     0,     0,     0,   133,     0,   134,   135,
     136,   120,   121,   122,     0,     0,   124,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   120,     0,   122,     0,     0,
     124,   125,   126,     0,     0,     0,   124,   125,   126,     0,
       0,     0,     0,     0,   127,   128,   129,   130,   131,   132,
     127,   128,   129,   130,   131,   132,   134,   135,   136,     0,
       0,     0,   134,   135,   136
  };

  const short int
  Parser::yycheck_[] =
  {
      10,     5,     0,    18,    85,    46,     4,     1,     1,    18,
      36,    34,    38,    82,     1,    18,    18,    18,    43,    44,
     149,    18,     3,    21,    18,    18,    30,    37,     3,    45,
     266,    18,    42,    45,    49,    45,    46,     0,    47,   275,
     276,    48,    45,    17,    18,    19,    20,    18,    64,    23,
      18,    18,    48,    47,    47,    45,    30,    18,    55,    32,
      34,    35,    36,   192,    79,    15,    47,    41,    42,    43,
      79,    45,    47,    47,    75,    45,    79,    79,    79,    55,
      54,    57,    52,    48,    55,    79,    79,    55,    55,   218,
      18,    64,    79,    52,    55,    18,   100,    47,   139,    73,
      74,    75,    76,    77,    78,    79,    58,    59,    60,    61,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,    55,   257,   139,
     211,    44,    55,   143,   203,   158,     0,     1,   161,    44,
       4,     5,     6,     7,     8,     9,   156,   157,    44,    51,
     160,   149,   162,   163,   164,    52,   166,    46,    46,    56,
     170,    46,    46,   173,   174,    62,    55,    55,    50,    65,
      55,    51,     1,    55,   303,     4,     5,     6,     7,     8,
       9,    44,    55,    47,    51,    55,    48,   137,     4,     5,
       6,     7,     8,     9,     2,    48,   221,    65,    50,    58,
     210,    61,    55,   153,   154,   155,    65,    65,    16,    17,
      18,    19,    20,    49,   218,    46,    42,    43,    47,    46,
      58,    65,   220,    55,    65,    55,    34,    35,    36,    44,
      38,    47,    58,    59,    60,    61,    64,    45,   248,    44,
     265,   266,   192,   269,   270,   268,   271,    67,    65,    13,
     275,   276,    15,    50,    72,   153,   154,   155,    11,   257,
     264,    46,   272,   273,   274,    46,    49,    49,    10,   219,
      57,    49,   222,    25,    50,    21,    51,    51,    50,    30,
     312,   387,   138,   169,   211,   247,   296,   297,   298,   299,
     247,   316,   100,   318,   192,    89,   390,   247,   308,   100,
     310,   257,   327,   158,   329,    -1,   331,    -1,   268,   390,
      -1,    -1,    -1,    -1,   312,    -1,    -1,    -1,    -1,    -1,
     330,   219,    -1,    -1,   222,    -1,   351,    -1,    -1,   354,
     138,   356,    -1,   141,    -1,   143,    -1,    -1,    -1,    -1,
      -1,   149,   352,   353,   294,   295,    -1,    -1,    -1,   247,
     158,    -1,   302,   161,   379,    -1,   381,   382,    -1,    -1,
      -1,   169,    -1,   373,    -1,   375,    -1,    -1,    -1,    -1,
     380,   396,   397,   221,    -1,   400,    -1,   387,   403,    -1,
      -1,   221,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,
     340,    -1,   342,    -1,    -1,    -1,   294,   295,    -1,    -1,
      -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,    -1,    -1,
     218,    -1,   220,    -1,    -1,    -1,    -1,   265,   266,    -1,
      -1,    -1,    -1,   271,    -1,   265,   266,   275,   276,    -1,
      -1,   271,    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,
      -1,    -1,   340,    -1,   342,    -1,    -1,    -1,    -1,   257,
      -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,
     268,   269,   270,    -1,    -1,    -1,    -1,   221,   316,    -1,
     318,    -1,    -1,    -1,    -1,    -1,   316,    -1,   318,   327,
      -1,   329,    -1,   331,    -1,    -1,    -1,   327,    -1,   329,
      -1,   331,    -1,    -1,    -1,   303,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   351,   312,    -1,   354,    -1,   356,    42,
      43,   351,    -1,    -1,   354,    -1,   356,   271,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,   379,    -1,   381,   382,    -1,    69,    70,    -1,   379,
      -1,   381,   382,    -1,    -1,    -1,    -1,    -1,   396,   397,
      -1,    -1,   400,    -1,    -1,   403,   396,   397,    -1,    -1,
     400,    37,   316,   403,   318,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,   327,    -1,   329,    -1,   331,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,     1,    -1,
      -1,    -1,    68,    69,    70,    -1,    -1,   351,    -1,    12,
     354,    14,   356,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,   379,    -1,   381,   382,    42,
      43,    -1,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    54,   396,   397,    -1,    -1,   400,    -1,    -1,   403,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    71,    -1,    73,    74,
      75,    76,    77,    78,    79,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    71,    -1,    73,    74,    75,    76,
      77,    78,    79,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,    30,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    -1,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    12,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,    -1,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    74,    75,    76,    77,    78,
      79,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    45,    -1,    47,    -1,    49,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73,    74,    75,    76,    77,    78,    79,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    45,    -1,    47,    -1,    49,    50,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      73,    74,    75,    76,    77,    78,    79,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      45,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    12,    -1,    14,    -1,    16,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    49,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    73,    74,    75,    76,
      77,    78,    79,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,    -1,    -1,    50,    -1,    -1,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    17,    18,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    18,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      41,    42,    43,    -1,    45,    -1,    47,    34,    35,    36,
      -1,    -1,    -1,    54,    -1,    42,    43,    -1,    45,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    73,    74,    75,    76,
      77,    78,    79,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    22,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    22,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    22,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    22,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    24,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    24,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      25,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    -1,
      -1,    -1,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    27,    -1,    -1,
      -1,    66,    -1,    68,    69,    70,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    29,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    31,
      66,    -1,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    63,
      -1,    -1,    66,    -1,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    68,    69,    70,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    68,    69,    70,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      68,    69,    70,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    68,    69,    70,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    68,    69,
      70,    37,    38,    39,    -1,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    37,    -1,    39,    -1,    -1,
      42,    43,    44,    -1,    -1,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      56,    57,    58,    59,    60,    61,    68,    69,    70,    -1,
      -1,    -1,    68,    69,    70
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    86,    87,   174,   175,     1,    18,    79,
     164,   176,   177,     0,     1,     4,     5,     6,     7,     8,
       9,    88,    89,    90,    91,    92,    93,    94,    95,    98,
     174,     3,   175,    48,    17,    19,    20,    23,    30,    34,
      35,    36,    41,    42,    43,    45,    47,    54,    73,    74,
      75,    76,    77,    78,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   164,   165,    48,    48,    49,   165,   164,   164,   164,
     164,   164,    89,    90,   164,   166,   169,   170,   172,   173,
     174,   167,   170,   167,   116,   167,   116,   117,   117,     1,
     115,   116,   143,   144,   164,     1,    48,   115,   116,   165,
      37,    38,    39,    40,    42,    43,    44,    56,    57,    58,
      59,    60,    61,    66,    68,    69,    70,    32,    64,    45,
     154,    52,   154,    45,   116,   141,   161,   162,   163,    45,
     158,    44,   158,    44,    51,    51,    44,    18,    55,   166,
      18,    55,    18,    24,    18,    46,    55,    46,    46,    55,
      51,    48,    48,    55,    63,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,    45,   146,   147,   148,   149,   150,   151,   152,
     153,   165,   133,   164,     1,    46,   115,   116,   164,   116,
      65,    55,    50,     1,   157,   164,   169,   171,   174,    65,
      49,    44,    65,   146,   146,   155,   156,   146,   116,   116,
     172,   116,   170,   116,   116,   116,   116,   144,   164,   116,
     116,   116,   145,   146,   164,   168,   169,    56,    62,   154,
      46,    46,    46,   116,   162,    46,    46,    55,   169,   146,
       1,    96,    97,   164,   174,    12,    14,    16,    17,    19,
      20,    21,    23,    26,    33,    49,    71,    99,   101,   102,
     103,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     117,   119,   120,   146,    58,    65,    29,    22,    25,    31,
      46,    48,    55,    55,   145,   146,   156,   116,    65,   171,
      44,    50,    55,   164,     1,    99,   100,     1,   100,   173,
     167,   167,    99,   116,   116,   116,     1,   100,     1,   100,
      67,    44,   146,   146,   116,   116,   116,   116,   146,   169,
      55,    57,    65,   116,   116,    96,    13,    13,    99,    15,
      15,    18,    18,    18,    24,    27,    22,    50,    50,    72,
      72,   116,    99,    11,   159,    46,    46,   146,   146,    99,
     116,   116,    99,    49,    99,    49,    10,   160,    57,    22,
      31,    22,    25,     1,    28,    53,   104,   105,   116,   116,
      49,    99,   116,    99,    99,    50,    51,    51,    50,   104,
      51,    50,   163,    22,    99,    99,    99,    50,    99
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    85,    86,    87,    87,    88,    88,    89,    89,    89,
      90,    90,    90,    90,    90,    91,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   107,   107,   108,   109,   110,   110,
     110,   110,   111,   111,   111,   111,   112,   113,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   120,   120,   121,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   132,   132,   133,   134,   135,   136,   136,   137,
     138,   139,   139,   139,   140,   141,   142,   143,   143,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   148,   148,
     149,   150,   151,   152,   153,   154,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   162,   162,   163,   163,   164,   164,
     165,   165,   166,   166,   167,   167,   168,   168,   169,   170,
     170,   171,   171,   172,   173,   173,   174,   174,   175,   175,
     175,   176,   177
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     6,     7,     5,     7,     8,
       1,     2,     4,     1,     2,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     4,     6,     6,     6,     3,     3,
       3,     2,     1,     4,     6,     8,     6,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     2,     3,
       4,     3,     2,     3,     4,     6,     6,     6,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     3,     5,     5,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     4,     6,     3,     3,     3,     2,     3,     1,
       1,     0,     3,     1,     3,     3,     0,     4,     0,     4,
       0,     3,     1,     1,     5,     3,     1,     0,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     3,     2,
       1,     2,     1,     3,     3,     1,     2,     1,     3,     3,
       3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"as\"", "\"while\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"::\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"decimal\"", "\"string\"", "\"identifier\"", "BASIC_TYPE", "CALL",
  "UPLUS", "UMINUS", "CALL_WITHOUT_ARGS", "$accept", "Specification",
  "Header", "Definitions", "AttributedDefinition", "Definition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "UsingDefinition", "Rule",
  "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "WhileRule",
  "Terms", "Term", "SimpleOrClaspedTerm", "OperatorExpression",
  "CallExpression", "DirectCallExpression", "MethodCallExpression",
  "LiteralCallExpression", "IndirectCallExpression",
  "TypeCastingExpression", "LetExpression", "ConditionalExpression",
  "ChooseExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "Literal", "UndefinedLiteral",
  "BooleanLiteral", "IntegerLiteral", "RationalLiteral", "DecimalLiteral",
  "BinaryLiteral", "StringLiteral", "ReferenceLiteral", "ListLiteral",
  "RangeLiteral", "TupleLiteral", "RecordLiteral", "Assignments",
  "Assignment", "Types", "Type", "BasicType", "ComposedType", "TupleType",
  "RecordType", "TemplateType", "RelationType", "FixedSizedType",
  "Arguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifier",
  "IdentifierPath", "Variable", "AttributedVariables", "TypedVariables",
  "TypedVariable", "AttributedVariable", "TypedAttributedVariable",
  "VariableBinding", "VariableBindings", "Attributes", "Attribute",
  "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   396,   396,   405,   411,   419,   425,   435,   441,   445,
     453,   457,   461,   465,   469,   477,   485,   493,   498,   507,
     523,   531,   553,   571,   575,   581,   589,   595,   605,   617,
     621,   625,   629,   633,   637,   641,   645,   649,   653,   657,
     661,   669,   675,   685,   693,   697,   705,   709,   717,   721,
     725,   733,   739,   749,   757,   761,   769,   777,   785,   789,
     793,   798,   807,   811,   815,   820,   829,   837,   845,   857,
     863,   873,   877,   881,   885,   889,   893,   897,   901,   909,
     913,   917,   921,   925,   929,   933,   945,   949,   953,   957,
     961,   965,   969,   973,   977,   981,   985,   989,   993,   997,
    1001,  1005,  1009,  1013,  1021,  1025,  1029,  1037,  1042,  1050,
    1055,  1063,  1071,  1079,  1087,  1095,  1103,  1111,  1119,  1131,
    1135,  1139,  1143,  1147,  1151,  1155,  1159,  1163,  1167,  1171,
    1175,  1183,  1191,  1196,  1205,  1221,  1237,  1253,  1265,  1281,
    1297,  1305,  1310,  1314,  1322,  1329,  1337,  1344,  1350,  1359,
    1371,  1377,  1387,  1391,  1395,  1399,  1403,  1411,  1419,  1423,
    1430,  1440,  1460,  1468,  1476,  1488,  1492,  1496,  1510,  1516,
    1526,  1530,  1538,  1544,  1554,  1558,  1562,  1574,  1578,  1586,
    1590,  1598,  1604,  1614,  1621,  1630,  1640,  1644,  1656,  1660,
    1668,  1674,  1686,  1690,  1699,  1705,  1715,  1721,  1731,  1739,
    1745,  1753,  1759,  1767,  1775,  1781,  1795,  1801,  1811,  1815,
    1819,  1827,  1835
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


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 4469 "GrammarParser.cpp" // lalr1.cc:1167
#line 1841 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
