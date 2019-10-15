//  : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubMapPosDlg.h"
#include "../ImageLoadApi/ImageLoadApi.h"
#include "../ResolutionChange.h"
#define SUBMAPOSDLG_POSX 50
#define SUBMAPOSDLG_POSY 160

#define SUBMAPOSDLG_CENTERPOSX 450
#define SUBMAPOSDLG_CENTERPOSY 450

#define SUBMAPOSDLG_CENTERSIZE 10
#define SUBMAPOSDLG_RECREDSIZE 5

#define SUBMAPOSDLG_POSTEXTX 450
#define SUBMAPOSDLG_POSTEXTY 50

CSubMapPosDlg::CSubMapPosDlg()
{

}
void CSubMapPosDlg::init(HWND _hWnd)
{
	hWnd = _hWnd;
	drawPosItem.clear();
	drawPosItemsize = 1;
	typeOption = 0;

	bLClick = false;
}
UINT CSubMapPosDlg::imgId[IMAGE_MAX]=
{
	IDB_RP_MAPGRID_1,
	IDB_RP_MAPGRID_2,
	IDB_RP_MAPGRID_3,
	IDB_RP_MAPGRID_4,
	IDB_RP_MAPGRID_5,
	IDB_RP_MAPGRID_6,
	IDB_RP_MAPGRID_7,
	IDB_RP_MAPGRID_8
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
	dc.Ellipse(SUBMAPOSDLG_CENTERPOSX-SUBMAPOSDLG_CENTERSIZE, SUBMAPOSDLG_CENTERPOSY-SUBMAPOSDLG_CENTERSIZE, SUBMAPOSDLG_CENTERPOSX+SUBMAPOSDLG_CENTERSIZE, SUBMAPOSDLG_CENTERPOSY+SUBMAPOSDLG_CENTERSIZE);
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

	CPen penRed;
	penRed.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen old_pen = dc.SelectPen(penRed);

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
		opt = 0.25f;
	}
	else if(typeOption == 4)
	{
		opt = 0.2f;
	}
	else if(typeOption == 5)
	{
		opt = 0.8f;
	}
	else if(typeOption == 6)
	{
		opt = 0.2f;
	}
	else if(typeOption == 7)
	{
		opt = 0.088f;
	}


	if(drawAreaPosItem.size() >= 4)
	{
		CPoint pt[5];
		pt[0] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[0].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[0].y*opt)));
		pt[1] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[1].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[1].y*opt)));
		pt[2] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[2].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[2].y*opt)));
		pt[3] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[3].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[3].y*opt)));
		pt[4] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[0].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[0].y*opt)));

		dc.Polyline(pt, 5);
	}

	for (int i = 0; i < min((int)drawPosItem.size(), drawPosItemsize); i++)
	{
		int left = (int)(SUBMAPOSDLG_CENTERPOSX + (drawPosItem[i].x*opt))-SUBMAPOSDLG_RECREDSIZE;
		int top = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))-SUBMAPOSDLG_RECREDSIZE;
		int right = (int)(SUBMAPOSDLG_CENTERPOSX + (drawPosItem[i].x*opt))+SUBMAPOSDLG_RECREDSIZE;
		int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))+SUBMAPOSDLG_RECREDSIZE;
		dc.Rectangle(left, top, right, bottom);
	}

	int left = (int)(SUBMAPOSDLG_CENTERPOSX + (drawAggPosItem.x*opt))-SUBMAPOSDLG_RECREDSIZE;
	int top = (int)(SUBMAPOSDLG_CENTERPOSY - (drawAggPosItem.y*opt))-SUBMAPOSDLG_RECREDSIZE;
	int right = (int)(SUBMAPOSDLG_CENTERPOSX + (drawAggPosItem.x*opt))+SUBMAPOSDLG_RECREDSIZE;
	int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - (drawAggPosItem.y*opt))+SUBMAPOSDLG_RECREDSIZE;
	dc.Ellipse(left, top, right, bottom);

	dc.SelectBrush(old_brush);
	dc.SelectPen(old_pen);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 100, 255));
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 21;
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"), 7);
	CFont font;
	font.CreateFontIndirect(&lf);;
	CFont font_old = dc.SelectFont(font);
	dc.DrawText(drawtextItem.GetBuffer(), drawtextItem.GetLength(), CRect((SUBMAPOSDLG_POSTEXTX - 80), SUBMAPOSDLG_POSTEXTY+10, (SUBMAPOSDLG_POSTEXTX-80) + ((drawtextItem.GetLength()*12)), SUBMAPOSDLG_POSTEXTY+35), DT_TOP|DT_LEFT);

	dc.SelectFont(font_old);
}

void CSubMapPosDlg::drawResolutionPosition(vector<CVector2d> pos, int typeOp, vector<CVector2d> areaPos, CString text)
{
	drawPosItem.clear();
	drawPosItem = pos;
	typeOption = typeOp;
	drawAreaPosItem = areaPos;
	drawtextItem = text;

	CLogDlg::initStream();
	CLogDlg::insertStream("출력개수 :");
	CLogDlg::insertStream(min((int)drawPosItem.size(), drawPosItemsize), '	');
	CLogDlg::addLogTextStream();

	drawAggPosItem = CResolutionChange::changeAggregatedPosition(pos, drawPosItemsize);

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}

void CSubMapPosDlg::drawResolutionPositionSize(int drawSize)
{
	drawPosItemsize = drawSize;
}

LRESULT CSubMapPosDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	GetParent().GetWindowRect(winPos);
	SetCapture();
	bLClick = true;
	startPoint = CPoint(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

LRESULT CSubMapPosDlg::OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(bLClick)
	{
		GetParent().GetWindowRect(winPos);
		GetParent().SetWindowPos(NULL, winPos.left+(LOWORD(lParam) - startPoint.x), winPos.top+(HIWORD(lParam) - startPoint.y), 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	return 0;
}

LRESULT CSubMapPosDlg::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	bLClick = false;
	ReleaseCapture();
	return 0;
}