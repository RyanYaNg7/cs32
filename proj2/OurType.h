//
//  OurType.hpp
//  proj2
//
//  Created by 杨子鸣 on 5/2/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

//=========================== OurType.h ==============================
#ifndef OURTYPE_INCLUDED
#define OURTYPE_INCLUDED

struct OurType
{
    explicit OurType(int v = 0) : m_value(v) { m_count++; }
    OurType(const OurType& other) : m_value(other.m_value)
    { m_count++; m_asstcopycount++; }
    ~OurType() { m_count--; }
    OurType& operator=(const OurType& rhs)
    { m_value = rhs.m_value; m_asstcopycount++; return *this; }
    
    int m_value;
    static int m_count;
    static int m_asstcopycount;
};

inline
bool operator==(const OurType& lhs, const OurType& rhs)
{ return lhs.m_value == rhs.m_value; }

inline
bool operator<(const OurType& lhs, const OurType& rhs)
{ return lhs.m_value < rhs.m_value; }

inline
bool operator!=(const OurType& lhs, const OurType& rhs)
{ return ! (lhs == rhs); }

inline
bool operator<=(const OurType& lhs, const OurType& rhs)
{ return ! (rhs < lhs); }

inline
bool operator>=(const OurType& lhs, const OurType& rhs)
{ return ! (lhs < rhs); }

inline
bool operator>(const OurType& lhs, const OurType& rhs)
{ return rhs < lhs; }

inline
bool operator==(const OurType& lhs, int rhs)
{ return lhs.m_value == rhs; }

inline
bool operator!=(const OurType& lhs, int rhs)
{ return ! (lhs == rhs); }

#include <iostream>

inline
std::ostream& operator<<(std::ostream& lhs, const OurType& rhs)
{ return lhs << rhs.m_value; }

#endif // OURTYPE_INCLUDED