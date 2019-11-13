#ifndef VECPOINT4_H
#define VECPOINT4_H

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

#endif //VECPOINT4_H