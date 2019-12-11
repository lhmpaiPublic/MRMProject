// ResolutionPropertyDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolutionPropertyDlg.h"
#include "PropertyList.h"

vector<SPrCoNa::HICOLUMNNAME> CResolutionPropertyDlg::setHiRetenListNum;
vector<SPrCoNa::HICOLUMNNAME> CResolutionPropertyDlg::setHiAccListNum;

vector<SPrCoNa::LOWCOLUMNNAME> CResolutionPropertyDlg::setLowRetenListNum;
vector<SPrCoNa::LOWCOLUMNNAME> CResolutionPropertyDlg::setLowAccListNum;

vector<SPrCoNa::HIRATIOCOLUMNNAME> CResolutionPropertyDlg::setHiRetenRitioNum;
vector<SPrCoNa::HIRATIOCOLUMNNAME> CResolutionPropertyDlg::setHiLimtRitioNum;

vector<SPrCoNa::LOWRATIOCOLUMNNAME> CResolutionPropertyDlg::setLowRetenRitioNum;
vector<SPrCoNa::LOWRATIOCOLUMNNAME> CResolutionPropertyDlg::setLowLimtRitioNum;

CResolutionPropertyDlg::CResolutionPropertyDlg()
{
	m_lowModelList.RegisterClass();
	m_lowModelRatio.RegisterClass();
	m_hiModelList.RegisterClass();
	m_hiModelRatio.RegisterClass();

	bEditHiRatio = false;
	hiRatioSelectNum = -1;

	bEditLowRatio = false;
	lowRatioSelectNum = -1;

	itemKey[SPrMoTy::MTLOW].RemoveAll();
	itemKey[SPrMoTy::MTHI].RemoveAll();
	itemMappStr[SPrMoTy::MTLOW].RemoveAll();
	itemMappStr[SPrMoTy::MTHI].RemoveAll();
	itemListIndex[SPrMoTy::MTLOW].RemoveAll();
	itemListIndex[SPrMoTy::MTHI].RemoveAll();

	setHiRetenListNum.push_back(SPrCoNa::HMN_04);
	setHiRetenListNum.push_back(SPrCoNa::HMN_06);
	setHiRetenListNum.push_back(SPrCoNa::HMN_08);
	setHiRetenListNum.push_back(SPrCoNa::HMN_10);

	setHiAccListNum.push_back(SPrCoNa::HMN_05);
	setHiAccListNum.push_back(SPrCoNa::HMN_07);
	setHiAccListNum.push_back(SPrCoNa::HMN_09);
	setHiAccListNum.push_back(SPrCoNa::HMN_11);

	setLowRetenListNum.push_back(SPrCoNa::LMN_03);
	setLowRetenListNum.push_back(SPrCoNa::LMN_05);
	setLowRetenListNum.push_back(SPrCoNa::LMN_07);
	setLowRetenListNum.push_back(SPrCoNa::LMN_09);

	setLowAccListNum.push_back(SPrCoNa::LMN_04);
	setLowAccListNum.push_back(SPrCoNa::LMN_06);
	setLowAccListNum.push_back(SPrCoNa::LMN_08);
	setLowAccListNum.push_back(SPrCoNa::LMN_10);

	setHiRetenRitioNum.push_back(SPrCoNa::HRMN_04);
	setHiRetenRitioNum.push_back(SPrCoNa::HRMN_06);
	setHiRetenRitioNum.push_back(SPrCoNa::HRMN_08);
	setHiRetenRitioNum.push_back(SPrCoNa::HRMN_10);

	setHiLimtRitioNum.push_back(SPrCoNa::HRMN_05);
	setHiLimtRitioNum.push_back(SPrCoNa::HRMN_07);
	setHiLimtRitioNum.push_back(SPrCoNa::HRMN_09);
	setHiLimtRitioNum.push_back(SPrCoNa::HRMN_11);

	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_01);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_03);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_05);
	setLowRetenRitioNum.push_back(SPrCoNa::LRMN_07);

	setLowLimtRitioNum.push_back(SPrCoNa::LRMN_02);
	setLowLimtRitioNum.push_back(SPrCoNa::LRMN_04);
	setLowLimtRitioNum.push_back(SPrCoNa::LRMN_06);
	setLowLimtRitioNum.push_back(SPrCoNa::LRMN_08);
}

CResolutionPropertyDlg::~CResolutionPropertyDlg()
{

}

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

	inUnitType.Attach(GetDlgItem(IDCC_PPTY_INUNITTYPE));
	vector<CString> vecCombat = SPrMoTy::strCOMBATANT();
	for (int i = 0; i < (int)vecCombat.size(); i++)
	{
		inUnitType.AddString(vecCombat[i]);
	}
	inUnitType.SetCurSel(0);

	inUnitScale.Attach(GetDlgItem(IDCC_PPTY_INUNITSCALE));
	vector<CString> vecCombatClass = SPrMoTy::strCOMBATANTCLASS(SPrMoTy::INFANTRY);
	for (int i = 0; i < (int)vecCombatClass.size(); i++)
	{
		inUnitScale.AddString(vecCombatClass[i]);
	}
	inUnitScale.SetCurSel(0);

	propertyDiv.Attach(GetDlgItem(IDCC_PPTY_PROPERTYDIV));
	vector<CString> vecPropertyType = SPrMoTy::strPRODUCTTYPE();
	for (int i = 0; i < (int)vecPropertyType.size(); i++)
	{
		propertyDiv.AddString(vecPropertyType[i]);
	}
	propertyDiv.SetCurSel(0);

	startPoint = CPoint(0, 0);
	bLClick = false;
	GetWindowRect(winPos);

	m_lowModelList.SubclassWindow(GetDlgItem(IDCCUST_LOWMODELLIST));
	m_lowModelRatio.SubclassWindow(GetDlgItem(IDCCUST_LOWMODELRATIO));
	m_hiModelList.SubclassWindow(GetDlgItem(IDCCUST_HIMODELLIST));
	m_hiModelRatio.SubclassWindow(GetDlgItem(IDCCUST_HIMODELRATIO));

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

	m_hiModelRatio.SetImageList( m_ilItemImages );
	m_hiModelRatio.SetFocusSubItem( TRUE );

	m_lowModelList.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelList.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "소대본부" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "분대1" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "분대2" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "분대3" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.ShowHeaderSort(FALSE);	
	lowPropertyItem(&m_lowModelList, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

	m_lowModelRatio.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelRatio.AddColumn( _T( "소대본부" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.AddColumn( _T( "분대1" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.AddColumn( _T( "분대2" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.AddColumn( _T( "분대3" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelRatio.ShowHeaderSort(FALSE);	
	lowPropertyIRatio(&m_lowModelRatio, 
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
	hiPropertyItem(&m_hiModelList, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

	m_hiModelRatio.AddColumn( _T( "부대타입" ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelRatio.AddColumn( _T( " " ), 220, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelRatio.AddColumn( _T( "소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( "본부소대" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( "분대1" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( "분대2" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( "분대3" ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.AddColumn( _T( " " ), 60, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_hiModelRatio.ShowHeaderSort(FALSE);	
	hiPropertyRatio(&m_hiModelRatio, 
		SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel()),
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), SPrMoTy::INFANTRY));

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

LRESULT CResolutionPropertyDlg::OnCbnSelchangePptyInunittype(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
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

	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_INUNITSCALE, CBN_SELCHANGE), (LPARAM)inUnitScale.m_hWnd);
	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_INUNITSCALE, CBN_KILLFOCUS), (LPARAM)inUnitScale.m_hWnd);

	return 0;
}

LRESULT CResolutionPropertyDlg::OnCbnSelchangePptyInunitscale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_lowModelList.DeleteAllItems();
	m_lowModelRatio.DeleteAllItems();
	m_hiModelList.DeleteAllItems();
	m_hiModelRatio.DeleteAllItems();
	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	SPrMoTy::COMBATANTCLASS combatClass = SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType);

	if(SPrMoTy::BATTALION == combatClass)
	{
		m_lowModelList.SetColumn(1, _T("대대"));
		m_lowModelList.SetColumn(3, _T("대대본부"));
		m_lowModelList.SetColumn(5, _T("중대1"));
		m_lowModelList.SetColumn(7, _T("중대2"));
		m_lowModelList.SetColumn(9, _T("중대3"));

		m_lowModelRatio.SetColumn(1, _T("대대본부"));
		m_lowModelRatio.SetColumn(3, _T("중대1"));
		m_lowModelRatio.SetColumn(5, _T("중대2"));
		m_lowModelRatio.SetColumn(7, _T("중대3"));

		m_hiModelList.SetColumn(2, _T("대대"));
		m_hiModelList.SetColumn(4, _T("본부대대"));
		m_hiModelList.SetColumn(6, _T("중대1"));
		m_hiModelList.SetColumn(8, _T("중대2"));
		m_hiModelList.SetColumn(10, _T("중대3"));

		m_hiModelRatio.SetColumn(2, _T("대대"));
		m_hiModelRatio.SetColumn(4, _T("본부대대"));
		m_hiModelRatio.SetColumn(6, _T("중대1"));
		m_hiModelRatio.SetColumn(8, _T("중대2"));
		m_hiModelRatio.SetColumn(10, _T("중대3"));
	}
	else if(SPrMoTy::COMPANY == combatClass)
	{
		m_lowModelList.SetColumn(1, _T("중대"));
		m_lowModelList.SetColumn(3, _T("중대본부"));
		m_lowModelList.SetColumn(5, _T("소대1"));
		m_lowModelList.SetColumn(7, _T("소대2"));
		m_lowModelList.SetColumn(9, _T("소대3"));

		m_lowModelRatio.SetColumn(1, _T("중대본부"));
		m_lowModelRatio.SetColumn(3, _T("소대1"));
		m_lowModelRatio.SetColumn(5, _T("소대2"));
		m_lowModelRatio.SetColumn(7, _T("소대3"));

		m_hiModelList.SetColumn(2, _T("중대"));
		m_hiModelList.SetColumn(4, _T("본부중대"));
		m_hiModelList.SetColumn(6, _T("소대1"));
		m_hiModelList.SetColumn(8, _T("소대2"));
		m_hiModelList.SetColumn(10, _T("소대3"));

		m_hiModelRatio.SetColumn(2, _T("중대"));
		m_hiModelRatio.SetColumn(4, _T("본부중대"));
		m_hiModelRatio.SetColumn(6, _T("소대1"));
		m_hiModelRatio.SetColumn(8, _T("소대2"));
		m_hiModelRatio.SetColumn(10, _T("소대3"));
	}
	else
	{
		m_lowModelList.SetColumn(1, _T("소대"));
		m_lowModelList.SetColumn(3, _T("소대본부"));
		m_lowModelList.SetColumn(5, _T("분대1"));
		m_lowModelList.SetColumn(7, _T("분대2"));
		m_lowModelList.SetColumn(9, _T("분대3"));

		m_lowModelRatio.SetColumn(1, _T("소대본부"));
		m_lowModelRatio.SetColumn(3, _T("분대1"));
		m_lowModelRatio.SetColumn(5, _T("분대2"));
		m_lowModelRatio.SetColumn(7, _T("분대3"));

		m_hiModelList.SetColumn(2, _T("소대"));
		m_hiModelList.SetColumn(4, _T("본부소대"));
		m_hiModelList.SetColumn(6, _T("분대1"));
		m_hiModelList.SetColumn(8, _T("분대2"));
		m_hiModelList.SetColumn(10, _T("분대3"));

		m_hiModelRatio.SetColumn(2, _T("소대"));
		m_hiModelRatio.SetColumn(4, _T("본부소대"));
		m_hiModelRatio.SetColumn(6, _T("분대1"));
		m_hiModelRatio.SetColumn(8, _T("분대2"));
		m_hiModelRatio.SetColumn(10, _T("분대3"));
	}

	lowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	lowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hiPropertyItem(&m_hiModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hiPropertyRatio(&m_hiModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_INUNITTYPE, CBN_KILLFOCUS), (LPARAM)inUnitType.m_hWnd);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnCbnSelchangePptyPropertydiv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_lowModelList.DeleteAllItems();
	m_lowModelRatio.DeleteAllItems();
	m_hiModelList.DeleteAllItems();
	m_hiModelRatio.DeleteAllItems();
	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	lowPropertyItem(&m_lowModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	lowPropertyIRatio(&m_lowModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hiPropertyItem(&m_hiModelList, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	hiPropertyRatio(&m_hiModelRatio, 
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));

	SetFocus();
	SendMessage(WM_COMMAND, MAKEWPARAM(IDCC_PPTY_PROPERTYDIV, CBN_KILLFOCUS), (LPARAM)propertyDiv.m_hWnd);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelListSelected( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Selected item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_lowModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelListSelectedLeft( LPNMHDR lpNMHDR )
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
	m_lowModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);

	if(ITEM_FORMAT_EDIT == listSubItem.m_nFormat)
	{
		int numSelectLow = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
		CLogDlg::AddLogText("ITEM_FORMAT_EDIT");
	}

	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelListSelectedRight( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Right item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_lowModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelListModify( LPNMHDR lpNMHDR )
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
	m_lowModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	int numVerify = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
	m_lowModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem+1, listSubItem);
	int numVerifyComp = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);

	if (numVerify < 0)
	{
		osItemText.str(_T(""));
		osItemText << 0;
		m_lowModelList.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("0 보다 작다"), _T("입력오류"), MB_OK);
	}
	else if (numVerify > numVerifyComp)
	{
		osItemText.str(_T(""));
		osItemText << numVerifyComp;
		m_lowModelList.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("한계치보다 크다"), _T("입력오류"), MB_OK);
	}
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelRatioSelected( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Selected item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelRatioSelectedLeft( LPNMHDR lpNMHDR )
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

LRESULT CResolutionPropertyDlg::OnLowModelRatioSelectedRight( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Right item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_lowModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnLowModelRatioModify( LPNMHDR lpNMHDR )
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

LRESULT CResolutionPropertyDlg::OnHiModelListSelected( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( " Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelList.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);

	return 0;
}

LRESULT CResolutionPropertyDlg::OnHiModelListSelectedLeft( LPNMHDR lpNMHDR )
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

	return 0;
}

LRESULT CResolutionPropertyDlg::OnHiModelRatioSelected( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Selected item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnHiModelRatioSelectedLeft( LPNMHDR lpNMHDR )
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
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);

	if(ITEM_FORMAT_EDIT == listSubItem.m_nFormat)
	{
		int numSelectHi = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
		CLogDlg::AddLogText("ITEM_FORMAT_EDIT");
		bEditHiRatio = true;
		hiRatioSelectNum = pListNotify->m_nItem;
	}

	return 0;
}

LRESULT CResolutionPropertyDlg::OnHiModelRatioSelectedRight( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );


#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText << _T( "Right item Num: " ) << pListNotify->m_nItem << _T( " " )
		<< _T( "Sub item Num: " ) << pListNotify->m_nSubItem << _T( " " );

	CLogDlg::AddLogText(osItemText.str().c_str());

	CSubItem listSubItem;
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	return 0;
}

LRESULT CResolutionPropertyDlg::OnHiModelRatioModify( LPNMHDR lpNMHDR )
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
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem, listSubItem);
	CLogDlg::AddLogText(listSubItem.m_strText);
	int numVerify = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);
	m_hiModelRatio.GetSubItem(pListNotify->m_nItem, pListNotify->m_nSubItem+1, listSubItem);
	int numVerifyComp = strtoul(CStringA(listSubItem.m_strText).GetBuffer(), NULL, 10);

	if (numVerify < 0)
	{
		osItemText.str(_T(""));
		osItemText << 0;
		m_hiModelRatio.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("0 보다 작다"), _T("입력오류"), MB_OK);
	}
	else if (numVerify > numVerifyComp)
	{
		osItemText.str(_T(""));
		osItemText << numVerifyComp;
		m_hiModelRatio.SetItemText(pListNotify->m_nItem, pListNotify->m_nSubItem, osItemText.str().c_str());
		MessageBox(_T("인가량보다 크다"), _T("입력오류"), MB_OK);
	}

	if((bEditHiRatio == true) && (hiRatioSelectNum == pListNotify->m_nItem))
	{
		bEditHiRatio = false;
		hiRatioSelectNum = -1;
		int total = 0;
		for (int idx = 0; idx < (int)STPL_HIRR.size(); idx++)
		{
			total += strtoul(CStringA(m_hiModelRatio.GetItemText(pListNotify->m_nItem, STPL_HIRR[idx])).GetBuffer(), NULL, 10);
		}	
		osItemText.str(_T(""));
		osItemText << total;
		m_hiModelRatio.SetItemText(pListNotify->m_nItem, SPrCoNa::HRMN_02, osItemText.str().c_str());

	}
	return 0;
}

LRESULT CResolutionPropertyDlg::OnBnClickedPptyResolutionchange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

#ifdef _UNICODE
	wostringstream osItemText;
#else
	ostringstream osItemText;
#endif

	osItemText.str(_T(""));
	osItemText << _T( "Low Item Count: " ) << m_lowModelList.GetItemCount();
	CLogDlg::AddLogText(osItemText.str().c_str());

	osItemText.str(_T(""));
	osItemText << _T( "Hi Item Count: " ) << m_hiModelList.GetItemCount();
	CLogDlg::AddLogText(osItemText.str().c_str());

	SPrMoTy::COMBATANT combatType = SPrMoTy::indexCOMBATANT(inUnitType.GetCurSel());
	resolutionChangeProperty(&m_lowModelRatio, &m_lowModelList, &m_hiModelRatio, &m_hiModelList,
		combatType,
		SPrMoTy::indexPRODUCTTYPE(propertyDiv.GetCurSel()),
		SPrMoTy::indexCOMBATANTCLASS(inUnitScale.GetCurSel(), combatType));
	
	return 0;
}

void CResolutionPropertyDlg::lowPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{

	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_03, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_04, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_05, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_06, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_07, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_08, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_09, _T("보유량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_09, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LMN_10, _T("인가량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LMN_10, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	vector<int> lowKey;
	vector<int> hiKey;
	SPrMa prVal;
	CGAgt::PropLi()->getPropertyItem( combat, propType, cbtClass, lowKey, hiKey, prVal);

	itemKey[SPrMoTy::MTLOW].RemoveAll();
	itemMappStr[SPrMoTy::MTLOW].RemoveAll();
	itemListIndex[SPrMoTy::MTLOW].RemoveAll();
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
			itemKey[SPrMoTy::MTLOW].SetAt(val[iv].strName, prKe);
			//mapping key to product Name
			setPropKeyMappString(val[iv].mappKey, SPrMoTy::MTLOW, val[iv].strName);
			setPropKeyMappListIndex(val[iv].mappKey, SPrMoTy::MTLOW, nUser);			

			std::wstringstream strStream;
			strStream.str(L"");
			strStream << val[iv].accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_01, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LMN_01, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_01, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );

			listCtrl->SetItemText( nUser, SPrCoNa::LMN_02, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_02, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );

			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_03, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_03, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_04, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_04, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );

			keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_05, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_05, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_06, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_06, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_07, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_07, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_08, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_08, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_09, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_09, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LMN_10, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_10, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
		}

	}
}

void CResolutionPropertyDlg::lowPropertyIRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_01, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_02, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_03, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_04, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_05, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_06, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_07, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::LRMN_08, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

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
			listCtrl->SetItemColours( nUser, SPrCoNa::LMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

			std::wstringstream strStream;
			SPrVa keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_01, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LRMN_01, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_01, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_02, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_02, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );

			keyval = prVal.getValKey(val[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTLOW);
			strStream.str(L"");
			strStream << keyval.accreditation;
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_03, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LRMN_03, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_03, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_04, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_04, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_05, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LRMN_05, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_05, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_06, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_06, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_07, strStream.str().c_str());
			listCtrl->SetItemFormat( nUser, SPrCoNa::LRMN_07, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_07, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
			listCtrl->SetItemText( nUser, SPrCoNa::LRMN_08, strStream.str().c_str());
			listCtrl->SetItemColours( nUser, SPrCoNa::LRMN_08, RGB( 192, 192, 192  ), RGB( 0, 0, 0 ) );
		}

	}
}

void CResolutionPropertyDlg::hiPropertyItem(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("모체자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HMN_01, _T("변환자산명"));
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

	itemKey[SPrMoTy::MTHI].RemoveAll();
	itemMappStr[SPrMoTy::MTHI].RemoveAll();
	itemListIndex[SPrMoTy::MTHI].RemoveAll();
	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(hiKey[i], cbtClass, SPrMoTy::MTHI);

		if(lowVal.size() <= hiVal.size())
		{
			for (int iv = 0; iv < (int)hiVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				SPrKe prKe;
				prKe.setVal(hiVal[iv].mappKey, hiVal[iv].key, nUser);
				itemKey[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
				//mapping key to product Name
				setPropKeyMappString(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
				setPropKeyMappListIndex(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

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
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
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
					itemKey[SPrMoTy::MTHI].SetAt(hiVal[iv].strName, prKe);
					//mapping key to product Name
					setPropKeyMappString(hiVal[iv].mappKey, SPrMoTy::MTHI, hiVal[iv].strName);
					setPropKeyMappListIndex(hiVal[iv].mappKey, SPrMoTy::MTHI, nUser);

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
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_04, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_05, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_06, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_06, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_07, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_08, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_08, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_09, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_10, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_10, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HMN_11, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				}				
			}
		}		
	}
}

void CResolutionPropertyDlg::hiPropertyRatio(CListCtrl* listCtrl, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
{
	int nUser = listCtrl->AddItem(_T("모체자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_00, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_01, _T("변환자산명"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_01, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_02, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_02, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_03, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_03, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_04, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_04, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_05, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_05, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_06, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_06, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_07, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_07, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_08, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_08, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_09, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_09, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_10, _T("설정량"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_10, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );
	listCtrl->SetItemText( nUser, SPrCoNa::HRMN_11, _T("한계치"));
	listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_11, RGB( 128, 128, 64 ), RGB( 0, 255, 0 ) );

	vector<int> lowKey;
	vector<int> hiKey;
	SPrMa prVal;
	CGAgt::PropLi()->getPropertyItem( combat, propType, cbtClass, lowKey, hiKey, prVal);

	for (int i = 0; i < (int)lowKey.size(); i++)
	{
		vector<SPrVa> lowVal = prVal.getVal(lowKey[i], cbtClass, SPrMoTy::MTLOW);
		vector<SPrVa> hiVal = prVal.getVal(hiKey[i], cbtClass, SPrMoTy::MTHI);

		if(lowVal.size() <= hiVal.size())
		{
			for (int iv = 0; iv < (int)hiVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(iv == 0 ? lowVal[0].strName : " ");
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_01, hiVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				std::wstringstream strStream;
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_02, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				strStream.str(L"");
				strStream << hiVal[iv].accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_03, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_04, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_04, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_04, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_05, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
				strStream.str(L"");
				strStream << keyval.accreditation;
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_06, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_06, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_06, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_07, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_08, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_08, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_08, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_09, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_10, strStream.str().c_str());
				listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_10, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_10, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
				listCtrl->SetItemText( nUser, SPrCoNa::HRMN_11, strStream.str().c_str());
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
			}
		}
		else
		{
			for (int iv = 0; iv < (int)lowVal.size(); iv++)
			{
				int nUser = listCtrl->AddItem(lowVal[iv].strName);
				listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_00, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

				if(iv == 0)
				{
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_01, hiVal[iv].strName);
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_01, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					std::wstringstream strStream;
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_02, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_02, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					strStream.str(L"");
					strStream << hiVal[iv].accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_03, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_03, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					SPrVa keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-1), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_04, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_04, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_04, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_05, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_05, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );

					keyval = prVal.getValKey(hiVal[iv].key, SPrMoTy::COMBATANTCLASS(cbtClass-2), SPrMoTy::MTHI);
					strStream.str(L"");
					strStream << keyval.accreditation;
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_06, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_06, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_06, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_07, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_07, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_08, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_08, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_08, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_09, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_09, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_10, strStream.str().c_str());
					listCtrl->SetItemFormat( nUser, SPrCoNa::HRMN_10, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT);
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_10, RGB( 153, 217, 234 ), RGB( 0, 0, 0 ) );
					listCtrl->SetItemText( nUser, SPrCoNa::HRMN_11, strStream.str().c_str());
					listCtrl->SetItemColours( nUser, SPrCoNa::HRMN_11, RGB( 192, 192, 192 ), RGB( 0, 0, 0 ) );
				}				
			}
		}		
	}
}

void CResolutionPropertyDlg::resolutionChangeProperty(CListCtrl* listCtrlLowRatio, CListCtrl* listCtrlLow, CListCtrl* listCtrlHiRatio, CListCtrl* listCtrlHi, SPrMoTy::COMBATANT combat, SPrMoTy::PRODUCTTYPE propType, SPrMoTy::COMBATANTCLASS cbtClass)
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
		if(itemKey[SPrMoTy::MTLOW].Lookup(listCtrlLow->GetItemText(i, SPrCoNa::LMN_00), val))
		{
			if(mappKeyBackup.end() == find(mappKeyBackup.begin(), mappKeyBackup.end(), val.getMappKey()))
			{
				vecPrKeVal.push_back(val);
				mappKeyBackup.push_back(val.getMappKey());
			}			
		}
	}

	//PropNameKeyVal::CPair* pair;
	//POSITION pos = itemKey[SPrMoTy::MTLOW].GetStartPosition();
	//while(pos)
	//{
	//	pair = NULL;
	//	osItemText.str(_T(""));
	//	pair = itemKey[SPrMoTy::MTLOW].GetNext(pos);
	//	CString str = pair->m_key;
	//	osItemText << _T("LOW ITEM : ") << str.GetBuffer() << _T("	colNum : ") << pair->m_value.getColNum() <<  _T("	mappKey : ") << pair->m_value.getMappKey() <<  _T("	primkey : ") << pair->m_value.getPrimKey() ;
	//	CLogDlg::AddLogText(osItemText.str().c_str());

	//	vector<CString> strProp;
	//	if(getPropKeyMappString(pair->m_value.getMappKey(), SPrMoTy::MTLOW, strProp))
	//	{
	//		CLogDlg::AddLogText(_T("LOW Prop Name : "));
	//		CLogDlg::AddLogText(strProp);
	//	}

	//	vector<int> idxList;
	//	if(getPropKeyMappListIndex(pair->m_value.getMappKey(), SPrMoTy::MTLOW, idxList))
	//	{
	//		CLogDlg::AddLogText(_T("LOW List Index : "));
	//		CLogDlg::AddLogText(idxList);
	//	}
	//}

	//pos = itemKey[SPrMoTy::MTHI].GetStartPosition();
	//while(pos)
	//{
	//	pair = NULL;
	//	osItemText.str(_T(""));
	//	pair = itemKey[SPrMoTy::MTHI].GetNext(pos);
	//	CString str = pair->m_key;
	//	osItemText << _T("HI ITEM : ") << str.GetBuffer() << _T("	colNum : ") << pair->m_value.getColNum() <<  _T("	mappKey : ") << pair->m_value.getMappKey() <<  _T("	primkey : ") << pair->m_value.getPrimKey() ;
	//	CLogDlg::AddLogText(osItemText.str().c_str());

	//	vector<CString> strProp;
	//	if(getPropKeyMappString(pair->m_value.getMappKey(), SPrMoTy::MTHI, strProp))
	//	{
	//		CLogDlg::AddLogText(_T("HI Prop Name : "));
	//		CLogDlg::AddLogText(strProp);

	//	}

	//	vector<int> idxList;
	//	if(getPropKeyMappListIndex(pair->m_value.getMappKey(), SPrMoTy::MTHI, idxList))
	//	{
	//		CLogDlg::AddLogText(_T("HI List index : "));
	//		CLogDlg::AddLogText(idxList);

	//	}
	//}
	//LOW -> HI 계산 세팅
	for (int mIdx = 0; mIdx < (int)mappKeyBackup.size(); mIdx++)
	{
		vector<int> idxListHiVec;
		vector<int> idxListLowVec;
		//Low Hi Mapping List가 존재할 경우
		if(getPropKeyMappListIndex(mappKeyBackup[mIdx], SPrMoTy::MTLOW, idxListLowVec) && 
			getPropKeyMappListIndex(mappKeyBackup[mIdx], SPrMoTy::MTHI, idxListHiVec))
		{
			//Low 매핑 키가 같은 아이템에 대하여 함산 개수 계산
			int itemNum = 0;
			for (int idxLowVec = 0; idxLowVec < (int)idxListLowVec.size(); idxLowVec++)
			{
				itemNum += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLowVec], SPrCoNa::LMN_01)).GetBuffer(), NULL, 10);
			}
			//설정 값이 0이면 모든 보유량 0 세팅
			if(0 == itemNum)
			{
				osItemText.str(_T(""));
				osItemText << itemNum;
				for (int idx = 0; idx < (int)idxListHiVec.size(); idx++)
				{
					listCtrlHi->SetItemText(idxListHiVec[idx] , SPrCoNa::HMN_02, osItemText.str().c_str());
					listCtrlHi->SetItemText(idxListHiVec[idx] , SPrCoNa::HMN_04, osItemText.str().c_str());
					listCtrlHi->SetItemText(idxListHiVec[idx] , SPrCoNa::HMN_06, osItemText.str().c_str());
					listCtrlHi->SetItemText(idxListHiVec[idx] , SPrCoNa::HMN_08, osItemText.str().c_str());
					listCtrlHi->SetItemText(idxListHiVec[idx] , SPrCoNa::HMN_10, osItemText.str().c_str());

					listCtrlHiRatio->SetItemText(idxListHiVec[idx] , SPrCoNa::HRMN_02, osItemText.str().c_str());
					listCtrlHiRatio->SetItemText(idxListHiVec[idx] , SPrCoNa::HRMN_04, osItemText.str().c_str());
					listCtrlHiRatio->SetItemText(idxListHiVec[idx] , SPrCoNa::HRMN_06, osItemText.str().c_str());
					listCtrlHiRatio->SetItemText(idxListHiVec[idx] , SPrCoNa::HRMN_08, osItemText.str().c_str());
					listCtrlHiRatio->SetItemText(idxListHiVec[idx] , SPrCoNa::HRMN_10, osItemText.str().c_str());
				}
			}
			//먼저 Hi 의 상의 부대 개수 세팅
			else // if(0 != itemNum)
			{
				//Low 설정 값을 Hi 보유량으로 세팅하기 위한 계산 작업
				vector<int> accTotalvec;
				int accHiTotal = 0;
				accTotalvec.resize(idxListHiVec.size());
				//Hi의 인가량을 가저와서 저장한다.
				for (int idx = 0; idx < (int)idxListHiVec.size(); idx++)
				{
					accTotalvec[idx] = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idx], SPrCoNa::HMN_02)).GetBuffer(), NULL, 10);
					accHiTotal += accTotalvec[idx];
				}
				if(accHiTotal == 0)
					continue;
				vector<float> accRatio;
				accRatio.resize(idxListHiVec.size());
				vector<int> retVal;
				retVal.resize(idxListHiVec.size());
				int retToTalVal = 0;
				//인가량을 이용하여 세팅 계산 비를 계산한다.
				for (int idx = 0; idx < (int)idxListHiVec.size(); idx++)
				{
					accRatio[idx] = itemNum * ((float)accTotalvec[idx]/(float)accHiTotal);
					retVal[idx] = (int)accRatio[idx];
					retToTalVal += retVal[idx];
				}
				//계산 비에 의해서 정수 개수 외 나머지 몇개 인가를 계산
				int retRest = itemNum - retToTalVal;
				//나머지 세팅 개수가 존재하면 진입한다.
				if(retRest > 0)
				{
					vector<SVeCoIdVa> retRestVal;
					retRestVal.resize(idxListHiVec.size());
					//비율과 인텍스를 매핑하여 저장
					for (int idx = 0; idx < (int)retRestVal.size(); idx++)
					{
						retRestVal[idx].idx = idx;
						retRestVal[idx].val = (accRatio[idx] - retVal[idx]);
					}
					//랜덤으로 임의 순서 세팅
					vector<SVeCoIdVa> listIndexSelect = CPropertyList::randomVec(retRestVal);
					//임의 순서에서 내림 차순 정령
					sort(listIndexSelect.begin(), listIndexSelect.end(), SVeCoIdVa::compare);

					int maxretValRest = 0;
					//나머지 개수 만큼 개수를 증가 시킨다.
					while(retRest > 0 && maxretValRest < (int)listIndexSelect.size())
					{
						retVal[listIndexSelect[maxretValRest].idx]++;
						retRest--;
						maxretValRest++;
					}

				}
				//Low 설정 값 -> Hi 보유량 최종 세팅
				for (int idx = 0; idx < (int)accTotalvec.size(); idx++)
				{
					osItemText.str(_T(""));
					osItemText << retVal[idx];
					listCtrlHi->SetItemText(idxListHiVec[idx], SPrCoNa::HMN_02, osItemText.str().c_str());
				}

				//Hi의 각 하위 4개 개체로 분할 세팅 계산.
				for (int idxHi = 0; idxHi < (int)idxListHiVec.size(); idxHi++)
				{
					int hItemNum = strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], SPrCoNa::HMN_02)).GetBuffer(), NULL, 10);
					int accTotal = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idxHi], SPrCoNa::HRMN_02)).GetBuffer(), NULL, 10);
					if(accTotal == 0)
						continue;
					vector<int> accVec;
					accVec.resize(4);
					//세팅이 필요한 인가량을 가져온다.
					accVec[0] = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[0])).GetBuffer(), NULL, 10);
					accVec[1] = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[1])).GetBuffer(), NULL, 10);
					accVec[2] = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[2])).GetBuffer(), NULL, 10);
					accVec[3] = strtoul(CStringA(listCtrlHiRatio->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[3])).GetBuffer(), NULL, 10);

					vector<float>  accRatio;
					accRatio.resize(4);
					for (int idx = 0; idx < (int)accVec.size(); idx++)
					{
						accRatio[idx] = hItemNum * ((float)accVec[idx]/(float)accTotal);
					}

					vector<int> retVal;
					retVal.resize(4);
					retVal[0] = (int)accRatio[0];
					retVal[1] = (int)accRatio[1];
					retVal[2] = (int)accRatio[2];
					retVal[3] = (int)accRatio[3];
					int retToTalVal = retVal[0] + retVal[1] + retVal[2] + retVal[3];
					int retRest = hItemNum - retToTalVal;

					if(retRest > 0)
					{
						vector<SVeCoIdVa> retRestVal;
						retRestVal.resize(4);
						for (int idx = 0; idx < (int)retRestVal.size(); idx++)
						{
							retRestVal[idx].idx = idx;
							retRestVal[idx].val = (accRatio[idx] - retVal[idx]);
						}
						vector<SVeCoIdVa> listIndexSelect = CPropertyList::randomVec(retRestVal);
						sort(listIndexSelect.begin(), listIndexSelect.end(), SVeCoIdVa::compare);

						int maxretValRest = 0;
						while(retRest > 0 && maxretValRest < (int)listIndexSelect.size())
						{
							retVal[listIndexSelect[maxretValRest].idx]++;
							retRest--;
							maxretValRest++;
						}

					}						

					for (int idx = 0; idx < (int)accVec.size(); idx++)
					{
						osItemText.str(_T(""));
						osItemText << retVal[idx];
						listCtrlHi->SetItemText(idxListHiVec[idxHi] , setHiRetenListNum[idx], osItemText.str().c_str());
					}
				}
			}

		}
		//Low Hi Mapping List가 없을 경우
		else
		{
			MessageBox( _T("Low - Hi Mapping List가 없다"), _T("매핑오류"), MB_OK);
		}
	}

	//HI -> LOW 계산 세팅
	for (int mIdx = 0; mIdx < (int)mappKeyBackup.size(); mIdx++)
	{
		vector<int> idxListHiVec;
		vector<int> idxListLowVec;
		//Low Hi Mapping List가 존재할 경우
		if(getPropKeyMappListIndex(mappKeyBackup[mIdx], SPrMoTy::MTLOW, idxListLowVec) && 
			getPropKeyMappListIndex(mappKeyBackup[mIdx], SPrMoTy::MTHI, idxListHiVec))
		{
			vector<int> retenHiVec(4,0);
			vector<int> accLowTotal(4,0);
			vector<int> accLowRatioTotal(4,0);
			//Hi의 각 하위 보유량 합산 개수
			for (int idxHi = 0; idxHi < (int)idxListHiVec.size(); idxHi++)
			{
				//보유량 합산
				retenHiVec[0] += strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[0])).GetBuffer(), NULL, 10);
				retenHiVec[1] += strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[1])).GetBuffer(), NULL, 10);
				retenHiVec[2] += strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[2])).GetBuffer(), NULL, 10);
				retenHiVec[3] += strtoul(CStringA(listCtrlHi->GetItemText(idxListHiVec[idxHi], setHiRetenListNum[3])).GetBuffer(), NULL, 10);
			}

			//Low의 각 하위  설정량 합산 개수
			for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
			{
				//설정량 합산
				accLowRatioTotal[0] += strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[0])).GetBuffer(), NULL, 10);
				accLowRatioTotal[1] += strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[1])).GetBuffer(), NULL, 10);
				accLowRatioTotal[2] += strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[2])).GetBuffer(), NULL, 10);
				accLowRatioTotal[3] += strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[3])).GetBuffer(), NULL, 10);

				//Low 인가량 합산
				accLowTotal[0] += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLow], setLowAccListNum[0])).GetBuffer(), NULL, 10);
				accLowTotal[1] += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLow], setLowAccListNum[1])).GetBuffer(), NULL, 10);
				accLowTotal[2] += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLow], setLowAccListNum[2])).GetBuffer(), NULL, 10);
				accLowTotal[3] += strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLow], setLowAccListNum[3])).GetBuffer(), NULL, 10);
			}

			for (int idxRtn = 0; idxRtn < (int)retenHiVec.size(); idxRtn++)
			{
				if(0 == accLowRatioTotal[idxRtn])
					continue;
				//보유량 합산이 0이면 0 세팅
				if(0 == retenHiVec[idxRtn])
				{
					//Hi 값 -> LOW 보유량 최종 세팅
					for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
					{
						osItemText.str(_T(""));
						osItemText << retenHiVec[idxRtn];
						listCtrlLow->SetItemText(idxListLowVec[idxLow], setLowRetenListNum[idxRtn], osItemText.str().c_str());
					}
				}
				else // if(0 != retenHiVec[idxRtn])
				{
					vector<float> accRatio;
					accRatio.resize(idxListLowVec.size());
					vector<int> retVal;
					retVal.resize(idxListLowVec.size());
					int retToTalVal = 0;
					vector<int> accValTotal;
					accValTotal.resize(idxListLowVec.size());
					for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
					{
						//LOW 인가량 저장
						accValTotal[idxLow] = strtoul(CStringA(listCtrlLow->GetItemText(idxListLowVec[idxLow], setLowAccListNum[idxRtn])).GetBuffer(), NULL, 10);
						//LOW 비율
						int lowRatioVal = strtoul(CStringA(listCtrlLowRatio->GetItemText(idxListLowVec[idxLow], setLowRetenRitioNum[idxRtn])).GetBuffer(), NULL, 10);

						accRatio[idxLow] = retenHiVec[idxRtn] * ((float)lowRatioVal/(float)accLowRatioTotal[idxRtn]);
						retVal[idxLow] = (int)accRatio[idxLow];
						retToTalVal += retVal[idxLow];
					}
					//계산 비에 의해서 정수 개수 외 나머지 몇개 인가를 계산
					int retRest = retenHiVec[idxRtn] - retToTalVal;

					//나머지 세팅 개수가 존재하면 진입한다.
					if(retRest > 0)
					{
						vector<SVeCoIdVa> retRestVal;
						retRestVal.resize(idxListLowVec.size());
						//비율과 인텍스를 매핑하여 저장
						for (int idx = 0; idx < (int)retRestVal.size(); idx++)
						{
							retRestVal[idx].idx = idx;
							retRestVal[idx].val = (accRatio[idx] - retVal[idx]);
						}
						//랜덤으로 임의 순서 세팅
						vector<SVeCoIdVa> listIndexSelect = CPropertyList::randomVec(retRestVal);
						//임의 순서에서 내림 차순 정령
						sort(listIndexSelect.begin(), listIndexSelect.end(), SVeCoIdVa::compare);

						int maxretValRest = 0;
						//나머지 개수 만큼 개수를 증가 시킨다.
						while(retRest > 0 && maxretValRest < (int)listIndexSelect.size())
						{
							retVal[listIndexSelect[maxretValRest].idx]++;
							retRest--;
							maxretValRest++;
						}

					}
					//Hi 값 -> LOW 보유량 최종 세팅
					for (int idxLow = 0; idxLow < (int)idxListLowVec.size(); idxLow++)
					{
						osItemText.str(_T(""));
						osItemText << retVal[idxLow];
						listCtrlLow->SetItemText(idxListLowVec[idxLow], setLowRetenListNum[idxRtn], osItemText.str().c_str());
					}
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
}

void CResolutionPropertyDlg::setPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, CString propName)
{
	PropKeyMappString::CPair* pair = itemMappStr[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(propName);
	}
	else
	{
		SPrKeMaSt keyMappStr;
		keyMappStr.setVal(propName);
		itemMappStr[modelType].SetAt(mappKey, keyMappStr);
	}
}

bool CResolutionPropertyDlg::getPropKeyMappString(int mappKey, SPrMoTy::MODELTYPE modelType, vector<CString>& strProp)
{
	PropKeyMappString::CPair* pair = itemMappStr[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		strProp = pair->m_value.getVal();
	}
	return (0 != strProp.size());
}

void CResolutionPropertyDlg::setPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, int idx)
{
	PropKeyMappListIndex::CPair* pair = itemListIndex[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		pair->m_value.setVal(idx);
	}
	else
	{
		SPrKeMaLiIn keyMapp;
		keyMapp.setVal(idx);
		itemListIndex[modelType].SetAt(mappKey, keyMapp);
	}
}

bool CResolutionPropertyDlg::getPropKeyMappListIndex(int mappKey, SPrMoTy::MODELTYPE modelType, vector<int>& idxVal)
{
	PropKeyMappListIndex::CPair* pair = itemListIndex[modelType].Lookup(mappKey);
	if(pair != NULL)
	{
		idxVal = pair->m_value.getVal();
	}
	return (0 != idxVal.size());
}