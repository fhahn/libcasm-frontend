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

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

Definition::Definition( Node::ID type, const Identifier::Ptr& identifier )
: TypedNode( type )
, m_identifier( identifier )
, m_attributes( std::make_shared< Attributes >() )
{
}

Identifier::Ptr Definition::identifier( void ) const
{
    return m_identifier;
}

void Definition::setAttributes( const Attributes::Ptr& attributes )
{
    m_attributes = attributes;
}

Attributes::Ptr Definition::attributes( void ) const
{
    return m_attributes;
}

VariableDefinition::VariableDefinition(
    const Identifier::Ptr& identifier, const Type::Ptr& variableType )
: Definition( Node::ID::VARIABLE_DEFINITION, identifier )
, m_variableType( variableType )
, m_localIndex( 0 )
{
}

Type::Ptr VariableDefinition::variableType( void ) const
{
    return m_variableType;
}

void VariableDefinition::setLocalIndex( std::size_t localIndex )
{
    m_localIndex = localIndex;
}

std::size_t VariableDefinition::localIndex( void ) const
{
    return m_localIndex;
}

void VariableDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

FunctionDefinition::FunctionDefinition( const Identifier::Ptr& identifier,
    const Types::Ptr& argumentTypes,
    const Type::Ptr& returnType )
: Definition( Node::ID::FUNCTION_DEFINITION, identifier )
, m_classification( Classification::CONTROLLED )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_symbolic( false )
, m_initializers( std::make_shared< NodeList< UpdateRule > >() )
, m_defaultValue( std::make_shared< UndefAtom >() )
{
}

Types::Ptr FunctionDefinition::argumentTypes( void ) const
{
    return m_argumentTypes;
}

Type::Ptr FunctionDefinition::returnType( void ) const
{
    return m_returnType;
}

void FunctionDefinition::setClassification(
    FunctionDefinition::Classification classification )
{
    m_classification = classification;
}

FunctionDefinition::Classification FunctionDefinition::classification(
    void ) const
{
    return m_classification;
}

std::string FunctionDefinition::classificationName( void ) const
{
    switch( classification() )
    {
        case FunctionDefinition::Classification::IN:
        {
            return "in";
        }
        case FunctionDefinition::Classification::CONTROLLED:
        {
            return "controlled";
        }
        case FunctionDefinition::Classification::SHARED:
        {
            return "shared";
        }
        case FunctionDefinition::Classification::OUT:
        {
            return "out";
        }
        case FunctionDefinition::Classification::STATIC:
        {
            return "static";
        }
    }

    assert( !" internal error " );
    return "";
}

void FunctionDefinition::setSymbolic( u1 symbolic )
{
    m_symbolic = symbolic;
}

u1 FunctionDefinition::symbolic( void ) const
{
    return m_symbolic;
}

void FunctionDefinition::setInitializers(
    const NodeList< UpdateRule >::Ptr& initializers )
{
    m_initializers = initializers;
}

NodeList< UpdateRule >::Ptr FunctionDefinition::initializers( void ) const
{
    return m_initializers;
}

void FunctionDefinition::setDefaultValue( const Expression::Ptr& defaultValue )
{
    m_defaultValue = defaultValue;
}

Expression::Ptr FunctionDefinition::defaultValue( void ) const
{
    return m_defaultValue;
}

void FunctionDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

DerivedDefinition::DerivedDefinition( const Identifier::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
    const Type::Ptr& returnType,
    const Expression::Ptr& expression )
: Definition( Node::ID::DERIVED_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_expression( expression )
, m_maxNumberOfLocals( 0 )
{
}

NodeList< VariableDefinition >::Ptr DerivedDefinition::arguments( void ) const
{
    return m_arguments;
}

Type::Ptr DerivedDefinition::returnType( void ) const
{
    return m_returnType;
}

Expression::Ptr DerivedDefinition::expression( void ) const
{
    return m_expression;
}

void DerivedDefinition::setMaximumNumberOfLocals(
    std::size_t maxNumberOfLocals )
{
    m_maxNumberOfLocals = maxNumberOfLocals;
}

std::size_t DerivedDefinition::maximumNumberOfLocals( void ) const
{
    return m_maxNumberOfLocals;
}

void DerivedDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

RuleDefinition::RuleDefinition( const Identifier::Ptr& identifier,
    const NodeList< VariableDefinition >::Ptr& arguments,
    const Type::Ptr& returnType,
    const Rule::Ptr& rule )
: Definition( Node::ID::RULE_DEFINITION, identifier )
, m_arguments( arguments )
, m_returnType( returnType )
, m_rule( rule )
, m_maxNumberOfLocals( 0 )
{
}

NodeList< VariableDefinition >::Ptr RuleDefinition::arguments( void ) const
{
    return m_arguments;
}

Type::Ptr RuleDefinition::returnType( void ) const
{
    return m_returnType;
}

Rule::Ptr RuleDefinition::rule( void ) const
{
    return m_rule;
}

void RuleDefinition::setMaximumNumberOfLocals( std::size_t maxNumberOfLocals )
{
    m_maxNumberOfLocals = maxNumberOfLocals;
}

std::size_t RuleDefinition::maximumNumberOfLocals( void ) const
{
    return m_maxNumberOfLocals;
}

void RuleDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

EnumerationDefinition::EnumerationDefinition(
    const Identifier::Ptr& identifier, const Identifiers::Ptr& enumerators )
: Definition( Node::ID::ENUMERATION_DEFINITION, identifier )
, m_enumerators( enumerators )
{
}

Identifiers::Ptr EnumerationDefinition::enumerators( void ) const
{
    return m_enumerators;
}

void EnumerationDefinition::accept( Visitor& visitor )
{
    visitor.visit( *this );
}
