#pragma once


#include "UnitSize.h"
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

	struct inputPosVal
	{
		inputPosVal(){}
		CVector2d parent;
		DIRECTIONTYPE dir;
		DEPLOYMENTTYPE dep;
		CUnitSize::InputVal unitSizeVal;
	};
private:
	CUnitSize *unitSizeVal;
	inputPosVal inPosVal;

public:
	void setParentPos(CVector2d parentPos);
	void setDirectionType(DIRECTIONTYPE em);
	void setDeploymentType(DEPLOYMENTTYPE em);
	void setMoveType(CUnitSize::MOVETYPE em);
	void setForce(CUnitSize::FORCE em);
	void setCombatent(CUnitSize::COMBATANT em);
	void setMilitarybranch(CUnitSize::MILITARYBRANCH em);
public:	

	void changeAggregated();

	void changeDisaggregated();

	vector<CVector2d> changeDisaggregatedPosition(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText);
	vector<CVector2d> changeDisaggregatedPositionInfantrySquad(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText);
	vector<CVector2d> changeDisaggregatedPositionArtilleryCompany(inputPosVal val, vector<CVector2d>& areaPos, CString& drawText);

	CVector2d frontDirection(DIRECTIONTYPE dir);

	CVector2d crossDirection(CVector2d frontNorDir);

	CVector2d calcPosition(CALCPOSITIONTYPE calcType, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);

	vector<CVector2d> deploymentPosition(DEPLOYMENTTYPE deployment, CVector2d parent, CVector2d front, CVector2d cross, vector<int> sizeUnit);

	vector<CVector2d> areaPosition(CVector2d front, CVector2d cross, vector<int> sizeUnit);

	CVector2d changeAggregatedPosition(vector<CVector2d> posList);

	static CVector2d changeAggregatedPosition(vector<CVector2d> posList, int size);

	CVector2d changeAggregatedPositionInfantrySquad(vector<CVector2d> posList);
};