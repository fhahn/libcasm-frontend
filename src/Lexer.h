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

#ifndef _LIB_CASMFE_LEXER_H_
#define _LIB_CASMFE_LEXER_H_

#include <string>
#include <FlexLexer.h>

#include "various/GrammarParser.tab.h"

namespace yy
{
    class Lexer : public yyFlexLexer
    {
    public:
        Lexer( std::istream& in, std::ostream& out );

        yy::Parser::symbol_type nextToken();

    protected:
        //void LexerError( const char* msg ) override; TODO

    private:
        yy::Parser::location_type loc;
        std::string strbuf;
    };
}

#endif // _LIB_CASMFE_LEXER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
