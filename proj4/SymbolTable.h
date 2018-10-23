#ifndef SYMBOLTABLE_INCLUDED
#define SYMBOLTABLE_INCLUDED

#include <string>

class SymbolTableImpl;

class SymbolTable
{
  public:
    SymbolTable();
    ~SymbolTable();
    void enterScope();
    bool exitScope();
    bool declare(const std::string& id, int lineNum);
    int find(const std::string& id) const;
      // We prevent a SymbolTable object from being copied or assigned
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable& operator=(const SymbolTable&) = delete;

  private:
    SymbolTableImpl* m_impl;
};

#endif // SYMBOLTABLE_INCLUDED
