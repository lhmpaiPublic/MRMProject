#pragma once


#include "UnitSize.h"
class CResolutionChange
{
public:
	CResolutionChange();
	~CResolutionChange();
public:
	//부대 진행 방향 Type 정의
	enum DIRECTIONTYPE
	{
		NONE_DIRECTION = 0,
		N_DIRECTION,
		NE_DIRECTION,
		E_DIRECTION,
		SE_DIRECTION,
		S_DIRECTION,
		SW_DIRECTION,
		W_DIRECTION,
		NW_DIRECTION
	};

	//위치 계산 Type 정의
	enum CALCPOSITIONTYPE
	{
		CALC_POS0 = 0,
		CALC_POS1,
		CALC_POS2,
		CALC_POS3,
		CALC_POS4,
		CALC_POS5,
		CALC_POS6,
		CALC_POS7,
		CALC_POS8,
		CALC_POS9,
	};

	//SIZE VECTOR Type 정의
	enum SIZEVECTORTYPE
	{
		SIZEVEC_WIDTH = 0,
		SIZEVEC_HIGHT,
	};

	//Deployment Type 정의
	enum DEPLOYMENTTYPE
	{
		DEP_NONE = 0,
		DEP_INVERTEDTRIANGLE = 1,	// 역삼각대
		DEP_TRIANGLE,				// 삼각대(원형)
		DEP_LINE,					// 횡대
		DEP_COLUMN					// 종대
	};

	//분해 요소 Type 정의
	enum DISAGGREGATEDTYPE
	{
		DISAGG_NUM1 = 0,
		DISAGG_NUM2,
		DISAGG_NUM3,
		DISAGG_NUM4
	};

	struct inputPosVal
	{
		CVector2d parent;
		DIRECTIONTYPE dir;
		DEPLOYMENTTYPE dep;
		CUnitSize::InputVal unitSizeVal;
	};
private:
	CUnitSize *unitSizeVal;
public:	

	void changeAggregated();

	void changeDisaggregated();

	void changeDisaggregatedPosition(inputPosVal val);

	CVector2d frontDirection(DIRECTIONTYPE dir);

	CVector2d crossDirection(CVector2d frontNorDir);

	CVector2d calcPosition(CALCPOSITIONTYPE calcType, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);

	vector<CVector2d> deploymentPosition(DEPLOYMENTTYPE deployment, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);

	CVector2d changeAggregatedPosition(vector<CVector2d> posList);
};