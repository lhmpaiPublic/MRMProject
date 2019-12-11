#pragma once

class CPropertyList
{
	//�δ������� ��/���ػ� �� ����
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];
	//�δ����� �� ���� �⺻ �� ����
	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];
	//�δ������� �ڻ�Ÿ�� ���� �ڻ����� ����
	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];

public:
	//���� ������ ���� ����
	static vector<SVeCoIdVa> randomVec(vector<SVeCoIdVa> val);
public:
	CPropertyList();
	~CPropertyList();

	//�ڻ����� CSV���� �ε�
	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	void getLowPropertyItem(SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass, vector<int>& lowKey, vector<int>& hiKey, SPrMa& prVal);
};
