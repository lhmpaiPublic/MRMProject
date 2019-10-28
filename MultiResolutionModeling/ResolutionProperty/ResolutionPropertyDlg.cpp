// ResolutionPropertyDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResolutionPropertyDlg.h"
#include "PropertyList.h"


CResolutionPropertyDlg::CResolutionPropertyDlg()
{
	m_lowModelList.RegisterClass();
	m_hiModelList.RegisterClass();
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

	startPoint = CPoint(0, 0);
	bLClick = false;
	GetWindowRect(winPos);

	CPropertyList test;
	test.loadCSVFile("infantryPropertyList.csv");

	m_lowModelList.SubclassWindow(GetDlgItem(IDCCUST_LOWMODELLIST));
	m_hiModelList.SubclassWindow(GetDlgItem(IDCCUST_HIMODELLIST));

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

	m_hiModelList.SetImageList( m_ilItemImages );
	m_hiModelList.SetFocusSubItem( TRUE );

	m_lowModelList.AddColumn( _T( "부대타입" ), 250, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_lowModelList.AddColumn( _T( "대대" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "대대본부" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.AddColumn( _T( "중대" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT   );
	m_lowModelList.AddColumn( _T( " " ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
	m_lowModelList.ShowHeaderSort(FALSE);	
	test.initPropertyItem(SPrMoTy::MTLOW, &m_lowModelList);

	m_hiModelList.AddColumn( _T( "부대타입" ), 250, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelList.AddColumn( _T( " " ), 250, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT  );
	m_hiModelList.AddColumn( _T( "대대" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.AddColumn( _T( " " ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.AddColumn( _T( "본부대대" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.AddColumn( _T( "중대1" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.AddColumn( _T( "중대2" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.AddColumn( _T( "중대3" ), 80, -1, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_hiModelList.ShowHeaderSort(FALSE);	
	test.initPropertyItem(SPrMoTy::MTHI, &m_hiModelList);

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
