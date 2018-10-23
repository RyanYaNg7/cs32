//
//  main.cpp
//  proj2
//
//  Created by 杨子鸣 on 4/21/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
/*
#include "Set.h"

#include <iostream>
#include <cassert>
using namespace std;
void testCopy(Set t);
void test11();
void test22();

void test()
{
    Set s;
    //for an empty set
    assert(s.empty());          //test empty
    assert(!s.erase(1234));           //nothing to erase
    assert(s.size()==0);          //test size
    
    ItemType x;
    // test insert, get, erase and contains
    assert(s.insert(23123));     //test insert
    assert(s.get(0,x)&&x==23123);     //test get
    assert(s.insert(12345));
    assert(s.get(0,x)&&x==12345);     //test if get can get correct item in set
    assert(s.get(1,x)&&x==23123);
    assert(s.insert(45678));
    assert(s.insert(34567));
    assert(s.size()==4);     //test size
    assert(s.insert(99999)&&s.size()==5);
    assert(s.get(4,x)&&x==99999);     //see if new item correctly inserted
    
    assert(s.erase(99999));     //test erase
    assert(s.size()==4 &&!s.get(4,x));     //test if completely erased
    assert(s.contains(45678));     //test contains
    assert(!s.contains(99999));
    assert(!s.contains(22222));
    s.dump();     //check 12345 23123 34567 45678
    
    
    
    
    Set ss(s);
    //test copy constructor
    assert(ss.size()==4);     //test if copy get size right
    assert(ss.get(0,x)&&x==12345);     //test if copy get item right
    assert(ss.get(1,x)&&x==23123);
    assert(ss.get(2,x)&&x==34567);
    assert(ss.get(3,x)&&x==45678);
    assert(ss.erase(12345));     //make sure s will not change is we change ss
    assert(s.get(0,x)&&x==12345);     //s is not affected by ss
    
    Set sss;
    assert(sss.insert(11111));
    //test assign operator
    sss=s;
    assert(sss.contains(12345));     //test if sss get everything from s
    assert(sss.contains(23123));
    assert(sss.contains(34567));
    assert(sss.contains(45678));
    assert(sss.size()==4);
    assert(sss.erase(34567));     //make sure the change of sss doesn't affect s
    assert(sss.size()==3);     //make sure 34567 is erased
    assert(sss.insert(66666));
    assert(sss.insert(77777));
    assert(sss.insert(88888));
    assert(sss.insert(99999));
    assert(sss.erase(12345));
    
    sss.dump();
    assert(s.size()==4);     //make sure that s is not changed
    assert(s.contains(12345));     //test if sss get everything from s
    assert(s.contains(23123));
    assert(s.contains(34567));
    assert(s.contains(45678));
    
    sss.swap(s);
    //test swap
    assert(sss.get(0,x)&&x==12345);     //test if swap get item right
    assert(sss.get(1,x)&&x==23123);
    assert(sss.get(2,x)&&x==34567);
    assert(sss.get(3,x)&&x==45678);
    assert(sss.size()==4);
    
    assert(s.get(0,x)&&x==23123);     //test if swap get item right
    assert(s.get(1,x)&&x==45678);
    assert(s.get(2,x)&&x==66666);
    assert(s.get(3,x)&&x==77777);
    assert(s.get(4,x)&&x==88888);
    assert(s.get(5,x)&&x==99999);
    assert(s.size()==6);
    
    assert(ss.insert(45454));     //add something to test unite later on
    ss.dump();
    unite(sss,s,ss);     //test unite
    ss.dump();
    assert(ss.get(0,x)&&x==12345);     //test if unite get data right
    assert(ss.get(1,x)&&x==23123);
    assert(ss.get(2,x)&&x==34567);
    assert(ss.get(3,x)&&x==45678);
    assert(ss.get(4,x)&&x==66666);
    assert(ss.get(5,x)&&x==77777);
    assert(ss.get(6,x)&&x==88888);
    assert(ss.get(7,x)&&x==99999);
    
    subtract(sss,s,ss);     //test subtract
    assert(ss.get(0,x)&&x==12345);
    assert(ss.get(1,x)&&x==34567);
    
    
    
}
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Set>::value,
              "Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
              "Set must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Set::operator=, Set& (Set::*)(const ItemType&));
    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
    CHECKTYPE(&Set::size,      int  (Set::*)() const);
    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
    CHECKTYPE(unite,    void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(subtract, void (*)(const Set&, const Set&, Set&));
}



int main()
{
    Set test1;
    test1.dump();
    assert(!test1.contains(123));   //test contain when empty
    assert(test1.empty());          //test empty
    assert(test1.size() == 0);      //test size when empty
    
    assert(test1.insert(500));      //test insert
    test1.dump();
    assert(test1.contains(500));       //test contain
    
    assert(test1.insert(999));  //insert at the end
    
    assert(test1.insert(100));  //insert at the beginning
    assert(!test1.contains(123));       //test contain when there is no such item
    assert(test1.contains(100));        //test contain when not empty
    assert(!test1.insert(100));         //insert an existing object
    
    assert(!test1.empty());             //test empty when not empty
    assert(test1.size() == 3);          //test size when not empty
    assert(test1.insert(109));   //in the middle
    assert(!test1.insert(109));         //insert existing object
    test1.dump();
    
    
    
    assert(!test1.erase(923));      //test erase an item not in the list
    assert(test1.erase(100));       //test erase at the beginning
    test1.dump();
    assert(test1.erase(999));       //test erase at the end
    assert(!test1.erase(100));
    assert(test1.insert(100));
    test1.dump();
    assert(test1.erase(109));       //test erase in the middle
    assert(test1.size() == 2);      //test size after erase
    
    assert(test1.erase(100));       //
    assert(test1.erase(500));
    assert(test1.empty());          //test empty after erasing
    test1.dump();
    assert(test1.insert(100));
    assert(test1.insert(500));
    assert(test1.insert(999));
    test1.dump();
    
    //copy
    
    Set test2;
    assert(test2.insert(123));
    assert(test2.insert(234));
    assert(test2.insert(345));
    assert(test2.insert(456));
    assert(test2.insert(567));
    assert(test2.insert(678));
    
    Set pop = test1;            //test copy-
    test1 = test2;              //test assign
    test1.dump();
    
    testCopy(test1);            //-test assign operator and copy constructor
    assert(test1.size() == 6);  //test copy constructor that it does not change the original
    cerr <<endl;
    test1.dump();
    
    ItemType x;
    assert(test1.get(0,x) && x == 123);     //test get when i = 0
    assert(test1.get(5,x) && x == 678);     //test get when i = size-1
    assert(!test1.get(6,x));                //test get when i = size
    assert(!test1.get(-1, x));              //test get when i < 0
    //test11();
    test22();                               //test code from website

    Set test3;
    assert(test3.insert(124235));
    assert(test3.insert(87324));
    assert(test3.insert(2315));
    
    unite(test1, pop, test3);               //test unite with 3 different Set:
    test3.dump();
    assert(test3.size()==9);
    assert(test3.contains(123));
    assert(test3.contains(234));
    assert(test3.contains(345));
    assert(test3.contains(456));
    assert(test3.contains(567));
    assert(test3.contains(678));
    assert(test3.contains(100));
    assert(test3.contains(500));
    assert(test3.contains(999));


    Set jim;
    
    subtract(test3, pop, jim);          //test subtract with 3 different
    jim.dump();
    assert(jim.size()==6);
    
    
    unite(test1, pop, test1);           //test unite with s1 and result aliasing
    assert(test1.size() == 9);
    assert(test1.contains(123));
    assert(test1.contains(234));
    assert(test1.contains(678));
    assert(test1.contains(500));
    assert(test1.contains(100));


    subtract(test1, pop, test1);        //test subtract with s1 and result aliasing
    assert(test1.size() == 6);
    assert(test1.contains(123));
    assert(test1.contains(234));
    assert(test1.contains(345));
    assert(test1.contains(456));
    assert(test1.contains(567));
    assert(test1.contains(678));

    
    unite(test1, pop, pop);         //test unite with s2 and result aliasing
    assert(pop.size() == 9);
    assert(pop.contains(123));
    assert(pop.contains(567));
    assert(pop.contains(500));

    
    subtract(test1, pop, pop);      //test subtract with s2 and result aliasing
    assert(pop.empty());
    
    unite(test1, test1, pop);        //test unite with s1 and s2 aliasing
    assert(pop.size() == 6);
    assert(pop.contains(123));
    assert(pop.contains(234));
    assert(pop.contains(567));
    assert(pop.contains(678));

    subtract(test1, test1, pop);        //test subtract with s1 and s2 aliasing
    assert(pop.empty());
    
    unite(test1, test1, test1);     //test 3 same unite aliasing
    assert(test1.size() == 6);
    assert(test1.contains(123));
    assert(test1.contains(234));
    assert(test1.contains(345));
    assert(test1.contains(456));
    assert(test1.contains(567));
    assert(test1.contains(678));
    
    test1 = test1;              //test assign operator aliasing
    assert(test1.size() == 6);
    assert(test1.contains(123));
    assert(test1.contains(234));
    assert(test1.contains(345));
    assert(test1.contains(456));
    assert(test1.contains(567));
    assert(test1.contains(678));
    
    subtract(test1, test1, test1);      //test subtract with 3 same aliasing
    test1.dump();
    assert(test1.empty());
    
    
    test();
}


void testCopy(Set t)
{
    std::cerr << "Set t is: " << std::endl;
    t.dump();
    t.erase(123);
    t.erase(234);
    t.erase(345);
    assert(t.size() == 3);


}
/*
void test11()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "bing";
    assert(ss.get(0, x)  &&  x == "pita");
    assert(ss.get(1, x)  &&  x == "roti");
}

void test22()
{
    Set uls;
    assert(uls.insert(10));
    assert(uls.insert(20));
    assert(uls.size() == 2);
    assert(uls.contains(20));
    ItemType x = 30;
    assert(uls.get(0, x)  &&  x == 10);
    assert(uls.get(1, x)  &&  x == 20);
}

#include <iostream>
void dosmt()
{
    if(0==0)
    {
        std::cout << "yes" << std::endl;
        return;
    }
    else
        {
            std::cout << "no" <<std::endl;
        }
}

int main()
{
    dosmt();
}


*/

