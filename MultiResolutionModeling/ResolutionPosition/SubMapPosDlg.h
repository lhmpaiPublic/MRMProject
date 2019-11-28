// SubMapPosDlg.h : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define IMAGE_MAX 8
#define MAPIMAGE_MAX 7
//위치 좌표 표현 객체
class CSubMapPosDlg : public CDialogImpl<CSubMapPosDlg>, public CMessageFilter
{
	//
	static UINT imgId[IMAGE_MAX];
	static UINT mapImgId[MAPIMAGE_MAX];
	//부모 핸들
	HWND hWnd;
	//저해상도 위치좌표
	vector<CVector2d> drawPosItem;
	//고해상도 위치좌표
	CVector2d drawAggPosItem;
	//부대 영역 표시 
	vector<CVector2d> drawAreaPosItem;
	//그릴 위치 개체 수
	int drawPosItemsize;
	//영역 크기
	CSize areaSize;

	//마우스로 화면 이동
	//윈도우 영역
	CRect winPos;
	//시작점
	CPoint startPoint;
	//클릭 여부
	bool bLClick;

	//화면 크기
	CSize winSz;
	//맵 격자 저장
	vector<CRect> mapLattice;
	//선택된 맵 격자
	vector<CRect> mapLatticeSelect;
	//격자 선택 이미지 번호
	vector<UINT> selImgMap;

	//격자 크기
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

	int drawResolutionPosition(vector<CVector2d> pos, vector<CVector2d> areaPos, CSize _areaSize);
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
