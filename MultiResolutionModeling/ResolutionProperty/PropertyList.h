#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];

	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];

	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];

	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];
public:
	CPropertyList();
	~CPropertyList();

	void initPropertyList(CString fileNm);

	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
};