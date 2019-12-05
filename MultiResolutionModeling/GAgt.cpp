// CSVFile.cpp
//

#include "stdafx.h"
#include "ResolutionPosition/ResolutionPosition.h"
#include "ResolutionProperty/ResolutionProperty.h"
#include "ResolutionProperty/PropertyList.h"

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
	return G()->mResCha;
}

CGAgt::CGAgt()
{
	mG = this;
	mResPosDlg = NULL;
	mResCha = NULL;
	mResPptyDlg = NULL;
	mPropList = NULL;
}

CGAgt::~CGAgt()
{
	delete mResPosDlg;
	mResPosDlg = NULL;

	delete mResCha;
	mResCha = NULL;

	delete mResPptyDlg;
	mResPptyDlg = NULL;

	delete mPropList;
	mPropList = NULL;
}

void CGAgt::initGAgt(HWND _hParent)
{
	hParent = _hParent;
	mResCha = new CResolutionChange();

	mResPosDlg = new CResolutionPositionDlg();
	if(mResPosDlg)	mResPosDlg->Create(hParent);


	mPropList = new CPropertyList();
	mPropList->loadCSVFile("infantryPropertyList.csv", SPrMoTy::INFANTRY);
	mPropList->loadCSVFile("armoredPropertyList.csv", SPrMoTy::ARMORED);
	mPropList->loadCSVFile("artilleryPropertyList.csv", SPrMoTy::ARTILLERY);

	mResPptyDlg = new CResolutionPropertyDlg();
	if(mResPptyDlg)	mResPptyDlg->Create(hParent);

	mResHPptyDlg = new CResolHiPropDlg();
	if(mResHPptyDlg)	mResHPptyDlg->Create(hParent);
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
	case RESHPPTY:mResHPptyDlg->ShowWindow(SW_SHOW);
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
	case RESHPPTY:mResHPptyDlg->ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}
}

CResolutionPositionDlg* CGAgt::ResPosDlg()
{
	return  G()->mResPosDlg;
}


CPropertyList* CGAgt::PropLi()
{
	return G()->mPropList;
}

CResolutionPropertyDlg* CGAgt::ResPptyDlg()
{
	return G()->mResPptyDlg;
}

CResolHiPropDlg* CGAgt::ResHPptyDlg()
{
	return G()->mResHPptyDlg;
}