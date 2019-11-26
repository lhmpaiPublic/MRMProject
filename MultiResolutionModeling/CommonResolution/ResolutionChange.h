#pragma once

//위치변환 응용객체
class CResolutionChange
{
public:
	CResolutionChange();
	~CResolutionChange();
public:
	//부대 진행 방향 Type 정의
	enum DIRECTIONTYPE
	{
		NONE_DIRECTION = 0,
		N_DIRECTION,			//북
		NE_DIRECTION,			//북동
		E_DIRECTION,			//동
		SE_DIRECTION,			//남동
		S_DIRECTION,			//남
		SW_DIRECTION,			//남서
		W_DIRECTION,			//서
		NW_DIRECTION			//북서
	};
	static CString strDirectionType(CResolutionChange::DIRECTIONTYPE em);
	static vector<CString> strDirectionType();
	static CResolutionChange::DIRECTIONTYPE emDirectionType(int selNum);

	//위치 계산 Type 정의
	enum CALCPOSITIONTYPE
	{
		CALC_POS0 = 0,
		CALC_POS1,
		CALC_POS2,
		CALC_POS3,
		CALC_POS4,
		CALC_POS5,
		CALC_POS6,
		CALC_POS7,
		CALC_POS8,
		CALC_POS9,
		CALC_POS10,
		CALC_POS11,
	};

	//SIZE VECTOR Type 정의
	enum SIZEVECTORTYPE
	{
		SIZEVEC_WIDTH = 0,
		SIZEVEC_HIGHT,
		SIZEVEC_SIZE
	};

	enum SIZEVECTORBUTTOMTYPE
	{
		SIZEVECBT_WIDTH = 2,
		SIZEVECBT_HIGHT,
		SIZEVECBT_SIZE
	};

	//Deployment Type 정의
	enum DEPLOYMENTTYPE
	{
		DEP_NONE = 0,
		DEP_INVERTEDTRIANGLE = 1,	// 역삼각대
		DEP_CIRCLE,					// 원형
		DEP_LINE,					// 횡대
		DEP_COLUMN,					// 종대
		DEP_TRIANGLE				// 삼각대
	};
	static CString strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, CResolutionChange::DEPLOYMENTTYPE em);
	static vector<CString> strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil);
	static CResolutionChange::DEPLOYMENTTYPE emDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, int selNum);

	//분해 요소 Type 정의
	enum DISAGGREGATEDTYPE
	{
		DISAGG_NUM1 = 0,
		DISAGG_NUM2,
		DISAGG_NUM3,
		DISAGG_NUM4,
		DISAGG_SIZE
	};

	//영역
	enum AREAPOS
	{
		AREAPOS_NUM1 = 0,
		AREAPOS_NUM2,
		AREAPOS_NUM3,
		AREAPOS_NUM4,
		AREAPOS_SIZE
	};

	//분할객체 영역
	enum AREABUTTOMPOS
	{
		AREABTP_NUM1 = 4,
		AREABTP_NUM2,
		AREABTP_NUM3,
		AREABTP_NUM4,
		AREABTP_SIZE
	};

	//보병분대 분해 요소 Type 정의
	enum INFANTRYSQUADDISAGGREGATEDTYPE
	{
		SQUDISAGG_NUM01 = 0,
		SQUDISAGG_NUM02,
		SQUDISAGG_NUM03,
		SQUDISAGG_NUM04,
		SQUDISAGG_NUM05,
		SQUDISAGG_NUM06,
		SQUDISAGG_NUM07,
		SQUDISAGG_NUM08,
		SQUDISAGG_NUM09,
		SQUDISAGG_NUM10,
		SQUDISAGG_NUM11,
		SQUDISAGG_NUM12,
		SQUDISAGG_SIZE
	};

	//포대 분해 요소 Type 정의
	enum ARTILLERYCOMPANYDISAGGREGATEDTYPE
	{
		ARCOMDISAGG_NUM01 = 0,
		ARCOMDISAGG_NUM02,
		ARCOMDISAGG_NUM03,
		ARCOMDISAGG_NUM04,
		ARCOMDISAGG_NUM05,
		ARCOMDISAGG_NUM06,
		ARCOMDISAGG_SIZE
	};

	//부대의 지형요소
	enum TOPOGRAPHICCHAR
	{
		TOPO_MAPRI = 0,
		TOPO_MAPSE,
		TOPO_MAPMO,
		TOPO_MAPHO,
		TOPO_MAPFO,
		TOPO_MAPSW,
		TOPO_MAPFA
	};
	static CString strTopographicChar(CUnitSize::COMBATANT combat, CResolutionChange::TOPOGRAPHICCHAR em);
	static vector<CString> strTopographicChar(CUnitSize::COMBATANT combat);
	static CResolutionChange::TOPOGRAPHICCHAR emTopographicChar(CUnitSize::COMBATANT combat, int selNum);

	//위치변환 입력 정의 객체
	struct inputPosVal
	{
		inputPosVal(){}
		CVector2d parent;
		DIRECTIONTYPE dir;
		DEPLOYMENTTYPE dep;
		CUnitSize::InputVal unitSizeVal;
	};
private:
	//부대 타입별 크기 저장 변수
	CUnitSize* unitSizeVal;
	//변환 입력 변수
	inputPosVal inPosVal;
	//지형영향 변수
	TOPOGRAPHICCHAR topoChar;
public:
	void setParentPos(CVector2d parentPos);
	void setDirectionType(DIRECTIONTYPE em);
	void setDeploymentType(DEPLOYMENTTYPE em);
	void setMoveType(CUnitSize::MOVETYPE em);
	void setForce(CUnitSize::FORCE em);
	void setCombatent(CUnitSize::COMBATANT em);
	void setMilitarybranch(CUnitSize::MILITARYBRANCH em);
	void setTopographicChar(TOPOGRAPHICCHAR em);

	TOPOGRAPHICCHAR getTopographicChar();

	static CVector2d frontDirection(DIRECTIONTYPE dir);
	static CVector2d crossDirection(CVector2d frontNorDir);
public:	
	//고 -> 저 변환
	void changeAggregated();
	//저 -> 고 변환
	void changeDisaggregated();
	//고해상도 변환
	vector<CVector2d> changeDisaggregatedPosition(inputPosVal val, vector<CVector2d>& areaPos, CSize& areaSize);
	//고해상도 변환(보병 분대)
	vector<CVector2d> changeDisaggregatedPositionInfantrySquad(inputPosVal val, vector<CVector2d>& areaPos, CSize& areaSize);
	//고해상도 변환(포대)
	vector<CVector2d> changeDisaggregatedPositionArtilleryCompany(inputPosVal val, vector<CVector2d>& areaPos, CSize& areaSize);
	//위치 계산
	CVector2d calcPosition(CALCPOSITIONTYPE calcType, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);
	//대형 전개
	vector<CVector2d> deploymentPosition(DEPLOYMENTTYPE deployment, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);
	//부대 타입별 영역 좌표
	vector<CVector2d> areaPosition(CVector2d front, CVector2d cross, vector<int> sizeUnit);
	//저해상도 변환
	CVector2d changeAggregatedPosition(vector<CVector2d> posList);
	//저해상도 변환
	static CVector2d changeAggregatedPosition(vector<CVector2d> posList, int size);
	//저해상도 변환(보병 분대)
	CVector2d changeAggregatedPositionInfantrySquad(vector<CVector2d> posList);
};