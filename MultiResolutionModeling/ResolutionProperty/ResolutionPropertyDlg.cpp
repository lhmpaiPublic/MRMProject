// ResolutionPropertyDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolutionPropertyDlg.h"
#include "PropertyList.h"


BOOL CResolutionPropertyDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CResolutionPropertyDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

LRESULT CResolutionPropertyDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	startPoint = CPoint(0, 0);
	bLClick = false;
	GetWindowRect(winPos);

	CPropertyList test;
	test.loadCSVFile("infantryPropertyList.csv");
	
	return TRUE;
}

LRESULT CResolutionPropertyDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CResolutionPropertyDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void CResolutionPropertyDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CResolutionPropertyDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	GetWindowRect(winPos);
	SetCapture();
	bLClick = true;
	startPoint = CPoint(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(bLClick)
	{
		GetWindowRect(winPos);
		SetWindowPos(NULL, winPos.left+(LOWORD(lParam) - startPoint.x), winPos.top+(HIWORD(lParam) - startPoint.y), 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	bLClick = false;
	ReleaseCapture();
	return 0;
}
