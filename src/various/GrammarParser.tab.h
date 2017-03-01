// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file GrammarParser.tab.h
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
# define YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
// //                    "%code requires" blocks.
#line 36 "../../obj/src/GrammarParser.yy" // lalr1.cc:377

    #include "src/Driver.h"
    #include "src/Exceptions.h"

    #include "src/ast/Specification.h"

    #include "../stdhl/cpp/Type.h"

    using namespace libcasm_fe;
    using namespace Ast;

#line 56 "GrammarParser.tab.h" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 133 "GrammarParser.tab.h" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // BasicType
      char dummy1[sizeof(BasicType::Ptr)];

      // BlockRule
      char dummy2[sizeof(BlockRule::Ptr)];

      // CallRule
      char dummy3[sizeof(CallRule::Ptr)];

      // CaseLabel
      char dummy4[sizeof(CaseRule::Case)];

      // CaseRule
      char dummy5[sizeof(CaseRule::Ptr)];

      // ComposedType
      char dummy6[sizeof(ComposedType::Ptr)];

      // ConditionalExpression
      char dummy7[sizeof(ConditionalExpression::Ptr)];

      // ConditionalRule
      char dummy8[sizeof(ConditionalRule::Ptr)];

      // Definition
      char dummy9[sizeof(Definition::Ptr)];

      // Definitions
      char dummy10[sizeof(Definitions::Ptr)];

      // DerivedDefinition
      char dummy11[sizeof(DerivedDefinition::Ptr)];

      // DirectCallExpression
      char dummy12[sizeof(DirectCallExpression::Ptr)];

      // EnumerationDefinition
      char dummy13[sizeof(EnumerationDefinition::Ptr)];

      // ExistentialQuantifierExpression
      char dummy14[sizeof(ExistentialQuantifierExpression::Ptr)];

      // MaybeDefined
      // Atom
      // Expression
      // Term
      char dummy15[sizeof(Expression::Ptr)];

      // Expressions
      // MaybeExpressions
      // Arguments
      // MaybeArguments
      char dummy16[sizeof(Expressions::Ptr)];

      // FixedSizedType
      char dummy17[sizeof(FixedSizedType::Ptr)];

      // ForallRule
      char dummy18[sizeof(ForallRule::Ptr)];

      // FunctionDefinition
      // ProgramFunctionDefinition
      char dummy19[sizeof(FunctionDefinition::Ptr)];

      // Identifier
      char dummy20[sizeof(IdentifierNode::Ptr)];

      // IndirectCallExpression
      char dummy21[sizeof(IndirectCallExpression::Ptr)];

      // IterateRule
      char dummy22[sizeof(IterateRule::Ptr)];

      // LetRule
      char dummy23[sizeof(LetRule::Ptr)];

      // List
      char dummy24[sizeof(ListExpression::Ptr)];

      // MaybeFunctionAttributes
      // Identifiers
      // MaybeIdentifiers
      char dummy25[sizeof(NodeList< IdentifierNode >::Ptr)];

      // MaybeInitially
      // Initializers
      // MaybeInitializers
      char dummy26[sizeof(NodeList< UpdateRule >::Ptr)];

      // Parameters
      // MaybeParameters
      char dummy27[sizeof(NodeList< VariableDefinition >::Ptr)];

      // Range
      char dummy28[sizeof(RangeExpression::Ptr)];

      // RangedType
      char dummy29[sizeof(RangedType::Ptr)];

      // Rule
      char dummy30[sizeof(Rule::Ptr)];

      // RuleDefinition
      char dummy31[sizeof(RuleDefinition::Ptr)];

      // RuleReference
      char dummy32[sizeof(RuleReferenceAtom::Ptr)];

      // Rules
      char dummy33[sizeof(Rules::Ptr)];

      // SequenceRule
      char dummy34[sizeof(SequenceRule::Ptr)];

      // SkipRule
      char dummy35[sizeof(SkipRule::Ptr)];

      // Specification
      char dummy36[sizeof(Specification::Ptr)];

      // Type
      char dummy37[sizeof(Type::Ptr)];

      // FunctionParameters
      // MaybeFunctionParameters
      // Types
      char dummy38[sizeof(Types::Ptr)];

      // Undefined
      char dummy39[sizeof(UndefAtom::Ptr)];

      // UniversalQuantifierExpression
      char dummy40[sizeof(UniversalQuantifierExpression::Ptr)];

      // Initializer
      // UpdateRule
      char dummy41[sizeof(UpdateRule::Ptr)];

      // Boolean
      // String
      // BitNumber
      // IntegerNumber
      // FloatingNumber
      // RationalNumber
      char dummy42[sizeof(ValueAtom::Ptr)];

      // Variable
      char dummy43[sizeof(VariableDefinition::Ptr)];

      // "binary"
      // "hexadecimal"
      // "integer"
      // "rational"
      // "floating"
      // "string"
      // "identifier"
      char dummy44[sizeof(std::string)];

      // CaseLabels
      char dummy45[sizeof(std::vector< CaseRule::Case >)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        CASM = 258,
        INIT = 259,
        OPTION = 260,
        DERIVED = 261,
        ENUM = 262,
        RULE = 263,
        DUMPS = 264,
        FUNCTION = 265,
        INITIALLY = 266,
        DEFINED = 267,
        SEQ = 268,
        ENDSEQ = 269,
        PAR = 270,
        ENDPAR = 271,
        SKIP = 272,
        LET = 273,
        IN = 274,
        FORALL = 275,
        ITERATE = 276,
        DO = 277,
        CALL = 278,
        IF = 279,
        THEN = 280,
        ELSE = 281,
        CASE = 282,
        OF = 283,
        DEFAULT = 284,
        HOLDS = 285,
        EXISTS = 286,
        WITH = 287,
        UNDEF = 288,
        FALSE = 289,
        TRUE = 290,
        AND = 291,
        OR = 292,
        XOR = 293,
        IMPLIES = 294,
        NOT = 295,
        PLUS = 296,
        MINUS = 297,
        EQUAL = 298,
        LPAREN = 299,
        RPAREN = 300,
        LSQPAREN = 301,
        RSQPAREN = 302,
        LCURPAREN = 303,
        RCURPAREN = 304,
        COLON = 305,
        UNDERLINE = 306,
        AT = 307,
        COMMA = 308,
        LESSER = 309,
        GREATER = 310,
        ASTERIX = 311,
        SLASH = 312,
        PERCENT = 313,
        CARET = 314,
        DOTDOT = 315,
        ARROW = 316,
        UPDATE = 317,
        NEQUAL = 318,
        LESSEQ = 319,
        GREATEREQ = 320,
        SEQ_BRACKET = 321,
        ENDSEQ_BRACKET = 322,
        BINARY = 323,
        HEXADECIMAL = 324,
        INTEGER = 325,
        RATIONAL = 326,
        FLOATING = 327,
        STRING = 328,
        IDENTIFIER = 329,
        UPLUS = 330,
        UMINUS = 331,
        UASTERIX = 332
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BasicType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BlockRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CallRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CaseRule::Case v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CaseRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ComposedType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ConditionalExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ConditionalRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Definition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Definitions::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const DerivedDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const DirectCallExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const EnumerationDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ExistentialQuantifierExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Expression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Expressions::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FixedSizedType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ForallRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FunctionDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IdentifierNode::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IndirectCallExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IterateRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const LetRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ListExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const NodeList< IdentifierNode >::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const NodeList< UpdateRule >::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const NodeList< VariableDefinition >::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RangeExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RangedType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Rule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RuleDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RuleReferenceAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Rules::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const SequenceRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const SkipRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Specification::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Type::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Types::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UndefAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UniversalQuantifierExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UpdateRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ValueAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const VariableDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector< CaseRule::Case > v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_CASM (const location_type& l);

    static inline
    symbol_type
    make_INIT (const location_type& l);

    static inline
    symbol_type
    make_OPTION (const location_type& l);

    static inline
    symbol_type
    make_DERIVED (const location_type& l);

    static inline
    symbol_type
    make_ENUM (const location_type& l);

    static inline
    symbol_type
    make_RULE (const location_type& l);

    static inline
    symbol_type
    make_DUMPS (const location_type& l);

    static inline
    symbol_type
    make_FUNCTION (const location_type& l);

    static inline
    symbol_type
    make_INITIALLY (const location_type& l);

    static inline
    symbol_type
    make_DEFINED (const location_type& l);

    static inline
    symbol_type
    make_SEQ (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQ (const location_type& l);

    static inline
    symbol_type
    make_PAR (const location_type& l);

    static inline
    symbol_type
    make_ENDPAR (const location_type& l);

    static inline
    symbol_type
    make_SKIP (const location_type& l);

    static inline
    symbol_type
    make_LET (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_FORALL (const location_type& l);

    static inline
    symbol_type
    make_ITERATE (const location_type& l);

    static inline
    symbol_type
    make_DO (const location_type& l);

    static inline
    symbol_type
    make_CALL (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_THEN (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_CASE (const location_type& l);

    static inline
    symbol_type
    make_OF (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const location_type& l);

    static inline
    symbol_type
    make_HOLDS (const location_type& l);

    static inline
    symbol_type
    make_EXISTS (const location_type& l);

    static inline
    symbol_type
    make_WITH (const location_type& l);

    static inline
    symbol_type
    make_UNDEF (const location_type& l);

    static inline
    symbol_type
    make_FALSE (const location_type& l);

    static inline
    symbol_type
    make_TRUE (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_IMPLIES (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_LSQPAREN (const location_type& l);

    static inline
    symbol_type
    make_RSQPAREN (const location_type& l);

    static inline
    symbol_type
    make_LCURPAREN (const location_type& l);

    static inline
    symbol_type
    make_RCURPAREN (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_UNDERLINE (const location_type& l);

    static inline
    symbol_type
    make_AT (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_LESSER (const location_type& l);

    static inline
    symbol_type
    make_GREATER (const location_type& l);

    static inline
    symbol_type
    make_ASTERIX (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_PERCENT (const location_type& l);

    static inline
    symbol_type
    make_CARET (const location_type& l);

    static inline
    symbol_type
    make_DOTDOT (const location_type& l);

    static inline
    symbol_type
    make_ARROW (const location_type& l);

    static inline
    symbol_type
    make_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_NEQUAL (const location_type& l);

    static inline
    symbol_type
    make_LESSEQ (const location_type& l);

    static inline
    symbol_type
    make_GREATEREQ (const location_type& l);

    static inline
    symbol_type
    make_SEQ_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQ_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_BINARY (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_HEXADECIMAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_RATIONAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_FLOATING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_UPLUS (const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_UASTERIX (const location_type& l);


    /// Build a parser object.
    Parser ();
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1247,     ///< Last index in yytable_.
      yynnts_ = 65,  ///< Number of nonterminal symbols.
      yyfinal_ = 15, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 78  ///< Number of tokens.
    };


  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77
    };
    const unsigned int user_token_number_max_ = 332;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 101: // BasicType
        value.copy< BasicType::Ptr > (other.value);
        break;

      case 139: // BlockRule
        value.copy< BlockRule::Ptr > (other.value);
        break;

      case 142: // CallRule
        value.copy< CallRule::Ptr > (other.value);
        break;

      case 134: // CaseLabel
        value.copy< CaseRule::Case > (other.value);
        break;

      case 133: // CaseRule
        value.copy< CaseRule::Ptr > (other.value);
        break;

      case 102: // ComposedType
        value.copy< ComposedType::Ptr > (other.value);
        break;

      case 125: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (other.value);
        break;

      case 132: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (other.value);
        break;

      case 80: // Definition
        value.copy< Definition::Ptr > (other.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (other.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (other.value);
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (other.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (other.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (other.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.copy< Expression::Ptr > (other.value);
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.copy< Expressions::Ptr > (other.value);
        break;

      case 103: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (other.value);
        break;

      case 137: // ForallRule
        value.copy< ForallRule::Ptr > (other.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (other.value);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (other.value);
        break;

      case 124: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (other.value);
        break;

      case 138: // IterateRule
        value.copy< IterateRule::Ptr > (other.value);
        break;

      case 136: // LetRule
        value.copy< LetRule::Ptr > (other.value);
        break;

      case 116: // List
        value.copy< ListExpression::Ptr > (other.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (other.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (other.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (other.value);
        break;

      case 115: // Range
        value.copy< RangeExpression::Ptr > (other.value);
        break;

      case 104: // RangedType
        value.copy< RangedType::Ptr > (other.value);
        break;

      case 129: // Rule
        value.copy< Rule::Ptr > (other.value);
        break;

      case 128: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (other.value);
        break;

      case 114: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (other.value);
        break;

      case 130: // Rules
        value.copy< Rules::Ptr > (other.value);
        break;

      case 140: // SequenceRule
        value.copy< SequenceRule::Ptr > (other.value);
        break;

      case 131: // SkipRule
        value.copy< SkipRule::Ptr > (other.value);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (other.value);
        break;

      case 100: // Type
        value.copy< Type::Ptr > (other.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.copy< Types::Ptr > (other.value);
        break;

      case 107: // Undefined
        value.copy< UndefAtom::Ptr > (other.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (other.value);
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.copy< UpdateRule::Ptr > (other.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.copy< ValueAtom::Ptr > (other.value);
        break;

      case 97: // Variable
        value.copy< VariableDefinition::Ptr > (other.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.copy< std::string > (other.value);
        break;

      case 135: // CaseLabels
        value.copy< std::vector< CaseRule::Case > > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 101: // BasicType
        value.copy< BasicType::Ptr > (v);
        break;

      case 139: // BlockRule
        value.copy< BlockRule::Ptr > (v);
        break;

      case 142: // CallRule
        value.copy< CallRule::Ptr > (v);
        break;

      case 134: // CaseLabel
        value.copy< CaseRule::Case > (v);
        break;

      case 133: // CaseRule
        value.copy< CaseRule::Ptr > (v);
        break;

      case 102: // ComposedType
        value.copy< ComposedType::Ptr > (v);
        break;

      case 125: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (v);
        break;

      case 132: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (v);
        break;

      case 80: // Definition
        value.copy< Definition::Ptr > (v);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (v);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (v);
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (v);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (v);
        break;

      case 127: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (v);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.copy< Expression::Ptr > (v);
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.copy< Expressions::Ptr > (v);
        break;

      case 103: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (v);
        break;

      case 137: // ForallRule
        value.copy< ForallRule::Ptr > (v);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (v);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (v);
        break;

      case 124: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (v);
        break;

      case 138: // IterateRule
        value.copy< IterateRule::Ptr > (v);
        break;

      case 136: // LetRule
        value.copy< LetRule::Ptr > (v);
        break;

      case 116: // List
        value.copy< ListExpression::Ptr > (v);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (v);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (v);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (v);
        break;

      case 115: // Range
        value.copy< RangeExpression::Ptr > (v);
        break;

      case 104: // RangedType
        value.copy< RangedType::Ptr > (v);
        break;

      case 129: // Rule
        value.copy< Rule::Ptr > (v);
        break;

      case 128: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (v);
        break;

      case 114: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (v);
        break;

      case 130: // Rules
        value.copy< Rules::Ptr > (v);
        break;

      case 140: // SequenceRule
        value.copy< SequenceRule::Ptr > (v);
        break;

      case 131: // SkipRule
        value.copy< SkipRule::Ptr > (v);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (v);
        break;

      case 100: // Type
        value.copy< Type::Ptr > (v);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.copy< Types::Ptr > (v);
        break;

      case 107: // Undefined
        value.copy< UndefAtom::Ptr > (v);
        break;

      case 126: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (v);
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.copy< UpdateRule::Ptr > (v);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.copy< ValueAtom::Ptr > (v);
        break;

      case 97: // Variable
        value.copy< VariableDefinition::Ptr > (v);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.copy< std::string > (v);
        break;

      case 135: // CaseLabels
        value.copy< std::vector< CaseRule::Case > > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BasicType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BlockRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CallRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CaseRule::Case v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CaseRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ComposedType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ConditionalExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ConditionalRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Definition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Definitions::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const DerivedDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const DirectCallExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const EnumerationDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ExistentialQuantifierExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expressions::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FixedSizedType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ForallRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FunctionDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IdentifierNode::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IndirectCallExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IterateRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LetRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ListExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeList< IdentifierNode >::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeList< UpdateRule >::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeList< VariableDefinition >::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RangeExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RangedType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Rule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RuleDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RuleReferenceAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Rules::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SequenceRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SkipRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Specification::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Type::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Types::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UndefAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UniversalQuantifierExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UpdateRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ValueAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const VariableDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector< CaseRule::Case > v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 101: // BasicType
        value.template destroy< BasicType::Ptr > ();
        break;

      case 139: // BlockRule
        value.template destroy< BlockRule::Ptr > ();
        break;

      case 142: // CallRule
        value.template destroy< CallRule::Ptr > ();
        break;

      case 134: // CaseLabel
        value.template destroy< CaseRule::Case > ();
        break;

      case 133: // CaseRule
        value.template destroy< CaseRule::Ptr > ();
        break;

      case 102: // ComposedType
        value.template destroy< ComposedType::Ptr > ();
        break;

      case 125: // ConditionalExpression
        value.template destroy< ConditionalExpression::Ptr > ();
        break;

      case 132: // ConditionalRule
        value.template destroy< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
        value.template destroy< Definition::Ptr > ();
        break;

      case 81: // Definitions
        value.template destroy< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        value.template destroy< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        value.template destroy< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        value.template destroy< EnumerationDefinition::Ptr > ();
        break;

      case 127: // ExistentialQuantifierExpression
        value.template destroy< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.template destroy< Expression::Ptr > ();
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.template destroy< Expressions::Ptr > ();
        break;

      case 103: // FixedSizedType
        value.template destroy< FixedSizedType::Ptr > ();
        break;

      case 137: // ForallRule
        value.template destroy< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.template destroy< FunctionDefinition::Ptr > ();
        break;

      case 94: // Identifier
        value.template destroy< IdentifierNode::Ptr > ();
        break;

      case 124: // IndirectCallExpression
        value.template destroy< IndirectCallExpression::Ptr > ();
        break;

      case 138: // IterateRule
        value.template destroy< IterateRule::Ptr > ();
        break;

      case 136: // LetRule
        value.template destroy< LetRule::Ptr > ();
        break;

      case 116: // List
        value.template destroy< ListExpression::Ptr > ();
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.template destroy< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.template destroy< NodeList< UpdateRule >::Ptr > ();
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.template destroy< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 115: // Range
        value.template destroy< RangeExpression::Ptr > ();
        break;

      case 104: // RangedType
        value.template destroy< RangedType::Ptr > ();
        break;

      case 129: // Rule
        value.template destroy< Rule::Ptr > ();
        break;

      case 128: // RuleDefinition
        value.template destroy< RuleDefinition::Ptr > ();
        break;

      case 114: // RuleReference
        value.template destroy< RuleReferenceAtom::Ptr > ();
        break;

      case 130: // Rules
        value.template destroy< Rules::Ptr > ();
        break;

      case 140: // SequenceRule
        value.template destroy< SequenceRule::Ptr > ();
        break;

      case 131: // SkipRule
        value.template destroy< SkipRule::Ptr > ();
        break;

      case 79: // Specification
        value.template destroy< Specification::Ptr > ();
        break;

      case 100: // Type
        value.template destroy< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.template destroy< Types::Ptr > ();
        break;

      case 107: // Undefined
        value.template destroy< UndefAtom::Ptr > ();
        break;

      case 126: // UniversalQuantifierExpression
        value.template destroy< UniversalQuantifierExpression::Ptr > ();
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.template destroy< UpdateRule::Ptr > ();
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.template destroy< ValueAtom::Ptr > ();
        break;

      case 97: // Variable
        value.template destroy< VariableDefinition::Ptr > ();
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.template destroy< std::string > ();
        break;

      case 135: // CaseLabels
        value.template destroy< std::vector< CaseRule::Case > > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 101: // BasicType
        value.move< BasicType::Ptr > (s.value);
        break;

      case 139: // BlockRule
        value.move< BlockRule::Ptr > (s.value);
        break;

      case 142: // CallRule
        value.move< CallRule::Ptr > (s.value);
        break;

      case 134: // CaseLabel
        value.move< CaseRule::Case > (s.value);
        break;

      case 133: // CaseRule
        value.move< CaseRule::Ptr > (s.value);
        break;

      case 102: // ComposedType
        value.move< ComposedType::Ptr > (s.value);
        break;

      case 125: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (s.value);
        break;

      case 132: // ConditionalRule
        value.move< ConditionalRule::Ptr > (s.value);
        break;

      case 80: // Definition
        value.move< Definition::Ptr > (s.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (s.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (s.value);
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (s.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (s.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (s.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.move< Expression::Ptr > (s.value);
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.move< Expressions::Ptr > (s.value);
        break;

      case 103: // FixedSizedType
        value.move< FixedSizedType::Ptr > (s.value);
        break;

      case 137: // ForallRule
        value.move< ForallRule::Ptr > (s.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (s.value);
        break;

      case 94: // Identifier
        value.move< IdentifierNode::Ptr > (s.value);
        break;

      case 124: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (s.value);
        break;

      case 138: // IterateRule
        value.move< IterateRule::Ptr > (s.value);
        break;

      case 136: // LetRule
        value.move< LetRule::Ptr > (s.value);
        break;

      case 116: // List
        value.move< ListExpression::Ptr > (s.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (s.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (s.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (s.value);
        break;

      case 115: // Range
        value.move< RangeExpression::Ptr > (s.value);
        break;

      case 104: // RangedType
        value.move< RangedType::Ptr > (s.value);
        break;

      case 129: // Rule
        value.move< Rule::Ptr > (s.value);
        break;

      case 128: // RuleDefinition
        value.move< RuleDefinition::Ptr > (s.value);
        break;

      case 114: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (s.value);
        break;

      case 130: // Rules
        value.move< Rules::Ptr > (s.value);
        break;

      case 140: // SequenceRule
        value.move< SequenceRule::Ptr > (s.value);
        break;

      case 131: // SkipRule
        value.move< SkipRule::Ptr > (s.value);
        break;

      case 79: // Specification
        value.move< Specification::Ptr > (s.value);
        break;

      case 100: // Type
        value.move< Type::Ptr > (s.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.move< Types::Ptr > (s.value);
        break;

      case 107: // Undefined
        value.move< UndefAtom::Ptr > (s.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (s.value);
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.move< UpdateRule::Ptr > (s.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.move< ValueAtom::Ptr > (s.value);
        break;

      case 97: // Variable
        value.move< VariableDefinition::Ptr > (s.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
        value.move< std::string > (s.value);
        break;

      case 135: // CaseLabels
        value.move< std::vector< CaseRule::Case > > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_CASM (const location_type& l)
  {
    return symbol_type (token::CASM, l);
  }

  Parser::symbol_type
  Parser::make_INIT (const location_type& l)
  {
    return symbol_type (token::INIT, l);
  }

  Parser::symbol_type
  Parser::make_OPTION (const location_type& l)
  {
    return symbol_type (token::OPTION, l);
  }

  Parser::symbol_type
  Parser::make_DERIVED (const location_type& l)
  {
    return symbol_type (token::DERIVED, l);
  }

  Parser::symbol_type
  Parser::make_ENUM (const location_type& l)
  {
    return symbol_type (token::ENUM, l);
  }

  Parser::symbol_type
  Parser::make_RULE (const location_type& l)
  {
    return symbol_type (token::RULE, l);
  }

  Parser::symbol_type
  Parser::make_DUMPS (const location_type& l)
  {
    return symbol_type (token::DUMPS, l);
  }

  Parser::symbol_type
  Parser::make_FUNCTION (const location_type& l)
  {
    return symbol_type (token::FUNCTION, l);
  }

  Parser::symbol_type
  Parser::make_INITIALLY (const location_type& l)
  {
    return symbol_type (token::INITIALLY, l);
  }

  Parser::symbol_type
  Parser::make_DEFINED (const location_type& l)
  {
    return symbol_type (token::DEFINED, l);
  }

  Parser::symbol_type
  Parser::make_SEQ (const location_type& l)
  {
    return symbol_type (token::SEQ, l);
  }

  Parser::symbol_type
  Parser::make_ENDSEQ (const location_type& l)
  {
    return symbol_type (token::ENDSEQ, l);
  }

  Parser::symbol_type
  Parser::make_PAR (const location_type& l)
  {
    return symbol_type (token::PAR, l);
  }

  Parser::symbol_type
  Parser::make_ENDPAR (const location_type& l)
  {
    return symbol_type (token::ENDPAR, l);
  }

  Parser::symbol_type
  Parser::make_SKIP (const location_type& l)
  {
    return symbol_type (token::SKIP, l);
  }

  Parser::symbol_type
  Parser::make_LET (const location_type& l)
  {
    return symbol_type (token::LET, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  Parser::symbol_type
  Parser::make_FORALL (const location_type& l)
  {
    return symbol_type (token::FORALL, l);
  }

  Parser::symbol_type
  Parser::make_ITERATE (const location_type& l)
  {
    return symbol_type (token::ITERATE, l);
  }

  Parser::symbol_type
  Parser::make_DO (const location_type& l)
  {
    return symbol_type (token::DO, l);
  }

  Parser::symbol_type
  Parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::CALL, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  Parser::symbol_type
  Parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  Parser::symbol_type
  Parser::make_CASE (const location_type& l)
  {
    return symbol_type (token::CASE, l);
  }

  Parser::symbol_type
  Parser::make_OF (const location_type& l)
  {
    return symbol_type (token::OF, l);
  }

  Parser::symbol_type
  Parser::make_DEFAULT (const location_type& l)
  {
    return symbol_type (token::DEFAULT, l);
  }

  Parser::symbol_type
  Parser::make_HOLDS (const location_type& l)
  {
    return symbol_type (token::HOLDS, l);
  }

  Parser::symbol_type
  Parser::make_EXISTS (const location_type& l)
  {
    return symbol_type (token::EXISTS, l);
  }

  Parser::symbol_type
  Parser::make_WITH (const location_type& l)
  {
    return symbol_type (token::WITH, l);
  }

  Parser::symbol_type
  Parser::make_UNDEF (const location_type& l)
  {
    return symbol_type (token::UNDEF, l);
  }

  Parser::symbol_type
  Parser::make_FALSE (const location_type& l)
  {
    return symbol_type (token::FALSE, l);
  }

  Parser::symbol_type
  Parser::make_TRUE (const location_type& l)
  {
    return symbol_type (token::TRUE, l);
  }

  Parser::symbol_type
  Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  Parser::symbol_type
  Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  Parser::symbol_type
  Parser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  Parser::symbol_type
  Parser::make_IMPLIES (const location_type& l)
  {
    return symbol_type (token::IMPLIES, l);
  }

  Parser::symbol_type
  Parser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  Parser::symbol_type
  Parser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::PLUS, l);
  }

  Parser::symbol_type
  Parser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::MINUS, l);
  }

  Parser::symbol_type
  Parser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::LPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::RPAREN, l);
  }

  Parser::symbol_type
  Parser::make_LSQPAREN (const location_type& l)
  {
    return symbol_type (token::LSQPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RSQPAREN (const location_type& l)
  {
    return symbol_type (token::RSQPAREN, l);
  }

  Parser::symbol_type
  Parser::make_LCURPAREN (const location_type& l)
  {
    return symbol_type (token::LCURPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RCURPAREN (const location_type& l)
  {
    return symbol_type (token::RCURPAREN, l);
  }

  Parser::symbol_type
  Parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::COLON, l);
  }

  Parser::symbol_type
  Parser::make_UNDERLINE (const location_type& l)
  {
    return symbol_type (token::UNDERLINE, l);
  }

  Parser::symbol_type
  Parser::make_AT (const location_type& l)
  {
    return symbol_type (token::AT, l);
  }

  Parser::symbol_type
  Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  Parser::symbol_type
  Parser::make_LESSER (const location_type& l)
  {
    return symbol_type (token::LESSER, l);
  }

  Parser::symbol_type
  Parser::make_GREATER (const location_type& l)
  {
    return symbol_type (token::GREATER, l);
  }

  Parser::symbol_type
  Parser::make_ASTERIX (const location_type& l)
  {
    return symbol_type (token::ASTERIX, l);
  }

  Parser::symbol_type
  Parser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::SLASH, l);
  }

  Parser::symbol_type
  Parser::make_PERCENT (const location_type& l)
  {
    return symbol_type (token::PERCENT, l);
  }

  Parser::symbol_type
  Parser::make_CARET (const location_type& l)
  {
    return symbol_type (token::CARET, l);
  }

  Parser::symbol_type
  Parser::make_DOTDOT (const location_type& l)
  {
    return symbol_type (token::DOTDOT, l);
  }

  Parser::symbol_type
  Parser::make_ARROW (const location_type& l)
  {
    return symbol_type (token::ARROW, l);
  }

  Parser::symbol_type
  Parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  Parser::symbol_type
  Parser::make_NEQUAL (const location_type& l)
  {
    return symbol_type (token::NEQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LESSEQ (const location_type& l)
  {
    return symbol_type (token::LESSEQ, l);
  }

  Parser::symbol_type
  Parser::make_GREATEREQ (const location_type& l)
  {
    return symbol_type (token::GREATEREQ, l);
  }

  Parser::symbol_type
  Parser::make_SEQ_BRACKET (const location_type& l)
  {
    return symbol_type (token::SEQ_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_ENDSEQ_BRACKET (const location_type& l)
  {
    return symbol_type (token::ENDSEQ_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_BINARY (const std::string& v, const location_type& l)
  {
    return symbol_type (token::BINARY, v, l);
  }

  Parser::symbol_type
  Parser::make_HEXADECIMAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::HEXADECIMAL, v, l);
  }

  Parser::symbol_type
  Parser::make_INTEGER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::INTEGER, v, l);
  }

  Parser::symbol_type
  Parser::make_RATIONAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::RATIONAL, v, l);
  }

  Parser::symbol_type
  Parser::make_FLOATING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::FLOATING, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_UPLUS (const location_type& l)
  {
    return symbol_type (token::UPLUS, l);
  }

  Parser::symbol_type
  Parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }

  Parser::symbol_type
  Parser::make_UASTERIX (const location_type& l)
  {
    return symbol_type (token::UASTERIX, l);
  }



} // yy
#line 3095 "GrammarParser.tab.h" // lalr1.cc:377




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
