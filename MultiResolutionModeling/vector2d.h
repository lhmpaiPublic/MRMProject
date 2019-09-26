#ifndef CVector2d_H
#define CVector2d_H

#include <cfloat>
#include <climits>

/*The CVector2d class is an object consisting of simply an x and
  y value. Certain operators are overloaded to make it easier
  for vector math to be performed.*/

class CVector2d {
public:
    /*The x and y values are public to give easier access for
      outside funtions. Accessors and mutators are not really
      necessary*/
    float x;
    float y;

    //Constructor assigns the inputs to x and y.
    CVector2d();
    CVector2d(float, float);

    /*The following operators simply return CVector2ds that
      have operations performed on the relative (x, y) values*/
    CVector2d operator+(const CVector2d&) const;
    CVector2d operator-(const CVector2d&) const;
    CVector2d operator*(const CVector2d&) const;
    CVector2d operator/(const CVector2d&) const;

    //Check if the Vectors have the same values.
    bool operator==(const CVector2d&) const;

    /*Check which Vectors are closer or further from the
      origin.*/
    bool operator>(const CVector2d&) const;
    bool operator<(const CVector2d&) const;
    bool operator>=(const CVector2d&) const;
    bool operator<=(const CVector2d&) const;

    //Negate both the x and y values.
    CVector2d operator-() const;

    //Apply scalar operations.
    CVector2d operator*(const float&) const;
    CVector2d operator/(const float&) const;

    //Product functions
    static float DotProduct(const CVector2d&, const CVector2d&);
    static float CrossProduct(const CVector2d&, const CVector2d&);

    //Returns the length of the vector from the origin.
    static float Magnitude(const CVector2d&);

    //Return the unit vector of the input
    static CVector2d Normal(const CVector2d&);

    //Return a vector perpendicular to the left.
    static CVector2d Perpendicular(const CVector2d&);

    //Return true if two line segments intersect.
    static bool Intersect(const CVector2d&, const CVector2d&, const CVector2d&, const CVector2d&);

    //Return the point where two lines intersect.
    static CVector2d GetIntersect(const CVector2d&, const CVector2d&, const CVector2d&, const CVector2d&);
};

#endif