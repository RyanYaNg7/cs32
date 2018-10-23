//
//  eval.cpp
//  hw2
//
//  Created by 杨子鸣 on 4/28/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result)
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.)
{
    string realinf;
    for (int n = 0; n < infix.size(); n++)
    {
        if (infix[n] != ' ')
        {
            if (infix[n] != 'F'  &&  infix[n] != 'T'  &&  infix[n] != '!'  &&  infix[n] != '&'  &&  infix[n] != '|'  &&  infix[n] != '('  &&  infix[n] != ')')
                return 1;
            else
                realinf += infix[n];
        }
    }
    
    if (realinf.size() == 0)
        return 1;
    int opencount = 0;
    int closecount = 0;
    
    stack<char> operators;
    postfix = "";
    //infix to postfi conversion
    for (int n = 0; n < realinf.size(); n++)
    {
        switch (realinf[n])
        {
            case 'T':
            case 'F':
                if (n > 0)
                {
                    if (realinf[n-1] == 'T' || realinf[n-1] == 'F')
                        return 1;
                }
                postfix += realinf[n];
                break;
            
            case '(':
                if (n > 0)
                    if (realinf[n-1] == 'F' ||  realinf[n-1] == 'T')
                        return 1;
                opencount++;
                operators.push(realinf[n]);
                break;
            case ')':
                closecount++;
                if(closecount > opencount)
                    return 1;
                if (realinf[n-1] == '('  ||  realinf[n-1] == '&'  ||  realinf[n-1] == '|'  ||  realinf[n-1] == '!')
                    return 1;
    
                while (operators.top() != '(')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop();
                break;
                
                
            case '!':
                if (n == realinf.size()-1)
                    return 1;
                if (n > 0)
                    if (realinf[n-1] == 'T'  ||  realinf[n-1] == 'F')
                
                while (!operators.empty()  &&  operators.top() != '(' &&  operators.top() != '&'  &&  operators.top() != '|')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(realinf[n]);
                break;
                
            case '&':
                if (n == realinf.size()-1)
                    return 1;
                if (n == 0)
                    return 1;
                if (realinf[n-1] == '(' ||  realinf[n-1] == '!'  ||  realinf[n-1] == '|'  ||  realinf[n-1] == '&')
                    return 1;
                
                while (!operators.empty()  &&  operators.top() != '(' &&  operators.top() != '|')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(realinf[n]);
                break;
                
            case '|':
                if (n == realinf.size()-1)
                    return 1;
                if (n == 0)
                    return 1;
                if (realinf[n-1] == '('  ||  realinf[n-1] == '!'  ||  realinf[n-1] == '&'  ||  realinf[n-1] == '|')
                    return 1;
                while (!operators.empty()  &&  operators.top() != '(')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(realinf[n]);
                break;
        }

    }
    if (opencount != closecount)
        return 1;
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    
    // evaluate the postfix
    for (int n = 0; n < postfix.size(); n++)
    {
        if (postfix[n] == 'T'  ||  postfix[n] == 'F')
        {
            operators.push(postfix[n]);
        }
        else if (postfix[n] == '|'  ||  postfix[n] == '&')
        {
            bool operand2;
            if (operators.top() == 'T')
                operand2 = true;
            else if (operators.top() == 'F')
                operand2 = false;
            else
            {
                cerr << "something wrong with your postfix in TF" << endl;
                return 1;
            }
            operators.pop();
            
            bool operand1;
            if (operators.top() == 'T')
                operand1 = true;
            else if (operators.top() == 'F')
                operand1 = false;
            else
            {
                cerr << "something wrong with your postfix in TF" << endl;
                return 1;
            }
            operators.pop();
            bool tempresult;
            if (postfix[n] == '|')
                tempresult = (operand1|operand2);
            else
                tempresult = (operand1&operand2);
            
            if (tempresult)
                operators.push('T');
            else
                operators.push('F');
        }
        else if (postfix[n] == '!')
        {
            bool operand;
            if (operators.top() == 'T')
                operand = true;
            else if (operators.top() == 'F')
                operand = false;
            else
            {
                cerr << "something wrong with your postfix in TF" << endl;
                return 1;
            }
            operators.pop();
            
            if (operand)
                operators.push('F');
            else
                operators.push('T');
        }
        else
        {
            cerr << "there is something wrong with you postfix!" << endl;
            return 1;
        }
    }
    bool operandfinal;
    if (operators.top() == 'T')
        operandfinal = true;
    else if (operators.top() == 'F')
        operandfinal = false;
    else
    {
        cerr << "there is something wrong with you postfix!" << endl;
        return 1;
    }
    
    operators.pop();
    if (operators.empty())
    {
        if (operandfinal)
        {
            result = true;
            return 0;
        }
        else
        {
            result = false;
            return 0;
        }
        
    }
    else
        return 1;
}



int main()
{
    string pf;
    
    bool answer;
    
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    
    
    assert(evaluate(" T ",pf,answer)==0 && pf =="T" && answer);
    assert(evaluate(" T F",pf,answer)==1);
    assert(evaluate(" T&&F ",pf,answer)==1);
    assert(evaluate(" T||F ",pf,answer)==1);
    assert(evaluate(" (F&T)F ",pf,answer)==1);
    assert(evaluate(" F(F&T) ",pf,answer)==1);
    assert(evaluate(" F( F & T ) ",pf,answer)==1);
    assert(evaluate(" F&(F&T) ",pf,answer)==0 && pf =="FFT&&" && !answer);
    assert(evaluate(" F&(F&T) ",pf,answer)==0 && pf =="FFT&&" && !answer);
    assert(evaluate(" F&(F&T)) ",pf,answer)==1);
    assert(evaluate(" (F&(F&T) ",pf,answer)==1);
    assert(evaluate(" (F&((F&T)) ",pf,answer)==1);
    assert(evaluate(" F&(F|T) ",pf,answer)==0 && pf =="FFT|&" &&!answer);
    assert(evaluate(" F|(F|T) ",pf,answer)==0 && pf =="FFT||" &&answer);
    assert(evaluate(" F&(F|!!!!T) ",pf,answer)==0 && pf =="FFT!!!!|&" &&!answer);
    assert(evaluate(" !F&(!F|!!!T) ",pf,answer)==0 && pf =="F!F!T!!!|&" &&answer);
    assert(evaluate(" !F&(!F|!!!T) ",pf,answer)==0 && pf =="F!F!T!!!|&" &&answer);
    assert(evaluate(" TT&(F) ",pf,answer)==1);
    assert(evaluate(" T&!(      F) ",pf,answer)==0 && pf =="TF!&" &&answer);
    assert(evaluate(" T&|F ",pf,answer)==1);
    assert(evaluate(" T&(|F) ",pf,answer)==1);
    assert(evaluate(" T&(!F) ",pf,answer)==0 && pf =="TF!&"&&answer);
    assert(evaluate(" T&(!F&) ",pf,answer)==1);
    assert(evaluate(" &T&(!F&) ",pf,answer)==1);
    assert(evaluate(" T&(!&F) ",pf,answer)==1);
    assert(evaluate(" ",pf,answer)==1);
    cout << "Passed all tests" << endl;
}