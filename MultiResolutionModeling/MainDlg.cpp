// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "aboutdlg.h"


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

namespace emMainDlgBV
{
	enum na1
	{
		DATA0 = 0,
		DATA1,
		DATA2,
		DATA3,
		DATA4,
		DATA5,
	};
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	//BaseValue 테스트 코드
	bv::BaseValue va;
	va.add(emMainDlgBV::DATA0, 3.141592, 8);
	va.add(emMainDlgBV::DATA1, 3);
	va.add(emMainDlgBV::DATA2, "한글저장안시");
	va.add_wstring(emMainDlgBV::DATA3, L"유니코드한글");

	va.add_BV(emMainDlgBV::DATA4, va);

	vector<int> keys = va.get_Keys();

	vector<string> value_data = va.get_Values_data();

	wstring val1 = va.get_wstring(emMainDlgBV::DATA3);

	double dVal = va.get<double>(emMainDlgBV::DATA0);

	std::string valtoken = va.get_tokenize();

	bv::BaseValue va2;
	va2.parsing(valtoken);
	va2.add_wstring(emMainDlgBV::DATA5, L"유니코드한글추가데이터");

	va2.add_autoName(100);
	va2.add_autoName(101);

	keys = va2.get_Keys();

	value_data = va2.get_Values_data();


	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
	//=============================================
	//  Gdiplus 사용 시작
	//=============================================
	CGdiPlusBitmap::GdiStart();

	if(NULL == CLogDlg::gLogDlg)
	{
		CLogDlg::gLogDlg = new CLogDlg();
		CLogDlg::gLogDlg->Create(m_hWnd);
	} 

	CGAgt::G()->initGAgt(m_hWnd);

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	//=============================================
	//  Gdiplus 사용 종료
	//=============================================
	CGdiPlusBitmap::GdiShut();

	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CLogDlg::gLogDlg->DestroyWindow();
	CGAgt::G()->releaseDlg();
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBnClickedLogwindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(NULL == CLogDlg::gLogDlg)
	{
		CLogDlg::gLogDlg = new CLogDlg();
		CLogDlg::gLogDlg->Create(m_hWnd);
	}
	CLogDlg::gLogDlg->ShowWindow(SW_SHOW);
	return 0;
}


LRESULT CMainDlg::OnBnClickedResposwin(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGAgt::G()->ShowDlg(CGAgt::RESPOS);
	return 0;
}

LRESULT CMainDlg::OnBnClickedRespropertywin(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CGAgt::G()->ShowDlg(CGAgt::RESPPTY);
	return 0;
}

LRESULT CMainDlg::OnBnClickedReshipropwin(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CGAgt::G()->ShowDlg(CGAgt::RESHPPTY);
	return 0;
}
