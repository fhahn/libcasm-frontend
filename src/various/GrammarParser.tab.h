//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
//  
//  This file is part of libcasm-fe.
//  
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//  

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
#line 36 "../../src/GrammarParser.yy" // lalr1.cc:377

    #include <cstdint>
    #include <string>
    #include <utility>

    #include "src/Ast.h"
    #include "src/Types.h"
    class Driver;

#line 54 "GrammarParser.tab.h" // lalr1.cc:377

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
#line 131 "GrammarParser.tab.h" // lalr1.cc:377



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
  class casmi_parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // BODY_ELEMENTS
      // STATEMENTS
      char dummy1[sizeof(AstListNode*)];

      // SPECIFICATION
      // BODY_ELEMENT
      // INIT_SYNTAX
      // RULE_SYNTAX
      // STATEMENT
      // IMPOSSIBLE_SYNTAX
      char dummy2[sizeof(AstNode*)];

      // VALUE
      // NUMBER
      // NUMBER_RANGE
      char dummy3[sizeof(AtomNode*)];

      // FUNCTION_SYNTAX
      char dummy4[sizeof(BaseFunctionAtom*)];

      // CALL_SYNTAX
      char dummy5[sizeof(CallNode*)];

      // CASE_SYNTAX
      char dummy6[sizeof(CaseNode*)];

      // DIEDIE_SYNTAX
      char dummy7[sizeof(DiedieNode*)];

      // ENUM_SYNTAX
      char dummy8[sizeof(Enum*)];

      // ATOM
      // EXPRESSION
      // BRACKET_EXPRESSION
      char dummy9[sizeof(ExpressionBase*)];

      // FLOATCONST
      char dummy10[sizeof(FLOAT_T)];

      // FORALL_SYNTAX
      char dummy11[sizeof(ForallNode*)];

      // DERIVED_SYNTAX
      // FUNCTION_DEFINITION
      char dummy12[sizeof(Function*)];

      // INTEGERCONST
      char dummy13[sizeof(INTEGER_T)];

      // IFTHENELSE
      char dummy14[sizeof(IfThenElseNode*)];

      // INTEGER_NUMBER
      char dummy15[sizeof(IntegerAtom*)];

      // LET_SYNTAX
      char dummy16[sizeof(LetNode*)];

      // POP_SYNTAX
      char dummy17[sizeof(PopNode*)];

      // DEBUGINFO_SYNTAX
      // PRINT_SYNTAX
      char dummy18[sizeof(PrintNode*)];

      // PUSH_SYNTAX
      char dummy19[sizeof(PushNode*)];

      // PARAM
      // TYPE_SYNTAX
      char dummy20[sizeof(Type*)];

      // ASSERT_SYNTAX
      // ASSURE_SYNTAX
      // KW_SEQBLOCK_SYNTAX
      // SEQBLOCK_SYNTAX
      // KW_PARBLOCK_SYNTAX
      // PARBLOCK_SYNTAX
      // ITERATE_SYNTAX
      char dummy21[sizeof(UnaryNode*)];

      // UPDATE_SYNTAX
      char dummy22[sizeof(UpdateNode*)];

      // RATIONALCONST
      char dummy23[sizeof(rational_t)];

      // CASE_LABEL
      // CASE_LABEL_DEFAULT
      // CASE_LABEL_NUMBER
      // CASE_LABEL_IDENT
      // CASE_LABEL_STRING
      char dummy24[sizeof(std::pair<AtomNode*, AstNode*>)];

      // INITIALIZER
      char dummy25[sizeof(std::pair<ExpressionBase*, ExpressionBase*>)];

      // DUMPSPEC
      char dummy26[sizeof(std::pair<std::string, std::vector<std::string>>)];

      // FUNCTION_SIGNATURE
      char dummy27[sizeof(std::pair<std::vector<Type*>, Type*>)];

      // STRCONST
      // "identifier"
      // RULEREF
      char dummy28[sizeof(std::string)];

      // DEBUG_ATOM_LIST
      char dummy29[sizeof(std::vector<ExpressionBase*>)];

      // LISTCONST
      // EXPRESSION_LIST
      // EXPRESSION_LIST_NO_COMMA
      char dummy30[sizeof(std::vector<ExpressionBase*>*)];

      // PARAM_LIST
      // PARAM_LIST_NO_COMMA
      // TYPE_IDENTIFIER_STARLIST
      // TYPE_SYNTAX_LIST
      char dummy31[sizeof(std::vector<Type*>)];

      // CASE_LABEL_LIST
      char dummy32[sizeof(std::vector<std::pair<AtomNode*, AstNode*>>)];

      // INITIALIZERS
      // INITIALIZER_LIST
      char dummy33[sizeof(std::vector<std::pair<ExpressionBase*, ExpressionBase*>>*)];

      // DUMPSPEC_LIST
      char dummy34[sizeof(std::vector<std::pair<std::string, std::vector<std::string>>>)];

      // IDENTIFIER_LIST
      // IDENTIFIER_LIST_NO_COMMA
      char dummy35[sizeof(std::vector<std::string>)];
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
        AND = 258,
        OR = 259,
        XOR = 260,
        NOT = 261,
        ASSERT = 262,
        ASSURE = 263,
        DIEDIE = 264,
        IMPOSSIBLE = 265,
        SKIP = 266,
        SEQBLOCK = 267,
        ENDSEQBLOCK = 268,
        PARBLOCK = 269,
        ENDPARBLOCK = 270,
        LET = 271,
        IN = 272,
        IF = 273,
        THEN = 274,
        ELSE = 275,
        PRINT = 276,
        DEBUGINFO = 277,
        DUMPS = 278,
        PUSH = 279,
        INTO = 280,
        POP = 281,
        FROM = 282,
        FORALL = 283,
        ITERATE = 284,
        DO = 285,
        CALL = 286,
        CASE = 287,
        DEFAULT = 288,
        OF = 289,
        ENDCASE = 290,
        INITIALLY = 291,
        FUNCTION = 292,
        DERIVED = 293,
        ENUM = 294,
        RULE = 295,
        PROVIDER = 296,
        INIT = 297,
        OPTION = 298,
        SELF = 299,
        UNDEF = 300,
        TRUE = 301,
        FALSE = 302,
        CASM = 303,
        SYMBOL = 304,
        INTERN = 305,
        RATIONAL_DIV = 306,
        OBJDUMP = 307,
        DOTDOT = 308,
        ARROW = 309,
        UPDATE = 310,
        NEQUAL = 311,
        LESSEQ = 312,
        GREATEREQ = 313,
        SEQBLOCK_BRACKET = 314,
        ENDSEQBLOCK_BRACKET = 315,
        PLUS = 316,
        MINUS = 317,
        EQ = 318,
        LPAREN = 319,
        RPAREN = 320,
        LSQPAREN = 321,
        RSQPAREN = 322,
        LCURPAREN = 323,
        RCURPAREN = 324,
        DOT = 325,
        COLON = 326,
        AT = 327,
        COMMA = 328,
        LESSER = 329,
        GREATER = 330,
        STAR = 331,
        SLASH = 332,
        PERCENT = 333,
        FLOATCONST = 334,
        INTEGERCONST = 335,
        RATIONALCONST = 336,
        STRCONST = 337,
        IDENTIFIER = 338,
        UMINUS = 339,
        UPLUS = 340,
        XIF = 341
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

  basic_symbol (typename Base::kind_type t, const AstListNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const AstNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const AtomNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BaseFunctionAtom* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CallNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CaseNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const DiedieNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Enum* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ExpressionBase* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FLOAT_T v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ForallNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Function* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const INTEGER_T v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IfThenElseNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IntegerAtom* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const LetNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const PopNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const PrintNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const PushNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Type* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UnaryNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UpdateNode* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const rational_t v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::pair<AtomNode*, AstNode*> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::pair<ExpressionBase*, ExpressionBase*> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::vector<std::string>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::pair<std::vector<Type*>, Type*> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<ExpressionBase*> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<ExpressionBase*>* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<Type*> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::pair<AtomNode*, AstNode*>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::pair<std::string, std::vector<std::string>>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l);


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
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_ASSERT (const location_type& l);

    static inline
    symbol_type
    make_ASSURE (const location_type& l);

    static inline
    symbol_type
    make_DIEDIE (const location_type& l);

    static inline
    symbol_type
    make_IMPOSSIBLE (const location_type& l);

    static inline
    symbol_type
    make_SKIP (const location_type& l);

    static inline
    symbol_type
    make_SEQBLOCK (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQBLOCK (const location_type& l);

    static inline
    symbol_type
    make_PARBLOCK (const location_type& l);

    static inline
    symbol_type
    make_ENDPARBLOCK (const location_type& l);

    static inline
    symbol_type
    make_LET (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

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
    make_PRINT (const location_type& l);

    static inline
    symbol_type
    make_DEBUGINFO (const location_type& l);

    static inline
    symbol_type
    make_DUMPS (const location_type& l);

    static inline
    symbol_type
    make_PUSH (const location_type& l);

    static inline
    symbol_type
    make_INTO (const location_type& l);

    static inline
    symbol_type
    make_POP (const location_type& l);

    static inline
    symbol_type
    make_FROM (const location_type& l);

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
    make_CASE (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const location_type& l);

    static inline
    symbol_type
    make_OF (const location_type& l);

    static inline
    symbol_type
    make_ENDCASE (const location_type& l);

    static inline
    symbol_type
    make_INITIALLY (const location_type& l);

    static inline
    symbol_type
    make_FUNCTION (const location_type& l);

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
    make_PROVIDER (const location_type& l);

    static inline
    symbol_type
    make_INIT (const location_type& l);

    static inline
    symbol_type
    make_OPTION (const location_type& l);

    static inline
    symbol_type
    make_SELF (const location_type& l);

    static inline
    symbol_type
    make_UNDEF (const location_type& l);

    static inline
    symbol_type
    make_TRUE (const location_type& l);

    static inline
    symbol_type
    make_FALSE (const location_type& l);

    static inline
    symbol_type
    make_CASM (const location_type& l);

    static inline
    symbol_type
    make_SYMBOL (const location_type& l);

    static inline
    symbol_type
    make_INTERN (const location_type& l);

    static inline
    symbol_type
    make_RATIONAL_DIV (const location_type& l);

    static inline
    symbol_type
    make_OBJDUMP (const location_type& l);

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
    make_SEQBLOCK_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQBLOCK_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_EQ (const location_type& l);

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
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

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
    make_STAR (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_PERCENT (const location_type& l);

    static inline
    symbol_type
    make_FLOATCONST (const FLOAT_T& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGERCONST (const INTEGER_T& v, const location_type& l);

    static inline
    symbol_type
    make_RATIONALCONST (const rational_t& v, const location_type& l);

    static inline
    symbol_type
    make_STRCONST (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_UPLUS (const location_type& l);

    static inline
    symbol_type
    make_XIF (const location_type& l);


    /// Build a parser object.
    casmi_parser (Driver& driver_yyarg);
    virtual ~casmi_parser ();

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
    casmi_parser (const casmi_parser&);
    casmi_parser& operator= (const casmi_parser&);

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
  static const short int yytable_[];

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
      yylast_ = 995,     ///< Last index in yytable_.
      yynnts_ = 68,  ///< Number of nonterminal symbols.
      yyfinal_ = 5, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 87  ///< Number of tokens.
    };


    // User arguments.
    Driver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
  casmi_parser::token_number_type
  casmi_parser::yytranslate_ (token_type t)
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86
    };
    const unsigned int user_token_number_max_ = 341;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  casmi_parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  casmi_parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  casmi_parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.copy< AstListNode* > (other.value);
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (other.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.copy< AtomNode* > (other.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (other.value);
        break;

      case 141: // CALL_SYNTAX
        value.copy< CallNode* > (other.value);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (other.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (other.value);
        break;

      case 95: // ENUM_SYNTAX
        value.copy< Enum* > (other.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.copy< ExpressionBase* > (other.value);
        break;

      case 79: // FLOATCONST
        value.copy< FLOAT_T > (other.value);
        break;

      case 153: // FORALL_SYNTAX
        value.copy< ForallNode* > (other.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.copy< Function* > (other.value);
        break;

      case 80: // INTEGERCONST
        value.copy< INTEGER_T > (other.value);
        break;

      case 147: // IFTHENELSE
        value.copy< IfThenElseNode* > (other.value);
        break;

      case 112: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (other.value);
        break;

      case 148: // LET_SYNTAX
        value.copy< LetNode* > (other.value);
        break;

      case 152: // POP_SYNTAX
        value.copy< PopNode* > (other.value);
        break;

      case 130: // DEBUGINFO_SYNTAX
      case 132: // PRINT_SYNTAX
        value.copy< PrintNode* > (other.value);
        break;

      case 151: // PUSH_SYNTAX
        value.copy< PushNode* > (other.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.copy< Type* > (other.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (other.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (other.value);
        break;

      case 81: // RATIONALCONST
        value.copy< rational_t > (other.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (other.value);
        break;

      case 109: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (other.value);
        break;

      case 124: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (other.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (other.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.copy< std::string > (other.value);
        break;

      case 131: // DEBUG_ATOM_LIST
        value.copy< std::vector<ExpressionBase*> > (other.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (other.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (other.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (other.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (other.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (other.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.copy< AstListNode* > (v);
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (v);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.copy< AtomNode* > (v);
        break;

      case 121: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (v);
        break;

      case 141: // CALL_SYNTAX
        value.copy< CallNode* > (v);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (v);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (v);
        break;

      case 95: // ENUM_SYNTAX
        value.copy< Enum* > (v);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.copy< ExpressionBase* > (v);
        break;

      case 79: // FLOATCONST
        value.copy< FLOAT_T > (v);
        break;

      case 153: // FORALL_SYNTAX
        value.copy< ForallNode* > (v);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.copy< Function* > (v);
        break;

      case 80: // INTEGERCONST
        value.copy< INTEGER_T > (v);
        break;

      case 147: // IFTHENELSE
        value.copy< IfThenElseNode* > (v);
        break;

      case 112: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (v);
        break;

      case 148: // LET_SYNTAX
        value.copy< LetNode* > (v);
        break;

      case 152: // POP_SYNTAX
        value.copy< PopNode* > (v);
        break;

      case 130: // DEBUGINFO_SYNTAX
      case 132: // PRINT_SYNTAX
        value.copy< PrintNode* > (v);
        break;

      case 151: // PUSH_SYNTAX
        value.copy< PushNode* > (v);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.copy< Type* > (v);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (v);
        break;

      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (v);
        break;

      case 81: // RATIONALCONST
        value.copy< rational_t > (v);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (v);
        break;

      case 109: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (v);
        break;

      case 124: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (v);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (v);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.copy< std::string > (v);
        break;

      case 131: // DEBUG_ATOM_LIST
        value.copy< std::vector<ExpressionBase*> > (v);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (v);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (v);
        break;

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (v);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (v);
        break;

      case 123: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (v);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const AstListNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const AstNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const AtomNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BaseFunctionAtom* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CallNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CaseNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const DiedieNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Enum* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ExpressionBase* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FLOAT_T v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ForallNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Function* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const INTEGER_T v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IfThenElseNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IntegerAtom* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LetNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const PopNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const PrintNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const PushNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Type* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UnaryNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UpdateNode* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const rational_t v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<AtomNode*, AstNode*> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<ExpressionBase*, ExpressionBase*> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::vector<std::string>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<std::vector<Type*>, Type*> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<ExpressionBase*> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<ExpressionBase*>* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<Type*> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::pair<AtomNode*, AstNode*>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::pair<std::string, std::vector<std::string>>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  casmi_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  casmi_parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  casmi_parser::basic_symbol<Base>::clear ()
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
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.template destroy< AstListNode* > ();
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.template destroy< AstNode* > ();
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.template destroy< AtomNode* > ();
        break;

      case 121: // FUNCTION_SYNTAX
        value.template destroy< BaseFunctionAtom* > ();
        break;

      case 141: // CALL_SYNTAX
        value.template destroy< CallNode* > ();
        break;

      case 134: // CASE_SYNTAX
        value.template destroy< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
        value.template destroy< DiedieNode* > ();
        break;

      case 95: // ENUM_SYNTAX
        value.template destroy< Enum* > ();
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.template destroy< ExpressionBase* > ();
        break;

      case 79: // FLOATCONST
        value.template destroy< FLOAT_T > ();
        break;

      case 153: // FORALL_SYNTAX
        value.template destroy< ForallNode* > ();
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.template destroy< Function* > ();
        break;

      case 80: // INTEGERCONST
        value.template destroy< INTEGER_T > ();
        break;

      case 147: // IFTHENELSE
        value.template destroy< IfThenElseNode* > ();
        break;

      case 112: // INTEGER_NUMBER
        value.template destroy< IntegerAtom* > ();
        break;

      case 148: // LET_SYNTAX
        value.template destroy< LetNode* > ();
        break;

      case 152: // POP_SYNTAX
        value.template destroy< PopNode* > ();
        break;

      case 130: // DEBUGINFO_SYNTAX
      case 132: // PRINT_SYNTAX
        value.template destroy< PrintNode* > ();
        break;

      case 151: // PUSH_SYNTAX
        value.template destroy< PushNode* > ();
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.template destroy< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.template destroy< UnaryNode* > ();
        break;

      case 133: // UPDATE_SYNTAX
        value.template destroy< UpdateNode* > ();
        break;

      case 81: // RATIONALCONST
        value.template destroy< rational_t > ();
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.template destroy< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 109: // INITIALIZER
        value.template destroy< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 124: // DUMPSPEC
        value.template destroy< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 100: // FUNCTION_SIGNATURE
        value.template destroy< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.template destroy< std::string > ();
        break;

      case 131: // DEBUG_ATOM_LIST
        value.template destroy< std::vector<ExpressionBase*> > ();
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.template destroy< std::vector<ExpressionBase*>* > ();
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.template destroy< std::vector<Type*> > ();
        break;

      case 135: // CASE_LABEL_LIST
        value.template destroy< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.template destroy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 123: // DUMPSPEC_LIST
        value.template destroy< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  casmi_parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  casmi_parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.move< AstListNode* > (s.value);
        break;

      case 88: // SPECIFICATION
      case 91: // BODY_ELEMENT
      case 92: // INIT_SYNTAX
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (s.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.move< AtomNode* > (s.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (s.value);
        break;

      case 141: // CALL_SYNTAX
        value.move< CallNode* > (s.value);
        break;

      case 134: // CASE_SYNTAX
        value.move< CaseNode* > (s.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (s.value);
        break;

      case 95: // ENUM_SYNTAX
        value.move< Enum* > (s.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.move< ExpressionBase* > (s.value);
        break;

      case 79: // FLOATCONST
        value.move< FLOAT_T > (s.value);
        break;

      case 153: // FORALL_SYNTAX
        value.move< ForallNode* > (s.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.move< Function* > (s.value);
        break;

      case 80: // INTEGERCONST
        value.move< INTEGER_T > (s.value);
        break;

      case 147: // IFTHENELSE
        value.move< IfThenElseNode* > (s.value);
        break;

      case 112: // INTEGER_NUMBER
        value.move< IntegerAtom* > (s.value);
        break;

      case 148: // LET_SYNTAX
        value.move< LetNode* > (s.value);
        break;

      case 152: // POP_SYNTAX
        value.move< PopNode* > (s.value);
        break;

      case 130: // DEBUGINFO_SYNTAX
      case 132: // PRINT_SYNTAX
        value.move< PrintNode* > (s.value);
        break;

      case 151: // PUSH_SYNTAX
        value.move< PushNode* > (s.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.move< Type* > (s.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // KW_SEQBLOCK_SYNTAX
      case 143: // SEQBLOCK_SYNTAX
      case 144: // KW_PARBLOCK_SYNTAX
      case 145: // PARBLOCK_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.move< UnaryNode* > (s.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.move< UpdateNode* > (s.value);
        break;

      case 81: // RATIONALCONST
        value.move< rational_t > (s.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.move< std::pair<AtomNode*, AstNode*> > (s.value);
        break;

      case 109: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (s.value);
        break;

      case 124: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (s.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (s.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.move< std::string > (s.value);
        break;

      case 131: // DEBUG_ATOM_LIST
        value.move< std::vector<ExpressionBase*> > (s.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (s.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (s.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (s.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (s.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (s.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  casmi_parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  casmi_parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  casmi_parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  casmi_parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  casmi_parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  casmi_parser::by_type::type_get () const
  {
    return type;
  }

  inline
  casmi_parser::token_type
  casmi_parser::by_type::token () const
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  casmi_parser::symbol_type
  casmi_parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ASSERT (const location_type& l)
  {
    return symbol_type (token::ASSERT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ASSURE (const location_type& l)
  {
    return symbol_type (token::ASSURE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DIEDIE (const location_type& l)
  {
    return symbol_type (token::DIEDIE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_IMPOSSIBLE (const location_type& l)
  {
    return symbol_type (token::IMPOSSIBLE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SKIP (const location_type& l)
  {
    return symbol_type (token::SKIP, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SEQBLOCK (const location_type& l)
  {
    return symbol_type (token::SEQBLOCK, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ENDSEQBLOCK (const location_type& l)
  {
    return symbol_type (token::ENDSEQBLOCK, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PARBLOCK (const location_type& l)
  {
    return symbol_type (token::PARBLOCK, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ENDPARBLOCK (const location_type& l)
  {
    return symbol_type (token::ENDPARBLOCK, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LET (const location_type& l)
  {
    return symbol_type (token::LET, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PRINT (const location_type& l)
  {
    return symbol_type (token::PRINT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DEBUGINFO (const location_type& l)
  {
    return symbol_type (token::DEBUGINFO, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DUMPS (const location_type& l)
  {
    return symbol_type (token::DUMPS, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PUSH (const location_type& l)
  {
    return symbol_type (token::PUSH, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_POP (const location_type& l)
  {
    return symbol_type (token::POP, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_FORALL (const location_type& l)
  {
    return symbol_type (token::FORALL, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ITERATE (const location_type& l)
  {
    return symbol_type (token::ITERATE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DO (const location_type& l)
  {
    return symbol_type (token::DO, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::CALL, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_CASE (const location_type& l)
  {
    return symbol_type (token::CASE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DEFAULT (const location_type& l)
  {
    return symbol_type (token::DEFAULT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_OF (const location_type& l)
  {
    return symbol_type (token::OF, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ENDCASE (const location_type& l)
  {
    return symbol_type (token::ENDCASE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_INITIALLY (const location_type& l)
  {
    return symbol_type (token::INITIALLY, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_FUNCTION (const location_type& l)
  {
    return symbol_type (token::FUNCTION, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DERIVED (const location_type& l)
  {
    return symbol_type (token::DERIVED, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ENUM (const location_type& l)
  {
    return symbol_type (token::ENUM, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RULE (const location_type& l)
  {
    return symbol_type (token::RULE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PROVIDER (const location_type& l)
  {
    return symbol_type (token::PROVIDER, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_INIT (const location_type& l)
  {
    return symbol_type (token::INIT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_OPTION (const location_type& l)
  {
    return symbol_type (token::OPTION, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SELF (const location_type& l)
  {
    return symbol_type (token::SELF, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_UNDEF (const location_type& l)
  {
    return symbol_type (token::UNDEF, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_TRUE (const location_type& l)
  {
    return symbol_type (token::TRUE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_FALSE (const location_type& l)
  {
    return symbol_type (token::FALSE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_CASM (const location_type& l)
  {
    return symbol_type (token::CASM, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SYMBOL (const location_type& l)
  {
    return symbol_type (token::SYMBOL, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_INTERN (const location_type& l)
  {
    return symbol_type (token::INTERN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RATIONAL_DIV (const location_type& l)
  {
    return symbol_type (token::RATIONAL_DIV, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_OBJDUMP (const location_type& l)
  {
    return symbol_type (token::OBJDUMP, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DOTDOT (const location_type& l)
  {
    return symbol_type (token::DOTDOT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ARROW (const location_type& l)
  {
    return symbol_type (token::ARROW, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_NEQUAL (const location_type& l)
  {
    return symbol_type (token::NEQUAL, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LESSEQ (const location_type& l)
  {
    return symbol_type (token::LESSEQ, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_GREATEREQ (const location_type& l)
  {
    return symbol_type (token::GREATEREQ, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SEQBLOCK_BRACKET (const location_type& l)
  {
    return symbol_type (token::SEQBLOCK_BRACKET, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_ENDSEQBLOCK_BRACKET (const location_type& l)
  {
    return symbol_type (token::ENDSEQBLOCK_BRACKET, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::PLUS, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::MINUS, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_EQ (const location_type& l)
  {
    return symbol_type (token::EQ, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::LPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::RPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LSQPAREN (const location_type& l)
  {
    return symbol_type (token::LSQPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RSQPAREN (const location_type& l)
  {
    return symbol_type (token::RSQPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LCURPAREN (const location_type& l)
  {
    return symbol_type (token::LCURPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RCURPAREN (const location_type& l)
  {
    return symbol_type (token::RCURPAREN, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::DOT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::COLON, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_AT (const location_type& l)
  {
    return symbol_type (token::AT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_LESSER (const location_type& l)
  {
    return symbol_type (token::LESSER, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_GREATER (const location_type& l)
  {
    return symbol_type (token::GREATER, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_STAR (const location_type& l)
  {
    return symbol_type (token::STAR, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::SLASH, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_PERCENT (const location_type& l)
  {
    return symbol_type (token::PERCENT, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_FLOATCONST (const FLOAT_T& v, const location_type& l)
  {
    return symbol_type (token::FLOATCONST, v, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_INTEGERCONST (const INTEGER_T& v, const location_type& l)
  {
    return symbol_type (token::INTEGERCONST, v, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_RATIONALCONST (const rational_t& v, const location_type& l)
  {
    return symbol_type (token::RATIONALCONST, v, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_STRCONST (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRCONST, v, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_UPLUS (const location_type& l)
  {
    return symbol_type (token::UPLUS, l);
  }

  casmi_parser::symbol_type
  casmi_parser::make_XIF (const location_type& l)
  {
    return symbol_type (token::XIF, l);
  }



} // yy
#line 2946 "GrammarParser.tab.h" // lalr1.cc:377




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
