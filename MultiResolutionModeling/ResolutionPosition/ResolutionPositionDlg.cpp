// ResolutionPositionDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolutionPositionDlg.h"
#include "SubMapPosDlg.h"


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

	startPoint = CPoint(0, 0);
	bLClick = false;
	GetWindowRect(winPos);
	
	inePosX.Attach(GetDlgItem(IDCE_INPOSX));
	inePosX.SetWindowText(CStringW("308320"));
	inePosY.Attach(GetDlgItem(IDCE_INPOSY));
	inePosY.SetWindowText(CStringW("4191390"));

	CGAgt::GResCha()->setParentPos(CVector2d(308320.0f, 4191390.0f));

	incDeployment.Attach(GetDlgItem(IDCC_INDEPLOYMENT));
	vector<CString> deployment = CResolutionChange::strDeploymentType(CUnitSize::INFANTRY, CUnitSize::INFANTRY_SQUAD);
	for (int i = 0; i < (int)deployment.size(); i++)
	{
		incDeployment.AddString(deployment[i]);
	}
	incDeployment.SetCurSel(0);
	CGAgt::GResCha()->setDeploymentType(CResolutionChange::emDeploymentType(CUnitSize::INFANTRY, CUnitSize::INFANTRY_SQUAD, incDeployment.GetCurSel()));
	

	incDirection.Attach(GetDlgItem(IDCC_INDIRECTION));
	vector<CString> dirctionType = CResolutionChange::strDirectionType();
	for (int i = 0; i < (int)dirctionType.size(); i++)
	{
		incDirection.AddString(dirctionType[i]);
	}
	incDirection.SetCurSel(0);
	CGAgt::GResCha()->setDirectionType(CResolutionChange::emDirectionType(incDirection.GetCurSel()));
	
	incUnitPosture.Attach(GetDlgItem(IDCC_INUNITPOSTURE));
	vector<CString> unitPosture = CUnitSize::strMoveType();
	for (int i = 0; i < (int)unitPosture.size(); i++)
	{
		incUnitPosture.AddString(unitPosture[i]);
	}
	incUnitPosture.SetCurSel(0);
	CGAgt::GResCha()->setMoveType(CUnitSize::emMoveType(incUnitPosture.GetCurSel()));

	incUnitType.Attach(GetDlgItem(IDCC_INUNITTYPE));
	vector<CString> unitType = CUnitSize::strCombatent();
	for (int i = 0; i < (int)unitType.size(); i++)
	{
		incUnitType.AddString(unitType[i]);
	}
	incUnitType.SetCurSel(0);
	CUnitSize::COMBATANT combatType = CUnitSize::emCombatent(incUnitType.GetCurSel());
	CGAgt::GResCha()->setCombatent(combatType);


	incUnitBlueRed.Attach(GetDlgItem(IDCC_INUNITBLUERED));
	vector<CString> unitBlueRed = CUnitSize::strForce();
	for (int i = 0; i < (int)unitBlueRed.size(); i++)
	{
		incUnitBlueRed.AddString(unitBlueRed[i]);
	}
	incUnitBlueRed.SetCurSel(0);
	CGAgt::GResCha()->setForce(CUnitSize::emForce(incUnitBlueRed.GetCurSel()));

	incUnitScale.Attach(GetDlgItem(IDCC_INUNITSCALE));
	vector<CString> unitScale = CUnitSize::strMilitarybranch(combatType);
	for (int i = 0; i < (int)unitScale.size(); i++)
	{
		incUnitScale.AddString(unitScale[i]);
	}
	incUnitScale.SetCurSel(0);
	CGAgt::GResCha()->setMilitarybranch(CUnitSize::emMilitarybranch(combatType, incUnitScale.GetCurSel()));

	incMapImpact.Attach(GetDlgItem(IDCC_INMAPIMPACT));
	incMapImpact.AddString(CStringW("개체1"));
	incMapImpact.AddString(CStringW("개체2"));
	incMapImpact.AddString(CStringW("개체3"));
	incMapImpact.AddString(CStringW("개체4"));
	incMapImpact.SetCurSel(0);

	incDivisionCount.Attach(GetDlgItem(IDCC_INDIVISIONCOUNT));
	vector<CString> divisionCount = strDivisionCount(CUnitSize::INFANTRY, CUnitSize::INFANTRY_SQUAD);
	for (int i = 0; i < (int)divisionCount.size(); i++)
	{
		incDivisionCount.AddString(divisionCount[i]);
	}
	incDivisionCount.SetCurSel(divisionCount.size()-1);

	//CSubMapPosDlg
	subMapPosDlg = new CSubMapPosDlg();
	subMapPosDlg->init(m_hWnd);
	subMapPosDlg->Create(m_hWnd);
	subMapPosDlg->ShowWindow(SW_SHOW);

	//CXLEzAutomation xlEz;
	//xlEz.OpenExcelFile(_T("E:\\_GitProject\\MRMWorkspace\\MRMProject\\MultiResolutionModeling\\sampleExcel.xls"));
	////xlEz.OpenExcelFile(_T(".\\sampleExcel.xls"));
	//CString valxl;// = xlEz.GetCellValue(1, 1);
	////valxl = xlEz.GetCellValue(1, 2);
	////valxl = xlEz.GetCellValue(1, 3);
	////valxl = xlEz.GetCellValue(2, 1);
	//xlEz.selectWorksheets(_T("E:\\_GitProject\\MRMWorkspace\\MRMProject\\MultiResolutionModeling\\sampleExcel.xls"), L"Aircraft");
	//valxl = xlEz.GetCellValue(1, 1);
	//valxl = xlEz.GetCellValue(1, 2);
	//valxl = xlEz.GetCellValue(1, 3);
	//xlEz.ReleaseExcel();

	////xlEz.OpenExcelFile(_T("E:\\_GitProject\\MRMWorkspace\\MRMProject\\MultiResolutionModeling\\sampleExcel.xls"));
	////xlEz.ExportCString(_T("Ship"));
	////valxl = xlEz.GetCellValue(1, 1);
	////xlEz.CloseExcelFile();
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
	//출력 Position 크기
	subMapPosDlg->drawResolutionPositionSize(valDivisionCount(incDivisionCount.GetCurSel()));

	CUnitSize::COMBATANT combatType = CUnitSize::emCombatent(incUnitType.GetCurSel());
	CUnitSize::MILITARYBRANCH mil = CUnitSize::emMilitarybranch(combatType, incUnitScale.GetCurSel());
	CGAgt::GResCha()->setParentPos(CVector2d((float)GetDlgItemInt(IDCE_INPOSX), (float)GetDlgItemInt(IDCE_INPOSY)));
	CGAgt::GResCha()->setDeploymentType(CResolutionChange::emDeploymentType(combatType, mil, incDeployment.GetCurSel()));
	CGAgt::GResCha()->setDirectionType(CResolutionChange::emDirectionType(incDirection.GetCurSel()));
	CGAgt::GResCha()->setMoveType(CUnitSize::emMoveType(incUnitPosture.GetCurSel()));
	CGAgt::GResCha()->setCombatent(combatType);
	CGAgt::GResCha()->setForce(CUnitSize::emForce(incUnitBlueRed.GetCurSel()));
	CGAgt::GResCha()->setMilitarybranch(mil);

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

	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_INUNITSCALE, CBN_SELCHANGE), (LPARAM)incUnitScale.m_hWnd);

	return 0;
}

LRESULT CResolutionPositionDlg::OnCbnSelchangeInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	incDeployment.ResetContent();
	CUnitSize::COMBATANT combatType = CUnitSize::emCombatent(incUnitType.GetCurSel());
	CUnitSize::MILITARYBRANCH mil = CUnitSize::emMilitarybranch(combatType, incUnitScale.GetCurSel());

	vector<CString> deployment = CResolutionChange::strDeploymentType(combatType, mil);
	for (int i = 0; i < (int)deployment.size(); i++)
	{
		incDeployment.AddString(deployment[i]);
	}
	incDeployment.SetCurSel(0);

	incDivisionCount.ResetContent();
	vector<CString> divisionCount = strDivisionCount(combatType, mil);
	for (int i = 0; i < (int)divisionCount.size(); i++)
	{
		incDivisionCount.AddString(divisionCount[i]);
	}
	incDivisionCount.SetCurSel(divisionCount.size()-1);

	return 0;
}

void CResolutionPositionDlg::drawResolutionPosition(vector<CVector2d> pos, int typeOp, vector<CVector2d> areaPos, CString text)
{
	subMapPosDlg->drawResolutionPosition(pos, typeOp, areaPos, text);
}

LRESULT CResolutionPositionDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	GetWindowRect(winPos);
	SetCapture();
	bLClick = true;
	startPoint = CPoint(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

LRESULT CResolutionPositionDlg::OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(bLClick)
	{
		GetWindowRect(winPos);
		SetWindowPos(NULL, winPos.left+(LOWORD(lParam) - startPoint.x), winPos.top+(HIWORD(lParam) - startPoint.y), 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	return 0;
}

LRESULT CResolutionPositionDlg::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	bLClick = false;
	ReleaseCapture();
	return 0;
}

vector<CString> CResolutionPositionDlg::strDivisionCount(CUnitSize::COMBATANT combat, CUnitSize::MILITARYBRANCH mil)
{
	vector<CString> strEm;
	strEm.clear();
	if(CUnitSize::INFANTRY == combat && CUnitSize::INFANTRY_SQUAD == mil)
	{
		strEm.push_back("1");
		strEm.push_back("2");
		strEm.push_back("3");
		strEm.push_back("4");
		strEm.push_back("5");
		strEm.push_back("6");
		strEm.push_back("7");
		strEm.push_back("8");
		strEm.push_back("9");
		strEm.push_back("10");
		strEm.push_back("11");
		strEm.push_back("12");
	}
	else if(CUnitSize::ARTILLERY == combat && CUnitSize::ARTILLERY_COMPANY == mil)
	{
		strEm.push_back("1");
		strEm.push_back("2");
		strEm.push_back("3");
		strEm.push_back("4");
		strEm.push_back("5");
		strEm.push_back("6");
	}
	else
	{
		strEm.push_back("1");
		strEm.push_back("2");
		strEm.push_back("3");
		strEm.push_back("4");
	}	
	return strEm;
}

int CResolutionPositionDlg::valDivisionCount(int selNum)
{
	int val = 1;
	val = selNum+1;
	return val;
}