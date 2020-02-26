// ExcelAutoDlg.cpp : implementation of the ExcelAutoDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExcelAutoDlg.h"
CExcelAutoDlg::CExcelAutoDlg()
{
	xlEz = NULL;
}

CExcelAutoDlg::~CExcelAutoDlg()
{
	if(NULL != xlEz)
	{
		xlEz->CloseExcelFile();
		xlEz->ReleaseExcel();
		delete xlEz;
		xlEz = NULL;
	}
}

BOOL CExcelAutoDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CExcelAutoDlg::OnIdle()
{
	return FALSE;
}

LRESULT CExcelAutoDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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


	return FALSE;
}

LRESULT CExcelAutoDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CExcelAutoDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CExcelAutoDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void CExcelAutoDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}
LRESULT CExcelAutoDlg::OnBnClickedExcelautostart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(NULL == xlEz)
	{
		TCHAR tcPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, tcPath);
		CString sPath;
		sPath.Format(_T("%s\\sampleExcel.xls"), tcPath);
		xlEz = new CXLEzAutomation();
		xlEz->OpenExcelFile(sPath.GetBuffer(), _T("Ship"));
		CString valxl;// = xlEz.GetCellValue(1, 1);
		valxl = xlEz->GetCellValue(1, 2);
		valxl = xlEz->GetCellValue(1, 3);
		valxl = xlEz->GetCellValue(2, 1);

		//xlEz->SetExcelVisible(TRUE);
		xlEz->selectWorksheets(_T("Aircraft"));
		valxl = xlEz->GetCellValue(1, 1);
		valxl = xlEz->GetCellValue(1, 2);
		valxl = xlEz->GetCellValue(1, 3);
	}
	
	return 0;
}

LRESULT CExcelAutoDlg::OnBnClickedExcelautorelease(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(NULL != xlEz)
	{
		xlEz->CloseExcelFile();
		xlEz->ReleaseExcel();
		delete xlEz;
		xlEz = NULL;
	}
	return 0;
}
