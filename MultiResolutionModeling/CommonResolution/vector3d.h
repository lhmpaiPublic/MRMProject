/* 
 I am creating a class CVector3d which will be used for vector operation . I have overloaded all the basic functions for the required for vector operation . 
 There is no need for extra class , so no inheritance was necessary . 
 */ 
#ifndef CVector3d_H
#define CVector3d_H

 #include<iostream> 
 #include<math.h> 
 #include<assert.h> 
 using namespace std; 
 typedef float f; 
 class CVector3d 
 { 
 public: 
     f x,y,z; 
     CVector3d()  //constructor 
     { 
         x=0; 
         y=0; 
         z=0; 
     } 
 

     CVector3d(f x1,f y1,f z1=0)     //initializing object with values. 
     { 
         x=x1; 
         y=y1; 
         z=z1; 
     } 
     CVector3d(const CVector3d &vec);    //copy constructor 
     CVector3d operator+(const CVector3d &vec);    //addition 
     CVector3d &operator+=(const CVector3d &vec);  ////assigning new result to the vector 
     CVector3d operator-(const CVector3d &vec);    //substraction 
     CVector3d &operator-=(const CVector3d &vec);  //assigning new result to the vector 
     CVector3d operator*(f value);    //multiplication 
     CVector3d &operator*=(f value);  //assigning new result to the vector. 
     CVector3d operator/(f value);    //division 
     CVector3d &operator/=(f value);  //assigning new result to the vector 
     CVector3d &operator=(const CVector3d &vec); 
     f dot_product(const CVector3d &vec); //scalar dot_product 
     CVector3d cross_product(const CVector3d &vec);    //cross_product 
     f magnitude();  //magnitude of the vector 
     CVector3d normalization();   //nor,malized vector 
     f square(); //gives square of the vector 
 

     f distance(const CVector3d &vec);    //gives distance between two vectors 
     f show_X(); //return x 
     f show_Y(); //return y 
     f show_Z(); //return z 
     void disp();    //display value of vectors 
 }; 
 
#endif // CVector3d_H