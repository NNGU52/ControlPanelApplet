
// AppletLauncherDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "AppletLauncher.h"
#include "AppletLauncherDlg.h"
#include "afxdialogex.h"

#include <Cpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CAppletLauncherDlg



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


// обработчики сообщений CAppletLauncherDlg

BOOL CAppletLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CAppletLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
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

	if (cplModule.hmModule) cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_EXIT, 0, 0);			// послать сигнал завершения, если ранее уже открывали
	FreeLibrary(cplModule.hmModule);															// освобождение ранее открытой библиотеки

	CString libPath;
	inPath.GetWindowText(libPath);
	HMODULE lib = LoadLibrary(libPath);															// открытие библиотеки
	if (!lib) { MessageBox(L"Ошибка при открытии библиотеки.", L"Внимание!", MB_ICONERROR); return; }

	CPlApplet address = (CPlApplet)GetProcAddress(lib, "CPlApplet");							// получение адреса функции в библиотеке
	if (!address) { MessageBox(L"Функция CPlApplet в библиотеке " + libPath + " не найдена.", L"Внимание!", MB_ICONERROR); return; }

	cplModule.hmModule = lib;
	cplModule.CPlAppletAddress = address;

	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_INIT, 0, 0)) { MessageBox(L"Ошибка при инициализации апплета.", L"Внимание!", MB_ICONERROR); return; }						// проверка работоспособности апплета
	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_GETCOUNT, 0, 0))	{ MessageBox(L"В указанной библиотеке апплеты не найдены.", L"Внимание!", MB_ICONERROR); return; }			// проверка наличия апплетов путём запроса их количества

	DWORD itemsCount = cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_GETCOUNT, 0, 0);			// количество апплетов в библиотеке
	lpCplInfo = new CPLINFO[itemsCount];														// куда будем сохранять информацию об апплете

	if (!cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&lpCplInfo[0])) { MessageBox(L"Ошибка при чтении свойств.", L"Внимание!", MB_ICONERROR); return; }	// получение информации (свойств)
	
	// чтение информации
	WCHAR str[1024];
	if (!LoadString(cplModule.hmModule, lpCplInfo[0].idName, str, 1024)) { MessageBox(L"Ошибка чтения имени.", L"Внимание!", MB_ICONERROR); return; }
	else appletName.SetWindowText(str);
	if (!LoadString(cplModule.hmModule, lpCplInfo[0].idInfo, str, 1024)) { MessageBox(L"Ошибка чтения описания.", L"Внимание!", MB_ICONERROR); return; }
	else appletDescription.SetWindowText(str);
	if (!(a_hIcon = LoadIcon(cplModule.hmModule, MAKEINTRESOURCE(lpCplInfo[0].idIcon)))) { MessageBox(L"Ошибка чтения иконки.", L"Внимание!", MB_ICONERROR); return; }
	else
	{
		appletIcon.SetIcon(a_hIcon);															// рисование иконки в Picture Control
	}

	delete[] lpCplInfo;
}

void CAppletLauncherDlg::OnBnClickedButtonStart()
{
	cplModule.CPlAppletAddress(GetSafeHwnd(), CPL_DBLCLK, 0, 0);
}
