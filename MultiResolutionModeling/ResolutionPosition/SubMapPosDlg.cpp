//  : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubMapPosDlg.h"
#include "../ImageLoadApi/ImageLoadApi.h"
#define SUBMAPOSDLG_POSX 50
#define SUBMAPOSDLG_POSY 160

#define SUBMAPOSDLG_CENTERPOSX 450
#define SUBMAPOSDLG_CENTERPOSY 450

#define SUBMAPOSDLG_RECSIZE 3
#define SUBMAPOSDLG_RECREDSIZE 5

CSubMapPosDlg::CSubMapPosDlg()
{

}
void CSubMapPosDlg::init(HWND _hWnd)
{
	hWnd = _hWnd;
	drawPosItem.clear();
	typeOption = 0;
}
UINT CSubMapPosDlg::imgId[IMAGE_MAX]=
{
	IDB_RP_MAPGRID_1,
	IDB_RP_MAPGRID_2,
	IDB_RP_MAPGRID_3,
	IDB_RP_MAPGRID_4,
	IDB_RP_MAPGRID_5
};

LRESULT CSubMapPosDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	CGdiPlusBitmapResource pBitmap;
	pBitmap.Load(imgId[0],_T("PNG"));
	CBitmap backimage = pBitmap.GetWinBitmap();
	BITMAP bitmap;
	::GetObject(backimage, sizeof(BITMAP), &bitmap); 
	int imgBackX = bitmap.bmWidth;
	int imgBackY = bitmap.bmHeight;

	CRect parentRect;
	::GetWindowRect(hWnd, &parentRect);
	MoveWindow(CRect(SUBMAPOSDLG_POSX, SUBMAPOSDLG_POSY, SUBMAPOSDLG_POSX+imgBackX, SUBMAPOSDLG_POSY+imgBackY));
	
	return TRUE;
}
//--------------------------------------------------------------
//|
//|객체 소멸 함수
//|
//---------------------------------------------------------------
LRESULT CSubMapPosDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	return 0;
}
LRESULT CSubMapPosDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DestroyWindow();
	return 0;
}
//--------------------------------------------------------------
//|
//|
//|
//---------------------------------------------------------------
BOOL CSubMapPosDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

//--------------------------------------------------------------
//|
//|버튼 애니메이션
//|
//---------------------------------------------------------------
void CSubMapPosDlg::buttonAnimation()
{
	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}

//--------------------------------------------------------------
//|
//|
//|
//---------------------------------------------------------------
BOOL CSubMapPosDlg::OnEraseBkgnd(CDCHandle dc)
{
	CGdiPlusBitmapResource pBitmap;
	pBitmap.Load(imgId[typeOption],_T("PNG"));
	CBitmap backimage = pBitmap.GetWinBitmap();

	// create memory DC
	dc.SetBkColor(RGB(255,0,0));
	CDC * pMemDC = new CDC;
	pMemDC -> CreateCompatibleDC(dc.m_hDC);
	CBitmapHandle pOldBitmap;

	SIZE bmSize;
	backimage.GetSize(bmSize);
	pOldBitmap = pMemDC -> SelectBitmap(backimage);
	dc.BitBlt(0,0,bmSize.cx, bmSize.cy,pMemDC->m_hDC,0,0,SRCCOPY);
	pMemDC -> SelectBitmap(pOldBitmap);
	delete pMemDC;

	CBrush blue;
	blue.CreateSolidBrush(RGB(0, 100, 255));
	CBrush old_brush = dc.SelectBrush(blue);
	dc.Rectangle(SUBMAPOSDLG_CENTERPOSX-SUBMAPOSDLG_RECSIZE, SUBMAPOSDLG_CENTERPOSY-SUBMAPOSDLG_RECSIZE, SUBMAPOSDLG_CENTERPOSX+SUBMAPOSDLG_RECSIZE, SUBMAPOSDLG_CENTERPOSY+SUBMAPOSDLG_RECSIZE);
	dc.SelectBrush(old_brush);

	if(drawPosItem.size())
	{
		drawResolutionPos(dc);
	}
	return FALSE;
}

void CSubMapPosDlg::drawResolutionPos(CDCHandle dc)
{
	CBrush Red;
	Red.CreateSolidBrush(RGB(255, 0, 0));
	CBrush old_brush = dc.SelectBrush(Red);

	float opt = 1.0f;
	if(typeOption == 1)
	{
		opt = 5;
	}
	else if(typeOption == 2)
	{
		opt = 0.5f;
	}
	else if(typeOption == 3)
	{
		opt = 0.4f;
	}
	else if(typeOption == 4)
	{
		opt = 0.8f;
	}

	for (int i = 0; i < (int)drawPosItem.size(); i++)
	{
		int left = (int)(SUBMAPOSDLG_CENTERPOSX - (drawPosItem[i].x*opt))-SUBMAPOSDLG_RECREDSIZE;
		int top = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))-SUBMAPOSDLG_RECREDSIZE;
		int right = (int)(SUBMAPOSDLG_CENTERPOSX - (drawPosItem[i].x*opt))+SUBMAPOSDLG_RECREDSIZE;
		int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))+SUBMAPOSDLG_RECREDSIZE;
		dc.Rectangle(left, top, right, bottom);
	}
	dc.SelectBrush(old_brush);
}

void CSubMapPosDlg::drawResolutionPosition(vector<CVector2d> pos, int typeOp)
{
	drawPosItem.clear();
	drawPosItem = pos;
	typeOption = typeOp;

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}