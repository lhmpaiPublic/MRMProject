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
	//CSV open Type ����
	enum DLGNAME
	{
		RESPOS = 0,
		RESPPTY,
	};
	void ShowDlg(DLGNAME name);
	void HideDlg(DLGNAME name);

	CResolutionPositionDlg* ResPosDlg();

	CResolutionChange* ResCha();

	CResolutionPropertyDlg* ResPptyDlg();

	CPropertyList* PropLi();

	void drawResolutionPosition(vector<CVector2d> pos, int typeOp, vector<CVector2d> areaPos, CString text);
};