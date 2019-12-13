// LogDlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//�α� ��� ��ü
class CLogDlg : public CDialogImpl<CLogDlg>
{
	//csv ���� ��� ���� üũ�ڽ�
	static CButton csvLogCheck;
public:
	//�α� ���� ���� ��ü
	static CLogDlg* gLogDlg;
	//�α� ���� ��Ʈ��
	static std::stringstream mkLog;
	//��Ʈ�� ù��° �Է� ����
	static bool bFirst;
	//csv �ľ� ���� ��Ʈ��
	static std::stringstream mkcsvLog;

	enum { IDD = IDD_LOGPOPUP };

	BEGIN_MSG_MAP(CLogDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	//������
	CLogDlg();
	//�Ҹ���
	~CLogDlg();
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	//�α� ��ü ���� �䱸
	CString CLogDlg::getLogText();

	//�α� ���� ���
	void CLogDlg::setLogText(CString text);

	//�Է� ���� ��� ���� �Լ�
	static void AddLogText(CString text);
	static void AddLogText(vector<int> text, char delimiter = ' ');
	static void AddLogText(vector<string> text, char delimiter = ' ');
	static void AddLogText(vector<CString> text, char delimiter = ' ');
	static void AddLogText(vector<float> text, char delimiter = ' ');

	//��Ʈ�� ��� �Լ�
	//��Ʈ�� �ʱ�ȭ
	static void initStream();
	//��Ʈ�� �߰� �Լ� - �����Լ���
	static void insertStream(string str, char delimiter = ' ');
	static void insertStream(wstring str, char delimiter = ' ');
	static void insertStream(int val, char delimiter = ' ');
	static void insertStream(float val, char delimiter = ' ');
	static void insertStreamVec(vector<int> val, char delimiter = ' ');
	static void insertStreamVec(vector<float> val, char delimiter = ' ');
	static void insertStreamVec(vector<string> val, char delimiter = ' ');
	//��Ʈ�� ���� ���� �α� ��� �Լ�
	static void addLogTextStream();
};
