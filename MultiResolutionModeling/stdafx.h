// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0500

#include <atlbase.h>

//CString 클래스 사용
#include <atlstr.h>
//#define _WTL_NO_WTYPES
#include <atltypes.h>

#include <atlapp.h>

extern CAppModule _Module;

//윈도우 기반의 기본 클래스
#include <atlwin.h>

// MSG_WM_ 메시지를 사용하기 위한 클래스
#include <atlcrack.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlcoll.h>
#include <atlctrlx.h>
#include <atltheme.h>
//COleDateTime 클래스
#include <ATLComTime.h>
#include <atlcom.h>
#include <comdef.h>

#include <stdio.h>
#include <tchar.h>
#include <shlobj.h>

//STL
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//STL CONTAIN
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

#include "resource.h"


//================================
//기본자료형 정의 클래스
#include "BaseValue/BaseValue.h"
//OpenGL 클래스
#include "OpenGL/AtlOpengl.h"

//================================
//이미지 관련 클래스
#include <atlimage.h> //CImage Class 사용
#include "subControl.h"

//================================
#include "CommonResolution/CommonResolution.h"

#include "ImageLoadApi/ImageLoadApi.h"
#include "ExcelAuto/XLAutomation.h"
#include "ExcelAuto/XLEzAutomation.h"
//================================
//에이전트 클래스
#include "GAgt.h"
//로그 출력 클래스
#include "LogDlg.h"
#include "ResolutionProperty/PropertyKind.h"


#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
