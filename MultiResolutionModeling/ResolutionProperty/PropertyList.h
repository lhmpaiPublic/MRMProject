#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];

	ProductMappingVal productMappingVal;

	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];
public:
	CPropertyList();
	~CPropertyList();

	void initPropertyList(CString fileNm);

	void loadCSVFile(string fileName);

	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl);

	void lowPropertyItem(CListCtrl* listCtrl);
	void hiPropertyItem(CListCtrl* listCtrl);
};