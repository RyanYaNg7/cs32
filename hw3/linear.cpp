//
//
//
//
/*
#include <iostream>
#include <string>
using namespace std;
 */
bool somePredicate(string s);
/*
{
    return (s.length() != 0);
}
*/
//The first four take an array of strings and the number of strings to examine in the array; the last takes two arrays of strings and the number of strings to examine in each:

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.

bool allTrue(const string a[], int n)
{
    if (n < 0)
    {
        cerr << "your n is negative!!! Let's pretend it is 0." << endl;
        n = 0;
    }
    
    //what if n > size
    
    //base caes
    if (n == 0)
    {
        cerr << " finally now n == 0 and we return true" << endl;
        return true;
    }
    
    //recursive case
    if (somePredicate(a[n-1]))
    {
        cerr << "The " << n << "th string passes!!" << endl;
        return allTrue(a, n-1);
    }
    else
    {
        cerr << "The " << n << "th string fails!!" << endl;
        return false;
    }
}



// Return the number of elements in the array for which the
// somePredicate function returns false.

int countFalse(const string a[], int n)
{
    int numberC = 0;
    if (n < 0)
    {
        cerr << "your n is negative!!! Let's pretend it is 0." << endl;
        n = 0;
    }
    
    //base case
    if (n == 0)
    {
        return numberC;
    }
    
    //recursive case
    if (somePredicate(a[n-1]))
    {
        return countFalse(a, n-1)+numberC;
    }
    else
    {
        numberC++;
        cerr << "The " << n << "th string fails!!" << endl;
        return countFalse(a, n-1)+numberC;
    }
}


// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n < 0)
    {
        cerr << "your n is negative!!! Let's pretend it is 0." << endl;
        n = 0;
    }
    
    if (n == 0)
        return -1;
    
    int front = firstFalse(a, n-1);

    if (!somePredicate(a[n-1]))
    {
        if (front != -1)
            return front;
        else
            return n-1;
    }
    else
        return front;
}



// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const string a[], int n)
{
    if (n < 0)
    {
        cerr << "your n is negative!!! Let's pretend it is 0." << endl;
        n = 0;
    }
    
    if (n == 0)
        return -1;
    
    if (n == 1)
        return 0;
    int front = indexOfLeast(a, n-1);
    
    if (a[front] <= a[n-1])
    {
        return front;
    }
    else
        return n-1;

}




// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true;

// otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.

// (Of course, if a2 is empty (i.e., n2 is 0), return true.)

// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0)
        return false;
    
    if (n2 <= 0)
        return true;
    
    if (n1 < n2)
        return false;
        
        
    if (a1[0] == a2[0])
    {
        if (n2 == 1)
            return true;
        else
            return includes(a1+1, n1-1, a2+1, n2-1);
    }
    else
        return includes(a1+1, n1-1, a2, n2);
        

    
    
}

/*
int main()
{
    string t[4];
    t[0] = "yang";
    t[1] = "zi";
    t[2] = "ming";
    t[3] = "zhu";
    
    assert(allTrue(t, 4));
    assert(allTrue(t, -1));
    assert(allTrue(t, 0));
    
    assert(countFalse(t, -7) == 0);
    assert(countFalse(t, 4) == 0);
    
    assert(firstFalse(t, 4) == -1);
    
    assert(indexOfLeast(t, 4) == 2);
    assert(indexOfLeast(t, 0) == -1);
    assert(indexOfLeast(t, -3) == -1);
    assert(indexOfLeast(t, 1) == 0);
    assert(indexOfLeast(t, 2) == 0);
    
    
    
    string e[4];
    e[0] = "zi";
    e[1] = "alabo";
    e[2] = "ming";
    e[3] = "";
    assert(!allTrue(e, 4));
    assert(allTrue(e, 1));
    assert(allTrue(e, 0));
    assert(allTrue(e, -4));
    
    assert(countFalse(e, 0) == 0);
    assert(countFalse(e, 4) == 1);
    
    assert(firstFalse(e, 4) == 3);
    assert(firstFalse(e, 0) == -1);
    assert(firstFalse(e, -1) == -1);
    assert(firstFalse(e, 3) == -1);

    assert(indexOfLeast(e, 4) == 3);
    assert(indexOfLeast(e, 3) == 1);
    assert(indexOfLeast(e, 1) == 0);
    
    string s[4];
    s[0] = "yang";
    s[1] = "";
    s[2] = "zi";
    s[3] = "";
    
    assert(countFalse(s, 4) == 2);
    assert(countFalse(s, 2) == 1);
    
    assert(firstFalse(s, 4) == 1);
    assert(firstFalse(s, 1) == -1);
    assert(firstFalse(s, 2) == 1);

    assert(indexOfLeast(s, 4) == 1);
    assert(indexOfLeast(s, 1) == 0);
    
    // For example, if a1 is the 7 element array
        //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
        // then the function should return true if a2 is
        //    "kyle" "kenny" "butters"
        // or
        //    "kyle" "cartman" "cartman"
        // and it should return false if a2 is
        //    "kyle" "butters" "kenny"
        // or
        //    "stan" "kenny" "kenny"
    
    string a1[7] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    
    string a2[3] = {"kyle", "kenny", "butters"};
    
    assert(includes(a1, 7, a2, 3));
    assert(!includes(a2,3, a1, 7));
    assert(!includes(a1, 6, a2, 3));
    assert(includes(a1,5, a2, 2));
    assert(includes(a1, 5, a2, 0));
    assert(includes(a1, 5, a2, -5));
    assert(!includes(a1, 0, a2, 3));
    assert(!includes(a1, -2, a2, 3));
    assert(includes(a1, 6, a1, 6));
    assert(includes(a2, 3, a2, 1));
    
    string a3[3] = {"kyle", "cartman", "cartman"};
    assert(includes(a1, 7, a3, 3));
    assert(includes(a1, 6, a3, 3));
    assert(!includes(a1, 3, a3, 3));
    assert(includes(a1, 3, a3, 2));
    
    string a4[] = {"kyle", "butters", "kenny"};
    assert(!includes(a1, 7, a4, 3));
    assert(includes(a1, 7, a4, 2));
    
    string a5[] = {"stan", "kenny", "kenny"};
    assert(!includes(a1, 7, a5, 3));
    assert(includes(a1, 5, a5, 2));

    
    
}
*/
