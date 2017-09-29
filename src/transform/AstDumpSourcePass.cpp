//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
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

#include "AstDumpSourcePass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Specification.h"
#include "../Logger.h"
#include "../analyze/ConsistencyCheckPass.h"
#include "../ast/RecursiveVisitor.h"
#include "../ast/Definition.h"
#include "../ast/Expression.h"
#include "../ast/Rule.h"

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

char AstDumpSourcePass::id = 0;

static libpass::PassRegistration< AstDumpSourcePass > PASS( "AstDumpSourcePass",
    "outputs the parsed AST as a CASM input specification to stdout",
    "ast-dump", 0 );

class Indentation
{
  public:
    class NextLevel
    {
      public:
        explicit NextLevel( Indentation& indentation )
        : m_indentation( indentation )
        {
            m_indentation.push();
        }

        ~NextLevel()
        {
            m_indentation.pop();
        }

      private:
        Indentation& m_indentation;
    };

    class PreviousLevel
    {
      public:
        explicit PreviousLevel( Indentation& indentation )
        : m_indentation( indentation )
        {
            m_indentation.pop();
        }

        ~PreviousLevel()
        {
            m_indentation.push();
        }

      private:
        Indentation& m_indentation;
    };

  public:
    explicit Indentation( std::size_t stepSize )
    : m_stepSize( stepSize )
    , m_length( 0 )
    {
    }

    void push()
    {
        m_length += m_stepSize;
    }

    void pop()
    {
        assert( m_length >= m_stepSize );
        m_length -= m_stepSize;
    }

    std::size_t length() const
    {
        return m_length;
    }

  private:
    const std::size_t m_stepSize;
    std::size_t m_length;
};

std::ostream& operator<<( std::ostream& stream, const Indentation& indentation )
{
    stream << std::string( indentation.length(), ' ' );
    return stream;
}

class AstDumpSourceVisitor final : public Visitor
{
  public:
    explicit AstDumpSourceVisitor( std::ostream& stream );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( SkipRule& node ) override;
    void visit( ConditionalRule& node ) override;
    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( IterateRule& node ) override;
    void visit( BlockRule& node ) override;
    void visit( SequenceRule& node ) override;
    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;

    void visit( UnresolvedType& node ) override;
    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( Identifier& node ) override;
    void visit( IdentifierPath& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

  private:
    std::ostream& m_stream;
    Indentation m_indentation;
};

AstDumpSourceVisitor::AstDumpSourceVisitor( std::ostream& stream )
: m_stream( stream )
, m_indentation( 4 )
{
}

void AstDumpSourceVisitor::visit( VariableDefinition& node )
{
    node.identifier()->accept( *this );
    m_stream << " : ";
    node.variableType()->accept( *this );
}

void AstDumpSourceVisitor::visit( FunctionDefinition& node )
{
    m_stream << "function ";
    std::string classification;
    switch( node.classification() )
    {
        case FunctionDefinition::Classification::IN:
            classification = "in";
            break;
        case FunctionDefinition::Classification::CONTROLLED:
            classification = "controlled";
            break;
        case FunctionDefinition::Classification::SHARED:
            classification = "shared";
            break;
        case FunctionDefinition::Classification::OUT:
            classification = "out";
            break;
        case FunctionDefinition::Classification::STATIC:
            classification = "static";
            break;
    }
    if( node.symbolic() )
    {
        m_stream << "(symbolic, " + classification + ") ";
    }
    else
    {
        m_stream << "(" + classification + ") ";
    }
    node.identifier()->accept( *this );
    m_stream << " : ";
    bool firstArgType = true;
    for( auto& t : *node.argumentTypes() )
    {
        if( not firstArgType )
        {
            m_stream << " * ";
        }
        t->accept( *this );
        firstArgType = false;
    }
    m_stream << " -> ";
    node.returnType()->accept( *this );
    m_stream << " default { ";
    node.defaultValue()->accept( *this );
    m_stream << " } initially { ";
    bool firstInitializer = true;
    for( auto& i : *node.initializers() )
    {
        if( not firstInitializer )
        {
            m_stream << ", ";
        }
        i->accept( *this );
        firstInitializer = false;
    }
    m_stream << " }";
}

void AstDumpSourceVisitor::visit( DerivedDefinition& node )
{
    m_stream << "derived ";
    node.identifier()->accept( *this );
    m_stream << "(";
    bool firstArg = true;
    for( auto& a : *node.arguments() )
    {
        if( not firstArg )
        {
            m_stream << ", ";
        }
        a->accept( *this );
        firstArg = false;
    }
    m_stream << ") -> ";
    node.returnType()->accept( *this );
    const auto levelGuard = Indentation::NextLevel( m_indentation );
    m_stream << " =\n" << m_indentation;
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( RuleDefinition& node )
{
    m_stream << "rule ";
    node.identifier()->accept( *this );
    m_stream << "(";
    bool firstArg = true;
    for( auto& a : *node.arguments() )
    {
        if( not firstArg )
        {
            m_stream << ", ";
        }
        a->accept( *this );
        firstArg = false;
    }
    m_stream << ") -> ";
    node.returnType()->accept( *this );
    m_stream << " =\n";
    const auto levelGuard = Indentation::NextLevel( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourceVisitor::visit( EnumerationDefinition& node )
{
    m_stream << "enum ";
    node.identifier()->accept( *this );
    m_stream << " = {";
    bool firstEnumerator = true;
    for( auto& e : *node.enumerators() )
    {
        if( not firstEnumerator )
        {
            m_stream << ", ";
        }
        e->accept( *this );
        firstEnumerator = false;
    }
    m_stream << "}";
}

void AstDumpSourceVisitor::visit( ValueAtom& node )
{
    m_stream << node.value()->name();
}

void AstDumpSourceVisitor::visit( ReferenceAtom& node )
{
    m_stream << "@";
    node.identifier()->accept( *this );
}

void AstDumpSourceVisitor::visit( UndefAtom& node )
{
    m_stream << "undef";
}

void AstDumpSourceVisitor::visit( DirectCallExpression& node )
{
    node.identifier()->accept( *this );
    if( not node.arguments()->empty() )
    {
        m_stream << "(";
        bool firstArg = true;
        for( auto& a : *node.arguments() )
        {
            if( not firstArg )
            {
                m_stream << ", ";
            }
            a->accept( *this );
            firstArg = false;
        }
        m_stream << ")";
    }
}

void AstDumpSourceVisitor::visit( IndirectCallExpression& node )
{
    m_stream << "(*";
    node.expression()->accept( *this );
    m_stream << ")(";
    bool firstArg = true;
    for( auto& a : *node.arguments() )
    {
        if( not firstArg )
        {
            m_stream << ", ";
        }
        a->accept( *this );
        firstArg = false;
    }
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( UnaryExpression& node )
{
    m_stream << ir::Value::token( node.op() );
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( BinaryExpression& node )
{
    node.left()->accept( *this );
    m_stream << " " << ir::Value::token( node.op() ) << " ";
    node.right()->accept( *this );
}

void AstDumpSourceVisitor::visit( RangeExpression& node )
{
    m_stream << "[";
    node.left()->accept( *this );
    m_stream << "..";
    node.right()->accept( *this );
    m_stream << "]";
}

void AstDumpSourceVisitor::visit( ListExpression& node )
{
    m_stream << "[";
    bool firstExpr = true;
    for( auto& e : *node.expressions() )
    {
        if( not firstExpr )
        {
            m_stream << ", ";
        }
        e->accept( *this );
        firstExpr = false;
    }
    m_stream << "]";
}

void AstDumpSourceVisitor::visit( LetExpression& node )
{
    m_stream << "let ";
    node.variable()->accept( *this );
    m_stream << " = ";
    node.initializer()->accept( *this );
    m_stream << " in ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( ConditionalExpression& node )
{
    m_stream << "if ";
    node.condition()->accept( *this );
    m_stream << " then ";
    node.thenExpression()->accept( *this );
    m_stream << " else ";
    node.elseExpression()->accept( *this );
}

void AstDumpSourceVisitor::visit( ChooseExpression& node )
{
    m_stream << "choose ";
    node.variable()->accept( *this );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " do ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( UniversalQuantifierExpression& node )
{
    m_stream << "forall ";
    node.predicateVariable()->accept( *this );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " holds ";
    node.proposition()->accept( *this );
}

void AstDumpSourceVisitor::visit( ExistentialQuantifierExpression& node )
{
    m_stream << "exists ";
    node.predicateVariable()->accept( *this );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " with ";
    node.proposition()->accept( *this );
}

void AstDumpSourceVisitor::visit( SkipRule& node )
{
    m_stream << m_indentation << "skip";
}

void AstDumpSourceVisitor::visit( ConditionalRule& node )
{
    m_stream << m_indentation << "if ";
    node.condition()->accept( *this );
    m_stream << " then\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.thenRule()->accept( *this );
    }
    m_stream << "\n" << m_indentation << "else\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.elseRule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( CaseRule& node )
{
    m_stream << m_indentation << "case ";
    node.expression()->accept( *this );
    m_stream << " of\n" << m_indentation << "{\n";
    for( auto& c : *node.cases() )
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        c->accept( *this );
        m_stream << "\n";
    }
    m_stream << m_indentation << "}";
}

void AstDumpSourceVisitor::visit( LetRule& node )
{
    m_stream << m_indentation << "let ";
    node.variable()->accept( *this );
    m_stream << " = ";
    node.expression()->accept( *this );
    m_stream << " in\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( ForallRule& node )
{
    m_stream << m_indentation << "forall ";
    node.variable()->accept( *this );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " do\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( ChooseRule& node )
{
    m_stream << m_indentation << "choose ";
    node.variable()->accept( *this );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " do\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( IterateRule& node )
{
    m_stream << "iterate\n";
    {
        const auto levelGuard = Indentation::NextLevel( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( BlockRule& node )
{
    {
        const auto levelGuard = Indentation::PreviousLevel( m_indentation );
        m_stream << m_indentation << "{\n";
    }
    for( auto& r : *node.rules() )
    {
        r->accept( *this );
        m_stream << "\n";
    }
    {
        const auto levelGuard = Indentation::PreviousLevel( m_indentation );
        m_stream << m_indentation << "}";
    }
}

void AstDumpSourceVisitor::visit( SequenceRule& node )
{
    {
        const auto levelGuard = Indentation::PreviousLevel( m_indentation );
        m_stream << m_indentation << "{|\n";
    }
    for( auto& r : *node.rules() )
    {
        r->accept( *this );
        m_stream << "\n";
    }
    {
        const auto levelGuard = Indentation::PreviousLevel( m_indentation );
        m_stream << m_indentation << "|}";
    }
}

void AstDumpSourceVisitor::visit( UpdateRule& node )
{
    m_stream << m_indentation;
    node.function()->accept( *this );
    m_stream << " := ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( CallRule& node )
{
    m_stream << m_indentation << "call ";
    node.call()->accept( *this );
}

void AstDumpSourceVisitor::visit( UnresolvedType& node )
{
    node.name()->accept( *this );
}

void AstDumpSourceVisitor::visit( BasicType& node )
{
    node.name()->accept( *this );
}

void AstDumpSourceVisitor::visit( ComposedType& node )
{
    node.name()->accept( *this );
    m_stream << "<";
    bool firstSubType = true;
    for( auto& s : *node.subTypes() )
    {
        if( not firstSubType )
        {
            m_stream << ", ";
        }
        s->accept( *this );
        firstSubType = false;
    }
    m_stream << ">";
}

void AstDumpSourceVisitor::visit( FixedSizedType& node )
{
    node.name()->accept( *this );
    m_stream << "<";
    node.size()->accept( *this );
    m_stream << ">";
}

void AstDumpSourceVisitor::visit( RelationType& node )
{
    m_stream << "<";

    u1 first = true;
    for( auto& s : *node.argumentTypes() )
    {
        m_stream << ( first ? "" : " * " );
        s->accept( *this );
        first = false;
    }

    m_stream << " -> ";

    node.returnType()->accept( *this );

    m_stream << ">";
}

void AstDumpSourceVisitor::visit( BasicAttribute& node )
{
    m_stream << "[ ";
    node.identifier()->accept( *this );
    m_stream << " ]\n";
}

void AstDumpSourceVisitor::visit( ExpressionAttribute& node )
{
    m_stream << "[ ";
    node.identifier()->accept( *this );
    m_stream << " ";
    node.expression()->accept( *this );
    m_stream << " ]\n";
}

void AstDumpSourceVisitor::visit( Identifier& node )
{
    m_stream << node.name();
}

void AstDumpSourceVisitor::visit( IdentifierPath& node )
{
    m_stream << node.path();
}

void AstDumpSourceVisitor::visit( ExpressionCase& node )
{
    m_stream << m_indentation;
    node.expression()->accept( *this );
    m_stream << ":\n";
    const auto levelGuard = Indentation::NextLevel( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourceVisitor::visit( DefaultCase& node )
{
    m_stream << m_indentation << "default:\n";
    const auto levelGuard = Indentation::NextLevel( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourcePass::usage( libpass::PassUsage& pu )
{
    pu.require< ConsistencyCheckPass >();
}

u1 AstDumpSourcePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.result< ConsistencyCheckPass >();
    const auto& specification = data->specification();

    auto& outputStream = std::cout;

    AstDumpSourceVisitor visitor{ outputStream };

    outputStream << "CASM\n";
    for( const auto& definition : *specification->definitions() )
    {
        outputStream << "\n";
        definition->accept( visitor );
        outputStream << "\n";
    }

    return true;
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
