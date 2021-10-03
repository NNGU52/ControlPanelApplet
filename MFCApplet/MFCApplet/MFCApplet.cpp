// MFCApplet.cpp: определяет процедуры инициализации для DLL.
//

#include "stdafx.h"
#include "MFCApplet.h"

#include "AppletDialog.h"
#include "resource.h"
#include <Cpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		он должен быть первым оператором 
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CMFCAppletApp

BEGIN_MESSAGE_MAP(CMFCAppletApp, CWinApp)
END_MESSAGE_MAP()


// создание CMFCAppletApp

CMFCAppletApp::CMFCAppletApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMFCAppletApp

CMFCAppletApp theApp;


// инициализация CMFCAppletApp

BOOL CMFCAppletApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


LONG WINAPI CPlApplet(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPCPLINFO lpCPlInfo;
	LONG retCode = 0;

	switch (msg)
	{
		case CPL_INIT:
		{
			return TRUE;									// успешная инициализация (в соответствии со стандартом Microsoft - положено возвращать TRUE)
		}

		case CPL_GETCOUNT:
		{
			return 1L;										// количество апплетовв данной библиотеке (LONG)
		}

		case CPL_INQUIRE:
		{
			lpCPlInfo = (LPCPLINFO)lParam2;					// сюда запишем информацию об апплете
			lpCPlInfo->idIcon = IDI_ICON2;
			lpCPlInfo->idInfo = IDS_APPLET_DESCRIPTION;
			lpCPlInfo->idName = IDS_APPLET_NAME;
			lpCPlInfo->lData = 0L;
			return 1;										// возврат единицы указывает вызывающему на успешное выполнение
		}

		case CPL_DBLCLK:
		{
			AppletDialog dlg;								// класс окна
			dlg.DoModal();									// открытие окна
			break;
		}
	}

	return retCode;

}