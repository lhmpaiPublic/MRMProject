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
	incDeployment.AddString(CStringW("���ﰢ��"));
	incDeployment.AddString(CStringW("�ﰢ��(����)"));
	incDeployment.AddString(CStringW("����"));
	incDeployment.AddString(CStringW("Ⱦ��"));
	incDeployment.SetCurSel(0);

	incDirection.Attach(GetDlgItem(IDCC_INDIRECTION));
	incDirection.AddString(CStringW("��"));
	incDirection.AddString(CStringW("�ϵ�"));
	incDirection.AddString(CStringW("��"));
	incDirection.AddString(CStringW("����"));
	incDirection.AddString(CStringW("��"));
	incDirection.AddString(CStringW("����"));
	incDirection.AddString(CStringW("��"));
	incDirection.AddString(CStringW("�ϼ�"));
	incDirection.SetCurSel(0);

	incUnitPosture.Attach(GetDlgItem(IDCC_INUNITPOSTURE));
	incUnitPosture.AddString(CStringW("���"));
	incUnitPosture.AddString(CStringW("����"));
	incUnitPosture.SetCurSel(0);

	incUnitType.Attach(GetDlgItem(IDCC_INUNITTYPE));
	incUnitType.AddString(CStringW("����"));
	incUnitType.AddString(CStringW("����"));
	incUnitType.AddString(CStringW("����"));
	incUnitType.SetCurSel(0);

	incUnitBlueRed.Attach(GetDlgItem(IDCC_INUNITBLUERED));
	incUnitBlueRed.AddString(CStringW("û��"));
	incUnitBlueRed.AddString(CStringW("ȫ��"));
	incUnitBlueRed.SetCurSel(0);

	incUnitScale.Attach(GetDlgItem(IDCC_INUNITSCALE));
	incUnitScale.AddString(CStringW("�д�"));
	incUnitScale.AddString(CStringW("�Ҵ�"));
	incUnitScale.AddString(CStringW("�ߴ�"));
	incUnitScale.AddString(CStringW("���"));
	incUnitScale.SetCurSel(0);

	incMapImpact.Attach(GetDlgItem(IDCC_INMAPIMPACT));
	incMapImpact.AddString(CStringW("��ü1"));
	incMapImpact.AddString(CStringW("��ü2"));
	incMapImpact.AddString(CStringW("��ü3"));
	incMapImpact.AddString(CStringW("��ü4"));
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

