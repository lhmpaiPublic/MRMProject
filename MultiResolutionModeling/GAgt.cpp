// CSVFile.cpp
//

#include "stdafx.h"
#include "ResolutionPosition/ResolutionPosition.h"
#include "ResolutionProperty/ResolutionProperty.h"

//초기화
CGAgt* CGAgt::mG = NULL;
//전역객체 생성
CGAgt gG;
//전역객체 접근
CGAgt* CGAgt::G()
{
	return mG;
}

CResolutionChange* CGAgt::GResCha()
{
	return G()->ResCha();
}

CGAgt::CGAgt()
{
	mG = this;
	mResPosDlg = NULL;
	mResCha = NULL;
	mResPptyDlg = NULL;
}

CGAgt::~CGAgt()
{
}

void CGAgt::initGAgt(HWND _hParent)
{
	hParent = _hParent;
	mResCha = new CResolutionChange();

	mResPosDlg = new CResolutionPositionDlg();
	if(mResPosDlg)	mResPosDlg->Create(hParent);

	mResPptyDlg = new CResolutionPropertyDlg();
	if(mResPptyDlg)	mResPptyDlg->Create(hParent);
}

void CGAgt::releaseDlg()
{
	if(mResPosDlg)	mResPosDlg->CloseDialog(0);
}

void CGAgt::ShowDlg(DLGNAME name)
{
	switch(name)
	{
	case RESPOS:mResPosDlg->ShowWindow(SW_SHOW);
		break;
	case RESPPTY:mResPptyDlg->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void CGAgt::HideDlg(DLGNAME name)
{
	switch(name)
	{
	case RESPOS:mResPosDlg->ShowWindow(SW_HIDE);
		break;
	case RESPPTY:mResPptyDlg->ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
}

CResolutionPositionDlg* CGAgt::ResPosDlg()
{
	return mResPosDlg;
}

CResolutionChange* CGAgt::ResCha()
{
	return mResCha;
}

CResolutionPropertyDlg* CGAgt::ResPptyDlg()
{
	return mResPptyDlg;
}

void CGAgt::drawResolutionPosition(vector<CVector2d> pos, int typeOp, vector<CVector2d> areaPos, CString text)
{
	mResPosDlg->drawResolutionPosition(pos, typeOp, areaPos, text);
}