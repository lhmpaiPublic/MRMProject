#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];

	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];

	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];

	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];

	PropKeyMappString itemMappStr[SPrMoTy::MT_SIZE];

	void setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);

	bool getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);

	PropKeyMappListIndex itemListIndex[SPrMoTy::MT_SIZE];

	void setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);

	bool getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);

	vector<SVeCoIdVa> randomVec(vector<SVeCoIdVa> val);

public:
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
	static vector<SPrCoNa::HICOLUMNNAME> setHiAccListNum;

	static vector<SPrCoNa::LOWCOLUMNNAME> setLowRetenListNum;
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowAccListNum;

	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiRetenRitioNum;
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiLimtRitioNum;

	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowLimtRitioNum;
public:
	CPropertyList();
	~CPropertyList();

	void initPropertyList(CString fileNm);

	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	void lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	void hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	void resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
};

#define STPL_LOWR CPropertyList::setLowRetenListNum
#define STPL_LOWA CPropertyList::setLowAccListNum
#define STPL_HIR CPropertyList::setHiRetenListNum
#define STPL_HIA CPropertyList::setHiAccListNum
#define STPL_HIRR CPropertyList::setHiRetenRitioNum
#define STPL_HIRL CPropertyList::setHiLimtRitioNum