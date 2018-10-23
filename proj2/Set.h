//
//  Set.hpp
//  proj2
//
//  Created by 杨子鸣 on 4/21/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//



#ifndef SET_INCLUDED
#define SET_INCLUDED
#include "OurType.h"
#include <iostream>
#include <string>

typedef unsigned long ItemType;
//typedef std::string ItemType;

struct Node
{
    ItemType value;
    Node* next;
    Node* prev;
};

class Set
{
public:
    Set();         // Create an empty set.
    
    ~Set();         //Destructor: When a Set is destroyed, the nodes in the linked list must be deallocated.
    
    Set (const Set& other);
    //Copy constructor
    //When a brand new Set is created as a copy of an existing Set, enough new nodes
    //must be allocated to hold a duplicate of the original list.
    
    Set operator=(const Set& rhs);
    //Assignment operator
    //When an existing Set (the left-hand side) is assigned the value of another Set (the right-hand side),
    //the result must be that the left-hand side object is a duplicate of the right-hand side object, with no
    //memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still
    //allocated yet inaccessible).
    
    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // is already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // greater than exactly i items in the set and return true.  Otherwise,
    // leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    void dump() const;
private:
    int numOfNode;
    Node *head;
    
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);




#endif //SET_INCLUDED



