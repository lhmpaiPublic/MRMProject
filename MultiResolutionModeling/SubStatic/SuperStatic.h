
#ifndef __SUPERSTATIC_B7A15A9D01DC403996FC45F7F92F52D3_H__
#define __SUPERSTATIC_B7A15A9D01DC403996FC45F7F92F52D3_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��ư �̹��� ����


class CSuperStatic : public CWindowImpl<CSuperStatic, CStatic>, public COwnerDraw<CSuperStatic>,public CMessageFilter
{
	//
	typedef vector<CBitmapHandle> VECBITHANDLE;
	//��Ʈ ����
	LOGFONT fontinfo;
	//��Ʈ Į��
	COLORREF fontcolor;
	BOOL bNeedImage;
	int mgnum;
	//��Ʈ�� ��ư �̹��� ����
	VECBITHANDLE staticimage;
	CRgnHandle m_hRgn;
public:
	DECLARE_WND_SUPERCLASS(_T("SuperStatic"), _T("STATIC"))
	BEGIN_MSG_MAP_EX(CSuperStatic)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MSG_WM_CREATE(OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CSuperStatic>, 1)
		DEFAULT_REFLECTION_HANDLER()
		END_MSG_MAP()
	//������
	CSuperStatic(void);
	//�Ҹ���
	~CSuperStatic(void);
	//
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//��ư �ʱ�ȭ �Լ�
	void initSuperStatic(UINT ImageId, BOOL bOwnerDraw=TRUE);
#ifdef WINCE
	void initSuperStatic(UINT ImageId, LPCWSTR type, BOOL bOwnerDraw=TRUE);
#endif //WINCE
	void initSuperStatic(CBitmapHandle bit, BOOL bOwnerDraw=TRUE);
	//Rgn  �ʱ�ȭ �Լ�
	void initRgnSuperStatic(UINT ImageId, UINT MaskId, BOOL bOwnerDraw=TRUE);
	//Owner Draw ȣ�� �Լ�
	void DrawItem(LPDRAWITEMSTRUCT lpdis);
	//��ư �׸���;
	void DrawStatic(CDC * pDC, UINT state);
	//�ؽ�Ʈ�� ���� �Լ�
	void DrawWhiteText(CDC* pDC, SIZE bmSize);
	//����Ŭ���� �Լ�
	BOOL SubclassWindow(HWND hWnd);
	HWND UnsubclassWindow(BOOL bForce = FALSE);
	//��ư ����
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnEraseBkgnd(CDCHandle dc);
	//��Ʈ ����
	void SetSuperStaticFont(LOGFONT* fontinfo=NULL,COLORREF* fontcolor=NULL);
	//�̹��� ����
	void StaticClear();
	//
	BOOL DivideHbitmap(CBitmapHandle hbit);
	//Rgn 
	BOOL RgnDivideHbitmap(CBitmapHandle hbit);
	//�̹��� �߰� �Լ�
	void AddImagedata(CBitmapHandle bit);
	//
	void AddImagedata(UINT ImageId);
	//Rgn �̹��� �߰�
	void AddImagedataRgn(UINT ImageId, UINT MaskId);
#ifdef WINCE
	BOOL MakeResource(HMODULE hMod, UINT resId, LPCWSTR type);
#endif //WINCE
};
#endif// __SUPERSTATIC_B7A15A9D01DC403996FC45F7F92F52D3_H__
