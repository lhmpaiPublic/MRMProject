// LogDlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CLogDlg : public CDialogImpl<CLogDlg>
{
	static CButton csvLogCheck;
public:
	static CLogDlg* gLogDlg;
	static std::stringstream mkLog;
	static bool bFirst;

	static std::stringstream mkcsvLog;
	enum { IDD = IDD_LOGPOPUP };

	BEGIN_MSG_MAP(CLogDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	//持失切
	CLogDlg();
	//社瑚切
	~CLogDlg();
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	CString CLogDlg::getLogText();

	void CLogDlg::setLogText(CString text);

	static void AddLogText(CString text);

	static void AddLogText(vector<int> text, char delimiter = ' ');

	static void AddLogText(vector<string> text, char delimiter = ' ');

	static void AddLogText(vector<CString> text, char delimiter = ' ');

	static void initStream();
	static void insertStream(string str, char delimiter = ' ');
	static void insertStream(int val, char delimiter = ' ');
	static void insertStreamVec(vector<int> val, char delimiter = ' ');
	static void insertStreamVec(vector<float> val, char delimiter = ' ');
	static void insertStreamVec(vector<string> val, char delimiter = ' ');
	static void addLogTextStream();
};
