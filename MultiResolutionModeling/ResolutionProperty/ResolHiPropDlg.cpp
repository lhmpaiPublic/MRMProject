// ResolHiPropDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolHiPropDlg.h"
#include "PropertyList.h"


CResolHiPropDlg::CResolHiPropDlg()
{
	m_lowModelList.RegisterClass();
	m_lowModelRatio.RegisterClass();
	m_hiModelList.RegisterClass();

	bEditHiItem = false;
	hiItemSelectNum = -1;

	bEditLowRatio = false;
	lowRatioSelectNum = -1;
}

CResolHiPropDlg::~CResolHiPropDlg()
{

}

BOOL CResolHiPropDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CResolHiPropDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

LRESULT CResolHiPropDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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

	inUnitType.Attach(GetDlgItem(IDCC_HPPTY_INUNITTYPE));
	vector<CString> vecCombat = SPrMoTy::strCOMBATANT();
	for (int i = 0; i < (int)vecCombat.size(); i++)
	{
		inUnitType.AddString(vecCombat[i]);
	}
	inUnitType.SetCurSel(0);

	inUnitScale.Attach(GetDlgItem(IDCC_HPPTY_INUNITSCALE));
	vector<CString> vecCombatClass = SPrMoTy::strCOMBATANTCLASS(SPrMoTy::INFANTRY);
	for (int i = 0; i < (int)vecCombatClass.size(); i++)
	{
		inUnitScale.AddString(vecCombatClass[i]);
	}
	inUnitScale.SetCurSel(0);

	propertyDiv.Attach(GetDlgItem(IDCC_HPPTY_PROPERTYDIV));
	vector<CString> vecPropertyType = SPrMoTy::strPRODUCTTYPE();
	for (int i = 0; i < (int)vecPropertyType.size(); i++)
	{
		propertyDiv.AddString(vecPropertyType[i]);
	}
	propertyDiv.SetCurSel(0);

	startPoint = CPoint(0, 0);
	bLClick = false;
	GetWindowRect(winPos);

	m_lowModelList.SubclassWindow(GetDlgItem(IDCCUST_HLOWMODELLIST));
	m_lowModelRatio.SubclassWindow(GetDlgItem(IDCCUST_HLOWMODELRATIO));
	m_hiModelList.SubclassWindow(GetDlgItem(IDCCUST_HHIMODELLIST));
	//m_hiModelRatio.SubclassWindow(GetDlgItem(IDCCUST_HIMODELRATIO));

	if ( !m_ilItemImages.CreateFromImage(IDB_EXAMPLE, 16, 0, RGB( 255, 0, 255 ), IMAGE_BITMAP, LR_CREATEDIBSECTION ) )
		return FALSE;

	LOGFONT logFont = { 0 };
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfHeight = 90;
	lstrcpy( logFont.lfFaceName, _T( "New Times Roman" ) );
	logFont.lfWeight = FW_BOLD;
	logFont.lfItalic = (BYTE)TRUE;

	m_fntCustomFont1.CreatePointFontIndirect( &logFont );

	logFont.lfHeight = 100;
	lstrcpy( logFont.lfFaceName, _T( "Arial" ) );
	logFont.lfUnderline = (BYTE)TRUE;
	m_fntCustomFont2.CreatePointFontIndirect( &logFont );

	m_lowModelList.SetImageList( m_ilItemImages );
	m_lowModelList.SetFocusSubItem( TRUE );

	m_lowModelRatio.SetImageList( m_ilItemImages );
	m_lowModelRatio.SetFocusSubItem( TRUE );

	m_hiModelList.SetImageList( m_ilItemImages );
	m_hiModelList.SetFocusSubItem( TRUE );

	m_lowModelList.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelList.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.ShowHeaderSort(FALSE);	
	CGAgt::PropLi()->hLowPropertyItem(&m_lowModelList, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

	m_lowModelRatio.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelRatio.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.ShowHeaderSort(FALSE);	
	CGAgt::PropLi()->hLowPropertyIRatio(&m_lowModelRatio, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

	m_hiModelList.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelList.AddColumn( _T( " " ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelList.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( "본부소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( "분대1" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( "분대2" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( "분대3" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelList.ShowHeaderSort(FALSE);	
	CGAgt::PropLi()->hHiPropertyItem(&m_hiModelList, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

	return TRUE;
}

LRESULT CResolHiPropDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CResolHiPropDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CResolHiPropDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void CResolHiPropDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CResolHiPropDlg::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	GetWindowRect(winPos);
	SetCapture();
	bLClick = true;
	startPoint = CPoint(LOWORD(lParam), HIWORD(lParam));
	return 0;
}

LRESULT CResolHiPropDlg::OnLMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	if(bLClick)
	{
		GetWindowRect(winPos);
		SetWindowPos(NULL, winPos.left+(LOWORD(lParam) - startPoint.x), winPos.top+(HIWORD(lParam) - startPoint.y), 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
	return 0;
}

LRESULT CResolHiPropDlg::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	bLClick = false;
	ReleaseCapture();
	return 0;
}

LRESULT CResolHiPropDlg::OnCbnSelchangeHPptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	inUnitScale.ResetContent();
	vector<CString> vecCombatClass = SPrMoTy::strCOMBATANTCLASS(combatType);
	for (int i = 0; i < (int)vecCombatClass.size(); i++)
	{
		inUnitScale.AddString(vecCombatClass[i]);
	}
	inUnitScale.SetCurSel(0);

	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_HPPTY_INUNITSCALE, CBN_SELCHANGE), (LPARAM)inUnitScale.m_hWnd);
	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_HPPTY_INUNITSCALE, CBN_KILLFOCUS), (LPARAM)inUnitScale.m_hWnd);

	return 0;
}

LRESULT CResolHiPropDlg::OnCbnSelchangeHPptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_lowModelList.DeleteAllItems();
	m_lowModelRatio.DeleteAllItems();
	m_hiModelList.DeleteAllItems();
	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	SPrMoTy::COMBATANTCLASS combatClass = SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType);

	if(SPrMoTy::BATTALION == combatClass)
	{
		m_lowModelList.SetColumn(1, _T("대대"));

		m_lowModelRatio.SetColumn(1, _T("대대"));

		m_hiModelList.SetColumn(2, _T("대대"));
		m_hiModelList.SetColumn(4, _T("본부대대"));
		m_hiModelList.SetColumn(6, _T("중대1"));
		m_hiModelList.SetColumn(8, _T("중대2"));
		m_hiModelList.SetColumn(10, _T("중대3"));

	}
	else if(SPrMoTy::COMPANY == combatClass)
	{
		m_lowModelList.SetColumn(1, _T("중대"));

		m_lowModelRatio.SetColumn(1, _T("중대"));

		m_hiModelList.SetColumn(2, _T("중대"));
		m_hiModelList.SetColumn(4, _T("본부중대"));
		m_hiModelList.SetColumn(6, _T("소대1"));
		m_hiModelList.SetColumn(8, _T("소대2"));
		m_hiModelList.SetColumn(10, _T("소대3"));

	}
	else
	{
		m_lowModelList.SetColumn(1, _T("소대"));

		m_lowModelRatio.SetColumn(1, _T("소대"));

		m_hiModelList.SetColumn(2, _T("소대"));
		m_hiModelList.SetColumn(4, _T("본부소대"));
		m_hiModelList.SetColumn(6, _T("분대1"));
		m_hiModelList.SetColumn(8, _T("분대2"));
		m_hiModelList.SetColumn(10, _T("분대3"));

	}

	CGAgt::PropLi()->hLowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	CGAgt::PropLi()->hLowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	CGAgt::PropLi()->hHiPropertyItem(&m_hiModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_INUNITTYPE, CBN_KILLFOCUS), (LPARAM)inUnitType.m_hWnd);
	return 0;
}

LRESULT CResolHiPropDlg::OnCbnSelchangeHPptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_lowModelList.DeleteAllItems();
	m_lowModelRatio.DeleteAllItems();
	m_hiModelList.DeleteAllItems();
	//m_hiModelRatio.DeleteAllItems();
	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	CGAgt::PropLi()->hLowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	CGAgt::PropLi()->hLowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	CGAgt::PropLi()->hHiPropertyItem(&m_hiModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_PROPERTYDIV, CBN_KILLFOCUS), (LPARAM)propertyDiv.m_hWnd);
	return 0;
}

LRESULT CResolHiPropDlg::OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Left item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_lowModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);

	if(ITEM_FORMAT_EDIT == listSubItem.m_nFormat)
	{
		int numSelectLow = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
		CLogDlg::AddLogText("ITEM_FORMAT_EDIT");
		bEditLowRatio = true;
		lowRatioSelectNum = pListNotify->m_nItem;
	}

	return 0;
}

LRESULT CResolHiPropDlg::OnLowModelRatioModify( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Modify item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_lowModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	int numVerify = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
	m_lowModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem+1, listSubItem);
	int numVerifyComp = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);

	if (numVerify < 0)
	{
		osItemText.str(_T(""));
		osItemText << 0;
		m_lowModelRatio.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("0 보다 작다"), _T("입력오류"), MB_OK);
	}
	else if (numVerify > numVerifyComp)
	{
		osItemText.str(_T(""));
		osItemText << numVerifyComp;
		m_lowModelRatio.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("인가량보다 크다"), _T("입력오류"), MB_OK);
	}

	if((bEditLowRatio == true) && (lowRatioSelectNum == pListNotify->m_nItem))
	{
		bEditLowRatio = false;
		lowRatioSelectNum = -1;
	}
	return 0;
}

LRESULT CResolHiPropDlg::OnHiModelListSelectedLeft( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Lef item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);

	if(ITEM_FORMAT_EDIT == listSubItem.m_nFormat)
	{
		int numSelectLow = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
		CLogDlg::AddLogText("ITEM_FORMAT_EDIT");
		bEditHiItem = true;
		hiItemSelectNum = pListNotify->m_nItem;
	}

	return 0;
}

LRESULT CResolHiPropDlg::OnHiModelListModify( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Modify item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	int numVerify = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
	m_hiModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem+1, listSubItem);
	int numVerifyComp = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);

	if (numVerify < 0)
	{
		osItemText.str(_T(""));
		osItemText << 0;
		m_hiModelList.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("0 보다 작다"), _T("입력오류"), MB_OK);
	}
	else if (numVerify > numVerifyComp)
	{
		osItemText.str(_T(""));
		osItemText << numVerifyComp;
		m_hiModelList.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("인가량보다 크다"), _T("입력오류"), MB_OK);
	}

	if((bEditHiItem == true) && (hiItemSelectNum == pListNotify->m_nItem))
	{
		bEditHiItem = false;
		hiItemSelectNum = -1;

		int total = 0;
		for (int idx = 0; idx < (int)STPL_HIR.size(); idx++)
		{
			total += strtoul(CStringA(m_hiModelList.GetItemText(pListNotify->m_nItem, STPL_HIR[idx])).GetBuffer(), NULL, 10);
		}	
		osItemText.str(_T(""));
		osItemText << total;
		m_hiModelList.SetItemText(pListNotify->m_nItem, SPrCoNa::LMN_02, osItemText.str().c_str());

	}
	return 0;
}

LRESULT CResolHiPropDlg::OnBnClickedHpptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText.str(_T(""));
	osItemText << _T( "Hi Item Count: " ) << m_hiModelList.GetItemCount();
	CLogDlg::AddLogText(osItemText.str().c_str());

	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	CGAgt::PropLi()->resolutionChangeHiProperty(&m_hiModelList, &m_lowModelRatio, &m_lowModelList,
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	return 0;
}
