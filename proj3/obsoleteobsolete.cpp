//
//  obsoleteobsolete.cpp
//  proj3
//
//  Created by 杨子鸣 on 5/29/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

/*
 ability of good player when attacking:   .
 0. counting what kind of ships are left, accordign to this information, it try attack the point where the ship are most likely to appear.
 1. randomly attack the place
 2. if attacked on a ship segment and end up not destroyed, attack its neighbor position in order of possibility(how many '.' in certain direction related to what ship length are left).
 {
 check horizontal: if the 1st attacked position does not have a match of horizontal '.' length with ship length, go to vertical; else go on horizontally
 check left: if the 1st attacked position does not have a match of '.' length with ship length to the left, go to right; else, attack left:
 if hit, but not destroyed, keep attack on the left
 if hit and destroyed, go back to random
 if missed, go to right
 check right: if the 1st attacked position does not have a match of '.' length with ship length to the right, and we did not attack a segment furthur on the left, go to vertical; else, attack right:
 if hit, but not destroyed, keep attack
 if hit and destroyed, go back to random
 
 check vertical:
 check downwards: if there is not enough '.'s downward that match ship length, go to upward; else
 check upwards:////
 }
 {
 Then if hit, record the direction, attacking on the same line direction within distance of existing length,
 if missed, attack the other way;
 if hit but not destroyed, keep going
 if hit and destroyed, record the result and go back to random attack
 }
 */

Point GoodPlayer::recommendAttack()         //same as mediocrePlayer
{
    //TODO:
    
    //if state 1
    if (state == true)
    {
        if (isValid(PostConfirmHit))    // previous attack accitentally find a ship
        {
            cerr << "you could do something to attack a previously accidentally attacked ship, but you did not." << endl;
        }
        
        Point l = Point(randInt(10), randInt(10));
        while (attackBefore(l, prevAttack))
        {
            l = Point(randInt(10), randInt(10));
        }
        prevAttack.push_back(l);
        return l;
    }
    
    //if state 2
    else
    {
        if (!haveInitialed)
        {
            //the initial condition, the last to come to
            
            //pre left
            int leftAvailable = 0;
            for(int n = 1; isValid(Point(lastHit.r, lastHit.c-n)); n++)
            {
                if(!attackBefore(Point(lastHit.r, lastHit.c-n), prevAttack))
                {
                    leftAvailable++;
                }
                else
                    break;
            }
            
            //pre right
            int rightAvailable = 0;
            for(int n = 1; isValid(Point(lastHit.r, lastHit.c+n)); n++)
            {
                if(!attackBefore(Point(lastHit.r, lastHit.c+n), prevAttack))
                {
                    rightAvailable++;
                }
                else
                    break;
            }
            
            //pre up
            int upAvailable = 0;
            for(int n = 1; isValid(Point(lastHit.r-n, lastHit.c)); n++)
            {
                /*
                 vector<Point>::iterator p; // = find(prevAttack.begin(), prevAttack.end(), Point(lastHit.r-n, lastHit.c));
                 for (p = prevAttack.begin();p != prevAttack.end();p++)
                 {
                 if (p->r == lastHit.r-n &&  p->c == lastHit.c)
                 break;
                 }
                 if (p == prevAttack.end())
                 {
                 upAvailable++;
                 }
                 else
                 break;
                 */
                if(!attackBefore(Point(lastHit.r-n, lastHit.c), prevAttack))
                {
                    upAvailable++;
                }
                else
                    break;
            }
            
            //pre down
            int downAvailable = 0;
            for(int n = 1; isValid(Point(lastHit.r+n, lastHit.c)); n++)
            {
                if(!attackBefore(Point(lastHit.r+n, lastHit.c), prevAttack))
                {
                    downAvailable++;
                }
                else
                    break;
            }
            
            dir = direc(leftAvailable, rightAvailable, upAvailable, downAvailable);     //biggest availability first
            haveInitialed = true;
        }
        
        
        if (!directionCondirmed)
        {
            Point temp(-1,-1);
            while (!isValid(temp)  ||  attackBefore(temp, prevAttack))
            {
                switch (dir)
                {
                    case 'l':
                    {
                        Point tes = Point(lastHit.r, lastHit.c-1);
                        if (isValid(tes) &&  !attackBefore(tes, prevAttack))
                        {
                            temp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try another" << endl;
                            dir = 'r';
                            temp = Point(lastHit.r, lastHit.c+1);
                        }
                        
                    }
                        break;
                        
                    case 'r':
                    {
                        Point tes = Point(lastHit.r, lastHit.c+1);
                        if (isValid(tes) &&  !attackBefore(tes, prevAttack))
                        {
                            temp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try another" << endl;
                            dir = 'u';
                            temp = Point(lastHit.r-1, lastHit.c);
                        }
                        
                    }
                        break;
                        
                    case 'u':
                    {
                        Point tes = Point(lastHit.r-1, lastHit.c);
                        if (isValid(tes) &&  !attackBefore(tes, prevAttack))
                        {
                            temp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try another" << endl;
                            dir = 'd';
                            temp = Point(lastHit.r+1, lastHit.c);
                        }
                        
                    }
                        break;
                    case 'd':
                    {
                        Point tes = Point(lastHit.r+1, lastHit.c);
                        if (isValid(tes) &&  !attackBefore(tes, prevAttack))
                        {
                            temp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try the opposite" << endl;
                            dir = 'l';
                            temp = Point(lastHit.r, lastHit.c-1);
                        }
                    }
                        break;
                    default:
                        cerr << "direction is wrong" << endl;
                        break;
                }
                
            }
            
            
            prevAttack.push_back(temp);
            return temp;
        }
        
        else    //directionCondirmed
        {
            Point tmp(-1, -1);
            int timeTry = 0;
            
            while (!isValid(tmp)  ||  attackBefore(tmp, prevAttack))
            {
                switch (dir)
                {
                    case 'l':
                    {
                        Point tes = Point(PostConfirmHit.r, PostConfirmHit.c-1);
                        if (isValid(tes) &&  !attackBefore(tes, prevAttack))
                        {
                            tmp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try the opposite" << endl;
                            dir = 'r';
                            tmp = Point(lastHit.r, lastHit.c+1);
                        }
                    }
                        break;
                        
                    case 'r':
                    {
                        Point tes = Point(PostConfirmHit.r, PostConfirmHit.c+1);
                        if (isValid(tes) && !attackBefore(tes, prevAttack))
                        {
                            tmp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try the opposite" << endl;
                            dir = 'l';
                            tmp = Point(lastHit.r, lastHit.c-1);
                        }
                    }
                        break;
                    case 'u':
                    {
                        Point tes = Point(PostConfirmHit.r-1, PostConfirmHit.c);
                        if (isValid(tes) && !attackBefore(tes, prevAttack))
                        {
                            tmp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try the opposite" << endl;
                            dir = 'd';
                            tmp = Point(lastHit.r+1, lastHit.c);
                            
                        }
                    }
                        break;
                    case 'd':
                    {
                        Point tes = Point(PostConfirmHit.r+1, PostConfirmHit.c);
                        if (isValid(tes) && !attackBefore(tes, prevAttack))
                        {
                            tmp = tes;
                        }
                        else
                        {
                            cerr << "this direction comes to an end, try the opposite" << endl;
                            dir = 'u';
                            tmp = Point(lastHit.r-1, lastHit.c);
                        }
                    }
                        break;
                    default:
                        cerr << "direction is wrong" << endl;
                        break;
                }
                timeTry++;
                if (timeTry == 4)
                {
                    cerr << "we might hit another ship, store that position and then go back to the previous track" << endl;
                    directionCondirmed = false;
                    int poi = 0;
                    while (!isValid(tmp)  ||  attackBefore(tmp, prevAttack))
                    {
                        switch (dir)
                        {
                            case 'l':
                            {
                                dir = 'r';
                                tmp = Point(lastHit.r, lastHit.c+1);
                            }
                                break;
                                
                            case 'r':
                            {
                                dir = 'u';
                                tmp = Point(lastHit.r-1, lastHit.c);
                            }
                                break;
                                
                            case 'u':
                            {
                                dir = 'd';
                                tmp = Point(lastHit.r+1, lastHit.c);
                            }
                                break;
                            case 'd':
                            {
                                dir = 'l';
                                tmp = Point(lastHit.r, lastHit.c-1);
                            }
                                break;
                            default:
                                cerr << "direction is wrong" << endl;
                                break;
                        }
                        poi++;
                        if (poi == 5)
                        {
                            ////////
                            toState1();
                            Point l = Point(randInt(10), randInt(10));
                            while (attackBefore(l, prevAttack))
                            {
                                l = Point(randInt(10), randInt(10));
                            }
                            prevAttack.push_back(l);
                            return l;
                        }
                    }
                    prevAttack.push_back(tmp);
                    return tmp;
                }
            }
            prevAttack.push_back(tmp);
            return tmp;
        }
    }
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    if (state)  //if in state 1
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit || shipDestroyed)   //missed OR destroyed
            return;
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            lastHit = p;
            toState2();
        }
    }
    else    //in state 2
    {
        if (!validShot)
        {
            cerr << "invalid shot, do not record!" << endl;
            return;
        }
        if (!shotHit)   //missed
        {
            if (directionCondirmed)
            {
                //changed direction
                cerr << "changed the direction of attack to the opposite" << endl;
                PostConfirmHit = lastHit;
                switch (dir)
                {
                    case 'l':
                        dir = 'r';
                        break;
                    case 'r':
                        dir = 'l';
                        break;
                    case 'u':
                        dir = 'd';
                        break;
                    case 'd':
                        dir = 'u';
                        break;
                    default:
                        cerr << "how can you miss without a direction" <<endl;
                        break;
                }
            }
            else    //direction has not been confirmed!
            {
                cerr << "trying another direction ! because direction has not been confirmed" << endl;
                switch (dir)
                {
                    case 'l':
                        dir = 'r';
                        break;
                    case 'r':
                        dir = 'u';
                        break;
                    case 'u':
                        dir = 'd';
                        break;
                    case 'd':
                        dir = 'l';
                        break;
                    default:
                        cerr << "how can you miss without a direction" <<endl;
                        break;
                }
            }
            return;
        }
        if (shotHit && !shipDestroyed)  //hit but not destroyed
        {
            PostConfirmHit = p;
            //stay in state two, keep hitting
            directionCondirmed = true;
            return;
        }
        if (shotHit && shipDestroyed)   //hit and destroyed
        {
            PostConfirmHit = Point(-1, -1);
            toState1();
        }
    }
    
}














bool hh;
vector<Ship>::iterator p;
for (p = ships.begin(); p != ships.end(); p++)
{
    if (p->shiplength == (left+right+1))    //the length of such ship exist
        break;
}
if (p == ships.end())   //did not find
{
    hh = true;  //horizontally no ship
}
else
hh = false; //found

bool vv;
for (p = ships.begin(); p != ships.end(); p++)
{
    if (p->shiplength == (up+down+1))    //the length of such ship exist
        break;
}
if (p == ships.end())   //did not find
{
    vv = true;  //horizontally no ship
}
else
vv = false; //found





75time     81.6%

50time     79.5%

25time     81.5%


