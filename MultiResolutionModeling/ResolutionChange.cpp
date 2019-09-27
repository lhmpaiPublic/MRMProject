// ResolutionChange.cpp
//

#include "stdafx.h"
#include "ResolutionChange.h"
#include "UnitSize.h"


CResolutionChange::CResolutionChange()
{
	unitSizeVal = new CUnitSize();
	unitSizeVal->loadCSVFile("UnitSizeInfo.csv");
}
CResolutionChange::~CResolutionChange()
{

}

void CResolutionChange::changeAggregated()
{

}

void CResolutionChange::changeDisaggregated()
{

}

void CResolutionChange::changeDisaggregatedPosition(inputPosVal val)
{
	//지향방향 노말 벡터
	CVector2d front = frontDirection(val.dir);
	//직각 y 방향 벡터
	CVector2d cross = crossDirection(front);
	//부대 반경
	vector<int> sizeUnit = unitSizeVal->unitZoneSize(val.unitSizeVal);
	//최종 분해 요소 값
	vector<CVector2d> vecHiData = deploymentPosition(val.dep, val.parent, front, cross, sizeUnit);
}

CVector2d CResolutionChange::frontDirection(DIRECTIONTYPE dir)
{
	CVector2d vecVal(0,1);
	switch (dir)
	{
	case N_DIRECTION:		// 북
		vecVal = CVector2d(0, 1);
		break;
	case NE_DIRECTION:		// 북동
		vecVal = CVector2d(1, 1);
		break;
	case E_DIRECTION:		// 동
		vecVal = CVector2d(1, 0);
		break;
	case SE_DIRECTION:		// 남동
		vecVal = CVector2d(1, -1);
		break;
	case S_DIRECTION:		// 남
		vecVal = CVector2d(0, -1);
		break;
	case SW_DIRECTION:		// 남서
		vecVal = CVector2d(-1, -1);
		break;
	case W_DIRECTION:		// 서
		vecVal = CVector2d(-1, 0);
		break;
	case NW_DIRECTION:		// 북서
	default:
		vecVal = CVector2d(-1, 1);
		break;
	}
	vecVal = CVector2d::Normal(vecVal);
	return vecVal;
}

CVector2d CResolutionChange::crossDirection(CVector2d frontNorDir)
{
	CVector3d directionFront3D(frontNorDir.x, frontNorDir.y, 0);
	CVector3d directionTop3D(0, 0, 1);
	CVector3d directionRight3D = directionFront3D.cross_product(directionTop3D);

	CVector2d vecVal(directionRight3D.x, directionRight3D.y);
	vecVal = CVector2d::Normal(vecVal);
	return vecVal;
}

CVector2d CResolutionChange::calcPosition(CALCPOSITIONTYPE calcType, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit)
{
	CVector2d vecVal(parent.x,parent.y);
	switch (calcType)
	{
	case CALC_POS0:		//1
		vecVal = parent + cross*(-(sizeUnit[SIZEVEC_WIDTH] * 3.0f / 8.0f)) + front*(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f);
		break;
	case CALC_POS1:		// 2
		vecVal = parent + cross*(-(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f)) + front*(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f);
		break;
	case CALC_POS2:		// 3
		vecVal = parent + front*(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f);
		break;
	case CALC_POS3:		// 4
		vecVal = parent + cross*(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f) + front*(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f);
		break;
	case CALC_POS4:		// 5
		vecVal = parent + cross*(sizeUnit[SIZEVEC_WIDTH] * 3.0f / 8.0f) + front*(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f);
		break;
	case CALC_POS5:		// 6
		vecVal = parent + cross*(-(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f));
		break;
	case CALC_POS6:		// 7
		vecVal = parent;
		break;
	case CALC_POS7:		// 8
		vecVal = parent + cross*(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f);
		break;
	case CALC_POS8:		// 8
		vecVal = parent + front*(-(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f));
		break;
	case CALC_POS9:		// 8
	default:
		vecVal = parent + front*(-(sizeUnit[SIZEVEC_HIGHT] * 3.0f / 8.0f));
		break;
	}
	return vecVal;
}

vector<CVector2d> CResolutionChange::deploymentPosition(DEPLOYMENTTYPE deployment, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit)
{
	vector<CVector2d> result;
	switch (deployment)
	{
	case DEP_INVERTEDTRIANGLE:		// 역삼각대
		result[DISAGG_NUM1] = calcPosition(CALC_POS1, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS3, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS9, parent, front, cross, sizeUnit);
		break;
	case DEP_TRIANGLE:		// 삼각대(원형)
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS5, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS7, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		break;
	case DEP_LINE:		// 횡대
		result[DISAGG_NUM1] = calcPosition(CALC_POS0, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS4, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		break;
	case DEP_COLUMN:		// 종대
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS6, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS9, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		break;
	default:					// 역삼각대
		result[DISAGG_NUM1] = calcPosition(CALC_POS1, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS3, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS9, parent, front, cross, sizeUnit);
		break;
	}
	return result;
}

CVector2d CResolutionChange::changeAggregatedPosition(vector<CVector2d> posList)
{
	CVector2d centroid(0.0f, 0.0f);

	int size = (int)posList.size();
	if (size >= 3)
	{
		double factor = 0;
		double centerX = 0;
		double centerY = 0;
		double area = 0;

		for (int firstIndex = 0; firstIndex < size; firstIndex++)
		{
			int secondIndex = (firstIndex + 1) % size;

			CVector2d firstPoint = posList[firstIndex];
			CVector2d secondPoint = posList[secondIndex];

			factor = ((firstPoint.x * secondPoint.y) - (secondPoint.x * firstPoint.y));

			area += factor;

			centerX += (firstPoint.x + secondPoint.x) * factor;
			centerY += (firstPoint.y + secondPoint.y) * factor;
		}

		if ((0.0 == area) == false)
		{
			area /= 2.0f;
			area *= 6.0f;

			factor = 1 / area;
			centerX *= factor;
			centerY *= factor;

			centroid.x = (float)centerX;
			centroid.y = (float)centerY;
		}
		else
		{
			centerX = 0.0;
			centerY = 0.0;

			for (int i = 0; i < size; ++i)
			{
				CVector2d point = posList[i];

				centerX += point.x;
				centerY += point.y;
			}

			centroid.x = (float)centerX/size;
			centroid.y = (float)centerY/size;
		}
	}
	else if (size > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			centroid = centroid + posList[i];
		}
		centroid = centroid/(float)size;
	}

	return centroid;
}