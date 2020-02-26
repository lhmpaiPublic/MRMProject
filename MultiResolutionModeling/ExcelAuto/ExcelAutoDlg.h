// ExcelAutoDlg.h : interface of the ExcelAutoDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CXLEzAutomation;
//XMLDlg
class CExcelAutoDlg : public CDialogImpl<CExcelAutoDlg>,
		public CMessageFilter, public CIdleHandler
{
	//ø¢ºø ø¿≈‰∏ﬁ¿Ãº«
	CXLEzAutomation* xlEz;
public:

	enum { IDD = IDD_EXCELAUTODLG };

	CExcelAutoDlg();

	~CExcelAutoDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_MSG_MAP(CExcelAutoDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_EXCELAUTOSTART, BN_CLICKED, OnBnClickedExcelautostart)
		COMMAND_HANDLER(IDC_EXCELAUTORELEASE, BN_CLICKED, OnBnClickedExcelautorelease)
		REFLECT_NOTIFICATIONS()		
		
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	LRESULT OnBnClickedExcelautostart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedExcelautorelease(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
