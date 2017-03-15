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

#ifndef _LIB_CASMFE_TYPECHECKPASS_H_
#define _LIB_CASMFE_TYPECHECKPASS_H_

#include <set>

#include "libpass.h"

#include "../Visitor.h"

#include "../transform/SourceToAstPass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class TypeCheckPass final : public libpass::Pass,
                                public Visitor< Type *, Type * >
    {
      public:
        static char id;

        bool run( libpass::PassResult& pr ) override;

        LIB_CASMFE_VISITOR_INTERFACE( Type*, Type* );

        void check_type_valid( const location& location, const Type& type );

        void check_numeric_operator(
            const location& loc, Type* type, const libcasm_ir::Value::ID op );

        std::vector< std::vector< Type* >* > rule_binding_types;
        std::vector< std::map< std::string, size_t >* > rule_binding_offsets;

        bool forall_head;

      private:
        // type checker is in a function definition
        bool m_isInFunctionDefinition = false;
        // type checker is in a rule
        bool m_isInRule = false;

        // to simulate top-down function declaration (used during function
        // initialization)
        std::set< std::string > m_declaredFunctions;

        // indicates if the type checker has found an init node
        bool m_specificationHasInitNode = false;

      public:
        using Data = SourceToAstPass::Data;
    };

    template <>
    void AstWalker< TypeCheckPass, Type* >::walk_forall( ForallNode* node );
}

#endif // _LIB_CASMFE_TYPECHECKPASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
