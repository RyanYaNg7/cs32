//
//  OurType.cpp
//  proj2
//
//  Created by 杨子鸣 on 5/2/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "OurType.h"
#include "Set.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <type_traits>
#include <cassert>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
    return OurType::m_count;
}

inline int nasstcopys()
{
    return OurType::m_asstcopycount;
}

ItemType SOMEVAL = ItemType(123);
ItemType DEFAULT = ItemType(0);
ItemType ARRAY[6] = {
    ItemType(10), ItemType(20), ItemType(30),
    ItemType(40), ItemType(50), ItemType(60),
};

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
            ItemType x = SOMEVAL;
            assert(!s.get(0, x));
        } break; case 10: {
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 11: {
            assert(s.insert(SOMEVAL));
        } break; case 12: {
            s.insert(SOMEVAL);
            assert(!s.empty());
        } break; case 13: {
            s.insert(SOMEVAL);
            assert(s.size() == 1);
        } break; case 14: {
            s.insert(SOMEVAL);
            assert(s.contains(SOMEVAL));
        } break; case 15: {
            s.insert(SOMEVAL);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 16: {
            s.insert(SOMEVAL);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == SOMEVAL);
        } break; case 17: {
            assert(s.insert(SOMEVAL)  &&  !s.insert(SOMEVAL));
        } break; case 18: {
            s.insert(SOMEVAL);
            s.insert(SOMEVAL);
            assert(s.size() == 1);
        } break; case 19: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(!s.empty()   &&  s.size() == 2);
        } break; case 20: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 21: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 22: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = SOMEVAL;
            s.get(0, x);
            ItemType y = SOMEVAL;
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
            ItemType x = SOMEVAL;
            s.get(-1, x);
            assert(x == SOMEVAL);
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
            ItemType x = SOMEVAL;
            s.get(3, x);
            assert(x == SOMEVAL);
        } break; case 41: {
            s.insert(DEFAULT);
            ItemType x = SOMEVAL;
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
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[0]);
                int n = nasstcopys();
                s.swap(s2);
                int n2 = nasstcopys();
                assert(n2 >= n  &&  n2 <= n+3);  // swapping head nodes OK
            }
        } break; case 50: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                s2.erase(ARRAY[1]);
                s2.insert(ARRAY[3]);
                s2.erase(ARRAY[2]);
                s2.insert(ARRAY[1]);
                s2.erase(ARRAY[0]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 51: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                Set s3(s2);
                s3.insert(ARRAY[2]);
                s3.erase(ARRAY[1]);
                s3.insert(ARRAY[3]);
                s3.erase(ARRAY[2]);
                s3.insert(ARRAY[1]);
                s3.erase(ARRAY[0]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 52: {
            int before = itemcount();
            {
                Set s2;
                s2.insert(SOMEVAL);
                assert(itemcount() > before);
            }
            assert(itemcount() == before);
        } break; case 53: {
            int before = itemcount();
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                int mid = itemcount();
                Set s3(s2);
                assert(s3.size() == 3);
                assert(itemcount() - mid == mid - before);
            }
            assert(itemcount() == before);
        } break; case 54: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 55: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s2, ARRAY, 4));
            }
        } break; case 56: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s, ARRAY, 3));
            }
        } break; case 57: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                Set s3;
                s3.insert(ARRAY[3]);
                s3.insert(ARRAY[4]);
                s3 = s2;
                s3.insert(ARRAY[2]);
                s3.erase(ARRAY[1]);
                s3.insert(ARRAY[3]);
                s3.erase(ARRAY[2]);
                s3.insert(ARRAY[1]);
                s3.erase(ARRAY[0]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 58: {
            int before = itemcount();
            {
                Set s2;
                Set s3;
                int mid = itemcount();
                s3.insert(ARRAY[0]);
                s3.insert(ARRAY[1]);
                assert(s2.empty());
                s3 = s2;
                assert(s3.size() == 0);
                assert(itemcount() == mid);
            }
            assert(itemcount() == before);
        } break; case 59: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            int before = itemcount();
            {
                Set s2;
                s2.insert(ARRAY[2]);
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                int mid = itemcount();
                s2 = s;
                assert(itemcount() <= mid);
            }
            assert(itemcount() == before);
        } break; case 60: {
            int before = itemcount();
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                int mid = itemcount();
                Set s3;
                s3.insert(ARRAY[3]);
                s3.insert(ARRAY[4]);
                s3 = s2;
                assert(itemcount() - mid == mid - before);
            }
        } break; case 61: {
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
        } break; case 62: {
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
        } break; case 63: {
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
        } break; case 64: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                int n2 = itemcount();
                s2 = s2;
                assert(itemcount() == n2);
            }
        } break; case 65: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                s2 = s2;
                s2.insert(ARRAY[3]);
                assert(isPermutation(s2, ARRAY, 4));
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 66: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            Set s3;
            unite(s,s2,s3);
            assert(s3.size() == s.size());
            assert(isPermutation(s3, ARRAY, 2));
        } break; case 67: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            Set s3;
            unite(s2,s,s3);
            assert(s3.size() == s.size());
            assert(isPermutation(s3, ARRAY, 2));
        } break; case 68: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            Set s3;
            unite(s,s2,s3);
            assert(isPermutation(s3, ARRAY, 3));
        } break; case 69: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            Set s3;
            s3.insert(ARRAY[3]);
            unite(s,s2,s3);
            assert(isPermutation(s3, ARRAY, 3));
        } break; case 70: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            unite(s,s2,s);
            assert(isPermutation(s, ARRAY, 3));
        } break; case 71: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            unite(s,s2,s2);
            assert(isPermutation(s2, ARRAY, 3));
        } break; case 72: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            Set s3;
            subtract(s,s2,s3);
            assert(s3.size() == s.size());
            assert(isPermutation(s3, ARRAY, 2));
        } break; case 73: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            Set s3;
            subtract(s2,s,s3);
            assert(s3.size() == 0);
        } break; case 74: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            Set s3;
            subtract(s,s2,s3);
            assert(s3.size() == 1);
            ItemType x;
            s3.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 75: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            Set s3;
            s3.insert(ARRAY[3]);
            s3.insert(ARRAY[4]);
            subtract(s,s2,s3);
            assert(s3.size() == 1);
            ItemType x;
            s3.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 76: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            subtract(s,s2,s);
            assert(s.size() == 1);
            ItemType x;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 77: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            Set s2;
            s2.insert(ARRAY[1]);
            s2.insert(ARRAY[2]);
            subtract(s,s2,s2);
            assert(s2.size() == 1);
            ItemType x;
            s2.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 78: {
            const int NITEMS = 2000;
            for (int k = NITEMS; k > 0; k--)
                assert(s.insert(ItemType(k)));
            assert(s.size() == NITEMS);
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