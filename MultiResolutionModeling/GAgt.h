#pragma once

//생성할 개체
class CResolutionPositionDlg;
class CResolutionChange;
class CPropertyList;
class CResolutionPropertyDlg;
class CResolHiPropDlg;

//객체 생성 및 관리 개체
class CGAgt
{
	HWND hParent;
	static CGAgt* mG;
public:
	//전역 개체 접근
	static CGAgt* G();
	static CResolutionChange* GResCha();
	static CResolutionPositionDlg* ResPosDlg();
	static CResolutionPropertyDlg* ResPptyDlg();
	static CResolHiPropDlg* ResHPptyDlg();
	static CPropertyList* PropLi();
	CGAgt();
	~CGAgt();

public:
	//관리 개체 생성
	void initGAgt(HWND _hParent);
	//관리 종료
	void releaseDlg();

private:
	//위치변환 출력 개체
	CResolutionPositionDlg* mResPosDlg;
	//위치변환 개체
	CResolutionChange* mResCha;
	//자산변환 출력 개체
	CResolutionPropertyDlg* mResPptyDlg;
	//자산변환 개체
	CPropertyList* mPropList;

	//고해상도 자산변환 출력 개체
	CResolHiPropDlg* mResHPptyDlg;
public:
	//CSV open Type 정의
	enum DLGNAME
	{
		RESPOS = 0,
		RESPPTY,
		RESHPPTY,
	};
	//개체 Show
	void ShowDlg(DLGNAME name);
	//개체 Hide
	void HideDlg(DLGNAME name);
};

#define GPOSSUBDLG CGAgt::ResPosDlg()->foSMPDg()