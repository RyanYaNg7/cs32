Our specially instrumented class is IntWrapper.

========================== IntWrapper.h

#ifndef INTWRAPPER_INCLUDED
#define INTWRAPPER_INCLUDED

// IntWrapper simply stores and retrieves an int.  However, every
// constructor, the destructor, and the assignment operator report
// when they're called.

class IntWrapper
{
  public:
    IntWrapper();
    IntWrapper(int i);
    IntWrapper(const IntWrapper& other);
    ~IntWrapper();
    IntWrapper& operator=(const IntWrapper& rhs);
    int value() const;
  private:
    int m_value;
};

bool operator==(const IntWrapper& lhs, const IntWrapper& rhs);
bool operator!=(const IntWrapper& lhs, const IntWrapper& rhs);

#endif // INTWRAPPER_INCLUDED

========================== IntWrapper.cpp

#include "IntWrapper.h"
#include <iostream>

using namespace std;

IntWrapper::IntWrapper() : m_value(0)
{
    cerr << "Created 0(" << this << ") (default)" << endl;
}

IntWrapper::IntWrapper(int i) : m_value(i)
{
    cerr << "Created " << m_value << "(" << this << ")" << endl;
}

IntWrapper::IntWrapper(const IntWrapper& other) : m_value(other.m_value)
{
    cerr << "Created " << m_value << "(" << this << ") copied from ("
         << &other << ")" << endl;
}

IntWrapper::~IntWrapper()
{
    cerr << "Destroyed " << m_value << "(" << this << ")" << endl;
}

IntWrapper& IntWrapper::operator=(const IntWrapper& other)
{
    cerr << "Replaced " << m_value << "(" << this << ") by assigning from "
	 << other.m_value << "(" << &other << ")" << endl;
    m_value = other.m_value;
    return *this;
}

int IntWrapper::value() const
{
    return m_value;
}

bool operator==(const IntWrapper& lhs, const IntWrapper& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(const IntWrapper& lhs, const IntWrapper& rhs)
{
    return lhs.value() != rhs.value();
}

========================== Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include "IntWrapper.h"       // TODO: remove this line after testing
#include <string>

using KeyType = std::string;
using ValueType = IntWrapper; // TODO: replace this line after testing

class Map
{
  public:

etc.

========================== Map.cpp

#include "Map.h"

etc.

========================== testMapMemoryLeak.cpp

#include "Map.h"
#include <iostream>

using namespace std;

void test()
{
	  cerr << "test A" << endl;
	Map m;
	  cerr << "test B" << endl;
	m.insert("10", IntWrapper(10));
	  cerr << "test C" << endl;
	m.insert("20", IntWrapper(20));
	  cerr << "test D" << endl;
	Map m2;
	  cerr << "test E" << endl;
	m2.insert("30", IntWrapper(30));
	  cerr << "test F" << endl;
	m2 = m;
	  cerr << "test G" << endl;
	m2.insert("40", IntWrapper(40));
	  cerr << "test H" << endl;
}

int main()
{
	test();
	cerr << "DONE" << endl;
}

==========================

If building this and executing it produced the output below, then since
every address that appears in a creation message has a corresponding
appearance in a destruction message, we know that for this test, at least,
there were no memory leaks of list nodes.  This is by no means a complete
test, but it gives you an idea of what you can do.

The following output has been annotated by hand.  It so happens that our
Map implementation uses a dummy node; yours need not.

test A
Created 0(0x12f86018) (default)      // value in dummy node for m's list
test B
Created 10(0x7fff8b5f5790)  // the temporary object produced by IntWrapper(10)
Created 0(0x12f86078) (default)      // in the new node created in Map::insert
Replaced 0(0x12f86078) by assigning from 10(0x7fff8b5f5790)  // stuffing Map::insert's
                                                 // parameter into the new node
Destroyed 10(0x7fff8b5f5790) // After returning from Map::insert, destroy the temp
test C
Created 20(0x7fff8b5f57b0)  // ditto for IntWrapper(20)
Created 0(0x12f860d8) (default)
Replaced 0(0x12f860d8) by assigning from 20(0x7fff8b5f57b0)
Destroyed 20(0x7fff8b5f57b0)
test D
Created 0(0x12f86108) (default)      // value in dummy node for m2's list
test E
Created 30(0x7fff8b5f57d0)  // creating and inserting IntWrapper(30)
Created 0(0x12f86168) (default)
Replaced 0(0x12f86168) by assigning from 30(0x7fff8b5f57d0)
Destroyed 30(0x7fff8b5f57d0)
test F          // We implemented Map::operator= using copy-and-swap
Created 0(0x12f86198) (default)      // value in dummy node of temp list
Created 0(0x12f861c8) (default)      // copy the two nodes of m
Replaced 0(0x12f861c8) by assigning from 10(0x12f86078)
Created 0(0x12f861f8) (default)
Replaced 0(0x12f861f8) by assigning from 20(0x12f860d8)
Destroyed 30(0x12f86168)             // after swap, destroy old list
Destroyed 0(0x12f86108)
test G
Created 40(0x7fff8b5f57f0)  // creating and inserting IntWrapper(40)
Created 0(0x12f86168) (default)
Replaced 0(0x12f86168) by assigning from 40(0x7fff8b5f57f0)
Destroyed 40(0x7fff8b5f57f0)
test H
Destroyed 40(0x12f86168)    // destroy the nodes in m2
Destroyed 20(0x12f861f8)
Destroyed 10(0x12f861c8)
Destroyed 0(0x12f86198)
Destroyed 20(0x12f860d8)    // destroy the nodes in m
Destroyed 10(0x12f86078)
Destroyed 0(0x12f86018)
DONE
