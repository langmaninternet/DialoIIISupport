
// DialoIIISupportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DiabloIIISupport.h"
#include "DiabloIIISupportDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/************************************************************************/
/* StarPact Engine                                                      */
/************************************************************************/
bool		InitStarPactEngine(const wchar_t * licenseID);
void		GenDeviceIdentification(wchar_t * bufferDeviceID, int bufferDeviceIDSize);

void		ArchonStarPactCastMeteor(const wchar_t meteorKey,
	const wchar_t archonKey,
	const wchar_t primaryKey,
	const wchar_t secondaryKey,
	const wchar_t forceStandKey);

void		ArchonStarPactCycle(const wchar_t blackHoleKey,
	const wchar_t wayOfForceKey,
	const wchar_t meteorKey,
	const wchar_t archonKey,
	const wchar_t primaryKey,
	const wchar_t secondaryKey,
	const wchar_t forceStandKey);
void		StartStarPact(void);
void		StopStarPact(void);

void		StarPactDumpData(void);




struct DiabloIIIStatusStruct
{
	bool	flagInAttackMode;
	bool	flagPotionReady;
	bool	flagIsOpenMap;
	bool	flagIsOpenSkillTable;
	bool	flagIsOpenKadala;
	bool	flagIsOpenUrshi;
	bool	flagIsOpenStash;
	bool	flagSkill01IsLightningBlast;
	bool	flagSkill01IsReadyToAndNeedAutoPress;
	bool	flagSkill02IsReadyToAndNeedAutoPress;
	bool	flagSkill03IsReadyToAndNeedAutoPress;
	bool	flagSkill04IsReadyToAndNeedAutoPress;
	int		skill01Key;
	int		skill02Key;
	int		skill03Key;
	int		skill04Key;
	int		healingKey;

#ifdef _DEBUG
	int		getStatusTime;
#endif
};
void		GetCurrentDiabloIIStatus(DiabloIIIStatusStruct & gameStatus);





DiabloIIIStatusStruct gameStatus;
const double DiabloIIISupportVersion = 1.07;
const int defaultHeathLimit = 80;
/************************************************************************/
/* Struct                                                               */
/************************************************************************/
const int	maxProfileNumber = 10;
const int	maxProfileNameLength = 15;
const int	profileID[maxProfileNumber] =
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
struct DiabloIIISupportConfig
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
	int		modeFireBirdEnable;
	int		modeArchonEnable;
	int		fullCycleEnable;


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
	int		profilemodeFireBirdEnable[maxProfileNumber + 1];
	int		profilemodeArchonEnable[maxProfileNumber + 1];
	int		profilelightingBlastEnable[maxProfileNumber + 1];

	wchar_t	keySKill01;
	wchar_t	keySKill02;
	wchar_t	keySKill03;
	wchar_t	keySKill04;
	wchar_t	keyHealing;
	wchar_t keyForceClose;
	wchar_t keyForceStand;
	wchar_t keyForceMove;
	wchar_t keyBlackHole;
	wchar_t keyWaveOfForce;
	wchar_t keyPrimary;
	wchar_t keySecondary;
	wchar_t keyMeteor;
	wchar_t keyArchon;
	wchar_t keyWizSingleShot;





	double	saveDiabloIIISupportVersion;
};



/************************************************************************/
/* Variable                                                             */
/************************************************************************/
DiabloIIISupportConfig	d3Config;
wchar_t					configSavePath[3000] = { 0 };

const int				mainTimerDelay = 50/*ms*/;
bool					flagOnF1 = false;
bool					flagOnF2 = false;
bool					flagOnF3 = false;
bool					flagOnCtrl5 = false;
bool					flagOnCtrl6 = false;
bool					flagOnCtrl7 = false;
bool					flagOnCtrl9 = false;
bool					flagOnWizSingleShot = false;
bool					flagOnProcess = false;
int						leftMouseCooldown;
int						rightMouseCooldown;
int						skillSlot01Cooldown;
int						skillSlot02Cooldown;
int						skillSlot03Cooldown;
int						skillSlot04Cooldown;
HHOOK					hGlobalHook;
//double				currentHeath = 0.0;
//bool					flagAttackMode = true;

/************************************************************************/
/* Process Function                                                     */
/************************************************************************/
void		ValidateD3Key(wchar_t & keyValue, const wchar_t defaultValue)
{
	if (keyValue == '`') keyValue = '~';
	if (!((keyValue >= 'A' && keyValue <= 'Z')
		|| (keyValue >= '0' && keyValue <= '9')
		|| keyValue == ' '
		|| keyValue == '~'
		|| keyValue == VK_SHIFT
		|| keyValue == VK_CONTROL
		|| keyValue == VK_LBUTTON
		|| keyValue == VK_RBUTTON
		))
	{
		keyValue = defaultValue;
	}
}
void		ValidateD3Config(void)
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
	if (d3Config.modeArchonEnable != 0) d3Config.modeArchonEnable = 1;
	if (d3Config.modeFireBirdEnable != 0) d3Config.modeFireBirdEnable = 1;
	if (d3Config.currentProfile < 0 || d3Config.currentProfile >= maxProfileNumber) d3Config.currentProfile = 0;
	if (d3Config.fullCycleEnable != 0) d3Config.fullCycleEnable = 1;

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
		if (d3Config.profilemodeFireBirdEnable[iprofile] != 0) d3Config.profilemodeFireBirdEnable[iprofile] = 1;
		if (d3Config.profilemodeArchonEnable[iprofile] != 0) d3Config.profilemodeArchonEnable[iprofile] = 1;
		if (d3Config.profilelightingBlastEnable[iprofile] != 0) d3Config.profilelightingBlastEnable[iprofile] = 1;
	}




	ValidateD3Key(d3Config.keySKill01, '1');
	ValidateD3Key(d3Config.keySKill02, '2');
	ValidateD3Key(d3Config.keySKill03, '3');
	ValidateD3Key(d3Config.keySKill04, '4');
	ValidateD3Key(d3Config.keyHealing, 'Q');
	ValidateD3Key(d3Config.keyForceClose, ' ');


	//wiz
	ValidateD3Key(d3Config.keyForceStand, VK_SHIFT);
	ValidateD3Key(d3Config.keyWaveOfForce, '1');
	ValidateD3Key(d3Config.keyMeteor, '2');
	ValidateD3Key(d3Config.keyPrimary, VK_LBUTTON);
	ValidateD3Key(d3Config.keySecondary, VK_RBUTTON);
	ValidateD3Key(d3Config.keyBlackHole, '3');
	ValidateD3Key(d3Config.keyArchon, '4');
	ValidateD3Key(d3Config.keyWizSingleShot, '~');



	/************************************************************************/
	/* Force                                                                */
	/************************************************************************/
	d3Config.healingTime = 50;
}
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
		Sleep(10 + (rand() % 3));
		SendMessage(d3Wnd, WM_LBUTTONUP, 0, lParam);
		Sleep(10 + (rand() % 3));
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
		Sleep(10 + (rand() % 3));
		SendMessage(d3Wnd, WM_RBUTTONUP, 0, lParam);
		Sleep(10 + (rand() % 3));
	}
}
void		SendD3Key(int keyCode)
{
	HWND d3Wnd = GetD3Windows();
	if (d3Wnd)
	{
		SendMessage(d3Wnd, WM_KEYDOWN, keyCode, 0);
		Sleep(10 + (rand() % 3));
		SendMessage(d3Wnd, WM_KEYUP, keyCode, 0);
		Sleep(10 + (rand() % 3));
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

						//Season Journey Button
						if (PointInRect(point, d3Rect.left + 1649, d3Rect.left + 1698, d3Rect.top + 25, d3Rect.top + 51))
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
/* Hook                                                                 */
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
				flagOnWizSingleShot = false;
				StopStarPact();
				break;

#ifdef _DEBUG
			case VK_F5:
				StarPactDumpData();

				//skill 01 635 1005 - 682 1502 - 682 1029
				break;
#endif


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
			default:
				if (flagOnWizSingleShot == false && (d3Config.modeArchonEnable || d3Config.modeFireBirdEnable))
				{
					if ((keyParam->vkCode == d3Config.keyWizSingleShot) || (d3Config.keyWizSingleShot == L'~' && keyParam->vkCode == VK_OEM_3))
					{
						StopStarPact();
						Sleep(10);
						StartStarPact();
						flagOnWizSingleShot = true;

					}
				}
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





/************************************************************************/
/* MFC                                                                  */
/************************************************************************/
/**/		CDiabloIIISupportDlg::CDiabloIIISupportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIABLOIIISUPPORT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void		CDiabloIIISupportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDiabloIIISupportDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_LEFTMOUSETIME, &CDiabloIIISupportDlg::OnKillFocusLeftMouseTime)
	ON_EN_KILLFOCUS(IDC_RIGHTMOUSETIME, &CDiabloIIISupportDlg::OnKillFocusRightMouseTime)
	ON_EN_KILLFOCUS(IDC_SKILL01TIME, &CDiabloIIISupportDlg::OnKillFocusSkill01Time)
	ON_EN_KILLFOCUS(IDC_SKILL02TIME, &CDiabloIIISupportDlg::OnKillFocusSkill02Time)
	ON_EN_KILLFOCUS(IDC_SKILL03TIME, &CDiabloIIISupportDlg::OnKillFocusSkill03Time)
	ON_EN_KILLFOCUS(IDC_SKILL04TIME, &CDiabloIIISupportDlg::OnKillFocusSkill04Time)
	//ON_EN_KILLFOCUS(IDC_HEALINGTIME, &CDialoIIISupportDlg::OnKillFocusHealingTime)
	ON_BN_CLICKED(IDC_SKILL01CHECK, &CDiabloIIISupportDlg::OnClickedSkill01Check)
	ON_BN_CLICKED(IDC_SKILL02CHECK, &CDiabloIIISupportDlg::OnClickedSkill02Check)
	ON_BN_CLICKED(IDC_SKILL03CHECK, &CDiabloIIISupportDlg::OnClickedSkill03Check)
	ON_BN_CLICKED(IDC_SKILL04CHECK, &CDiabloIIISupportDlg::OnClickedSkill04Check)
	ON_BN_CLICKED(IDC_HEALINGCHECK, &CDiabloIIISupportDlg::OnClickedHealingCheck)
	//ON_BN_CLICKED(IDC_SPACECHECK, &CDialoIIISupportDlg::OnClickedSpaceCheck)
	ON_COMMAND(ID_HELP, &CDiabloIIISupportDlg::OnHelp)
	ON_EN_KILLFOCUS(IDC_PROFILENAME, &CDiabloIIISupportDlg::OnKillFocusProfileName)
	ON_BN_CLICKED(IDC_PROFILE01, &CDiabloIIISupportDlg::OnBnClickedProfile01)
	ON_BN_CLICKED(IDC_PROFILE02, &CDiabloIIISupportDlg::OnBnClickedProfile02)
	ON_BN_CLICKED(IDC_PROFILE03, &CDiabloIIISupportDlg::OnBnClickedProfile03)
	ON_BN_CLICKED(IDC_PROFILE04, &CDiabloIIISupportDlg::OnBnClickedProfile04)
	ON_BN_CLICKED(IDC_PROFILE05, &CDiabloIIISupportDlg::OnBnClickedProfile05)
	ON_BN_CLICKED(IDC_PROFILE06, &CDiabloIIISupportDlg::OnBnClickedProfile06)
	ON_BN_CLICKED(IDC_PROFILE07, &CDiabloIIISupportDlg::OnBnClickedProfile07)
	ON_BN_CLICKED(IDC_PROFILE08, &CDiabloIIISupportDlg::OnBnClickedProfile08)
	ON_BN_CLICKED(IDC_PROFILE09, &CDiabloIIISupportDlg::OnBnClickedProfile09)
	ON_BN_CLICKED(IDC_PROFILE10, &CDiabloIIISupportDlg::OnBnClickedProfile10)
	ON_EN_KILLFOCUS(IDC_SKILLKEY01, &CDiabloIIISupportDlg::OnKillFocusSkillKey01)
	ON_EN_KILLFOCUS(IDC_SKILLKEY02, &CDiabloIIISupportDlg::OnKillFocusSkillKey02)
	ON_EN_KILLFOCUS(IDC_SKILLKEY03, &CDiabloIIISupportDlg::OnKillFocusSkillKey03)
	ON_EN_KILLFOCUS(IDC_SKILLKEY04, &CDiabloIIISupportDlg::OnKillFocusSkillKey04)
	ON_EN_KILLFOCUS(IDC_HEALINGKEY, &CDiabloIIISupportDlg::OnKillfocusHealingKey)
	ON_BN_CLICKED(IDC_WIZARCHONCHECK, &CDiabloIIISupportDlg::OnBnClickedWizArchoncheck)
	//ON_EN_KILLFOCUS(IDC_CLOSEPOPUPKEY, &CDialoIIISupportDlg::OnKillFocusClosePopupKey)
	ON_EN_KILLFOCUS(IDC_METEORKEY, &CDiabloIIISupportDlg::OnKillFocusMeteorKey)
	ON_BN_CLICKED(IDC_WIZFIREBRIDCHECK, &CDiabloIIISupportDlg::OnBnClickedWizFireBridCheck)
	ON_EN_KILLFOCUS(IDC_FORCESTANDKEY, &CDiabloIIISupportDlg::OnKillFocusForceStandKey)
	ON_EN_KILLFOCUS(IDC_FORCEMOVEKEY, &CDiabloIIISupportDlg::OnKillFocusForceMoveKey)
	ON_EN_KILLFOCUS(IDC_ARCHONKEY, &CDiabloIIISupportDlg::OnKillFocusArchonKey)
	ON_EN_KILLFOCUS(IDC_SINGLESHOTHOTKEY, &CDiabloIIISupportDlg::OnKillFocusSingleShotHotKey)
	ON_EN_KILLFOCUS(IDC_BLACKHOLEKEY, &CDiabloIIISupportDlg::OnKillFocusBlackHoleKey)
	ON_EN_KILLFOCUS(IDC_WAVEOFFORCEKEY, &CDiabloIIISupportDlg::OnKillFocusWaveOfForceKey)
	ON_EN_KILLFOCUS(IDC_PRIMARYSKILLKEY, &CDiabloIIISupportDlg::OnKillFocusPrimarySkillKey)
	ON_EN_KILLFOCUS(IDC_SECONDARYSKILLKEY, &CDiabloIIISupportDlg::OnKillFocusSecondarySkillKey)
	ON_BN_CLICKED(IDC_SINGLESHOTHOTCASTMETEORONLY, &CDiabloIIISupportDlg::OnBnClickedSingleshothotcastmeteoronly)
	ON_BN_CLICKED(IDC_SINGLESHOTHOTCASTFULLCYCLE, &CDiabloIIISupportDlg::OnBnClickedSingleshothotcastfullcycle)
END_MESSAGE_MAP()

BOOL		CDiabloIIISupportDlg::OnInitDialog()
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
	mainTimerID = CDialogEx::SetTimer(1, mainTimerDelay, NULL);

	if (configSavePath[0] == 0)
	{
		wchar_t appdataPath[2000] = { 0 };
		GetEnvironmentVariable(L"AppData", appdataPath, 1999);
		wchar_t bufferDir[2000] = { 0 };
		swprintf_s(bufferDir, L"%ls\\DialoIIISupport\\", appdataPath);
		CreateDirectoryW(bufferDir, 0);
		swprintf_s(configSavePath, L"%ls\\DialoIIISupport\\DiabloIIISupport.dat", appdataPath);
	}

	OnLoadConfig();

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


	swprintf_s(buffer, L"Diablo III Support Version %0.2lf", DiabloIIISupportVersion);
	SetWindowTextW(buffer);


	GetDlgItem(IDC_SKILL01TIME)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TIME)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TIME)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TIME)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL01TEXT)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TEXT)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TEXT)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TEXT)->EnableWindow(d3Config.skill04Enable);
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


	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY))->SetCheck(d3Config.fullCycleEnable == false);
	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE))->SetCheck(d3Config.fullCycleEnable);

	OnShowSkillKey(IDC_SKILLKEY01, d3Config.keySKill01);
	OnShowSkillKey(IDC_SKILLKEY02, d3Config.keySKill02);
	OnShowSkillKey(IDC_SKILLKEY03, d3Config.keySKill03);
	OnShowSkillKey(IDC_SKILLKEY04, d3Config.keySKill04);
	OnShowSkillKey(IDC_HEALINGKEY, d3Config.keyHealing);
	OnShowSkillKey(IDC_ARCHONKEY, d3Config.keyArchon);
	OnShowSkillKey(IDC_METEORKEY, d3Config.keyMeteor);
	OnShowSkillKey(IDC_FORCESTANDKEY, d3Config.keyForceStand);
	OnShowSkillKey(IDC_SINGLESHOTHOTKEY, d3Config.keyWizSingleShot);
	OnShowSkillKey(IDC_BLACKHOLEKEY, d3Config.keyBlackHole);
	OnShowSkillKey(IDC_WAVEOFFORCEKEY, d3Config.keyWaveOfForce);
	OnShowSkillKey(IDC_PRIMARYSKILLKEY, d3Config.keyPrimary);
	OnShowSkillKey(IDC_SECONDARYSKILLKEY, d3Config.keySecondary);

	GetDlgItem(IDC_METEORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_METEORKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYFORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);



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

	((CButton*)GetDlgItem(IDC_WIZFIREBRIDCHECK))->SetCheck(d3Config.modeFireBirdEnable);
	((CButton*)GetDlgItem(IDC_WIZARCHONCHECK))->SetCheck(d3Config.modeArchonEnable);

	if (InitStarPactEngine(NULL) == false)
	{
		d3Config.modeArchonEnable = 0;
		d3Config.modeFireBirdEnable = 0;
		((CButton*)GetDlgItem(IDC_WIZFIREBRIDCHECK))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_WIZARCHONCHECK))->EnableWindow(FALSE);
		GenDeviceIdentification(buffer, 999);


		wchar_t bufferAbout[10000] = { 0 };
		swprintf_s(bufferAbout, L"DiabloIIISupport is free, but [Wizard - Meteor Star Pact] feature is limited distribution.\r\nTo get Activation Key, please email to quangxengvn@gmail.com.\r\nYour DeviceID is [%ls].", buffer);
		GetDlgItem(IDC_ABOUT)->SetWindowTextW(bufferAbout);
	}

	d3Config.modeArchonEnable = !d3Config.modeArchonEnable;
	OnBnClickedWizArchoncheck();

	hGlobalHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, GetModuleHandle(NULL), 0);




	return TRUE;  // return TRUE  unless you set the focus to a control
}
void		CDiabloIIISupportDlg::OnPaint()
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
HCURSOR		CDiabloIIISupportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void		CDiabloIIISupportDlg::WinHelp(DWORD dwData, UINT nCmd)
{//prevent help to use F1 

}
void		CDiabloIIISupportDlg::OnHelp()
{
	// TODO: Add your command handler code here
}












/************************************************************************/
/*                                                                      */
/************************************************************************/
void CDiabloIIISupportDlg::OnTimer(UINT_PTR nIdEvent)
{
	if (mainTimerID == nIdEvent)
	{
		if (flagOnProcess == false)
		{
			flagOnProcess = true;
			WCHAR bufferActive[100] = L"Found";
			if (gameStatus.flagInAttackMode)
			{
				swprintf_s(bufferActive, L" AttackMode");
			}

#ifdef _DEBUG
			swprintf_s(bufferActive, L"%d %d %d", gameStatus.flagInAttackMode, gameStatus.flagPotionReady, gameStatus.getStatusTime);
#endif 
			HWND d3Wnd = GetD3Windows();
			RECT d3Rect = { 0 };
			if (d3Wnd == 0)
			{
				bufferActive[0] = NULL;
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
			debugInfo.AppendFormat(L"Diablo III: %ls\r\n	X: %04d     Y: %04d\r\n	W: %04d     H: %04d\r\nCursor: %ls\r\n	X : %04d     Y : %04d\r\n",
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
			if (flagOnWizSingleShot)
			{
				if (d3Config.fullCycleEnable)
				{
					ArchonStarPactCycle(
						d3Config.keyBlackHole,
						d3Config.keyWaveOfForce,
						d3Config.keyMeteor,
						d3Config.keyArchon,
						d3Config.keyPrimary,
						d3Config.keySecondary,
						d3Config.keyForceStand
					);
				}
				else
				{
					ArchonStarPactCastMeteor(
						d3Config.keyMeteor,
						d3Config.keyArchon,
						d3Config.keyPrimary,
						d3Config.keySecondary,
						d3Config.keyForceStand
					);
				}
				flagOnWizSingleShot = false;
				//if (d3Config.lightingBlastEnable)
				//{
				//	mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				//	flagOnHoldRightMouse = true;
				//}

				GetDlgItem(IDC_SINGLESHOTHOTKEYTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
				GetDlgItem(IDC_SINGLESHOTHOTKEYFORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
				GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
				GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
				OnShowSkillKey(IDC_SINGLESHOTHOTKEY, d3Config.keyWizSingleShot);
			}
			GetCurrentDiabloIIStatus(gameStatus);


			/************************************************************************/
			/*                                                                      */
			/************************************************************************/
			if (gameStatus.flagIsOpenMap == false
				&& gameStatus.flagIsOpenSkillTable == false
				&& gameStatus.flagIsOpenUrshi == false
				)
			{
				if (flagOnF2 && gameStatus.flagIsOpenKadala == false && gameStatus.flagIsOpenStash == false && gameStatus.flagInAttackMode)
				{
					GetDlgItem(IDC_SKILL01TIME)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL02TIME)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL03TIME)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL04TIME)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL01CHECK)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL02CHECK)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL03CHECK)->EnableWindow(FALSE);
					GetDlgItem(IDC_SKILL04CHECK)->EnableWindow(FALSE);
					GetDlgItem(IDC_HEALINGCHECK)->EnableWindow(FALSE);
					GetDlgItem(IDC_F2BIGFRAME)->SetWindowTextW(L"Skill (Hotkey F2) - Running");
					if (d3Wnd != 0)
					{

						if (d3Config.skill01Enable)
						{
							skillSlot01Cooldown += mainTimerDelay;
							if (skillSlot01Cooldown >= d3Config.skillSlot01Time && gameStatus.flagInAttackMode)
							{
								SendD3Key(d3Config.keySKill01);
								skillSlot01Cooldown = 0;
							}
						}
						if (d3Config.skill02Enable)
						{
							skillSlot02Cooldown += mainTimerDelay;
							if (skillSlot02Cooldown >= d3Config.skillSlot02Time && gameStatus.flagInAttackMode)
							{
								SendD3Key(d3Config.keySKill02);
								skillSlot02Cooldown = 0;
							}
						}
						if (d3Config.skill03Enable)
						{
							skillSlot03Cooldown += mainTimerDelay;
							if (skillSlot03Cooldown >= d3Config.skillSlot03Time && gameStatus.flagInAttackMode)
							{
								SendD3Key(d3Config.keySKill03);
								skillSlot03Cooldown = 0;
							}
						}
						if (d3Config.skill04Enable)
						{
							skillSlot04Cooldown += mainTimerDelay;
							if (skillSlot04Cooldown >= d3Config.skillSlot04Time && gameStatus.flagInAttackMode)
							{
								SendD3Key(d3Config.keySKill04);
								skillSlot04Cooldown = 0;
							}
						}
						if (d3Config.healingEnable && gameStatus.flagPotionReady)
						{
							SendD3Key(d3Config.keyHealing);
						}
					}
				}
				else
				{
					if (d3Config.skill01Enable) GetDlgItem(IDC_SKILL01TIME)->EnableWindow(TRUE);
					if (d3Config.skill02Enable) GetDlgItem(IDC_SKILL02TIME)->EnableWindow(TRUE);
					if (d3Config.skill03Enable) GetDlgItem(IDC_SKILL03TIME)->EnableWindow(TRUE);
					if (d3Config.skill04Enable) GetDlgItem(IDC_SKILL04TIME)->EnableWindow(TRUE);
					GetDlgItem(IDC_SKILL01CHECK)->EnableWindow(TRUE);
					GetDlgItem(IDC_SKILL02CHECK)->EnableWindow(TRUE);
					GetDlgItem(IDC_SKILL03CHECK)->EnableWindow(TRUE);
					GetDlgItem(IDC_SKILL04CHECK)->EnableWindow(TRUE);
					GetDlgItem(IDC_HEALINGCHECK)->EnableWindow(TRUE);
					GetDlgItem(IDC_F2BIGFRAME)->SetWindowTextW(L"Skill (Hotkey F2)");
				}
				if (flagOnF1 && gameStatus.flagIsOpenKadala == false && gameStatus.flagIsOpenStash == false)
				{
					GetDlgItem(IDC_LEFTMOUSETEXT)->SetWindowText(L"Left mouse (Hotkey F1): \r\n	Running");
					GetDlgItem(IDC_LEFTMOUSETEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_LEFTMOUSETEXTMS)->EnableWindow(FALSE);
					GetDlgItem(IDC_LEFTMOUSETIME)->EnableWindow(FALSE);
					if (d3Wnd != 0)
					{
						leftMouseCooldown += mainTimerDelay;
						if (leftMouseCooldown >= d3Config.leftMouseTime)
						{
							if (ValidToSendD3Click()) SendD3LeftMouseClick();
							else
							{
								::SendMessageW(d3Wnd, WM_KEYDOWN, d3Config.keyForceStand, 0);
								Sleep(10);
								SendD3LeftMouseClick();
								::SendMessageW(d3Wnd, WM_KEYUP, d3Config.keyForceStand, 0);
							}
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
				if (flagOnF3 && (gameStatus.flagInAttackMode || gameStatus.flagIsOpenKadala))
				{
					GetDlgItem(IDC_RIGHTMOUSETEXT)->SetWindowText(L"Right Mouse (Hotkey F3): \r\n	Running");
					GetDlgItem(IDC_RIGHTMOUSETEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_RIGHTMOUSETEXTMS)->EnableWindow(FALSE);
					GetDlgItem(IDC_RIGHTMOUSETIME)->EnableWindow(FALSE);
					if (d3Wnd != 0)
					{
						rightMouseCooldown += mainTimerDelay;
						if (rightMouseCooldown >= d3Config.leftMouseTime)
						{
							if (ValidToSendD3Click()) SendD3RightMouseClick();
							else
							{
								::SendMessageW(d3Wnd, WM_KEYDOWN, d3Config.keyForceStand, 0);
								Sleep(10);
								SendD3RightMouseClick();
								::SendMessageW(d3Wnd, WM_KEYUP, d3Config.keyForceStand, 0);
							}
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
				/* Auto press                                                           */
				/************************************************************************/
				if (gameStatus.flagSkill01IsReadyToAndNeedAutoPress && gameStatus.skill01Key && gameStatus.flagInAttackMode)
				{
					SendD3Key(gameStatus.skill01Key);
				}
				else if (d3Config.profilemodeArchonEnable && gameStatus.flagSkill01IsReadyToAndNeedAutoPress && gameStatus.flagSkill01IsLightningBlast)
				{
					SendD3Key(d3Config.keySKill01);
				}
				if (gameStatus.flagSkill02IsReadyToAndNeedAutoPress && gameStatus.skill02Key && gameStatus.flagInAttackMode)
				{
					SendD3Key(gameStatus.skill02Key);
				}
				if (gameStatus.flagSkill03IsReadyToAndNeedAutoPress && gameStatus.skill03Key && gameStatus.flagInAttackMode)
				{
					SendD3Key(gameStatus.skill03Key);
				}
				if (gameStatus.flagSkill04IsReadyToAndNeedAutoPress && gameStatus.skill04Key && gameStatus.flagInAttackMode)
				{
					SendD3Key(gameStatus.skill04Key);
				}
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
					double		xCubeLeftPage = 583 * d3Scale;
					double		yCubeLeftPage = 840 * d3Scale;
					double		xCubeRightPage = 852 * d3Scale;
					double		yCubeRightPage = 840 * d3Scale;


					int xForgeWeaponTable = 517 * d3Scale;
					int yForgeWeaponTable = 223 * d3Scale;

					int xSalvageTable = 517 * d3Scale;
					int ySalvageTable = 500 * d3Scale;

					int xRepairTable = 517 * d3Scale;
					int yRepairTable = 620 * d3Scale;

					int xRepairButton = 264 * d3Scale;
					int yRepairButton = 594 * d3Scale;

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

							Sleep(250 + (rand() % 10));

							if (flagOnCtrl5) SetD3Mouse(xCubeLeftPage, yCubeLeftPage);
							if (flagOnCtrl5) SendD3LeftMouseClick();
							if (flagOnCtrl5) Sleep(50 + (rand() % 5));

							if (flagOnCtrl5) SetD3Mouse(xCubeRightPage, yCubeRightPage);
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

							Sleep(250 + (rand() % 10));

							if (flagOnCtrl6) SetD3Mouse(xCubeLeftPage, yCubeLeftPage);
							if (flagOnCtrl6) SendD3LeftMouseClick();
							if (flagOnCtrl6) Sleep(50 + (rand() % 5));

							if (flagOnCtrl6) SetD3Mouse(xCubeRightPage, yCubeRightPage);
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
						if (flagOnCtrl9) SetD3Mouse(xForgeWeaponTable, yForgeWeaponTable);
						if (flagOnCtrl9) SendD3LeftMouseClick();
						if (flagOnCtrl9) SetD3Mouse(xSalvageTable, ySalvageTable);
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
							if (flagOnCtrl9) Sleep(50 + (rand() % 5));
						}

						if (flagOnCtrl9) SetD3Mouse(xRepairTable, yRepairTable);
						if (flagOnCtrl9) SendD3LeftMouseClick();
						if (flagOnCtrl9) Sleep(50 + (rand() % 5));
						if (flagOnCtrl9) SetD3Mouse(xRepairButton, yRepairButton);
						if (flagOnCtrl9) SendD3LeftMouseClick();
						if (flagOnCtrl9) Sleep(50 + (rand() % 5));
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
void CDiabloIIISupportDlg::OnLoadConfig()
{
	CFile loadFile;
	if (loadFile.Open(configSavePath, CFile::modeRead | CFile::typeBinary))
	{
		int fileSize = int(loadFile.GetLength());
		if (fileSize > sizeof(d3Config))
		{
			fileSize = sizeof(d3Config);
		}
		loadFile.Read(&d3Config, fileSize);
		loadFile.Close();
		if (d3Config.saveDiabloIIISupportVersion != DiabloIIISupportVersion)
		{
			memset(&d3Config, 0, sizeof(d3Config));
			d3Config.saveDiabloIIISupportVersion = DiabloIIISupportVersion;
			ValidateD3Config();
			OnSaveConfig();
		}
	}
}
void CDiabloIIISupportDlg::OnSaveConfig()
{
	CFile saveFile;
	if (saveFile.Open(configSavePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		saveFile.Write(&d3Config, sizeof(d3Config));
		saveFile.Close();
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CDiabloIIISupportDlg::OnKillFocusLeftMouseTime()
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
		OnSaveConfig();
	}
}
void CDiabloIIISupportDlg::OnKillFocusRightMouseTime()
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
		OnSaveConfig();
	}
}
void CDiabloIIISupportDlg::OnKillFocusSkill01Time()
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
		OnSaveConfig();
	}
}
void CDiabloIIISupportDlg::OnKillFocusSkill02Time()
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
		OnSaveConfig();
	}
}
void CDiabloIIISupportDlg::OnKillFocusSkill03Time()
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
		OnSaveConfig();
	}
}
void CDiabloIIISupportDlg::OnKillFocusSkill04Time()
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
		OnSaveConfig();
	}
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void CDiabloIIISupportDlg::OnShowSkillKey(int idW, wchar_t key)
{
	wchar_t buffer[100] = { 0 };
	if (key == L' ') wcscpy(buffer, L"Space");
	else if (key == VK_SHIFT) wcscpy(buffer, L"Shift");
	else if (key == VK_LBUTTON) wcscpy(buffer, L"LeftMouse");
	else if (key == VK_RBUTTON) wcscpy(buffer, L"RightMouse");
	else swprintf_s(buffer, L"%lc", key);
	GetDlgItem(idW)->SetWindowText(buffer);
}
void CDiabloIIISupportDlg::OnKillFocusSkillKey(int changeID, wchar_t & keySkill)
{
	wchar_t bufferText[1001] = { 0 };
	GetDlgItem(changeID)->GetWindowTextW(bufferText, 999);

	CString tempTrunc = bufferText;
	tempTrunc.Replace(L" ", L"");
	tempTrunc.MakeUpper();
	wcscpy(bufferText, tempTrunc.GetBuffer());
	if (InitStarPactEngine(NULL) == false && InitStarPactEngine(bufferText))
	{
		GetDlgItem(IDC_ABOUT)->SetWindowTextW(L"Create by Bùi Tấn Quang\r\nhttps://github.com/langmaninternet\r\nhttps://www.facebook.com/langmaninternet");
		OnShowSkillKey(changeID, keySkill);
		return;
	}


	int newValue = bufferText[0];
	if (newValue == '`') newValue = '~';
	if (wcscmp(bufferText, L"SPACE") == 0 || newValue == ' ')
	{
		wcscpy(bufferText, L"Space");
		newValue = L' ';
	}
	else if (wcscmp(bufferText, L"SHIFT") == 0)
	{
		wcscpy(bufferText, L"Shift");
		newValue = VK_SHIFT;
	}
	else if (wcscmp(bufferText, L"CTRL") == 0)
	{
		wcscpy(bufferText, L"Ctrl");
		newValue = VK_CONTROL;
	}
	else if (wcscmp(bufferText, L"LEFTMOUSE") == 0 || wcscmp(bufferText, L"LM") == 0)
	{
		wcscpy(bufferText, L"LeftMouse");
		newValue = VK_LBUTTON;
	}
	else if (wcscmp(bufferText, L"RIGHTMOUSE") == 0 || wcscmp(bufferText, L"RM") == 0)
	{
		wcscpy(bufferText, L"RightMouse");
		newValue = VK_RBUTTON;
	}
	else bufferText[1] = 0;

	//	if ((changeID == IDC_PRIMARYSKILLKEY || changeID == IDC_SECONDARYSKILLKEY) && (newValue == VK_RBUTTON || newValue == VK_LBUTTON))
	//	{
	//		MessageBoxW(L"English : Channling Skill Only allow :\r\nABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n0123456789\r\n\r\nVietnamese : Tạm thời các skill channling chưa hỗ trợ chuột trái chuột phải");
	//		OnShowSkillKey(changeID, keySkill);
	//		return;
	//	}


	if (newValue >= 'a' && newValue <= 'z') newValue = 'A' + newValue - 'a';
	if ((newValue >= 'A' && newValue <= 'Z')
		|| (newValue >= '0' && newValue <= '9')
		|| newValue == ' '
		|| newValue == '~'
		|| newValue == VK_SHIFT
		|| newValue == VK_CONTROL
		|| newValue == VK_RBUTTON
		|| newValue == VK_LBUTTON
		)
	{
		if (newValue != keySkill)
		{
			keySkill = newValue;
			OnSaveConfig();
		}
	}
	else
	{
		static int flagAlreadyWarning = 0;
		if (flagAlreadyWarning == 0)
		{
			MessageBoxW(L"English : Only allow :\r\nABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n0123456789\r\n~\r\nSpace\r\nShift\r\nCtrl\r\n\r\n Vietnamese : Chỉ hỗ trợ các kí tự A-Z 0-9 Shift, Space, Ctrl, LeftMouse, RightMouse\r\n Đối với các kí tự điều khiển thì cần bạn gõ đúng chuỗi kí tự vào");
			flagAlreadyWarning = 1;
		}
	}
	OnShowSkillKey(changeID, keySkill);
}
void CDiabloIIISupportDlg::OnKillFocusSkillKey01()
{
	OnKillFocusSkillKey(IDC_SKILLKEY01, d3Config.keySKill01);
}
void CDiabloIIISupportDlg::OnKillFocusSkillKey02()
{
	OnKillFocusSkillKey(IDC_SKILLKEY02, d3Config.keySKill02);
}
void CDiabloIIISupportDlg::OnKillFocusSkillKey03()
{
	OnKillFocusSkillKey(IDC_SKILLKEY03, d3Config.keySKill03);
}
void CDiabloIIISupportDlg::OnKillFocusSkillKey04()
{
	OnKillFocusSkillKey(IDC_SKILLKEY04, d3Config.keySKill04);
}
void CDiabloIIISupportDlg::OnKillfocusHealingKey()
{
	OnKillFocusSkillKey(IDC_HEALINGKEY, d3Config.keyHealing);
}
void CDiabloIIISupportDlg::OnKillFocusForceStandKey()
{
	OnKillFocusSkillKey(IDC_FORCESTANDKEY, d3Config.keyForceStand);
}
void CDiabloIIISupportDlg::OnKillFocusForceMoveKey()
{
	OnKillFocusSkillKey(IDC_FORCEMOVEKEY, d3Config.keyForceMove);
}
void CDiabloIIISupportDlg::OnKillFocusSingleShotHotKey()
{
	OnKillFocusSkillKey(IDC_SINGLESHOTHOTKEY, d3Config.keyWizSingleShot);
}
void CDiabloIIISupportDlg::OnKillFocusMeteorKey()
{
	OnKillFocusSkillKey(IDC_METEORKEY, d3Config.keyMeteor);
}
void CDiabloIIISupportDlg::OnKillFocusArchonKey()
{
	OnKillFocusSkillKey(IDC_ARCHONKEY, d3Config.keyArchon);
}
void CDiabloIIISupportDlg::OnKillFocusBlackHoleKey()
{
	OnKillFocusSkillKey(IDC_BLACKHOLEKEY, d3Config.keyBlackHole);
}
void CDiabloIIISupportDlg::OnKillFocusWaveOfForceKey()
{
	OnKillFocusSkillKey(IDC_WAVEOFFORCEKEY, d3Config.keyWaveOfForce);
}
void CDiabloIIISupportDlg::OnKillFocusPrimarySkillKey()
{
	OnKillFocusSkillKey(IDC_PRIMARYSKILLKEY, d3Config.keyPrimary);
}
void CDiabloIIISupportDlg::OnKillFocusSecondarySkillKey()
{
	OnKillFocusSkillKey(IDC_SECONDARYSKILLKEY, d3Config.keySecondary);
}




void CDiabloIIISupportDlg::OnClickedSkill01Check()
{
	d3Config.skill01Enable = !d3Config.skill01Enable;
	d3Config.profileskill01Enable[d3Config.currentProfile] = d3Config.skill01Enable;
	((CButton*)GetDlgItem(IDC_SKILL01CHECK))->SetCheck(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL01TIME)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL01TEXT)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL01TEXTMS)->EnableWindow(d3Config.skill01Enable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnClickedSkill02Check()
{
	d3Config.skill02Enable = !d3Config.skill02Enable;
	d3Config.profileskill02Enable[d3Config.currentProfile] = d3Config.skill02Enable;
	((CButton*)GetDlgItem(IDC_SKILL02CHECK))->SetCheck(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL02TIME)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL02TEXT)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL02TEXTMS)->EnableWindow(d3Config.skill02Enable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnClickedSkill03Check()
{
	d3Config.skill03Enable = !d3Config.skill03Enable;
	d3Config.profileskill03Enable[d3Config.currentProfile] = d3Config.skill03Enable;
	((CButton*)GetDlgItem(IDC_SKILL03CHECK))->SetCheck(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL03TIME)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL03TEXT)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL03TEXTMS)->EnableWindow(d3Config.skill03Enable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnClickedSkill04Check()
{
	d3Config.skill04Enable = !d3Config.skill04Enable;
	d3Config.profileskill04Enable[d3Config.currentProfile] = d3Config.skill04Enable;
	((CButton*)GetDlgItem(IDC_SKILL04CHECK))->SetCheck(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL04TIME)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL04TEXT)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL04TEXTMS)->EnableWindow(d3Config.skill04Enable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnClickedHealingCheck()
{
	d3Config.healingEnable = !d3Config.healingEnable;
	d3Config.profilehealingEnable[d3Config.currentProfile] = d3Config.healingEnable;
	((CButton*)GetDlgItem(IDC_HEALINGCHECK))->SetCheck(d3Config.healingEnable);
	GetDlgItem(IDC_HEALINGTEXTMS)->EnableWindow(d3Config.healingEnable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnBnClickedWizArchoncheck()
{
	d3Config.modeArchonEnable = !d3Config.modeArchonEnable;
	d3Config.profilemodeArchonEnable[d3Config.currentProfile] = d3Config.modeArchonEnable;
	GetDlgItem(IDC_ARCHONTEXT)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_ARCHONKEY)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_BLACKHOLETEXT)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_BLACKHOLEKEY)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_WAVEOFFORCEKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_WAVEOFFORCEKEY)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_PRIMARYSKILLKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_PRIMARYSKILLKEY)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_SECONDARYSKILLKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
	GetDlgItem(IDC_SECONDARYSKILLKEY)->EnableWindow(d3Config.modeArchonEnable);
	if (d3Config.modeArchonEnable)
	{
		d3Config.modeFireBirdEnable = 0;
		((CButton*)GetDlgItem(IDC_WIZFIREBRIDCHECK))->SetCheck(0);
	}
	GetDlgItem(IDC_METEORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_METEORKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYFORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnBnClickedWizFireBridCheck()
{
	d3Config.modeFireBirdEnable = !d3Config.modeFireBirdEnable;
	d3Config.profilemodeFireBirdEnable[d3Config.currentProfile] = !d3Config.modeFireBirdEnable;
	if (d3Config.modeFireBirdEnable)
	{
		d3Config.modeArchonEnable = 0;
		((CButton*)GetDlgItem(IDC_WIZARCHONCHECK))->SetCheck(0);
		GetDlgItem(IDC_ARCHONTEXT)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_ARCHONKEY)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_BLACKHOLETEXT)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_BLACKHOLEKEY)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_WAVEOFFORCEKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_WAVEOFFORCEKEY)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_PRIMARYSKILLKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_PRIMARYSKILLKEY)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_SECONDARYSKILLKEYTEXT)->EnableWindow(d3Config.modeArchonEnable);
		GetDlgItem(IDC_SECONDARYSKILLKEY)->EnableWindow(d3Config.modeArchonEnable);
	}
	GetDlgItem(IDC_METEORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_METEORKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYFORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnBnClickedSingleshothotcastmeteoronly()
{
	d3Config.fullCycleEnable = !d3Config.fullCycleEnable;
	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY))->SetCheck(d3Config.fullCycleEnable == false);
	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE))->SetCheck(d3Config.fullCycleEnable);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnBnClickedSingleshothotcastfullcycle()
{
	d3Config.fullCycleEnable = !d3Config.fullCycleEnable;
	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY))->SetCheck(d3Config.fullCycleEnable == false);
	((CButton*)GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE))->SetCheck(d3Config.fullCycleEnable);
	OnSaveConfig();
}




void CDiabloIIISupportDlg::OnKillFocusProfileName()
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
void CDiabloIIISupportDlg::OnBnClickedProfile()
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
	d3Config.modeFireBirdEnable = d3Config.profilemodeFireBirdEnable[d3Config.currentProfile];
	d3Config.modeArchonEnable = d3Config.profilemodeArchonEnable[d3Config.currentProfile];





	/************************************************************************/
	/* Force                                                                */
	/************************************************************************/
	d3Config.healingTime = 50;







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


	GetDlgItem(IDC_SKILL01TIME)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TIME)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TIME)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TIME)->EnableWindow(d3Config.skill04Enable);
	GetDlgItem(IDC_SKILL01TEXT)->EnableWindow(d3Config.skill01Enable);
	GetDlgItem(IDC_SKILL02TEXT)->EnableWindow(d3Config.skill02Enable);
	GetDlgItem(IDC_SKILL03TEXT)->EnableWindow(d3Config.skill03Enable);
	GetDlgItem(IDC_SKILL04TEXT)->EnableWindow(d3Config.skill04Enable);
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


	GetDlgItem(IDC_METEORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_METEORKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEYFORTEXT)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTMETEORONLY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTCASTFULLCYCLE)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	GetDlgItem(IDC_SINGLESHOTHOTKEY)->EnableWindow(d3Config.modeFireBirdEnable || d3Config.modeArchonEnable);
	((CButton*)GetDlgItem(IDC_WIZFIREBRIDCHECK))->SetCheck(d3Config.modeFireBirdEnable);
	((CButton*)GetDlgItem(IDC_WIZARCHONCHECK))->SetCheck(d3Config.modeArchonEnable);

	d3Config.modeArchonEnable = !d3Config.modeArchonEnable;
	OnBnClickedWizArchoncheck();

	CString currentProfileName = L"> ";
	currentProfileName += d3Config.profileName[d3Config.currentProfile];
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(currentProfileName);
	GetDlgItem(IDC_PROFILENAME)->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	OnSaveConfig();
}
void CDiabloIIISupportDlg::OnBnClickedProfile01()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 0;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile02()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 1;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile03()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 2;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile04()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 3;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile05()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 4;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile06()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 5;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile07()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 6;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile08()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 7;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile09()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 8;
	OnBnClickedProfile();
}
void CDiabloIIISupportDlg::OnBnClickedProfile10()
{
	GetDlgItem(profileID[d3Config.currentProfile])->SetWindowTextW(d3Config.profileName[d3Config.currentProfile]);
	d3Config.currentProfile = 9;
	OnBnClickedProfile();
}

