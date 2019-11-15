// SubMapPosDlg.h : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define IMAGE_MAX 8
#define MAPIMAGE_MAX 7
class CSubMapPosDlg : public CDialogImpl<CSubMapPosDlg>, public CMessageFilter
{
	//
	static UINT imgId[IMAGE_MAX];
	static UINT mapImgId[MAPIMAGE_MAX];

	HWND hWnd;

	vector<CVector2d> drawPosItem;
	CVector2d drawAggPosItem;
	vector<CVector2d> drawAreaPosItem;
	int drawPosItemsize;
	CSize areaSize;

	CRect winPos;
	CPoint startPoint;
	bool bLClick;


	CSize winSz;
	vector<CRect> mapLattice;
	vector<CRect> mapLatticeSelect;
	vector<UINT> selImgMap;

	int latticSize;
public:
	enum { IDD = IDD_SUBMAPPOSDLG };

	BEGIN_MSG_MAP(CSubMapPosDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnLMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	int moveindex;
	//======================================================//
	//			
	//======================================================//
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	//생성자
	CSubMapPosDlg();
	//초기값 설정함수
	void init(HWND _hWnd);
	//Dlg 종료 함수
	void DlgClose();
	//위치 변환 지우기
	void clearAll();
	void clearPosition();
	void clearMapPos();
	//Dlg 초기화 
	//======================================================//
	//			초기화
	//======================================================//
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//======================================================//
	//			윈도우 파괴함수
	//======================================================//
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//--------------------------------------------------------------
	//|
	//|
	//|
	//---------------------------------------------------------------
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	//--------------------------------------------------------------
	//|
	//|
	//|
	//---------------------------------------------------------------
	BOOL PreTranslateMessage(MSG* pMsg);

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	//--------------------------------------------------------------
	//|
	//|
	//|
	//---------------------------------------------------------------
	void buttonAnimation();
	//
	//--------------------------------------------------------------
	//|
	//|
	//|
	//---------------------------------------------------------------
	BOOL OnEraseBkgnd(CDCHandle dc);

	void drawResolutionPos(CDCHandle dc);

	void drawResolutionPosition(vector<CVector2d> pos, vector<CVector2d> areaPos, CSize _areaSize);
	void drawResolutionPositionSize(int drawSize);

	void makeMapLattice(int nRows, int nCols, int nRowDistance, int nColDistance);
	//void drawMapLattice(CDCHandle dc);
	bool addMapLatticeSelect(CPoint point);
	CRect findMapLattice(CPoint point);
	bool findMapLatticeSelect(int left, int top, int right, int bottom);
	void drawMapLatticeSelect(CDCHandle dc);
	float getMapOpt();

	//기본 맵 격자 그리기
	void baseMapLatticeDraw(CDCHandle dc);
	void baseMapLatticeDraw(CDCHandle dc, int nRows, int nCols, int nRowDistance, int nColDistance);
	
	//그릴 좌표의 격자 검사하여 지형의 영향에 이동 위치 계산
	void examineMapAffect(vector<CVector2d>& vecHiPos, CSize hiSize, CVector2d parent, CVector2d front, CVector2d cross);

	bool examineLatticeSelec(CVector2d vecHiPos, CVector2d parent, float opt);
};
