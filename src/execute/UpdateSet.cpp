//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

#include "UpdateSet.h"

#include <algorithm>
#include <cassert>

#include "../Exceptions.h"

UpdateSet::MergeError::MergeError(const std::string& msg,
                                  Update* conflictingUpdate,
                                  Update* existingUpdate) :
    std::logic_error(msg),
    m_conflictingUpdate(conflictingUpdate),
    m_existingUpdate(existingUpdate)
{

}

Update* UpdateSet::MergeError::conflictingUpdate() const noexcept
{
    return m_conflictingUpdate;
}

Update* UpdateSet::MergeError::existingUpdate() const noexcept
{
    return m_existingUpdate;
}

UpdateSet::UpdateSet(UpdateSet* parent) :
    m_parent(parent),
    m_set(100)
{
    if (parent) {
        m_type = (parent->m_type == Type::Parallel) ? Type::Sequential : Type::Parallel;
    } else {
        m_type = Type::Parallel;
    }
}

UpdateSet::~UpdateSet()
{
    clear();
}

UpdateSet::Type UpdateSet::type() const noexcept
{
    return m_type;
}

bool UpdateSet::empty() const noexcept
{
    return m_set.empty();
}

size_t UpdateSet::size() const noexcept
{
    return m_set.size();
}

void UpdateSet::add(const uint64_t key, Update* update)
{
    const auto result = m_set.insert(key, update);
    if (!result.second) {
        // check if values match
        /*const Function* function_symbol = context_.function_symbols[sym_id]; FIXME
        for (int i=0; i < up->num_args; i++) {
            if (!eq_uint64_value(function_symbol->arguments_[i], up->args[i], v->args[i])) {
                return;
            }
        }*/

        throw RuntimeException("Conflict in updateset");
    }
}

Update* UpdateSet::lookup(const uint64_t key) const
{
    if (m_type == Type::Sequential) {
        const auto it = m_set.find(key);
        if (it != m_set.cend()) {
            return it->second;
        }
    }

    if (m_parent) {
        return m_parent->lookup(key);
    }

    return nullptr;
}

UpdateSet *UpdateSet::fork()
{
    return new UpdateSet(this);
}

static void mergeParallelIntoSequential(const LinkedHashMap<uint64_t, Update*>& from,
                                        LinkedHashMap<uint64_t, Update*>& to)
{
    to.reserve(to.size() + from.size());

    for(const auto& pair : from) {
        to[pair.first] = pair.second;
    };
}

static void mergeSequentialIntoParallel(const LinkedHashMap<uint64_t, Update*>& from,
                                        LinkedHashMap<uint64_t, Update*>& to)
{
    to.reserve(to.size() + from.size());

    for(const auto& pair : from) {
        const auto result = to.insert(pair);
        if (!result.second) {
            const auto existingPair = *(result.first);
            const auto conflictingUpdate = pair.second;
            const auto existingUpdate = existingPair.second;
            // FIXME EP: check values before merge (same values don't clash)
            throw UpdateSet::MergeError("conflicting update-sets", conflictingUpdate, existingUpdate);
        }
    };
}

UpdateSet* UpdateSet::merge()
{
    if (type() == Type::Parallel) {
        mergeParallelIntoSequential(m_set, m_parent->m_set);
    } else {
        mergeSequentialIntoParallel(m_set, m_parent->m_set);
    }

    clear();

    return m_parent;
}

void UpdateSet::clear()
{
    m_set.clear();
}

typename UpdateSet::const_iterator UpdateSet::cbegin() const noexcept
{
    return m_set.cbegin();
}

typename UpdateSet::const_iterator UpdateSet::cend() const noexcept
{
    return m_set.cend();
}

UpdateSetManager::UpdateSetManager() :
    m_updateSets()
{
    m_updateSets.push(new UpdateSet);
}

UpdateSetManager::~UpdateSetManager()
{
    while (!m_updateSets.empty()) {
        delete m_updateSets.top();
        m_updateSets.pop();
    }
}

void UpdateSetManager::add(const uint64_t key, Update* update)
{
    assert(!m_updateSets.empty());
    m_updateSets.top()->add(key, update);
}

Update* UpdateSetManager::lookup(const uint64_t key) const
{
    assert(!m_updateSets.empty());
    return m_updateSets.top()->lookup(key);
}

bool UpdateSetManager::fork(const UpdateSet::Type updateSetType)
{
    assert(!m_updateSets.empty());
    auto currentUpdateSet = m_updateSets.top();
    if (currentUpdateSet->type() != updateSetType) {
        auto forkedUpdateSet = currentUpdateSet->fork();
        m_updateSets.push(forkedUpdateSet);
        return true;
    }
    return false;
}

void UpdateSetManager::merge()
{
    if (m_updateSets.size() > 1) {
        auto currentUpdateSet = m_updateSets.top();
        currentUpdateSet->merge();
        m_updateSets.pop();
        delete currentUpdateSet;
    }
}

UpdateSet* UpdateSetManager::currentUpdateSet() const
{
    return m_updateSets.top();
}

size_t UpdateSetManager::size() const
{
    return m_updateSets.size();
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
