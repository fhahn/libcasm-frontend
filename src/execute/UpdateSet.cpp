//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "UpdateSet.h"

#include <algorithm>
#include <cassert>

UpdateSet::Conflict::Conflict(const std::string& msg,
                              Update* conflictingUpdate,
                              Update* existingUpdate) :
    std::logic_error(msg),
    m_conflictingUpdate(conflictingUpdate),
    m_existingUpdate(existingUpdate)
{

}

Update* UpdateSet::Conflict::conflictingUpdate() const noexcept
{
    return m_conflictingUpdate;
}

Update* UpdateSet::Conflict::existingUpdate() const noexcept
{
    return m_existingUpdate;
}

UpdateSet::UpdateSet(std::size_t initialSize, UpdateSet* parent) :
    m_set(initialSize),
    m_parent(parent)
{

}

UpdateSet::~UpdateSet()
{

}

bool UpdateSet::empty() const noexcept
{
    return m_set.empty();
}

size_t UpdateSet::size() const noexcept
{
    return m_set.size();
}

void UpdateSet::clear()
{
    m_set.clear();
}

Update* UpdateSet::lookup(const value_t* location) const
{
    if (m_parent) {
        return m_parent->lookup(location);
    }

    return nullptr;
}

UpdateSet *UpdateSet::fork(const UpdateSet::Type updateSetType, std::size_t initialSize)
{
    switch (updateSetType) {
    case Type::Sequential:
        return new SequentialUpdateSet(initialSize, this);
    case Type::Parallel:
        return new ParallelUpdateSet(initialSize, this);
    }
}

void UpdateSet::merge()
{
    if (m_parent->m_set.empty()) {
        std::swap(m_parent->m_set, m_set);
    } else {
        m_parent->m_set.reserve(m_parent->m_set.size() + m_set.size());
        for(const auto& pair : m_set) {
            m_parent->add(pair.first, pair.second);
        }
        clear();
    }
}

typename UpdateSet::const_iterator UpdateSet::cbegin() const noexcept
{
    return m_set.cbegin();
}

typename UpdateSet::const_iterator UpdateSet::cend() const noexcept
{
    return m_set.cend();
}

Update* UpdateSet::get(const value_t* location) const noexcept
{
    const auto it = m_set.find(location);
    return (it != m_set.cend()) ? it->second : nullptr;
}

UpdateSet::Type SequentialUpdateSet::type() const noexcept
{
    return Type::Sequential;
}

void SequentialUpdateSet::add(const value_t* location, Update* update)
{
    m_set[location] = update;
}

Update* SequentialUpdateSet::lookup(const value_t* location) const
{
    const auto it = m_set.find(location);
    if (it != m_set.cend()) {
        return it->second;
    }

    return UpdateSet::lookup(location);
}

UpdateSet::Type ParallelUpdateSet::type() const noexcept
{
    return Type::Parallel;
}

void ParallelUpdateSet::add(const value_t* location, Update* update)
{
    const auto result = m_set.insert(location, update);
    if (!result.second) {
        const auto existingPair = *(result.first);
        const auto existingUpdate = existingPair.second;

        if (update->value != existingUpdate->value) {
            throw Conflict("Conflict in updateset", update, existingUpdate);
        }
    }
}

UpdateSetManager::UpdateSetManager() :
    m_updateSets()
{

}

UpdateSetManager::~UpdateSetManager()
{
    clear();
}

void UpdateSetManager::add(const value_t* location, Update* update)
{
    assert(!m_updateSets.empty());
    m_updateSets.top()->add(location, update);
}

Update* UpdateSetManager::lookup(const value_t* location) const
{
    if (m_updateSets.empty()) {
      return nullptr;
    } else {
      return m_updateSets.top()->lookup(location);
    }
}

void UpdateSetManager::fork(const UpdateSet::Type updateSetType, std::size_t initialSize)
{
    if (m_updateSets.empty()) {
        switch (updateSetType) {
        case UpdateSet::Type::Sequential:
            m_updateSets.push(new SequentialUpdateSet(initialSize));
            break;
        case UpdateSet::Type::Parallel:
            m_updateSets.push(new ParallelUpdateSet(initialSize));
            break;
        }
    } else {
        auto currentUpdateSet = m_updateSets.top();
        auto forkedUpdateSet = currentUpdateSet->fork(updateSetType, initialSize);
        m_updateSets.push(forkedUpdateSet);
    }
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

void UpdateSetManager::clear()
{
    while (!m_updateSets.empty()) {
        delete m_updateSets.top();
        m_updateSets.pop();
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
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
