#pragma once

//������ ��ü
class CResolutionPositionDlg;
class CResolutionChange;
class CPropertyList;
class CResolutionPropertyDlg;
class CResolHiPropDlg;

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
	static CResolHiPropDlg* ResHPptyDlg();
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

	//���ػ� �ڻ꺯ȯ ��� ��ü
	CResolHiPropDlg* mResHPptyDlg;
public:
	//CSV open Type ����
	enum DLGNAME
	{
		RESPOS = 0,
		RESPPTY,
		RESHPPTY,
	};
	//��ü Show
	void ShowDlg(DLGNAME name);
	//��ü Hide
	void HideDlg(DLGNAME name);
};

#define GPOSSUBDLG CGAgt::ResPosDlg()->foSMPDg()