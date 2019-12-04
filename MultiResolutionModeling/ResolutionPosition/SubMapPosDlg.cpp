//  : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolutionPositionDlg.h"
#include "SubMapPosDlg.h"
#include "../ImageLoadApi/ImageLoadApi.h"


#define SUBMAPOSDLG_POSX 5
#define SUBMAPOSDLG_POSY 180

#define SUBMAPOSDLG_STARTCX 1
#define SUBMAPOSDLG_STARTCY 1

#define SUBMAPOSDLG_CX 1053
#define SUBMAPOSDLG_CY 1053

#define SUBMAPOSDLG_PIXCELX 42
#define SUBMAPOSDLG_PIXCELY 42

#define SUBMAPOSDLG_DISTX 25
#define SUBMAPOSDLG_DISTY 25

#define SUBMAPOSDLG_CENTERPOSX 526
#define SUBMAPOSDLG_CENTERPOSY 526

#define SUBMAPOSDLG_CENTERSIZE 10
#define SUBMAPOSDLG_RECREDSIZE 5

#define SUBMAPOSDLG_POSTEXTX 526
#define SUBMAPOSDLG_POSTEXTY 50

#define LATTICEDIV 40


CSubMapPosDlg::CSubMapPosDlg()
{

}
void CSubMapPosDlg::init(HWND _hWnd)
{
	hWnd = _hWnd;
	drawPosItem.clear();
	drawPosItemsize = 1;
	mapLattice.clear();
	mapLatticeSelect.clear();
	selImgMap.clear();

	latticSize = 0;

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

UINT CSubMapPosDlg::mapImgId[MAPIMAGE_MAX]=
{
	IDB_MAPRI,
	IDB_MAPSE,
	IDB_MAPMO,
	IDB_MAPHO,
	IDB_MAPFO,
	IDB_MAPSW,
	IDB_MAPFA
};

void CSubMapPosDlg::clearPosition()
{
	drawPosItem.clear();
	drawPosItemsize = 1;

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}

void CSubMapPosDlg::clearMapPos()
{
	mapLatticeSelect.clear();
	selImgMap.clear();

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}

void CSubMapPosDlg::clearAll()
{
	drawPosItem.clear();
	drawPosItemsize = 1;

	mapLatticeSelect.clear();
	selImgMap.clear();

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
}

LRESULT CSubMapPosDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	//CGdiPlusBitmapResource pBitmap;
	//pBitmap.Load(imgId[0],_T("PNG"));
	//CBitmap backimage = pBitmap.GetWinBitmap();
	//BITMAP bitmap;
	//::GetObject(backimage, sizeof(BITMAP), &bitmap); 
	//winSz.cx = bitmap.bmWidth;
	//winSz.cy = bitmap.bmHeight;

	//MoveWindow(CRect(SUBMAPOSDLG_POSX, SUBMAPOSDLG_POSY, SUBMAPOSDLG_POSX+winSz.cx, SUBMAPOSDLG_POSY+winSz.cy));

	MoveWindow(CRect(SUBMAPOSDLG_POSX, SUBMAPOSDLG_POSY, SUBMAPOSDLG_POSX+SUBMAPOSDLG_CX, SUBMAPOSDLG_POSY+SUBMAPOSDLG_CY));

	makeMapLattice(SUBMAPOSDLG_PIXCELX, SUBMAPOSDLG_PIXCELX, SUBMAPOSDLG_DISTX, SUBMAPOSDLG_DISTX);
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
	//CGdiPlusBitmapResource pBitmap;
	//pBitmap.Load(imgId[typeOption],_T("PNG"));
	//CBitmap backimage = pBitmap.GetWinBitmap();

	// create memory DC
	dc.FillSolidRect(CRect(0, 0, SUBMAPOSDLG_CX, SUBMAPOSDLG_CY), RGB(255,255,255));
	//CDC * pMemDC = new CDC;
	//pMemDC -> CreateCompatibleDC(dc.m_hDC);
	//CBitmapHandle pOldBitmap;

	//SIZE bmSize;
	//backimage.GetSize(bmSize);
	//pOldBitmap = pMemDC -> SelectBitmap(backimage);
	//dc.BitBlt(0,0,bmSize.cx, bmSize.cy,pMemDC->m_hDC,0,0,SRCCOPY);
	//pMemDC -> SelectBitmap(pOldBitmap);
	//delete pMemDC;

	baseMapLatticeDraw(dc);
	//drawMapLattice(dc);

	drawMapLatticeSelect(dc);

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

float CSubMapPosDlg::getMapOpt()
{
	//부대 규모에 따라서 격자의 크기 옵션 적용
	float opt = 1.0f;
	int maxArea = max(areaSize.cx, areaSize.cy);
	if(maxArea <= 500)
	{
		int pxVec[] = {3, 5, 7, 10, 12, 15};
		for (int i = 0; i < sizeof(pxVec)/sizeof(int); i++)
		{
			if(maxArea < pxVec[i]*LATTICEDIV)
			{
				latticSize = pxVec[i];
				opt = (float)(SUBMAPOSDLG_DISTX*LATTICEDIV)/(float)(pxVec[i]*LATTICEDIV);
				break;
			}
		}
	}
	else
	{
		for (int px = 15; px <= 100; px+=5)
		{
			if(maxArea < px*LATTICEDIV)
			{
				latticSize = px;
				opt = (float)(SUBMAPOSDLG_DISTX*LATTICEDIV)/(float)(px*LATTICEDIV);
				break;
			}
		}
	}
	return opt;
}

void CSubMapPosDlg::drawResolutionPos(CDCHandle dc)
{
	float opt = getMapOpt();

	//영역 사각형 그리기
	if(drawAreaPosItem.size() >= 4)
	{
		CPen penRed;
		penRed.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		CPen old_pen = dc.SelectPen(penRed);

		CPoint pt[5];
		pt[0] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[0].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[0].y*opt)));
		pt[1] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[1].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[1].y*opt)));
		pt[2] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[2].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[2].y*opt)));
		pt[3] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[3].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[3].y*opt)));
		pt[4] = CPoint((SUBMAPOSDLG_CENTERPOSX + (int)(drawAreaPosItem[0].x*opt)), (SUBMAPOSDLG_CENTERPOSY - (int)(drawAreaPosItem[0].y*opt)));

		dc.Polyline(pt, 5);
		dc.SelectPen(old_pen);
	}

	//분할 부대 위치 그리기
	for (int i = 0; i < min((int)drawPosItem.size(), drawPosItemsize); i++)
	{
		int clr = 255/(int)(drawPosItem.size()-1);
		CPen penRed;
		penRed.CreatePen(PS_SOLID, 3, RGB((clr*i), 0, 255-(clr*i)));
		CPen old_pen = dc.SelectPen(penRed);

		CBrush Red;
		Red.CreateSolidBrush(RGB((clr*i), 0, 255-(clr*i)));
		CBrush old_brush = dc.SelectBrush(Red);

		int left = (int)(SUBMAPOSDLG_CENTERPOSX + (drawPosItem[i].x*opt))-SUBMAPOSDLG_RECREDSIZE;
		int top = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))-SUBMAPOSDLG_RECREDSIZE;
		int right = (int)(SUBMAPOSDLG_CENTERPOSX + (drawPosItem[i].x*opt))+SUBMAPOSDLG_RECREDSIZE;
		int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - (drawPosItem[i].y*opt))+SUBMAPOSDLG_RECREDSIZE;
		dc.Rectangle(left, top, right, bottom);

		//분할 객체 영역 사각형 그리기
		if((BST_CHECKED == CResolutionPositionDlg::childAreaCheck.GetCheck()) && drawAreaPosItem.size() >= 8)
		{
			CPoint pt[5];
			pt[0] = CPoint((((left+right)/2) + (int)(drawAreaPosItem[4].x*opt)), (((top+bottom)/2) - (int)(drawAreaPosItem[4].y*opt)));
			pt[1] = CPoint((((left+right)/2) + (int)(drawAreaPosItem[5].x*opt)), (((top+bottom)/2) - (int)(drawAreaPosItem[5].y*opt)));
			pt[2] = CPoint((((left+right)/2) + (int)(drawAreaPosItem[6].x*opt)), (((top+bottom)/2) - (int)(drawAreaPosItem[6].y*opt)));
			pt[3] = CPoint((((left+right)/2) + (int)(drawAreaPosItem[7].x*opt)), (((top+bottom)/2) - (int)(drawAreaPosItem[7].y*opt)));
			pt[4] = CPoint((((left+right)/2) + (int)(drawAreaPosItem[4].x*opt)), (((top+bottom)/2) - (int)(drawAreaPosItem[4].y*opt)));
			dc.Polyline(pt, 5);
		}
		dc.SelectPen(old_pen);
		dc.SelectBrush(old_brush);
	}

	CBrush Red;
	Red.CreateSolidBrush(RGB(255, 0, 0));
	CBrush old_brush = dc.SelectBrush(Red);

	//다시 합쳐진 부대 그리기
	int left = (int)(SUBMAPOSDLG_CENTERPOSX + (drawAggPosItem.x*opt))-SUBMAPOSDLG_RECREDSIZE;
	int top = (int)(SUBMAPOSDLG_CENTERPOSY - (drawAggPosItem.y*opt))-SUBMAPOSDLG_RECREDSIZE;
	int right = (int)(SUBMAPOSDLG_CENTERPOSX + (drawAggPosItem.x*opt))+SUBMAPOSDLG_RECREDSIZE;
	int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - (drawAggPosItem.y*opt))+SUBMAPOSDLG_RECREDSIZE;
	dc.Ellipse(left, top, right, bottom);
	dc.SelectBrush(old_brush);

	//영역 크기 텍스트 쓰기
	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetTextColor(RGB(0, 100, 255));
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 21;
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"), 7);
	CFont font;
	font.CreateFontIndirect(&lf);;
	CFont font_old = dc.SelectFont(font);

	CString drawAreaText;
	drawAreaText.Format(_T("작전지역 : %d X %d , px Size : %d "), areaSize.cx, areaSize.cy, latticSize);
	dc.DrawText(drawAreaText.GetBuffer(), drawAreaText.GetLength(), CRect((SUBMAPOSDLG_POSTEXTX - 80), SUBMAPOSDLG_POSTEXTY+10, (SUBMAPOSDLG_POSTEXTX-80) + ((drawAreaText.GetLength()*12)), SUBMAPOSDLG_POSTEXTY+35), DT_TOP|DT_LEFT);
	dc.SelectFont(font_old);
}

int CSubMapPosDlg::drawResolutionPosition(vector<CVector2d> pos, vector<CVector2d> areaPos, CSize _areaSize)
{
	drawPosItem.clear();
	drawPosItem = pos;
	drawAreaPosItem = areaPos;
	areaSize = _areaSize;

	CLogDlg::initStream();
	CLogDlg::insertStream("출력개수 :");
	CLogDlg::insertStream(min((int)drawPosItem.size(), drawPosItemsize), '	');
	CLogDlg::addLogTextStream();

	drawAggPosItem = CResolutionChange::changeAggregatedPosition(pos, drawPosItemsize);

	InvalidateRect(NULL);
	//InvalidateRect를 강제로 바로 실행 하기 위해존제..
	UpdateWindow();
	return drawPosItemsize;
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

LRESULT CSubMapPosDlg::OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(drawPosItem.size())
		clearPosition();
	if(addMapLatticeSelect(CPoint(LOWORD(lParam), HIWORD(lParam))))
	{
		InvalidateRect(NULL);
		//InvalidateRect를 강제로 바로 실행 하기 위해존제..
		UpdateWindow();
	}
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

void CSubMapPosDlg::makeMapLattice(int nRows, int nCols, int nRowDistance, int nColDistance)
{
	CPoint ptInit(1,1);
	CPoint ptMoving = ptInit;
	for (int idxR = 0; idxR < nRows; idxR++)
	{
		for (int idxC = 0; idxC < nCols; idxC++)
		{
			CRect rc;
			rc.left = ptMoving.x;
			rc.right = ptMoving.x+nColDistance;
			rc.top = ptMoving.y;
			rc.bottom = ptMoving.y+nRowDistance;
			mapLattice.push_back(rc);

			ptMoving.x+=nColDistance;
		}
		ptMoving.x = ptInit.x;
		ptMoving.y+=nRowDistance;
	}
}

//void CSubMapPosDlg::drawMapLattice(CDCHandle dc)
//{
//	CBrush brCr1;
//	brCr1.CreateSolidBrush(RGB(192, 0, 0));
//	CBrush old_brush = dc.SelectBrush(brCr1);
//
//	for (int lattice = 0; lattice < (int)mapLattice.size(); lattice+=3)
//	{
//		dc.Rectangle(mapLattice[lattice].left, mapLattice[lattice].top, mapLattice[lattice].right, mapLattice[lattice].bottom);
//	}
//
//	dc.SelectBrush(old_brush);
//
//	CBrush brCr2;
//	brCr2.CreateSolidBrush(RGB(192, 192, 0));
//	old_brush = dc.SelectBrush(brCr2);
//
//	for (int lattice = 1; lattice < (int)mapLattice.size(); lattice+=3)
//	{
//		dc.Rectangle(mapLattice[lattice].left, mapLattice[lattice].top, mapLattice[lattice].right, mapLattice[lattice].bottom);
//	}
//
//	dc.SelectBrush(old_brush);
//
//	CBrush brCr3;
//	brCr3.CreateSolidBrush(RGB(192, 192, 192));
//	old_brush = dc.SelectBrush(brCr3);
//
//	for (int lattice = 2; lattice < (int)mapLattice.size(); lattice+=3)
//	{
//		dc.Rectangle(mapLattice[lattice].left, mapLattice[lattice].top, mapLattice[lattice].right, mapLattice[lattice].bottom);
//	}
//
//	dc.SelectBrush(old_brush);
//}

bool CSubMapPosDlg::addMapLatticeSelect(CPoint point)
{
	bool b = false;
	CRect val = findMapLattice(point);
	if(mapLatticeSelect.end() == find(mapLatticeSelect.begin(), mapLatticeSelect.end(), val))
	{
		mapLatticeSelect.push_back(val);
		selImgMap.push_back(CGAgt::GResCha()->getTopographicChar());
		b = true;
	}
	return b;
}

CRect CSubMapPosDlg::findMapLattice(CPoint point)
{
	CRect result(0, 0, 0, 0);
	for (int la = 0; la < (int)mapLattice.size(); la++)
	{
		if(mapLattice[la].PtInRect(point))
		{
			result = mapLattice[la];
			break;
		}
	}
	return result;
}

bool CSubMapPosDlg::findMapLatticeSelect(int left, int top, int right, int bottom)
{
	bool b = false;
	for (int la = 0; la < (int)mapLatticeSelect.size(); la++)
	{
		CRect rectDiff;
		if(rectDiff.IntersectRect(mapLatticeSelect[la], CRect(left, top, right, bottom)))
		{
			b = true;
			break;
		}
	}
	return b;
}

void CSubMapPosDlg::drawMapLatticeSelect(CDCHandle dc)
{
	//CBrush brCr1;
	//brCr1.CreateSolidBrush(RGB(0, 0, 192));
	//CBrush old_brush = dc.SelectBrush(brCr1);

	
	for (int sel = 0; sel < (int)mapLatticeSelect.size(); sel++)
	{
		CGdiPlusBitmapResource pBitmap;
		pBitmap.Load(mapImgId[selImgMap[sel]],_T("PNG"));
		CBitmap backimage = pBitmap.GetWinBitmap();

		// create memory DC
		dc.SetBkColor(RGB(255,0,0));
		CDC * pMemDC = new CDC;
		pMemDC -> CreateCompatibleDC(dc.m_hDC);
		CBitmapHandle pOldBitmap;

		SIZE bmSize;
		backimage.GetSize(bmSize);
		pOldBitmap = pMemDC -> SelectBitmap(backimage);
		dc.BitBlt(mapLatticeSelect[sel].left,mapLatticeSelect[sel].top,bmSize.cx, bmSize.cy,pMemDC->m_hDC,0,0,SRCCOPY);
		pMemDC -> SelectBitmap(pOldBitmap);
		delete pMemDC;

		//dc.Rectangle(mapLatticeSelect[sel].left, mapLatticeSelect[sel].top, mapLatticeSelect[sel].right, mapLatticeSelect[sel].bottom);
	}

	//dc.SelectBrush(old_brush);
}

void CSubMapPosDlg::baseMapLatticeDraw(CDCHandle dc)
{
	CPen penRed;
	penRed.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen old_pen = dc.SelectPen(penRed);
	//외곽 라인 그리기
	dc.MoveTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_STARTCY);
	dc.LineTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_STARTCY);
	dc.MoveTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_STARTCY);
	dc.LineTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_CY);
	dc.MoveTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_CY);
	dc.LineTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_CY);
	dc.MoveTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_CY);
	dc.LineTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_STARTCY);

	////내부 두꺼운 라인그리기
	//for (int ln = 0; ln < SUBMAPOSDLG_CENTERPOSX; ln+=(SUBMAPOSDLG_DISTX*2))
	//{
	//	dc.MoveTo(SUBMAPOSDLG_CENTERPOSX+ln, SUBMAPOSDLG_STARTCY);
	//	dc.LineTo(SUBMAPOSDLG_CENTERPOSX+ln, SUBMAPOSDLG_CY);

	//	dc.MoveTo(SUBMAPOSDLG_CENTERPOSX-ln, SUBMAPOSDLG_STARTCY);
	//	dc.LineTo(SUBMAPOSDLG_CENTERPOSX-ln, SUBMAPOSDLG_CY);
	//}

	//for (int ln = 0; ln < SUBMAPOSDLG_CENTERPOSY; ln+=(SUBMAPOSDLG_DISTY*2))
	//{
	//	dc.MoveTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_CENTERPOSY+ln);
	//	dc.LineTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_CENTERPOSY+ln);

	//	dc.MoveTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_CENTERPOSY-ln);
	//	dc.LineTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_CENTERPOSY-ln);
	//}	

	dc.MoveTo(SUBMAPOSDLG_CENTERPOSX, SUBMAPOSDLG_STARTCY);
	dc.LineTo(SUBMAPOSDLG_CENTERPOSX, SUBMAPOSDLG_CY);
	dc.MoveTo(SUBMAPOSDLG_STARTCX, SUBMAPOSDLG_CENTERPOSY);
	dc.LineTo(SUBMAPOSDLG_CX, SUBMAPOSDLG_CENTERPOSY);


	dc.SelectPen(old_pen);
	baseMapLatticeDraw(dc, SUBMAPOSDLG_PIXCELX, SUBMAPOSDLG_PIXCELX, SUBMAPOSDLG_DISTX, SUBMAPOSDLG_DISTX);
	
}

void CSubMapPosDlg::baseMapLatticeDraw(CDCHandle dc, int nRows, int nCols, int nRowDistance, int nColDistance)
{
	CPen penRed;
	penRed.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen old_pen = dc.SelectPen(penRed);
	CPoint ptInit(1,1);
	CPoint ptMoving = ptInit;
	for (int idxR = 0; idxR < nRows; idxR++)
	{
		for (int idxC = 0; idxC < nCols; idxC++)
		{
			dc.MoveTo(ptMoving.x, ptMoving.y);
			dc.LineTo(ptMoving.x+nColDistance, ptMoving.y);
			dc.MoveTo(ptMoving.x+nColDistance, ptMoving.y);
			dc.LineTo(ptMoving.x+nColDistance, ptMoving.y+nRowDistance);
			dc.MoveTo(ptMoving.x+nColDistance, ptMoving.y+nRowDistance);
			dc.LineTo(ptMoving.x, ptMoving.y+nRowDistance);
			dc.MoveTo(ptMoving.x, ptMoving.y+nRowDistance);
			dc.LineTo(ptMoving.x, ptMoving.y);
			ptMoving.x+=nColDistance;
		}
		ptMoving.x = ptInit.x;
		ptMoving.y+=nRowDistance;
	}
	dc.SelectPen(old_pen);
}

bool CSubMapPosDlg::examineLatticeSelec(CVector2d vecHiPos, CVector2d parent, float opt)
{
	bool b = false;
	int left = (int)(SUBMAPOSDLG_CENTERPOSX + ((vecHiPos.x-parent.x)*opt))-SUBMAPOSDLG_RECREDSIZE;
	int top = (int)(SUBMAPOSDLG_CENTERPOSY - ((vecHiPos.y-parent.y)*opt))-SUBMAPOSDLG_RECREDSIZE;
	int right = (int)(SUBMAPOSDLG_CENTERPOSX + ((vecHiPos.x-parent.x)*opt))+SUBMAPOSDLG_RECREDSIZE;
	int bottom = (int)(SUBMAPOSDLG_CENTERPOSY - ((vecHiPos.y-parent.y)*opt))+SUBMAPOSDLG_RECREDSIZE;
	if(findMapLatticeSelect(left, top, right, bottom))
	{
		b = true;
	}
	return b;
}

void CSubMapPosDlg::examineMapAffect(vector<CVector2d>& vecHiPos, CSize hiSize, CVector2d parent, CVector2d front, CVector2d cross)
{
	float opt = getMapOpt();
	//float move = sqrt(pow((float)(hiSize.cy/2), 2)/(float)2);
	float move = (float)(hiSize.cy/2);
	for (int hP = 0; hP < (int)vecHiPos.size(); hP++)
	{
		if(examineLatticeSelec(vecHiPos[hP], parent, opt))
		{
			vector<int> rdVec;
			vector<CVector2d> result;
			result.resize(3);
			result[0] = vecHiPos[hP] + front*(move*-1);
			if(false == examineLatticeSelec(result[0], parent, opt))
			{
				rdVec.push_back(0);
			}
			result[1] = vecHiPos[hP] + front*(move*-1) + cross*(move*-1);
			if(false == examineLatticeSelec(result[1], parent, opt))
			{
				rdVec.push_back(1);
			}
			result[2] = vecHiPos[hP] + front*(move*-1) + cross*(move);
			if(false == examineLatticeSelec(result[2], parent, opt))
			{
				rdVec.push_back(2);
			}
			if(rdVec.size())
			{
				int rd = rand()%rdVec.size();
				vecHiPos[hP] = result[rdVec[rd]];
			}
		}
	}	
}