// XMLDlg.cpp : implementation of the XMLDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLDlg.h"
#include "tinyxml.h"
#include <iostream>

BOOL CXMLDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CXMLDlg::OnIdle()
{
	return FALSE;
}

LRESULT CXMLDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CXMLDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CXMLDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT CXMLDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void CXMLDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}


LRESULT CXMLDlg::OnBnClickedXmlfilewrite(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//xml 선언
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//루트 노드 추가
	TiXmlElement* pRoot = new TiXmlElement("DB");
	doc.LinkEndChild(pRoot);

	//주석 문장 추가
	TiXmlComment* pComment = new TiXmlComment();
	pComment->SetValue("This is score DB");
	pRoot->LinkEndChild(pComment);

	// 하위노드 및 데이터 추가
	TiXmlElement* pElem = new TiXmlElement("class1");
	pRoot->LinkEndChild(pElem);
	TiXmlElement* pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("JJJ"));
	pElem->LinkEndChild(pElem0);

	//하위노드 및 속성 추가
	TiXmlElement* pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("aa", 100);
	pSubElem->SetAttribute("bb", 50);
	pSubElem->SetAttribute("cc", 90);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("aa", 90);
	pSubElem->SetAttribute("bb", 70);
	pSubElem->SetAttribute("cc", 95);

	pElem = new TiXmlElement("class2");
	pRoot->LinkEndChild(pElem);
	pElem0 = new TiXmlElement("Teacher");
	pElem0->LinkEndChild(new TiXmlElement("SSS"));
	pElem->LinkEndChild(pElem0);

	pSubElem = new TiXmlElement("English");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 70);
	pSubElem->SetAttribute("vc", 90);
	pSubElem->SetAttribute("ds", 30);

	pSubElem = new TiXmlElement("Math");
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("name", "score");
	pSubElem->SetAttribute("ab", 60);
	pSubElem->SetAttribute("vc", 70);
	pSubElem->SetAttribute("ds", 25);

	doc.SaveFile("Test.xml");
	return 0;
}

LRESULT CXMLDlg::OnBnClickedXmlfileread(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile("Test.xml");// xml 파일 로드
	//"DB"라는 노드를 찾는다
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
	//ReadRoot("DB")노드 하위의 "class1",의 하위 "Teacher"라는 노드를 찾는다.
	TiXmlElement* sub = ReadRoot->FirstChildElement("class1")->FirstChildElement("Teacher");
	TiXmlHandle handle(0);// 노드를 다루기 위한 핸들
	handle = TiXmlHandle(sub);
	//ReadRoot->Value() ReadRoot의 노드 명을 반환한다 "DB"

	CLogDlg::initStream();
	CLogDlg::insertStream("ReadRoot->Value() ReadRoot의 노드 명을 반환한다 :");
	CLogDlg::insertStream(ReadRoot->Value());
	CLogDlg::addLogTextStream();


	//핸들에 저장된 노드 하위에 존재하는 노드를 찾는다. 그 노드명을 반환한다.
	TiXmlElement* tmp = handle.FirstChildElement().Element();

	CLogDlg::initStream();
	CLogDlg::insertStream("핸들에 저장된 노드 하위에 존재하는 노드를 찾는다. :");
	CLogDlg::insertStream(tmp->Value());
	CLogDlg::addLogTextStream();

	sub = ReadRoot->FirstChildElement("class1")->FirstChildElement("English");
	//sub(class1->english의 속성을 읽어온다.
	TiXmlAttribute *pAttrib;
	pAttrib = sub->FirstAttribute();
	while (pAttrib)
	{
		CLogDlg::initStream();
		CLogDlg::insertStream("sub(class1->english의 속성을 읽어온다. :");
		CLogDlg::insertStream(pAttrib->Name(), ' ');
		CLogDlg::insertStream(pAttrib->Value(), ' ');
		CLogDlg::addLogTextStream();

		pAttrib = pAttrib->Next();
	}
	return 0;
}
