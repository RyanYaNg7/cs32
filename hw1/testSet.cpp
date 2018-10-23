//
//  testSet.cpp
//  hw1
//
//  Created by 杨子鸣 on 4/15/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
/*

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set s;
    assert(s.empty());
    
    ItemType x = 9876543;
    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    assert( !s.get(-10, x)  &&  x == 9876543);
    
    s.insert(123456789);
    assert(s.size() == 1);
    s.insert(1122334);
    s.insert(87162354);
    s.insert(01723461);
    assert(s.size() == 4);
    
    assert(!s.insert(1122334));
    assert(!s.erase(0000000));
    assert(s.erase(1122334));
    assert(s.size() ==3);
    
    assert(s.contains(87162354));
    assert(!s.contains(1122334));
    
    assert(s.get(0, x)  &&  x == 01723461);
    assert(s.get(2, x)  &&  x == 123456789);
    
    s.erase(87162354);
    s.erase(123456789);
    s.erase(01723461);
    assert(s.empty());
    
    Set t;
    t.insert(1234567);
    t.insert(7654321);
    assert(t.size() == 2);
    
    t.swap(s);
    assert(t.empty()  &&  s.size() == 2);
    assert(s.contains(1234567));
    assert(s.get(1,x)  &&  x == 7654321);
    
    s.swap(t);
    assert(s.empty()  &&  t.size() == 2);
    assert(t.contains(1234567));
    assert(t.get(1,x)  &&  x == 7654321);
    
    cout << "Passed all tests" << endl;
}

*/
