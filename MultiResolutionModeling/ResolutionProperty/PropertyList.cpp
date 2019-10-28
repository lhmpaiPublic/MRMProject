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
				keyList[SPrMoTy::INFANTRY][dis].setVal(modelType, strtoul(row[2].c_str(), NULL, 10), strtoul(row[1].c_str(), NULL, 10));

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
				prVa.mappKey = strtoul(row[2].c_str(), NULL, 10);
				prVa.strName = row[3].c_str();
				
				prVa.accreditation = strtoul(row[4].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::BATTALION, prVa);

				prVa.accreditation = strtoul(row[5].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::BATTALION_CENTER, prVa);

				prVa.accreditation = strtoul(row[6].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMPANY, prVa);

				prVa.accreditation = strtoul(row[7].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::COMPANY_CENTER, prVa);

				prVa.accreditation = strtoul(row[8].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::PLATOON, prVa);

				prVa.accreditation = strtoul(row[9].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::PLATOON_CENTER, prVa);

				prVa.accreditation = strtoul(row[10].c_str(), NULL, 10);
				prMa[dis].setVal(modelTypePrMa, SPrMoTy::SQUAD, prVa);
			
			}
			else if(row[0][0] == '#' && bNotValue == false)
			{
				for (int i = 0; i < (int)SPrMoTy::PROD_SIZE; i++)
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

					propertyMap[modelType][SPrMoTy::INFANTRY].SetAt((SPrMoTy::PRODUCTTYPE)i, prBaValType0);
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
			productMappingVal.SetAt((SPrMoTy::PRODUCTTYPE)i, prMa[i]);
		}
		readCSV.unloadCSVFile();
	}
}

void CPropertyList::initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl)
{
	switch(modelType)
	{
	case SPrMoTy::MTLOW: lowPropertyItem(listCtrl);
		break;
	case SPrMoTy::MTHI: hiPropertyItem(listCtrl);
		break;
	default:
		break;
	}
}

void CPropertyList::lowPropertyItem(CListCtrl* listCtrl)
{
	CLogDlg::AddLogText("<Key 값>");
	vector<int> lowKey = keyList[SPrMoTy::INFANTRY][SPrMoTy::TY0].getMappKey(SPrMoTy::MTLOW);
	CLogDlg::initStream();
	CLogDlg::insertStream("보병 병력 low 값 :");
	CLogDlg::insertStreamVec(lowKey, '	');
	CLogDlg::addLogTextStream();
	vector<int> hiKey = keyList[SPrMoTy::INFANTRY][SPrMoTy::TY0].getMappKey(SPrMoTy::MTLOW);
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
	productMappingVal.Lookup(SPrMoTy::TY0, prVal);
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		CLogDlg::initStream();
		CLogDlg::insertStream("map key :");
		CLogDlg::insertStream(lowKey[i], '	');
		CLogDlg::addLogTextStream();

		vector<SPrVa> val = prVal.getVal(lowKey[i], SPrMoTy::BATTALION, SPrMoTy::MTLOW);
		for (int iv = 0; iv < (int)val.size(); iv++)
		{
			CLogDlg::initStream();
			CLogDlg::insertStream("low val :");
			CLogDlg::insertStream(val[iv].strLogVal(), '	');
			CLogDlg::addLogTextStream();
			int nUser = listCtrl->AddItem(val[iv].strName);
			listCtrl->SetItemFormat( nUser, 1, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			std::wstringstream strStream;
			strStream.str(L"");
			strStream << val[iv].accreditation;
			listCtrl->SetItemText( nUser, 1, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 2, strStream.str().c_str());

			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::BATTALION_CENTER, SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, 3, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 4, strStream.str().c_str());

			keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMPANY, SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, 5, strStream.str().c_str());
			listCtrl->SetItemText( nUser, 6, strStream.str().c_str());
		}

	}
}

void CPropertyList::hiPropertyItem(CListCtrl* listCtrl)
{
	CLogDlg::AddLogText("<Key 값>");
	vector<int> lowKey = keyList[SPrMoTy::INFANTRY][SPrMoTy::TY0].getMappKey(SPrMoTy::MTLOW);
	CLogDlg::initStream();
	CLogDlg::insertStream("보병 병력 low 값 :");
	CLogDlg::insertStreamVec(lowKey, '	');
	CLogDlg::addLogTextStream();
	vector<int> hiKey = keyList[SPrMoTy::INFANTRY][SPrMoTy::TY0].getMappKey(SPrMoTy::MTLOW);
	CLogDlg::initStream();
	CLogDlg::insertStream("보병 병력 hi 값 :");
	CLogDlg::insertStreamVec(hiKey, '	');
	CLogDlg::addLogTextStream();

	int nUser = listCtrl->AddItem(_T("모체자산명"));
	listCtrl->SetItemColours( nUser, 0, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 1, _T("변환자산명"));
	listCtrl->SetItemColours( nUser, 1, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 2, _T("설정량"));
	listCtrl->SetItemColours( nUser, 2, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 3, _T("인가량"));
	listCtrl->SetItemColours( nUser, 3, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 4, _T("인가량"));
	listCtrl->SetItemColours( nUser, 4, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 5, _T("인가량"));
	listCtrl->SetItemColours( nUser, 5, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 6, _T("인가량"));
	listCtrl->SetItemColours( nUser, 6, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, 7, _T("인가량"));
	listCtrl->SetItemColours( nUser, 7, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	listCtrl->SetColumn(2, _T("22222"));

	SPrMa prVal;
	productMappingVal.Lookup(SPrMoTy::TY0, prVal);
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		CLogDlg::initStream();
		CLogDlg::insertStream("map key :");
		CLogDlg::insertStream(lowKey[i], '	');
		CLogDlg::addLogTextStream();

		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], SPrMoTy::BATTALION, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(lowKey[i], SPrMoTy::BATTALION, SPrMoTy::MTHI);
		for (int iv = 0; iv < (int)hiVal.size(); iv++)
		{
			CLogDlg::initStream();
			CLogDlg::insertStream("hi val :");
			CLogDlg::insertStream(hiVal[iv].strLogVal(), '	');
			CLogDlg::addLogTextStream();
			int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");
			listCtrl->SetItemText( nUser, 1, hiVal[iv].strName);
			std::wstringstream strStream;
			strStream.str(L"");
			strStream << hiVal[iv].accreditation;
			listCtrl->SetItemText( nUser, 2, strStream.str().c_str());
			strStream.str(L"");
			strStream << hiVal[iv].accreditation;
			listCtrl->SetItemText( nUser, 3, strStream.str().c_str());
		}
	}
}