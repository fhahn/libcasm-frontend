//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                Ioan Molnar
//                <https://github.com/casm-lang/libcasm-fe>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "SymbolicConsistencyVisitor.h"

#include <libstdhl/RestoreOnScopeExit>

#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace libcasm_fe;
using SCVisitor = SymbolicConsistencyVisitor;

template < typename T >
class ScopedOverwrite : public libstdhl::RestoreOnScopeExit< T >
{
  public:
    ScopedOverwrite( T& target, const T& value )
    : RestoreOnScopeExit< T >( target )
    {
        target = value;
    }
};

SCVisitor::RuleDependency::RuleDependency( const Ast::RuleDefinition::Ptr& rule )
: m_rule( rule )
, m_dependsOn()
, m_usedBy()
, m_returns( FunctionType::UNKNOWN )
, m_arguments( rule->arguments()->size(), FunctionType::UNKNOWN )
, m_status( Status::INIT )
{
    if( rule->type()->result().isVoid() )
    {
        m_returns = FunctionType::NUMERIC;
    }
}

const Ast::RuleDefinition::Ptr& SCVisitor::RuleDependency::rule( void ) const
{
    return m_rule;
}

std::set< SCVisitor::RuleDependency::Ptr >& SCVisitor::RuleDependency::dependsOn( void )
{
    return m_dependsOn;
}

std::set< SCVisitor::RuleDependency::Ptr >& SCVisitor::RuleDependency::usedBy( void )
{
    return m_usedBy;
}

void SCVisitor::RuleDependency::calls( RuleDependency::Ptr& callee )
{
    m_dependsOn.insert( callee );
}

void SCVisitor::RuleDependency::isCalledBy(
    RuleDependency::Ptr& caller, std::vector< FunctionType >& args )
{
    for( size_t i = 0; i < args.size(); ++i )
    {
        m_arguments[ i ] = m_arguments[ i ] && args[ i ];
    }
    m_usedBy.insert( caller );
}

SCVisitor::FunctionType SCVisitor::RuleDependency::returns( void )
{
    return m_returns;
}

bool SCVisitor::RuleDependency::fullyDefined( void ) const
{
    return std::all_of( m_arguments.begin(), m_arguments.end(), [ & ]( auto& arg ) {
        return arg != FunctionType::UNKNOWN;
    } );
}

void SCVisitor::RuleDependency::define( void )
{
    for( auto& arg : m_arguments )
    {
        if( arg == FunctionType::UNKNOWN )
        {
            arg = FunctionType::NUMERIC;
        }
    }
}

SCVisitor::RuleDependency::Status SCVisitor::RuleDependency::status( void ) const
{
    return m_status;
}

void SCVisitor::RuleDependency::setStatus( Status status )
{
    m_status = status;
}

bool SCVisitor::RuleDependency::inStatus( std::vector< Status > status ) const
{
    return std::any_of( status.begin(), status.end(), [ & ]( auto s ) { return s == m_status; } );
}

SCVisitor::RuleDependency::Ptr SCVisitor::findOrInsert( const Ast::RuleDefinition::Ptr& rule )
{
    auto ruleIt = std::find_if( m_dependencies.begin(), m_dependencies.end(), [ & ]( auto& r ) {
        return r->rule() == rule;
    } );
    if( ruleIt == m_dependencies.end() )
    {
        return *( m_dependencies.insert( std::make_shared< RuleDependency >( rule ) ) ).first;
    }
    else
    {
        return *ruleIt;
    }
}

SCVisitor::Conflict::Conflict(
    const Ast::FunctionDefinition::Ptr& function,
    const std::vector< libstdhl::SourceLocation >& locations,
    Cause cause )
: Conflict( description( function, cause ), function, locations, cause )
{
}

SCVisitor::Conflict::Conflict(
    const std::string& msg,
    const Ast::FunctionDefinition::Ptr& function,
    const std::vector< libstdhl::SourceLocation >& locations,
    Cause cause )
: Exception( locations, msg, Code::Unspecified )
, m_function( function )
, m_cause( cause )
{
}

Ast::FunctionDefinition::Ptr& SCVisitor::Conflict::conflictingFunction( void )
{
    return m_function;
}

std::string SCVisitor::Conflict::description(
    const Ast::FunctionDefinition::Ptr& function, Cause cause )
{
    std::stringstream str;
    str << "Promoting function '" << function->identifier()->name() << "' to be symbolic."
        << std::endl;
    str << "Cause: " << causeDescription( cause );
    return str.str();
}

std::string SCVisitor::Conflict::causeDescription( Cause cause )
{
    switch( cause )
    {
        case Cause::UPDATE:
        {
            return "Function is updated with symbolic value.";
        }
        case Cause::CALLED:
        {
            return "Function is called with symbolic argument.";
        }
        case Cause::CONDITION:
        {
            return "Function is updated in a condition.";
        }
    }
}

SCVisitor::Abort::Abort( void )
: std::logic_error( "rule check aborted" )
{
}

SCVisitor::Frame::Frame( Ast::Node* callee, std::size_t numberOfLocals )
: m_callee( callee )
, m_locals( numberOfLocals, FunctionType::UNKNOWN )
{
}

Ast::Node* SCVisitor::Frame::callee( void ) const
{
    return m_callee;
}

void SCVisitor::Frame::setLocal( std::size_t index, FunctionType function )
{
    assert( index < m_locals.size() );
    m_locals[ index ] = function;
}

SCVisitor::FunctionType SCVisitor::Frame::local( std::size_t index )
{
    assert( index < m_locals.size() );
    return m_locals[ index ];
}

std::vector< SCVisitor::FunctionType >& SCVisitor::Frame::locals( void )
{
    return m_locals;
}

SymbolicConsistencyVisitor::SymbolicConsistencyVisitor( Logger& logger )
: m_logger( logger )
, m_dependencies()
, m_stack()
, m_context()
, m_forceContextCreation( false )
, m_unknownUpdate( false )
, m_evaluateUpdateLocation( false )
, m_updateLocation( nullptr )
, m_currentRule( nullptr )
, m_frame( nullptr )
{
}

void SymbolicConsistencyVisitor::visit( Specification& specification )
{
    ExecutionLocationRegistry registry;
    Storage storage;
    SCStateInitializationVisitor initVisitor( registry, storage, m_logger );
    try
    {
        initVisitor.visit( specification );
    }
    catch( Abort ignore )
    {
        assert( !"rule calles in init definitions are not supported." );
    }

    const auto end = storage.programState().end();
    for( auto it = storage.programState().begin(); it != end; ++it )
    {
        auto value = it.value();
        const auto& ruleRef = static_cast< const ReferenceConstant& >( value );

        if( ruleRef.defined() )
        {
            const auto& literal = ruleRef.value();
            assert(
                ( literal->referenceType() == Ast::ReferenceLiteral::ReferenceType::RULE ) &&
                "Must be a rule reference" );

            const auto& rule =
                std::static_pointer_cast< Ast::RuleDefinition >( literal->reference() );
            assert(
                ( rule->arguments()->size() == 0 ) && "Only parameter-less rules are supported" );
            m_dependencies.insert( std::make_shared< RuleDependency >( rule ) );
        }
    }

    using Status = RuleDependency::Status;
    while( not done() )
    {
        m_stack.clear();
        m_context.clear();
        m_context.push( Context::PLAIN );

        auto rule = nextRule();

        m_currentRule = rule->rule();

        m_frame = std::make_shared< Frame >(
            m_currentRule.get(), m_currentRule->maximumNumberOfLocals() );

        try
        {
            rule->setStatus( Status::STARTED );
            m_unknownUpdate = false;
            m_currentRule->accept( *this );
        }
        catch( Abort ignore )
        {
            continue;
        }

        if( m_unknownUpdate || ( not m_currentRule->type()->result().isVoid() &&
                                 m_stack.pop() == FunctionType::UNKNOWN ) )
        {
            rule->setStatus( Status::EVALUATED );
        }
        else
        {
            rule->setStatus( Status::FINISHED );
        }
        bool allEvaluated =
            std::all_of( m_dependencies.begin(), m_dependencies.end(), [ & ]( const auto& dep ) {
                return dep->inStatus( { Status::EVALUATED, Status::FINISHED } );
            } );

        if( allEvaluated )
        {
            for( auto& dep : m_dependencies )
            {
                dep->define();
            }
        }
    }
}

void SymbolicConsistencyVisitor::visit( Ast::Initially& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::Initializer& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::VariableDefinition& node )
{
    m_stack.push( m_frame->local( node.localIndex() ) );
}

void SymbolicConsistencyVisitor::visit( Ast::FunctionDefinition& node )
{
    if( m_evaluateUpdateLocation )
    {
        m_updateLocation = node.ptr< Ast::FunctionDefinition >();
    }
    m_stack.push( node.symbolic() ? FunctionType::SYMBOLIC : FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( Ast::DerivedDefinition& node )
{
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::RuleDefinition& node )
{
    node.rule()->accept( *this );

    const auto& returnType = node.type()->ptr_result();
    if( not returnType->isVoid() )
    {
        if( false /* update set has result update */ )
        {
            // const auto& value = TODO get update value and REMOVE update from
            // update set
            // TODO validate return value
            // m_evaluationStack.push( value );
        }
        else
        {
            m_stack.push( FunctionType::NUMERIC );
        }
    }
}

void SymbolicConsistencyVisitor::visit( Ast::EnumeratorDefinition& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::InvariantDefinition& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::UndefLiteral& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( Ast::ValueLiteral& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( Ast::ReferenceLiteral& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( Ast::ListLiteral& node )
{
    auto type = typeOfList( node.expressions() );
    m_stack.push( type );
}

void SymbolicConsistencyVisitor::visit( Ast::RangeLiteral& node )
{
    node.left()->accept( *this );
    auto left = m_stack.pop();

    node.right()->accept( *this );
    auto right = m_stack.pop();

    m_stack.push( left && right );
}

void SymbolicConsistencyVisitor::visit( Ast::TupleLiteral& node )
{
    auto type = typeOfList( node.expressions() );
    m_stack.push( type );
}

void SymbolicConsistencyVisitor::visit( Ast::RecordLiteral& node )
{
    auto type = typeOfList( node.namedExpressions() );
    m_stack.push( type );
}

void SymbolicConsistencyVisitor::visit( Ast::BasicType& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( Ast::EmbracedExpression& node )
{
    // just evaluate the named expression and push it to the stack
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::NamedExpression& node )
{
    // just evaluate the named expression and push it to the stack
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::DirectCallExpression& node )
{
    using TargetType = Ast::DirectCallExpression::TargetType;
    switch( node.targetType() )
    {
        case TargetType::FUNCTION:  // [[fallthrough]]
        case TargetType::DERIVED:
        {
            const auto& function =
                std::static_pointer_cast< Ast::FunctionDefinition >( node.targetDefinition() );
            function->accept( *this );
            auto functionType = m_stack.pop();

            assert(
                functionType != FunctionType::UNKNOWN &&
                "function type of definition must be symbolic or numeric" );

            if( functionType == FunctionType::SYMBOLIC )
            {
                m_stack.push( FunctionType::SYMBOLIC );
                return;
            }

            auto type = typeOfList( node.arguments() );
            if( type == FunctionType::SYMBOLIC )
            {
                throw SCVisitor::Conflict(
                    function, { node.sourceLocation() }, Conflict::Cause::CALLED );
            }
            m_stack.push( type );
            break;
        }
        case TargetType::RULE:
        {
            // TODO: @moosbruggerj fix me
            auto result = callRule( node.ptr< Ast::DirectCallExpression >() );
            if( not node.type()->result().isVoid() )
            {
                m_stack.push( result );
            }
            break;
        }
        case TargetType::BUILTIN:
        {
            // TODO: @moosbruggerj fix me
            break;
        }
        case TargetType::TYPE_DOMAIN:
        {
            // no symbolic types
            m_stack.push( FunctionType::NUMERIC );
            break;
        }
        case TargetType::CONSTANT:  // [[fallthrough]]
        case TargetType::VARIABLE:
        {
            node.targetDefinition()->accept( *this );
            break;
        }
        case TargetType::SELF:
        {
            m_stack.push( FunctionType::NUMERIC );
            break;
        }
        case TargetType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

void SymbolicConsistencyVisitor::visit( Ast::MethodCallExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::LiteralCallExpression& node )
{
    node.object()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::IndirectCallExpression& node )
{
    // TODO: fix me: needs evaluation of reference
}

void SymbolicConsistencyVisitor::visit( Ast::TypeCastingExpression& node )
{
    // no symbolic types -> symbolic state of from expression is symbolic state of casted
    // expression
    node.fromExpression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::UnaryExpression& node )
{
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::BinaryExpression& node )
{
    node.left()->accept( *this );
    auto left = m_stack.pop();

    node.right()->accept( *this );
    auto right = m_stack.pop();

    m_stack.push( left && right );
}

void SymbolicConsistencyVisitor::visit( Ast::LetExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::ConditionalExpression& node )
{
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    if( not createContext( condition ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
    }

    node.thenExpression()->accept( *this );
    auto thenExp = m_stack.pop();

    node.elseExpression()->accept( *this );
    auto elseExp = m_stack.pop();

    if( m_context.top() == Context::PLAIN )
    {
        m_stack.push( thenExp && elseExp );
    }
    else
    {
        m_stack.push( FunctionType::SYMBOLIC );
    }

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( Ast::ChooseExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::UniversalQuantifierExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::ExistentialQuantifierExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::CardinalityExpression& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::ConditionalRule& node )
{
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    if( not createContext( condition ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
    }

    node.thenRule()->accept( *this );

    // TODO
    node.elseRule()->accept( *this );

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( Ast::CaseRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::LetRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::LocalRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::ForallRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::ChooseRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::IterateRule& node )
{
}

void SymbolicConsistencyVisitor::visit( Ast::BlockRule& node )
{
    node.rules()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::SequenceRule& node )
{
    node.rules()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( Ast::UpdateRule& node )
{
    ScopedOverwrite< Ast::FunctionDefinition::Ptr > withUpdateLocation( m_updateLocation, nullptr );
    {
        ScopedOverwrite< bool > withLocationEvaluation( m_evaluateUpdateLocation, true );
        node.function()->accept( *this );

        assert( m_updateLocation != nullptr && "update location must be defined" );
    }
    auto function = m_stack.pop();

    node.expression()->accept( *this );
    auto expression = m_stack.pop();

    if( function == FunctionType::NUMERIC )
    {
        if( expression == FunctionType::UNKNOWN )
        {
            m_unknownUpdate = true;
            return;
        }
        if( expression == FunctionType::SYMBOLIC )
        {
            throw Conflict(
                m_updateLocation, { m_updateLocation->sourceLocation() }, Conflict::Cause::UPDATE );
        }
        if( m_context.top() == Context::CONDITIONAL )
        {
            throw Conflict(
                m_updateLocation,
                { m_updateLocation->sourceLocation() },
                Conflict::Cause::CONDITION );
        }
    }
    if( function == FunctionType::UNKNOWN )
    {
        m_logger.warning(
            { m_updateLocation->sourceLocation() },
            "update location is unknown if symbolic or numeric" );
        if( expression == FunctionType::SYMBOLIC )
        {
            m_logger.warning(
                { m_updateLocation->sourceLocation() },
                "function may be numeric with symbolic update" );
        }
        m_unknownUpdate = true;
    }
}

void SymbolicConsistencyVisitor::visit( Ast::CallRule& node )
{
    node.accept( *this );
    const auto& returnType = node.call()->type()->result();
    if( not returnType.isVoid() )
    {
        m_stack.pop();  // drop return value
    }
}

void SymbolicConsistencyVisitor::visit( Ast::WhileRule& node )
{
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    if( not createContext( condition ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
    }

    node.rule()->accept( *this );

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( Ast::VariableBinding& node )
{
    node.expression()->accept( *this );
    const auto value = m_stack.pop();

    const auto variableIndex = node.variable()->localIndex();
    m_frame->setLocal( variableIndex, value );
}

bool SymbolicConsistencyVisitor::createContext( const FunctionType condition )
{
    if( m_context.top() == Context::CONDITIONAL )
    {
        m_context.push( Context::CONDITIONAL );
        return true;
    }

    switch( condition )
    {
        case FunctionType::UNKNOWN:
        {
            if( not m_forceContextCreation )
            {
                throw Abort();
            }
            else
            {
                m_context.push( Context::CONDITIONAL );
                return false;
            }
        }

        case FunctionType::SYMBOLIC:
        {
            m_context.push( Context::CONDITIONAL );
            break;
        }
        case FunctionType::NUMERIC:
        {
            m_context.push( Context::PLAIN );
            break;
        }
    }
    return true;
}

SymbolicConsistencyVisitor::FunctionType SymbolicConsistencyVisitor::callRule(
    const Ast::DirectCallExpression::Ptr& call )
{
    auto currentDeps = findOrInsert( m_currentRule );
    assert( call->targetDefinition()->id() == Ast::Node::ID::RULE_DEFINITION );

    const auto rule = std::static_pointer_cast< Ast::RuleDefinition >( call->targetDefinition() );
    auto ruleDeps = findOrInsert( rule );
    currentDeps->calls( ruleDeps );

    std::vector< FunctionType > args;
    for( const auto& arg : *call->arguments() )
    {
        arg->accept( *this );
        args.push_back( m_stack.pop() );
    }
    ruleDeps->isCalledBy( currentDeps, args );

    return ruleDeps->returns();
}

template < class T >
SCVisitor::FunctionType SymbolicConsistencyVisitor::typeOfList( const T& list )
{
    FunctionType type = FunctionType::NUMERIC;
    for( const auto& el : *list )
    {
        el->accept( *this );
        auto value = m_stack.pop();
        if( value == FunctionType::SYMBOLIC )
        {
            return FunctionType::SYMBOLIC;
        }
        type = type && value;
    }
    return type;
}

bool SymbolicConsistencyVisitor::done( void ) const
{
    return std::all_of( m_dependencies.begin(), m_dependencies.end(), [ & ]( const auto& dep ) {
        return dep->inStatus( { RuleDependency::Status::FINISHED } );
    } );
}

SymbolicConsistencyVisitor::RuleDependency::Ptr SymbolicConsistencyVisitor::nextRule( void )
{
    using Status = RuleDependency::Status;
    RuleDependency::Ptr next;
    Status nextStatus = Status::FINISHED;
    bool nextDefined = false;
    for( auto const& rule : m_dependencies )
    {
        if( rule->inStatus( { Status::FINISHED } ) )
        {
            continue;
        }
        if( rule->status() < nextStatus )
        {
            next = rule;
            nextStatus = rule->status();
            nextDefined = rule->fullyDefined();
        }
        if( rule->status() == nextStatus && nextDefined == false && rule->fullyDefined() == true )
        {
            next = rule;
            nextStatus = rule->status();
            nextDefined = rule->fullyDefined();
        }
    }
    if( next == nullptr )
    {
        throw RuntimeException(
            {}, "Pass is not done, but no calculatable rule available.", {}, Code::Unspecified );
    }
    return next;
}

SymbolicConsistencyVisitor::FunctionType libcasm_fe::operator&&(
    const SymbolicConsistencyVisitor::FunctionType lhs,
    const SymbolicConsistencyVisitor::FunctionType rhs )
{
    using FunctionType = SymbolicConsistencyVisitor::FunctionType;

    if( lhs == FunctionType::SYMBOLIC || rhs == FunctionType::SYMBOLIC )
    {
        return FunctionType::SYMBOLIC;
    }
    if( lhs == FunctionType::UNKNOWN || rhs == FunctionType::UNKNOWN )
    {
        return FunctionType::UNKNOWN;
    }
    if( lhs == FunctionType::NUMERIC && rhs == FunctionType::NUMERIC )
    {
        return FunctionType::NUMERIC;
    }
    assert( !"invalid Function Type" );
}

SCStateInitializationVisitor::SCStateInitializationVisitor(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState, Logger& logger )
: EmptyVisitor()
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager()
, m_logger( logger )
{
}

void SCStateInitializationVisitor::visit( Specification& node )
{
    m_updateSetManager.fork( Semantics::Sequential, 100 );

    node.header()->accept( *this );
    node.definitions()->accept( *this );

    auto updateSet = m_updateSetManager.currentUpdateSet();
    m_globalState.fireUpdateSet( updateSet );
    m_updateSetManager.clear();
}

void SCStateInitializationVisitor::visit( Ast::InitDefinition& node )
{
    assert( node.programFunction() and "checked during frame size determination pass!" );
    node.programFunction()->accept( *this );
}

void SCStateInitializationVisitor::visit( Ast::FunctionDefinition& node )
{
    assert( not node.isLocal() );

    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    if( node.isProgram() )
    {
        ExecutionVisitor executionVisitor(
            m_locationRegistry, m_globalState, m_updateSetManager, ReferenceConstant() );
        node.initially()->accept( executionVisitor );
    }
    else
    {
        // TODO: @moosbruggerj check if symbolic checks are done
        SymbolicConsistencyVisitor consistencyVisitor( m_logger );
        node.initially()->accept( consistencyVisitor );
    }
    transaction.merge();
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
