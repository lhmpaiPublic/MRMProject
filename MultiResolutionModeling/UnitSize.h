#pragma once


class CUnitSize
{
public:
	CUnitSize();
	~CUnitSize();
public:
	enum MOVETYPE
	{
		DEFENCE = 0,
		OFFENCE = 4
	};

	enum UNITDEPTH
	{
		WIDTH = 0,
		HIGHT = 2
	};

	enum FORCE
	{
		BLUEFORCE = 0,
		REDFORCE = 1
	};

	enum UNITSIZE
	{
		xUNITSIZE = 0,
		yUNITSIZE = 1
	};

	enum COMBATANT
	{
		INFANTRY = 0,
		ARMORED = 4,
		ARTILLERY = 8
	};

	enum MILITARYBRANCH
	{
		SQUAD = 0,
		PLATOON = 1,
		COMPANY = 2,
		BATTALION = 3,
	};

	enum MILITARYBRANCH_AR
	{
		ARTILLERYUNIT = 0,
		ARTILLERYBT = 1
	};

	void loadCSVFile(string fileName);

	vector<int> getINFANTRYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);

	vector<int> getARMOREDSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);

	vector<int> getARTILLERYSize(MILITARYBRANCH_AR mil, MOVETYPE mo, FORCE fo);

private:
	//MOVETYPE + FORCE + UNITDEPTH
	typedef vector<int> VECINT;
	//MILITARYBRANCH, MILITARYBRANCH_AR
	typedef vector<VECINT> VECVECINT;
	//COMBATANT
	CAtlMap<COMBATANT, VECVECINT> mapCombatant;

};