#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	SPrBaMap propertyMap[SPrBa::MT_SIZE][SPrBa::COMBATANT_SIZE];

	ProductMappingVal productMappingVal;
public:
	CPropertyList();
	~CPropertyList();

	void initPropertyList(CString fileNm);

	void loadCSVFile(string fileName);
};