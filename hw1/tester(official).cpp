//When the following program is compiled along with Set.cpp, it can be run with input 1 through 52 to test your solution to Problem 3.
//If the #define of TESTNEW is uncommented and the program is compiled along with newSet.cpp, it can be run with input 1 through 68 to test your solution to Problem 5. (This program uses some features of C++ we're not covering, but that's irrelevant to you.)

// tester.cpp
// To test HW 1 Problem 5, uncomment the following line:
 #define TESTNEW

#ifdef TESTNEW
#include "newSet.h"
#else
#include "Set.h"
#endif

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

static ItemType DUMMY = 123;
static ItemType DEFAULT = 0;
static ItemType ARRAY[6] = { 10, 20, 30, 40, 50, 60 };

bool isPermutation(const Set& s, const ItemType a[], int n)
{
    if (s.size() != n)
        return false;
    vector<ItemType> b(n);
    for (int i = 0; i < n; i++)
        s.get(i, b[i]);
    for (int j = 0; j < n; j++)
    {
        int i;
        for (i = j; i < n; i++)
        {
            if (a[j] == b[i])
            {
                ItemType t = b[j];
                b[j] = b[i];
                b[i] = t;
                break;
            }
        }
        if (i == n)
            return false;
    }
    return true;
}

const int SPEC_MAX = 200;

void testone(int n)
{
    Set s;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Set::empty), bool (Set::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Set::size), int (Set::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Set::contains),
                    bool (Set::*)(const ItemType&) const>::value));
        } break; case  4: {
            assert((is_same<decltype(&Set::get),
                    bool (Set::*)(int, ItemType&) const>::value));
        } break; case  5: {
            assert(s.empty());
        } break; case  6: {
            assert(s.size() == 0);
        } break; case  7: {
            assert(!s.erase(DEFAULT)  &&  s.size() == 0);
        } break; case  8: {
            assert(!s.contains(DEFAULT));
        } break; case  9: {
            ItemType x = DUMMY;
            assert(!s.get(0, x));
        } break; case 10: {
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 11: {
            assert(s.insert(DUMMY));
        } break; case 12: {
            s.insert(DUMMY);
            assert(!s.empty());
        } break; case 13: {
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 14: {
            s.insert(DUMMY);
            assert(s.contains(DUMMY));
        } break; case 15: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 16: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 17: {
            assert(s.insert(DUMMY)  &&  !s.insert(DUMMY));
        } break; case 18: {
            s.insert(DUMMY);
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 19: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(!s.empty()   &&  s.size() == 2);
        } break; case 20: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 21: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 22: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = DUMMY;
            s.get(0, x);
            ItemType y = DUMMY;
            s.get(1, y);
            assert(x == ARRAY[0]  &&  y == ARRAY[1]);
        } break; case 23: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            assert(s.size() == 5);
        } break; case 24: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            ItemType x;
            for (int k = 0; k < 5; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 25: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            assert(s.size() == 2);
        } break; case 26: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x;
            for (int k = 0; k < 2; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 27: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[3]));
        } break; case 28: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            s.erase(ARRAY[3]);
            assert(s.size() == 4);
        } break; case 29: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[0])  &&  s.size() == 4);
        } break; case 30: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[4])  &&  s.size() == 4);
        } break; case 31: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            assert(s.erase(ARRAY[1])  &&  s.size() == 2);
        } break; case 32: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.erase(ARRAY[3]);
            assert(isPermutation(s, ARRAY, 3));
        } break; case 33: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[3]);
            assert(isPermutation(s, ARRAY, 3));
        } break; case 34: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(!s.erase(ARRAY[4]));
        } break; case 35: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[4]);
            assert(s.size() == 4);
        } break; case 36: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.erase(ARRAY[0]);
            s.erase(ARRAY[1]);
            assert(s.size() == 0);
        } break; case 37: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(!s.get(-1, x));
        } break; case 38: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(-1, x);
            assert(x == DUMMY);
        } break; case 39: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(! s.get(3, x));
        } break; case 40: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(3, x);
            assert(x == DUMMY);
        } break; case 41: {
            s.insert(DEFAULT);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(s.size() == 1  &&  x == DEFAULT);
        } break; case 42: {
            s.insert(DEFAULT);
            s.erase(DEFAULT);
            assert(s.size() == 0  &&  !s.contains(DEFAULT));
        } break; case 43: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(!s.contains(DEFAULT));
        } break; case 44: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(s.contains(ARRAY[2]));
        } break; case 45: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[2]);
            assert(s.size() == 2  &&  !s.contains(ARRAY[2]));
        } break; case 46: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(s.size() == 3  &&  s.contains(ARRAY[2])  &&
                   s.contains(ARRAY[3]));
        } break; case 47: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                assert(s.size() == 2  &&  s2.size() == 3);
            }
        } break; case 48: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                for (size_t k = 0; k < 3; k++)
                {
                    assert(!s.contains(ARRAY[k]));
                    assert(s2.contains(ARRAY[k]));
                }
                for (size_t k = 3; k < 5; k++)
                {
                    assert(s.contains(ARRAY[k]));
                    assert(!s2.contains(ARRAY[k]));
                }
            }
        } break; case 49: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(s.size() == SPEC_MAX);
        } break; case 50: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            ItemType x = SPEC_MAX;
            assert(!s.insert(x)  &&  s.size() == SPEC_MAX  &&  !s.contains(x));
        } break; case 51: {
            assert(s.insert(DUMMY));
            for (size_t k = 0; k < 10*SPEC_MAX; k++)
                assert(!s.insert(DUMMY));
            assert(s.size() == 1);
        } break; case 52: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(!s.insert(SPEC_MAX));
            s.erase(0);
            assert(s.insert(SPEC_MAX+1));
            assert(!s.insert(SPEC_MAX+2));
#ifdef TESTNEW
        } break; case 53: {
            // This test checked that swap takes the same amount of time
            // no matter how many items are in the Sets.
        } break; case 54: {
            const size_t CAPACITY = 2;
            Set s2(CAPACITY);
            for (size_t k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 55: {
            const size_t CAPACITY = SPEC_MAX*2;
            Set s2(CAPACITY);
            for (size_t k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 56: {
            // This test checked that the destructor deletes the dynamic array.
        } break; case 57: {
            // This test checked that Sets can be properly copied and destroyed.
        } break; case 58: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 59: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s2, ARRAY, 4));
            }
        } break; case 60: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s, ARRAY, 3));
            }
        } break; case 61: {
            {
                Set s2(2);
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                Set s3(s2);
                assert(!s3.insert(ARRAY[2]));
            }
        } break; case 62: {
            // This test checked that the assignment operator doesn't just
            // copy a pointer.
        } break; case 63: {
            // This test checked that empty Sets can be assigned and properly
            // destroyed.
        } break; case 64: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[2]);
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2 = s;
                s2.insert(ARRAY[5]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 65: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                assert(isPermutation(s2, ARRAY, 3));
            }
        } break; case 66: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                assert(isPermutation(s, ARRAY, 2));
            }
        } break; case 67: {
            // This test checked that self-assignment doesn't change the
            // number of items in existence.
        } break; case 68: {
            // This test checked that self-assignment doesn't change the Set.
#endif
        }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}