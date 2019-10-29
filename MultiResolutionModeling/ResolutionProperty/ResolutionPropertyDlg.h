// ResolutionPropertyDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CResolutionPropertyDlg : public CDialogImpl<CResolutionPropertyDlg>, public CUpdateUI<CResolutionPropertyDlg>,
		public CMessageFilter, public CIdleHandler
{

	CRect winPos;
	CPoint startPoint;
	bool bLClick;
	CListCtrl m_lowModelList;
	CListCtrl m_hiModelList;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;

	CComboBox inUnitType;
	CComboBox inUnitScale;
	CComboBox propertyDiv;

public:
	CResolutionPropertyDlg();

	~CResolutionPropertyDlg();

	enum { IDD = IDD_RESOLUTIONPROPERTY };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CResolutionPropertyDlg)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CResolutionPropertyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnLMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		COMMAND_HANDLER(IDCC_PPTY_INUNITTYPE, CBN_SELCHANGE, OnCbnSelchangePptyInunittype)
		COMMAND_HANDLER(IDCC_PPTY_INUNITSCALE, CBN_SELCHANGE, OnCbnSelchangePptyInunitscale)
		COMMAND_HANDLER(IDCC_PPTY_PROPERTYDIV, CBN_SELCHANGE, OnCbnSelchangePptyPropertydiv)

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

	void CloseDialog(int nVal);
	
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangePptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangePptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangePptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
