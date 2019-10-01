// CSVFile.cpp
//

#include "stdafx.h"
#include "GAgt.h"
#include "ResolutionPositionDlg.h"
#include "ResolutionChange.h"
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