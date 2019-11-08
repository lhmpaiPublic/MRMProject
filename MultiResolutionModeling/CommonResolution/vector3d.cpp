
// CVector3d.cpp
//

#include "stdafx.h"
#include "vector3d.h"

 CVector3d::CVector3d(const CVector3d &vec) 
 { 
     x=vec.x; 
     y=vec.y; 
     z=vec.z; 
 } 
 

 //addition 
 

 CVector3d CVector3d ::operator+(const CVector3d &vec) 
 { 
     return CVector3d(x+vec.x,y+vec.y,z+vec.z); 
 } 
 

 CVector3d &CVector3d ::operator+=(const CVector3d &vec) 
 { 
     x+=vec.x; 
     y+=vec.y; 
     z+=vec.z; 
     return *this; 
 } 
 //substraction// 
 CVector3d CVector3d ::operator-(const CVector3d &vec) 
 { 
     return CVector3d(x-vec.x,y-vec.y,z-vec.z); 
 } 
 

 CVector3d &CVector3d::operator-=(const CVector3d &vec) 
 { 
     x-=vec.x; 
     y-=vec.y; 
     z-=vec.z; 
     return *this; 
 } 
 

 //scalar multiplication 
 

 CVector3d CVector3d ::operator*(f value) 
 { 
     return CVector3d(x*value,y*value,z*value); 
 } 
 

 

 

 CVector3d &CVector3d::operator*=(f value) 
 { 
     x*=value; 
     y*=value; 
     z*=value; 
     return *this; 
 } 
 

 //scalar division 
 CVector3d CVector3d ::operator/(f value) 
 { 
     assert(value!=0); 
     return CVector3d(x/value,y/value,z/value); 
 } 
 

 CVector3d &CVector3d ::operator/=(f value) 
 { 
     assert(value!=0); 
     x/=value; 
     y/=value; 
     z/=value; 
     return *this; 
 } 
 

 

 CVector3d &CVector3d::operator=(const CVector3d &vec) 
 { 
     x=vec.x; 
     y=vec.y; 
     z=vec.z; 
     return *this; 
 } 
 

 //Dot product 
 f CVector3d::dot_product(const CVector3d &vec) 
 { 
     return x*vec.x+vec.y*y+vec.z*z; 
 } 
 

 //cross product 
 CVector3d CVector3d ::cross_product(const CVector3d &vec) 
 { 
     f ni=y*vec.z-z*vec.y; 
     f nj=z*vec.x-x*vec.z; 
     f nk=x*vec.y-y*vec.x; 
     return CVector3d(ni,nj,nk); 
 } 
 

 f CVector3d::magnitude() 
 { 
     return sqrt(square()); 
 } 
 

 f CVector3d::square() 
 { 
     return x*x+y*y+z*z; 
 } 
 

 CVector3d CVector3d:: normalization() 
 { 
     assert(magnitude()!=0); 
     *this/=magnitude(); 
     return *this; 
 } 
 

 f CVector3d::distance(const CVector3d &vec) 
 { 
     CVector3d dist=*this-vec; 
     return dist.magnitude(); 
 } 
 

 f CVector3d::show_X() 
 { 
     return x; 
 } 
 

 f CVector3d::show_Y() 
 { 
     return y; 
 } 
 

 f CVector3d::show_Z() 
 { 
     return z; 
 } 
 

 void CVector3d::disp() 
 { 
     cout<<x<<" "<<y<<" "<<z<<endl; 
 } 
 