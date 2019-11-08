// UnitSize.cpp
//

#include "stdafx.h"
#include "UnitSize.h"
#include "CSVFile.h"


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
	CLogDlg::AddLogText("<작전지역 표>");
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

vector<int> CUnitSize::getARTILLERYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo)
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
		size = getINFANTRYSize(in.mil, in.moveType, in.force);
		break;
	case ARMORED:
		size = getARMOREDSize(in.mil, in.moveType, in.force);
		break;
	case ARTILLERY:
		size = getARTILLERYSize(in.mil, in.moveType, in.force);
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

vector<CString> CUnitSize::strMoveType()
{
	vector<CString> strEm;
	strEm.clear();
	strEm.push_back("방어");
	strEm.push_back("공격");
	return strEm;
}

CUnitSize::MOVETYPE CUnitSize::emMoveType(int selNum)
{
	CUnitSize::MOVETYPE em = DEFENCE;
	switch (selNum)
	{
	case 0: em = DEFENCE;
		break;
	case 1: em = OFFENCE;
		break;
	default:
		break;
	}
	return em;
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

vector<CString> CUnitSize::strForce()
{
	vector<CString> strEm;
	strEm.clear();
	strEm.push_back("청군");
	strEm.push_back("홍군");
	return strEm;
}

CUnitSize::FORCE CUnitSize::emForce(int selNum)
{
	CUnitSize::FORCE em = BLUEFORCE;
	switch (selNum)
	{
	case 0: em = BLUEFORCE;
		break;
	case 1: em = REDFORCE;
		break;
	default:
		break;
	}
	return em;
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

vector<CString> CUnitSize::strCombatent()
{
	vector<CString> strEm;
	strEm.clear();
	strEm.push_back("보병");
	strEm.push_back("전차");
	strEm.push_back("포병");
	return strEm;
}

CUnitSize::COMBATANT CUnitSize::emCombatent(int selNum)
{
	CUnitSize::COMBATANT em = INFANTRY;
	switch (selNum)
	{
	case 0: em = INFANTRY;
		break;
	case 1: em = ARMORED;
		break;
	case 2: em = ARTILLERY;
		break;
	default:
		break;
	}
	return em;
}

CString CUnitSize::strMilitarybranch(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH em)
{
	CString strEm = "UNKNOW";
	switch (combat)
	{
	case INFANTRY:
		switch (em)
		{
		case INFANTRY_SQUAD:strEm = "분대";
			break;
		case INFANTRY_PLATOON:strEm = "소대";
			break;
		case INFANTRY_COMPANY:strEm = "중대";
			break;
		case INFANTRY_BATTALION:strEm = "대대";
			break;
		default:
			break;
		}
		break;
	case ARMORED:
		switch (em)
		{
		case ARMORED_PLATOON:strEm = "소대";
			break;
		case ARMORED_COMPANY:strEm = "중대";
			break;
		case ARMORED_BATTALION:strEm = "대대";
			break;
		default:
			break;
		}
		break;
	case ARTILLERY:
		switch (em)
		{
		case ARTILLERY_COMPANY:strEm = "포대";
			break;
		case ARTILLERY_BATTALION:strEm = "대대";
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return strEm;
}

vector<CString> CUnitSize::strMilitarybranch(CUnitSize::COMBATANT combat)
{
	vector<CString> strEm;
	strEm.clear();
	switch (combat)
	{
	case INFANTRY:
		strEm.push_back("분대");
		strEm.push_back("소대");
		strEm.push_back("중대");
		strEm.push_back("대대");
		break;
	case ARMORED:
		strEm.push_back("소대");
		strEm.push_back("중대");
		strEm.push_back("대대");
		break;
	case ARTILLERY:
		strEm.push_back("포대");
		strEm.push_back("대대");
		break;
	default:
		break;
	}
	return strEm;
}

CUnitSize::MILITARYBRANCH CUnitSize::emMilitarybranch(CUnitSize::COMBATANT combat, int selNum)
{
	CUnitSize::MILITARYBRANCH em = INFANTRY_SQUAD;
	switch (combat)
	{
	case INFANTRY:
		switch (selNum)
		{
		case 0: em = INFANTRY_SQUAD;
			break;
		case 1: em = INFANTRY_PLATOON;
			break;
		case 2: em = INFANTRY_COMPANY;
			break;
		case 3: em = INFANTRY_BATTALION;
			break;
		default:
			break;
		}
		break;
	case ARMORED:
		switch (selNum)
		{
		case 0: em = ARMORED_PLATOON;
			break;
		case 1: em = ARMORED_COMPANY;
			break;
		case 2: em = ARMORED_BATTALION;
			break;
		default:
			break;
		}
		break;
	case ARTILLERY:
		switch (selNum)
		{
		case 0: em = ARTILLERY_COMPANY;
			break;
		case 1: em = ARTILLERY_BATTALION;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return em;
}
