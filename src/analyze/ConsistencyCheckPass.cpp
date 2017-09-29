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

#include "ConsistencyCheckPass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../Namespace.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char ConsistencyCheckPass::id = 0;

static libpass::PassRegistration< ConsistencyCheckPass > PASS(
    "ASTConsistencyCheckPass",
    "checks the consistency of the AST representation", "ast-check", 0 );

static const std::string PROGRAM = "program";

//
// ConsistencyCheckVisitor
//

class ConsistencyCheckVisitor final : public RecursiveVisitor
{
  public:
    ConsistencyCheckVisitor( Logger& m_log, const Namespace& symboltable );

    void visit( Specification& node );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;

    void visit( ReferenceAtom& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;

    void visit( UpdateRule& node ) override;
    void visit( CallRule& node ) override;

    void verify( const TypedNode& node );

  private:
    Logger& m_log;
    const Namespace& m_symboltable;
    u1 m_functionInitially;
    u1 m_sideEffectFree;
};

ConsistencyCheckVisitor::ConsistencyCheckVisitor(
    Logger& log, const Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_functionInitially( false )
, m_sideEffectFree( false )
{
}

void ConsistencyCheckVisitor::visit( Specification& node )
{
    try
    {
        m_symboltable.find( PROGRAM );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( "no init definition found in the specification",
            Code::AgentInitRuleNotDefined );
    }

    node.definitions()->accept( *this );
}

void ConsistencyCheckVisitor::visit( FunctionDefinition& node )
{
    verify( *node.returnType() );

    for( auto arg : *node.argumentTypes() )
    {
        verify( *arg );
    }

    m_functionInitially = true;

    node.initializers()->accept( *this );

    m_functionInitially = false;

    node.identifier()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
    node.defaultValue()->accept( *this );
    node.attributes()->accept( *this );
}

void ConsistencyCheckVisitor::visit( DerivedDefinition& node )
{
    for( auto arg : *node.arguments() )
    {
        verify( *arg );
    }

    m_sideEffectFree = true;

    RecursiveVisitor::visit( node );

    m_sideEffectFree = false;
}

void ConsistencyCheckVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( DirectCallExpression& node )
{
    assert( node.targetType() != CallExpression::TargetType::UNKNOWN
            && "all calls should have been resolved by previous passes" );

    RecursiveVisitor::visit( node );

    if( node.targetType() == CallExpression::TargetType::FUNCTION )
    {
        const auto& function
            = node.targetDefinition()->ptr< FunctionDefinition >();
        if( function->classification()
            == FunctionDefinition::Classification::OUT )
        {
            // calling an out function isn't allowed (write-only)
            m_log.error( { node.sourceLocation() },
                "calling function '" + node.identifier()->path()
                    + "' is not allowed, it is classified as '"
                    + function->classificationName()
                    + "' ",
                Code::DirectCallExpressionInvalidClassifier );

            m_log.info( { function->sourceLocation() },
                "function '" + node.identifier()->path()
                    + "' is classified as '"
                    + function->classificationName()
                    + "', incorrect usage in line "
                    + std::to_string( node.sourceLocation().begin.line ) );
        }
    }

    if( node.targetType() == CallExpression::TargetType::RULE )
    {
        if( m_sideEffectFree )
        {
            m_log.error( { node.sourceLocation() },
                "calling rule '" + node.identifier()->path()
                    + "' is not allowed inside a derived definition",
                Code::NotSideEffectFreeRuleCall );
        }
    }
}

void ConsistencyCheckVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );

    const auto& func = node.function();
    if( func->targetType() != CallExpression::TargetType::FUNCTION )
    {
        m_log.error( { func->sourceLocation() },
            "updating " + func->targetTypeName() + " '"
                + func->identifier()->path()
                + "' is not allowed, only function symbols are allowed",
            Code::UpdateRuleFunctionSymbolIsInvalid );
        return;
    }

    const auto& def = func->targetDefinition()->ptr< FunctionDefinition >();

    bool updatesAllowed;
    switch( def->classification() )
    {
        case FunctionDefinition::Classification::IN:
        {
            updatesAllowed = false;
            break;
        }
        case FunctionDefinition::Classification::STATIC:
        {
            // static function updates are only allowed during initialisation
            updatesAllowed = m_functionInitially;
            break;
        }
        default:
        {
            updatesAllowed = true;
        }
    }

    if( not updatesAllowed )
    {
        m_log.error( { func->sourceLocation() },
            "updating function '" + func->identifier()->path()
                + "' is not allowed, it is classified as '"
                + def->classificationName()
                + "' ",
            Code::UpdateRuleInvalidClassifier );

        m_log.info( { def->sourceLocation() },
            "function '" + func->identifier()->path() + "' is classified as '"
                + def->classificationName()
                + "', incorrect usage in line "
                + std::to_string( func->sourceLocation().begin.line ) );
    }
}

void ConsistencyCheckVisitor::visit( CallRule& node )
{
    RecursiveVisitor::visit( node );

    const auto& call = node.call();
    const auto& kind = node.allowedCallTargetTypes();

    if( kind.find( call->targetType() ) == kind.end() )
    {
        m_log.error( { node.sourceLocation() },
            call->targetTypeName() + " is not allowed to be called",
            Code::Unspecified );
    }
}

void ConsistencyCheckVisitor::verify( const TypedNode& node )
{
    if( not node.type() )
    {
        m_log.error( { node.sourceLocation() }, "unable to infer type",
            Code::TypeInferenceUnableToInferType );
    }
}

//
// ConsistencyCheckPass
//

void ConsistencyCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeInferencePass >();
}

u1 ConsistencyCheckPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< TypeInferencePass >();
    const auto specification = data->specification();

    ConsistencyCheckVisitor visitor( log, specification->symboltable() );
    visitor.visit( *specification );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during consistency checking", errors );
        return false;
    }

    pr.setResult< ConsistencyCheckPass >(
        libstdhl::make< Data >( specification ) );

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
