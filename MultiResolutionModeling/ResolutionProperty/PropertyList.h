#pragma once

//자산 리스트 정보 저장 객체
class CPropertyList
{
	//부대유형과 고/저해상도 별 저장
	SPrBaMap propertyMap[SPrMoTy::MT_SIZE][SPrMoTy::COMBATANT_SIZE];
	//부대유형 별 매핑 기본 값 저장
	ProductMappingVal productMappingVal[SPrMoTy::COMBATANT_SIZE];
	//부대유형과 자산타입 구분 자산정보 저장
	SPrMaKe keyList[SPrMoTy::COMBATANT_SIZE][SPrMoTy::PROD_SIZE];

public:
	//설정 아이템 랜덤 선택
	static vector<SVeCoIdVa> randomVec(vector<SVeCoIdVa> val);
	//자산 해상도변환 식
	static vector<int> resolutionChangeProperty(vector<int> ratioVal, float retenVec, float accRatioTotal);
public:
	CPropertyList();
	~CPropertyList();

	//자산정보 CSV파일 로딩
	void loadCSVFile(string fileName, SPrMoTy::COMBATANT combat);
	//자산정보 요구
	void getPropertyItem(SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass, vector<int>& lowKey, vector<int>& hiKey, SPrMa& prVal);
};
