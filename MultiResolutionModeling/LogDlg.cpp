// LogDlg.cpp : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LogDlg.h"
#include "CSVFile.h"

CLogDlg* CLogDlg::gLogDlg=NULL;
std::stringstream CLogDlg::mkLog;
std::stringstream CLogDlg::mkcsvLog;
bool CLogDlg::bFirst;
CButton CLogDlg::csvLogCheck;
CLogDlg::CLogDlg()
{
	mkLog.str("");
	mkcsvLog.str("");
	bFirst = true;
}
CLogDlg::~CLogDlg()
{
}

LRESULT CLogDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	csvLogCheck.Attach(GetDlgItem(IDCCK_LOGCSVFILE));
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
		bool _bFirst = true;
		for (int i = 0; i <(int) text.size(); i++)
		{
			if(false == _bFirst) coutLog  << delimiter;
			_bFirst = false;
			coutLog  << text[i];
		}
		gLogDlg->setLogText(coutLog.str().c_str());
	}
}

void CLogDlg::AddLogText(vector<float> text, char delimiter)
{
	if(gLogDlg)
	{
		std::stringstream coutLog;
		bool _bFirst = true;
		for (int i = 0; i <(int) text.size(); i++)
		{
			if(false == _bFirst) coutLog  << delimiter;
			_bFirst = false;
			coutLog  << text[i];
		}
		gLogDlg->setLogText(coutLog.str().c_str());
	}
}

void CLogDlg::AddLogText(vector<string> text, char delimiter)
{
	if(gLogDlg)
	{
		std::stringstream coutLog;
		bool _bFirst = true;
		for (int i = 0; i <(int) text.size(); i++)
		{
			if(false == _bFirst) coutLog  << delimiter;
			_bFirst = false;
			coutLog  << text[i].c_str();
		}
		gLogDlg->setLogText(coutLog.str().c_str());
	}
}

void CLogDlg::AddLogText(vector<CString> text, char delimiter)
{
	if(gLogDlg)
	{
		std::stringstream coutLog;
		bool _bFirst = true;
		for (int i = 0; i <(int) text.size(); i++)
		{
			if(false == _bFirst) coutLog  << delimiter;
			_bFirst = false;
			coutLog  << CStringA(text[i]);
		}
		gLogDlg->setLogText(coutLog.str().c_str());
	}
}

void CLogDlg::initStream()
{
	mkLog.str("");
	mkLog.clear();
	mkcsvLog.str("");
	mkcsvLog.clear();
	bFirst = true;
}

void CLogDlg::insertStream(string str, char delimiter)
{
	if(false == bFirst) mkLog  << delimiter;
	if(false == bFirst) mkcsvLog  << ',';
	bFirst = false;
	mkLog  << str.c_str();
	mkcsvLog  << str.c_str();	
}

void CLogDlg::insertStream(wstring str, char delimiter)
{
	if(false == bFirst) mkLog  << delimiter;
	if(false == bFirst) mkcsvLog  << ',';
	bFirst = false;
	mkLog  << CStringA(str.c_str()).GetBuffer();
	mkcsvLog  << CStringA(str.c_str()).GetBuffer();
}

void CLogDlg::insertStream(int val, char delimiter)
{
	if(false == bFirst) mkLog  << delimiter;
	if(false == bFirst) mkcsvLog  << ',';
	bFirst = false;
	mkLog  << val;
	mkcsvLog  << val;
}

void CLogDlg::insertStreamVec(vector<int> val, char delimiter)
{
	for (int i = 0; i <(int) val.size(); i++)
	{
		if(false == bFirst) mkLog  << delimiter;
		if(false == bFirst) mkcsvLog  << ',';
		bFirst = false;
		mkLog  << val[i];
		mkcsvLog  << val[i];
	}

}

void CLogDlg::insertStreamVec(vector<float> val, char delimiter)
{
	for (int i = 0; i <(int) val.size(); i++)
	{
		if(false == bFirst) mkLog  << delimiter;
		if(false == bFirst) mkcsvLog  << ',';
		bFirst = false;
		mkLog  << val[i];
		mkcsvLog  << val[i];
	}

}

void CLogDlg::insertStreamVec(vector<string> val, char delimiter)
{
	for (int i = 0; i <(int) val.size(); i++)
	{
		if(false == bFirst) mkLog  << delimiter;
		if(false == bFirst) mkcsvLog  << ',';
		bFirst = false;
		mkLog  << val[i];
		mkcsvLog  << val[i];
	}
}

void CLogDlg::addLogTextStream()
{
	if(gLogDlg)
	{
		gLogDlg->setLogText(mkLog.str().c_str());
		
		if(BST_CHECKED == CLogDlg::csvLogCheck.GetCheck())
			CCSVFile::csv_write_log(mkcsvLog.str().c_str());
	}
}