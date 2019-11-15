#pragma once

class CResolutionPositionDlg;
class CResolutionChange;
class CPropertyList;
class CResolutionPropertyDlg;
class CGAgt
{
	HWND hParent;
	static CGAgt* mG;
public:
	static CGAgt* G();
	static CResolutionChange* GResCha();
	static CResolutionPositionDlg* ResPosDlg();
	static CResolutionChange* ResCha();
	static CResolutionPropertyDlg* ResPptyDlg();
	static CPropertyList* PropLi();
	CGAgt();
	~CGAgt();

public:
	void initGAgt(HWND _hParent);
	void releaseDlg();

private:
	CResolutionPositionDlg* mResPosDlg;
	CResolutionChange* mResCha;
	CResolutionPropertyDlg* mResPptyDlg;
	CPropertyList* mPropList;
public:
	//CSV open Type Á¤ÀÇ
	enum DLGNAME
	{
		RESPOS = 0,
		RESPPTY,
	};
	void ShowDlg(DLGNAME name);
	void HideDlg(DLGNAME name);

	//void drawResolutionPosition(vector<CVector2d> pos, vector<CVector2d> areaPos, CSize _areaSize);
};

#define GPOSSUBDLG CGAgt::ResPosDlg()->foSMPDg()