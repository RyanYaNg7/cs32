//
//  main.cpp
//  proj1
//
//  Created by 杨子鸣 on 4/9/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//


#include "Game.h"

#include <iostream>

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(3, 5, 2);
    
    // Play the game
    g.play();
}
/*
#include "rat.h"
#include "arena.h"
#include "player.h"

#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

class streambuf_switcher
{
public:
    streambuf_switcher(ios& dest, ios& src)
    : dest_stream(dest), saved_streambuf(dest.rdbuf(src.rdbuf()))
    {}
    ~streambuf_switcher()
    {
        dest_stream.rdbuf(saved_streambuf);
    }
private:
    ios& dest_stream;
    streambuf* saved_streambuf;
};

set<void*> addrs;
bool recordaddrs = false;

inline bool isRecordedSize(size_t n)
{
    return n == sizeof(Rat)  ||  n == sizeof(Player);
}

void* operator new(size_t n)
{
    void* p = malloc(n);
    fill_n(static_cast<char*>(p), n, 0xca);
    if (recordaddrs  &&  isRecordedSize(n))
    {
        recordaddrs = false;
        addrs.insert(p);
        recordaddrs = true;
    }
    return p;
}

#if __cplusplus >= 201402L
void operator delete(void* p) noexcept
{
    free(p);
}

void operator delete(void* p, size_t n) noexcept
{
    if (recordaddrs  &&  isRecordedSize(n))
    {
        recordaddrs = false;
        set<void*>::iterator it = addrs.find(p);
        if (it != addrs.end())
            addrs.erase(it);
            recordaddrs = true;
            }
    operator delete(p);
}
#else
void operator delete(void* p) noexcept
{
    if (recordaddrs)
    {
        recordaddrs = false;
        set<void*>::iterator it = addrs.find(p);
        if (it != addrs.end())
            addrs.erase(it);
            recordaddrs = true;
            }
    free(p);
}
#endif

bool recommendMove(const Arena& a, int r, int c, int& bestDir);

void testone(int n)
{
    streambuf_switcher sso(cout, cerr);
    
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            int k;
            for (k = 0; k < 300; k++)
            {
                Arena a(1, 20);
                a.addPlayer(1, 3);
                Rat r(&a, 1, 18);
                assert(r.row() == 1  &&  r.col() == 18);
                r.move(); assert(r.row() == 1);
                if (r.col() != 19)
                {
                    assert(r.col() == 17  ||  r.col() == 18);
                    continue;
                }
                r.move(); assert(r.row() == 1);
                if (r.col() == 20)
                    break;
                assert(r.col() == 18  ||  r.col() == 19);
            }
            assert(k < 300);
        } break; case  2: {
            int k;
            for (k = 0; k < 600; k++)
            {
                Arena a(1, 20);
                a.addPlayer(1, 3);
                Rat r(&a, 1, 19);
                assert(r.row() == 1  &&  r.col() == 19);
                r.move(); assert(r.row() == 1);
                if (r.col() != 19)
                {
                    assert(r.col() == 18  ||  r.col() == 20);
                    continue;
                }
                r.move(); assert(r.row() == 1);
                if (r.col() != 19)
                {
                    assert(r.col() == 18  ||  r.col() == 20);
                    continue;
                }
                r.move(); assert(r.row() == 1);
                if (r.col() != 19)
                {
                    assert(r.col() == 18  ||  r.col() == 20);
                    continue;
                }
                r.move(); assert(r.row() == 1);
                if (r.col() != 19)
                {
                    assert(r.col() == 18  ||  r.col() == 20);
                    continue;
                }
                r.move(); assert(r.row() == 1);
                if (r.col() == 18  ||  r.col() == 20)
                    break;
                assert(r.col() == 19);
            }
            assert(k < 600);
        } break; case  3: {
            int k;
            for (k = 0; k < 600; k++)
            {
                Arena a(20, 1);
                a.addPlayer(3, 1);
                Rat r(&a, 19, 1);
                assert(r.row() == 19  &&  r.col() == 1);
                r.move(); assert(r.col() == 1);
                if (r.row() != 19)
                {
                    assert(r.row() == 18  ||  r.row() == 20);
                    continue;
                }
                r.move(); assert(r.col() == 1);
                if (r.row() != 19)
                {
                    assert(r.row() == 18  ||  r.row() == 20);
                    continue;
                }
                r.move(); assert(r.col() == 1);
                if (r.row() != 19)
                {
                    assert(r.row() == 18  ||  r.row() == 20);
                    continue;
                }
                r.move(); assert(r.col() == 1);
                if (r.row() != 19)
                {
                    assert(r.row() == 18  ||  r.row() == 20);
                    continue;
                }
                r.move(); assert(r.col() == 1);
                if (r.row() == 18  ||  r.row() == 20)
                    break;
                assert(r.row() == 19);
            }
            assert(k < 600);
        } break; case  4: {
            Arena a(10,20);
            a.addPlayer(9, 19);
            for (int r = 5-2; r <= 5+2; r++)
                for (int c = 10-2; c <= 10+2; c++)
                    a.setCellStatus(r, c, HAS_POISON);
            Rat r(&a, 5, 10);
            r.move();
            assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
                   (r.col() == 10  &&  abs(r.row() - 5) == 1));
            int oldr = r.row();
            int oldc = r.col();
            r.move();
            assert(r.row() == oldr  &&  r.col() == oldc);
            r.move();
            assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
                   (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
        } break; case  5: {
            Arena a(10,20);
            a.addPlayer(9, 19);
            for (int r = 5-2; r <= 5+2; r++)
                for (int c = 10-2; c <= 10+2; c++)
                    if (r != 5  ||  c != 10)
                        a.setCellStatus(r, c, HAS_POISON);
            Rat r(&a, 5, 10);
            assert(!r.isDead());
            r.move();
            assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
                   (r.col() == 10  &&  abs(r.row() - 5) == 1));
            int oldr = r.row();
            int oldc = r.col();
            assert(!r.isDead());
            a.setCellStatus(5, 10, HAS_POISON);
            r.move();
            assert(r.row() == oldr  &&  r.col() == oldc);
            assert(!r.isDead());
            r.move();
            assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
                   (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
            assert(r.isDead());
        } break; case  6: {
            Arena a(10,20);
            a.addPlayer(9, 19);
            a.setCellStatus(4, 10, HAS_POISON);
            a.setCellStatus(6, 10, HAS_POISON);
            a.setCellStatus(5, 9, HAS_POISON);
            a.setCellStatus(5, 11, HAS_POISON);
            Rat r(&a, 5, 10);
            r.move();
            assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
                   (r.col() == 10  &&  abs(r.row() - 5) == 1));
            int oldr = r.row();
            int oldc = r.col();
            r.move();
            assert(r.row() == oldr  &&  r.col() == oldc);
            r.move();
            assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
                   (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
            oldr = r.row();
            oldc = r.col();
            r.move();
            assert(r.row() == oldr  &&  r.col() == oldc);
            a.setCellStatus(oldr-1, oldc, EMPTY);
            a.setCellStatus(oldr+1, oldc, EMPTY);
            a.setCellStatus(oldr, oldc-1, EMPTY);
            a.setCellStatus(oldr, oldc+1, EMPTY);
            r.move();
            assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
                   (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
        } break; case  7: {
            Arena a(1, 20);
            a.addPlayer(1, 3);
            Player* p = a.player();
            assert(p->row() == 1  &&  p->col() == 3);
            p->move(WEST); assert(p->row() == 1  &&  p->col() == 2);
            p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
        } break; case  8: {
            Arena a(1, 20);
            a.addPlayer(1, 3);
            Player* p = a.player();
            p->move(WEST); assert(p->row() == 1  &&  p->col() == 2);
            p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
            p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
            p->move(NORTH); assert(p->row() == 1  &&  p->col() == 1);
            p->move(SOUTH); assert(p->row() == 1  &&  p->col() == 1);
        } break; case  9: {
            Arena a(10, 20);
            a.addPlayer(3, 6);
            Player* p = a.player();
            assert( ! p->isDead());
            p->setDead();
            assert(p->isDead());
        } break; case 10: {
            Arena a(20, 1);
            a.addPlayer(1, 1);
            Player* p = a.player();
            assert(p->move(WEST).find(" stands") != string::npos);
            assert(p->move(EAST).find(" stands") != string::npos);
            assert(p->move(NORTH).find(" stands") != string::npos);
            assert(p->move(SOUTH).find(" south") != string::npos);
        } break; case 11: {
            Arena a(20, 1);
            a.addPlayer(1, 1);
            Player* p = a.player();
            a.addRat(2, 1);
            assert(p->move(SOUTH).find(" died") != string::npos);
        } break; case 12: {
            Arena a(20, 1);
            a.addPlayer(1, 1);
            Player* p = a.player();
            a.addRat(2, 1);
            assert(!p->isDead());
            p->move(SOUTH);
            assert(p->isDead());
        } break; case 13: {
            Arena a(6, 15);
            assert(a.rows() == 6  &&  a.cols() == 15);
        } break; case 14: {
            Arena a(10, 20);
            a.addPlayer(3, 6);
            a.addRat(7, 5);
            assert(a.numberOfRatsAt(7, 5) == 1  &&  a.ratCount() == 1);
        } break; case 15: {
            Arena a(10, 20);
            a.addPlayer(3, 6);
            a.addRat(7, 5);
            a.addRat(4, 7);
            a.addRat(7, 5);
            assert(a.numberOfRatsAt(7, 5) == 2  &&  a.ratCount() == 3);
        } break; case 16: {
            Arena a(1, 20);
            a.addPlayer(1, 8);
            a.addRat(1, 1);
            a.setCellStatus(1, 2, HAS_POISON);
            a.setCellStatus(1, 3, HAS_POISON);
            a.addRat(1, 16);
            a.setCellStatus(1, 14, HAS_POISON);
            a.setCellStatus(1, 15, HAS_POISON);
            a.setCellStatus(1, 17, HAS_POISON);
            a.setCellStatus(1, 18, HAS_POISON);
            assert(a.ratCount() == 2);
            int k;
            for (k = 0; k < 200; k++)
            {
                a.moveRats();
                int nb1 = (a.getCellStatus(1, 2) == HAS_POISON) +
                (a.getCellStatus(1, 3) == HAS_POISON);
                int nb2 = (a.getCellStatus(1, 14) == HAS_POISON) +
                (a.getCellStatus(1, 15) == HAS_POISON) +
                (a.getCellStatus(1, 17) == HAS_POISON) +
                (a.getCellStatus(1, 18) == HAS_POISON);
                assert(a.ratCount() == (nb1 > 0) + (nb2 > 2));
                if (a.ratCount() == 0)
                    break;
            }
            assert(k < 200);
        } break; case 17: {
            Arena a(1, 3);
            a.addPlayer(1, 1);
            Player* p = a.player();
            for (int j = 0; j < 10; j++)
                a.addRat(1, 3);
            assert(!p->isDead());
            a.moveRats();
            int k;
            for (k = 0; k < 100; k++)
            {
                assert(!p->isDead());
                a.moveRats();
                if (a.numberOfRatsAt(1, 1) > 0)
                {
                    assert(p->isDead());
                    break;
                }
            }
            assert(k < 100);
        } break; case 18: {
            ostringstream oss;
            streambuf_switcher sso2(cout, oss);
            Arena a(2, 3);
            a.addPlayer(2, 3);
            a.addRat(2, 1);
            a.addRat(2, 1);
            a.addRat(2, 2);
            a.display("");
            assert(oss.str().find("2R@") != string::npos);
        } break; case 19: {
            ostringstream oss;
            streambuf_switcher sso2(cout, oss);
            Arena a(2, 3);
            a.addPlayer(2, 3);
            for (int k = 1; k <= 20; k++)
                a.addRat(2, 1);
            a.display("");
            assert(oss.str().find("9.@") != string::npos);
        } break; case 20: {
            recordaddrs = true;
            int n = addrs.size();
            {
                Arena a(20, 20);
                for (int r = 1; r <= 5; r++)
                    for (int c = 11; c <= 20; c++)
                        a.setCellStatus(r, c, HAS_POISON);
                for (int r = 16; r <= 20; r++)
                    for (int c = 15; c <= 20; c++)
                        a.setCellStatus(r, c, HAS_POISON);
                a.addPlayer(19, 19);
                int n2 = addrs.size();
                a.setCellStatus(3, 13, EMPTY);
                a.setCellStatus(3, 18, EMPTY);
                a.addRat(3, 13);
                a.addRat(3, 18);
                for (int k = 0; k < 4; k++)
                {
                    a.addRat(1, 1);
                    a.addRat(1, 4);
                    a.addRat(4, 1);
                    a.addRat(4, 4);
                }
                assert(addrs.size() >= n2 + 18);
                a.moveRats();
                a.setCellStatus(3, 13, HAS_POISON);
                a.setCellStatus(3, 18, HAS_POISON);
                a.moveRats();
                a.moveRats();
                assert(a.ratCount() == 18-2);
                for (int k = a.ratCount(); k < MAXRATS; k++)
                    assert(a.addRat(1, 1));
                int j;
                for (j = 0; j < 1000  &&  a.ratCount() > 20; j++)
                {
                    for (int r = 1; r <= 20; r++)
                        for (int c = 1; c <= 20; c++)
                            if (a.numberOfRatsAt(r, c) == 0  &&  !(r == 19 && c == 19))
                                a.setCellStatus(r, c, HAS_POISON);
                    a.moveRats();
                }
                assert(j < 1000);
                a.setCellStatus(1, 1, EMPTY);
                for (int k = a.ratCount(); k < MAXRATS; k++)
                    assert(a.addRat(1, 1));
                assert(addrs.size() >= n2 + MAXRATS);
            }
            assert(addrs.size() == n);
            recordaddrs = false;
        } break; case 21: {
            Arena a(20, 20);
            a.addPlayer(19, 19);
            for (int r = 1; r < 19; r++)
                for (int c = 1; c < 19; c++)
                    if (r != 10  ||  c != 10)
                        a.setCellStatus(r, c, HAS_POISON);
            for (int k = 0; k < 100; k++)
                a.addRat(10, 10);
            assert(a.ratCount() == 100  &&  a.numberOfRatsAt(10, 10) == 100);
            int nr[1+20][1+20];
            a.moveRats();
            int tot = 0;
            for (int r = 1; r < 19; r++)
            {
                for (int c = 1; c < 19; c++)
                {
                    nr[r][c] = a.numberOfRatsAt(r, c);
                    tot += nr[r][c];
                    assert((r == 10  &&  c >= 9 && c <= 11) ||
                           (c == 10  &&  r >= 9 && r <= 11) ||
                           nr[r][c] == 0);
                }
            }
            assert(nr[10][10] == 0  &&  tot == a.ratCount());
            assert(nr[9][10] == 0  ||  a.getCellStatus(9, 10) == EMPTY);
            assert(nr[11][10] == 0  ||  a.getCellStatus(11, 10) == EMPTY);
            assert(nr[10][9] == 0  ||  a.getCellStatus(10, 9) == EMPTY);
            assert(nr[10][11] == 0  ||  a.getCellStatus(10, 11) == EMPTY);
            a.setCellStatus(10, 10, HAS_POISON);
            a.moveRats();
            assert(a.numberOfRatsAt(9, 10) == (nr[9][10] == 0 ? 0 : 1));
            assert(a.numberOfRatsAt(11, 10) == (nr[11][10] == 0 ? 0 : 1));
            assert(a.numberOfRatsAt(10, 9) == (nr[10][9] == 0 ? 0 : 1));
            assert(a.numberOfRatsAt(10, 11) == (nr[10][11] == 0 ? 0 : 1));
            for (int k = 0; k < 17; k++)
            {
                for (int r = 1; r < 19; r++)
                    for (int c = 1; c < 19; c++)
                        if (a.numberOfRatsAt(r, c) == 0)
                            a.setCellStatus(r, c, HAS_POISON);
                a.moveRats();
            }
            tot = 0;
            for (int r = 1; r < 19; r++)
                for (int c = 1; c < 19; c++)
                    tot += a.numberOfRatsAt(r, c);
            assert(a.ratCount() == tot  &&  tot < 100);
        } break; case 22: {
            Arena a(4, 2);
            a.addPlayer(1, 1);
            Player* p = a.player();
            a.addRat(4, 2);
            for (int k = 0; k < 10000 &&  ! a.player()->isDead()  &&
                 a.ratCount() != 0; k++)
            {
                int dir;
                if (recommendMove(a, p->row(), p->col(), dir))
                    p->move(dir);
                else
                    p->dropPoisonPellet();
                a.moveRats();
            }
            assert(! a.player()->isDead()  &&  a.ratCount() == 0);
        } break; case 23: {
            Arena a(10, 10);
            a.addPlayer(6, 6);
            a.addRat(5, 6);
            a.addRat(7, 6);
            a.addRat(6, 7);
            int dir;
            assert(recommendMove(a, 6, 6, dir)  &&  dir == WEST);
        } break; case 24: {
            Arena a(10, 10);
            a.addPlayer(6, 6);
            a.addRat(4, 6);
            a.addRat(5, 7);
            a.addRat(6, 8);
            a.addRat(7, 7);
            a.addRat(8, 6);
            a.addRat(7, 5);
            a.addRat(6, 4);
            a.addRat(5, 5);
            int dir;
            assert(!recommendMove(a, 6, 6, dir));
        } break; case 25: {
            Arena a(2, 3);
            a.addPlayer(1, 2);
            a.addRat(1, 1);
            for (int k = 0; k < 10; k++)
                a.addRat(2, 3);
            int dir;
            assert(!recommendMove(a, 1, 2, dir));
        } break; case 26: {
            Arena a(3, 2);
            a.addPlayer(3, 1);
            a.addRat(1, 1);
            for (int k = 0; k < 10; k++)
                a.addRat(3, 2);
            int dir;
            assert(recommendMove(a, 3, 1, dir)  &&  dir == NORTH);
        } break;
    }
}

int main()
{
    cout << "Enter test number (1-26): ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed!" << endl;
}

*/