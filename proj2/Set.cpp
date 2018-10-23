//
//  Set.cpp
//  proj2
//
//  Created by 杨子鸣 on 4/21/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "Set.h"

Set::Set()               // Create an empty set.
{
    numOfNode = 0;
}

Set::~Set()         //Destructor: When a Set is destroyed, the nodes in the linked list must be deallocated.
{
    if (!empty())
    {
    Node *e = head->prev;
    Node *p = head;
    while (p != e)
    {
        Node *nex = p->next;
        delete p;
        p = nex;
    }
    delete p;
    }
}

Set::Set(const Set& other)
//Copy constructor
//When a brand new Set is created as a copy of an existing Set, enough new nodes
//must be allocated to hold a duplicate of the original list.
{
    numOfNode = 0;
    Node *p = other.head;
    if (other.empty())
    {
        return;
    }
    for (p; p != other.head->prev; p = p->next)
    {
        insert(p->value);
    }
    insert(p->value);
}

Set Set::operator=(const Set& rhs)
//Assignment operator
//When an existing Set (the left-hand side) is assigned the value of another Set (the right-hand side),
//the result must be that the left-hand side object is a duplicate of the right-hand side object, with no
//memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still
//allocated yet inaccessible).
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}




bool Set::empty() const  // Return true if the set is empty, otherwise false.
{
    return numOfNode==0;
}



int Set::size() const    // Return the number of items in the set.
{
    return numOfNode;
}



bool Set::insert(const ItemType& value)
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full).
{
    //if the value is contained in the list
    if (contains(value))
    {
        std::cerr << "the value you want to insert is already contained" << std::endl;
        return false;
    }
    
    //if the circular list is empty
    if (empty())
    {
        head = new Node;
        head->value = value;
        head->prev = head;
        head->next = head;
        numOfNode++;
        return true;
    }
    
    //if smaller than the first one
    if (value < head->value)
    {
        Node *add = new Node;
        
        add->value = value;
        
        add->prev = head->prev;
        add->next = head;
    
        head->prev->next = add;
        head->prev = add;

        head = add;
        numOfNode++;
        return true;
    }
    //if bigger than the last one
    else if (value > head->prev->value)
    {
        Node *add = new Node;
        
        add->value = value;
        
        add->next = head;
        add->prev = head->prev;
        
        head->prev->next = add;
        head->prev = add;
        numOfNode++;
        return true;
    }
    //if in the middle
    else
    {
        Node *p = head;
        for (p; p != head->prev; p = p->next)
        {
            if (value > p->value && value < p->next->value)
                break;
        }
        
        Node *add = new Node;
        
        add->value = value;
        
        add->prev = p;
        add->next = p->next;
        
        p->next->prev = add;
        p->next = add;
        numOfNode++;
        return true;
    }
}



bool Set::erase(const ItemType& value)
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
{
    if (!contains(value))
    {
        std::cerr << "the value you want to remove is not in the list!!!" << std::endl;
        return false;
    }
    else
    {
        Node *p = head;
        for (p; p != head->prev; p = p->next)
        {
            if (value == p->value)
                break;
        }
        if (p->value == value)  //double check the last one
        {
            if (p == head)      //if the first one
            {
                head = p->next;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            numOfNode--;
            return true;
        }
        else
            return false;

    }
}



bool Set::contains(const ItemType& value) const
// Return true if the value is in the set, otherwise false.
{
    if (empty())
        return false;
    else
    {
        Node *p = head;
        for (p; p != head->prev; p = p->next)
        {
            if (value == p->value)
                return true;
        }
        if (value == p->value)      //check the last position and the one-element case
            return true;
        return false;
    }
}

bool Set::get(int pos, ItemType& value) const
// If 0 <= i < size(), copy into value the item in the set that is
// greater than exactly i items in the set and return true.  Otherwise,
// leave value unchanged and return false.
{
    if (empty())
        return false;
    
    if (pos >=0 && pos < numOfNode)
    {
        int countNum = 1;
        Node *p = head;
        for (p; p != head->prev  &&  countNum <= pos; p = p->next,countNum++)
            //move p up to the position we want
        ;
        if (countNum == pos+1)
        {
            value = p->value;
        }
        return true;
    }
    else
    {
        std::cerr << "the number has to be with in the range"<<std::endl;
        return false;
    }
    
}

void Set::swap(Set& other)
// Exchange the contents of this set with the other one.
{
    
    int tempNum = other.numOfNode;
    other.numOfNode = numOfNode;
    numOfNode = tempNum;
    
    //exchange the head pointer
    Node *tempH = other.head;
    other.head = head;
    head = tempH;
    
}

void Set::dump() const
{
    if (empty())
        std::cerr << "there is no element!!!" << std::endl;
    else
    {
    Node *p = head;
    std::cerr << "the element in the list in order is:\n";
    for (p; p != head->prev; p = p->next)
    {
        std::cerr << p->value << std::endl;
    }
    std::cerr << p->value << std::endl;
    }
}


void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType temp;
    //checking the situation of aliasing
    if (&result == &s1)
    {
        for (int i = 0; i < s2.size(); i++)
        {
            s2.get(i, temp);
            result.insert(temp);
        }

    }
    else if(&result == &s2)
    {
        for (int i = 0; i < s1.size(); i++)
        {
            s1.get(i, temp);
            result.insert(temp);
        }
        
    }
    //if there is no aliasing
    else
    {
    for (int i = 0; result.size() != 0;)
    {
        result.get(i, temp);
        result.erase(temp);
    }
    
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, temp);
        result.insert(temp);
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        result.insert(temp);
    }
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    ItemType temp;
    //check the situation of aliasing
    if( &result == &s2)
    {
        Set tempS = s2;
        for (int i = 0; i < s1.size(); i++)
        {
            s1.get(i, temp);
            result.insert(temp);
        }
        
        for (int i = 0; i < tempS.size(); i++)
        {
            tempS.get(i, temp);
            result.erase(temp);
        }

    }
    else if (&result == &s1)
    {
        for (int i = 0; i < s2.size(); i++)
        {
            s2.get(i, temp);
            result.erase(temp);
        }
    }

    //if there is no aliasing
    else
    {
    for (int i = 0; result.size() != 0;)
    {
        result.get(i, temp);
        result.erase(temp);
    }
    
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, temp);
        result.insert(temp);
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        result.erase(temp);
    }
    }
}



