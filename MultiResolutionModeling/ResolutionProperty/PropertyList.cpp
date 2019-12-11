// PropertyList.cpp
//

#include "stdafx.h"
#include "PropertyList.h"

CPropertyList::CPropertyList()
{
	srand((DWORD)time(NULL));
}
CPropertyList::~CPropertyList()
{

}

void CPropertyList::loadCSVFile(string fileName, SPrMoTy::COMBATANT combat)
{
	CCSVFile readCSV;

	char delimiter = ',';
	CLogDlg::AddLogText("<자산변환목록>");
	bool bNotValue = true;
	SPrMoTy::MODELTYPE modelType = SPrMoTy::MTLOW;
	SPrMoTy::MODELTYPE modelTypePrMa = SPrMoTy::MTLOW;
	if (readCSV.loadCSVFile(fileName)) {
		SPrClKi spba[SPrMoTy::PROD_SIZE];
		SPrClKi spbatop[SPrMoTy::PROD_SIZE];
		SPrClKi spco[SPrMoTy::PROD_SIZE];
		SPrClKi spcotop[SPrMoTy::PROD_SIZE];
		SPrClKi sppl[SPrMoTy::PROD_SIZE];
		SPrClKi sppltop[SPrMoTy::PROD_SIZE];
		SPrClKi spsq[SPrMoTy::PROD_SIZE];

		SPrMa prMa[SPrMoTy::PROD_SIZE];
		while (readCSV.inStream().good()) {
			vector<string> row = CCSVFile::csv_read_row(readCSV.inStream(), delimiter);
			CLogDlg::AddLogText(row, '	');
			if(row[0][0] != '#')
			{
				bNotValue = false;
				SPrNu inputVal;
				int dis = strtoul(row[0].c_str(), NULL, 10);
				//검색용 키 저장
				keyList[combat][dis].setVal(modelType, strtoul(row[2].c_str(), NULL, 10), strtoul(row[1].c_str(), NULL, 10));

				inputVal.key = strtoul(row[1].c_str(), NULL, 10);
				inputVal.mappingNumber = strtoul(row[2].c_str(), NULL, 10);
				inputVal.strName = row[3].c_str();

				for (int rowVal = 4; rowVal < (int)row.size(); rowVal++)
				{
					inputVal.retention = strtoul(row[rowVal].c_str(), NULL, 10);
					inputVal.accreditation = strtoul(row[rowVal].c_str(), NULL, 10);
					spba[dis].setVal(inputVal);
				}

				SPrVa prVa;
				prVa.key = strtoul(row[1].c_str(), NULL, 10);
				prVa.mappKey = strtoul(row[2].c_str(), NULL, 10);
				prVa.strName = row[3].c_str();

				for (int rowVal = 4, cbc = 0; rowVal < (int)row.size(); rowVal++, cbc++)
				{
					prVa.accreditation = strtoul(row[rowVal].c_str(), NULL, 10);
					prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMBATANTCLASS(SPrMoTy::BATTALION-cbc), prVa);
				}
				
			
			}
			else if(row[0][0] == '#' && bNotValue == false)
			{
				for (int i = 0; i < (int)SPrMoTy::PROD_SIZE; i++)
				{
					SPrBa prBaValType0;
					prBaValType0.setValBattalion(MAKEMIL1(SPrBa::MY0), spba[i]);

					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY0, SPrBa::LV1), spbatop[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY1, SPrBa::LV1), spco[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY2, SPrBa::LV1), spco[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY3, SPrBa::LV1), spco[i]);

					if((SPrMoTy::INFANTRY == combat) || (SPrMoTy::ARMORED == combat))
					{
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY0, SPrCo::LV1, SPrBa::LV1), spcotop[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY1, SPrCo::LV1, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY2, SPrCo::LV1, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY3, SPrCo::LV1, SPrBa::LV1), sppl[i]);

						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY0, SPrCo::LV2, SPrBa::LV1), spcotop[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY1, SPrCo::LV2, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY2, SPrCo::LV2, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY3, SPrCo::LV2, SPrBa::LV1), sppl[i]);

						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY0, SPrCo::LV3, SPrBa::LV1), spcotop[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY1, SPrCo::LV3, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY2, SPrCo::LV3, SPrBa::LV1), sppl[i]);
						prBaValType0.setValPlatoon(MAKEMIL3(SPrPl::MY3, SPrCo::LV3, SPrBa::LV1), sppl[i]);
					}

					if(SPrMoTy::INFANTRY == combat)
					{
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV1, SPrCo::LV1, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV1, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV1, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV1, SPrCo::LV1, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV2, SPrCo::LV1, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV2, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV2, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV2, SPrCo::LV1, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV3, SPrCo::LV1, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV3, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV3, SPrCo::LV1, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV3, SPrCo::LV1, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV1, SPrCo::LV2, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV1, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV1, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV1, SPrCo::LV2, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV2, SPrCo::LV2, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV2, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV2, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV2, SPrCo::LV2, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV3, SPrCo::LV2, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV3, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV3, SPrCo::LV2, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV3, SPrCo::LV2, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV1, SPrCo::LV3, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV1, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV1, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV1, SPrCo::LV3, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV2, SPrCo::LV3, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV2, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV2, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV2, SPrCo::LV3, SPrBa::LV1), spsq[i]);

						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY0, SPrPl::LV3, SPrCo::LV3, SPrBa::LV1), sppltop[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY1, SPrPl::LV3, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY2, SPrPl::LV3, SPrCo::LV3, SPrBa::LV1), spsq[i]);
						prBaValType0.setValSquad(MAKEMIL4(SPrSq::MY3, SPrPl::LV3, SPrCo::LV3, SPrBa::LV1), spsq[i]);
					}
					propertyMap[modelType][combat].SetAt((SPrMoTy::PRODUCTTYPE)i, prBaValType0);
				}

				modelType = SPrMoTy::MTHI;
				modelTypePrMa = SPrMoTy::MTHI;
				bNotValue = true;

				for (int i = 0; i < (int)SPrMoTy::PROD_SIZE; i++)
				{
					spba[i].clearVal();
					spbatop[i].clearVal();
					spco[i].clearVal();
					spcotop[i].clearVal();
					sppl[i].clearVal();
					sppltop[i].clearVal();
					spsq[i].clearVal();
				}
			}

		}
		for (int i = 0; i < (int)SPrMoTy::PROD_SIZE; i++)
		{
			productMappingVal[combat].SetAt((SPrMoTy::PRODUCTTYPE)i, prMa[i]);
		}
		readCSV.unloadCSVFile();
	}
}

void CPropertyList::getLowPropertyItem(SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass, vector<int>& lowKey, vector<int>& hiKey, SPrMa& prVal)
{
	lowKey = keyList[combat][propType].getMappKey(SPrMoTy::MTLOW);
	hiKey = keyList[combat][propType].getMappKey(SPrMoTy::MTHI);
	productMappingVal[combat].Lookup(propType, prVal);
}

vector<SVeCoIdVa> CPropertyList::randomVec(vector<SVeCoIdVa> val)
{
	vector<SVeCoIdVa> rVal;

	while(val.size())
	{
		int num = rand() % val.size();
		rVal.push_back(val[num]);
		val.erase(val.begin()+num);
	}
	return rVal;
}
