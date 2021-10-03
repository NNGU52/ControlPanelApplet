// MFCApplet.cpp: ���������� ��������� ������������� ��� DLL.
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
//TODO: ���� ��� ���������� DLL ����������� ������� � ������������ DLL MFC,
//		��� �������, ���������������� �� ������ DLL-����������, ������� ��������� ������ �
//		MFC, ������ ��������� ������ AFX_MANAGE_STATE �
//		����� ������ �������.
//
//		��������:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���� ���������� �������
//		}
//
//		�����, ����� ������ ������ ��� ����������� � ������
//		������� �� ������ MFC.  ��� ��������, ���
//		�� ������ ���� ������ ���������� 
//		������� � �������������� ���� ����� ����������� ���������� �������,
//		��������� �� ������������ ����� ��������� ������ � MFC
//		DLL.
//
//		� ����������� ��������� MFC 33 � 58 ���������� �����
//		��������� ��������.
//

// CMFCAppletApp

BEGIN_MESSAGE_MAP(CMFCAppletApp, CWinApp)
END_MESSAGE_MAP()


// �������� CMFCAppletApp

CMFCAppletApp::CMFCAppletApp()
{
	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ CMFCAppletApp

CMFCAppletApp theApp;


// ������������� CMFCAppletApp

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
			return TRUE;									// �������� ������������� (� ������������ �� ���������� Microsoft - �������� ���������� TRUE)
		}

		case CPL_GETCOUNT:
		{
			return 1L;										// ���������� ��������� ������ ���������� (LONG)
		}

		case CPL_INQUIRE:
		{
			lpCPlInfo = (LPCPLINFO)lParam2;					// ���� ������� ���������� �� �������
			lpCPlInfo->idIcon = IDI_ICON2;
			lpCPlInfo->idInfo = IDS_APPLET_DESCRIPTION;
			lpCPlInfo->idName = IDS_APPLET_NAME;
			lpCPlInfo->lData = 0L;
			return 1;										// ������� ������� ��������� ����������� �� �������� ����������
		}

		case CPL_DBLCLK:
		{
			AppletDialog dlg;								// ����� ����
			dlg.DoModal();									// �������� ����
			break;
		}
	}

	return retCode;

}