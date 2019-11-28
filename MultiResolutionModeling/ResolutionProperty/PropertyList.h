#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	//�δ������� ��/���ػ� �� ����
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];
	//�δ����� �� ���� �⺻ �� ����
	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];
	//�δ������� �ڻ�Ÿ�� ���� �ڻ����� ����
	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];
	//��/���ػ� ���� �ڻ� Ű ����
	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];
	//��/���ػ� ���� �ڻ� �� ����
	PropKeyMappString itemMappStr[SPrMoTy::MT_SIZE];

	//����Ű�� ��/���ػ� ���� �ڻ�� ����
	void setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);

	//����Ű�� ��/���ػ� ���� �ڻ�� �䱸
	bool getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);

	//��/���ػ� ���� �ڻ� ���� �ε��� ����
	PropKeyMappListIndex itemListIndex[SPrMoTy::MT_SIZE];

	//����Ű�� ��/���ػ� ���� �ε��� ����
	void setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);

	//����Ű�� ��/���ػ� ���� �ε��� �䱸
	bool getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);

	//���� ������ ���� ����
	vector<SVeCoIdVa> randomVec(vector<SVeCoIdVa> val);

public:
	//CListCtrl ����
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::HICOLUMNNAME> setHiAccListNum;

	//CListCtrl ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowRetenListNum;
	//CListCtrl ����� ���ػ� �ΰ��� COL ����
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowAccListNum;

	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiRetenRitioNum;
	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiLimtRitioNum;

	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl ���ػ� ����� ���ػ� ������ COL ����
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowLimtRitioNum;
public:
	CPropertyList();
	~CPropertyList();

	//�ڻ����� CSV���� �ε�
	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	//��/���ػ� ���� �ڻ� ����
	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//���ػ� ���� �ڻ� CListCtrl ����
	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� ���� CListCtrl ����
	void lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� �ڻ� CListCtrl ����
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//���ػ� ���� ���� CListCtrl ����
	void hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//�ػ� ��ȯ�� ���� ���� ����
	void resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
};

#define STPL_LOWR CPropertyList::setLowRetenListNum
#define STPL_LOWA CPropertyList::setLowAccListNum
#define STPL_HIR CPropertyList::setHiRetenListNum
#define STPL_HIA CPropertyList::setHiAccListNum
#define STPL_HIRR CPropertyList::setHiRetenRitioNum
#define STPL_HIRL CPropertyList::setHiLimtRitioNum