#pragma once


#include "UnitSize.h"
class CResolutionChange
{
public:
	CResolutionChange();
	~CResolutionChange();
public:
	//�δ� ���� ���� Type ����
	enum DIRECTIONTYPE
	{
		NONE_DIRECTION = 0,
		N_DIRECTION,			//��
		NE_DIRECTION,			//�ϵ�
		E_DIRECTION,			//��
		SE_DIRECTION,			//����
		S_DIRECTION,			//��
		SW_DIRECTION,			//����
		W_DIRECTION,			//��
		NW_DIRECTION			//�ϼ�
	};
	static CString strDirectionType(CResolutionChange::DIRECTIONTYPE em);
	static vector<CString> strDirectionType();
	static CResolutionChange::DIRECTIONTYPE emDirectionType(int selNum);

	//��ġ ��� Type ����
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

	//SIZE VECTOR Type ����
	enum SIZEVECTORTYPE
	{
		SIZEVEC_WIDTH = 0,
		SIZEVEC_HIGHT,
	};

	//Deployment Type ����
	enum DEPLOYMENTTYPE
	{
		DEP_NONE = 0,
		DEP_INVERTEDTRIANGLE = 1,	// ���ﰢ��
		DEP_CIRCLE,					// ����
		DEP_LINE,					// Ⱦ��
		DEP_COLUMN,					// ����
		DEP_TRIANGLE				// �ﰢ��
	};
	static CString strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, CResolutionChange::DEPLOYMENTTYPE em);
	static vector<CString> strDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil);
	static CResolutionChange::DEPLOYMENTTYPE emDeploymentType(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil, int selNum);

	//���� ��� Type ����
	enum DISAGGREGATEDTYPE
	{
		DISAGG_NUM1 = 0,
		DISAGG_NUM2,
		DISAGG_NUM3,
		DISAGG_NUM4,
		DISAGG_SIZE
	};

	//����
	enum AREAPOS
	{
		AREAPOS_NUM1 = 0,
		AREAPOS_NUM2,
		AREAPOS_NUM3,
		AREAPOS_NUM4,
		AREAPOS_SIZE
	};

	//�����д� ���� ��� Type ����
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

	//���� ���� ��� Type ����
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