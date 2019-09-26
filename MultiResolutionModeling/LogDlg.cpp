// LogDlg.cpp : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LogDlg.h"

CLogDlg* CLogDlg::gLogDlg=NULL;
CLogDlg::CLogDlg()
{
}
CLogDlg::~CLogDlg()
{
}

LRESULT CLogDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CLogDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

CString CLogDlg::getLogText()
{
	CString logText = _T("");
	CEdit log = GetDlgItem(IDC_LOGTEXT);
	log.GetWindowText(logText);
	return logText.GetBuffer();
}

void CLogDlg::setLogText(CString text)
{
	CEdit log = GetDlgItem(IDC_LOGTEXT);
	log.AppendText(text+"\r\n");
}

void CLogDlg::AddLogText(CString text)
{
	if(gLogDlg)
	{
		gLogDlg->setLogText(text);
	}
}

void CLogDlg::AddLogText(vector<int> text, char delimiter)
{
	if(gLogDlg)
	{
		std::stringstream coutLog;
		for (int i = 0; i <(int) text.size(); i++)
		{
			coutLog  << text[i] << delimiter;
		}
		gLogDlg->setLogText(coutLog.str().c_str());
	}
}