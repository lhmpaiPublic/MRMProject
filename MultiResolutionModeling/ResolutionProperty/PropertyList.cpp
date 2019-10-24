// PropertyList.cpp
//

#include "stdafx.h"
#include "PropertyList.h"
#include "../CSVFile.h"


CPropertyList::CPropertyList()
{

}
CPropertyList::~CPropertyList()
{

}

void CPropertyList::initPropertyList(CString fileNm)
{

}

void CPropertyList::loadCSVFile(string fileName)
{
	CCSVFile readCSV;

	char delimiter = ',';
	CLogDlg::AddLogText("<자산변환목록>");
	bool bNotValue = true;
	SPrBa::MODELTYPE modelType = SPrBa::MTLOW;
	SPrMa::MODELTYPE modelTypePrMa = SPrMa::MTLOW;
	if (readCSV.loadCSVFile(fileName)) {
		SPrClKi spba[SPrBa::PROD_SIZE];
		SPrClKi spbatop[SPrBa::PROD_SIZE];
		SPrClKi spco[SPrBa::PROD_SIZE];
		SPrClKi spcotop[SPrBa::PROD_SIZE];
		SPrClKi sppl[SPrBa::PROD_SIZE];
		SPrClKi sppltop[SPrBa::PROD_SIZE];
		SPrClKi spsq[SPrBa::PROD_SIZE];

		SPrMa prMa[SPrMa::PROD_SIZE];
		while (readCSV.inStream().good()) {
			vector<string> row = CCSVFile::csv_read_row(readCSV.inStream(), delimiter);
			CLogDlg::AddLogText(row, '	');
			if(row[0][0] != '#')
			{
				bNotValue = false;
				SPrNu inputVal;
				int dis = strtoul(row[0].c_str(), NULL, 10);

				inputVal.key = strtoul(row[1].c_str(), NULL, 10);
				inputVal.mappingNumber = strtoul(row[2].c_str(), NULL, 10);
				inputVal.strName = row[3].c_str();

				inputVal.retention = strtoul(row[4].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[4].c_str(), NULL, 10);
				spba[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[5].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[5].c_str(), NULL, 10);
				spbatop[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[6].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[6].c_str(), NULL, 10);
				spco[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[7].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[7].c_str(), NULL, 10);
				spcotop[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[8].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[8].c_str(), NULL, 10);
				sppl[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[9].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[9].c_str(), NULL, 10);
				sppltop[dis].setVal(inputVal);

				inputVal.retention = strtoul(row[10].c_str(), NULL, 10);
				inputVal.accreditation = strtoul(row[10].c_str(), NULL, 10);
				spsq[dis].setVal(inputVal);

				SPrVa prVa;
				prVa.key = strtoul(row[1].c_str(), NULL, 10);
				prVa.strName = row[3].c_str();
				
				prVa.accreditation = strtoul(row[4].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::BATTALION, prVa);

				prVa.accreditation = strtoul(row[5].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::BATTALION_CENTER, prVa);

				prVa.accreditation = strtoul(row[6].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::COMPANY, prVa);

				prVa.accreditation = strtoul(row[7].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::COMPANY_CENTER, prVa);

				prVa.accreditation = strtoul(row[8].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::PLATOON, prVa);

				prVa.accreditation = strtoul(row[9].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::PLATOON_CENTER, prVa);

				prVa.accreditation = strtoul(row[10].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMa::SQUAD, prVa);
			
			}
			else if(row[0][0] == '#' && bNotValue == false)
			{
				for (int i = 0; i < (int)SPrBa::PROD_SIZE; i++)
				{
					SPrBa prBaValType0;
					prBaValType0.setValBattalion(MAKEMIL1(SPrBa::MY0), spba[0]);

					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY0, SPrBa::LV1), spbatop[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY1, SPrBa::LV1), spco[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY2, SPrBa::LV1), spco[i]);
					prBaValType0.setValCompany(MAKEMIL2(SPrCo::MY3, SPrBa::LV1), spco[i]);

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

					propertyMap[modelType][SPrBa::INFANTRY].SetAt((SPrBa::PRODUCTTYPE)i, prBaValType0);
				}

				modelType = SPrBa::MTHI;
				modelTypePrMa = SPrMa::MTHI;
				bNotValue = true;

				for (int i = 0; i < (int)SPrBa::PROD_SIZE; i++)
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
		for (int i = 0; i < (int)SPrMa::PROD_SIZE; i++)
		{
			productMappingVal.SetAt((SPrMa::PRODUCTTYPE)i, prMa[i]);
		}
		readCSV.unloadCSVFile();
	}
}