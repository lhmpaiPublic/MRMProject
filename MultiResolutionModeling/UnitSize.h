#pragma once


class CUnitSize
{
public:
	CUnitSize();
	~CUnitSize();
public:
	enum MOVETYPE
	{
		DEFENCE = 0,	//공격
		OFFENCE = 4		//방어
	};

	enum UNITDEPTH
	{
		WIDTH = 0,	//넓이
		HIGHT = 2	//높이
	};

	enum FORCE
	{
		BLUEFORCE = 0,	//청군
		REDFORCE = 1	//홍군
	};

	enum UNITSIZE
	{
		xUNITSIZE = 0,	//x 크기
		yUNITSIZE = 1	//y 크기
	};

	enum COMBATANT
	{
		INFANTRY = 0,	//보병
		ARMORED = 4,	//전차
		ARTILLERY = 8	//포병
	};

	enum MILITARYBRANCH
	{
		SQUAD = 0,		//분대
		PLATOON = 1,	//소대
		COMPANY = 2,	//중대
		BATTALION = 3,	//대대
	};

	enum MILITARYBRANCH_AR
	{
		ARTILLERYUNIT = 0, //포대
		ARTILLERYBT = 1		//대대
	};

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
		InputVal(MOVETYPE _moveType, FORCE _force, COMBATANT _combat, MILITARYBRANCH _mil)
		{
			moveType = _moveType; force = _force; combat = _combat; milVal.mil = _mil; milVal.mil_AR = ARTILLERYBT;
		}
		InputVal(MOVETYPE _moveType, FORCE _force, COMBATANT _combat, MILITARYBRANCH_AR _mil_AR)
		{
			moveType = _moveType; force = _force; combat = _combat; milVal.mil_AR = _mil_AR; milVal.mil = BATTALION;
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