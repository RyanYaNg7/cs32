// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.

#include "SymbolTable.h"
#include <string>
#include <vector>
#include <cassert>
#include <functional>
using namespace std;

int NUM_BUCKETS =449;

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
    vector<string> stringId;
    vector<int> scopeNum;
    vector<int> lineNum;
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
    Identifiers *Buckets[449];
    int scopeN;
    bool exist(const string& id, int bucketNum) const;
    vector<int> bucket_number;
    
};

bool SymbolTableImpl::exist(const string& id, int bucketNum) const   //exist in the same scope
{
    int n = Buckets[bucketNum]->stringId.size()-1;
    while (n >= 0  &&  Buckets[bucketNum]->stringId[n] != id)
    {
        n--;
    }
    if (n < 0)
        return false;
    else
    {
        if (Buckets[bucketNum]->scopeNum[n] == scopeN)
            return true;
        else
            return false;
    }
}


SymbolTableImpl::SymbolTableImpl() : scopeN(0)
{
    for (int n = 0; n < 449; n++)
    {
        Buckets[n] = nullptr;
    }
}

SymbolTableImpl::~SymbolTableImpl()
{
    for (int n = 0; n < 449; n++)
    {
            delete Buckets[n];
    }
}

void SymbolTableImpl::enterScope()      //O(1)
{
    // Extend the id vector with an empty string that
    // serves as a scope entry marker.
    scopeN++;
}

bool SymbolTableImpl::exitScope()       //O(n)  n: number of identifiers with in a scope
{
    if (scopeN == 0)
        return false;
    
    
    // Remove ids back to the last scope entry.
/*
    for (int n = 0; n < NUM_BUCKETS; n++)
    {
        if (Buckets[n] != nullptr  &&  Buckets[n]->scopeNum.back() == scopeN)
        {
            Buckets[n]->scopeNum.pop_back();
            Buckets[n]->lineNum.pop_back();
            Buckets[n]->stringId.pop_back();
            
            if (Buckets[n]->lineNum.size() == 0)
                Buckets[n] = nullptr;
        }

    }
    */
    
    while (Buckets[bucket_number.back()]->scopeNum.back() == scopeN)    //still in this scope
    {
        //delete the information in Buckets
        Buckets[bucket_number.back()]->scopeNum.pop_back();
        Buckets[bucket_number.back()]->stringId.pop_back();
        Buckets[bucket_number.back()]->lineNum.pop_back();
        
        if (Buckets[bucket_number.back()]->lineNum.size() == 0)
            Buckets[bucket_number.back()] = nullptr;
        //delete the information in bucket_number vector
        
        bucket_number.pop_back();
    }
    
    scopeN--;
    return true;
    // Remove the scope entry marker itself.

    
}

bool SymbolTableImpl::declare(const string& id, int lineNum)    //O(N)
{
    if (id.empty())
        return false;
    
    // Check for another declaration in the same scope.
    // Return if found, break out if encounter the scope
    // entry marker.

    int bucketNum = hashFunction(id);
    
    if (Buckets[bucketNum] != nullptr  &&  exist(id, bucketNum))
    {
        return false;
    }
    
    // Save the declaration
    if (Buckets[bucketNum] == nullptr)
    {
        Buckets[bucketNum] = new Identifiers;
        Buckets[bucketNum]->lineNum.push_back(lineNum);
        Buckets[bucketNum]->scopeNum.push_back(scopeN);
        Buckets[bucketNum]->stringId.push_back(id);
    }
    else
    {
        Buckets[bucketNum]->lineNum.push_back(lineNum);
        Buckets[bucketNum]->scopeNum.push_back(scopeN);
        Buckets[bucketNum]->stringId.push_back(id);
    }
    bucket_number.push_back(bucketNum);
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
    {
        int n = Buckets[bucketNum]->stringId.size()-1;
        while (n >= 0  &&  Buckets[bucketNum]->stringId[n] != id)
        {
            n--;
        }
        if (n < 0)
            return -1;
        else
            return Buckets[bucketNum]->lineNum[n];   //return the last entered line number for this identifier
    }
    
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


