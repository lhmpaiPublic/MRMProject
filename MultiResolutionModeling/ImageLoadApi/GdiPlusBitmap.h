
#ifndef __GDIPLUSBITMAP_74F736E25AB94b5dA789E4730F58F2A1_H__
#define __GDIPLUSBITMAP_74F736E25AB94b5dA789E4730F58F2A1_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//���� �ε带 �⺻���� �ϴ� ��Ʈ�� Ŭ����
class CGdiPlusBitmap
{
	 static ULONG_PTR       m_gdiplusToken;
public:
	//======================================================//
	//			Gdi ��Ʈ��
	//======================================================//
	Gdiplus::Bitmap* m_pBitmap;
public:
	//������
	CGdiPlusBitmap();
	CGdiPlusBitmap(LPCWSTR pFile);
	//�Ҹ���
	virtual ~CGdiPlusBitmap();
	//��ü�� ����
	void Empty();
	//������ �̿��Ͽ� ��Ʈ���� ���� ��
	bool Load(LPCWSTR pFile);
	//����
	bool SavePNG(const CString strSaveFilePath);
	//��Ʈ�� ��ü�� �ѱ��
	operator Gdiplus::Bitmap*() const;
	//Gdiplus ��� ���
	static void GdiStart();
	//Gdiplus ��� ����
	static void GdiShut();
	//png encod
	static int GetEncoderClsid(const WCHAR* format/*IN*/, CLSID* pClsid/*OUT*/);
	//
	static BOOL SaveTransparentHBITMAPPNG(const HBITMAP& hSrcBimap, const CString strSaveFilePath, COLORREF colorRemove, WCHAR* format = CA2T("Image/png"));

	DWORD GetBitmapBits() const
	{
		CBitmapHandle hBitmap;
		m_pBitmap->GetHBITMAP(RGB(0,0,0), &hBitmap.m_hBitmap);
		return 0;
	}
};
//���ҽ� �̹����� �ε��ؼ� ���� ���� Ŭ����
class CGdiPlusBitmapResource : public CGdiPlusBitmap
{
protected:
	//�۷ι� �״� �޸� ���� ��ü
	HGLOBAL m_hBuffer;
public:
	// ������
	CGdiPlusBitmapResource();
	CGdiPlusBitmapResource(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	CGdiPlusBitmapResource(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	CGdiPlusBitmapResource(UINT id, UINT type, HMODULE hInst = NULL);
	//�Ҹ���
	virtual ~CGdiPlusBitmapResource();
	//��ü�� ����
	void Empty();
	//���ҽ� �ε��Լ�
	bool Load(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	bool Load(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);
	bool Load(UINT id, UINT type, HMODULE hInst = NULL);
	//��Ʈ�� ������ �ѱ��
	CBitmap GetWinBitmap();

};
#endif //__GDIPLUSBITMAP_74F736E25AB94b5dA789E4730F58F2A1_H__