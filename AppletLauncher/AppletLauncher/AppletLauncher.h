
// AppletLauncher.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CAppletLauncherApp:
// � ���������� ������� ������ ��. AppletLauncher.cpp
//

class CAppletLauncherApp : public CWinApp
{
public:
	CAppletLauncherApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CAppletLauncherApp theApp;