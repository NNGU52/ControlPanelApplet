
// AppletLauncher.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CAppletLauncherApp:
// О реализации данного класса см. AppletLauncher.cpp
//

class CAppletLauncherApp : public CWinApp
{
public:
	CAppletLauncherApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CAppletLauncherApp theApp;