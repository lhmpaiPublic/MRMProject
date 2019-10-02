
#include "stdafx.h"
//Gdiplus ���̺귯�� ��ũ
#pragma comment(lib, "gdiplus.lib")
//==================================================================
//|
//|CGdiPlusBitmap Ŭ����
//|
//==================================================================
//
//--------------------------------------------------------------
//|
//|��ü �ʱ�ȭ
//|
//---------------------------------------------------------------
ULONG_PTR       CGdiPlusBitmap::m_gdiplusToken=0;
//Gdiplus ��� ���
void CGdiPlusBitmap::GdiStart()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

//--------------------------------------------------------------
//|
//|Gdiplus ��� ����
//|
//---------------------------------------------------------------
void CGdiPlusBitmap::GdiShut()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}
//GIF ���� �ִϸ��̼� ����
// How many frame dimensions does the Image object have?
// CLSID encoderClsid;
// int result = GetEncoderClsid( L"image/gif", &encoderClsid );
// if( result < 0 )
// {
// 
// }
// 
// Image *image1 = NULL;
// image1 = new Image( L"d:\\ani.gif", TRUE );
// if( !image1 )
// return -1;
// 
// if( image1->GetLastStatus() != Ok )
// return -1;
// 
// UINT count = 0;
// count = image1->GetFrameDimensionsCount();
// GUID *pDimensionIDs = new GUID[ count ];
// 
// // Get the list of frame dimensions from the Image object.
// image1->GetFrameDimensionsList( pDimensionIDs, count );
// 
// // Display the GUID of the first (and only) frame dimension.
// WCHAR strGuid[39];
// StringFromGUID2( pDimensionIDs[0], strGuid, 39 );
// 
// // Get the number of frames in the first dimension.
// UINT frameCount = image1->GetFrameCount(&pDimensionIDs[0]);
// 
// Graphics graph( hWnd );
// 
// static UINT uIndex = 0;
// 
// image1->SelectActiveFrame( &pDimensionIDs[0], uIndex );
// 
// float fRate = static_cast<float>(image1->GetHeight())/image1->GetWidth();
// 
// graph.FillRectangle( &SolidBrush( Color( 128, 128, 255 ) ), 0, 0, 600, static_cast<int>(600*fRate) );
// 
// graph.DrawImage( image1, 0, 0, 600, static_cast<int>(600*fRate) );
// 
// uIndex = (uIndex + 1) % 6;
// 
// delete []pDimensionIDs;
// 
// delete image1;
//--------------------------------------------------------------
//|
//|������
//|
//---------------------------------------------------------------
CGdiPlusBitmap::CGdiPlusBitmap()
{
	m_pBitmap = NULL; 
}
//--------------------------------------------------------------
//|
//|���� ��θ� �ѱ�� ������
//|
//---------------------------------------------------------------
CGdiPlusBitmap::CGdiPlusBitmap(LPCWSTR pFile)
{
	m_pBitmap = NULL; Load(pFile); 
}
//--------------------------------------------------------------
//|
//|�Ҹ���
//|
//---------------------------------------------------------------
CGdiPlusBitmap::~CGdiPlusBitmap()
{
	Empty(); 
}
//--------------------------------------------------------------
//|
//|��ü�� �޸� ����
//|
//---------------------------------------------------------------
void CGdiPlusBitmap::Empty()
{
	delete m_pBitmap; m_pBitmap = NULL; 
}
//--------------------------------------------------------------
//|
//|���� �ε� �Լ�
//|
//---------------------------------------------------------------
bool CGdiPlusBitmap::Load(LPCWSTR pFile)
{
	Empty();
	m_pBitmap = Gdiplus::Bitmap::FromFile(pFile);
	return m_pBitmap->GetLastStatus() == Gdiplus::Ok;
}
//--------------------------------------------------------------
//|
//|GDIPlus ��ü�� �ѱ��
//|
//---------------------------------------------------------------
CGdiPlusBitmap::operator Gdiplus::Bitmap*() const
{
	return m_pBitmap; 
}
//==================================================================
//|
//|CGdiPlusBitmapResource Ŭ����
//|
//==================================================================
//--------------------------------------------------------------
//|
//|������
//|
//---------------------------------------------------------------
CGdiPlusBitmapResource::CGdiPlusBitmapResource()
{ 
	m_hBuffer = NULL; 
}
//--------------------------------------------------------------
//|
//|��ü �μ�, 
//|
//---------------------------------------------------------------
CGdiPlusBitmapResource::CGdiPlusBitmapResource(LPCTSTR pName, LPCTSTR pType, HMODULE hInst)
{
	m_hBuffer = NULL; Load(pName, pType, hInst); 
}
//--------------------------------------------------------------
//|
//|
//|
//---------------------------------------------------------------
CGdiPlusBitmapResource::CGdiPlusBitmapResource(UINT id, LPCTSTR pType, HMODULE hInst)
{
	m_hBuffer = NULL; Load(id, pType, hInst); 
}
//--------------------------------------------------------------
//|
//|
//|
//---------------------------------------------------------------
CGdiPlusBitmapResource::CGdiPlusBitmapResource(UINT id, UINT type, HMODULE hInst)
{
	m_hBuffer = NULL; Load(id, type, hInst); 
}
//--------------------------------------------------------------
//|
//|�Ҹ���
//|
//---------------------------------------------------------------
CGdiPlusBitmapResource::~CGdiPlusBitmapResource()
{
	Empty();
}
//--------------------------------------------------------------
//|
//|���ҽ� �ε�
//|
//---------------------------------------------------------------
bool CGdiPlusBitmapResource::Load(UINT id, LPCTSTR pType, HMODULE hInst )
{
	return Load(MAKEINTRESOURCE(id), pType, hInst);
}
//--------------------------------------------------------------
//|
//|
//|
//---------------------------------------------------------------
bool CGdiPlusBitmapResource::Load(UINT id, UINT type, HMODULE hInst)
{
	return Load(MAKEINTRESOURCE(id), MAKEINTRESOURCE(type), hInst); 
}
//--------------------------------------------------------------
//|
//|��ü�� ����(
//|
//---------------------------------------------------------------
void CGdiPlusBitmapResource::Empty()
{
	CGdiPlusBitmap::Empty();
	if (m_hBuffer)
	{
		::GlobalUnlock(m_hBuffer);
		::GlobalFree(m_hBuffer);
		m_hBuffer = NULL;
	} 
}
//--------------------------------------------------------------
//|
//|���� �ε� �Լ�(���ҽ�)
//|
//---------------------------------------------------------------
bool CGdiPlusBitmapResource::Load(LPCTSTR pName, LPCTSTR pType, HMODULE hInst)
{
	Empty();

	HRSRC hResource = ::FindResource(hInst, pName, pType);
	if (!hResource)
		return false;

	DWORD imageSize = ::SizeofResource(hInst, hResource);
	if (!imageSize)
		return false;

	const void* pResourceData = ::LockResource(::LoadResource(hInst, hResource));
	if (!pResourceData)
		return false;

	m_hBuffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
	if (m_hBuffer)
	{
		void* pBuffer = ::GlobalLock(m_hBuffer);
		if (pBuffer)
		{
			CopyMemory(pBuffer, pResourceData, imageSize);

			IStream* pStream = NULL;
			if (::CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
			{
				m_pBitmap = Gdiplus::Bitmap::FromStream(pStream);
				pStream->Release();
				if (m_pBitmap)
				{ 
					if (m_pBitmap->GetLastStatus() == Gdiplus::Ok)
						return true;

					delete m_pBitmap;
					m_pBitmap = NULL;
				}
			}
			::GlobalUnlock(m_hBuffer);
		}
		::GlobalFree(m_hBuffer);
		m_hBuffer = NULL;
	}
	return false;
}
//--------------------------------------------------------------
//|
//|��Ʈ���� �ѱ��
//|
//---------------------------------------------------------------
CBitmap CGdiPlusBitmapResource::GetWinBitmap()
{
	HBITMAP bit=NULL;
	m_pBitmap->GetHBITMAP(RGB(0,0,0),&bit);
	return bit;
}

// BLENDFUNCTION bf;
// bf.BlendOp = AC_SRC_OVER;
// bf.BlendFlags =0;
// bf.SourceConstantAlpha = 150;   // 0: ����, 255: ������
// bf.AlphaFormat=0;
// 
// 
// dc.AlphaBlend(bmpInfo.bmWidth*2, 20,
// 			  bmpInfo.bmWidth, bmpInfo.bmHeight,
// 			  &MemDC,
// 			  0,0,
// 			  bmpInfo.bmWidth, bmpInfo.bmHeight,
// 			  bf);


// void CBmpOutDemoView::OnPaint()
// {
// 	CPaintDC dc(this); // device context for painting
// 
// 	CDC MemDC;
// 	BITMAP bmpInfo;
// 	MemDC.CreateCompatibleDC(&dc);
// 
// 	CBitmap bmp;
// 	CBitmap* pOldBmp = NULL;
// 	bmp.LoadBitmapW(IDB_BITMAP1);
// 
// 	bmp.GetBitmap(&bmpInfo);
// 	pOldBmp = MemDC.SelectObject(&bmp);
// 
// 
// 
// 	dc.StretchBlt(20, 20,
// 		bmpInfo.bmWidth*2, bmpInfo.bmHeight*2,
// 		&MemDC,
// 		0, 0,
// 		bmpInfo.bmWidth, bmpInfo.bmHeight,
// 		SRCCOPY); // ������ ���� ��
// 
// 
// 
// 	dc.TransparentBlt(bmpInfo.bmWidth*2, 20,
// 		bmpInfo.bmWidth*2, bmpInfo.bmHeight*2,
// 		&MemDC,
// 		0, 0,
// 		bmpInfo.bmWidth, bmpInfo.bmHeight,
// 		RGB(2,2,0)); //���� ó���� ������ RGB��
// 
// 
// 
// 	MemDC.SelectObject(pOldBmp);
// 
// }

