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

				//inputVal.retention = strtoul(row[4].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[4].c_str(), NULL, 10);
				//spba[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[5].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[5].c_str(), NULL, 10);
				//spbatop[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[6].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[6].c_str(), NULL, 10);
				//spco[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[7].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[7].c_str(), NULL, 10);
				//spcotop[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[8].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[8].c_str(), NULL, 10);
				//sppl[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[9].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[9].c_str(), NULL, 10);
				//sppltop[dis].setVal(inputVal);

				//inputVal.retention = strtoul(row[10].c_str(), NULL, 10);
				//inputVal.accreditation = strtoul(row[10].c_str(), NULL, 10);
				//spsq[dis].setVal(inputVal);

				SPrVa prVa;
				prVa.key = strtoul(row[1].c_str(), NULL, 10);
				prVa.mappKey = strtoul(row[2].c_str(), NULL, 10);
				prVa.strName = row[3].c_str();

				for (int rowVal = 4, cbc = 0; rowVal < (int)row.size(); rowVal++, cbc++)
				{
					prVa.accreditation = strtoul(row[rowVal].c_str(), NULL, 10);
					prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMBATANTCLASS(SPrMoTy::BATTALION-cbc), prVa);
				}
				
				//prVa.accreditation = strtoul(row[4].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::BATTALION, prVa);

				//prVa.accreditation = strtoul(row[5].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::BATTALION_CENTER, prVa);

				//prVa.accreditation = strtoul(row[6].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMPANY, prVa);

				//prVa.accreditation = strtoul(row[7].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMPANY_CENTER, prVa);

				//prVa.accreditation = strtoul(row[8].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::PLATOON, prVa);

				//prVa.accreditation = strtoul(row[9].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::PLATOON_CENTER, prVa);

				//prVa.accreditation = strtoul(row[10].c_str(), NULL, 10);
				//prMa[dis].setVal(modelTypePrMa, SPrMoTy::SQUAD, prVa);
			
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

void CPropertyList::initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	switch(modelType)
	{
	case SPrMoTy::MTLOW: lowPropertyItem(listCtrl, combat, propType, cbtClass);
		break;
	case SPrMoTy::MTHI: hiPropertyItem(listCtrl, combat, propType, cbtClass);
		break;
	default:
		break;
	}
}

void CPropertyList::lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	CLogDlg::AddLogText("<Key 값>");
	vector<int> lowKey = keyList[combat][propType].getMappKey(SPrMoTy::MTLOW);
	CLogDlg::initStream();
	CLogDlg::insertStream("보병 병력 low 값 :");
	CLogDlg::insertStreamVec(lowKey, '	');
	CLogDlg::addLogTextStream();
	vector<int> hiKey = keyList[combat][propType].getMappKey(SPrMoTy::MTHI);
	CLogDlg::initStream();
	CLogDlg::insertStream("보병 병력 hi 값 :");
	CLogDlg::insertStreamVec(hiKey, '	');
	CLogDlg::addLogTextStream();

	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, 0, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 1, _T("설정량"));
	listCtrl->SetItemColours( nUser, 1, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 2, _T("인가량"));
	listCtrl->SetItemColours( nUser, 2, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 3, _T("보유량"));
	listCtrl->SetItemColours( nUser, 3, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 4, _T("인가량"));
	listCtrl->SetItemColours( nUser, 4, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 5, _T("보유량"));
	listCtrl->SetItemColours( nUser, 5, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 6, _T("인가량"));
	listCtrl->SetItemColours( nUser, 6, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	SPrMa prVal;
	productMappingVal[combat].Lookup(propType, prVal);
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		CLogDlg::initStream();
		CLogDlg::insertStream("map key :");
		CLogDlg::insertStream(lowKey[i], '	');
		CLogDlg::addLogTextStream();

		vector<SPrVa> val = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		for (int iv = 0; iv < (int)val.size(); iv++)
		{
			CLogDlg::initStream();
			CLogDlg::insertStream("low val :");
			CLogDlg::insertStream(val[iv].strLogVal(), '	');
			CLogDlg::addLogTextStream();
			int nUser = listCtrl->AddItem(val[iv].strName);
			listCtrl->SetItemColours( nUser, 0, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemFormat( nUser, 1, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, 1, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ) );
			std::wstringstream strStream;
			strStream.str(L"");
			strStream << val[iv].accreditation;
			listCtrl->SetItemText( nUser, 1, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 2, strStream.str().c_str());

			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, 3, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 4, strStream.str().c_str());

			keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, 5, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 6, strStream.str().c_str());
		}

	}
}

void CPropertyList::hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	vector<int> lowKey = keyList[combat][propType].getMappKey(SPrMoTy::MTLOW);
	vector<int> hiKey = keyList[combat][propType].getMappKey(SPrMoTy::MTHI);

	int nUser = listCtrl->AddItem(_T("모체자산명"));
	listCtrl->SetItemColours( nUser, 0, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 1, _T("변환자산명"));
	listCtrl->SetItemColours( nUser, 1, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 2, _T("보유량"));
	listCtrl->SetItemColours( nUser, 2, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 3, _T("인가량"));
	listCtrl->SetItemColours( nUser, 3, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 4, _T("보유량"));
	listCtrl->SetItemColours( nUser, 4, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 5, _T("보유량"));
	listCtrl->SetItemColours( nUser, 5, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 6, _T("보유량"));
	listCtrl->SetItemColours( nUser, 6, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 7, _T("보유량"));
	listCtrl->SetItemColours( nUser, 7, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	SPrMa prVal;
	productMappingVal[combat].Lookup(propType, prVal);
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		CLogDlg::initStream();
		CLogDlg::insertStream("map key :");
		CLogDlg::insertStream(lowKey[i], '	');
		CLogDlg::addLogTextStream();

		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTHI);
		if(lowVal.size() <= hiVal.size())
		{
			for (int iv = 0; iv < (int)hiVal.size(); iv++)
			{
				CLogDlg::initStream();
				CLogDlg::insertStream("hi val :");
				CLogDlg::insertStream(hiVal[iv].strLogVal(), '	');
				CLogDlg::addLogTextStream();
				int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");
				listCtrl->SetItemColours( nUser, 0, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, 1, hiVal[iv].strName);
				listCtrl->SetItemColours( nUser, 1, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				std::wstringstream strStream;
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, 2, strStream.str().c_str());
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, 3, strStream.str().c_str());
			}
		}
		else
		{
			for (int iv = 0; iv < (int)lowVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(lowVal[iv].strName);
				listCtrl->SetItemColours( nUser, 0, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemColours( nUser, 1, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				if(iv == 0)
				{
					listCtrl->SetItemText( nUser, 1, hiVal[iv].strName);
					std::wstringstream strStream;
					strStream.str(L"");
					strStream << hiVal[0].accreditation;
					listCtrl->SetItemText( nUser, 2, strStream.str().c_str());
					strStream.str(L"");
					strStream << hiVal[0].accreditation;
					listCtrl->SetItemText( nUser, 3, strStream.str().c_str());
				}				
			}
		}		
	}
}