
#include "stdAfx.h"
CSuperEditImpl * CSuperEditImpl::pThis = NULL;

//--------------------------------------------------------------
//|
//|������
//|
//---------------------------------------------------------------
CSuperEditImpl::CSuperEditImpl() : m_hHook(NULL) { }
//--------------------------------------------------------------
//|
//| ��� �Լ�
//|
//---------------------------------------------------------------
void CSuperEditImpl::PreSubclassWindow(HWND hWnd)
{
	ATLASSERT(::IsWindow(hWnd));
	// default : NOP
}
//--------------------------------------------------------------
//|
//|���� ��� �Լ�
//|
//---------------------------------------------------------------
HWND CSuperEditImpl::Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName /*= NULL*/,
							DWORD dwStyle/* = 0*/, DWORD dwExStyle /*= 0*/,	UINT nID /*= 0*/, LPVOID lpCreateParam /*= NULL*/)
{
	// to set up CBT hook for subclassing (in order to be able to receive WM_NCCREATE and WM_CREATE messages)
	pThis = this;
	m_hHook = ::SetWindowsHookEx(WH_CBT, &CBTHookProc, NULL, ::GetCurrentThreadId());

	CEdit wndTemp;
	// to create a TBase window to subclass
	wndTemp.Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	if(m_hHook)
	{
		// to remove CBT hook (just in case)
		::UnhookWindowsHookEx(m_hHook);
		m_hHook = NULL;
		pThis = NULL;
	}
	ATLASSERT(wndTemp.IsWindow());
	HWND hWnd = wndTemp.m_hWnd;
	wndTemp.Detach();
	return hWnd;
}
//--------------------------------------------------------------
//|
//|����Ŭ���� ��� �Լ�
//|
//---------------------------------------------------------------
BOOL CSuperEditImpl::SubclassWindow(HWND hWnd)
{
	PreSubclassWindow(hWnd);
	return baseClass::SubclassWindow(hWnd);
}
//--------------------------------------------------------------
//|
//|��ŷ �ݹ� ��� �Լ�
//|
//---------------------------------------------------------------
LRESULT CALLBACK CSuperEditImpl::CBTHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	ATLASSERT(NULL != CSuperEditImpl::pThis);
	if(HCBT_CREATEWND == nCode)
	{
		HWND hwndCreated = (HWND)wParam;
		LPCBT_CREATEWND lpccw = (LPCBT_CREATEWND)lParam;
		if( CSuperEditImpl::pThis && NULL == CSuperEditImpl::pThis->m_hWnd && !::lstrcmpi( lpccw->lpcs->lpszClass, _T("EDIT") ) )
		{
			CSuperEditImpl::pThis->SubclassWindow(hwndCreated);
			LRESULT lRes = ::CallNextHookEx(CSuperEditImpl::pThis->m_hHook, nCode, wParam, lParam);
			// to remove CBT hook immediately
			::UnhookWindowsHookEx(CSuperEditImpl::pThis->m_hHook);
			CSuperEditImpl::pThis->m_hHook = NULL;
			CSuperEditImpl::pThis = NULL;
			return lRes;
		}
	}
	return ::CallNextHookEx(CSuperEditImpl::pThis->m_hHook, nCode, wParam, lParam);
}
