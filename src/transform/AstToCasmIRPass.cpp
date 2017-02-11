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

#include "AstToCasmIRPass.h"

#include "analyze/TypeCheckPass.h"

#include "libcasm-ir.h"

using namespace libcasm_fe;

char AstToCasmIRPass::id = 0;

static libpass::PassRegistration< AstToCasmIRPass > PASS( "AST to CASM IR",
    "translates the AST to the CASM intermeditate representation",
    "ast2ir",
    0 );

static libcasm_ir::Type* getType( Type* type )
{
    assert( type && "not initialized type used" );

    switch( type->t )
    {
        case TypeType::AGENT:
            return libcasm_ir::Type::Agent();
        case TypeType::RULEREF:
            return libcasm_ir::Type::RuleReference();
        case TypeType::BOOLEAN:
            return libcasm_ir::Type::Boolean();
        case TypeType::INTEGER:
            return libcasm_ir::Type::Integer();
        case TypeType::BIT:
            if( not( type->bitsize > 0 && type->bitsize <= 256 ) )
            {
                std::cout << std::string( __FUNCTION__ ) << ": "
                          << type->to_str() << "\n";
            }
            assert( type->bitsize > 0 && type->bitsize <= 256
                    && "invalid Bit size for Bit type" );
            return libcasm_ir::Type::Bit( type->bitsize );
        case TypeType::STRING:
            return libcasm_ir::Type::String();
        default:
            std::cerr << type->to_str() << "\n";
            assert( 0 && "not implemented function atom identifier type" );
            return 0;
    }
}

bool AstToCasmIRPass::run( libpass::PassResult& pr )
{
    specification = 0;

    initially_scope = 0;
    initially_update_scope = 0;
    is_initially = false;

    Ast* root = (Ast*)pr.result< TypeCheckPass >();

    AstWalker< AstToCasmIRPass, bool > walker( *this );
    walker.walk_specification( root );

    // PPA: IMPROVEMENT: maybe there is a better solution later for this
    // 'RuleRef to Rule' checking/resolving issue!
    libcasm_ir::RuleReferenceConstant::checking();

    // casm_frontend_destroy(); // PPA: enable this if it is safe to remove the
    // AST object

    pr.setResult< AstToCasmIRPass >( specification );
    pr.setResult< libcasm_ir::CasmIRDumpPass >( specification );

    return true;
}

libcasm_ir::Specification* AstToCasmIRPass::getSpecification( void ) const
{
    assert( specification );
    return specification;
}

#define VISIT                                                                  \
/*printf( "===--- %s:%i: %s: %p: %s\n", __FILE__, __LINE__, __FUNCTION__,      \
  node, node->to_str().c_str() )*/

#define FIXME                                                                  \
    printf( "+++ FIXME +++: '%s:%i' in '%s'\n", __FILE__, __LINE__,            \
        __FUNCTION__ );                                                        \
    fflush( stdout );                                                          \
    assert( 0 );

void AstToCasmIRPass::visit_root( Ast* node )
{
    VISIT;
    assert( not specification );
    assert( not is_initially );
    assert( not initially_scope );
    assert( not initially_update_scope );
}

void AstToCasmIRPass::visit_specification( SpecificationNode* node )
{
    VISIT;
    specification = new libcasm_ir::Specification(
        libstdhl::Allocator::string( node->identifier ) );

    libcasm_ir::Rule* ir_initially_rule = new libcasm_ir::Rule(
        ".initially", libcasm_ir::Type::RuleReference() );
    assert( ir_initially_rule );

    getSpecification()->add( ir_initially_rule );

    libcasm_ir::ParallelBlock* ir_initially_rule_scope
        = new libcasm_ir::ParallelBlock();
    assert( ir_initially_rule_scope );
    ir_initially_rule->setContext( ir_initially_rule_scope );

    libcasm_ir::SequentialBlock* ir_initially_rule_inner_scope
        = new libcasm_ir::SequentialBlock();
    assert( ir_initially_rule_inner_scope );
    ir_initially_rule_scope->add( ir_initially_rule_inner_scope );

    initially_scope = ir_initially_rule_inner_scope;

    // single execution agent!
    libcasm_ir::Agent* ir_agent = new libcasm_ir::Agent();
    assert( ir_agent );
    libcasm_ir::Value* ir_agent_init_rule
        = libcasm_ir::Constant::RuleReference( ir_initially_rule );
    ir_agent->setInitRuleReference( ir_agent_init_rule );
    getSpecification()->add( ir_agent );
}

void AstToCasmIRPass::visit_init( InitNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_body_elements_pre( AstListNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_body_elements_post( AstListNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_function_def_pre( FunctionDefNode* node, bool )
{
    VISIT;

    is_initially = true;

    if( node->initializers().size() > 0 )
    {
        initially_update_scope = new libcasm_ir::ParallelBlock();
        assert( initially_update_scope );
        assert( initially_scope );
        initially_scope->add( initially_update_scope );
    }

    std::vector< libcasm_ir::Type* > ftype_args;
    for( auto argument : node->sym->arguments_ )
    {
        ftype_args.push_back( getType( argument ) );
    }

    libcasm_ir::Type* ftype = libcasm_ir::Type::Relation(
        getType( node->sym->return_type_ ), ftype_args );

    libcasm_ir::Function* ir_function
        = new libcasm_ir::Function( node->sym->name.c_str(), ftype );
    assert( ir_function );

    getSpecification()->add( ir_function );

    ast2casmir[ (AstNode*)node->sym ] = ir_function;
}

void AstToCasmIRPass::visit_function_def_post( FunctionDefNode* node )
{
    VISIT;

    is_initially = false;
    initially_update_scope = 0;
}

void AstToCasmIRPass::visit_derived_def_pre( DerivedDefNode* node )
{
    VISIT;

    std::vector< libcasm_ir::Type* > ftype_args;
    for( auto argument : node->sym->arguments_ )
    {
        ftype_args.push_back( getType( argument ) );
    }

    libcasm_ir::Type* ftype = libcasm_ir::Type::Relation(
        getType( node->sym->return_type_ ), ftype_args );

    libcasm_ir::Derived* ir_derived
        = new libcasm_ir::Derived( node->sym->name.c_str(), ftype );
    assert( ir_derived );

    for( i32 i = 0; i < node->sym->arguments_.size(); i++ )
    {
        const char* param_ident = node->sym->parameter[ i ];
        // printf( "param %s\n", param_ident );

        ir_derived->addParameter(
            libcasm_ir::Identifier::create( ftype_args[ i ], param_ident
                //, ir_derived
                ) );
    }

    current_scope.push_back( ir_derived );
}

void AstToCasmIRPass::visit_derived_def( DerivedDefNode* node, bool expr )
{
    VISIT;
    std::string x;
    for( auto& a : node->sym->arguments_ )
    {
        x.append( a->to_str() );
    }

    assert( node->sym->type == Symbol::SymbolType::DERIVED );

    libcasm_ir::Value* ir_expr
        = lookup< libcasm_ir::Value >( node->sym->derived );
    assert( ir_expr );

    libcasm_ir::TrivialStatement* ir_stmt = new libcasm_ir::TrivialStatement();
    assert( ir_stmt );
    ir_stmt->add( ir_expr );

    assert( libcasm_ir::isa< libcasm_ir::Derived >( current_scope.back() )
            and "invalid scope!" );

    libcasm_ir::Derived* ir_derived
        = (libcasm_ir::Derived*)current_scope.back();
    ir_derived->setContext( ir_stmt );

    for( auto param : ir_derived->parameters() )
    {
        libcasm_ir::Identifier::forgetSymbol( param->name() );
    }

    current_scope.pop_back();

    getSpecification()->add( ir_derived );

    ast2casmir[ (AstNode*)node->sym ] = ir_derived;
}

void AstToCasmIRPass::visit_skip( AstNode* node )
{
    VISIT;

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    libcasm_ir::TrivialStatement* ir_stmt
        = new libcasm_ir::TrivialStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    libcasm_ir::SkipInstruction* ir_skip = new libcasm_ir::SkipInstruction();
    assert( ir_skip );

    ir_stmt->add( ir_skip );
}

void AstToCasmIRPass::visit_rule( RuleNode* node )
{
    //    printf( "\n\n" );
    VISIT;
    std::string x;
    for( auto& a : node->arguments )
    {
        x.append( a->to_str() );
    }
    //    printf( "%p -> %p\n", node, node->child_ );
    assert( node );

    libcasm_ir::Rule* ir_rule = new libcasm_ir::Rule(
        node->name.c_str(), libcasm_ir::Type::RuleReference() );
    assert( ir_rule );
    ast2casmir[ node ] = ir_rule;
    ast2parent[ node->child_ ] = node;

    if( node->child_->node_type_ != NodeType::PARBLOCK )
    {
        libcasm_ir::ParallelBlock* ir_scope = new libcasm_ir::ParallelBlock();
        assert( ir_scope );
        ast2casmir[ node ] = ir_scope;

        ir_rule->setContext( ir_scope );
    }

    for( i32 i = 0; i < node->arguments.size(); i++ )
    {
        ir_rule->addParameter( libcasm_ir::Identifier::create(
            getType( node->arguments[ i ] ), node->parameter[ i ] ) );
    }

    current_scope.push_back( ir_rule );
}

void AstToCasmIRPass::visit_rule_post( RuleNode* node )
{
    VISIT;

    assert( libcasm_ir::isa< libcasm_ir::Rule >( current_scope.back() )
            and "invalid scope!" );
    libcasm_ir::Rule* ir_rule = (libcasm_ir::Rule*)current_scope.back();

    getSpecification()->add( ir_rule );

    for( auto param : ir_rule->parameters() )
    {
        libcasm_ir::Identifier::forgetSymbol( param->name() );
    }

    current_scope.pop_back();
}

void AstToCasmIRPass::visit_parblock_pre( UnaryNode* node )
{
    VISIT;
    // printf( "{ }\n" );
    // printf( "%p -> %p\n", node, node->child_ );

    assert( node );

    libcasm_ir::ParallelBlock* ir_scope = new libcasm_ir::ParallelBlock();
    assert( ir_scope );
    ast2casmir[ node ] = ir_scope;
    ast2parent[ node->child_ ] = node;

    libcasm_ir::Value* parent = lookupParent< libcasm_ir::Value >( node );
    assert( parent );

    if( libcasm_ir::isa< libcasm_ir::Rule >( parent ) )
    {
        libcasm_ir::Rule* ir_rule = ( (libcasm_ir::Rule*)parent );
        ir_rule->setContext( ir_scope );
        ir_scope->bind( ir_rule );
    }
    else if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        ( (libcasm_ir::ExecutionSemanticsBlock*)parent )->add( ir_scope );
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        ( (libcasm_ir::Statement*)parent )->scope()->add( ir_scope );
    }
    else
    {
        assert( 0 );
    }
}

void AstToCasmIRPass::visit_parblock_post( UnaryNode* node )
{
}

void AstToCasmIRPass::visit_seqblock_pre( UnaryNode* node )
{
    VISIT;
    // printf( "{| |}\n" );
    // printf( "%p -> %p\n", node, node->child_ );

    assert( node );

    libcasm_ir::SequentialBlock* ir_scope = new libcasm_ir::SequentialBlock();
    assert( ir_scope );
    ast2casmir[ node ] = ir_scope;
    ast2parent[ node->child_ ] = node;

    libcasm_ir::Value* parent = lookupParent< libcasm_ir::Value >( node );
    assert( parent );

    // if( isa< Rule >( parent ) )
    // {
    //     ParallelBlock* ir_par = new ParallelBlock();
    //     ir_par->add( ir_scope );
    //     ((Rule*)parent)->setContext( ir_par );
    // }
    // else
    if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        ( (libcasm_ir::ExecutionSemanticsBlock*)parent )->add( ir_scope );
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        ( (libcasm_ir::Statement*)parent )->scope()->add( ir_scope );
    }
    else
    {
        assert( 0 );
    }
}

void AstToCasmIRPass::visit_seqblock_post( UnaryNode* node )
{
}

void AstToCasmIRPass::visit_statements( AstListNode* node )
{
    VISIT;
    // printf( "...\n" );
    // for( AstNode *s : node->nodes )
    // {
    //     printf( "%p -> %p\n", node, s );
    // }

    assert( node );

    auto parent = ast2parent.find( node );
    assert( parent != ast2parent.end() );

    for( AstNode* s : node->nodes )
    {
        ast2parent[ s ] = parent->second;
    }
}

void AstToCasmIRPass::visit_forall_pre( ForallNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_forall_post( ForallNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_iterate( UnaryNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_update(
    UpdateNode* node, std::vector< bool >& args, bool expr )
{
    VISIT;
    // printf( "%p -> %p\n", node, node->func );
    // printf( "%p -> %p\n", node, node->expr_ );

    assert( node->func );
    visit_function_atom( node->func, args );

    libcasm_ir::ExecutionSemanticsBlock* ir_scope = 0;
    if( is_initially )
    {
        ir_scope = initially_update_scope;
    }
    else
    {
        ir_scope = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    }
    assert( ir_scope );

    libcasm_ir::TrivialStatement* ir_stmt
        = new libcasm_ir::TrivialStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;
    ast2parent[ node->func ] = node;
    ast2parent[ node->expr_ ] = node;

    libcasm_ir::Value* ir_lhs = lookup< libcasm_ir::Value >( node->func );
    libcasm_ir::Value* ir_rhs = lookup< libcasm_ir::Value >( node->expr_ );

    assert( ir_lhs );
    assert( ir_rhs );

    assert( libcasm_ir::isa< libcasm_ir::LookupInstruction >( ir_lhs ) );

    ir_stmt->add( new libcasm_ir::UpdateInstruction(
        ( (libcasm_ir::Instruction*)ir_lhs )->value( 0 ), ir_rhs ) );
}

void AstToCasmIRPass::visit_call_pre( CallNode* node )
{
    // VISIT;
}

void AstToCasmIRPass::visit_call_pre( CallNode* node, bool expr )
{
    // VISIT;
}

void AstToCasmIRPass::visit_call( CallNode* node, std::vector< bool >& args )
{
    VISIT;

    printf( "FIXME: call: %s, %p, %p\n", node->rule_name.c_str(), node->rule,
        node->ruleref );

    // ExecutionSemanticsBlock* ir_scope =
    //     lookupParent< ExecutionSemanticsBlock >( node );
    // assert( ir_scope );

    // TrivialStatement* ir_stmt = new TrivialStatement( ir_scope );
    // assert( ir_stmt );
    // ir_scope->add( ir_stmt );

    // ast2casmir[ node ]         = ir_stmt;
    // // ast2parent[ node->func ]   = node;
    // // ast2parent[ node->expr_ ]  = node;

    // Value* instr = lookup< Value >( a );

    // CallInstruction* ir_call = new CallInstruction();
    // assert( ir_call );

    // for( auto a : node->atoms )
    // {
    //     Value* instr = lookup< Value >( a );
    //     ir_print->add( instr );
    // }
    // ir_print->add( StringConstant::create( (const char*)"\n" ) );

    // ir_stmt->add( ir_print );

    // FIXME;
}

void AstToCasmIRPass::visit_call_post( CallNode* node )
{
    // VISIT;
}

void AstToCasmIRPass::visit_print( PrintNode* node, bool expr )
{
    VISIT;

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    libcasm_ir::TrivialStatement* ir_stmt
        = new libcasm_ir::TrivialStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    libcasm_ir::PrintInstruction* ir_print = new libcasm_ir::PrintInstruction();
    assert( ir_print );

    // for( auto a : node->atoms )
    // {
    //     Value* instr = lookup< Value >( a );
    //     ir_print->add( instr );
    // }
    ir_print->add( lookup< libcasm_ir::Value >( node->getAtom() ) );

    // INFO: PPA: commented line below, because the 'IR' itself adds this during
    // runtime (interpreter)
    // and compilation --> this should not be part of the CASM IR!!!
    // ir_print->add( StringConstant::create( (const char*)"\n" ) );

    ir_stmt->add( ir_print );
}

void AstToCasmIRPass::visit_diedie( DiedieNode* node, bool msg )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_impossible( AstNode* node )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_assert( UnaryNode* node, bool expr )
{
    VISIT;

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    libcasm_ir::TrivialStatement* ir_stmt
        = new libcasm_ir::TrivialStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    ast2casmir[ node ] = ir_stmt;

    libcasm_ir::Value* ir_cond = lookup< libcasm_ir::Value >( node->child_ );
    assert( ir_cond );

    libcasm_ir::Instruction* ir_instr
        = new libcasm_ir::AssertInstruction( ir_cond );
    assert( ir_instr );

    ir_stmt->add( ir_instr );
}

void AstToCasmIRPass::visit_assure( UnaryNode* node, bool expr )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_let( LetNode* node, bool var )
{
    VISIT;

    ast2parent[ node->expr ] = node;
    ast2parent[ node->stmt ] = node;

    libcasm_ir::Value* ir_expr = lookup< libcasm_ir::Value >( node->expr );
    assert( ir_expr );

    libcasm_ir::Value* ir_ident = libcasm_ir::Identifier::create(
        getType( &node->type_ ), node->identifier.c_str() );
    assert( ir_ident );

    libcasm_ir::Value* ir_local
        = new libcasm_ir::LocalInstruction( ir_ident, ir_expr );
    assert( ir_local );

    libcasm_ir::ExecutionSemanticsBlock* ir_scope = 0;
    libcasm_ir::Value* parent = lookupParent< libcasm_ir::Value >( node );
    assert( parent );

    if( libcasm_ir::isa< libcasm_ir::ExecutionSemanticsBlock >( parent ) )
    {
        ir_scope = (libcasm_ir::ExecutionSemanticsBlock*)parent;
    }
    else if( libcasm_ir::isa< libcasm_ir::Statement >( parent ) )
    {
        ir_scope = ( (libcasm_ir::Statement*)parent )->scope();
    }
    else
    {
        assert( 0 );
    }

    libcasm_ir::SequentialBlock* ir_block = new libcasm_ir::SequentialBlock();
    assert( ir_block );
    ir_scope->add( ir_block );
    ir_block->setParent( ir_scope );

    libcasm_ir::TrivialStatement* ir_stmt
        = new libcasm_ir::TrivialStatement( ir_block );
    assert( ir_stmt );
    ir_block->add( ir_stmt );

    ir_stmt->add( ir_local );
    ir_stmt->setParent( ir_block );

    ast2casmir[ node ] = ir_block;

    // SequentialBlock* ir_block = new SequentialBlock( ir_scope );
    // assert( ir_block );
    // TrivialStatement* ir_stmt = new TrivialStatement( ir_block );
    // assert( ir_stmt );
    // ir_block->add( ir_stmt );

    // ir_stmt->add( ir_local );

    // ast2casmir[ node ] = ir_stmt;

    // ir_block->add( ir_ );

    // if( node->stmt->node_type_ != NodeType::PARBLOCK )
    // {
    //     ParallelBlock* ir_blk = new ParallelBlock();
    //     assert( ir_blk );
    //     ast2casmir[ node ] = ir_blk;
    //     ir_stmt->addBlock( ir_blk );
    // }

    // assert( !" DEPRECATED IMPLEMENTATION, TODO: FIXME: PPA!!! " );
}

void AstToCasmIRPass::visit_let_post( LetNode* node )
{
    VISIT;
    libcasm_ir::Identifier::forgetSymbol( node->identifier.c_str() );
}

void AstToCasmIRPass::visit_push( PushNode* node, bool expr, bool atom )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_pop( PopNode* node, bool atom )
{
    VISIT;
    FIXME;
}

void AstToCasmIRPass::visit_ifthenelse( IfThenElseNode* node, bool cond )
{
    VISIT;
    // printf( "%p -> %p\n",      node, node->condition_ );
    // printf( "%p -> %p | %p\n", node, node->then_, node->else_ );

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    libcasm_ir::BranchStatement* ir_stmt
        = new libcasm_ir::BranchStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    assert( node->condition_ );
    libcasm_ir::Value* ir_cond
        = lookup< libcasm_ir::Value >( node->condition_ );
    assert( ir_cond );

    assert( ( libcasm_ir::isa< libcasm_ir::Instruction >( ir_cond )
                and ir_cond->type().id() == libcasm_ir::Type::BOOLEAN )
            or libcasm_ir::isa< libcasm_ir::BooleanConstant >( ir_cond ) );

    ir_stmt->add( ir_cond );

    libcasm_ir::Instruction* ir_select
        = new libcasm_ir::SelectInstruction( ir_cond );
    assert( ir_select );

    assert( node->then_ );
    libcasm_ir::ExecutionSemanticsBlock* ir_case_true
        = new libcasm_ir::ParallelBlock( ir_scope );
    assert( ir_case_true );
    ast2casmir[ node ] = ir_case_true;
    ast2parent[ node->then_ ] = node;
    ir_stmt->addBlock( ir_case_true );

    libcasm_ir::Value* ir_true = libcasm_ir::Constant::Boolean( true );
    getSpecification()->add( ir_true );

    ir_select->add( ir_true );
    ir_select->add( ir_case_true );

    if( node->else_ )
    {
        libcasm_ir::ExecutionSemanticsBlock* ir_case_false
            = new libcasm_ir::ParallelBlock( ir_scope );
        assert( ir_case_false );
        ast2casmir[ node->condition_ ] = ir_case_false;
        ast2parent[ node->condition_ ] = node;
        ast2parent[ node->else_ ] = node->condition_;

        ir_stmt->addBlock( ir_case_false );

        libcasm_ir::Value* ir_false = libcasm_ir::Constant::Boolean( false );
        getSpecification()->add( ir_false );

        ir_select->add( ir_false );
        ir_select->add( ir_case_false );
    }

    ir_stmt->add( ir_select );
}

void AstToCasmIRPass::visit_case_pre( CaseNode* node, bool val )
{
    VISIT;
    // printf( "%p -> %p\n",      node, node->expr );

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    for( auto& a : node->case_list )
    {
        // printf( "%p: %p -> %p\n", &node->case_list, a.first, a.second );

        libcasm_ir::Value* ir_case = new libcasm_ir::ParallelBlock( ir_scope );
        assert( ir_case );
        ast2casmir[ (AstNode*)&a ] = ir_case;
        ast2parent[ a.second ] = (AstNode*)&a;
    }
}

void AstToCasmIRPass::visit_case(
    CaseNode* node, bool val, const std::vector< bool >& case_labels )
{
    VISIT;

    libcasm_ir::ExecutionSemanticsBlock* ir_scope
        = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( node );
    assert( ir_scope );

    libcasm_ir::BranchStatement* ir_stmt
        = new libcasm_ir::BranchStatement( ir_scope );
    assert( ir_stmt );
    ir_scope->add( ir_stmt );

    libcasm_ir::Value* ir_expr = lookup< libcasm_ir::Value >( node->expr );
    assert( ir_expr );
    assert( libcasm_ir::isa< libcasm_ir::Instruction >( ir_expr )
            or libcasm_ir::isa< libcasm_ir::Constant >( ir_expr )
            or libcasm_ir::isa< libcasm_ir::Identifier >( ir_expr ) );

    libcasm_ir::Instruction* ir_select
        = new libcasm_ir::SelectInstruction( ir_expr );
    assert( ir_select );

    libcasm_ir::ExecutionSemanticsBlock* default_case = 0;

    for( auto& a : node->case_list )
    {
        // printf( "case: %p: %p -> %p\n", &node->case_list, a.first, a.second
        // );

        libcasm_ir::ExecutionSemanticsBlock* ir_case
            = lookupParent< libcasm_ir::ExecutionSemanticsBlock >( a.second );
        assert( ir_case );

        if( !a.first )
        {
            default_case = ir_case;
            continue;
        }

        libcasm_ir::Value* ir_label = lookup< libcasm_ir::Value >( a.first );
        assert( ir_label );

        ir_select->add( ir_label );
        ir_select->add( ir_case );

        ir_stmt->addBlock( ir_case );
    }

    if( default_case )
    {
        ir_select->add( default_case );

        ir_stmt->addBlock( default_case );
    }

    ir_stmt->add( ir_select );
}

bool AstToCasmIRPass::visit_expression(
    BinaryExpression* node, bool lhs, bool rhs )
{
    VISIT;
    // printf( "%s, %p, %p\n", operator_to_str( node->op ).c_str(), node->left_,
    // node->right_ );

    libcasm_ir::Value* ir_lhs = lookup< libcasm_ir::Value >( node->left_ );
    libcasm_ir::Value* ir_rhs = lookup< libcasm_ir::Value >( node->right_ );
    assert( ir_lhs );
    assert( ir_rhs );

    using Opcode = libcasm_ir::Value::ID;

    // PPA: TODO: this section can be omitted if the IR directly uses the ID
    // value to
    // create on the fly the Instruction instance
    libcasm_ir::Value* ir_expr = 0;
    switch( node->op )
    {
        case Opcode::ADD_INSTRUCTION:
            ir_expr = new libcasm_ir::AddInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::SUB_INSTRUCTION:
            ir_expr = new libcasm_ir::SubInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::MUL_INSTRUCTION:
            ir_expr = new libcasm_ir::MulInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::DIV_INSTRUCTION:
            ir_expr = new libcasm_ir::DivInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::MOD_INSTRUCTION:
            ir_expr = new libcasm_ir::ModInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::EQU_INSTRUCTION:
            ir_expr = new libcasm_ir::EquInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::NEQ_INSTRUCTION:
            ir_expr = new libcasm_ir::NeqInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::LTH_INSTRUCTION:
            ir_expr = new libcasm_ir::LthInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::LEQ_INSTRUCTION:
            ir_expr = new libcasm_ir::LeqInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::GTH_INSTRUCTION:
            ir_expr = new libcasm_ir::GthInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::GEQ_INSTRUCTION:
            ir_expr = new libcasm_ir::GeqInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::OR_INSTRUCTION:
            ir_expr = new libcasm_ir::OrInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::XOR_INSTRUCTION:
            ir_expr = new libcasm_ir::XorInstruction( ir_lhs, ir_rhs );
            break;
        case Opcode::AND_INSTRUCTION:
            ir_expr = new libcasm_ir::AndInstruction( ir_lhs, ir_rhs );
            break;
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
    }

    assert( ir_expr );
    ast2casmir[ node ] = ir_expr;
    return 0;
}

bool AstToCasmIRPass::visit_expression_single( UnaryExpression* node, bool val )
{
    VISIT;
    // printf( "%s, %p\n", operator_to_str( node->op ).c_str(), node->left_ );

    libcasm_ir::Value* ir_lhs = lookup< libcasm_ir::Value >( node->expr_ );
    assert( ir_lhs );

    using Opcode = libcasm_ir::Value::ID;

    libcasm_ir::Value* ir_expr = 0;
    switch( node->op )
    {
        case Opcode::NOT_INSTRUCTION:
            ir_expr = new libcasm_ir::NotInstruction( ir_lhs );
            break;
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
    }

    assert( ir_expr );
    ast2casmir[ node ] = ir_expr;
    return 0;
}

bool AstToCasmIRPass::visit_function_atom(
    FunctionAtom* node, std::vector< bool >& args )
{
    VISIT;

    if( node->symbol_type == FunctionAtom::SymbolType::PARAMETER )
    {
        libcasm_ir::Value* scope = 0;
        if( current_scope.size() > 0 )
        {
            scope = current_scope.back();
        }

        libcasm_ir::Value* ir_ident = libcasm_ir::Identifier::create(
            getType( &node->type_ ), node->name.c_str(), scope );

        assert( ir_ident );
        ast2casmir[ node ] = ir_ident;
        return 0;
    }

    libcasm_ir::Value* ir_ident
        = lookup< libcasm_ir::Value >( (AstNode*)node->symbol );
    assert( ir_ident );

    libcasm_ir::LocationInstruction* ir_loc
        = new libcasm_ir::LocationInstruction( ir_ident );
    assert( ir_loc );
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            libcasm_ir::Value* instr = lookup< libcasm_ir::Value >( a );
            ir_loc->add( instr );
        }
    }

    libcasm_ir::LookupInstruction* ir_lup
        = new libcasm_ir::LookupInstruction( ir_loc );
    assert( ir_lup );
    ast2casmir[ node ] = ir_lup;

    return 0;
}

void AstToCasmIRPass::visit_derived_function_atom_pre(
    FunctionAtom* node, std::vector< bool >& args )
{
    VISIT;
}

bool AstToCasmIRPass::visit_derived_function_atom(
    FunctionAtom* node, bool expr )
{
    VISIT;
    std::string x;

    assert( node->symbol );
    assert( node->symbol_type == FunctionAtom::SymbolType::DERIVED );

    libcasm_ir::Value* ir_derived
        = lookup< libcasm_ir::Value >( (AstNode*)node->symbol );
    assert( ir_derived );

    libcasm_ir::CallInstruction* ir_call
        = new libcasm_ir::CallInstruction( ir_derived );
    assert( ir_call );
    ast2casmir[ node ] = ir_call;
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            libcasm_ir::Value* instr = lookup< libcasm_ir::Value >( a );
            ir_call->add( instr );
        }
    }

    return 0;
}

bool AstToCasmIRPass::visit_undef_atom( UndefAtom* node )
{
    VISIT;
    // printf( "undef\n" );

    libcasm_ir::Value* ir_const = 0;

    switch( node->type_.t )
    {
        case TypeType::RULEREF:
            ir_const = libcasm_ir::Constant::Undef(
                libcasm_ir::Type::RuleReference() );
            break;
        case TypeType::BOOLEAN:
            ir_const
                = libcasm_ir::Constant::Undef( libcasm_ir::Type::Boolean() );
            break;
        case TypeType::BIT:
            ir_const = libcasm_ir::Constant::Undef(
                libcasm_ir::Type::Bit( node->type_.bitsize ) );
            break;
        case TypeType::INTEGER:
            ir_const
                = libcasm_ir::Constant::Undef( libcasm_ir::Type::Integer() );
            break;
        case TypeType::STRING:
            ir_const
                = libcasm_ir::Constant::Undef( libcasm_ir::Type::String() );
            break;
        default:
            assert( 0 && "unimplemented undef constant!" );
    }

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_boolean_atom( BooleanAtom* node )
{
    VISIT;
    // printf( "%u\n", node->value );

    libcasm_ir::Value* ir_const = libcasm_ir::Constant::Boolean(
        (libcasm_ir::Type::BooleanTy)node->value );

    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_int_atom( IntegerAtom* node )
{
    VISIT;
    // printf( "%lu\n", node->val_    );

    libcasm_ir::Value* ir_const = libcasm_ir::Constant::Integer(
        (libcasm_ir::Type::IntegerTy)node->val_ );
    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_bit_atom( IntegerAtom* node )
{
    VISIT;
    // printf( "%lu (0x%lx)\n", node->val_, node->val_    );

    libcasm_ir::Value* ir_const = libcasm_ir::Constant::Bit(
        libcasm_ir::Type::Bit( node->type_.bitsize ),
        (u64)node->val_ ); // LIMITATION: PPA: input
                           // parameter can be larger than
                           // 64bit!
    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_floating_atom( FloatingAtom* node )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_rational_atom( RationalAtom* node )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_string_atom( StringAtom* node )
{
    VISIT;

    libcasm_ir::Value* ir_const
        = libcasm_ir::Constant::String( node->string.c_str() );
    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    // printf( "%s\n", node->string.c_str() );

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_self_atom( SelfAtom* node )
{
    VISIT;

    libcasm_ir::Value* ir_const = libcasm_ir::Constant::Agent( 0 );
    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_rule_atom( RuleAtom* node )
{
    VISIT;

    libcasm_ir::Value* ir_const
        = libcasm_ir::Constant::RuleReference( node->name.c_str() );
    assert( ir_const );
    ast2casmir[ node ] = ir_const;

    // printf( "rule: @%s\n", node->name.c_str() );

    getSpecification()->add( ir_const );
    return 0;
}

bool AstToCasmIRPass::visit_list_atom(
    ListAtom* node, const std::vector< bool >& args )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_number_range_atom(
    NumberRangeAtom* node, bool start, bool end )
{
    VISIT;
    FIXME;
    return 0;
}

bool AstToCasmIRPass::visit_builtin_atom(
    BuiltinAtom* node, std::vector< bool >& args )
{
    VISIT;

    // printf( "builtin: %s\n", node->to_str().c_str() );

    std::vector< libcasm_ir::Type* > ty_ident_args;
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            ty_ident_args.push_back( getType( &( a->type_ ) ) );
        }
    }

    libcasm_ir::Type* ty_ident = libcasm_ir::Type::Relation(
        getType( node->return_type ), ty_ident_args );

    libcasm_ir::Value* ir_ident
        = libcasm_ir::Builtin::find( node->to_str().c_str(), ty_ident );

    assert( ir_ident );
    getSpecification()->add( ir_ident );

    libcasm_ir::CallInstruction* ir_call
        = new libcasm_ir::CallInstruction( ir_ident );
    assert( ir_call );
    ast2casmir[ node ] = ir_call;
    if( node->arguments )
    {
        for( auto a : *( node->arguments ) )
        {
            libcasm_ir::Value* instr = lookup< libcasm_ir::Value >( a );
            ir_call->add( instr );
        }
    }

    return 0;
}

void AstToCasmIRPass::visit_statement( AstNode* node )
{
    VISIT;
}

void AstToCasmIRPass::visit_forall_iteration_pre( ForallNode* node, bool )
{
    VISIT;
}

void AstToCasmIRPass::visit_forall_iteration_post( ForallNode* node )
{
    VISIT;
}

bool AstToCasmIRPass::visit_zero_atom( ZeroAtom* node )
{
    VISIT;
    return false;
}

template < class C >
C* AstToCasmIRPass::lookupParent( AstNode* node )
{
    // printf( "%s: ??? %p\n", __FUNCTION__, node );

    auto result = ast2parent.find( node );
    if( result != ast2parent.end() )
    {
        // printf( "%s: %p, %p\n", __FUNCTION__, result->first, result->second
        // );
        return lookup< C >( result->second );
    }

    return 0;
}

template < class C >
C* AstToCasmIRPass::lookup( AstNode* node )
{
    // printf( "%s: %p\n", __FUNCTION__, node );

    auto result = ast2casmir.find( node );
    if( result != ast2casmir.end() )
    {
        // printf( "%s: %p\n", __FUNCTION__, result->second );
        if( libcasm_ir::isa< C >( result->second ) )
        {
            return static_cast< C* >( result->second );
        }
        else
        {
            assert( 0 );
        }
    }

    return 0;
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
