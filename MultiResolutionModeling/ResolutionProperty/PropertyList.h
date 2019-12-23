#pragma once

//�ڻ� ����Ʈ ���� ���� ��ü
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
	//�ڻ� �ػ󵵺�ȯ ��
	static vector<int> resolutionChangeProperty(vector<int> ratioVal, float retenVec, float accRatioTotal);
public:
	CPropertyList();
	~CPropertyList();

	//�ڻ����� CSV���� �ε�
	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);
	//�ڻ����� �䱸
	void getPropertyItem(SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass, vector<int>& lowKey, vector<int>& hiKey, SPrMa& prVal);
};
