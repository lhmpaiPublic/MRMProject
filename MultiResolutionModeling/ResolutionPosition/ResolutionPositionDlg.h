// ResolutionPositionDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CSubMapPosDlg;
class CResolutionPositionDlg : public CDialogImpl<CResolutionPositionDlg>, public CUpdateUI<CResolutionPositionDlg>,
		public CMessageFilter, public CIdleHandler
{
	CEdit inePosX;
	CEdit inePosY;
	CComboBox incDeployment;
	CComboBox incDirection;
	CComboBox incUnitPosture;
	CComboBox incUnitType;
	CComboBox incUnitBlueRed;
	CComboBox incUnitScale;
	CComboBox incMapImpact;
	CComboBox incDivisionCount;

	CSubMapPosDlg* subMapPosDlg;

	CRect winPos;
	CPoint startPoint;
	bool bLClick;
public:
	enum { IDD = IDD_RESOLUTIONPOSITION };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CResolutionPositionDlg)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CResolutionPositionDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDCB_RESOLUTIONCHANGE, BN_CLICKED, OnBnClickedResolutionchange)
		COMMAND_HANDLER(IDCC_INUNITTYPE, CBN_SELCHANGE, OnCbnSelchangeInunittype)
		COMMAND_HANDLER(IDCC_INUNITSCALE, CBN_SELCHANGE, OnCbnSelchangeInunitscale)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnLMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		REFLECT_NOTIFICATIONS()		
		
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	
	LRESULT OnCbnSelchangeInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void drawResolutionPosition(vector<CVector2d> pos, int typeOp, vector<CVector2d> areaPos, CString text);

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	vector<CString> strDivisionCount(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil);
	int valDivisionCount(int selNum);
};
