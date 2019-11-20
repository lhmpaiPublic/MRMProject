#pragma once

//부대 크기 저장 객체
class CUnitSize
{
public:
	CUnitSize();
	~CUnitSize();
public:
	enum MOVETYPE
	{
		DEFENCE = 0,	//방어
		OFFENCE = 4		//공격
	};
	static CString strMoveType(CUnitSize::MOVETYPE em);
	static vector<CString> strMoveType();
	static CUnitSize::MOVETYPE emMoveType(int selNum);

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
	static CString strForce(CUnitSize::FORCE em);
	static vector<CString> strForce();
	static CUnitSize::FORCE emForce(int selNum);

	enum UNITSIZE
	{
		xUNITSIZE = 0,	//x 크기
		yUNITSIZE = 1	//y 크기
	};

	enum COMBATANT
	{
		INFANTRY = 0,	//보병
		ARMORED = 4,	//전차
		ARTILLERY = 7	//포병
	};
	static CString strCombatent(CUnitSize::COMBATANT em);
	static vector<CString> strCombatent();
	static CUnitSize::COMBATANT emCombatent(int selNum);

	enum MILITARYBRANCH
	{
		INFANTRY_SQUAD = 0,		//보병 분대
		INFANTRY_PLATOON = 1,	//보병 소대
		INFANTRY_COMPANY = 2,	//보병 중대
		INFANTRY_BATTALION = 3,	//보병 대대
		ARMORED_PLATOON = 0,	//전차 소대
		ARMORED_COMPANY = 1,	//전차 중대
		ARMORED_BATTALION = 2,	//전차 대대
		ARTILLERY_COMPANY = 0,	//포대
		ARTILLERY_BATTALION = 1		//포병 대대
	};
	static CString strMilitarybranch(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH em);
	static vector<CString> strMilitarybranch(CUnitSize::COMBATANT combat);
	static CUnitSize::MILITARYBRANCH emMilitarybranch(CUnitSize::COMBATANT combat, int selNum);

	struct InputVal
	{
		MOVETYPE moveType;
		FORCE force;
		COMBATANT combat;
		MILITARYBRANCH mil;
		InputVal()
		{
			moveType = OFFENCE; force = BLUEFORCE; combat = INFANTRY; mil = INFANTRY_SQUAD;
		}
		InputVal(MOVETYPE _moveType, FORCE _force, COMBATANT _combat, MILITARYBRANCH _mil)
		{
			moveType = _moveType; force = _force; combat = _combat; mil = _mil;
		}
	};
	//부대 타입별 크기 csv파일 읽기
	void loadCSVFile(string fileName);
	//보병 타입별 영역 
	vector<int> getINFANTRYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//전차 타입별 영역
	vector<int> getARMOREDSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//포병 타입별 영역
	vector<int> getARTILLERYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//부대 타입별 크기
	vector<int> unitZoneSize(InputVal in);

private:
	//MOVETYPE + FORCE + UNITDEPTH
	typedef vector<int> VECINT;
	//MILITARYBRANCH, MILITARYBRANCH_AR
	typedef vector<VECINT> VECVECINT;
	//COMBATANT
	CAtlMap<COMBATANT, VECVECINT> mapCombatant;

};