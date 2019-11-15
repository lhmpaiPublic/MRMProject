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
	//������
	CSubMapPosDlg();
	//�ʱⰪ �����Լ�
	void init(HWND _hWnd);
	//Dlg ���� �Լ�
	void DlgClose();
	//��ġ ��ȯ �����
	void clearAll();
	void clearPosition();
	void clearMapPos();
	//Dlg �ʱ�ȭ 
	//======================================================//
	//			�ʱ�ȭ
	//======================================================//
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//======================================================//
	//			������ �ı��Լ�
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

	//�⺻ �� ���� �׸���
	void baseMapLatticeDraw(CDCHandle dc);
	void baseMapLatticeDraw(CDCHandle dc, int nRows, int nCols, int nRowDistance, int nColDistance);
	
	//�׸� ��ǥ�� ���� �˻��Ͽ� ������ ���⿡ �̵� ��ġ ���
	void examineMapAffect(vector<CVector2d>& vecHiPos, CSize hiSize, CVector2d parent, CVector2d front, CVector2d cross);

	bool examineLatticeSelec(CVector2d vecHiPos, CVector2d parent, float opt);
};
