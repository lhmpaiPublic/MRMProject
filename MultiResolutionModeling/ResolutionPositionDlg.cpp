// ResolutionPositionDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "LogDlg.h"
#include "ResolutionPositionDlg.h"
#include "GAgt.h"
#include "ResolutionChange.h"



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

	CGAgt::GResCha()->setParentPos(CVector2d(308320.0f, 4191390.0f));

	incDeployment.Attach(GetDlgItem(IDCC_INDEPLOYMENT));
	incDeployment.AddString(CStringW("역삼각대"));
	incDeployment.AddString(CStringW("원형"));
	incDeployment.AddString(CStringW("종대"));
	incDeployment.AddString(CStringW("횡대"));
	incDeployment.AddString(CStringW("삼각대"));
	incDeployment.SetCurSel(0);
	CGAgt::GResCha()->setDeploymentType(CResolutionChange::DEP_INVERTEDTRIANGLE);
	

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
	CGAgt::GResCha()->setDirectionType(CResolutionChange::N_DIRECTION);
	
	incUnitPosture.Attach(GetDlgItem(IDCC_INUNITPOSTURE));
	incUnitPosture.AddString(CStringW("방어"));
	incUnitPosture.AddString(CStringW("공격"));
	incUnitPosture.SetCurSel(0);
	CGAgt::GResCha()->setMoveType(CUnitSize::DEFENCE);

	incUnitType.Attach(GetDlgItem(IDCC_INUNITTYPE));
	incUnitType.AddString(CStringW("보병"));
	incUnitType.AddString(CStringW("전차"));
	incUnitType.AddString(CStringW("포병"));
	incUnitType.SetCurSel(0);
	CGAgt::GResCha()->setCombatent(CUnitSize::INFANTRY);

	CUnitSize::COMBATANT combatType = CUnitSize::INFANTRY;

	incUnitBlueRed.Attach(GetDlgItem(IDCC_INUNITBLUERED));
	incUnitBlueRed.AddString(CStringW("청군"));
	incUnitBlueRed.AddString(CStringW("홍군"));
	incUnitBlueRed.SetCurSel(0);
	CGAgt::GResCha()->setForce(CUnitSize::BLUEFORCE);

	incUnitScale.Attach(GetDlgItem(IDCC_INUNITSCALE));
	vector<CString> unitScale = CUnitSize::strMilitarybranch(combatType);
	for (int i = 0; i < (int)unitScale.size(); i++)
	{
		incUnitScale.AddString(unitScale[i]);
	}
	incUnitScale.SetCurSel(0);
	CGAgt::GResCha()->setMilitarybranch(CUnitSize::emMilitarybranch(combatType, 0));

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
	incDivisionCount.SetCurSel(3);

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


LRESULT CResolutionPositionDlg::OnBnClickedResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGAgt::GResCha()->setParentPos(CVector2d((float)GetDlgItemInt(IDCE_INPOSX), (float)GetDlgItemInt(IDCE_INPOSY)));
	CGAgt::GResCha()->setDeploymentType(CResolutionChange::emDeploymentType(incDeployment.GetCurSel()));
	CGAgt::GResCha()->setDirectionType(CResolutionChange::emDirectionType(incDirection.GetCurSel()));
	CGAgt::GResCha()->setMoveType(CUnitSize::emMoveType(incUnitPosture.GetCurSel()));
	CGAgt::GResCha()->setCombatent(CUnitSize::emCombatent(incUnitType.GetCurSel()));
	CUnitSize::COMBATANT combatType = CUnitSize::emCombatent(incUnitType.GetCurSel());
	CGAgt::GResCha()->setCombatent(combatType);
	CGAgt::GResCha()->setForce(CUnitSize::emForce(incUnitBlueRed.GetCurSel()));

	CGAgt::GResCha()->setMilitarybranch(CUnitSize::emMilitarybranch(combatType, incUnitScale.GetCurSel()));

	CGAgt::GResCha()->changeDisaggregated();
	return 0;
}

LRESULT CResolutionPositionDlg::OnCbnSelchangeInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	incUnitScale.ResetContent();
	CUnitSize::COMBATANT combatType = CUnitSize::emCombatent(incUnitType.GetCurSel());
	vector<CString> unitScale = CUnitSize::strMilitarybranch(combatType);
	for (int i = 0; i < (int)unitScale.size(); i++)
	{
		incUnitScale.AddString(unitScale[i]);
	}
	incUnitScale.SetCurSel(0);

	return 0;
}
