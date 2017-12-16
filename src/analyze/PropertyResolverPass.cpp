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

#include "PropertyResolverPass.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include <libcasm-ir/Annotation>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

char PropertyResolverPass::id = 0;

static libpass::PassRegistration< PropertyResolverPass > PASS(
    "ASTPropertyResolverPass",
    "property resolving and checking of AST representation",
    "ast-prop-res",
    0 );

class PropertyResolverVisitor final : public RecursiveVisitor
{
  public:
    PropertyResolverVisitor( libcasm_fe::Logger& log );

    void visit( Specification& specification );

    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

    void visit( TypeCastingExpression& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( ReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( MethodCallExpression& node ) override;
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
    libcasm_fe::Logger& m_log;
};

PropertyResolverVisitor::PropertyResolverVisitor( libcasm_fe::Logger& log )
: m_log( log )
{
}

void PropertyResolverVisitor::visit( Specification& specification )
{
    specification.header()->accept( *this );
    specification.definitions()->accept( *this );
}

void PropertyResolverVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( FunctionDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( DerivedDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
}

void PropertyResolverVisitor::visit( RuleDefinition& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( EnumeratorDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );
}

void PropertyResolverVisitor::visit( EnumerationDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );
}

void PropertyResolverVisitor::visit( TypeCastingExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );
}

void PropertyResolverVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );
}

void PropertyResolverVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );
    node.setProperty( libcasm_ir::Property::CONSTANT );
    node.setProperty( libcasm_ir::Property::PURE );
}

void PropertyResolverVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( MethodCallExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UnaryExpression& node )
{
    RecursiveVisitor::visit( node );
    const auto& annotation = libcasm_ir::Annotation::find( node.op() );
    node.setProperties( annotation.properties() * node.expression()->properties() );
}

void PropertyResolverVisitor::visit( BinaryExpression& node )
{
    RecursiveVisitor::visit( node );
    const auto& annotation = libcasm_ir::Annotation::find( node.op() );
    node.setProperties(
        annotation.properties() * node.left()->properties() * node.right()->properties() );
}

void PropertyResolverVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( LetExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ConditionalExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ChooseExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UniversalQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExistentialQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( SkipRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ConditionalRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( CaseRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( LetRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ForallRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ChooseRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( IterateRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BlockRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( SequenceRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( CallRule& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( UnresolvedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ComposedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( BasicAttribute& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExpressionAttribute& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( Identifier& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( IdentifierPath& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( ExpressionCase& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverVisitor::visit( DefaultCase& node )
{
    RecursiveVisitor::visit( node );
}

void PropertyResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 PropertyResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();

    PropertyResolverVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during property resolving", errors );
        return false;
    }

    pr.setResult< PropertyResolverPass >( data );
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
