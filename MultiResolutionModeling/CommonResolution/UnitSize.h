#pragma once

//�δ� ũ�� ���� ��ü
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
	static vector<CString> strMoveType();
	static CUnitSize::MOVETYPE emMoveType(int selNum);

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
	static vector<CString> strForce();
	static CUnitSize::FORCE emForce(int selNum);

	enum UNITSIZE
	{
		xUNITSIZE = 0,	//x ũ��
		yUNITSIZE = 1	//y ũ��
	};

	enum COMBATANT
	{
		INFANTRY = 0,	//����
		ARMORED = 4,	//����
		ARTILLERY = 7	//����
	};
	static CString strCombatent(CUnitSize::COMBATANT em);
	static vector<CString> strCombatent();
	static CUnitSize::COMBATANT emCombatent(int selNum);

	enum MILITARYBRANCH
	{
		INFANTRY_SQUAD = 0,		//���� �д�
		INFANTRY_PLATOON = 1,	//���� �Ҵ�
		INFANTRY_COMPANY = 2,	//���� �ߴ�
		INFANTRY_BATTALION = 3,	//���� ���
		ARMORED_PLATOON = 0,	//���� �Ҵ�
		ARMORED_COMPANY = 1,	//���� �ߴ�
		ARMORED_BATTALION = 2,	//���� ���
		ARTILLERY_COMPANY = 0,	//����
		ARTILLERY_BATTALION = 1		//���� ���
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
	//�δ� Ÿ�Ժ� ũ�� csv���� �б�
	void loadCSVFile(string fileName);
	//���� Ÿ�Ժ� ���� 
	vector<int> getINFANTRYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//���� Ÿ�Ժ� ����
	vector<int> getARMOREDSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//���� Ÿ�Ժ� ����
	vector<int> getARTILLERYSize(MILITARYBRANCH mil, MOVETYPE mo, FORCE fo);
	//�δ� Ÿ�Ժ� ũ��
	vector<int> unitZoneSize(InputVal in);

private:
	//MOVETYPE + FORCE + UNITDEPTH
	typedef vector<int> VECINT;
	//MILITARYBRANCH, MILITARYBRANCH_AR
	typedef vector<VECINT> VECVECINT;
	//COMBATANT
	CAtlMap<COMBATANT, VECVECINT> mapCombatant;

};