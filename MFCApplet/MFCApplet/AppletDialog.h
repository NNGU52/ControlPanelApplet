#pragma once
#include "afxcmn.h"


//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfow

// диалоговое окно AppletDialog

class AppletDialog : public CDialog
{
	DECLARE_DYNAMIC(AppletDialog)

public:
	AppletDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~AppletDialog();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual BOOL OnInitDialog();
	int GetMouseSpeed();
	int GetMouseTrails();
	bool SetMouseSpeed(int MouseSpeed);
	bool SetMouseTrails(int MouseTrails);
	void RefreshParams();
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl SliderControlSpeed;
	CSliderCtrl SliderControlTrails;
	afx_msg void OnBnClickedButtonDefault();
};
