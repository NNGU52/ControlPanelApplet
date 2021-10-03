
// AppletLauncherDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"

#include <Cpl.h>


// �������� ���������� ������� CPlApplet
typedef LONG(WINAPI* CPlApplet) (HWND, UINT, LPARAM, LPARAM);

// ��������� ��� ��������� ������ � �������
struct CPLMODULE
{
	HMODULE hmModule;	// ��������� �� ����������
	CPlApplet CPlAppletAddress;	// ����� ������� � ����������
};

// ���������� ���� CAppletLauncherDlg
class CAppletLauncherDlg : public CDialogEx
{
// ��������
public:
	CAppletLauncherDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_APPLETLAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;
	HICON a_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��� ������ � �������
	CPLMODULE cplModule;
	// ��� �������� ������������ �������� CPlApplet
	CPLINFO* lpCplInfo;
	afx_msg void OnBnClickedButtonOpen();
	// ���� �� ���������� ������
	CEdit inPath;
	// ��� �������� ����� �������
	CEdit appletName;
	// ��� �������� �������� �������
	CEdit appletDescription;
	// ��� �������� ������
	CStatic appletIcon;
	afx_msg void OnBnClickedButtonStart();
};
