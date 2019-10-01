#pragma once

class CResolutionPositionDlg;
class CGAgt
{
	HWND hParent;
	static CGAgt* mG;
public:
	static CGAgt* G();
	CGAgt();
	~CGAgt();

public:
	void initGAgt(HWND _hParent);
	void releaseDlg();

private:
	CResolutionPositionDlg* mResPosDlg;

public:
	//CSV open Type Á¤ÀÇ
	enum DLGNAME
	{
		RESPOS = 0,
	};
	void ShowDlg(DLGNAME name);
	void HideDlg(DLGNAME name);
	CResolutionPositionDlg* ResPosDlg();

};