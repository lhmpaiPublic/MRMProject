// ResolHiPropDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolHiPropDlg.h"
#include "PropertyList.h"

vector<SPrCoNa::HICOLUMNNAME> CResolHiPropDlg::setHiRetenListNum;
vector<SPrCoNa::LOWRATIOCOLUMNNAME> CResolHiPropDlg::setLowRetenRitioNum;

CResolHiPropDlg::CResolHiPropDlg()
{
	m_lowModelList.RegisterClass();
	m_lowModelRatio.RegisterClass();
	m_hiModelList.RegisterClass();

	bEditHiItem = false;
	hiItemSelectNum = -1;

	bEditLowRatio = false;
	lowRatioSelectNum = -1;

	itemKeyHi[SPrMoTy::MTLOW].RemoveAll();
	itemKeyHi[SPrMoTy::MTHI].RemoveAll();
	itemMappStrHi[SPrMoTy::MTLOW].RemoveAll();
	itemMappStrHi[SPrMoTy::MTHI].RemoveAll();
	itemListIndexHi[SPrMoTy::MTLOW].RemoveAll();
	itemListIndexHi[SPrMoTy::MTHI].RemoveAll();

	setHiRetenListNum.push_back(SPrCoNa::HMN_04);
	setHiRetenListNum.push_back(SPrCoNa::HMN_06);
	setHiRetenListNum.push_back(SPrCoNa::HMN_08);
	setHiRetenListNum.push_back(SPrCoNa::HMN_10);

	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_01);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_03);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_05);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_07);
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
	hLowPropertyItem(&m_lowModelList, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));
	m_lowModelList.ShowHeader(TRUE);

	m_lowModelRatio.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelRatio.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.ShowHeaderSort(FALSE);	
	hLowPropertyIRatio(&m_lowModelRatio, 
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
	hHiPropertyItem(&m_hiModelList, 
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

	hLowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hLowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hHiPropertyItem(&m_hiModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_INUNITTYPE, CBN_KILLFOCUS), (LPARAM)inUnitType.m_hWnd);
	return 0;
}

LRESULT CResolHiPropDlg::OnCbnSelchangeHPptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_lowModelList.DeleteAllItems();
	m_lowModelRatio.DeleteAllItems();
	m_hiModelList.DeleteAllItems();
	//m_hiModelRatio.DeleteAllItems();
	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	hLowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hLowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hHiPropertyItem(&m_hiModelList, 
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
		for (int idx = 0; idx < (int)STPL_HHIR.size(); idx++)
		{
			total += strtoul(CStringA(m_hiModelList.GetItemText(pListNotify->m_nItem, STPL_HHIR[idx])).GetBuffer(), NULL, 10);
		}	
		osItemText.str(_T(""));
		osItemText << total;
		m_hiModelList.SetItemText(pListNotify->m_nItem, SPrCoNa::LMN_02, osItemText.str().c_str());

	}
	return 0;
}

LRESULT CResolHiPropDlg::OnBnClickedHpptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText.str(_T(""));
	osItemText << _T( "Hi Item Count: " ) << m_hiModelList.GetItemCount();
	CLogDlg::AddLogText(osItemText.str().c_str());

	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	resolutionChangeHiProperty(&m_hiModelList, &m_lowModelRatio, &m_lowModelList,
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	return 0;
}

void CResolHiPropDlg::hHiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("Low 자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, _T("Hi 자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	vector<int> lowKey;
	vector<int> hiKey;
	SPrMa prVal;
	CGAgt::PropLi()->getPropertyItem( combat, propType, cbtClass, lowKey, hiKey, prVal);

	itemKeyHi[SPrMoTy::MTHI].RemoveAll();
	itemMappStrHi[SPrMoTy::MTHI].RemoveAll();
	itemListIndexHi[SPrMoTy::MTHI].RemoveAll();
	
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(hiKey[i], cbtClass, SPrMoTy::MTHI);

		if(lowVal.size() <= hiVal.size())
		{
			for (int iv = 0; iv < (int)hiVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");

				SPrKe prKe;
				prKe.setVal(hiVal[iv].mappKey, hiVal[iv].key, nUser);
				itemKeyHi[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
				//mapping key to product Name
				setPropKeyMappStringHi(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
				setPropKeyMappListIndexHi(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, hiVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				std::wstringstream strStream;
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_04, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_06, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_08, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_10, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
			}
		}
		else
		{
			for (int iv = 0; iv < (int)lowVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(lowVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				if(iv == 0)
				{
					SPrKe prKe;
					prKe.setVal(hiVal[iv].mappKey, hiVal[iv].key, nUser);
					itemKeyHi[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
					//mapping key to product Name
					setPropKeyMappStringHi(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
					setPropKeyMappListIndexHi(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

					listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, hiVal[iv].strName);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					std::wstringstream strStream;
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_02, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_03, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_04, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_04, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_06, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_08, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HMN_10, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				}				
			}
		}		
	}
}

void CResolHiPropDlg::hLowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	vector<int> lowKey;
	vector<int> hiKey;
	SPrMa prVal;
	CGAgt::PropLi()->getPropertyItem( combat, propType, cbtClass, lowKey, hiKey, prVal);

	itemKeyHi[SPrMoTy::MTLOW].RemoveAll();
	itemMappStrHi[SPrMoTy::MTLOW].RemoveAll();
	itemListIndexHi[SPrMoTy::MTLOW].RemoveAll();

	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> val = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		for (int iv = 0; iv < (int)val.size(); iv++)
		{
			int nUser = listCtrl->AddItem(val[iv].strName);
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

			//키 저장 LOW
			SPrKe prKe;
			prKe.setVal(val[iv].mappKey, val[iv].key, nUser);
			itemKeyHi[SPrMoTy::MTLOW].SetAt(val[iv].strName, prKe);
			//mapping key to product Name
			setPropKeyMappStringHi(val[iv].mappKey, SPrMoTy::MTLOW, val[iv].strName);
			setPropKeyMappListIndexHi(val[iv].mappKey, SPrMoTy::MTLOW, nUser);		

			std::wstringstream strStream;
			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_02, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
		}

	}

}

void CResolHiPropDlg::hLowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_01, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_02, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	vector<int> lowKey;
	vector<int> hiKey;
	SPrMa prVal;
	CGAgt::PropLi()->getPropertyItem( combat, propType, cbtClass, lowKey, hiKey, prVal);

	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> val = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		for (int iv = 0; iv < (int)val.size(); iv++)
		{
			int nUser = listCtrl->AddItem(val[iv].strName);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

			std::wstringstream strStream;
			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_01, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LRMN_01, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_01, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_02, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_02, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
		}

	}
}

void CResolHiPropDlg::resolutionChangeHiProperty(CListCtrl* listCtrlHi, CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	//Low Item String 이름, List index 값
	SVeStIn LowListItem;
	vector<SPrKe> vecPrKeVal;
	vector<int> mappKeyBackup;
	for (int i = 1; i < (int)listCtrlLow->GetItemCount(); i++)
	{
		LowListItem.setVal(listCtrlLow->GetItemText(i, SPrCoNa::LMN_00),
			strtoul(CStringA(listCtrlLow->GetItemText(i, SPrCoNa::LMN_01)).GetBuffer(), NULL, 10));
		SPrKe val;
		if(itemKeyHi[SPrMoTy::MTLOW].Lookup(listCtrlLow->GetItemText(i, SPrCoNa::LMN_00), val))
		{
			if(mappKeyBackup.end() == find(mappKeyBackup.begin(), mappKeyBackup.end(), val.getMappKey()))
			{
				vecPrKeVal.push_back(val);
				mappKeyBackup.push_back(val.getMappKey());
			}			
		}
	}


	//HI -> LOW 계산 세팅
	for (int mIdx = 0; mIdx < (int)mappKeyBackup.size(); mIdx++)
	{
		vector<int> idxListHiVec;
		vector<int> idxListLowVec;
		//Low Hi Mapping List가 존재할 경우
		if(getPropKeyMappListIndexHi(mappKeyBackup[mIdx], SPrMoTy::MTLOW, idxListLowVec) && 
			getPropKeyMappListIndexHi(mappKeyBackup[mIdx], SPrMoTy::MTHI, idxListHiVec))
		{
			vector<int> retenHiVec(1,0);
			vector<int> accLowRatioTotal(1,0);
			//Hi의 각 하위 보유량 합산 개수
			for (int idxHi = 0; idxHi < (int)idxListHiVec.size(); idxHi++)
			{
				//보유량 합산
				retenHiVec[0] += strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], SPrCoNa::HMN_02)).GetBuffer(), NULL, 10);
			}

			//Low의 각 하위  설정량 합산 개수
			for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
			{
				//설정량 합산
				accLowRatioTotal[0] += strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], SPrCoNa::LRMN_01)).GetBuffer(), NULL, 10);
			}

			for (int idxRtn = 0; idxRtn < (int)retenHiVec.size(); idxRtn++)
			{
				if(0 == accLowRatioTotal[idxRtn])
					continue;
				//LOW 비율을 읽는다.
				vector<int> lowRatioVal;
				lowRatioVal.resize(idxListLowVec.size());
				for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
				{
					//LOW 비율
					lowRatioVal[idxLow] = strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[idxRtn])).GetBuffer(), NULL, 10);
				}

				vector<int> retVal = CPropertyList::calcResolutionChangeProperty(lowRatioVal, (float)retenHiVec[idxRtn], (float)accLowRatioTotal[idxRtn]);

				//Hi 값 -> LOW 보유량 최종 세팅
				for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
				{
					osItemText.str(_T(""));
					osItemText << retVal[idxLow];
					listCtrlLow->SetItemText(idxListLowVec[idxLow], SPrCoNa::LMN_01, osItemText.str().c_str());
				}
			}
		}
		//Low Hi Mapping List가 없을 경우
		else
		{
			MessageBox(_T("Low - Hi Mapping List가 없다"), _T("매핑오류"), MB_OK);
		}
	}

	CLogDlg::AddLogText(_T("======================================================================================="));
	CLogDlg::initStream();
	for (int columnCount = 0; columnCount < (int)listCtrlHi->GetColumnCount(); columnCount++)
	{
		CListColumn listColumn;
		listCtrlHi->GetColumn(columnCount, listColumn);
		if(0 == listColumn.m_strText.GetLength())
			CLogDlg::insertStream(_T("	"), '	');
		else
			CLogDlg::insertStream(listColumn.m_strText.GetBuffer(), '	');
	}
	CLogDlg::addLogTextStream();

	for (int itemCount = 0; itemCount < (int)listCtrlHi->GetItemCount(); itemCount++)
	{
		CLogDlg::initStream();
		for (int columnCount = 0; columnCount < (int)listCtrlHi->GetColumnCount(); columnCount++)
		{
			CString str = CString(listCtrlHi->GetItemText(itemCount, columnCount));
			if(0 == str.GetLength())
				CLogDlg::insertStream(_T("	"), '	');
			else
				CLogDlg::insertStream(str.GetBuffer(), '	');

		}
		CLogDlg::addLogTextStream();
	}

	CLogDlg::AddLogText(_T("======================================================================================="));
	CLogDlg::initStream();
	for (int columnCount = 0; columnCount < (int)listCtrlLow->GetColumnCount(); columnCount++)
	{
		CListColumn listColumn;
		listCtrlLow->GetColumn(columnCount, listColumn);
		if(0 == listColumn.m_strText.GetLength())
			CLogDlg::insertStream(_T("	"), '	');
		else
			CLogDlg::insertStream(listColumn.m_strText.GetBuffer(), '	');
	}
	CLogDlg::addLogTextStream();

	CString strTap = _T("	");
	for (int itemCount = 0; itemCount < (int)listCtrlLow->GetItemCount(); itemCount++)
	{
		CLogDlg::initStream();
		for (int columnCount = 0; columnCount < (int)listCtrlLow->GetColumnCount(); columnCount++)
		{
			CString str = CString(listCtrlLow->GetItemText(itemCount, columnCount));
			if(0 == str.GetLength())
				CLogDlg::insertStream(_T("	"), '	');
			else
				CLogDlg::insertStream(str.GetBuffer(), '	');

		}
		CLogDlg::addLogTextStream();
	}
}

void CResolHiPropDlg::setPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName)
{
	PropKeyMappString::CPair* pair = itemMappStrHi[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(propName);
	}
	else
	{
		SPrKeMaSt keyMappStr;
		keyMappStr.setVal(propName);
		itemMappStrHi[modelType].SetAt(mappKey, keyMappStr);
	}
}

bool CResolHiPropDlg::getPropKeyMappStringHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp)
{
	PropKeyMappString::CPair* pair = itemMappStrHi[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		strProp = pair->m_value.getVal();
	}
	return (0 != strProp.size());
}

void CResolHiPropDlg::setPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, int idx)
{
	PropKeyMappListIndex::CPair* pair = itemListIndexHi[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(idx);
	}
	else
	{
		SPrKeMaLiIn keyMapp;
		keyMapp.setVal(idx);
		itemListIndexHi[modelType].SetAt(mappKey, keyMapp);
	}
}

bool CResolHiPropDlg::getPropKeyMappListIndexHi(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal)
{
	PropKeyMappListIndex::CPair* pair = itemListIndexHi[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		idxVal = pair->m_value.getVal();
	}
	return (0 != idxVal.size());
}