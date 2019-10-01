// ResolutionPositionDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "LogDlg.h"
#include "ResolutionPositionDlg.h"



BOOL CResolutionPositionDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CResolutionPositionDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

LRESULT CResolutionPositionDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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
	
	inePosX.Attach(GetDlgItem(IDCE_INPOSX));
	inePosX.SetWindowText(CStringW("308320"));
	inePosY.Attach(GetDlgItem(IDCE_INPOSY));
	inePosY.SetWindowText(CStringW("4191390"));
	incDeployment.Attach(GetDlgItem(IDCC_INDEPLOYMENT));
	incDeployment.AddString(CStringW("역삼각대"));
	incDeployment.AddString(CStringW("삼각대(원형)"));
	incDeployment.AddString(CStringW("종대"));
	incDeployment.AddString(CStringW("횡대"));
	incDeployment.SetCurSel(0);

	incDirection.Attach(GetDlgItem(IDCC_INDIRECTION));
	incDirection.AddString(CStringW("북"));
	incDirection.AddString(CStringW("북동"));
	incDirection.AddString(CStringW("동"));
	incDirection.AddString(CStringW("남동"));
	incDirection.AddString(CStringW("남"));
	incDirection.AddString(CStringW("남서"));
	incDirection.AddString(CStringW("서"));
	incDirection.AddString(CStringW("북서"));
	incDirection.SetCurSel(0);

	incUnitPosture.Attach(GetDlgItem(IDCC_INUNITPOSTURE));
	incUnitPosture.AddString(CStringW("방어"));
	incUnitPosture.AddString(CStringW("공격"));
	incUnitPosture.SetCurSel(0);

	incUnitType.Attach(GetDlgItem(IDCC_INUNITTYPE));
	incUnitType.AddString(CStringW("보병"));
	incUnitType.AddString(CStringW("전차"));
	incUnitType.AddString(CStringW("포병"));
	incUnitType.SetCurSel(0);

	incUnitBlueRed.Attach(GetDlgItem(IDCC_INUNITBLUERED));
	incUnitBlueRed.AddString(CStringW("청군"));
	incUnitBlueRed.AddString(CStringW("홍군"));
	incUnitBlueRed.SetCurSel(0);

	incUnitScale.Attach(GetDlgItem(IDCC_INUNITSCALE));
	incUnitScale.AddString(CStringW("분대"));
	incUnitScale.AddString(CStringW("소대"));
	incUnitScale.AddString(CStringW("중대"));
	incUnitScale.AddString(CStringW("대대"));
	incUnitScale.SetCurSel(0);

	incMapImpact.Attach(GetDlgItem(IDCC_INMAPIMPACT));
	incMapImpact.AddString(CStringW("개체1"));
	incMapImpact.AddString(CStringW("개체2"));
	incMapImpact.AddString(CStringW("개체3"));
	incMapImpact.AddString(CStringW("개체4"));
	incMapImpact.SetCurSel(0);

	incDivisionCount.Attach(GetDlgItem(IDCC_INDIVISIONCOUNT));
	incDivisionCount.AddString(CStringW("1"));
	incDivisionCount.AddString(CStringW("2"));
	incDivisionCount.AddString(CStringW("3"));
	incDivisionCount.AddString(CStringW("4"));
	incDivisionCount.SetCurSel(0);

	return TRUE;
}

LRESULT CResolutionPositionDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CResolutionPositionDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CResolutionPositionDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void CResolutionPositionDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

