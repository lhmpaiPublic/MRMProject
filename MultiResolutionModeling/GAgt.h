#pragma once

class CResolutionPositionDlg;
class CResolutionChange;
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
public:
	//CSV open Type Á¤ÀÇ
	enum DLGNAME
	{
		RESPOS = 0,
	};
	void ShowDlg(DLGNAME name);
	void HideDlg(DLGNAME name);

	CResolutionPositionDlg* ResPosDlg();

	CResolutionChange* ResCha();
};