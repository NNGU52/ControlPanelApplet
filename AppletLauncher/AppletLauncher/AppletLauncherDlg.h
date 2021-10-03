
// AppletLauncherDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"

#include <Cpl.h>


// Прототип глобальной функции CPlApplet
typedef LONG(WINAPI* CPlApplet) (HWND, UINT, LPARAM, LPARAM);

// Структура для упрощения работы с модулем
struct CPLMODULE
{
	HMODULE hmModule;	// Указатель на библиотеку
	CPlApplet CPlAppletAddress;	// Адрес функции в библиотеке
};

// диалоговое окно CAppletLauncherDlg
class CAppletLauncherDlg : public CDialogEx
{
// Создание
public:
	CAppletLauncherDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_APPLETLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	HICON a_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Для работы с модулем
	CPLMODULE cplModule;
	// Для хранения возвращаемых значений CPlApplet
	CPLINFO* lpCplInfo;
	afx_msg void OnBnClickedButtonOpen();
	// Путь до выбранного модуля
	CEdit inPath;
	// Для хранения имени апплета
	CEdit appletName;
	// Для хранения описания апплета
	CEdit appletDescription;
	// Для хранения иконки
	CStatic appletIcon;
	afx_msg void OnBnClickedButtonStart();
};
