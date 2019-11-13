// ResolutionChange.cpp
//

#include "stdafx.h"
#include "UnitSize.h"
#include <math.h>


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
	CLogDlg::AddLogText("<=================>");
	CLogDlg::AddLogText("<입력 값>");
	CLogDlg::initStream();
	CLogDlg::insertStream("전개대형 :");
	CLogDlg::insertStream(CStringA(strDeploymentType(inPosVal.unitSizeVal.combat, inPosVal.unitSizeVal.mil, inPosVal.dep)).GetBuffer());
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
	CLogDlg::insertStream("작전지역 입력 :");
	CLogDlg::insertStream(CStringA(CUnitSize::strMoveType(inPosVal.unitSizeVal.moveType)).GetBuffer(), '	');
	CLogDlg::insertStream(CStringA(CUnitSize::strForce(inPosVal.unitSizeVal.force)).GetBuffer(), '	');
	CLogDlg::insertStream(CStringA(CUnitSize::strCombatent(inPosVal.unitSizeVal.combat)).GetBuffer(), '	');
	CLogDlg::insertStream(CStringA(CUnitSize::strMilitarybranch(inPosVal.unitSizeVal.combat, inPosVal.unitSizeVal.mil)).GetBuffer(), '	');
	CLogDlg::addLogTextStream();

	CLogDlg::AddLogText("<====================>");
	CLogDlg::AddLogText("<출력 값>");

	vector<CVector2d> drawPosItem;
	int typeOp = 0;
	vector<CVector2d> areaPos;
	CString drawtext;
	if(inPosVal.unitSizeVal.combat == CUnitSize::INFANTRY)
	{
		if(inPosVal.unitSizeVal.mil == CUnitSize::INFANTRY_SQUAD)
		{
			typeOp = 1;
		}
		else if(inPosVal.unitSizeVal.mil == CUnitSize::INFANTRY_COMPANY)
		{
			typeOp = 2;
		}
		else if(inPosVal.unitSizeVal.mil == CUnitSize::INFANTRY_BATTALION)
		{
			typeOp = 3;
		}
		else
		{
			typeOp = 0;
		}
	}
	else if(inPosVal.unitSizeVal.combat == CUnitSize::ARMORED)
	{
		if(inPosVal.unitSizeVal.moveType == CUnitSize::DEFENCE)
		{
			
			if(inPosVal.unitSizeVal.mil == CUnitSize::ARMORED_COMPANY)
			{
				typeOp = 2;
			}
			else if(inPosVal.unitSizeVal.mil == CUnitSize::ARMORED_BATTALION)
			{
				typeOp = 4;
			}
			else
			{
				typeOp = 0;
			}
		}
		else
		{
			if(inPosVal.unitSizeVal.mil == CUnitSize::ARMORED_COMPANY)
			{
				typeOp = 2;
			}
			else if(inPosVal.unitSizeVal.mil == CUnitSize::ARMORED_BATTALION)
			{
				typeOp = 4;
			}
			else
			{
				typeOp = 0;
			}
		}
	}
	else
	{
		if(inPosVal.unitSizeVal.mil == CUnitSize::ARTILLERY_BATTALION)
		{
			typeOp = 2;
		}
		else
		{
			typeOp = 0;
		}
	}


	if(inPosVal.unitSizeVal.combat == CUnitSize::INFANTRY && inPosVal.unitSizeVal.mil == CUnitSize::INFANTRY_SQUAD)
	{
		vector<CVector2d> vecHiData = changeDisaggregatedPositionInfantrySquad(inPosVal, areaPos, drawtext);

		vector<int> logVal;
		vector<float> logVal_sub;
		for(int i = 0; i < (int)vecHiData.size(); i++)
		{
			logVal.push_back((int)vecHiData[i].x);
			logVal.push_back((int)vecHiData[i].y);

			logVal_sub.push_back(ceilf((vecHiData[i].x - inPosVal.parent.x)*100)/100);
			logVal_sub.push_back(ceilf((vecHiData[i].y - inPosVal.parent.y)*100)/100);

			drawPosItem.push_back(CVector2d(ceilf((vecHiData[i].x - inPosVal.parent.x)*100)/100,
			ceilf((vecHiData[i].y - inPosVal.parent.y)*100)/100));
		}
		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg 값 :");
		CLogDlg::insertStreamVec(logVal, '	');
		CLogDlg::addLogTextStream();


		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg Sub :");
		CLogDlg::insertStreamVec(logVal_sub, '	');
		CLogDlg::addLogTextStream();

		CVector2d centroid = changeAggregatedPositionInfantrySquad(vecHiData);

		logVal.clear();
		logVal_sub.clear();
		logVal.push_back((int)centroid.x);
		logVal.push_back((int)centroid.y);

		int subX = (int)centroid.x - (int)inPosVal.parent.x;
		int subY = (int)centroid.y - (int)inPosVal.parent.y;

		logVal_sub.push_back((float)subX);
		logVal_sub.push_back((float)subY);

		int Aggdistance = (int)sqrt((pow((float)subX, 2)+pow((float)subY, 2)));

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 좌표 :");
		CLogDlg::insertStreamVec(logVal,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg Sub : ");
		CLogDlg::insertStreamVec(logVal_sub,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 거리 :");
		CLogDlg::insertStream(Aggdistance,'	');
		CLogDlg::addLogTextStream();
	}
	else if(inPosVal.unitSizeVal.combat == CUnitSize::ARTILLERY && inPosVal.unitSizeVal.mil == CUnitSize::ARTILLERY_COMPANY)
	{
		vector<CVector2d> vecHiData = changeDisaggregatedPositionArtilleryCompany(inPosVal, areaPos, drawtext);

		vector<int> logVal;
		vector<float> logVal_sub;
		for(int i = 0; i < (int)vecHiData.size(); i++)
		{
			logVal.push_back((int)vecHiData[i].x);
			logVal.push_back((int)vecHiData[i].y);

			logVal_sub.push_back(ceilf((vecHiData[i].x - inPosVal.parent.x)*100)/100);
			logVal_sub.push_back(ceilf((vecHiData[i].y - inPosVal.parent.y)*100)/100);

			drawPosItem.push_back(CVector2d(ceilf((vecHiData[i].x - inPosVal.parent.x)*100)/100,
				ceilf((vecHiData[i].y - inPosVal.parent.y)*100)/100));
		}
		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg 값 :");
		CLogDlg::insertStreamVec(logVal, '	');
		CLogDlg::addLogTextStream();


		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg Sub :");
		CLogDlg::insertStreamVec(logVal_sub, '	');
		CLogDlg::addLogTextStream();

		CVector2d centroid = changeAggregatedPositionInfantrySquad(vecHiData);

		logVal.clear();
		logVal_sub.clear();
		logVal.push_back((int)centroid.x);
		logVal.push_back((int)centroid.y);

		int subX = (int)centroid.x - (int)inPosVal.parent.x;
		int subY = (int)centroid.y - (int)inPosVal.parent.y;

		logVal_sub.push_back((float)subX);
		logVal_sub.push_back((float)subY);

		int Aggdistance = (int)sqrt((pow((float)subX, 2)+pow((float)subY, 2)));

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 좌표 :");
		CLogDlg::insertStreamVec(logVal,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg Sub : ");
		CLogDlg::insertStreamVec(logVal_sub,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 거리 :");
		CLogDlg::insertStream(Aggdistance,'	');
		CLogDlg::addLogTextStream();
	}
	else
	{
		vector<CVector2d> vecHiData = changeDisaggregatedPosition(inPosVal, areaPos, drawtext);
		vector<int> logVal;
		vector<int> logVal_sub;
		for(int i = 0; i < (int)vecHiData.size(); i++)
		{
			logVal.push_back((int)vecHiData[i].x);
			logVal.push_back((int)vecHiData[i].y);

			logVal_sub.push_back((int)vecHiData[i].x - (int)inPosVal.parent.x);
			logVal_sub.push_back((int)vecHiData[i].y - (int)inPosVal.parent.y);

			drawPosItem.push_back(CVector2d(ceilf((vecHiData[i].x - inPosVal.parent.x)*100)/100,
				ceilf((vecHiData[i].y - inPosVal.parent.y)*100)/100));
		}
		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg 값 :");
		CLogDlg::insertStreamVec(logVal, '	');
		CLogDlg::addLogTextStream();


		CLogDlg::initStream();
		CLogDlg::insertStream("DisAgg Sub :");
		CLogDlg::insertStreamVec(logVal_sub, '	');
		CLogDlg::addLogTextStream();

		CVector2d centroid = changeAggregatedPosition(vecHiData);

		logVal.clear();
		logVal_sub.clear();
		logVal.push_back((int)centroid.x);
		logVal.push_back((int)centroid.y);

		int subX = (int)centroid.x - (int)inPosVal.parent.x;
		int subY = (int)centroid.y - (int)inPosVal.parent.y;

		logVal_sub.push_back(subX);
		logVal_sub.push_back(subY);

		int Aggdistance = (int)sqrt((pow((float)subX, 2)+pow((float)subY, 2)));

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 좌표 :");
		CLogDlg::insertStreamVec(logVal,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg Sub : ");
		CLogDlg::insertStreamVec(logVal_sub,'	');
		CLogDlg::addLogTextStream();

		CLogDlg::initStream();
		CLogDlg::insertStream("Agg 거리 :");
		CLogDlg::insertStream(Aggdistance,'	');
		CLogDlg::addLogTextStream();
	}	

	CGAgt::G()->drawResolutionPosition(drawPosItem, typeOp, areaPos, drawtext);

	CLogDlg::AddLogText("<====================>");
}

vector<CVector2d> CResolutionChange::changeDisaggregatedPosition(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText)
{
	//지향방향 노말 벡터
	CVector2d front = frontDirection(val.dir);
	//직각 y 방향 벡터
	CVector2d cross = crossDirection(front);
	//부대 반경
	vector<int> sizeUnit = unitSizeVal->unitZoneSize(val.unitSizeVal);
	CLogDlg::initStream();
	CLogDlg::insertStream("작전지역 :");
	CLogDlg::insertStreamVec(sizeUnit, '	');
	CLogDlg::addLogTextStream();
	drawText.Format(_T("작전지역 : %d X %d "), sizeUnit[SIZEVEC_WIDTH], sizeUnit[SIZEVEC_HIGHT]);

	//최종 분해 요소 값
	vector<CVector2d> vecHiData = deploymentPosition(val.dep, val.parent, front, cross, sizeUnit);

	areaPos = areaPosition(front, cross, sizeUnit);

	return vecHiData;
}

vector<CVector2d> CResolutionChange::changeDisaggregatedPositionInfantrySquad(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText)
{
	//지향방향 노말 벡터
	CVector2d front = frontDirection(val.dir);
	//직각 y 방향 벡터
	CVector2d cross = crossDirection(front);

	//부대 반경
	vector<int> sizeUnit = unitSizeVal->unitZoneSize(val.unitSizeVal);
	CLogDlg::initStream();
	CLogDlg::insertStream("작전지역 :");
	CLogDlg::insertStreamVec(sizeUnit, '	');
	CLogDlg::addLogTextStream();
	drawText.Format(_T("작전지역 : %d X %d "), sizeUnit[SIZEVEC_WIDTH], sizeUnit[SIZEVEC_HIGHT]);

	areaPos = areaPosition(front, cross, sizeUnit);

	vector<CVector2d> result;
	result.resize(SQUDISAGG_SIZE);

	switch (val.unitSizeVal.moveType)
	{
	case CUnitSize::DEFENCE:
		switch (val.dep)
		{
		case DEP_CIRCLE:		// 원형
			result[SQUDISAGG_NUM01] = val.parent + cross*(-10) + front*(20);
			result[SQUDISAGG_NUM02] = val.parent + cross*(10) + front*(20);
			result[SQUDISAGG_NUM03] = val.parent + cross*(-20) + front*(10);
			result[SQUDISAGG_NUM04] = val.parent + cross*(20) + front*(10);
			result[SQUDISAGG_NUM05] = val.parent + cross*(-20) + front*(-10);
			result[SQUDISAGG_NUM06] = val.parent + cross*(20) + front*(-10);
			result[SQUDISAGG_NUM07] = val.parent + cross*(-10) + front*(-20);
			result[SQUDISAGG_NUM08] = val.parent + cross*(10) + front*(-20);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-20);
			result[SQUDISAGG_NUM10] = val.parent + cross*(20);
			result[SQUDISAGG_NUM11] = val.parent + front*(20);
			result[SQUDISAGG_NUM12] = val.parent + front*(-20);
			break;
		case DEP_LINE:		// 횡대
			result[SQUDISAGG_NUM01] = val.parent + cross*(-20) + front*(5);
			result[SQUDISAGG_NUM02] = val.parent + cross*(20) + front*(5);
			result[SQUDISAGG_NUM03] = val.parent + cross*(-40) + front*(5);
			result[SQUDISAGG_NUM04] = val.parent + cross*(40) + front*(5);
			result[SQUDISAGG_NUM05] = val.parent + cross*(-30) + front*(-5);
			result[SQUDISAGG_NUM06] = val.parent + cross*(10) + front*(-5);
			result[SQUDISAGG_NUM07] = val.parent + cross*(-50) + front*(-5);
			result[SQUDISAGG_NUM08] = val.parent + cross*(30) + front*(-5);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-60) + front*(5);
			result[SQUDISAGG_NUM10] = val.parent + cross*(-10) + front*(-5);
			result[SQUDISAGG_NUM11] = val.parent + cross*(60) + front*(5);
			result[SQUDISAGG_NUM12] = val.parent + cross*(50) + front*(-5);
			break;
		case DEP_COLUMN:		// 종대
			result[SQUDISAGG_NUM01] = val.parent + cross*(-5) + front*(25);
			result[SQUDISAGG_NUM02] = val.parent + cross*(-15) + front*(15);
			result[SQUDISAGG_NUM03] = val.parent + cross*(5) + front*(15);
			result[SQUDISAGG_NUM04] = val.parent + cross*(15) + front*(5);
			result[SQUDISAGG_NUM05] = val.parent + cross*(5) + front*(5);
			result[SQUDISAGG_NUM06] = val.parent + cross*(-5) + front*(-5);
			result[SQUDISAGG_NUM07] = val.parent + cross*(15) + front*(-5);
			result[SQUDISAGG_NUM08] = val.parent + cross*(-15) + front*(-15);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-25) + front*(5);
			result[SQUDISAGG_NUM10] = val.parent + cross*(-25) + front*(-25);
			result[SQUDISAGG_NUM11] = val.parent + cross*(25) + front*(-5);
			result[SQUDISAGG_NUM12] = val.parent + cross*(25) + front*(-15);
			break;
		default:
			break;
		}
		break;
	case CUnitSize::OFFENCE:
		switch (val.dep)
		{
		case DEP_CIRCLE:		// 원형
			result[SQUDISAGG_NUM01] = val.parent + cross*(-5) + front*(10);
			result[SQUDISAGG_NUM02] = val.parent + cross*(5) + front*(10);
			result[SQUDISAGG_NUM03] = val.parent + cross*(-10) + front*(5);
			result[SQUDISAGG_NUM04] = val.parent + cross*(10) + front*(5);
			result[SQUDISAGG_NUM05] = val.parent + cross*(-10) + front*(-5);
			result[SQUDISAGG_NUM06] = val.parent + cross*(10) + front*(-5);
			result[SQUDISAGG_NUM07] = val.parent + cross*(-5) + front*(-10);
			result[SQUDISAGG_NUM08] = val.parent + cross*(5) + front*(-10);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-10);
			result[SQUDISAGG_NUM10] = val.parent + cross*(10);
			result[SQUDISAGG_NUM11] = val.parent + front*(10);
			result[SQUDISAGG_NUM12] = val.parent + front*(-10);
			break;
		case DEP_LINE:		// 횡대
			result[SQUDISAGG_NUM01] = val.parent + cross*(-10) + front*(2.5);
			result[SQUDISAGG_NUM02] = val.parent + cross*(10) + front*(2.5);
			result[SQUDISAGG_NUM03] = val.parent + cross*(-20) + front*(2.5);
			result[SQUDISAGG_NUM04] = val.parent + cross*(20) + front*(2.5);
			result[SQUDISAGG_NUM05] = val.parent + cross*(-15) + front*(-2.5);
			result[SQUDISAGG_NUM06] = val.parent + cross*(5) + front*(-2.5);
			result[SQUDISAGG_NUM07] = val.parent + cross*(-25) + front*(-2.5);
			result[SQUDISAGG_NUM08] = val.parent + cross*(15) + front*(-2.5);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-30) + front*(2.5);
			result[SQUDISAGG_NUM10] = val.parent + cross*(-5) + front*(-2.5);
			result[SQUDISAGG_NUM11] = val.parent + cross*(30) + front*(2.5);
			result[SQUDISAGG_NUM12] = val.parent + cross*(25) + front*(-2.5);
			break;
		case DEP_COLUMN:		// 종대
			result[SQUDISAGG_NUM01] = val.parent + cross*(-2.5) + front*(12.5);
			result[SQUDISAGG_NUM02] = val.parent + cross*(-7.5) + front*(7.5);
			result[SQUDISAGG_NUM03] = val.parent + cross*(2.5) + front*(7.5);
			result[SQUDISAGG_NUM04] = val.parent + cross*(7.5) + front*(2.5);
			result[SQUDISAGG_NUM05] = val.parent + cross*(2.5) + front*(2.5);
			result[SQUDISAGG_NUM06] = val.parent + cross*(-2.5) + front*(-2.5);
			result[SQUDISAGG_NUM07] = val.parent + cross*(7.5) + front*(-2.5);
			result[SQUDISAGG_NUM08] = val.parent + cross*(-7.5) + front*(-7.5);
			result[SQUDISAGG_NUM09] = val.parent + cross*(-12.5) + front*(2.5);
			result[SQUDISAGG_NUM10] = val.parent + cross*(-12.5) + front*(-12.5);
			result[SQUDISAGG_NUM11] = val.parent + cross*(12.5) + front*(-2.5);
			result[SQUDISAGG_NUM12] = val.parent + cross*(12.5) + front*(-7.5);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return result;
}

vector<CVector2d> CResolutionChange::changeDisaggregatedPositionArtilleryCompany(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText)
{
	//지향방향 노말 벡터
	CVector2d front = frontDirection(val.dir);
	//직각 y 방향 벡터
	CVector2d cross = crossDirection(front);

	//부대 반경
	vector<int> sizeUnit = unitSizeVal->unitZoneSize(val.unitSizeVal);
	CLogDlg::initStream();
	CLogDlg::insertStream("작전지역 :");
	CLogDlg::insertStreamVec(sizeUnit, '	');
	CLogDlg::addLogTextStream();
	drawText.Format(_T("작전지역 : %d X %d "), sizeUnit[SIZEVEC_WIDTH], sizeUnit[SIZEVEC_HIGHT]);

	areaPos = areaPosition(front, cross, sizeUnit);

	vector<CVector2d> result;
	result.resize(ARCOMDISAGG_SIZE);


	switch (val.dep)
	{
	case DEP_CIRCLE:		// 원형
		result[ARCOMDISAGG_NUM01] = val.parent + cross*(-50) + front*(100);
		result[ARCOMDISAGG_NUM02] = val.parent + cross*(50) + front*(100);
		result[ARCOMDISAGG_NUM03] = val.parent + cross*(-50) + front*(-100);
		result[ARCOMDISAGG_NUM04] = val.parent + cross*(50) + front*(-100);
		result[ARCOMDISAGG_NUM05] = val.parent + cross*(-100);
		result[ARCOMDISAGG_NUM06] = val.parent + cross*(100);
		break;
	case DEP_LINE:		// 횡대
		result[ARCOMDISAGG_NUM01] = val.parent + cross*(-25) + front*(50);
		result[ARCOMDISAGG_NUM02] = val.parent + cross*(-125) + front*(50);
		result[ARCOMDISAGG_NUM03] = val.parent + cross*(75) + front*(50);
		result[ARCOMDISAGG_NUM04] = val.parent + cross*(25) + front*(-50);
		result[ARCOMDISAGG_NUM05] = val.parent + cross*(-75) + front*(-50);
		result[ARCOMDISAGG_NUM06] = val.parent + cross*(125) + front*(-50);
		break;
	case DEP_COLUMN:		// 종대
		result[ARCOMDISAGG_NUM01] = val.parent + front*(50);
		result[ARCOMDISAGG_NUM02] = val.parent + front*(-50);
		result[ARCOMDISAGG_NUM03] = val.parent + front*(150);
		result[ARCOMDISAGG_NUM04] = val.parent + front*(-150);
		result[ARCOMDISAGG_NUM05] = val.parent + front*(250);
		result[ARCOMDISAGG_NUM06] = val.parent + front*(-250);
		break;
	default:
		break;
	}

	return result;
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
	case CALC_POS8:		// 9
		vecVal = parent + front*(-(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f));
		break;
	case CALC_POS9:		// 10
		vecVal = parent + front*(-(sizeUnit[SIZEVEC_HIGHT] * 3.0f / 8.0f));
		break;
	case CALC_POS10:		// 11
		vecVal = parent + cross*(-(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f)) + front*(-(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f));
		break;
	case CALC_POS11:		// 12
		vecVal = parent + cross*(sizeUnit[SIZEVEC_WIDTH] * 2.0f / 8.0f) + front*(-(sizeUnit[SIZEVEC_HIGHT] * 2.0f / 8.0f));
		break;
	default:
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
	case DEP_CIRCLE:		// 원형
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS5, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS7, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		break;
	case DEP_LINE:		// 횡대
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS0, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS4, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		break;
	case DEP_COLUMN:		// 종대
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS6, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS8, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS9, parent, front, cross, sizeUnit);
		break;
	case DEP_TRIANGLE:		// 삼각대
		result[DISAGG_NUM1] = calcPosition(CALC_POS2, parent, front, cross, sizeUnit);
		result[DISAGG_NUM2] = calcPosition(CALC_POS10, parent, front, cross, sizeUnit);
		result[DISAGG_NUM3] = calcPosition(CALC_POS11, parent, front, cross, sizeUnit);
		result[DISAGG_NUM4] = calcPosition(CALC_POS9, parent, front, cross, sizeUnit);
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

vector<CVector2d> CResolutionChange::areaPosition(CVector2d front, CVector2d cross, vector<int> sizeUnit)
{
	vector<CVector2d> result;
	if(sizeUnit.size() <= SIZEVEC_SIZE)
	{
		result.resize(AREAPOS_SIZE);
		result[AREAPOS_NUM1] = cross*((float)-1*sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM2] = cross*((float)sizeUnit[SIZEVEC_WIDTH]/2) + front*(float)(sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM3] = cross*((float)sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM4] = cross*((float)-1*sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVEC_HIGHT]/2);
	}
	else
	{
		result.resize(AREABTP_SIZE);
		result[AREAPOS_NUM1] = cross*((float)-1*sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM2] = cross*((float)sizeUnit[SIZEVEC_WIDTH]/2) + front*(float)(sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM3] = cross*((float)sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVEC_HIGHT]/2);
		result[AREAPOS_NUM4] = cross*((float)-1*sizeUnit[SIZEVEC_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVEC_HIGHT]/2);

		result[AREABTP_NUM1] = cross*((float)-1*sizeUnit[SIZEVECBT_WIDTH]/2) + front*((float)sizeUnit[SIZEVECBT_HIGHT]/2);
		result[AREABTP_NUM2] = cross*((float)sizeUnit[SIZEVECBT_WIDTH]/2) + front*(float)(sizeUnit[SIZEVECBT_HIGHT]/2);
		result[AREABTP_NUM3] = cross*((float)sizeUnit[SIZEVECBT_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVECBT_HIGHT]/2);
		result[AREABTP_NUM4] = cross*((float)-1*sizeUnit[SIZEVECBT_WIDTH]/2) + front*((float)-1*sizeUnit[SIZEVECBT_HIGHT]/2);
	}
	
	return result;
}

CVector2d CResolutionChange::changeAggregatedPosition(vector<CVector2d> posList)
{
	CVector2d centroid(0.0f, 0.0f);
	for (int i = 0; i < (int)posList.size(); ++i)
	{
		centroid = centroid + posList[i];
	}
	centroid = centroid/(float)posList.size();

	//int size = (int)posList.size();
	//if (size >= 3)
	//{
	//	double factor = 0;
	//	double centerX = 0;
	//	double centerY = 0;
	//	double area = 0;

	//	for (int firstIndex = 0; firstIndex < size; firstIndex++)
	//	{
	//		int secondIndex = (firstIndex + 1) % size;

	//		CVector2d firstPoint = posList[firstIndex];
	//		CVector2d secondPoint = posList[secondIndex];

	//		factor = ((firstPoint.x * secondPoint.y) - (secondPoint.x * firstPoint.y));

	//		area += factor;

	//		centerX += (firstPoint.x + secondPoint.x) * factor;
	//		centerY += (firstPoint.y + secondPoint.y) * factor;
	//	}

	//	if ((0.0 == area) == false)
	//	{
	//		area /= 2.0f;
	//		area *= 6.0f;

	//		factor = 1 / area;
	//		centerX *= factor;
	//		centerY *= factor;

	//		centroid.x = (float)centerX;
	//		centroid.y = (float)centerY;
	//	}
	//	else
	//	{
	//		centerX = 0.0;
	//		centerY = 0.0;

	//		for (int i = 0; i < size; ++i)
	//		{
	//			CVector2d point = posList[i];

	//			centerX += point.x;
	//			centerY += point.y;
	//		}

	//		centroid.x = (float)centerX/size;
	//		centroid.y = (float)centerY/size;
	//	}
	//}
	//else if (size > 0)
	//{
	//	for (int i = 0; i < size; ++i)
	//	{
	//		centroid = centroid + posList[i];
	//	}
	//	centroid = centroid/(float)size;
	//}

	return centroid;
}

CVector2d CResolutionChange::changeAggregatedPosition(vector<CVector2d> posList, int size)
{
	CVector2d centroid(0.0f, 0.0f);
	int chSize = min((int)posList.size(), size);
	for (int i = 0; i < chSize; ++i)
	{
		centroid = centroid + posList[i];
	}
	centroid = centroid/(float)chSize;

	return centroid;
}

CVector2d CResolutionChange::changeAggregatedPositionInfantrySquad(vector<CVector2d> posList)
{
	CVector2d centroid(0.0f, 0.0f);
	for (int i = 0; i < (int)posList.size(); ++i)
	{
		centroid = centroid + posList[i];
	}
	centroid = centroid/(float)posList.size();
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

vector<CString> CResolutionChange::strDirectionType()
{
	vector<CString> strEm;
	strEm.clear();
	strEm.push_back("북");
	strEm.push_back("북동");
	strEm.push_back("동");
	strEm.push_back("남동");
	strEm.push_back("남");
	strEm.push_back("남서");
	strEm.push_back("서");
	strEm.push_back("북서");
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

CString CResolutionChange::strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, CResolutionChange::DEPLOYMENTTYPE em)
{
	CString strEm = "UNKNOW";
	if((CUnitSize::INFANTRY == combat && CUnitSize::INFANTRY_SQUAD == mil) || (CUnitSize::ARTILLERY == combat))
	{
		switch (em)
		{
		case DEP_CIRCLE:strEm = "원형";
			break;
		case DEP_LINE:strEm = "횡대";
			break;
		case DEP_COLUMN:strEm = "종대";
			break;
		default:
			break;
		}
	}
	else
	{
		switch (em)
		{
		case DEP_INVERTEDTRIANGLE:strEm = "역삼각대";
			break;
		case DEP_CIRCLE:strEm = "원형";
			break;
		case DEP_LINE:strEm = "횡대";
			break;
		case DEP_COLUMN:strEm = "종대";
			break;
		case DEP_TRIANGLE:strEm = "삼각대";
			break;
		default:
			break;
		}
	}	
	return strEm;
}

vector<CString> CResolutionChange::strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil)
{
	vector<CString> strEm;
	strEm.clear();
	if((CUnitSize::INFANTRY == combat && CUnitSize::INFANTRY_SQUAD == mil) || (CUnitSize::ARTILLERY == combat))
	{
		strEm.push_back("원형");
		strEm.push_back("횡대");
		strEm.push_back("종대");
	}
	else
	{
		strEm.push_back("역삼각대");
		strEm.push_back("원형");
		strEm.push_back("횡대");
		strEm.push_back("종대");
		strEm.push_back("삼각대");
	}	
	return strEm;
}

CResolutionChange::DEPLOYMENTTYPE CResolutionChange::emDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, int selNum)
{
	CResolutionChange::DEPLOYMENTTYPE em = DEP_NONE;
	if((CUnitSize::INFANTRY == combat && CUnitSize::INFANTRY_SQUAD == mil) || (CUnitSize::ARTILLERY == combat))
	{
		switch (selNum)
		{
		case 0: em = DEP_CIRCLE;
			break;
		case 1: em = DEP_LINE;
			break;
		case 2: em = DEP_COLUMN;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (selNum)
		{
		case 0: em = DEP_INVERTEDTRIANGLE;
			break;
		case 1: em = DEP_CIRCLE;
			break;
		case 2: em = DEP_LINE;
			break;
		case 3: em = DEP_COLUMN;
			break;
		case 4: em = DEP_TRIANGLE;
			break;
		default:
			break;
		}
	}
	return em;
}

CString CResolutionChange::strTopographicChar(CUnitSize::COMBATANT combat, CResolutionChange::TOPOGRAPHICCHAR em)
{
	CString strEm = "UNKNOW";
	if(CUnitSize::INFANTRY == combat)
	{
		switch (em)
		{
		case TOPO_MAPRI:strEm = "수면";
			break;
		case TOPO_MAPSE:strEm = "해수면";
			break;
		default:
			break;
		}
	}
	else if(CUnitSize::ARMORED == combat)
	{
		switch (em)
		{
		case TOPO_MAPSE:strEm = "해수면";
			break;
		case TOPO_MAPFO:strEm = "산림화";
			break;
		case TOPO_MAPSW:strEm = "늪지";
			break;
		default:
			break;
		}
	}
	else
	{
		switch (em)
		{
		case TOPO_MAPRI:strEm = "수면";
			break;
		case TOPO_MAPMO:strEm = "산악";
			break;
		case TOPO_MAPHO:strEm = "소택지";
			break;
		default:
			break;
		}
	}
	return strEm;
}

vector<CString> CResolutionChange::strTopographicChar(CUnitSize::COMBATANT combat)
{
	vector<CString> strEm;
	strEm.clear();
	if(CUnitSize::INFANTRY == combat)
	{
		strEm.push_back("수면");
		strEm.push_back("해수면");
	}
	else if(CUnitSize::ARMORED == combat)
	{
		strEm.push_back("해수면");
		strEm.push_back("산림화");
		strEm.push_back("늪지");
	}
	else
	{
		strEm.push_back("수면");
		strEm.push_back("산악");
		strEm.push_back("소택지");
	}
	return strEm;
}

CResolutionChange::TOPOGRAPHICCHAR CResolutionChange::emTopographicChar(CUnitSize::COMBATANT combat, int selNum)
{
	CResolutionChange::TOPOGRAPHICCHAR em = TOPO_MAPRI;
	if(CUnitSize::INFANTRY == combat)
	{
		switch (selNum)
		{
		case 0: em = TOPO_MAPRI;
			break;
		case 1: em = TOPO_MAPSE;
			break;
		default:
			break;
		}
	}
	else if(CUnitSize::ARMORED == combat)
	{
		switch (selNum)
		{
		case 0: em = TOPO_MAPSE;
			break;
		case 1: em = TOPO_MAPFO;
			break;
		case 2: em = TOPO_MAPSW;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (selNum)
		{
		case 0: em = TOPO_MAPRI;
			break;
		case 1: em = TOPO_MAPMO;
			break;
		case 2: em = TOPO_MAPHO;
			break;
		default:
			break;
		}
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
	inPosVal.unitSizeVal.mil = em;
}

void CResolutionChange::setTopographicChar(TOPOGRAPHICCHAR em)
{
	topoChar = em;
}

CResolutionChange::TOPOGRAPHICCHAR CResolutionChange::getTopographicChar()
{
	return topoChar;
}