// AppletDialog.cpp: ���� ����������
//

#include "stdafx.h"
#include "MFCApplet.h"
#include "AppletDialog.h"
#include "afxdialogex.h"

#include "resource.h"


// ���������� ���� AppletDialog

IMPLEMENT_DYNAMIC(AppletDialog, CDialog)

AppletDialog::AppletDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AppletDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

BOOL AppletDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	SliderControlSpeed.SetRange(1, 20);				// �������� ��������� ��������� � ������������ � ������������
	SliderControlSpeed.SetTicFreq(1);				// ���

	SliderControlTrails.SetRange(0, 15);
	SliderControlTrails.SetTicFreq(1);

	RefreshParams();								// ���������� ������� ���������� ������� �� �����

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

AppletDialog::~AppletDialog()
{
}

void AppletDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SPEED, SliderControlSpeed);
	DDX_Control(pDX, IDC_SLIDER_TRAILS, SliderControlTrails);
}


BEGIN_MESSAGE_MAP(AppletDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &AppletDialog::OnBnClickedButtonExit)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, &AppletDialog::OnBnClickedButtonDefault)
END_MESSAGE_MAP()


int AppletDialog::GetMouseSpeed()
{
	BOOL fResult;
	int aMouseInfo;

	fResult = SystemParametersInfo(SPI_GETMOUSESPEED,	// Get mouse information
		0,												// Not used
		&aMouseInfo,									// Holds mouse information
		0);												// Not used           

	return aMouseInfo;
}


bool AppletDialog::SetMouseSpeed(int MouseSpeed)
{
	return SystemParametersInfo(SPI_SETMOUSESPEED, 0, (LPVOID)MouseSpeed, SPIF_UPDATEINIFILE || SPIF_SENDCHANGE || SPIF_SENDWININICHANGE);

}


int AppletDialog::GetMouseTrails()
{
	BOOL fResult;
	int aMouseInfo;

	fResult = SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &aMouseInfo, 0);        

	return aMouseInfo;
}


bool AppletDialog::SetMouseTrails(int MouseTrails)
{
	return SystemParametersInfo(SPI_SETMOUSETRAILS, MouseTrails, 0, SPIF_UPDATEINIFILE || SPIF_SENDCHANGE || SPIF_SENDWININICHANGE);

}

// ����������� ��������� AppletDialog


void AppletDialog::OnBnClickedButtonExit()
{
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


void AppletDialog::OnBnClickedButtonDefault()
{
	SetMouseSpeed(10);
	SetMouseTrails(0);
	RefreshParams();
}


void AppletDialog::RefreshParams()
{
	CString cstr;
	int i;

	i = GetMouseSpeed();
	cstr.Format(L"�������� ����������� ������� (%d)", i);
	this->SetDlgItemText(IDC_STATIC, cstr);
	SliderControlSpeed.SetPos(i);

	i = GetMouseTrails();
	cstr.Format(L"����� ����� ������� (%d)",i);
	this->SetDlgItemText(IDC_STATIC1, cstr);
	SliderControlTrails.SetPos(i);
}


// ��� ��������� ��������� "��������"
void AppletDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (*pScrollBar == SliderControlSpeed)				// ���� ������� ��������� ��� ������� SliderControl
	{
		SetMouseSpeed(SliderControlSpeed.GetPos());
		RefreshParams();
	}
	if (*pScrollBar == SliderControlTrails)
	{
		SetMouseTrails(SliderControlTrails.GetPos());
		RefreshParams();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);		// �������� ���������� ������������� ������
}