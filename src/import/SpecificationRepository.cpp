//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
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

#include "SpecificationRepository.h"

using namespace libcasm_fe;

SpecificationRepository::SpecificationRepository( void )
: m_specificationBasePath()
, m_specifications()
, m_dependencyGraph()
{
}

void SpecificationRepository::setSpecificationBasePath( const std::string& specificationBasePath )
{
    m_specificationBasePath = specificationBasePath;
}

std::string SpecificationRepository::specificationBasePath( void ) const
{
    return m_specificationBasePath;
}

void SpecificationRepository::store(
    const std::string& id, const Specification::Ptr& specification )
{
    assert( get( id ) == libstdhl::nullopt );
    m_specifications.emplace( id, specification );
}

libstdhl::Optional< Specification::Ptr > SpecificationRepository::get( const std::string& id ) const
{
    const auto it = m_specifications.find( id );
    if( it != m_specifications.cend() )
    {
        return it->second;
    }

    return libstdhl::nullopt;
}

void SpecificationRepository::addDepenency(
    const Specification::Ptr& from, const Specification::Ptr& to )
{
    m_dependencyGraph.emplace( to.get(), std::unordered_set< const Specification* >() );
    const auto dependencyGraphIterator =
        m_dependencyGraph.emplace( from.get(), std::unordered_set< const Specification* >() );
    auto& dependencyList = dependencyGraphIterator.first->second;
    dependencyList.emplace( to.get() );

    // detect cycle due to the adding of the dependency edge 'from -> to'
    std::unordered_set< const Specification* > discovered;
    std::unordered_set< const Specification* > finished;

    for( const auto it : m_dependencyGraph )
    {
        const auto u = it.first;
        const auto dependencyList = it.second;

        if( discovered.find( u ) == discovered.end() and finished.find( u ) == finished.end() )
        {
            checkCircleDependency( u, discovered, finished );
        }
    }
}

void SpecificationRepository::checkCircleDependency(
    const Specification* from,
    std::unordered_set< const Specification* >& discovered,
    std::unordered_set< const Specification* >& finished )
{
    discovered.emplace( from );

    const auto it = m_dependencyGraph.find( from );
    assert( it != m_dependencyGraph.end() );
    const auto& fromList = it->second;

    for( const auto to : fromList )
    {
        if( discovered.find( to ) != discovered.end() )
        {
            throw std::domain_error( "cycle detected" );
        }

        if( discovered.find( to ) == discovered.end() and finished.find( to ) == finished.end() )
        {
            checkCircleDependency( to, discovered, finished );
        }
    }

    discovered.erase( from );
    finished.emplace( from );
}

std::vector< Specification::Ptr > SpecificationRepository::specifications( void ) const
{
    std::vector< Specification::Ptr > values;
    values.reserve( m_specifications.size() );

    for( const auto& keyValue : m_specifications )
    {
        values.emplace_back( keyValue.second );
    }

    return values;
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
