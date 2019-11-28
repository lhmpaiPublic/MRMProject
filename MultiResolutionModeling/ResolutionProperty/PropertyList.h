#pragma once


#include "PropertyKind.h"
class CPropertyList
{
	//부대유형과 고/저해상도 별 저장
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];
	//부대유형 별 매핑 기본 값 저장
	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];
	//부대유형과 자산타입 구분 자산정보 저장
	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];
	//고/저해상도 구분 자산 키 정보
	PropNameKeyVal itemKey[SPrMoTy::MT_SIZE];
	//고/저해상도 구분 자산 명 정보
	PropKeyMappString itemMappStr[SPrMoTy::MT_SIZE];

	//매핑키와 고/저해상도 구분 자산명 설정
	void setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName);

	//매핑키와 고/저해상도 구분 자산명 요구
	bool getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp);

	//고/저해상도 구분 자산 매핑 인덱스 정보
	PropKeyMappListIndex itemListIndex[SPrMoTy::MT_SIZE];

	//매핑키와 고/저해상도 구분 인덱스 설정
	void setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx);

	//매핑키와 고/저해상도 구분 인덱스 요구
	bool getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal);

	//설정 아이템 랜덤 선택
	vector<SVeCoIdVa> randomVec(vector<SVeCoIdVa> val);

public:
	//CListCtrl 정보
	//CListCtrl 계산할 고해상도 인가량 COL 정보
	static vector<SPrCoNa::HICOLUMNNAME> setHiRetenListNum;
	//CListCtrl 계산할 고해상도 인가량 COL 정보
	static vector<SPrCoNa::HICOLUMNNAME> setHiAccListNum;

	//CListCtrl 계산할 저해상도 보유량 COL 정보
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowRetenListNum;
	//CListCtrl 계산할 저해상도 인가량 COL 정보
	static vector<SPrCoNa::LOWCOLUMNNAME> setLowAccListNum;

	//CListCtrl 저해상도 계산할 고해상도 보유량 COL 정보
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiRetenRitioNum;
	//CListCtrl 저해상도 계산할 고해상도 설정량 COL 정보
	static vector<SPrCoNa::HIRATIOCOLUMNNAME> setHiLimtRitioNum;

	//CListCtrl 저해상도 계산할 저해상도 보유량 COL 정보
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowRetenRitioNum;
	//CListCtrl 저해상도 계산할 저해상도 설정량 COL 정보
	static vector<SPrCoNa::LOWRATIOCOLUMNNAME> setLowLimtRitioNum;
public:
	CPropertyList();
	~CPropertyList();

	//자산정보 CSV파일 로딩
	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);

	//고/저해상도 구분 자산 세팅
	void initPropertyItem(SPrMoTy::MODELTYPE modelType, CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//저해상도 구분 자산 CListCtrl 세팅
	void lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//저해상도 구분 비율 CListCtrl 세팅
	void lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//고해상도 구분 자산 CListCtrl 세팅
	void hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
	//고해상도 구분 비율 CListCtrl 세팅
	void hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);

	//해상도 변환을 위한 정보 세팅
	void resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass);
};

#define STPL_LOWR CPropertyList::setLowRetenListNum
#define STPL_LOWA CPropertyList::setLowAccListNum
#define STPL_HIR CPropertyList::setHiRetenListNum
#define STPL_HIA CPropertyList::setHiAccListNum
#define STPL_HIRR CPropertyList::setHiRetenRitioNum
#define STPL_HIRL CPropertyList::setHiLimtRitioNum