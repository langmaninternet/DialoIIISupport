
// DialoIIISupportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DialoIIISupport.h"
#include "DialoIIISupportDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct DialoIIISupportConfig
{
	int		leftMouseTime;
	int		rightMouseTime;
	int		skillSlot01Time;
	int		skillSlot02Time;
	int		skillSlot03Time;
	int		skillSlot04Time;
	int		healingTime;

	int		skill01Enable;
	int		skill02Enable;
	int		skill03Enable;
	int		skill04Enable;
	int		healingEnable;

	int		autoSpaceEnable;
};
DialoIIISupportConfig d3Config;
wchar_t savePath[3000] = { 0 };
void ValidateD3Config(void)
{
	d3Config.leftMouseTime = int(round(d3Config.leftMouseTime / 100.0) * 100);
	d3Config.rightMouseTime = int(round(d3Config.rightMouseTime / 100.0) * 100);
	d3Config.skillSlot01Time = int(round(d3Config.skillSlot01Time / 100.0) * 100);
	d3Config.skillSlot02Time = int(round(d3Config.skillSlot02Time / 100.0) * 100);
	d3Config.skillSlot03Time = int(round(d3Config.skillSlot03Time / 100.0) * 100);
	d3Config.skillSlot04Time = int(round(d3Config.skillSlot04Time / 100.0) * 100);
	d3Config.healingTime = int(round(d3Config.healingTime / 100.0) * 100);
	if (d3Config.leftMouseTime < 100) d3Config.leftMouseTime = 100;
	if (d3Config.rightMouseTime < 100) d3Config.rightMouseTime = 100;
	if (d3Config.skillSlot01Time < 100) d3Config.skillSlot01Time = 100;
	if (d3Config.skillSlot02Time < 100) d3Config.skillSlot02Time = 100;
	if (d3Config.skillSlot03Time < 100) d3Config.skillSlot03Time = 100;
	if (d3Config.skillSlot04Time < 100) d3Config.skillSlot04Time = 100;
	if (d3Config.healingTime < 100) d3Config.healingTime = 100;
	if (d3Config.skill01Enable != 0) d3Config.skill01Enable = 1;
	if (d3Config.skill02Enable != 0) d3Config.skill02Enable = 1;
	if (d3Config.skill03Enable != 0) d3Config.skill03Enable = 1;
	if (d3Config.skill04Enable != 0) d3Config.skill04Enable = 1;
	if (d3Config.healingEnable != 0) d3Config.healingEnable = 1;
	if (d3Config.autoSpaceEnable != 0) d3Config.autoSpaceEnable = 1;
}
const int	timerDelay = 100/*ms*/;
bool		flagOnF1 = false;
bool		flagOnF2 = false;
bool		flagOnF3 = false;
int			leftMouseCooldown;
int			rightMouseCooldown;
int			skillSlot01Cooldown;
int			skillSlot02Cooldown;
int			skillSlot03Cooldown;
int			skillSlot04Cooldown;
int			healingCooldown;

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include <Windows.h>
bool		IsD3WindowActive(void)
{
	HWND		currentHWD = GetForegroundWindow();
	if (currentHWD)
	{
		wchar_t		buffer[1024] = { 0 };
		GetWindowTextW(currentHWD, buffer, 1023);
		if (wcscmp(buffer, L"Diablo III") == 0)
		{
			return true;
		}
	}
	return false;
}
HWND		GetD3Windows(void)
{
	return FindWindowW(L"D3 Main Window Class", L"Diablo III");
}
void		SendD3Key(int keyCode)
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		SendMessage(d3Wnd, WM_KEYDOWN, keyCode, 0);
		Sleep(5);
		SendMessage(d3Wnd, WM_KEYUP, keyCode, 0);
		Sleep(5);
	}
}
void		SendD3LeftMouseClick()
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		SendMessage(d3Wnd, WM_LBUTTONDOWN, 0, 0);
		Sleep(5);
		SendMessage(d3Wnd, WM_LBUTTONUP, 0, 0);
		Sleep(5);
	}
}
void		SendD3RightMouseClick()
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		SendMessage(d3Wnd, WM_RBUTTONDOWN, 0, 0);
		Sleep(5);
		SendMessage(d3Wnd, WM_RBUTTONUP, 0, 0);
		Sleep(5);
	}
}
bool		PointInRect(POINT point, int rLeft, int rRight, int rTop, int rBottom)
{
	if (rLeft >= rRight || rTop >= rBottom)
	{
		MessageBox(0, L"D3 Engine Error!!", L"(rLeft <= rRight || rTop <= rBottom)", MB_OK);
	}
	return (point.x > rLeft && point.x < rRight && point.y > rTop && point.y < rBottom);
}
bool		ValidToSendD3Click(void)
{
	if (IsD3WindowActive())
	{
		HWND d3Wnd = GetD3Windows();
		if (d3Wnd)
		{
			RECT d3Rect = { 0 };
			GetWindowRect(d3Wnd, &d3Rect);
			if (d3Rect.right > d3Rect.left && d3Rect.bottom > d3Rect.top)
			{
				POINT point = { 0 };
				GetCursorPos(&point);
				if (PointInRect(point, d3Rect.left, d3Rect.right, d3Rect.top, d3Rect.bottom))
				{
					if (d3Rect.right - d3Rect.left == 1920 && d3Rect.bottom - d3Rect.top == 1080)
					{
						//chat button
						if (PointInRect(point, d3Rect.left + 10, d3Rect.left + 80, d3Rect.top + 980, d3Rect.top + 1044))
						{
							return false;
						}

						//Skill Inventory,...
						if (PointInRect(point, d3Rect.left + 1089, d3Rect.left + 1284, d3Rect.top + 995, d3Rect.top + 1062))
						{
							return false;
						}

						//Friend
						if (PointInRect(point, d3Rect.left + 1764, d3Rect.left + 1904, d3Rect.top + 979, d3Rect.top + 1044))
						{
							return false;
						}

						//Small chat box
						if (PointInRect(point, d3Rect.left + 32, d3Rect.left + 346, d3Rect.top + 738, d3Rect.top + 877))
						{
							return false;
						}

						//Objectives Object
						if (PointInRect(point, d3Rect.left + 1862, d3Rect.left + 1893, d3Rect.top + 367, d3Rect.top + 391))
						{
							return false;
						}

						//Player
						if (PointInRect(point, d3Rect.left + 28, d3Rect.left + 93, d3Rect.top + 47, d3Rect.top + 149))
						{
							return false;
						}


					}
					return true;
				}
			}
		}
	}
	return false;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#pragma data_seg(".shared")
HHOOK hGlobalHook;
#pragma data_seg()
extern "C" __declspec(dllexport) LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0 && nCode == HC_ACTION && wParam == WM_KEYDOWN)
	{
		LPKBDLLHOOKSTRUCT a = (LPKBDLLHOOKSTRUCT)(void*)lParam;
		switch (a->vkCode)
		{
		case VK_F1:
			flagOnF1 = !flagOnF1;
			break;
		case VK_F2:
			flagOnF2 = !flagOnF2;
			break;
		case VK_F3:
			flagOnF3 = !flagOnF3;
			break;
		}
	}
	return CallNextHookEx(hGlobalHook, nCode, wParam, lParam);
}







// CDialoIIISupportDlg dialog
CDialoIIISupportDlg::CDialoIIISupportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOIIISUPPORT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialoIIISupportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialoIIISupportDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_LEFTMOUSETIME, &CDialoIIISupportDlg::OnKillfocusLeftmousetime)
	ON_EN_KILLFOCUS(IDC_RIGHTMOUSETIME, &CDialoIIISupportDlg::OnKillfocusRightmousetime)
	ON_EN_KILLFOCUS(IDC_SKILL01TIME, &CDialoIIISupportDlg::OnKillfocusSkill01time)
	ON_EN_KILLFOCUS(IDC_SKILL02TIME, &CDialoIIISupportDlg::OnKillfocusSkill02time)
	ON_EN_KILLFOCUS(IDC_SKILL03TIME, &CDialoIIISupportDlg::OnKillfocusSkill03time)
	ON_EN_KILLFOCUS(IDC_SKILL04TIME, &CDialoIIISupportDlg::OnKillfocusSkill04time)
	ON_EN_KILLFOCUS(IDC_HEALINGTIME, &CDialoIIISupportDlg::OnKillfocusHealingtime)
	ON_BN_CLICKED(IDC_SKILL01CHECK, &CDialoIIISupportDlg::OnClickedSkill01check)
	ON_BN_CLICKED(IDC_SKILL02CHECK, &CDialoIIISupportDlg::OnClickedSkill02check)
	ON_BN_CLICKED(IDC_SKILL03CHECK, &CDialoIIISupportDlg::OnClickedSkill03check)
	ON_BN_CLICKED(IDC_SKILL04CHECK, &CDialoIIISupportDlg::OnClickedSkill04check)
	ON_BN_CLICKED(IDC_HEALINGCHECK, &CDialoIIISupportDlg::OnClickedHealingcheck)
	ON_BN_CLICKED(IDC_SPACECHECK, &CDialoIIISupportDlg::OnClickedSpacecheck)
END_MESSAGE_MAP()


// CDialoIIISupportDlg message handlers




BOOL CDialoIIISupportDlg::OnInitDialog()
{
	// Create mutex
	HANDLE hMutex = CreateMutex(NULL, TRUE, L"Diablo III Support");
	switch (GetLastError())
	{
	case ERROR_SUCCESS:
		// Mutex created successfully. There is 
		// no instances running
		break;

	case ERROR_ALREADY_EXISTS:
		// Mutex already exists so there is a 
		// running instance of our app.
		hMutex = NULL;
		exit(EXIT_SUCCESS);
		break;

	default:
		// Failed to create mutex by unknown reason
		break;
	}






	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	myTimerID = CDialogEx::SetTimer(1, timerDelay, NULL);

	if (savePath[0] == 0)
	{
		wchar_t appdataPath[2000] = { 0 };
		GetEnvironmentVariable(L"AppData", appdataPath, 1999);
		wchar_t bufferDir[2000] = { 0 };
		swprintf_s(bufferDir, L"%ls\\DialoIIISupport\\", appdataPath);
		CreateDirectoryW(bufferDir, 0);
		swprintf_s(savePath, L"%ls\\DialoIIISupport\\DialoIIISupport.dat", appdataPath);
	}
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeRead))
	{
		saveFile.Read(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	ValidateD3Config();
	wchar_t buffer[1000] = { 0 };

	swprintf_s(buffer, L"%d", d3Config.leftMouseTime);
	GetDlgItem(IDC_LEFTMOUSETIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.rightMouseTime);
	GetDlgItem(IDC_RIGHTMOUSETIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.skillSlot01Time);
	GetDlgItem(IDC_SKILL01TIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.skillSlot02Time);
	GetDlgItem(IDC_SKILL02TIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.skillSlot03Time);
	GetDlgItem(IDC_SKILL03TIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.skillSlot04Time);
	GetDlgItem(IDC_SKILL04TIME)->SetWindowText(buffer);

	swprintf_s(buffer, L"%d", d3Config.healingTime);
	GetDlgItem(IDC_HEALINGTIME)->SetWindowText(buffer);

	GetDlgItem(IDC_SKILL01TIME)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TIME)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TIME)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TIME)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_HEALINGTIME)->EnableWindow(d3Config.healingEnable);
	GetDlgItem(IDC_SKILL01TEXT)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TEXT)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TEXT)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TEXT)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_HEALINGTEXT)->EnableWindow(d3Config.healingEnable);
	GetDlgItem(IDC_SKILL01TEXTMS)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TEXTMS)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TEXTMS)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TEXTMS)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_HEALINGTEXTMS)->EnableWindow(d3Config.healingEnable);


	((CButton*)GetDlgItem(IDC_SKILL01CHECK))->SetCheck(d3Config.skill01Enable);
	((CButton*)GetDlgItem(IDC_SKILL02CHECK))->SetCheck(d3Config.skill02Enable);
	((CButton*)GetDlgItem(IDC_SKILL03CHECK))->SetCheck(d3Config.skill03Enable);
	((CButton*)GetDlgItem(IDC_SKILL04CHECK))->SetCheck(d3Config.skill04Enable);
	((CButton*)GetDlgItem(IDC_HEALINGCHECK))->SetCheck(d3Config.healingEnable);
	((CButton*)GetDlgItem(IDC_SPACECHECK))->SetCheck(d3Config.healingEnable);


	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);


	hGlobalHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, GetModuleHandle(NULL), 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}




// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDialoIIISupportDlg::OnPaint()
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
HCURSOR CDialoIIISupportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDialoIIISupportDlg::WinHelp(DWORD dwData, UINT nCmd)
{//prevent help to use F1 

}




















void CDialoIIISupportDlg::OnTimer(UINT_PTR nIdEvent)
{
	if (myTimerID == nIdEvent)
	{
		const WCHAR * bufferActive = L"Found";
		HWND d3Window = GetD3Windows();
		RECT d3Rect = { 0 };
		if (d3Window == 0)
		{
			bufferActive = L"";
		}
		POINT point = { 0 };
		GetCursorPos(&point);
		const WCHAR * validToClick = L"";
		if (ValidToSendD3Click())  validToClick = L"Vaild to click";
		CString debugInfo;
		debugInfo.AppendFormat(L"Diablo III: %ls\r\n	X: %d\r\n	Y: %d\r\n	W: %d\r\n	H: %d\r\nCursor: %ls\r\n	X : %d\r\n	Y : %d\r\n",
			bufferActive,
			d3Rect.left,
			d3Rect.top,
			d3Rect.right - d3Rect.left,
			d3Rect.bottom - d3Rect.top,
			validToClick,
			point.x,
			point.y
		);
		GetDlgItem(IDC_DEBUGINFO)->SetWindowTextW(debugInfo);
		if (flagOnF2)
		{
			GetDlgItem(IDC_SKILL01TIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL02TIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL03TIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL04TIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEALINGTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL01CHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL02CHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL03CHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_SKILL04CHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEALINGCHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_SPACECHECK)->EnableWindow(FALSE);
			GetDlgItem(IDC_F2BIGFRAME)->SetWindowTextW(L"Skill (Hotkey F2) - Running");
			if (d3Window != 0)
			{
				bool flagSendSpace = false;
				if (d3Config.skill01Enable)
				{
					skillSlot01Cooldown += timerDelay;
					if (skillSlot01Cooldown >= d3Config.skillSlot01Time)
					{
						if (flagSendSpace)
						{
							SendD3Key(VK_SPACE);
							flagSendSpace = false;
						}
						SendD3Key(0x31);
						skillSlot01Cooldown = 0;
					}
				}
				if (d3Config.skill02Enable)
				{
					skillSlot02Cooldown += timerDelay;
					if (skillSlot02Cooldown >= d3Config.skillSlot02Time)
					{
						if (flagSendSpace)
						{
							SendD3Key(VK_SPACE);
							flagSendSpace = false;
						}
						SendD3Key(0x32);
						skillSlot02Cooldown = 0;
					}
				}
				if (d3Config.skill03Enable)
				{
					skillSlot03Cooldown += timerDelay;
					if (skillSlot03Cooldown >= d3Config.skillSlot03Time)
					{
						if (flagSendSpace)
						{
							SendD3Key(VK_SPACE);
							flagSendSpace = false;
						}
						SendD3Key(0x33);
						skillSlot03Cooldown = 0;
					}
				}
				if (d3Config.skill04Enable)
				{
					skillSlot04Cooldown += timerDelay;
					if (skillSlot04Cooldown >= d3Config.skillSlot04Time)
					{
						if (flagSendSpace)
						{
							SendD3Key(VK_SPACE);
							flagSendSpace = false;
						}
						SendD3Key(0x34);
						skillSlot04Cooldown = 0;
					}
				}
				if (d3Config.healingEnable)
				{
					healingCooldown += timerDelay;
					if (healingCooldown >= d3Config.skillSlot04Time)
					{
						if (flagSendSpace)
						{
							SendD3Key(VK_SPACE);
							flagSendSpace = false;
						}
						SendD3Key(0x51);
						healingCooldown = 0;
					}
				}
			}
		}
		else
		{
			if (d3Config.skill01Enable) GetDlgItem(IDC_SKILL01TIME)->EnableWindow(TRUE);
			if (d3Config.skill02Enable) GetDlgItem(IDC_SKILL02TIME)->EnableWindow(TRUE);
			if (d3Config.skill03Enable) GetDlgItem(IDC_SKILL03TIME)->EnableWindow(TRUE);
			if (d3Config.skill04Enable) GetDlgItem(IDC_SKILL04TIME)->EnableWindow(TRUE);
			if (d3Config.healingEnable) GetDlgItem(IDC_HEALINGTIME)->EnableWindow(TRUE);
			GetDlgItem(IDC_SKILL01CHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_SKILL02CHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_SKILL03CHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_SKILL04CHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEALINGCHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_SPACECHECK)->EnableWindow(TRUE);
			GetDlgItem(IDC_F2BIGFRAME)->SetWindowTextW(L"Skill (Hotkey F2)");
		}
		if (flagOnF1)
		{
			GetDlgItem(IDC_LEFTMOUSETEXT)->SetWindowText(L"Left mouse (Hotkey F1): \r\n	Running");
			GetDlgItem(IDC_LEFTMOUSETEXT)->EnableWindow(FALSE);
			GetDlgItem(IDC_LEFTMOUSETEXTMS)->EnableWindow(FALSE);
			GetDlgItem(IDC_LEFTMOUSETIME)->EnableWindow(FALSE);
			if (d3Window != 0)
			{
				leftMouseCooldown += timerDelay;
				if (leftMouseCooldown >= d3Config.leftMouseTime)
				{
					if (ValidToSendD3Click()) SendD3LeftMouseClick();
					leftMouseCooldown = 0;
				}
			}
		}
		else
		{
			GetDlgItem(IDC_LEFTMOUSETEXT)->SetWindowText(L"Left mouse (Hotkey F1): ");
			GetDlgItem(IDC_LEFTMOUSETEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_LEFTMOUSETEXTMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_LEFTMOUSETIME)->EnableWindow(TRUE);
		}



		if (flagOnF3)
		{
			GetDlgItem(IDC_RIGHTMOUSETEXT)->SetWindowText(L"Right Mouse (Hotkey F2): \r\n	Running");
			GetDlgItem(IDC_RIGHTMOUSETEXT)->EnableWindow(FALSE);
			GetDlgItem(IDC_RIGHTMOUSETEXTMS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RIGHTMOUSETIME)->EnableWindow(FALSE);
			if (d3Window != 0)
			{
				rightMouseCooldown += timerDelay;
				if (rightMouseCooldown >= d3Config.leftMouseTime)
				{
					if (ValidToSendD3Click()) SendD3RightMouseClick();
					rightMouseCooldown = 0;
				}
			}
		}
		else
		{
			GetDlgItem(IDC_RIGHTMOUSETEXT)->SetWindowText(L"Right Mouse (Hotkey F2): ");
			GetDlgItem(IDC_RIGHTMOUSETEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_RIGHTMOUSETEXTMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_RIGHTMOUSETIME)->EnableWindow(TRUE);
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusLeftmousetime()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_LEFTMOUSETIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_LEFTMOUSETIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.leftMouseTime)
	{
		d3Config.leftMouseTime = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusRightmousetime()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_RIGHTMOUSETIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_RIGHTMOUSETIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.rightMouseTime)
	{
		d3Config.rightMouseTime = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusSkill01time()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_SKILL01TIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL01TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot01Time)
	{
		d3Config.skillSlot01Time = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusSkill02time()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_SKILL02TIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL02TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot02Time)
	{
		d3Config.skillSlot02Time = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusSkill03time()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_SKILL03TIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL03TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot03Time)
	{
		d3Config.skillSlot03Time = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusSkill04time()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_SKILL04TIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL04TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot04Time)
	{
		d3Config.skillSlot04Time = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusHealingtime()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_HEALINGTIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 100.0) * 100);
	if (newValue < 100) newValue = 100;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_HEALINGTIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.healingTime)
	{
		d3Config.healingTime = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnClickedSkill01check()
{
	d3Config.skill01Enable = !d3Config.skill01Enable;
	((CButton*)GetDlgItem(IDC_SKILL01CHECK))->SetCheck(d3Config.skill01Enable);// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SKILL01TIME)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL01TEXT)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL01TEXTMS)->EnableWindow(d3Config.skill01Enable);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}
void CDialoIIISupportDlg::OnClickedSkill02check()
{
	d3Config.skill02Enable = !d3Config.skill02Enable;
	((CButton*)GetDlgItem(IDC_SKILL02CHECK))->SetCheck(d3Config.skill02Enable);// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SKILL02TIME)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL02TEXT)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL02TEXTMS)->EnableWindow(d3Config.skill02Enable);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}
void CDialoIIISupportDlg::OnClickedSkill03check()
{
	d3Config.skill03Enable = !d3Config.skill03Enable;
	((CButton*)GetDlgItem(IDC_SKILL03CHECK))->SetCheck(d3Config.skill03Enable);// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SKILL03TIME)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL03TEXT)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL03TEXTMS)->EnableWindow(d3Config.skill03Enable);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}
void CDialoIIISupportDlg::OnClickedSkill04check()
{
	d3Config.skill04Enable = !d3Config.skill04Enable;
	((CButton*)GetDlgItem(IDC_SKILL04CHECK))->SetCheck(d3Config.skill04Enable);// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SKILL04TIME)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL04TEXT)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL04TEXTMS)->EnableWindow(d3Config.skill04Enable);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}
void CDialoIIISupportDlg::OnClickedHealingcheck()
{
	d3Config.healingEnable = !d3Config.healingEnable;
	((CButton*)GetDlgItem(IDC_HEALINGCHECK))->SetCheck(d3Config.healingEnable);// TODO: Add your control notification handler code here
	GetDlgItem(IDC_HEALINGTIME)->EnableWindow(d3Config.healingEnable);
	GetDlgItem(IDC_HEALINGTEXT)->EnableWindow(d3Config.healingEnable);
	GetDlgItem(IDC_HEALINGTEXTMS)->EnableWindow(d3Config.healingEnable);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}
void CDialoIIISupportDlg::OnClickedSpacecheck()
{
	d3Config.autoSpaceEnable = !d3Config.autoSpaceEnable;
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
	GetDlgItem(IDC_F2BIGFRAME)->EnableWindow(d3Config.skill01Enable != 0
		|| d3Config.skill02Enable != 0
		|| d3Config.skill03Enable != 0
		|| d3Config.skill04Enable != 0
		|| d3Config.healingEnable != 0
		|| d3Config.autoSpaceEnable != 0
	);
}

