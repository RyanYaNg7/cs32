// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.
/*
#include "SymbolTable.h"
#include <string>
#include <vector>
#include <cassert>
#include <functional>
using namespace std;

int NUM_BUCKETS = 20000;

//our own hashfunction
unsigned int hashFunction(const string& id)
{
    hash<string> str_hash;      //this is a string hasher
    unsigned int hashValue = str_hash(id);    //hash our stirng
    
    unsigned int bucketNum = hashValue %  NUM_BUCKETS;
    
    return bucketNum;
    
}



// This class does the real work of the implementation.
struct Identifiers
{
    vector<int> m_lines;
};


class SymbolTableImpl
{
public:
    SymbolTableImpl();
    ~SymbolTableImpl();
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
private:
    Identifiers *Buckets[20000];
    vector<int> startLineOfScope;     //
    int LastLine;
    vector<string> m_ids;
};

SymbolTableImpl::SymbolTableImpl() : LastLine(0)
{
    for (int n = 0; n < 20000; n++)
    {
        Buckets[n] = nullptr;
    }
}

SymbolTableImpl::~SymbolTableImpl()
{
    for (int n = 0; n < 20000; n++)
    {
        delete Buckets[n];
    }
}

void SymbolTableImpl::enterScope()      //O(1)
{
    // Extend the id vector with an empty string that
    // serves as a scope entry marker.
    
    startLineOfScope.push_back(LastLine+1);
    m_ids.push_back("");
}

bool SymbolTableImpl::exitScope()       //O(n)  n: number of identifiers with in a scope
{
    if (startLineOfScope.empty())
        return false;
    
    
    // Remove ids back to the last scope entry.
    //assert(m_ids[startLineOfScope.back()-1] == "");
    int n = LastLine-1;
    for (; m_ids[n] != ""; n--)
    {
        //assert(m_ids.back() == m_ids[n]);
        int bucketNum = hashFunction(m_ids.back());
        Buckets[bucketNum]->m_lines.pop_back();
        
        if (Buckets[bucketNum]->m_lines.empty())
            Buckets[bucketNum] = nullptr;
        m_ids.pop_back();
    }
    
    // Remove the scope entry marker itself.
    startLineOfScope.pop_back();
    m_ids.pop_back();

    LastLine = n;
    return true;

}

bool SymbolTableImpl::declare(const string& id, int lineNum)    //O(N)
{
    if (id.empty())
        return false;
    
    // Check for another declaration in the same scope.
    // Return if found, break out if encounter the scope
    // entry marker.
    
    if (!startLineOfScope.empty())
    {
        if (find(id) > startLineOfScope.back())    //this identifier is declared after the entering of current scope
            return false;
    }
    else
    {
        if (find(id) != -1)
            return false;
    }
    // Save the declaration
    m_ids.push_back(id);
    
    LastLine = lineNum;//+startLineOfScope.size(); /////////////////////////
    
    int bucketNum = hashFunction(id);
    if (Buckets[bucketNum] == nullptr)  //first identifier of this name
    {
        Buckets[bucketNum] = new Identifiers;
        Buckets[bucketNum]->m_lines.push_back(lineNum);
    }
    else    //already have this name before
    {
        Buckets[bucketNum]->m_lines.push_back(lineNum);
    }
    
    return true;
}

int SymbolTableImpl::find(const string& id) const   //O(N)
{
    if (id.empty())
        return -1;
    

    
    // Search back for the most recent declaration still
    // available.
    
    int bucketNum = hashFunction(id);
    if (Buckets[bucketNum] == nullptr)  //no such identifier
    {
        return -1;
    }
    else
        return Buckets[bucketNum]->m_lines.back();   //return the last entered line number for this identifier
    
}

//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
    m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
    delete m_impl;
}

void SymbolTable::enterScope()
{
    m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
    return m_impl->exitScope();
}

bool SymbolTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int SymbolTable::find(const string& id) const
{
    return m_impl->find(id);
}
 
*/
