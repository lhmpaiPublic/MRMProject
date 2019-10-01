// ResolutionChange.cpp
//

#include "stdafx.h"
#include "ResolutionChange.h"
#include "UnitSize.h"
#include "LogDlg.h"


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
	CLogDlg::initStream();
	CLogDlg::insertStream("전개대형 :");
	CLogDlg::insertStream(CStringA(strDeploymentType(inPosVal.dep)).GetBuffer());
	CLogDlg::addLogTextStream();

	CLogDlg::initStream();
	CLogDlg::insertStream("지향방향 :");
	CLogDlg::insertStream(CStringA(strDirectionType(inPosVal.dir)).GetBuffer());
	CLogDlg::addLogTextStream();

	CLogDlg::initStream();
	CLogDlg::insertStream("입력좌표 :");
	CLogDlg::insertStream((int)inPosVal.parent.x, '	');
	CLogDlg::insertStream((int)inPosVal.parent.y, '	');
	CLogDlg::addLogTextStream();

	CLogDlg::initStream();
	CLogDlg::insertStream("부대반경 입력 :");
	CLogDlg::insertStream(CStringA(CUnitSize::strMoveType(inPosVal.unitSizeVal.moveType)).GetBuffer(), '	');
	CLogDlg::insertStream(CStringA(CUnitSize::strForce(inPosVal.unitSizeVal.force)).GetBuffer(), '	');
	CLogDlg::insertStream(CStringA(CUnitSize::strCombatent(inPosVal.unitSizeVal.combat)).GetBuffer(), '	');
	if(inPosVal.unitSizeVal.combat != CUnitSize::ARTILLERY)
		CLogDlg::insertStream(CStringA(CUnitSize::strMilitarybranch(inPosVal.unitSizeVal.milVal.mil)).GetBuffer(), '	');
	else
		CLogDlg::insertStream(CStringA(CUnitSize::strMilitarybranch_AR(inPosVal.unitSizeVal.milVal.mil_AR)).GetBuffer(), '	');
	CLogDlg::addLogTextStream();


	vector<CVector2d> vecHiData = changeDisaggregatedPosition(inPosVal);

	CVector2d centroid = changeAggregatedPosition(vecHiData);
	vector<int> logVal;
	logVal.push_back((int)centroid.x);
	logVal.push_back((int)centroid.y);
	CLogDlg::initStream();
	CLogDlg::insertStream("Agg 좌표 :");
	CLogDlg::insertStreamVec(logVal,'	');
	CLogDlg::addLogTextStream();
}

vector<CVector2d> CResolutionChange::changeDisaggregatedPosition(inputPosVal val)
{
	//지향방향 노말 벡터
	CVector2d front = frontDirection(val.dir);
	//직각 y 방향 벡터
	CVector2d cross = crossDirection(front);
	//부대 반경
	vector<int> sizeUnit = unitSizeVal->unitZoneSize(val.unitSizeVal);
	CLogDlg::initStream();
	CLogDlg::insertStream("부대반경 :");
	CLogDlg::insertStreamVec(sizeUnit, '	');
	CLogDlg::addLogTextStream();

	//최종 분해 요소 값
	vector<CVector2d> vecHiData = deploymentPosition(val.dep, val.parent, front, cross, sizeUnit);
	vector<int> logVal;
	for(int i = 0; i < (int)vecHiData.size(); i++)
	{
		logVal.push_back((int)vecHiData[i].x);
		logVal.push_back((int)vecHiData[i].y);
	}
	CLogDlg::initStream();
	CLogDlg::insertStream("DisAgg 값 :");
	CLogDlg::insertStreamVec(logVal, '	');
	CLogDlg::addLogTextStream();

	return vecHiData;
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
	result.resize(DISAGG_SIZE);
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

CString CResolutionChange::strDirectionType(CResolutionChange::DIRECTIONTYPE em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case N_DIRECTION:strEm = "북";
		break;
	case NE_DIRECTION:strEm = "북동";
		break;
	case E_DIRECTION:strEm = "동";
		break;
	case SE_DIRECTION:strEm = "남동";
		break;
	case S_DIRECTION:strEm = "남";
		break;
	case SW_DIRECTION:strEm = "남서";
		break;
	case W_DIRECTION:strEm = "서";
		break;
	case NW_DIRECTION:strEm = "북서";
		break;
	default:
		break;
	}
	return strEm;
}

CResolutionChange::DIRECTIONTYPE CResolutionChange::emDirectionType(int selNum)
{
	CResolutionChange::DIRECTIONTYPE em = NONE_DIRECTION;
	switch (selNum)
	{
	case 0: em = N_DIRECTION;
		break;
	case 1: em = NE_DIRECTION;
		break;
	case 2: em = E_DIRECTION;
		break;
	case 3: em = SE_DIRECTION;
		break;
	case 4: em = S_DIRECTION;
		break;
	case 5: em = SW_DIRECTION;
		break;
	case 6: em = W_DIRECTION;
		break;
	case 7: em = NW_DIRECTION;
		break;
	default:
		break;
	}
	return em;
}

CString CResolutionChange::strDeploymentType(CResolutionChange::DEPLOYMENTTYPE em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case DEP_INVERTEDTRIANGLE:strEm = "역삼각대";
		break;
	case DEP_TRIANGLE:strEm = "삼각대(원형)";
		break;
	case DEP_LINE:strEm = "횡대";
		break;
	case DEP_COLUMN:strEm = "종대";
		break;
	default:
		break;
	}
	return strEm;
}

CResolutionChange::DEPLOYMENTTYPE CResolutionChange::emDeploymentType(int selNum)
{
	CResolutionChange::DEPLOYMENTTYPE em = DEP_NONE;
	switch (selNum)
	{
	case 0: em = DEP_INVERTEDTRIANGLE;
		break;
	case 1: em = DEP_TRIANGLE;
		break;
	case 2: em = DEP_LINE;
		break;
	case 3: em = DEP_COLUMN;
		break;
	default:
		break;
	}
	return em;
}

void CResolutionChange::setParentPos(CVector2d parentPos)
{
	inPosVal.parent = parentPos;
}

void CResolutionChange::setDirectionType(DIRECTIONTYPE em)
{
	inPosVal.dir = em;
}

void CResolutionChange::setDeploymentType(DEPLOYMENTTYPE em)
{
	inPosVal.dep = em;
}

void CResolutionChange::setMoveType(CUnitSize::MOVETYPE em)
{
	inPosVal.unitSizeVal.moveType = em;
}

void CResolutionChange::setForce(CUnitSize::FORCE em)
{
	inPosVal.unitSizeVal.force = em;
}

void CResolutionChange::setCombatent(CUnitSize::COMBATANT em)
{
	inPosVal.unitSizeVal.combat = em;
}

void CResolutionChange::setMilitarybranch(CUnitSize::MILITARYBRANCH em)
{
	inPosVal.unitSizeVal.milVal.mil = em;
}

void CResolutionChange::setMilitarybranch_AR(CUnitSize::MILITARYBRANCH_AR em)
{
	inPosVal.unitSizeVal.milVal.mil_AR = em;
}