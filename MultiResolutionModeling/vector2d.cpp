
// CVector2d.cpp
//

#include "stdafx.h"

#include "vector2d.h"
#include <cmath>

CVector2d::CVector2d()
{
    x = 0.0;
    y = 0.0;
}

CVector2d::CVector2d(float sourceX, float sourceY)
{
    x = sourceX;
    y = sourceY;
}

CVector2d CVector2d::operator+(const CVector2d &v) const
{
    return CVector2d(x+v.x, y+v.y);
}

CVector2d CVector2d::operator-(const CVector2d &v) const
{
    return CVector2d(x-v.x, y-v.y);
}

CVector2d CVector2d::operator*(const CVector2d &v) const
{
    return CVector2d(x*v.x, y*v.y);
}

CVector2d CVector2d::operator/(const CVector2d &v) const
{
    return CVector2d(x/v.x, y/v.y);
}

bool CVector2d::operator==(const CVector2d &v) const
{
    return ((x == v.x) && (y == v.y));
}

bool CVector2d::operator>(const CVector2d &v) const
{
    return (x*x + y*y) > (v.x*v.x + v.y*v.y);
}

bool CVector2d::operator<(const CVector2d &v) const
{
    return (x*x + y*y) < (v.x*v.x + v.y*v.y);
}

bool CVector2d::operator>=(const CVector2d &v) const
{
    return (x*x + y*y) > (v.x*v.x + v.y*v.y) ||
           (x*x + y*y) == (v.x*v.x + v.y*v.y);
}

bool CVector2d::operator<=(const CVector2d &v) const
{
    return (x*x + y*y) < (v.x*v.x + v.y*v.y) ||
           (x*x + y*y) == (v.x*v.x + v.y*v.y);
}
CVector2d CVector2d::operator-() const
{
    return CVector2d(-x, -y);
}

CVector2d CVector2d::operator*(const float& scalar) const
{
    return CVector2d(x*scalar, y*scalar);
}

CVector2d CVector2d::operator/(const float& scalar) const
{
    return CVector2d(x/scalar, y/scalar);
}

float CVector2d::DotProduct(const CVector2d &a, const CVector2d &b)
{
    return ((a.x * b.x) + (a.y * b.y));
}

float CVector2d::CrossProduct(const CVector2d &a, const CVector2d &b)
{
    return ((a.x * b.y) - (a.y * b.x));
}

float CVector2d::Magnitude(const CVector2d &v)
{
    return sqrt((v.x * v.x) + (v.y * v.y));
}

CVector2d CVector2d::Normal(const CVector2d &v)
{
    float magnitude = Magnitude(v);
    return CVector2d(v.x / magnitude, v.y / magnitude);
}

CVector2d CVector2d::Perpendicular(const CVector2d &v)
{
    return CVector2d(v.y, -v.x);
}

bool CVector2d::Intersect(const CVector2d &aa, const CVector2d &ab, const CVector2d &ba, const CVector2d &bb)
{
    CVector2d p = aa;
    CVector2d r = ab - aa;
    CVector2d q = ba;
    CVector2d s = bb - ba;

    float t = CrossProduct((q - p), s) / CrossProduct(r, s);
    float u = CrossProduct((q - p), r) / CrossProduct(r, s);

    return (0.0 <= t && t <= 1.0) &&
           (0.0 <= u && u <= 1.0);
}

CVector2d CVector2d::GetIntersect(const CVector2d &aa, const CVector2d &ab, const CVector2d &ba, const CVector2d &bb)
{
    float pX = (aa.x*ab.y - aa.y*ab.x)*(ba.x - bb.x) -
               (ba.x*bb.y - ba.y*bb.x)*(aa.x - ab.x);
    float pY = (aa.x*ab.y - aa.y*ab.x)*(ba.y - bb.y) -
               (ba.x*bb.y - ba.y*bb.x)*(aa.y - ab.y);
    float denominator = (aa.x - ab.x)*(ba.y - bb.y) -
                        (aa.y - ab.y)*(ba.x - bb.x);

    return CVector2d(pX / denominator, pY / denominator);
}