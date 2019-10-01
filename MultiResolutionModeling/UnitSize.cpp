// UnitSize.cpp
//

#include "stdafx.h"
#include "UnitSize.h"
#include "CSVFile.h"
#include "LogDlg.h"


CUnitSize::CUnitSize()
{

}
CUnitSize::~CUnitSize()
{

}

void CUnitSize::loadCSVFile(string fileName)
{
	CCSVFile readCSV;

	char delimiter = ',';
	CLogDlg::AddLogText("<부대반경 표>");
	if (readCSV.loadCSVFile(fileName)) {
		int loop = 0;
		VECVECINT vecinfantry;
		VECVECINT vecarmdred;
		VECVECINT vecartillery;
		while (readCSV.inStream().good()) {
			vector<int> row = CCSVFile::csv_read_row_int(readCSV.inStream(), delimiter);
			CLogDlg::AddLogText(row, '	');
			if (loop < (int)ARMORED) {
				vecinfantry.push_back(row);
			}
			else if (loop < (int)ARTILLERY) {
				vecarmdred.push_back(row);
			}
			else {
				vecartillery.push_back(row);
			}
			loop++;
		}
		readCSV.unloadCSVFile();
		mapCombatant.SetAt(INFANTRY, vecinfantry);
		mapCombatant.SetAt(ARMORED, vecarmdred);
		mapCombatant.SetAt(ARTILLERY, vecartillery);
	}
}

vector<int> CUnitSize::getINFANTRYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo)
{
	vector<int> size;
	VECVECINT infVal = mapCombatant[INFANTRY];
	int xVal = infVal[mil][mo+ fo+ WIDTH];
	int yVal = infVal[mil][mo + fo + HIGHT];
	size.push_back(xVal);
	size.push_back(yVal);
	return size;
}

vector<int> CUnitSize::getARMOREDSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo)
{
	vector<int> size;
	VECVECINT infVal = mapCombatant[ARMORED];
	int xVal = infVal[mil][mo + fo + WIDTH];
	int yVal = infVal[mil][mo + fo + HIGHT];
	size.push_back(xVal);
	size.push_back(yVal);
	return size;
}

vector<int> CUnitSize::getARTILLERYSize(MILITARYBRANCH_AR mil, MOVETYPE mo, FORCE fo)
{
	vector<int> size;
	VECVECINT infVal = mapCombatant[ARTILLERY];
	int xVal = infVal[mil][mo + fo + WIDTH];
	int yVal = infVal[mil][mo + fo + HIGHT];
	size.push_back(xVal);
	size.push_back(yVal);
	return size;
}

vector<int> CUnitSize::unitZoneSize(InputVal in)
{
	vector<int> size;
	switch (in.combat)
	{
	case INFANTRY:
		size = getINFANTRYSize(in.milVal.mil, in.moveType, in.force);
		break;
	case ARMORED:
		size = getARMOREDSize(in.milVal.mil, in.moveType, in.force);
		break;
	case ARTILLERY:
		size = getARTILLERYSize(in.milVal.mil_AR, in.moveType, in.force);
	default:
		break;
	}
	return size;
}

CString CUnitSize::strMoveType(CUnitSize::MOVETYPE em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case DEFENCE:strEm = "방어";
		break;
	case OFFENCE:strEm = "공격";
		break;
	default:
		break;
	}
	return strEm;
}

CString CUnitSize::strForce(CUnitSize::FORCE em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case BLUEFORCE:strEm = "청군";
		break;
	case REDFORCE:strEm = "홍군";
		break;
	default:
		break;
	}
	return strEm;
}

CString CUnitSize::strCombatent(CUnitSize::COMBATANT em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case INFANTRY:strEm = "보병";
		break;
	case ARMORED:strEm = "전차";
		break;
	case ARTILLERY:strEm = "포병";
		break;
	default:
		break;
	}
	return strEm;
}

CString CUnitSize::strMilitarybranch(CUnitSize::MILITARYBRANCH em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case SQUAD:strEm = "분대";
		break;
	case PLATOON:strEm = "소대";
		break;
	case COMPANY:strEm = "중대";
		break;
	case BATTALION:strEm = "대대";
		break;
	default:
		break;
	}
	return strEm;
}

CString CUnitSize::strMilitarybranch_AR(CUnitSize::MILITARYBRANCH_AR em)
{
	CString strEm = "UNKNOW";
	switch (em)
	{
	case ARTILLERYUNIT:strEm = "포대";
		break;
	case ARTILLERYBT:strEm = "대대";
		break;
	default:
		break;
	}
	return strEm;
}