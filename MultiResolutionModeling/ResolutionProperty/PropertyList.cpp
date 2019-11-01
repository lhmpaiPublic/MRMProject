// PropertyList.cpp
//

#include "stdafx.h"
#include "PropertyList.h"
#include "../CSVFile.h"


CPropertyList::CPropertyList()
{
	itemKey[SPrMoTy::MTLOW].RemoveAll();
	itemKey[SPrMoTy::MTHI].RemoveAll();
	itemMappStr[SPrMoTy::MTLOW].RemoveAll();
	itemMappStr[SPrMoTy::MTHI].RemoveAll();
	itemListIndex[SPrMoTy::MTLOW].RemoveAll();
	itemListIndex[SPrMoTy::MTHI].RemoveAll();
}
CPropertyList::~CPropertyList()
{

}

void CPropertyList::setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName)
{
	PropKeyMappString::CPair* pair = itemMappStr[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(propName);
	}
	else
	{
		SPrKeMaSt keyMappStr;
		keyMappStr.setVal(propName);
		itemMappStr[modelType].SetAt(mappKey, keyMappStr);
	}
}

bool CPropertyList::getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp)
{
	PropKeyMappString::CPair* pair = itemMappStr[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		strProp = pair->m_value.getVal();
	}
	return (0 != strProp.size());
}

void CPropertyList::setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx)
{
	PropKeyMappListIndex::CPair* pair = itemListIndex[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(idx);
	}
	else
	{
		SPrKeMaLiIn keyMapp;
		keyMapp.setVal(idx);
		itemListIndex[modelType].SetAt(mappKey, keyMapp);
	}
}

bool CPropertyList::getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal)
{
	PropKeyMappListIndex::CPair* pair = itemListIndex[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		idxVal = pair->m_value.getVal();
	}
	return (0 != idxVal.size());
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
	vector<int> lowKey = keyList[combat][propType].getMappKey(SPrMoTy::MTLOW);
	vector<int> hiKey = keyList[combat][propType].getMappKey(SPrMoTy::MTHI);

	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_03, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_04, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_05, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_06, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_07, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_08, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_09, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_09, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_10, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_10, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	SPrMa prVal;
	productMappingVal[combat].Lookup(propType, prVal);
	itemKey[SPrMoTy::MTLOW].RemoveAll();
	itemMappStr[SPrMoTy::MTLOW].RemoveAll();
	itemListIndex[SPrMoTy::MTLOW].RemoveAll();
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> val = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		for (int iv = 0; iv < (int)val.size(); iv++)
		{
			int nUser = listCtrl->AddItem(val[iv].strName);
			//키 저장 LOW
			SPrKe prKe;
			prKe.setVal(val[iv].mappKey, val[iv].key, nUser);
			itemKey[SPrMoTy::MTLOW].SetAt(val[iv].strName, prKe);
			//mapping key to product Name
			setPropKeyMappString(val[iv].mappKey, SPrMoTy::MTLOW, val[iv].strName);
			setPropKeyMappListIndex(val[iv].mappKey, SPrMoTy::MTLOW, nUser);
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
			
			std::wstringstream strStream;
			strStream.str(L"");
			strStream << val[iv].accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LMN_01, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );

			listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_02, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );

			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_03, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_03, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_04, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_04, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );

			keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_05, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_05, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_06, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_06, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_07, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_07, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_08, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_08, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_09, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_09, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_10, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_10, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
		}

	}
}

void CPropertyList::hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	vector<int> lowKey = keyList[combat][propType].getMappKey(SPrMoTy::MTLOW);
	vector<int> hiKey = keyList[combat][propType].getMappKey(SPrMoTy::MTHI);

	int nUser = listCtrl->AddItem(_T("모체자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, _T("변환자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	
	itemKey[SPrMoTy::MTHI].RemoveAll();
	itemMappStr[SPrMoTy::MTHI].RemoveAll();
	itemListIndex[SPrMoTy::MTHI].RemoveAll();
	SPrMa prVal;
	productMappingVal[combat].Lookup(propType, prVal);
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(hiKey[i], cbtClass, SPrMoTy::MTHI);
		
		if(lowVal.size() <= hiVal.size())
		{
			for (int iv = 0; iv < (int)hiVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");

				SPrKe prKe;
				prKe.setVal(hiVal[iv].mappKey, hiVal[iv].key, nUser);
				itemKey[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
				//mapping key to product Name
				setPropKeyMappString(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
				setPropKeyMappListIndex(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, hiVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				std::wstringstream strStream;
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
			}
		}
		else
		{
			for (int iv = 0; iv < (int)lowVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(lowVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				
				if(iv == 0)
				{
					SPrKe prKe;
					prKe.setVal(hiVal[iv].mappKey, hiVal[iv].key, nUser);
					itemKey[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
					//mapping key to product Name
					setPropKeyMappString(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
					setPropKeyMappListIndex(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

					listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, hiVal[iv].strName);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					std::wstringstream strStream;
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				}				
			}
		}		
	}
}

void CPropertyList::resolutionChangeProperty(CListCtrl* listCtrlLow, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	SVeStIn listItem;
	for (int i = 1; i < (int)listCtrlLow->GetItemCount(); i++)
	{
		listItem.setVal(listCtrlLow->GetItemText(i, SPrCoNa::LMN_00),
		strtoul(CStringA(listCtrlLow->GetItemText(i, SPrCoNa::LMN_01)).GetBuffer(), NULL, 10));
	}
	CLogDlg::AddLogText(listItem.getIVal(), '	');
	CLogDlg::AddLogText(listItem.getSVal(), '	');

	PropNameKeyVal::CPair* pair;
	POSITION pos = itemKey[SPrMoTy::MTLOW].GetStartPosition();
	while(pos)
	{
		pair = NULL;
		osItemText.str(_T(""));
		pair = itemKey[SPrMoTy::MTLOW].GetNext(pos);
		CString str = pair->m_key;
		osItemText << _T("LOW ITEM : ") << str.GetBuffer() << _T("	colNum : ") << pair->m_value.getColNum() <<  _T("	mappKey : ") << pair->m_value.getMappKey() <<  _T("	primkey : ") << pair->m_value.getPrimKey() ;
		CLogDlg::AddLogText(osItemText.str().c_str());

		vector<CString> strProp;
		if(getPropKeyMappString(pair->m_value.getMappKey(), SPrMoTy::MTLOW, strProp))
		{
			CLogDlg::AddLogText(_T("LOW Prop Name : "));
			CLogDlg::AddLogText(strProp);
		}

		vector<int> idxList;
		if(getPropKeyMappListIndex(pair->m_value.getMappKey(), SPrMoTy::MTLOW, idxList))
		{
			CLogDlg::AddLogText(_T("LOW List Index : "));
			CLogDlg::AddLogText(idxList);
		}
	}

	pos = itemKey[SPrMoTy::MTHI].GetStartPosition();
	while(pos)
	{
		pair = NULL;
		osItemText.str(_T(""));
		pair = itemKey[SPrMoTy::MTHI].GetNext(pos);
		CString str = pair->m_key;
		osItemText << _T("HI ITEM : ") << str.GetBuffer() << _T("	colNum : ") << pair->m_value.getColNum() <<  _T("	mappKey : ") << pair->m_value.getMappKey() <<  _T("	primkey : ") << pair->m_value.getPrimKey() ;
		CLogDlg::AddLogText(osItemText.str().c_str());

		vector<CString> strProp;
		if(getPropKeyMappString(pair->m_value.getMappKey(), SPrMoTy::MTHI, strProp))
		{
			CLogDlg::AddLogText(_T("HI Prop Name : "));
			CLogDlg::AddLogText(strProp);

		}

		vector<int> idxList;
		if(getPropKeyMappListIndex(pair->m_value.getMappKey(), SPrMoTy::MTHI, idxList))
		{
			CLogDlg::AddLogText(_T("HI List index : "));
			CLogDlg::AddLogText(idxList);

		}
	}
	
	for (int idxList = 0; idxList < listItem.getSize(); idxList++)
	{
		SPrKe val;
		if(itemKey[SPrMoTy::MTLOW].Lookup(listItem.getSVal(idxList), val))
		{
			vector<int> idxListHiVec;
			vector<int> idxListLowVec;
			getPropKeyMappListIndex(val.getMappKey(), SPrMoTy::MTLOW, idxListLowVec);
			if(getPropKeyMappListIndex(val.getMappKey(), SPrMoTy::MTHI, idxListHiVec))
			{

				for (int idxHiVec = 0; idxHiVec < (int)idxListHiVec.size(); idxHiVec++)
				{
					strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHiVec], SPrCoNa::HMN_03)).GetBuffer(), NULL, 10);
				}

				if(idxListHiVec.size() <= idxListLowVec.size())
				{
					int itemNum = 0;
					for (int idxLowVec = 0; idxLowVec < (int)idxListLowVec.size(); idxLowVec++)
					{
						itemNum += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLowVec], SPrCoNa::LMN_01)).GetBuffer(), NULL, 10);
					}
					osItemText.str(_T(""));
					osItemText << itemNum;
					listCtrlHi->SetItemText(idxListHiVec[0] , SPrCoNa::HMN_02, osItemText.str().c_str());
					if(0 == itemNum)
					{
						for (int idx = 0; idx < (int)idxListHiVec.size(); idx++)
						{
							listCtrlHi->SetItemText(idxListHiVec[0] , SPrCoNa::HMN_04, osItemText.str().c_str());
							listCtrlHi->SetItemText(idxListHiVec[0] , SPrCoNa::HMN_06, osItemText.str().c_str());
							listCtrlHi->SetItemText(idxListHiVec[0] , SPrCoNa::HMN_08, osItemText.str().c_str());
							listCtrlHi->SetItemText(idxListHiVec[0] , SPrCoNa::HMN_10, osItemText.str().c_str());
						}
					}
				}
				else
				{
					
				}
			}
		}
	}
}
