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

namespace CMainDlgBVEm
{
	enum BVValue
	{
		FDDATA0 = BVEm::FD+0,
		IIDATA1 = BVEm::II+1,
		SSDATA2 = BVEm::SS+2,
		SWDATA3 = BVEm::SW+3,
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

	////BaseValue 테스트 코드
	//BaseValue va;
	//va.add(CMainDlgBVEm::FDDATA0, 3.141592);
	//va.add(CMainDlgBVEm::IIDATA1, 3);
	//va.add(CMainDlgBVEm::SSDATA2, "한글저장안시");
	//va.add_wstring(CMainDlgBVEm::SWDATA3, L"유니코드한글");

	//vector<int> keys = va.get_Keys();

	//wstring val1 = va.get_wstring(CMainDlgBVEm::SWDATA3);

	//std::string valtoken = va.get_tokenize();

	//vector<std::string> valpar = va.tokenize_getline(valtoken);

	//BaseValue va2;
	//va2.parsing(valtoken);


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
