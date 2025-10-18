#ifndef VECPOINT_H
#define VECPOINT_H
//ÁÂÇ¥ °´Ã¼
typedef struct _S2Point
{
	int posX;
	int posY;

	_S2Point():posX(0),posY(0)
	{
	}
	_S2Point(int valX, int valY):posX(valX),posY(valY)
	{
	}
	_S2Point &operator=(const _S2Point &v) 
	{ 
		posX = v.posX;
		posY = v.posY;
		return *this; 
	}
	_S2Point operator+(const _S2Point &v) const
	{
		return _S2Point(posX+v.posX, posY+v.posY);
	}

	_S2Point operator-(const _S2Point &v) const
	{
		return _S2Point(posX-v.posX, posY-v.posY);
	}

	_S2Point operator*(const _S2Point &v) const
	{
		return _S2Point(posX*v.posX, posY*v.posY);
	}

	_S2Point operator/(const _S2Point &v) const
	{
		return _S2Point(posX/v.posX, posY/v.posY);
	}
	bool operator==(const _S2Point &v) const
	{
		return ((posX == v.posX) && (posY == v.posY));
	}

	bool operator>(const _S2Point &v) const
	{
		return ((posX > v.posX) && (posY < v.posY));
	}

	bool operator<(const _S2Point &v) const
	{
		return ((posX < v.posX) && (posY > v.posY));
	}

	bool operator>=(const _S2Point &v) const
	{
		return ((posX > v.posX) && (posY < v.posY)) ||
			((posX == v.posX) && (posY == v.posY));
	}

	bool operator<=(const _S2Point &v) const
	{
		return ((posX < v.posX) && (posY > v.posY)) ||
			((posX == v.posX) && (posY == v.posY));
	}

	_S2Point operator*(const int& scalar) const
	{
		return _S2Point(posX*scalar, posY*scalar);
	}

	_S2Point operator/(const int& scalar) const
	{
		return _S2Point(posX/scalar, posY/scalar);
	}

	_S2Point operator+(const int& scalar) const
	{
		return _S2Point(posX*scalar, posY*scalar);
	}

	_S2Point operator-(const int& scalar) const
	{
		return _S2Point(posX/scalar, posY/scalar);
	}

}S2Pos;

//ÁÂÇ¥ 4°³ ±¸¼º °´Ã¼(4°¢¿µ¿ª ÀúÀå °´Ã¼)
class CVecPoint4 {
public:
	enum POS
	{
		LT = 0,	
		RT = 1,
		LB = 2,				
		RB = 3,
		POS_SIZE
	};
	S2Pos posVal[POS_SIZE];
    //Constructor
    CVecPoint4();
	CVecPoint4(S2Pos lt, S2Pos lb, S2Pos rt, S2Pos rb);
    CVecPoint4(CVecPoint4&);

    CVecPoint4 operator+(const CVecPoint4&) const;
    CVecPoint4 operator-(const CVecPoint4&) const;
    CVecPoint4 operator*(const CVecPoint4&) const;
    CVecPoint4 operator/(const CVecPoint4&) const;
	CVecPoint4 &operator=(const CVecPoint4 &); 

    bool operator==(const CVecPoint4&) const;

    bool operator>(const CVecPoint4&) const;
    bool operator<(const CVecPoint4&) const;
    bool operator>=(const CVecPoint4&) const;
    bool operator<=(const CVecPoint4&) const;

    CVecPoint4 operator*(const int&) const;
    CVecPoint4 operator/(const int&) const;
	CVecPoint4 operator+(const int&) const;
	CVecPoint4 operator-(const int&) const;
};

typedef class CVecPoint4 CV4Pos;

//ÁÂÇ¥ 2°³ ±¸¼º °´Ã¼(¿µ¿ª ÀúÀå °´Ã¼)
class CVecPoint2 {
public:
	enum POS
	{
		LT = 0,	
		RB = 1,
		POS_SIZE
	};
	S2Pos posVal[POS_SIZE];
	//Constructor
	CVecPoint2();
	CVecPoint2(S2Pos lt, S2Pos rb);
	CVecPoint2(CVecPoint2&);

	CVecPoint2 operator+(const CVecPoint2&) const;
	CVecPoint2 operator-(const CVecPoint2&) const;
	CVecPoint2 operator*(const CVecPoint2&) const;
	CVecPoint2 operator/(const CVecPoint2&) const;
	CVecPoint2 &operator=(const CVecPoint2 &); 

	bool operator==(const CVecPoint2&) const;

	bool operator>(const CVecPoint2&) const;
	bool operator<(const CVecPoint2&) const;
	bool operator>=(const CVecPoint2&) const;
	bool operator<=(const CVecPoint2&) const;

	CVecPoint2 operator*(const int&) const;
	CVecPoint2 operator/(const int&) const;
	CVecPoint2 operator+(const int&) const;
	CVecPoint2 operator-(const int&) const;
};

typedef class CVecPoint2 CV2Pos;

#endif //VECPOINT_H