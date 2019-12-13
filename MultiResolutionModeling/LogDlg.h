// LogDlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//로그 출력 개체
class CLogDlg : public CDialogImpl<CLogDlg>
{
	//csv 파일 출력 여부 체크박스
	static CButton csvLogCheck;
public:
	//로그 전역 접근 객체
	static CLogDlg* gLogDlg;
	//로그 저장 스트립
	static std::stringstream mkLog;
	//스트립 첫번째 입력 여부
	static bool bFirst;
	//csv 파알 저장 스트립
	static std::stringstream mkcsvLog;

	enum { IDD = IDD_LOGPOPUP };

	BEGIN_MSG_MAP(CLogDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	//생성자
	CLogDlg();
	//소멸자
	~CLogDlg();
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//로그 전체 내용 요구
	CString CLogDlg::getLogText();

	//로그 내용 출력
	void CLogDlg::setLogText(CString text);

	//입력 내용 출력 서브 함수
	static void AddLogText(CString text);
	static void AddLogText(vector<int> text, char delimiter = ' ');
	static void AddLogText(vector<string> text, char delimiter = ' ');
	static void AddLogText(vector<CString> text, char delimiter = ' ');
	static void AddLogText(vector<float> text, char delimiter = ' ');

	//스트림 출력 함수
	//스트림 초기화
	static void initStream();
	//스트립 추가 함수 - 서브함수들
	static void insertStream(string str, char delimiter = ' ');
	static void insertStream(wstring str, char delimiter = ' ');
	static void insertStream(int val, char delimiter = ' ');
	static void insertStream(float val, char delimiter = ' ');
	static void insertStreamVec(vector<int> val, char delimiter = ' ');
	static void insertStreamVec(vector<float> val, char delimiter = ' ');
	static void insertStreamVec(vector<string> val, char delimiter = ' ');
	//스트립 저장 내용 로그 출력 함수
	static void addLogTextStream();
};
