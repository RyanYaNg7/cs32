//
//  Set.cpp
//  hw1
//
//  Created by 杨子鸣 on 4/14/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

/*


#include "Set.h"

#include <iostream>

Set::Set()  // Create an empty set.
{
    m_numberOfItems = 0;
}

bool Set::empty() const // Return true if the set is empty, otherwise false.
{
    return (m_numberOfItems == 0);
}

int Set::size() const   // Return the number of items in the set.
{
    std::cerr << "the size is " << m_numberOfItems << std::endl;
    return m_numberOfItems;
}

bool Set::insert(const ItemType& value)
{
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // is already in the set or because the set has a fixed capacity and
    // is full).
    if (m_numberOfItems == DEFAULT_MAX_ITEMS)
    {
        std::cerr << "the insert function return false!!! because the set is full!\n";
        return false;
    }
    
    for (int j = 0; j < m_numberOfItems; j++)
    {
        if (m_set[j] == value)
        {
            std::cerr << "the insert function return false!!! because there already is such value!\n";
            return false;
        }
    }
    
    
    for (int j = 0; j < m_numberOfItems; j++)
    {
    if (value > m_set[j])
        continue;
    else
    {
        for (int k = m_numberOfItems; k > j; k--)
        {
            m_set[k] = m_set[k-1];
        }
        m_set[j] = value;
        m_numberOfItems++;
        std::cerr << "the insert function return true!!! and the item is assigned at position" << j <<std::endl;
        return true;
    }
    }
    m_set[m_numberOfItems] = value;
    m_numberOfItems++;
    std::cerr << "the insert function return true!!! and the item is assigned at the end\n";
    return true;
}

bool Set::erase(const ItemType& value)
{
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    for (int j = 0; j < m_numberOfItems; j++)
    {
        if (m_set[j] == value)
        {
            for (int k = j; k < m_numberOfItems; k++)
            {
                m_set[k] = m_set[k+1];
            }
            m_numberOfItems--;
            return true;
        }
    }
    return false;
    
}

bool Set::contains(const ItemType& value) const // Return true if the value is in the set, otherwise false.
{
    for (int k = 0; k < m_numberOfItems; k++)
    {
        if (m_set[k] == value)
        {
            std::cerr << "the item " << value << "is contained in this set!!!\n";
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    // If 0 <= i < size(), copy into value the item in the set that is
    // greater than exactly i items in the set and return true.  Otherwise,
    // leave value unchanged and return false.
    if (0 <= i && i < m_numberOfItems)
    {
        value = m_set[i];
        return true;
    }
    else
        return false;
}

void Set::swap(Set& other)  // Exchange the contents of this set with the other one.
{
    Set tempSet = other;
    other = *this;
    *this = tempSet;
}

void Set::dump() const
{
    for(int k = 0; k < DEFAULT_MAX_ITEMS; k++)
    {
        std::cerr << m_set[k] << std::endl;
    }
}




*/





