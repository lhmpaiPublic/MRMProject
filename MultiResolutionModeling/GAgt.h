#pragma once

//������ ��ü
class CResolutionPositionDlg;
class CResolutionChange;
class CPropertyList;
class CResolutionPropertyDlg;

//��ü ���� �� ���� ��ü
class CGAgt
{
	HWND hParent;
	static CGAgt* mG;
public:
	//���� ��ü ����
	static CGAgt* G();
	static CResolutionChange* GResCha();
	static CResolutionPositionDlg* ResPosDlg();
	static CResolutionPropertyDlg* ResPptyDlg();
	static CPropertyList* PropLi();
	CGAgt();
	~CGAgt();

public:
	//���� ��ü ����
	void initGAgt(HWND _hParent);
	//���� ����
	void releaseDlg();

private:
	//��ġ��ȯ ��� ��ü
	CResolutionPositionDlg* mResPosDlg;
	//��ġ��ȯ ��ü
	CResolutionChange* mResCha;
	//�ڻ꺯ȯ ��� ��ü
	CResolutionPropertyDlg* mResPptyDlg;
	//�ڻ꺯ȯ ��ü
	CPropertyList* mPropList;
public:
	//CSV open Type ����
	enum DLGNAME
	{
		RESPOS = 0,
		RESPPTY,
	};
	//��ü Show
	void ShowDlg(DLGNAME name);
	//��ü Hide
	void HideDlg(DLGNAME name);

	//void drawResolutionPosition(vector<CVector2d> pos, vector<CVector2d> areaPos, CSize _areaSize);
};

#define GPOSSUBDLG CGAgt::ResPosDlg()->foSMPDg()