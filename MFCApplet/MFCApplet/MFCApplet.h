// MFCApplet.h: главный файл заголовка для DLL MFCApplet
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCAppletApp
// Про реализацию данного класса см. MFCApplet.cpp
//

class CMFCAppletApp : public CWinApp
{
public:
	CMFCAppletApp();

	typedef struct tagMOUSEKEYS {
		UINT  cbSize;
		DWORD dwFlags;
		DWORD iMaxSpeed;
		DWORD iTimeToMaxSpeed;
		DWORD iCtrlSpeed;
		DWORD dwReserved1;
		DWORD dwReserved2;
	} MOUSEKEYS, *LPMOUSEKEYS;

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
