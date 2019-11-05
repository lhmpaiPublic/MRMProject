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
	CPropertyList();
	~CPropertyList();

	void initPropertyList(CString fileNm);

	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	void resolutionChangeProperty(CListCtrl* listCtrlLow, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
};