
// CVecPoint4.cpp
//

#include "stdafx.h"
#include "vecPoint4.h"

CVecPoint4::CVecPoint4()
{
	posVal[LT] = S2Pos(0,0);
	posVal[RT] = S2Pos(0,0);
	posVal[LB] = S2Pos(0,0);
	posVal[RB] = S2Pos(0,0);
}

CVecPoint4::CVecPoint4(S2Pos lt, S2Pos lb, S2Pos rt, S2Pos rb)
{
	posVal[LT] = lt;
	posVal[RT] = lb;
	posVal[LB] = rt;
	posVal[RB] = rb;
}

CVecPoint4::CVecPoint4(CVecPoint4& val)
{
	posVal[LT] = val.posVal[LT];
	posVal[RT] = val.posVal[RT];
	posVal[LB] = val.posVal[LB];
	posVal[RB] = val.posVal[RB];
}

CVecPoint4 CVecPoint4::operator+(const CVecPoint4 &v) const
{
    return CVecPoint4(posVal[LT]+v.posVal[LT], posVal[RT]+v.posVal[RT], posVal[LB]+v.posVal[LB], posVal[RB]+v.posVal[RB]);
}

CVecPoint4 CVecPoint4::operator-(const CVecPoint4 &v) const
{
    return CVecPoint4(posVal[LT]-v.posVal[LT], posVal[RT]-v.posVal[RT], posVal[LB]-v.posVal[LB], posVal[RB]-v.posVal[RB]);
}

CVecPoint4 CVecPoint4::operator*(const CVecPoint4 &v) const
{
    return CVecPoint4(posVal[LT]*v.posVal[LT], posVal[RT]*v.posVal[RT], posVal[LB]*v.posVal[LB], posVal[RB]*v.posVal[RB]);
}

CVecPoint4 CVecPoint4::operator/(const CVecPoint4 &v) const
{
    return CVecPoint4(posVal[LT]/v.posVal[LT], posVal[RT]/v.posVal[RT], posVal[LB]/v.posVal[LB], posVal[RB]/v.posVal[RB]);
}

CVecPoint4 &CVecPoint4::operator=(const CVecPoint4 &v) 
{ 
	posVal[LT] = v.posVal[LT];
	posVal[RT] = v.posVal[RT];
	posVal[LB] = v.posVal[LB];
	posVal[RB] = v.posVal[RB];
	return *this; 
} 

bool CVecPoint4::operator==(const CVecPoint4 &v) const
{
    return ((posVal[LT] == v.posVal[LT]) && (posVal[RT] == v.posVal[RT]) && (posVal[LB] == v.posVal[LB]) && (posVal[RB] == v.posVal[RB]));
}

bool CVecPoint4::operator>(const CVecPoint4 &v) const
{
    return ((posVal[LT] > v.posVal[LT]) && (posVal[RT] > v.posVal[RT]) && (posVal[LB] > v.posVal[LB]) && (posVal[RB] > v.posVal[RB]));
}

bool CVecPoint4::operator<(const CVecPoint4 &v) const
{
    return ((posVal[LT] < v.posVal[LT]) && (posVal[RT] < v.posVal[RT]) && (posVal[LB] < v.posVal[LB]) && (posVal[RB] < v.posVal[RB]));
}

bool CVecPoint4::operator>=(const CVecPoint4 &v) const
{
    return ((posVal[LT] > v.posVal[LT]) && (posVal[RT] > v.posVal[RT]) && (posVal[LB] > v.posVal[LB]) && (posVal[RB] > v.posVal[RB])) ||
           ((posVal[LT] == v.posVal[LT]) && (posVal[RT] == v.posVal[RT]) && (posVal[LB] == v.posVal[LB]) && (posVal[RB] == v.posVal[RB]));
}

bool CVecPoint4::operator<=(const CVecPoint4 &v) const
{
    return ((posVal[LT] < v.posVal[LT]) && (posVal[RT] < v.posVal[RT]) && (posVal[LB] < v.posVal[LB]) && (posVal[RB] < v.posVal[RB]))||
           ((posVal[LT] == v.posVal[LT]) && (posVal[RT] == v.posVal[RT]) && (posVal[LB] == v.posVal[LB]) && (posVal[RB] == v.posVal[RB]));
}

CVecPoint4 CVecPoint4::operator*(const int& scalar) const
{
    return CVecPoint4(posVal[LT]*scalar, posVal[RT]*scalar, posVal[LB]*scalar, posVal[RB]*scalar);
}

CVecPoint4 CVecPoint4::operator/(const int& scalar) const
{
    return CVecPoint4(posVal[LT]/scalar, posVal[RT]/scalar, posVal[LB]/scalar, posVal[RB]/scalar);
}

CVecPoint4 CVecPoint4::operator+(const int& scalar) const
{
	return CVecPoint4(posVal[LT]+scalar, posVal[RT]+scalar, posVal[LB]+scalar, posVal[RB]+scalar);
}

CVecPoint4 CVecPoint4::operator-(const int& scalar) const
{
	return CVecPoint4(posVal[LT]-scalar, posVal[RT]-scalar, posVal[LB]-scalar, posVal[RB]-scalar);
}