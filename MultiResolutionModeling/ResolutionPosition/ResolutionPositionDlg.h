// ResolutionPositionDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//위치변환 출력 객체
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

	CSubMapPosDlg* mSubMapPosDlg;

	CRect winPos;
	CPoint startPoint;
	bool bLClick;

	//엑셀 오토메이션
	//CXLEzAutomation* xlEz;
public:
	static CButton childAreaCheck;

	CSubMapPosDlg* foSMPDg();

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
		COMMAND_HANDLER(IDCB_RESOLUTIONCLEAR, BN_CLICKED, OnBnClickedResolutionclear)
		COMMAND_HANDLER(IDCC_INUNITTYPE, CBN_SELCHANGE, OnCbnSelchangeInunittype)
		COMMAND_HANDLER(IDCC_INUNITSCALE, CBN_SELCHANGE, OnCbnSelchangeInunitscale)

		COMMAND_HANDLER(IDCC_INDEPLOYMENT, CBN_SELCHANGE, OnCbnSelchangeDefault)
		COMMAND_HANDLER(IDCC_INUNITPOSTURE, CBN_SELCHANGE, OnCbnSelchangeDefault)
		COMMAND_HANDLER(IDCC_INUNITBLUERED, CBN_SELCHANGE, OnCbnSelchangeDefault)
		COMMAND_HANDLER(IDCC_INDIRECTION, CBN_SELCHANGE, OnCbnSelchangeDefault)		
		COMMAND_HANDLER(IDCC_INDIVISIONCOUNT, CBN_SELCHANGE, OnCbnSelchangeDefault)

		COMMAND_HANDLER(IDCC_INMAPIMPACT, CBN_SELCHANGE, OnCbnSelchangeInMapImpact)

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
	LRESULT OnBnClickedResolutionclear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	
	LRESULT OnCbnSelchangeInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnCbnSelchangeDefault(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnCbnSelchangeInMapImpact(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	//고해상도 분할 개체 수 요구
	vector<CString> strDivisionCount(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil);
	//콤보박스에 있는 분할 개체 수 요구
	int valDivisionCount(int selNum);
	//선택 맵 번호
	UINT getMapSelect();
	
};
