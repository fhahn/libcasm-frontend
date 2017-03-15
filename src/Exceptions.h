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

#ifndef _LIB_CASMFE_EXCEPTIONS_H_
#define _LIB_CASMFE_EXCEPTIONS_H_

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "various/location.hh"

#include "Codes.h"

namespace libcasm_fe
{
    class Exception : public std::exception
    {
      private:
        std::vector< location > location_;
        const std::string msg_;
        const Codes error_code_;

      public:
        explicit Exception( const std::string& msg,
            const Codes error_code = Codes::Unspecified );

        explicit Exception( const location& location, const std::string& msg,
            const Codes error_code = Codes::Unspecified );

        explicit Exception( const std::vector< location >& location,
            const std::string& msg,
            const Codes error_code = Codes::Unspecified );

        virtual const char* what() const throw();

        void addLocation( const location& location );

        const std::vector< location >& getLocations( void ) const;

        const Codes getErrorCode( void ) const;
    };

    class RuntimeException : public Exception
    {
        using Exception::Exception;
    };

    class CompiletimeException : public Exception
    {
        using Exception::Exception;
    };
}

#endif // _LIB_CASMFE_EXCEPTIONS_H_
