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

#include "TypeInferencePass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"
#include "../casm-ir/src/Exception.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeInferencePass::id = 0;

static libpass::PassRegistration< TypeInferencePass > PASS(
    "ASTTypeInferencePass",
    "type inference of all types in the AST representation", "ast-infer", 0 );

class TypeInferenceVisitor final : public RecursiveVisitor
{
  public:
    TypeInferenceVisitor( Logger& log );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( UndefAtom& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
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

    void visit( ConditionalRule& node ) override;

    void visit( CaseRule& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;
    void visit( UpdateRule& node ) override;

    void assignment( const Node& node, TypedNode& lhs, TypedNode& rhs,
        const std::string& dst, const std::string& src, const Code& dstErr,
        const Code& srcErr, const Code& assignmentErr );

    const libcasm_ir::Annotation* annotate(
        Node& node, const std::vector< Expression::Ptr >& expressions = {} );

    void inference( const std::string& description,
        const libcasm_ir::Annotation* annotation, TypedNode& node,
        const std::vector< Expression::Ptr >& arguments = {} );

    void inference( FunctionDefinition& node,
        const std::vector< Expression::Ptr >& arguments );
    void inference( DerivedDefinition& node,
        const std::vector< Expression::Ptr >& arguments );
    void inference(
        RuleDefinition& node, const std::vector< Expression::Ptr >& arguments );

    void inference( QuantifierExpression& node );

    void push( VariableDefinition& node );
    void pop( VariableDefinition& node );
    VariableDefinition& find( const IdentifierPath& node );

  private:
    Logger& m_log;
    u1 m_functionInitially;

    std::unordered_map< std::string, VariableDefinition* > m_id2var;

    std::unordered_map< const Node*, std::vector< libcasm_ir::Type::ID > >
        m_resultTypes;
};

TypeInferenceVisitor::TypeInferenceVisitor( Logger& log )
: m_log( log )
, m_functionInitially( false )
{
}

void TypeInferenceVisitor::visit( FunctionDefinition& node )
{
    inference( node, {} );

    m_functionInitially = true;

    RecursiveVisitor::visit( node );

    m_functionInitially = false;

    inference( node, {} );
}

void TypeInferenceVisitor::visit( DerivedDefinition& node )
{
    inference( node, {} );

    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    const auto type = node.returnType()->type();
    assert( type );
    m_resultTypes[ node.expression().get() ].emplace_back( type->id() );

    RecursiveVisitor::visit( node );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }

    inference( node, {} );

    if( node.type() and node.expression()->type() )
    {
        const auto& expTy = node.expression()->type()->result();
        const auto& resTy = node.type()->result();

        if( resTy != expTy )
        {
            if( expTy.isInteger() and resTy.isInteger() )
            {
                return;
            }

            m_log.error( { node.expression()->sourceLocation() },
                "type mismatch: result type was '" + expTy.description()
                    + "', derived expects '"
                    + resTy.description()
                    + "'",
                Code::TypeInferenceDerivedReturnTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( RuleDefinition& node )
{
    inference( node, {} );

    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    RecursiveVisitor::visit( node );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }

    inference( node, {} );
}

void TypeInferenceVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );

    auto result = m_resultTypes.find( &node );
    if( result != m_resultTypes.end() and result->second.size() == 1 )
    {
        inference( "undef atom", 0, node );
    }
}

void TypeInferenceVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );

    auto result = m_resultTypes.find( &node );
    assert( node.value() and node.type() );

    std::vector< libcasm_ir::Type::ID > ty = { node.type()->id() };
    std::vector< libcasm_ir::Type::ID > tmp = {};

    if( result != m_resultTypes.end() )
    {
        std::set_intersection( result->second.begin(), result->second.end(),
            ty.begin(), ty.end(), std::back_inserter( tmp ) );
    }
    else
    {
        std::set_intersection( tmp.begin(), tmp.end(), ty.begin(), ty.end(),
            std::back_inserter( tmp ) );
    }

    m_resultTypes[&node ] = std::move( tmp );
}

void TypeInferenceVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );

    assert( not node.type() );

    switch( node.referenceType() )
    {
        case ReferenceAtom::ReferenceType::FUNCTION:
        {
            const auto& definition
                = std::static_pointer_cast< FunctionDefinition >(
                    node.reference() );

            inference( *definition, {} );
            assert(
                definition->type() and definition->type()->isRelation() );

            const auto type
                = libstdhl::make< libcasm_ir::FunctionReferenceType >(
                    std::static_pointer_cast< libcasm_ir::RelationType >(
                        definition->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceAtom::ReferenceType::DERIVED:
        {
            const auto& definition
                = std::static_pointer_cast< DerivedDefinition >(
                    node.reference() );

            inference( *definition, {} );
            assert(
                definition->type() and definition->type()->isRelation() );

            const auto type
                = libstdhl::make< libcasm_ir::FunctionReferenceType >(
                    std::static_pointer_cast< libcasm_ir::RelationType >(
                        definition->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceAtom::ReferenceType::BUILTIN:
        {
            // TODO
            break;
        }
        case ReferenceAtom::ReferenceType::RULE:
        {
            const auto& definition
                = std::static_pointer_cast< RuleDefinition >(
                    node.reference() );

            inference( *definition, {} );
            assert(
                definition->type() and definition->type()->isRelation() );

            const auto type
                = libstdhl::make< libcasm_ir::RuleReferenceType >(
                    std::static_pointer_cast< libcasm_ir::RelationType >(
                        definition->type() ) );
            node.setType( type );
            break;
        }
        case ReferenceAtom::ReferenceType::VARIABLE:
        {
            // TODO
            break;
        }
        default:
        {
            assert( !" unknown reference type! " );
        }
    }
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    const libcasm_ir::Annotation* annotation
        = annotate( node, node.arguments()->data() );

    RecursiveVisitor::visit( node );

    switch( node.targetType() )
    {
        case CallExpression::TargetType::VARIABLE:
        {
            try
            {
                auto& definition = find( *node.identifier() );

                if( definition.type() )
                {
                    if( not node.type() )
                    {
                        node.setType( definition.type() );
                    }
                    else
                    {
                        assert( *definition.type() == *node.type() );
                    }
                }
                else
                {
                    if( not node.type() )
                    {
                        const auto description
                            = "variable '" + path.path() + "'";
                        inference( description, 0, node );
                    }

                    definition.setType( node.type() );
                }
            }
            catch( const std::domain_error& e )
            {
                std::cerr << e.what() << "\n";
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            const auto description = "built-in '" + path.path() + "'";
            inference(
                description, annotation, node, node.arguments()->data() );

            std::vector< libcasm_ir::Type::Ptr > argTypeList;
            for( auto argumentType : *node.arguments() )
            {
                if( not argumentType->type() )
                {
                    m_log.debug( { argumentType->sourceLocation() },
                        "TODO: '" + path.path()
                            + "' has a non-typed argument(s)" );
                    return;
                }

                argTypeList.emplace_back( argumentType->type()->ptr_result() );
            }

            if( node.type() )
            {
                const auto type = libstdhl::make< libcasm_ir::RelationType >(
                    node.type(), argTypeList );

                node.setType( type );
            }

            break;
        }
        case CallExpression::TargetType::DERIVED:
        {
            assert( not node.type() );

            const auto& definition
                = std::static_pointer_cast< DerivedDefinition >(
                    node.targetDefinition() );

            inference( *definition, node.arguments()->data() );
            node.setType( definition->type() );
            break;
        }
        case CallExpression::TargetType::FUNCTION:
        {
            assert( not node.type() );

            const auto& definition
                = std::static_pointer_cast< FunctionDefinition >(
                    node.targetDefinition() );

            inference( *definition, node.arguments()->data() );
            node.setType( definition->type() );
            break;
        }
        case CallExpression::TargetType::RULE:
        {
            assert( not node.type() );

            const auto& definition
                = std::static_pointer_cast< RuleDefinition >(
                    node.targetDefinition() );

            inference( *definition, node.arguments()->data() );
            node.setType( definition->type() );
            break;
        }
        case CallExpression::TargetType::SELF:
        {
            assert( not node.type() );
            assert( node.targetDefinition() );
            node.setType( node.targetDefinition()->type() );
            break;
        }
        case CallExpression::TargetType::TYPE_DOMAIN:
        {
            if( not node.type() )
            {
                m_log.error( { node.sourceLocation() }, "TODO: TYPE_DOMAIN" );
            }
            break;
        }
        case CallExpression::TargetType::CONSTANT:
        {
            if( not node.type() )
            {
                m_log.error( { node.sourceLocation() }, "TODO: CONSTANT" );
            }
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( not" internal error" );
            break;
        }
    }

    if( node.type() )
    {
        const auto& call_type_args = node.type()->arguments();
        const auto& call_expr_args = *node.arguments();

        if( call_type_args.size() == call_expr_args.size() )
        {
            for( std::size_t pos = 0; pos < call_type_args.size(); pos++ )
            {
                const auto& exprArg = call_expr_args.at( pos );
                if( not exprArg->type() )
                {
                    continue;
                }

                const auto& callArgType = call_type_args.at( pos );
                if( callArgType->isInteger()
                    and exprArg->type()->result().isInteger() )
                {
                    continue;
                }

                if( *callArgType != exprArg->type()->result() )
                {
                    const std::unordered_map< CallExpression::TargetType, Code >
                        codes = {
                            { CallExpression::TargetType::FUNCTION,
                                Code::
                                    TypeInferenceFunctionArgumentTypeMismatch },
                            { CallExpression::TargetType::DERIVED,
                                Code::
                                    TypeInferenceDerivedArgumentTypeMismatch },
                            { CallExpression::TargetType::BUILTIN,
                                Code::
                                    TypeInferenceBuiltinArgumentTypeMismatch },
                            { CallExpression::TargetType::RULE,
                                Code::TypeInferenceRuleArgumentTypeMismatch },
                        };

                    const auto code = codes.find( node.targetType() );
                    assert( code != codes.end()
                            and " invalid target type with arguments " );

                    m_log.error( { exprArg->sourceLocation() },
                        "type mismatch: " + node.targetTypeName()
                            + " argument type at position "
                            + std::to_string( pos + 1 )
                            + " was '"
                            + exprArg->type()->description()
                            + "', "
                            + node.targetTypeName()
                            + " definition expects '"
                            + callArgType->description()
                            + "'",
                        code->second );
                }
            }
        }
        else
        {
            const std::unordered_map< CallExpression::TargetType, Code > codes
                = {
                    { CallExpression::TargetType::FUNCTION,
                        Code::TypeInferenceFunctionArgumentSizeMismatch },
                    { CallExpression::TargetType::DERIVED,
                        Code::TypeInferenceDerivedArgumentSizeMismatch },
                    { CallExpression::TargetType::BUILTIN,
                        Code::TypeInferenceBuiltinArgumentSizeMismatch },
                    { CallExpression::TargetType::RULE,
                        Code::TypeInferenceRuleArgumentSizeMismatch },
                  };

            const auto code = codes.find( node.targetType() );
            assert( code != codes.end()
                    and " invalid target type with arguments " );

            m_log.error( { node.sourceLocation() },
                "invalid argument size: " + node.targetTypeName() + " '"
                    + path.path()
                    + "' expects "
                    + std::to_string( call_type_args.size() )
                    + " arguments",
                code->second );

            m_log.info( { node.targetDefinition()->sourceLocation() },
                node.targetTypeName() + " '" + path.path()
                    + "' is defined as a relation '"
                    + node.type()->description()
                    + "', incorrect usage in line "
                    + std::to_string( node.sourceLocation().begin.line ) );
        }
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( not node.expression()->type() )
    {
        m_log.error( { node.sourceLocation() },
            "unable to resolve type of indirect call expression" );
    }

    node.setType( node.expression()->type() );

    assert( node.type()->isReference() );

    if( node.type()->isRuleReference() )
    {
        node.setTargetType( CallExpression::TargetType::RULE );
    }
    else if( node.type()->isFunctionReference() )
    {
        node.setTargetType( CallExpression::TargetType::FUNCTION );
    }
    else
    {
        m_log.debug( { node.expression()->sourceLocation() },
            "unable to set indirect call expression target type for expression "
            "kind of '"
                + node.expression()->description()
                + "'" );
    }

    const auto& refType
        = std::static_pointer_cast< libcasm_ir::ReferenceType >( node.type() );
    node.setType( refType->dereference() );
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    const auto* annotation = annotate( node, { node.expression() } );

    RecursiveVisitor::visit( node );

    const auto description
        = "operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.expression() } );
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    const auto* annotation = annotate( node, { node.left(), node.right() } );

    RecursiveVisitor::visit( node );

    const auto description
        = "operator '" + libcasm_ir::Value::token( node.op() ) + "'";
    inference( description, annotation, node, { node.left(), node.right() } );
}

void TypeInferenceVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& lhs = node.left()->type()->result();
    const auto& rhs = node.right()->type()->result();

    if( lhs != rhs )
    {
        m_log.error( { node.sourceLocation() },
            "types of range does not match, " + lhs.description() + " != "
                + rhs.description(),
            Code::TypeInferenceRangeExpressionTypeMismatch );
        return;
    }

    const auto range_type = libstdhl::get< libcasm_ir::RangeType >(
        node.left()->type()->ptr_result() );

    node.setType( range_type );
}

void TypeInferenceVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( LetExpression& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.initializer().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.initializer()->accept( *this );

    if( not node.variable()->type() and node.initializer()->type() )
    {
        node.variable()->setType( node.initializer()->type()->ptr_result() );
    }

    if( node.type() )
    {
        m_resultTypes[ node.expression().get() ].emplace_back(
            node.type()->id() );
    }

    node.expression()->accept( *this );
    pop( *node.variable() );

    if( not node.type() )
    {
        node.setType( node.expression()->type() );
    }

    assignment( node, *node.variable(), *node.initializer(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "let initializer", Code::TypeInferenceInvalidLetExpressionVariableType,
        Code::TypeInferenceInvalidLetExpressionInitializerType,
        Code::TypeInferenceInvalidLetExpressionTypeMismatch );

    if( not node.expression()->type() )
    {
        m_log.error( { node.expression()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& exprType = node.expression()->type()->result();
        if( *node.type() != exprType )
        {
            m_log.error(
                { node.sourceLocation(), node.expression()->sourceLocation() },
                node.description() + " has invalid expression type '"
                    + exprType.description()
                    + "' shall be '"
                    + node.type()->description()
                    + "'",
                Code::TypeInferenceInvalidLetExpressionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( ConditionalExpression& node )
{
    const auto& resTypes = m_resultTypes[&node ];
    for( auto type : resTypes )
    {
        m_resultTypes[ node.thenExpression().get() ].emplace_back( type );
        m_resultTypes[ node.elseExpression().get() ].emplace_back( type );
    }

    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();
    auto& thenExpr = *node.thenExpression();
    auto& elseExpr = *node.elseExpression();

    if( condExpr.type() )
    {
        if( condExpr.type()->id() != libcasm_ir::Type::BOOLEAN )
        {
            m_log.error( { condExpr.sourceLocation() },
                "condition type of conditional expression is not of type "
                "'Boolean', "
                "found type '"
                    + condExpr.type()->description()
                    + "'",
                Code::TypeInferenceInvalidConditionalExpressionCondition );
        }
    }

    if( resTypes.size() > 0 )
    {
        inference( "conditional expression", 0, node );
    }

    if( thenExpr.type() and elseExpr.type() )
    {
        if( *thenExpr.type() != *elseExpr.type() )
        {
            m_log.error(
                { thenExpr.sourceLocation(), elseExpr.sourceLocation() },
                "types of conditional expression paths does not match, "
                "found type '"
                    + thenExpr.type()->description()
                    + "' at 'then' path, and type '"
                    + elseExpr.type()->description()
                    + "' at 'else' path",
                Code::TypeInferenceInvalidConditionalExpressionPaths );
            return;
        }
    }

    if( thenExpr.type() and elseExpr.id() == Node::ID::UNDEF_ATOM )
    {
        elseExpr.setType( thenExpr.type() );
    }

    if( thenExpr.id() == Node::ID::UNDEF_ATOM and elseExpr.type() )
    {
        thenExpr.setType( elseExpr.type() );
    }

    if( node.type() and thenExpr.id() == Node::ID::UNDEF_ATOM
        and elseExpr.id() == Node::ID::UNDEF_ATOM )
    {
        thenExpr.setType( node.type() );
        elseExpr.setType( node.type() );
    }

    if( not node.type() )
    {
        node.setType( thenExpr.type() );
    }
}

void TypeInferenceVisitor::visit( ChooseExpression& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.universe().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    if( node.type() )
    {
        m_resultTypes[ node.expression().get() ].emplace_back(
            node.type()->id() );
    }

    node.expression()->accept( *this );
    pop( *node.variable() );

    if( not node.type() )
    {
        node.setType( node.expression()->type() );
    }

    if( not node.variable()->type() )
    {
        m_log.error( { node.variable()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error( { node.universe()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error( { node.variable()->sourceLocation(),
                             node.universe()->sourceLocation() },
                node.description() + " variable '"
                    + node.variable()->identifier()->name()
                    + "' of type '"
                    + node.variable()->type()->description()
                    + "' does not match the universe of type '"
                    + node.universe()->type()->result().description()
                    + "'",
                Code::
                    TypeInferenceInvalidChooseExpressionVariableTypeMismatch );
        }
    }

    if( not node.expression()->type() )
    {
        m_log.error( { node.expression()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& exprType = node.expression()->type()->result();
        if( *node.type() != exprType )
        {
            m_log.error(
                { node.sourceLocation(), node.expression()->sourceLocation() },
                node.description() + " has invalid expression type '"
                    + exprType.description()
                    + "' shall be '"
                    + node.type()->description()
                    + "'",
                Code::TypeInferenceInvalidChooseExpressionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( UniversalQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ExistentialQuantifierExpression& node )
{
    inference( node );
}

void TypeInferenceVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );

    const auto& condExpr = *node.condition();

    if( condExpr.type() )
    {
        if( condExpr.type()->result().id() != libcasm_ir::Type::BOOLEAN )
        {
            m_log.error( { condExpr.sourceLocation() },
                "invalid condition type '"
                    + condExpr.type()->result().description()
                    + ", shall be '"
                    + libcasm_ir::Type::token( libcasm_ir::Type::BOOLEAN )
                    + "'",
                Code::TypeInferenceConditionalRuleInvalidConditionType );
        }
    }
}

void TypeInferenceVisitor::visit( CaseRule& node )
{
    node.expression()->accept( *this );

    if( node.expression()->type() )
    {
        for( auto caseExpr : *node.cases() )
        {
            m_resultTypes[ caseExpr.get() ].emplace_back(
                node.expression()->type()->id() );
        }
    }

    node.cases()->accept( *this );
}

void TypeInferenceVisitor::visit( ExpressionCase& node )
{
    m_resultTypes[ node.expression().get() ] = m_resultTypes[&node ];

    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( DefaultCase& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.expression().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.expression()->accept( *this );

    if( not node.variable()->type() and node.expression()->type() )
    {
        node.variable()->setType( node.expression()->type()->ptr_result() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );

    assignment( node, *node.variable(), *node.expression(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "let expression", Code::TypeInferenceInvalidLetRuleVariableType,
        Code::TypeInferenceInvalidLetRuleExpressionType,
        Code::TypeInferenceLetRuleTypesMismatch );
}

void TypeInferenceVisitor::visit( ForallRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.universe().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );

    if( not node.variable()->type() )
    {
        m_log.error( { node.variable()->sourceLocation() },
            "no type found for 'forall' variable",
            Code::TypeInferenceForallVariableHasNoType );
    }

    if( not node.universe()->type() )
    {
        m_log.error( { node.universe()->sourceLocation() },
            "no type found for 'forall' universe",
            Code::TypeInferenceForallUniverseHasNoType );
    }

    if( node.variable()->type() and node.universe()->type() )
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error( { node.variable()->sourceLocation(),
                             node.universe()->sourceLocation() },
                node.description() + " variable '"
                    + node.variable()->identifier()->name()
                    + "' of type '"
                    + node.variable()->type()->description()
                    + "' does not match the universe of type '"
                    + node.universe()->type()->result().description()
                    + "'",
                Code::TypeInferenceForallRuleTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( ChooseRule& node )
{
    node.variable()->accept( *this );

    if( node.variable()->type() )
    {
        m_resultTypes[ node.universe().get() ].emplace_back(
            node.variable()->type()->id() );
    }

    push( *node.variable() );
    node.universe()->accept( *this );

    if( not node.variable()->type() and node.universe()->type() )
    {
        node.variable()->setType( node.universe()->type()->ptr_result() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );

    if( not node.variable()->type() )
    {
        m_log.error( { node.variable()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error( { node.universe()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.variable()->type() != node.universe()->type()->result() )
        {
            m_log.error( { node.variable()->sourceLocation(),
                             node.universe()->sourceLocation() },
                node.description() + " variable '"
                    + node.variable()->identifier()->name()
                    + "' of type '"
                    + node.variable()->type()->description()
                    + "' does not match the universe of type '"
                    + node.universe()->type()->result().description()
                    + "'",
                Code::TypeInferenceInvalidChooseRuleVariableTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::visit( UpdateRule& node )
{
    auto& func = *node.function();
    auto& expr = *node.expression();

    func.accept( *this );

    if( func.type() )
    {
        m_resultTypes[&expr ].emplace_back( func.type()->result().id() );
    }

    node.expression()->accept( *this );

    assignment( node, func, expr, "updated function", "updating expression",
        Code::TypeInferenceInvalidUpdateRuleFunctionType,
        Code::TypeInferenceInvalidUpdateRuleExpressionType,
        Code::TypeInferenceUpdateRuleTypesMismatch );
}

void TypeInferenceVisitor::assignment( const Node& node, TypedNode& lhs,
    TypedNode& rhs, const std::string& dst, const std::string& src,
    const Code& dstErr, const Code& srcErr, const Code& assignmentErr )
{
    if( lhs.type()
        and not rhs.type() ) // and rhs.id() == Node::ID::UNDEF_ATOM and  )
    {
        rhs.setType( lhs.type()->ptr_result() );
    }

    const auto error_count = m_log.errors();

    if( not lhs.type() )
    {
        m_log.error( { lhs.sourceLocation() }, "unable to infer type of " + dst,
            dstErr );
    }

    if( not rhs.type() )
    {
        m_log.error( { rhs.sourceLocation() }, "unable to infer type of " + src,
            srcErr );
    }

    if( error_count != m_log.errors() )
    {
        return;
    }

    const auto& tyLhs = lhs.type()->result();
    const auto& tyRhs = rhs.type()->result();

    if( tyLhs != tyRhs )
    {
        if( tyLhs.isInteger() and tyRhs.isInteger() )
        {
            // relaxation: mixed integer with range properties are checked
            //             at run-time
        }
        else if( tyLhs.isBit() and tyRhs.isBit()
                 and static_cast< const libcasm_ir::BitType& >( tyLhs )
                             .bitsize()
                         >= static_cast< const libcasm_ir::BitType& >( tyRhs )
                                .bitsize() )
        {
            // relaxation: mixed bit types are OK as long as
            //             bitsize(lhs) >= bitsize(rhs)
        }
        else if( tyLhs.isBit() and tyRhs.isInteger()
                 and rhs.id() == Node::ID::VALUE_ATOM )
        {
            // relaxation: lhs bit and rhs integer are OK as long as rhs is a
            //             integer constant with bitsize(lhs) >= bitsize(rhs)

            try
            {
                auto& valueAtom = static_cast< ValueAtom& >( rhs );
                assert( libcasm_ir::isa< libcasm_ir::IntegerConstant >(
                    valueAtom.value() ) );
                auto constant
                    = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        valueAtom.value() );

                const auto value = libstdhl::get< libcasm_ir::BitConstant >(
                    lhs.type()->ptr_result(),
                    static_cast< const libstdhl::Type::Natural& >(
                        constant->value() ) );

                valueAtom.setValue( value );
            }
            catch( const std::exception& e )
            {
                m_log.error( { lhs.sourceLocation(), rhs.sourceLocation() },
                    "type mismatch: " + src + " was '" + tyRhs.description()
                        + "', but "
                        + dst
                        + " expects '"
                        + tyLhs.description()
                        + "', "
                        + e.what(),
                    assignmentErr );
            }
        }
        else
        {
            m_log.error( { lhs.sourceLocation(), rhs.sourceLocation() },
                "type mismatch: " + src + " was '" + tyRhs.description()
                    + "', but "
                    + dst
                    + " expects '"
                    + tyLhs.description()
                    + "'",
                assignmentErr );
        }
    }
}

const libcasm_ir::Annotation* TypeInferenceVisitor::annotate(
    Node& node, const std::vector< Expression::Ptr >& expressions )
{
    const libcasm_ir::Annotation* annotation = nullptr;

    auto result = m_resultTypes.find( &node );

    if( node.id() == Type::ID::UNARY_EXPRESSION )
    {
        annotation = &libcasm_ir::Annotation::find(
            static_cast< const UnaryExpression& >( node ).op() );
    }
    else if( node.id() == Type::ID::BINARY_EXPRESSION )
    {
        annotation = &libcasm_ir::Annotation::find(
            static_cast< const UnaryExpression& >( node ).op() );
    }
    else if( node.id() == Type::ID::DIRECT_CALL_EXPRESSION )
    {

        auto& directCall = static_cast< DirectCallExpression& >( node );
        const auto& path = *directCall.identifier();

        switch( directCall.targetType() )
        {
            case CallExpression::TargetType::BUILTIN:
            {
                try
                {
                    const auto& builtin_annotation
                        = libcasm_ir::Annotation::find( path.baseName() );

                    annotation = &builtin_annotation;
                    directCall.setTargetBuiltinId( builtin_annotation.id() );

                    if( builtin_annotation.id()
                        == libcasm_ir::Value::AS_BIT_BUILTIN )
                    {
                        const auto& asbit_args = directCall.arguments()->data();
                        assert( asbit_args.size() == 2 );
                        const auto& asbit_size
                            = static_cast< const ValueAtom& >(
                                *asbit_args[ 1 ] );
                        if( asbit_size.id() == Node::ID::VALUE_ATOM
                            and asbit_size.type()
                            and asbit_size.type()->id()
                                    == libcasm_ir::Type::INTEGER )
                        {
                            const auto asbit_size_value
                                = std::static_pointer_cast< libcasm_ir::
                                        IntegerConstant >( asbit_size.value() );

                            const auto type
                                = libstdhl::get< libcasm_ir::BitType >(
                                    asbit_size_value );
                            directCall.setType( type );
                        }
                        else
                        {
                            m_log.error( { directCall.arguments()->data()[ 1 ]->sourceLocation() },
                             "2nd argument of built-in '"
                             + path.path()
                                         + "' is required to be a compile time 'Integer' constant value", Code::TypeInferenceBuiltinAsBitInvalid2ndArgumentType );
                        }
                    }
                }
                catch( const std::domain_error& e )
                {
                    m_log.error( { directCall.sourceLocation() },
                             "unable to resolve built-in symbol '"
                             + path.path()
                             + "', due to missing annotation information from 'libcasm-ir'" );
                }
                break;
            }
            case CallExpression::TargetType::DERIVED:  // [[fallthrough]]
            case CallExpression::TargetType::FUNCTION: // [[fallthrough]]
            case CallExpression::TargetType::RULE:
            {
                const auto& definition = directCall.targetDefinition();

                if( definition->type() )
                {
                    for( std::size_t c = 0; c < expressions.size(); c++ )
                    {
                        std::vector< libcasm_ir::Type::ID > ty = {
                            definition->type()->arguments()[ c ]->id()
                        };
                        std::vector< libcasm_ir::Type::ID > tmp = {};

                        std::copy( ty.begin(), ty.end(),
                            std::back_inserter(
                                m_resultTypes[ expressions[ c ].get() ] ) );
                    }

                    std::vector< libcasm_ir::Type::ID > ty
                        = { definition->type()->result().id() };
                    std::vector< libcasm_ir::Type::ID > tmp = {};

                    if( result != m_resultTypes.end() )
                    {
                        std::set_intersection( result->second.begin(),
                            result->second.end(), ty.begin(), ty.end(),
                            std::back_inserter( tmp ) );
                    }
                    else
                    {
                        std::set_intersection( tmp.begin(), tmp.end(),
                            ty.begin(), ty.end(),
                            std::back_inserter( tmp ) );
                    }

                    m_resultTypes[&node ] = std::move( tmp );
                }
                break;
            }
            case CallExpression::TargetType::SELF:
            {
                // CONT
                break;
            }
            case CallExpression::TargetType::TYPE_DOMAIN: // [[fallthrough]]
            case CallExpression::TargetType::CONSTANT:    // [[fallthrough]]
            case CallExpression::TargetType::VARIABLE:
            {
                break;
            }
            case CallExpression::TargetType::UNKNOWN:
            {
                assert( !" internal error" );
                break;
            }
        }
    }

    if( annotation )
    {
        if( result != m_resultTypes.end() )
        {
            const auto& map = annotation->map();

            for( auto t : result->second )
            {
                try
                {
                    const auto& map_result = map.at( t );

                    for( std::size_t c = 0; c < expressions.size(); c++ )
                    {
                        const auto& map_expr = map_result.at( c );

                        std::copy( map_expr.begin(), map_expr.end(),
                            std::back_inserter(
                                m_resultTypes[ expressions[ c ].get() ] ) );
                    }
                }
                catch( const std::out_of_range& e )
                {
                    continue;
                }
            }

            const auto& map_res = annotation->resultTypes();
            std::vector< libcasm_ir::Type::ID > tmp = {};

            std::set_intersection( result->second.begin(), result->second.end(),
                map_res.begin(), map_res.end(), std::back_inserter( tmp ) );

            m_resultTypes[&node ] = std::move( tmp );
        }
        else
        {
            for( std::size_t c = 0; c < expressions.size(); c++ )
            {
                const auto& map_expr = annotation->argumentTypes( c );

                std::copy( map_expr.begin(), map_expr.end(),
                    std::back_inserter(
                        m_resultTypes[ expressions[ c ].get() ] ) );
            }

            const auto& map_res = annotation->resultTypes();

            std::copy( map_res.begin(), map_res.end(),
                std::back_inserter( m_resultTypes[&node ] ) );
        }
    }

    return annotation;
}

void TypeInferenceVisitor::inference( const std::string& description,
    const libcasm_ir::Annotation* annotation, TypedNode& node,
    const std::vector< Expression::Ptr >& arguments )
{
    auto result = m_resultTypes.find( &node );
    if( result == m_resultTypes.end() )
    {
        m_log.error( { node.sourceLocation() },
            "unable to find type annotation for " + description,
            Code::TypeInferenceFoundNoTypeAnnotation );
        return;
    }

    if( annotation )
    {
        int pos = -1;
        int idx = 0;

        std::vector< libcasm_ir::Type::ID > argTypes;

        for( const auto& argument : arguments )
        {
            if( not argument->type() )
            {
                auto argTy = m_resultTypes.find( argument.get() );
                if( argTy != m_resultTypes.cend()
                    and argTy->second.size() == 1 )
                {
                    argTypes.emplace_back( *argTy->second.begin() );
                }
                else
                {
                    pos = idx;
                    argTypes.emplace_back( libcasm_ir::Type::ID::_TOP_ );
                }
            }
            else
            {
                const auto tid = argument->type()->result().id();
                argTypes.emplace_back( tid );
            }
            idx++;
        }

        try
        {
            const auto relation = annotation->resultTypeForRelation( argTypes );

            if( relation )
            {
                const std::vector< libcasm_ir::Type::ID > inf
                    = { relation->result };
                std::vector< libcasm_ir::Type::ID > tmp = {};

                std::set_intersection( result->second.begin(),
                    result->second.end(), inf.begin(), inf.end(),
                    std::back_inserter( tmp ) );

                m_resultTypes[&node ] = std::move( tmp );

                if( pos != -1
                    and arguments[ pos ]->id() == Node::ID::UNDEF_ATOM )
                {
                    auto undefAtom
                        = static_cast< UndefAtom* >( arguments[ pos ].get() );

                    m_resultTypes[ undefAtom ] = { relation->argument[ pos ] };
                    inference( "undef", 0, *undefAtom );
                }
            }
        }
        catch( const std::invalid_argument& e )
        {
            m_log.error( { node.sourceLocation() },
                "unable to infer result type of " + description );
        }
    }

    const auto& resTypes = m_resultTypes[&node ];

    if( resTypes.size() != 1 )
    {
        u1 first = true;
        std::string tmp = " from multiple possible types: ";
        for( auto t : resTypes )
        {
            tmp += ( first ? "" : ", " );
            tmp += "'" + libcasm_ir::Type::token( t ) + "'";
            first = false;
        }

        m_log.error( { node.sourceLocation() },
            "unable to infer result type of " + description
                + ( resTypes.size() > 0 ? tmp : "" ),
            ( resTypes.size() > 0 ? Code::TypeInferenceFoundMultipleResultTypes
                                  : Code::TypeInferenceFoundNoResultType ) );
        return;
    }

    libcasm_ir::Type::Ptr inferedType = nullptr;
    if( annotation and arguments.size() > 0 )
    {
        std::vector< libcasm_ir::Type::Ptr > argTypes = {};

        for( auto argument : arguments )
        {
            if( not argument->type() )
            {
                return;
            }
            argTypes.emplace_back( argument->type()->ptr_result() );
        }

        try
        {
            inferedType = annotation->inference( argTypes, {} );
        }
        catch( const libcasm_ir::TypeArgumentException& e )
        {
            m_log.error( { arguments[ e.position() ]->sourceLocation() },
                "type mismatch: " + description + " argument type at position "
                    + std::to_string( e.position() + 1 )
                    + ": "
                    + e.what(),
                Code::TypeInferenceArgumentTypeMismatch );
            return;
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() },
                "unable to infer result type of " + description + ": "
                    + e.what(),
                Code::TypeInferenceNotDefinedForExpression );
        }
    }

    switch( *resTypes.begin() )
    {
        case libcasm_ir::Type::VOID:
        {
            node.setType( libstdhl::get< libcasm_ir::VoidType >() );
            break;
        }
        case libcasm_ir::Type::BOOLEAN:
        {
            node.setType( libstdhl::get< libcasm_ir::BooleanType >() );
            break;
        }
        case libcasm_ir::Type::INTEGER:
        {
            node.setType(
                libstdhl::get< libcasm_ir::IntegerType >() ); // TODO: PPA:
                                                              // check for
                                                              // ranged integers
            break;
        }
        case libcasm_ir::Type::BIT:
        {
            if( node.type() )
            {
                return;
            }

            node.setType( inferedType );
            break;
        }
        case libcasm_ir::Type::STRING:
        {
            node.setType( libstdhl::get< libcasm_ir::StringType >() );
            break;
        }
        case libcasm_ir::Type::FLOATING:
        {
            node.setType( libstdhl::get< libcasm_ir::FloatingType >() );
            break;
        }
        case libcasm_ir::Type::RATIONAL:
        {
            node.setType( libstdhl::get< libcasm_ir::RationalType >() );
            break;
        }
        case libcasm_ir::Type::RULE_REFERENCE:
        {
            break;
        }
        case libcasm_ir::Type::FUNCTION_REFERENCE:
        {
            assert( 0 ); // TODO: PPA: retrieve relation to
                         // construct FuncRef type
            // node.setType( ? );
            break;
        }
        default:
        {
            assert( 0 );
        }
    }
}

void TypeInferenceVisitor::inference(
    FunctionDefinition& node, const std::vector< Expression::Ptr >& arguments )
{
    if( node.defaultValue()->id() == Node::ID::UNDEF_ATOM
        and not node.defaultValue()->type() )
    {
        node.defaultValue()->setType( node.returnType()->type() );
    }

    if( node.type() )
    {
        return;
    }

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + node.identifier()->name()
                    + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    if( not node.returnType()->type() )
    {
        m_log.info( { node.returnType()->sourceLocation() },
            "TODO: '" + node.identifier()->name() + "' has a no return type" );
        return;
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference(
    DerivedDefinition& node, const std::vector< Expression::Ptr >& arguments )
{
    if( node.type() )
    {
        return;
    }

    std::size_t pos = 0;
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            if( arguments.size() > 0 and pos < arguments.size()
                and arguments[ pos ]->type() )
            {
                argTypeList.emplace_back( arguments[ pos ]->type() );
                argumentType->setType( arguments[ pos ]->type() );
            }
            else
            {
                m_log.debug( "'" + node.identifier()->name()
                             + "' has a non-typed argument(s)" );
                return;
            }
        }
        else
        {
            argTypeList.emplace_back( argumentType->type() );
        }
        pos++;
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference(
    RuleDefinition& node, const std::vector< Expression::Ptr >& arguments )
{
    if( node.type() )
    {
        return;
    }

    std::size_t pos = 0;
    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            if( arguments.size() > 0 and arguments[ pos ]->type() )
            {
                argTypeList.emplace_back( arguments[ pos ]->type() );
                argumentType->setType( arguments[ pos ]->type() );
            }
            else
            {
                m_log.debug( "'" + node.identifier()->name()
                             + "' has a non-typed argument(s)" );
                return;
            }
        }
        else
        {
            argTypeList.emplace_back( argumentType->type() );
        }
        pos++;
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference( QuantifierExpression& node )
{
    node.setType( libstdhl::get< libcasm_ir::BooleanType >() );

    m_resultTypes[ node.proposition().get() ].emplace_back( node.type()->id() );

    if( node.predicateVariable()->type() )
    {
        m_resultTypes[ node.universe().get() ].emplace_back(
            node.predicateVariable()->type()->id() );
    }

    node.universe()->accept( *this );

    node.predicateVariable()->accept( *this );

    if( not node.predicateVariable()->type() and node.universe()->type() )
    {
        node.predicateVariable()->setType(
            node.universe()->type()->ptr_result() );
    }

    push( *node.predicateVariable() );
    node.proposition()->accept( *this );
    pop( *node.predicateVariable() );

    if( not node.predicateVariable()->type() )
    {
        m_log.error( { node.predicateVariable()->sourceLocation() },
            "no type found", Code::TypeInferenceInvalidExpression );
    }
    else if( not node.universe()->type() )
    {
        m_log.error( { node.universe()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        if( *node.predicateVariable()->type()
            != node.universe()->type()->result() )
        {
            m_log.error( { node.predicateVariable()->sourceLocation(),
                             node.universe()->sourceLocation() },
                node.description() + " predicate variable '"
                    + node.predicateVariable()->identifier()->name()
                    + "' of type '"
                    + node.predicateVariable()->type()->description()
                    + "' does not match the universe of type '"
                    + node.universe()->type()->result().description()
                    + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::
                          TypeInferenceQuantifierExistentialPredicateTypeMismatch
                    : Code::
                          TypeInferenceQuantifierUniversalPredicateTypeMismatch );
        }
    }

    if( not node.proposition()->type() )
    {
        m_log.error( { node.proposition()->sourceLocation() }, "no type found",
            Code::TypeInferenceInvalidExpression );
    }
    else
    {
        const auto& propType = node.proposition()->type()->result();
        if( *node.type() != propType )
        {
            m_log.error( { node.proposition()->sourceLocation() },

                node.description() + " has invalid proposition type '"
                    + propType.description()
                    + "' shall be '"
                    + node.type()->description()
                    + "'",

                ( node.id() == Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION )
                    ? Code::
                          TypeInferenceQuantifierExistentialPropositionTypeMismatch
                    : Code::
                          TypeInferenceQuantifierUniversalPropositionTypeMismatch );
        }
    }
}

void TypeInferenceVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    auto result = m_id2var.emplace( name, &node );
    if( not result.second )
    {
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
}

void TypeInferenceVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
}

VariableDefinition& TypeInferenceVisitor::find( const IdentifierPath& node )
{
    auto result = m_id2var.find( node.baseName() );
    if( result == m_id2var.end() )
    {
        throw std::domain_error(
            "unable to find symbol '" + node.path() + "'" );
    }

    return *result->second;
}

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeCheckPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< TypeCheckPass >();
    const auto specification = data->specification();

    TypeInferenceVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during type inference", errors );
        return false;
    }

    pr.setResult< TypeInferencePass >( data );

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
