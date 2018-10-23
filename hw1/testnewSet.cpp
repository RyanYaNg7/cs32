//
//  testnewSet.cpp
//  hw1
//
//  Created by 杨子鸣 on 4/15/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

/*


 #include "newSet.h"
 
 #include <iostream>
 #include <cassert>
 using namespace std;
 
 void testCopy(Set t);
 int main()
 { Set a(1000);   // a can hold at most 1000 distinct items
 Set b(5);      // b can hold at most 5 distinct items
 Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
 
 ItemType v[6] = {123,234,345,456,567,678};
 
 // No failures inserting 5 distinct items into b
 for (int k = 0; k < 5; k++)
 assert(b.insert(v[k]));
 
 // Failure if we try to insert a sixth distinct item into b
 assert(!b.insert(v[5]));
 
 // When two Sets' contents are swapped, their capacities are swapped
 // as well:
 cerr << "b is \n";
 b.dump();
 
 c = b;
 
 cerr << "c is \n";
 c.dump();
 
 testCopy(c);
 assert(c.size() == 5);
 
 a.swap(b);
 assert((!a.insert(v[5])) && b.insert(v[5]));
 cerr << "a is \n";
 a.dump();
 
 
 
 
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
 
 s = s;
 
 assert(s.size() == 3);
 assert(s.get(0, x)  &&  x == 01723461);
 assert(s.get(2, x)  &&  x == 123456789);
 assert(s.contains(87162354));
 assert(!s.contains(1122334));
 assert(!s.erase(0000000));
 assert(!s.insert(87162354));
 
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
 
 void testCopy(Set t)
 {
 std::cerr << "stupid t is " << std::endl;
 t.dump();
 t.erase(123);
 t.erase(234);
 t.erase(345);
 assert(t.size() == 2);
 }
 
 
 
 */
 
