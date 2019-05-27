
// StarPactKeyGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StarPactKeyGen.h"
#include "StarPactKeyGenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStarPactKeyGenDlg dialog



CStarPactKeyGenDlg::CStarPactKeyGenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARPACTKEYGEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStarPactKeyGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStarPactKeyGenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_DeviceID, &CStarPactKeyGenDlg::OnChangeDeviceid)
END_MESSAGE_MAP()


// CStarPactKeyGenDlg message handlers

BOOL CStarPactKeyGenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStarPactKeyGenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStarPactKeyGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void GenLicenseString(const wchar_t * deviceID, wchar_t * bufferLicenseID, int bufferLicenseSize);
void CStarPactKeyGenDlg::OnChangeDeviceid()
{
	wchar_t bufferDeviceID[1000] = { 0 };
	GetDlgItem(IDC_DeviceID)->GetWindowTextW(bufferDeviceID, 999);

	wchar_t bufferLicense[1000] = { 0 };
	GenLicenseString(bufferDeviceID, bufferLicense, 999);

	wchar_t emailLicense[100000] = { 0 };
	swprintf_s(emailLicense, L"Dear you\r\n\r\nYour DeviceID is %ls and Activation Key is %ls\r\n\r\nTo active :\r\n+ Put your Activation Key to Force Stand text box, and click to other text box. \r\n+ Restart app and you got access to StarPact Feature.\r\n\r\nNote : Firebird in Development\r\n\r\nHave a nice day!\r\n", bufferDeviceID, bufferLicense);

	GetDlgItem(IDC_ActivationKey)->SetWindowTextW(emailLicense);
}

void CStarPactKeyGenDlg::OnOK()
{

}

