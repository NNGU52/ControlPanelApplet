// MFCApplet.h: ������� ���� ��������� ��� DLL MFCApplet
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CMFCAppletApp
// ��� ���������� ������� ������ ��. MFCApplet.cpp
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

// ���������������
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
