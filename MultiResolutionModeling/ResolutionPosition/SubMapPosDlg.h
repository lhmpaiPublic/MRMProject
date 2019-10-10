// SubMapPosDlg.h : interface of the CSubMapPosDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define IMAGE_MAX 8
class CSubMapPosDlg : public CDialogImpl<CSubMapPosDlg>, public CMessageFilter
{
	//
	static UINT imgId[IMAGE_MAX];

	HWND hWnd;

	vector<CVector2d> drawPosItem;
	int typeOption;
	CVector2d drawAggPosItem;
	vector<CVector2d> drawAreaPosItem;
public:
	enum { IDD = IDD_SUBMAPPOSDLG };

	BEGIN_MSG_MAP(CSubMapPosDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
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

	void drawResolutionPosition(vector<CVector2d> pos, int typeOp, CVector2d aggPos, vector<CVector2d> areaPos);
};
