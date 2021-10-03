
// AppletLauncherDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "AppletLauncher.h"
#include "AppletLauncherDlg.h"
#include "afxdialogex.h"

#include <Cpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAppletLauncherDlg



CAppletLauncherDlg::CAppletLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppletLauncherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppletLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, inPath);
	DDX_Control(pDX, IDC_EDIT_NAME, appletName);
	DDX_Control(pDX, IDC_EDIT3, appletDescription);
	DDX_Control(pDX, IDC_STATIC_ICON, appletIcon);
}

BEGIN_MESSAGE_MAP(CAppletLauncherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CAppletLauncherDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_START, &CAppletLauncherDlg::OnBnClickedButtonStart)
//	ON_BN_CLICKED(IDC_BUTTON_START2, &CAppletLauncherDlg::OnBnClickedButtonStart2)
END_MESSAGE_MAP()


// ����������� ��������� CAppletLauncherDlg

BOOL CAppletLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CAppletLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CAppletLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAppletLauncherDlg::OnBnClickedButtonOpen()
{
	CFileDialog dlg(TRUE, L"*.cpl", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Applets (*.cpl)|*.cpl||", NULL, 0, TRUE);
	if (dlg.DoModal() == IDOK)
	{
		inPath.SetWindowText(dlg.GetPathName());
	}
	else return;

	if (cplModule.hmModule) cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_EXIT, 0, 0);			// ������� ������ ����������, ���� ����� ��� ���������
	FreeLibrary(cplModule.hmModule);															// ������������ ����� �������� ����������

	CString libPath;
	inPath.GetWindowText(libPath);
	HMODULE lib = LoadLibrary(libPath);															// �������� ����������
	if (!lib) { MessageBox(L"������ ��� �������� ����������.", L"��������!", MB_ICONERROR); return; }

	CPlApplet address = (CPlApplet)GetProcAddress(lib, "CPlApplet");							// ��������� ������ ������� � ����������
	if (!address) { MessageBox(L"������� CPlApplet � ���������� " + libPath + " �� �������.", L"��������!", MB_ICONERROR); return; }

	cplModule.hmModule = lib;
	cplModule.CPlAppletAddress = address;

	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_INIT, 0, 0)) { MessageBox(L"������ ��� ������������� �������.", L"��������!", MB_ICONERROR); return; }						// �������� ����������������� �������
	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_GETCOUNT, 0, 0))	{ MessageBox(L"� ��������� ���������� ������� �� �������.", L"��������!", MB_ICONERROR); return; }			// �������� ������� �������� ���� ������� �� ����������

	DWORD itemsCount = cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_GETCOUNT, 0, 0);			// ���������� �������� � ����������
	lpCplInfo = new CPLINFO[itemsCount];														// ���� ����� ��������� ���������� �� �������

	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&lpCplInfo[0])) { MessageBox(L"������ ��� ������ �������.", L"��������!", MB_ICONERROR); return; }	// ��������� ���������� (�������)
	
	// ������ ����������
	WCHAR str[1024];
	if (!LoadString(cplModule.hmModule, lpCplInfo[0].idName, str, 1024)) { MessageBox(L"������ ������ �����.", L"��������!", MB_ICONERROR); return; }
	else appletName.SetWindowText(str);
	if (!LoadString(cplModule.hmModule, lpCplInfo[0].idInfo, str, 1024)) { MessageBox(L"������ ������ ��������.", L"��������!", MB_ICONERROR); return; }
	else appletDescription.SetWindowText(str);
	if (!(a_hIcon = LoadIcon(cplModule.hmModule, MAKEINTRESOURCE(lpCplInfo[0].idIcon)))) { MessageBox(L"������ ������ ������.", L"��������!", MB_ICONERROR); return; }
	else
	{
		appletIcon.SetIcon(a_hIcon);															// ��������� ������ � Picture Control
	}

	delete[] lpCplInfo;
}

void CAppletLauncherDlg::OnBnClickedButtonStart()
{
	cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_DBLCLK, 0, 0);
}
