
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
const int maxProfileNumber = 10;
const int maxProfileNameLength = 15;
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

	int     currentProfile;
	wchar_t profileName[maxProfileNumber + 1][maxProfileNameLength + 1];
	int		profileleftMouseTime[maxProfileNumber + 1];
	int		profilerightMouseTime[maxProfileNumber + 1];
	int		profileskillSlot01Time[maxProfileNumber + 1];
	int		profileskillSlot02Time[maxProfileNumber + 1];
	int		profileskillSlot03Time[maxProfileNumber + 1];
	int		profileskillSlot04Time[maxProfileNumber + 1];
	int		profilehealingTime[maxProfileNumber + 1];
	int		profileskill01Enable[maxProfileNumber + 1];
	int		profileskill02Enable[maxProfileNumber + 1];
	int		profileskill03Enable[maxProfileNumber + 1];
	int		profileskill04Enable[maxProfileNumber + 1];
	int		profilehealingEnable[maxProfileNumber + 1];
	int		profileautoSpaceEnable[maxProfileNumber + 1];


	wchar_t	keySKill01;
	wchar_t	keySKill02;
	wchar_t	keySKill03;
	wchar_t	keySKill04;
	wchar_t	keyHealing;
	wchar_t keySpace;
};
DialoIIISupportConfig d3Config;
wchar_t savePath[3000] = { 0 };
void ValidateD3Config(void)
{
	d3Config.leftMouseTime = int(round(d3Config.leftMouseTime / 50.0) * 50);
	d3Config.rightMouseTime = int(round(d3Config.rightMouseTime / 50.0) * 50);
	d3Config.skillSlot01Time = int(round(d3Config.skillSlot01Time / 50.0) * 50);
	d3Config.skillSlot02Time = int(round(d3Config.skillSlot02Time / 50.0) * 50);
	d3Config.skillSlot03Time = int(round(d3Config.skillSlot03Time / 50.0) * 50);
	d3Config.skillSlot04Time = int(round(d3Config.skillSlot04Time / 50.0) * 50);
	d3Config.healingTime = int(round(d3Config.healingTime / 50.0) * 50);
	if (d3Config.leftMouseTime < 50) d3Config.leftMouseTime = 50;
	if (d3Config.rightMouseTime < 50) d3Config.rightMouseTime = 50;
	if (d3Config.skillSlot01Time < 50) d3Config.skillSlot01Time = 50;
	if (d3Config.skillSlot02Time < 50) d3Config.skillSlot02Time = 50;
	if (d3Config.skillSlot03Time < 50) d3Config.skillSlot03Time = 50;
	if (d3Config.skillSlot04Time < 50) d3Config.skillSlot04Time = 50;
	if (d3Config.healingTime < 50) d3Config.healingTime = 50;
	if (d3Config.skill01Enable != 0) d3Config.skill01Enable = 1;
	if (d3Config.skill02Enable != 0) d3Config.skill02Enable = 1;
	if (d3Config.skill03Enable != 0) d3Config.skill03Enable = 1;
	if (d3Config.skill04Enable != 0) d3Config.skill04Enable = 1;
	if (d3Config.healingEnable != 0) d3Config.healingEnable = 1;
	if (d3Config.autoSpaceEnable != 0) d3Config.autoSpaceEnable = 1;

	if (d3Config.currentProfile < 0 || d3Config.currentProfile >= maxProfileNumber) d3Config.currentProfile = 0;
	for (int iprofile = 0; iprofile < maxProfileNumber; iprofile++)
	{
		if (d3Config.profileName[iprofile][0] == 0)
		{
			swprintf_s(d3Config.profileName[iprofile], L"Profile %02d", iprofile);
		}
		d3Config.profileleftMouseTime[iprofile] = int(round(d3Config.profileleftMouseTime[iprofile] / 50.0) * 50);
		d3Config.profilerightMouseTime[iprofile] = int(round(d3Config.profilerightMouseTime[iprofile] / 50.0) * 50);
		d3Config.profileskillSlot01Time[iprofile] = int(round(d3Config.profileskillSlot01Time[iprofile] / 50.0) * 50);
		d3Config.profileskillSlot02Time[iprofile] = int(round(d3Config.profileskillSlot02Time[iprofile] / 50.0) * 50);
		d3Config.profileskillSlot03Time[iprofile] = int(round(d3Config.profileskillSlot03Time[iprofile] / 50.0) * 50);
		d3Config.profileskillSlot04Time[iprofile] = int(round(d3Config.profileskillSlot04Time[iprofile] / 50.0) * 50);
		d3Config.profilehealingTime[iprofile] = int(round(d3Config.profilehealingTime[iprofile] / 50.0) * 50);
		if (d3Config.profileleftMouseTime[iprofile] < 50) d3Config.profileleftMouseTime[iprofile] = 50;
		if (d3Config.profilerightMouseTime[iprofile] < 50) d3Config.profilerightMouseTime[iprofile] = 50;
		if (d3Config.profileskillSlot01Time[iprofile] < 50) d3Config.profileskillSlot01Time[iprofile] = 50;
		if (d3Config.profileskillSlot02Time[iprofile] < 50) d3Config.profileskillSlot02Time[iprofile] = 50;
		if (d3Config.profileskillSlot03Time[iprofile] < 50) d3Config.profileskillSlot03Time[iprofile] = 50;
		if (d3Config.profileskillSlot04Time[iprofile] < 50) d3Config.profileskillSlot04Time[iprofile] = 50;
		if (d3Config.profilehealingTime[iprofile] < 50) d3Config.profilehealingTime[iprofile] = 50;
		if (d3Config.profileskill01Enable[iprofile] != 0) d3Config.profileskill01Enable[iprofile] = 1;
		if (d3Config.profileskill02Enable[iprofile] != 0) d3Config.profileskill02Enable[iprofile] = 1;
		if (d3Config.profileskill03Enable[iprofile] != 0) d3Config.profileskill03Enable[iprofile] = 1;
		if (d3Config.profileskill04Enable[iprofile] != 0) d3Config.profileskill04Enable[iprofile] = 1;
		if (d3Config.profilehealingEnable[iprofile] != 0) d3Config.profilehealingEnable[iprofile] = 1;
		if (d3Config.profileautoSpaceEnable[iprofile] != 0) d3Config.profileautoSpaceEnable[iprofile] = 1;
	}


	if (!((d3Config.keySKill01 >= 'A' && d3Config.keySKill01 <= 'Z')
		|| (d3Config.keySKill01 >= '0' && d3Config.keySKill01 <= '9')
		|| d3Config.keySKill01 == ' '))
	{
		d3Config.keySKill01 = '1';
	}
	if (!((d3Config.keySKill02 >= 'A' && d3Config.keySKill02 <= 'Z')
		|| (d3Config.keySKill02 >= '0' && d3Config.keySKill02 <= '9')
		|| d3Config.keySKill02 == ' '))
	{
		d3Config.keySKill02 = '2';
	}
	if (!((d3Config.keySKill03 >= 'A' && d3Config.keySKill03 <= 'Z')
		|| (d3Config.keySKill03 >= '0' && d3Config.keySKill03 <= '9')
		|| d3Config.keySKill03 == ' '))
	{
		d3Config.keySKill03 = '3';
	}
	if (!((d3Config.keySKill04 >= 'A' && d3Config.keySKill04 <= 'Z')
		|| (d3Config.keySKill04 >= '0' && d3Config.keySKill04 <= '9')
		|| d3Config.keySKill04 == ' '))
	{
		d3Config.keySKill04 = '4';
	}
	if (!((d3Config.keyHealing >= 'A' && d3Config.keyHealing <= 'Z')
		|| (d3Config.keyHealing >= '0' && d3Config.keyHealing <= '9')
		|| d3Config.keyHealing == ' '))
	{
		d3Config.keyHealing = 'Q';
	}
	if (!((d3Config.keySpace >= 'A' && d3Config.keySpace <= 'Z')
		|| (d3Config.keySpace >= '0' && d3Config.keySpace <= '9')
		|| d3Config.keySpace == ' '))
	{
		d3Config.keySpace = ' ';
	}


}
const int	timerDelay = 50/*ms*/;
bool		flagOnF1 = false;
bool		flagOnF2 = false;
bool		flagOnF3 = false;

bool		flagOnCtrl5 = false;
bool		flagOnCtrl6 = false;
bool		flagOnCtrl7 = false;
bool		flagOnCtrl9 = false;
bool		flagOnProcess = false;

int			leftMouseCooldown;
int			rightMouseCooldown;
int			skillSlot01Cooldown;
int			skillSlot02Cooldown;
int			skillSlot03Cooldown;
int			skillSlot04Cooldown;
int			healingCooldown;
HHOOK		hGlobalHook;
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
		Sleep(5 + (rand() % 3));
		SendMessage(d3Wnd, WM_KEYUP, keyCode, 0);
		Sleep(5 + (rand() % 3));
	}
}
void		SetD3Mouse(int x, int y)
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		RECT d3Rect = { 0 };
		GetWindowRect(d3Wnd, &d3Rect);
		SetCursorPos(d3Rect.left + x, d3Rect.top + y);
	}
}
void		SendD3LeftMouseClick()
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		POINT point = { 0 };
		GetCursorPos(&point);

		RECT d3Rect = { 0 };
		GetWindowRect(d3Wnd, &d3Rect);

		LPARAM lParam = (point.x - d3Rect.left) | ((point.y - d3Rect.top) << 16);

		SendMessage(d3Wnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
		Sleep(5 + (rand() % 3));
		SendMessage(d3Wnd, WM_LBUTTONUP, 0, lParam);
		Sleep(5 + (rand() % 3));
	}
}
void		SendD3RightMouseClick()
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		POINT point = { 0 };
		GetCursorPos(&point);

		RECT d3Rect = { 0 };
		GetWindowRect(d3Wnd, &d3Rect);

		LPARAM lParam = (point.x - d3Rect.left) | ((point.y - d3Rect.top) << 16);

		SendMessage(d3Wnd, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
		Sleep(5 + (rand() % 3));
		SendMessage(d3Wnd, WM_RBUTTONUP, 0, lParam);
		Sleep(5 + (rand() % 3));
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

						//Skill, Inventory,...
						if (PointInRect(point, d3Rect.left + 1089, d3Rect.left + 1284, d3Rect.top + 995, d3Rect.top + 1062))
						{
							return false;
						}

						//Friend Button
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

						//Main-Player
						if (PointInRect(point, d3Rect.left + 28, d3Rect.left + 93, d3Rect.top + 47, d3Rect.top + 149))
						{
							return false;
						}
					}

					// 					else
					// 					{
					// 						double xScale = (d3Rect.bottom - d3Rect.top) / 1080.0;
					// 						double yScale = (d3Rect.bottom - d3Rect.top) / 1080.0;
					// 						//chat button
					// 						if (PointInRect(point, d3Rect.left + xScale * 10, d3Rect.left + xScale * 80, d3Rect.top + yScale * 980, d3Rect.top + yScale * 1044))
					// 						{
					// 							return false;
					// 						}
					// 
					// 						//Skill, Inventory,...
					// 						if (PointInRect(point, d3Rect.left + xScale * 1089, d3Rect.left + xScale * 1284, d3Rect.top + yScale * 995, d3Rect.top + yScale * 1062))
					// 						{
					// 							return false;
					// 						}
					// 
					// 						//Friend Button
					// 						if (PointInRect(point, d3Rect.left + xScale * 1764, d3Rect.left + xScale * 1904, d3Rect.top + yScale * 979, d3Rect.top + yScale * 1044))
					// 						{
					// 							return false;
					// 						}
					// 
					// 						//Small chat box
					// 						if (PointInRect(point, d3Rect.left + xScale * 32, d3Rect.left + xScale * 346, d3Rect.top + yScale * 738, d3Rect.top + yScale * 877))
					// 						{
					// 							return false;
					// 						}
					// 
					// 						//Objectives Object
					// 						if (PointInRect(point, d3Rect.left + xScale * 1862, d3Rect.left + xScale * 1893, d3Rect.top + yScale * 367, d3Rect.top + yScale * 391))
					// 						{
					// 							return false;
					// 						}
					// 
					// 						//Main-Player
					// 						if (PointInRect(point, d3Rect.left + xScale * 28, d3Rect.left + xScale * 93, d3Rect.top + yScale * 47, d3Rect.top + yScale * 149))
					// 						{
					// 							return false;
					// 						}
					// 
					// 					}
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
extern "C" __declspec(dllexport) LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	static bool flagOnCtrl = false;
	bool		flagNeedMoreHook = true;
	if (nCode >= 0 && nCode == HC_ACTION)
	{
		LPKBDLLHOOKSTRUCT keyParam = (LPKBDLLHOOKSTRUCT)(void*)lParam;
		if (wParam == WM_KEYUP)
		{
			switch (keyParam->vkCode)
			{
			case VK_LCONTROL:
			case VK_RCONTROL:
				flagOnCtrl = false;
				break;
			case VK_F1:
				if (IsD3WindowActive()) flagNeedMoreHook = false;
				break;
			}
		}
		else if (wParam == WM_KEYDOWN)
		{
			switch (keyParam->vkCode)
			{
			case VK_F1:
				flagNeedMoreHook = false;
				flagOnF1 = !flagOnF1;
				flagOnCtrl = false;
				flagOnCtrl5 = false;
				flagOnCtrl6 = false;
				flagOnCtrl7 = false;
				flagOnCtrl9 = false;
				leftMouseCooldown = 99999;
				break;
			case VK_F2:
				flagOnF2 = !flagOnF2;
				flagOnCtrl = false;
				flagOnCtrl5 = false;
				flagOnCtrl6 = false;
				flagOnCtrl7 = false;
				flagOnCtrl9 = false;
				skillSlot01Cooldown = 99999;
				skillSlot02Cooldown = 99999;
				skillSlot03Cooldown = 99999;
				skillSlot04Cooldown = 99999;
				healingCooldown = 99999;
				break;
			case VK_F3:
				flagOnF3 = !flagOnF3;
				flagOnCtrl = false;
				flagOnCtrl5 = false;
				flagOnCtrl6 = false;
				flagOnCtrl7 = false;
				flagOnCtrl9 = false;
				rightMouseCooldown = 99999;
				break;
			case VK_ESCAPE:
			case VK_SPACE:
				flagOnCtrl = false;
				flagOnCtrl5 = false;
				flagOnCtrl6 = false;
				flagOnCtrl7 = false;
				flagOnCtrl9 = false;
				break;
			case 0x35/*'5'*/:
				if (flagOnCtrl)
				{
					flagOnF1 = false;
					flagOnF2 = false;
					flagOnF3 = false;
					flagOnCtrl5 = true;
					flagOnCtrl6 = false;
					flagOnCtrl7 = false;
					flagOnCtrl9 = false;
				}
				break;
			case 0x36/*'6'*/:
				if (flagOnCtrl)
				{
					flagOnF1 = false;
					flagOnF2 = false;
					flagOnF3 = false;
					flagOnCtrl5 = false;
					flagOnCtrl6 = true;
					flagOnCtrl7 = false;
					flagOnCtrl9 = false;
				}
				break;
			case 0x37/*'7'*/:
				if (flagOnCtrl)
				{
					flagOnF1 = false;
					flagOnF2 = false;
					flagOnF3 = false;
					flagOnCtrl5 = false;
					flagOnCtrl6 = false;
					flagOnCtrl7 = true;
					flagOnCtrl9 = false;
				}
				break;
			case 0x39/*'9'*/:
				if (flagOnCtrl)
				{
					flagOnF1 = false;
					flagOnF2 = false;
					flagOnF3 = false;
					flagOnCtrl5 = false;
					flagOnCtrl6 = false;
					flagOnCtrl7 = false;
					flagOnCtrl9 = true;
				}
				break;
			case VK_LCONTROL:
			case VK_RCONTROL:
				flagOnCtrl = true;
				break;
			}
		}
	}
	if (flagNeedMoreHook == false)
	{
		return 1;
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
	ON_COMMAND(ID_HELP, &CDialoIIISupportDlg::OnHelp)
	ON_EN_KILLFOCUS(IDC_PROFILENAME, &CDialoIIISupportDlg::OnKillfocusProfilename)
	ON_BN_CLICKED(IDC_PROFILE01, &CDialoIIISupportDlg::OnBnClickedProfile01)
	ON_BN_CLICKED(IDC_PROFILE02, &CDialoIIISupportDlg::OnBnClickedProfile02)
	ON_BN_CLICKED(IDC_PROFILE03, &CDialoIIISupportDlg::OnBnClickedProfile03)
	ON_BN_CLICKED(IDC_PROFILE04, &CDialoIIISupportDlg::OnBnClickedProfile04)
	ON_BN_CLICKED(IDC_PROFILE05, &CDialoIIISupportDlg::OnBnClickedProfile05)
	ON_BN_CLICKED(IDC_PROFILE06, &CDialoIIISupportDlg::OnBnClickedProfile06)
	ON_BN_CLICKED(IDC_PROFILE07, &CDialoIIISupportDlg::OnBnClickedProfile07)
	ON_BN_CLICKED(IDC_PROFILE08, &CDialoIIISupportDlg::OnBnClickedProfile08)
	ON_BN_CLICKED(IDC_PROFILE09, &CDialoIIISupportDlg::OnBnClickedProfile09)
	ON_BN_CLICKED(IDC_PROFILE10, &CDialoIIISupportDlg::OnBnClickedProfile10)
	ON_EN_KILLFOCUS(IDC_SKILLKEY01, &CDialoIIISupportDlg::OnKillfocusSkillkey01)
	ON_EN_KILLFOCUS(IDC_SKILLKEY02, &CDialoIIISupportDlg::OnKillfocusSkillkey02)
	ON_EN_KILLFOCUS(IDC_SKILLKEY03, &CDialoIIISupportDlg::OnKillfocusSkillkey03)
	ON_EN_KILLFOCUS(IDC_SKILLKEY04, &CDialoIIISupportDlg::OnKillfocusSkillkey04)
	ON_EN_KILLFOCUS(IDC_HEALINGKEY, &CDialoIIISupportDlg::OnKillfocusHealingkey)
END_MESSAGE_MAP()


// CDialoIIISupportDlg message handlers

int profileID[maxProfileNumber] =
{
IDC_PROFILE01,
IDC_PROFILE02,
IDC_PROFILE03,
IDC_PROFILE04,
IDC_PROFILE05,
IDC_PROFILE06,
IDC_PROFILE07,
IDC_PROFILE08,
IDC_PROFILE09,
IDC_PROFILE10,
};


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

	srand((unsigned int)time((time_t*)0));




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


	swprintf_s(buffer, L"%lc", d3Config.keySKill01);
	GetDlgItem(IDC_SKILLKEY01)->SetWindowText(buffer);

	swprintf_s(buffer, L"%lc", d3Config.keySKill02);
	GetDlgItem(IDC_SKILLKEY02)->SetWindowText(buffer);

	swprintf_s(buffer, L"%lc", d3Config.keySKill03);
	GetDlgItem(IDC_SKILLKEY03)->SetWindowText(buffer);

	swprintf_s(buffer, L"%lc", d3Config.keySKill04);
	GetDlgItem(IDC_SKILLKEY04)->SetWindowText(buffer);

	swprintf_s(buffer, L"%lc", d3Config.keyHealing);
	GetDlgItem(IDC_HEALINGKEY)->SetWindowText(buffer);



	for (int iprofile = 0; iprofile < maxProfileNumber; iprofile++)
	{
		CString currentProfileName = d3Config.profileName[iprofile];
		if (iprofile == d3Config.currentProfile)
		{
			GetDlgItem(IDC_PROFILENAME)->SetWindowTextW(currentProfileName);
			currentProfileName.Insert(0, L"> ");
		}
		GetDlgItem(profileID[iprofile])->SetWindowTextW(currentProfileName);
	}

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
void CDialoIIISupportDlg::OnHelp()
{
	// TODO: Add your command handler code here
}




















void CDialoIIISupportDlg::OnTimer(UINT_PTR nIdEvent)
{
	if (myTimerID == nIdEvent)
	{
		if (flagOnProcess == false)
		{
			flagOnProcess = true;
			const WCHAR * bufferActive = L"Found";
			HWND d3Wnd = GetD3Windows();
			RECT d3Rect = { 0 };
			if (d3Wnd == 0)
			{
				bufferActive = L"";
				flagOnF1 = false;
				flagOnF2 = false;
				flagOnF3 = false;
			}
			else
			{
				::GetWindowRect(d3Wnd, &d3Rect);
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

			/************************************************************************/
			/*                                                                      */
			/************************************************************************/
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
				if (d3Wnd != 0)
				{
					bool flagValidForSendSpace = true;
					if (d3Config.skill01Enable)
					{
						skillSlot01Cooldown += timerDelay;
						if (skillSlot01Cooldown >= d3Config.skillSlot01Time)
						{
							if (flagValidForSendSpace)
							{
								if (d3Config.autoSpaceEnable) SendD3Key(VK_SPACE);
								flagValidForSendSpace = false;
							}
							SendD3Key(d3Config.keySKill01);
							skillSlot01Cooldown = 0;
						}
					}
					if (d3Config.skill02Enable)
					{
						skillSlot02Cooldown += timerDelay;
						if (skillSlot02Cooldown >= d3Config.skillSlot02Time)
						{
							if (flagValidForSendSpace)
							{
								if (d3Config.autoSpaceEnable) SendD3Key(VK_SPACE);
								flagValidForSendSpace = false;
							}
							SendD3Key(d3Config.keySKill02);
							skillSlot02Cooldown = 0;
						}
					}
					if (d3Config.skill03Enable)
					{
						skillSlot03Cooldown += timerDelay;
						if (skillSlot03Cooldown >= d3Config.skillSlot03Time)
						{
							if (flagValidForSendSpace)
							{
								if (d3Config.autoSpaceEnable) SendD3Key(VK_SPACE);
								flagValidForSendSpace = false;
							}
							SendD3Key(d3Config.keySKill03);
							skillSlot03Cooldown = 0;
						}
					}
					if (d3Config.skill04Enable)
					{
						skillSlot04Cooldown += timerDelay;
						if (skillSlot04Cooldown >= d3Config.skillSlot04Time)
						{
							if (flagValidForSendSpace)
							{
								if (d3Config.autoSpaceEnable) SendD3Key(VK_SPACE);
								flagValidForSendSpace = false;
							}
							SendD3Key(d3Config.keySKill04);
							skillSlot04Cooldown = 0;
						}
					}
					if (d3Config.healingEnable)
					{
						healingCooldown += timerDelay;
						if (healingCooldown >= d3Config.skillSlot04Time)
						{
							if (flagValidForSendSpace)
							{
								if (d3Config.autoSpaceEnable) SendD3Key(VK_SPACE);
								flagValidForSendSpace = false;
							}
							SendD3Key(d3Config.keyHealing);
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
				if (d3Wnd != 0)
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
				GetDlgItem(IDC_RIGHTMOUSETEXT)->SetWindowText(L"Right Mouse (Hotkey F3): \r\n	Running");
				GetDlgItem(IDC_RIGHTMOUSETEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_RIGHTMOUSETEXTMS)->EnableWindow(FALSE);
				GetDlgItem(IDC_RIGHTMOUSETIME)->EnableWindow(FALSE);
				if (d3Wnd != 0)
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
				GetDlgItem(IDC_RIGHTMOUSETEXT)->SetWindowText(L"Right Mouse (Hotkey F3): ");
				GetDlgItem(IDC_RIGHTMOUSETEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_RIGHTMOUSETEXTMS)->EnableWindow(TRUE);
				GetDlgItem(IDC_RIGHTMOUSETIME)->EnableWindow(TRUE);
			}

			/************************************************************************/
			/*                                                                      */
			/************************************************************************/
			if (d3Wnd != 0 && IsD3WindowActive())
			{
				if ((flagOnCtrl5 || flagOnCtrl6 || flagOnCtrl7 || flagOnCtrl9))
				{
					GetDlgItem(IDC_CTRL5TEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_CTRL6TEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_CTRL7TEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_CTRL9TEXT)->EnableWindow(FALSE);
					double		d3Width = d3Rect.right - d3Rect.left;
					double		d3Height = d3Rect.bottom - d3Rect.top;
					double		d3Scale = d3Height / 1080.0;
					int xSalvage = (int)round(170.0 * d3Scale);
					int ySalvage = (int)round(290.0 * d3Scale);
					int xTransmute = (int)round(230.0 * d3Scale);
					int yTransmute = (int)round(830.0 * d3Scale);
					int xFill = (int)round(720.0 * d3Scale);
					int yFill = (int)round(840.0 * d3Scale);

					int xCenter = int(d3Width / 2);
					int yCenter = int(d3Height / 2);

					int			xIventoryArray[60] = { 0 };
					int			yIventoryArray[60] = { 0 };
					double		xLeftPage = 583 * d3Scale;
					double		yLeftPage = 840 * d3Scale;
					double		xRightPage = 852 * d3Scale;
					double		yRightPage = 840 * d3Scale;


					int xSalTab01 = 517 * d3Scale;
					int ySalTab01 = 223 * d3Scale;

					int xSalTab01 = 517 * d3Scale;
					int ySalTab01 = 620 * d3Scale;



					if (xIventoryArray[0] == 0 && yIventoryArray[0] == 0)
					{
						double		xInventory = (d3Width - (1920.0 - 1423.0) * d3Scale);
						double		yInventory = 583 * d3Scale;
						double		wIventory = 500.0 * d3Scale;
						double		hIventory = 296.0 * d3Scale;
						double		wSlot = wIventory / 10.0;
						double		hSlot = hIventory / 6.0;
						for (int icolumn = 0; icolumn < 10; icolumn++)
						{
							int currentX = (int)round(xInventory + wSlot * icolumn);
							for (int irow = 0; irow < 6; irow++)
							{
								xIventoryArray[irow * 10 + icolumn] = currentX;
								yIventoryArray[irow * 10 + icolumn] = (int)round(yInventory + hSlot * irow);

							}
						}
					}


					/************************************************************************/
					/* 1 Slot                                                               */
					/************************************************************************/
					if (flagOnCtrl5)
					{
						for (int iitem = 0; iitem < 60; iitem++)
						{
							if (flagOnCtrl5) SetD3Mouse(xIventoryArray[iitem], yIventoryArray[iitem]);
							if (flagOnCtrl5) SendD3RightMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));

							if (flagOnCtrl5) SetD3Mouse(xFill, yFill);
							if (flagOnCtrl5) SendD3LeftMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));

							if (flagOnCtrl5) SetD3Mouse(xTransmute, yTransmute);
							if (flagOnCtrl5) SendD3LeftMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));

							Sleep(200 + (rand() % 10));

							if (flagOnCtrl5) SetD3Mouse(xLeftPage, yLeftPage);
							if (flagOnCtrl5) SendD3LeftMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));

							if (flagOnCtrl5) SetD3Mouse(xRightPage, yRightPage);
							if (flagOnCtrl5) SendD3LeftMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));
						}
						flagOnCtrl5 = false;
					}


					/************************************************************************/
					/* 2 Slot                                                               */
					/************************************************************************/
					if (flagOnCtrl6)
					{
						for (int iitem = 0; iitem < 60; iitem++)
						{
							if (flagOnCtrl6) SetD3Mouse(xIventoryArray[iitem], yIventoryArray[iitem]);
							if (flagOnCtrl6) SendD3RightMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							if (flagOnCtrl6) SetD3Mouse(xFill, yFill);
							if (flagOnCtrl6) SendD3LeftMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							if (flagOnCtrl6) SetD3Mouse(xTransmute, yTransmute);
							if (flagOnCtrl6) SendD3LeftMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							Sleep(200 + (rand() % 10));

							if (flagOnCtrl6) SetD3Mouse(xLeftPage, yLeftPage);
							if (flagOnCtrl6) SendD3LeftMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							if (flagOnCtrl6) SetD3Mouse(xRightPage, yRightPage);
							if (flagOnCtrl6) SendD3LeftMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							if (iitem == 9 || iitem == 29 || iitem == 49)
							{
								iitem += 10;
							}
						}
						flagOnCtrl6 = false;
					}



					/************************************************************************/
					/* Drop                                                                 */
					/************************************************************************/
					if (flagOnCtrl7)
					{
						for (int iitem = 0; iitem < 60; iitem++)
						{
							if (flagOnCtrl7) SetD3Mouse(xIventoryArray[iitem], yIventoryArray[iitem]);
							if (flagOnCtrl7) SendD3LeftMouseClick();
							if (flagOnCtrl7) Sleep(50 + (rand() % 5));

							if (flagOnCtrl7) SetD3Mouse(xCenter, yCenter);
							if (flagOnCtrl7) SendD3LeftMouseClick();
							if (flagOnCtrl7) Sleep(50 + (rand() % 5));
						}
						flagOnCtrl7 = false;
					}


					/************************************************************************/
					/*                                                                      */
					/************************************************************************/
					if (flagOnCtrl9)
					{
						if (flagOnCtrl9) SetD3Mouse(xSalTab01, ySalTab01);
						if (flagOnCtrl9) SendD3LeftMouseClick();
						if (flagOnCtrl9) SetD3Mouse(xSalTab01, ySalTab01);
						if (flagOnCtrl9) SendD3LeftMouseClick();

						if (flagOnCtrl9) SetD3Mouse(xSalvage, ySalvage);
						if (flagOnCtrl9) SendD3LeftMouseClick();
						if (flagOnCtrl9) Sleep(50 + (rand() % 5));
						for (int iitem = 0; iitem < 60; iitem++)
						{
							if (flagOnCtrl9) SetD3Mouse(xIventoryArray[iitem], yIventoryArray[iitem]);
							if (flagOnCtrl9) SendD3LeftMouseClick();
							if (flagOnCtrl9) Sleep(50 + (rand() % 5));
							if (flagOnCtrl9) SendD3Key(VK_RETURN);
						}
						flagOnCtrl9 = false;
					}

					GetDlgItem(IDC_CTRL5TEXT)->EnableWindow(TRUE);
					GetDlgItem(IDC_CTRL6TEXT)->EnableWindow(TRUE);
					GetDlgItem(IDC_CTRL7TEXT)->EnableWindow(TRUE);
					GetDlgItem(IDC_CTRL9TEXT)->EnableWindow(TRUE);


				}
			}
			else
			{
				flagOnCtrl5 = false;
				flagOnCtrl6 = false;
				flagOnCtrl7 = false;
			}







			flagOnProcess = false;
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusLeftmousetime()
{
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(IDC_LEFTMOUSETIME)->GetWindowTextW(bufferText, 999);
	int newValue = 0;
	swscanf(bufferText, L"%d", &newValue);
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL01TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot01Time)
	{
		d3Config.skillSlot01Time = newValue;
		d3Config.profileskillSlot01Time[d3Config.currentProfile] = newValue;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL02TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot02Time)
	{
		d3Config.skillSlot02Time = newValue;
		d3Config.profileskillSlot02Time[d3Config.currentProfile] = newValue;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL03TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot03Time)
	{
		d3Config.skillSlot03Time = newValue;
		d3Config.profileskillSlot03Time[d3Config.currentProfile] = newValue;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_SKILL04TIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.skillSlot04Time)
	{
		d3Config.skillSlot04Time = newValue;
		d3Config.profileskillSlot04Time[d3Config.currentProfile] = newValue;
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
	newValue = int(round(newValue / 50.0) * 50);
	if (newValue < 50) newValue = 50;
	swprintf(bufferText, L"%d", newValue);
	GetDlgItem(IDC_HEALINGTIME)->SetWindowTextW(bufferText);
	if (newValue != d3Config.healingTime)
	{
		d3Config.healingTime = newValue;
		d3Config.profilehealingTime[d3Config.currentProfile] = newValue;
		CFile saveFile;
		if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.Write(&d3Config, sizeof(d3Config));
			saveFile.Close();
		}
	}
}
void CDialoIIISupportDlg::OnKillfocusSkillkey01()
{
	int changeID = IDC_SKILLKEY01;
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);
	int newValue = bufferText[0];
	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' ')
	{


		if (newValue != d3Config.keySKill01)
		{
			d3Config.keySKill01 = newValue;

			CFile saveFile;
			if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
			{
				saveFile.Write(&d3Config, sizeof(d3Config));
				saveFile.Close();
			}
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"Only allow : ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
			flagAlreadyWarning = 1;
		}
	}
	swprintf_s(bufferText, L"%lc", d3Config.keySKill01);
	GetDlgItem(changeID)->SetWindowText(bufferText);
}
void CDialoIIISupportDlg::OnKillfocusSkillkey02()
{
	int changeID = IDC_SKILLKEY02;
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);
	int newValue = bufferText[0];
	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' ')
	{

		if (newValue != d3Config.keySKill02)
		{
			d3Config.keySKill02 = newValue;

			CFile saveFile;
			if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
			{
				saveFile.Write(&d3Config, sizeof(d3Config));
				saveFile.Close();
			}
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"Only allow : ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
			flagAlreadyWarning = 1;
		}
	}
	swprintf_s(bufferText, L"%lc", d3Config.keySKill02);
	GetDlgItem(changeID)->SetWindowText(bufferText);
}
void CDialoIIISupportDlg::OnKillfocusSkillkey03()
{
	int changeID = IDC_SKILLKEY03;
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);
	int newValue = bufferText[0];
	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' ')
	{

		if (newValue != d3Config.keySKill03)
		{
			d3Config.keySKill03 = newValue;

			CFile saveFile;
			if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
			{
				saveFile.Write(&d3Config, sizeof(d3Config));
				saveFile.Close();
			}
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"Only allow : ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
			flagAlreadyWarning = 1;
		}
	}
	swprintf_s(bufferText, L"%lc", d3Config.keySKill03);
	GetDlgItem(changeID)->SetWindowText(bufferText);
}
void CDialoIIISupportDlg::OnKillfocusSkillkey04()
{
	int changeID = IDC_SKILLKEY04;
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);
	int newValue = bufferText[0];
	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' ')
	{

		if (newValue != d3Config.keySKill04)
		{
			d3Config.keySKill04 = newValue;

			CFile saveFile;
			if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
			{
				saveFile.Write(&d3Config, sizeof(d3Config));
				saveFile.Close();
			}
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"Only allow : ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
			flagAlreadyWarning = 1;
		}
	}
	swprintf_s(bufferText, L"%lc", d3Config.keySKill04);
	GetDlgItem(changeID)->SetWindowText(bufferText);
}
void CDialoIIISupportDlg::OnKillfocusHealingkey()
{
	int changeID = IDC_HEALINGKEY;
	wchar_t bufferText[1000] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);
	int newValue = bufferText[0];
	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' ')
	{
		if (newValue != d3Config.keyHealing)
		{
			d3Config.keyHealing = newValue;
			CFile saveFile;
			if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
			{
				saveFile.Write(&d3Config, sizeof(d3Config));
				saveFile.Close();
			}
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"Only allow : ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
			flagAlreadyWarning = 1;
		}
	}
	swprintf_s(bufferText, L"%lc", d3Config.keyHealing);
	GetDlgItem(changeID)->SetWindowText(bufferText);
}
void CDialoIIISupportDlg::OnClickedSkill01check()
{
	d3Config.skill01Enable = !d3Config.skill01Enable;
	d3Config.profileskill01Enable[d3Config.currentProfile] = d3Config.skill01Enable;
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
	d3Config.profileskill02Enable[d3Config.currentProfile] = d3Config.skill02Enable;
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
	d3Config.profileskill03Enable[d3Config.currentProfile] = d3Config.skill03Enable;
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
	d3Config.profileskill04Enable[d3Config.currentProfile] = d3Config.skill04Enable;
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
	d3Config.profilehealingEnable[d3Config.currentProfile] = d3Config.healingEnable;
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
	d3Config.profileautoSpaceEnable[d3Config.currentProfile] = d3Config.autoSpaceEnable;
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
void CDialoIIISupportDlg::OnKillfocusProfilename()
{
	wchar_t bufferProfileName[1000];
	GetDlgItem(IDC_PROFILENAME)->GetWindowTextW(bufferProfileName, 999);
	bufferProfileName[maxProfileNameLength] = 0;
	GetDlgItem(IDC_PROFILENAME)->SetWindowTextW(bufferProfileName);
	wcscpy(d3Config.profileName[d3Config.currentProfile], bufferProfileName);

	CString currentProfileName = d3Config.profileName[d3Config.currentProfile];
	currentProfileName += L"*";
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(currentProfileName);
}
void CDialoIIISupportDlg::OnBnClickedProfile()
{
	d3Config.leftMouseTime = d3Config.profileleftMouseTime[d3Config.currentProfile];
	d3Config.rightMouseTime = d3Config.profilerightMouseTime[d3Config.currentProfile];
	d3Config.skillSlot01Time = d3Config.profileskillSlot01Time[d3Config.currentProfile];
	d3Config.skillSlot02Time = d3Config.profileskillSlot02Time[d3Config.currentProfile];
	d3Config.skillSlot03Time = d3Config.profileskillSlot03Time[d3Config.currentProfile];
	d3Config.skillSlot04Time = d3Config.profileskillSlot04Time[d3Config.currentProfile];
	d3Config.healingTime = d3Config.profilehealingTime[d3Config.currentProfile];
	d3Config.skill01Enable = d3Config.profileskill01Enable[d3Config.currentProfile];
	d3Config.skill02Enable = d3Config.profileskill02Enable[d3Config.currentProfile];
	d3Config.skill03Enable = d3Config.profileskill03Enable[d3Config.currentProfile];
	d3Config.skill04Enable = d3Config.profileskill04Enable[d3Config.currentProfile];
	d3Config.healingEnable = d3Config.profilehealingEnable[d3Config.currentProfile];
	d3Config.autoSpaceEnable = d3Config.profileautoSpaceEnable[d3Config.currentProfile];




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




	CString currentProfileName = L"> ";
	currentProfileName += d3Config.profileName[d3Config.currentProfile];
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(currentProfileName);
	GetDlgItem(IDC_PROFILENAME)->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	CFile saveFile;
	if (saveFile.Open(savePath, CFile::modeCreate | CFile::modeWrite))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
}
void CDialoIIISupportDlg::OnBnClickedProfile01()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 0;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile02()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 1;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile03()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 2;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile04()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 3;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile05()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 4;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile06()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 5;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile07()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 6;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile08()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 7;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile09()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 8;
	OnBnClickedProfile();
}
void CDialoIIISupportDlg::OnBnClickedProfile10()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 9;
	OnBnClickedProfile();
}


