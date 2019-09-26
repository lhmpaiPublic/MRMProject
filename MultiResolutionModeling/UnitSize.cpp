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
	if (readCSV.loadCSVFile(fileName)) {
		int loop = 0;
		VECVECINT vecinfantry;
		VECVECINT vecarmdred;
		VECVECINT vecartillery;
		while (readCSV.inStream().good()) {
			vector<int> row = CCSVFile::csv_read_row_int(readCSV.inStream(), delimiter);
			CLogDlg::AddLogText(row);
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

