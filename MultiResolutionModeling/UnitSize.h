#pragma once


class CUnitSize
{
public:
	CUnitSize();
	~CUnitSize();
public:
	enum MOVETYPE
	{
		DEFENCE = 0,	//���
		OFFENCE = 4		//����
	};
	static CString strMoveType(CUnitSize::MOVETYPE em);

	enum UNITDEPTH
	{
		WIDTH = 0,	//����
		HIGHT = 2	//����
	};

	enum FORCE
	{
		BLUEFORCE = 0,	//û��
		REDFORCE = 1	//ȫ��
	};
	static CString strForce(CUnitSize::FORCE em);

	enum UNITSIZE
	{
		xUNITSIZE = 0,	//x ũ��
		yUNITSIZE = 1	//y ũ��
	};

	enum COMBATANT
	{
		INFANTRY = 0,	//����
		ARMORED = 4,	//����
		ARTILLERY = 8	//����
	};
	static CString strCombatent(CUnitSize::COMBATANT em);

	enum MILITARYBRANCH
	{
		SQUAD = 0,		//�д�
		PLATOON = 1,	//�Ҵ�
		COMPANY = 2,	//�ߴ�
		BATTALION = 3,	//���
	};
	static CString strMilitarybranch(CUnitSize::MILITARYBRANCH em);

	enum MILITARYBRANCH_AR
	{
		ARTILLERYUNIT = 0, //����
		ARTILLERYBT = 1		//���
	};
	static CString strMilitarybranch_AR(CUnitSize::MILITARYBRANCH_AR em);

	struct InputVal
	{
		MOVETYPE moveType;
		FORCE force;
		COMBATANT combat;
		union
		{
			MILITARYBRANCH mil;
			MILITARYBRANCH_AR mil_AR;
		}milVal;
		InputVal()
		{
			moveType = OFFENCE; force = BLUEFORCE; combat = INFANTRY; milVal.mil = BATTALION;
		}
		InputVal(MOVETYPE _moveType, FORCE _force, COMBATANT _combat, MILITARYBRANCH _mil)
		{
			moveType = _moveType; force = _force; combat = _combat; milVal.mil = _mil;
		}
		InputVal(MOVETYPE _moveType, FORCE _force, COMBATANT _combat, MILITARYBRANCH_AR _mil_AR)
		{
			moveType = _moveType; force = _force; combat = _combat; milVal.mil_AR = _mil_AR;
		}
	};

	void loadCSVFile(string fileName);

	vector<int> getINFANTRYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);

	vector<int> getARMOREDSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);

	vector<int> getARTILLERYSize(MILITARYBRANCH_AR mil, MOVETYPE mo, FORCE fo);

	vector<int> unitZoneSize(InputVal in);

private:
	//MOVETYPE + FORCE + UNITDEPTH
	typedef vector<int> VECINT;
	//MILITARYBRANCH, MILITARYBRANCH_AR
	typedef vector<VECINT> VECVECINT;
	//COMBATANT
	CAtlMap<COMBATANT, VECVECINT> mapCombatant;

};