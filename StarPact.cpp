#include "stdafx.h"
#include <Windows.h>
#include <Wingdi.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <list>
#include "StarPact.h"




Win32GDI					w32gdi;
DiabloIIIStatusStruct		d3GameStatus;
bool						flagOnWizCycle;



/************************************************************************/
/* Public - StarPact Engine                                             */
/************************************************************************/
void			StartStarPact(void)
{
	flagOnWizCycle = true;
}
void			StopStarPact(void)
{
	flagOnWizCycle = false;
}





void			ArchonStarPactSCycle(wchar_t blackHoleKey, wchar_t wayOfForceKey, wchar_t meteorKey, wchar_t archonKey, wchar_t primaryKey, wchar_t secondaryKey, wchar_t forceStandKey)
{
	static int onProcress = false;
	if (onProcress == false)
	{
		onProcress = true;
		const int holdLparam = 0x20000000;
		HWND d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
		if (d3Wnd == NULL) d3Wnd = FindWindowW(L"D3 Main Window Class", NULL);
		if (d3Wnd == NULL) d3Wnd = FindWindowW(NULL, L"Diablo III");
		if (d3Wnd != NULL && d3Wnd == GetForegroundWindow())
		{
			POINT point = { 0 };
			GetCursorPos(&point);

			RECT d3Rect = { 0 };
			GetWindowRect(d3Wnd, &d3Rect);


			/************************************************************************/
			/* Force Stand                                                          */
			/************************************************************************/
			if (flagOnWizCycle) SendMessageW(d3Wnd, WM_KEYDOWN, forceStandKey, 0);
			if (flagOnWizCycle) Sleep(50);



			/************************************************************************/
			/* Start Primary Channeling                                             */
			/************************************************************************/
			if (primaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, primaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(1000);



			/************************************************************************/
			/* Cast Black Hole                                                      */
			/************************************************************************/
			if (blackHoleKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (blackHoleKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, blackHoleKey, 0);
				if (flagOnWizCycle) Sleep(100);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, blackHoleKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			if (flagOnWizCycle) Sleep(700);




			/************************************************************************/
			/* Cast Way of Force                                                    */
			/************************************************************************/
			if (wayOfForceKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (wayOfForceKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, wayOfForceKey, 0);
				if (flagOnWizCycle) Sleep(100);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, wayOfForceKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			if (flagOnWizCycle) Sleep(300);



			/************************************************************************/
			/* End of Force Stand                                                   */
			/************************************************************************/
			if (primaryKey == VK_LBUTTON)
			{
				mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
			}
			else
			{
				SendMessage(d3Wnd, WM_KEYUP, primaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(50);
			SendMessage(d3Wnd, WM_KEYUP, forceStandKey, 0);
			if (flagOnWizCycle) Sleep(50);
			/************************************************************************/
			/* Cast Meteor                                                          */
			/************************************************************************/
			if (meteorKey == VK_LBUTTON)
			{
				SendMessage(d3Wnd, WM_KEYDOWN, forceStandKey, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				SendMessage(d3Wnd, WM_KEYUP, forceStandKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (meteorKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, meteorKey, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, meteorKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}



			/************************************************************************/
			/* Start Secondary Channeling                                           */
			/************************************************************************/
			if (secondaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (secondaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, secondaryKey, holdLparam);
			}
			if (flagOnWizCycle) Sleep(900);



			/************************************************************************/
			/* Active Archon                                                        */
			/************************************************************************/
			for (int iloop = 0; iloop < 10; iloop++)
			{
				if (archonKey == VK_LBUTTON)
				{
					SendMessage(d3Wnd, WM_KEYDOWN, forceStandKey, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
					SendMessage(d3Wnd, WM_KEYUP, forceStandKey, 0);
					if (flagOnWizCycle) Sleep(50);
				}
				else if (archonKey == VK_RBUTTON)
				{
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
				}
				else
				{
					if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, archonKey, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, archonKey, 0);
					if (flagOnWizCycle) Sleep(50);
				}
			}


			/************************************************************************/
			/* Free key                                                             */
			/************************************************************************/
			if (secondaryKey == VK_LBUTTON)
			{
				mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
			}
			else if (secondaryKey == VK_RBUTTON)
			{
				mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
			}
			else
			{
				SendMessage(d3Wnd, WM_KEYUP, secondaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(50);

			SendMessage(d3Wnd, WM_KEYUP, forceStandKey, 0);
			if (flagOnWizCycle) Sleep(50);
		}
	}
	onProcress = false;
}


































































/************************************************************************/
/* ArchonStarPactFullCycle                                              */
/************************************************************************/
void			ArchonStarPactFullCycle(wchar_t blackHoleKey, wchar_t wayOfForceKey, wchar_t meteorKey, wchar_t archonKey, wchar_t primaryKey, wchar_t secondaryKey, wchar_t forceStandKey)
{
	static int onProcress = false;
	if ( onProcress == false)
	{
		onProcress = true;
		const int holdLparam = 0x20000000;
		HWND d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
		if (d3Wnd != NULL && d3Wnd == GetForegroundWindow())
		{
			POINT point = { 0 };
			GetCursorPos(&point);

			RECT d3Rect = { 0 };
			GetWindowRect(d3Wnd, &d3Rect);


			/************************************************************************/
			/* Force Stand                                                          */
			/************************************************************************/
			if (flagOnWizCycle) SendMessageW(d3Wnd, WM_KEYDOWN, forceStandKey, 0);
			if (flagOnWizCycle) Sleep(50);



			/************************************************************************/
			/* Start Primary Channeling                                             */
			/************************************************************************/
			if (primaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, primaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(100);
			if (flagOnWizCycle) Sleep(2000);




			/************************************************************************/
			/* Cast Black Hole                                                      */
			/************************************************************************/
			if (blackHoleKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (blackHoleKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, blackHoleKey, 0);
				if (flagOnWizCycle) Sleep(100);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, blackHoleKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			if (flagOnWizCycle) Sleep(700);



			/************************************************************************/
			/* Cast Way of Force                                                    */
			/************************************************************************/
			if (wayOfForceKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (wayOfForceKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, wayOfForceKey, 0);
				if (flagOnWizCycle) Sleep(100);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, wayOfForceKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			if (flagOnWizCycle) Sleep(300);



			/************************************************************************/
			/*                                                                      */
			/************************************************************************/
			if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, forceStandKey, holdLparam);
			if (flagOnWizCycle) Sleep(50);
			if (primaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, primaryKey, holdLparam);
			}
			if (flagOnWizCycle) Sleep(1000);




			/************************************************************************/
			/* Cast Meteor                                                          */
			/************************************************************************/
			if (meteorKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else if (meteorKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
				if (flagOnWizCycle) Sleep(50);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, meteorKey, 0);
				if (flagOnWizCycle) Sleep(50);
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, meteorKey, 0);
				if (flagOnWizCycle) Sleep(50);
			}


			/************************************************************************/
			/* Start Primary Channeling                                             */
			/************************************************************************/
			if (primaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, primaryKey, holdLparam);
			}
			if (flagOnWizCycle) Sleep(400);



			/************************************************************************/
			/* Start Secondary Channeling                                           */
			/************************************************************************/
			if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, forceStandKey, holdLparam);
			if (flagOnWizCycle) Sleep(50);
			if (secondaryKey == VK_LBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
			}
			else if (secondaryKey == VK_RBUTTON)
			{
				if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
			}
			else
			{
				if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, secondaryKey, holdLparam);
			}
			if (flagOnWizCycle) Sleep(400);



			/************************************************************************/
			/* Active Archon                                                        */
			/************************************************************************/
			if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, forceStandKey, holdLparam);
			if (flagOnWizCycle) Sleep(50);
			for (int iloop = 0; iloop < 10; iloop++)
			{
				if (archonKey == VK_LBUTTON)
				{
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
				}
				else if (archonKey == VK_RBUTTON)
				{
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
					if (flagOnWizCycle) Sleep(50);
				}
				else
				{
					if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYDOWN, archonKey, 0);
					if (flagOnWizCycle) Sleep(50);
					if (flagOnWizCycle) SendMessage(d3Wnd, WM_KEYUP, archonKey, 0);
					if (flagOnWizCycle) Sleep(50);
				}
			}


			/************************************************************************/
			/* Free key                                                             */
			/************************************************************************/
			if (primaryKey == VK_LBUTTON)
			{
				mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
			}
			else if (primaryKey == VK_RBUTTON)
			{
				mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
			}
			else
			{
				SendMessage(d3Wnd, WM_KEYUP, primaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(50);


			if (secondaryKey == VK_LBUTTON)
			{
				mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
			}
			else if (secondaryKey == VK_RBUTTON)
			{
				mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
			}
			else
			{
				SendMessage(d3Wnd, WM_KEYUP, secondaryKey, 0);
			}
			if (flagOnWizCycle) Sleep(50);

			SendMessage(d3Wnd, WM_KEYUP, forceStandKey, 0);
			if (flagOnWizCycle) Sleep(50);
		}
	}
	onProcress = false;
}
/************************************************************************/
/* D3 Game status                                                       */
/************************************************************************/
void		GetCurrentDiabloIIStatus(void)
{
	/************************************************************************/
	/* Giá trị mặc định , cần để bảo đảm tool vẫn chạy trong trường hợp xấu */
	/************************************************************************/
	d3GameStatus.flagInAttackMode = true;
	d3GameStatus.flagPotionReady = true;
	d3GameStatus.flagIsOpenMap = false;
	d3GameStatus.flagIsOpenSkillTable = false;
	d3GameStatus.flagIsOpenKadala = false;
	d3GameStatus.flagIsOpenUrshi = false;
	d3GameStatus.flagIsOpenStash = false;
	d3GameStatus.flagIsWizard = false;
	d3GameStatus.flagIsDemonHunter = false;
	d3GameStatus.flagIsMonk = false;
	d3GameStatus.flagInArchonMode = false;
	d3GameStatus.flagSkill01IsReadyToAndNeedAutoPress = false;
	d3GameStatus.flagSkill02IsReadyToAndNeedAutoPress = false;
	d3GameStatus.flagSkill03IsReadyToAndNeedAutoPress = false;
	d3GameStatus.flagSkill04IsReadyToAndNeedAutoPress = false;
#ifdef _DEBUG
	d3GameStatus.getStatusTime = 0;
	DWORD		startTime = GetTickCount();
#endif


	if (w32gdi.ValidMode())
	{
		w32gdi.CaptureDesktop();
		d3GameStatus.flagIsOpenMap = w32gdi.D3IsViewMap();
		d3GameStatus.flagIsOpenSkillTable = w32gdi.D3IsOpenSkillTable();
		d3GameStatus.flagIsOpenKadala = w32gdi.D3IsOpenKadala();
		d3GameStatus.flagIsOpenUrshi = w32gdi.D3IsOpenUrshi();
		d3GameStatus.flagIsOpenStash = w32gdi.D3IsOpenStash();
		//tọa độ cây kiếm 1155 1022
		//đứng im == 0x297EB1
		//đánh nhau == 0x16435E
		if (w32gdi.GetPixel(1155, 1022) == 0x297EB1 || d3GameStatus.flagIsOpenSkillTable) d3GameStatus.flagInAttackMode = false;

		//tọa độ bình máu
		//sẵn sàng 0x080808
		//cool down 0x020202
		if (w32gdi.GetPixel(1062, 1001) == 0x020202) d3GameStatus.flagPotionReady = false;


		//LightningBlast
		if (w32gdi.D3Skill01IsLightningBlastReady())
		{
			d3GameStatus.flagSkill01IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagInArchonMode = true;
			d3GameStatus.flagIsWizard = true;
			StopStarPact();
		}
		else if (d3GameStatus.flagIsWizard == false)
		{
			d3GameStatus.flagSkill01IsReadyToAndNeedAutoPress = w32gdi.D3Skill01IsShadowPowerAndReady();
			if (d3GameStatus.flagSkill01IsReadyToAndNeedAutoPress)
			{
				d3GameStatus.flagIsDemonHunter = true;
			}
		}

		//Skill02
		if (w32gdi.D3Skill02IsArchonSlowTimeAndReady())
		{
			d3GameStatus.flagSkill02IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagIsWizard = true;
			StopStarPact();
		}
		else if (d3GameStatus.flagIsWizard == false && d3GameStatus.flagIsMonk == false && w32gdi.D3Skill02IsShadowPowerAndReady())
		{
			d3GameStatus.flagSkill02IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagIsDemonHunter = true;
		}


		//Skill03
		if (d3GameStatus.flagIsWizard == false && d3GameStatus.flagIsMonk == false && w32gdi.D3Skill03IsShadowPowerAndReady())
		{
			d3GameStatus.flagSkill03IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagIsDemonHunter = true;
		}



		//Skill04
		if (d3GameStatus.flagIsWizard == false && d3GameStatus.flagIsMonk == false && w32gdi.D3Skill04IsShadowPowerAndReady())
		{
			d3GameStatus.flagSkill04IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagIsDemonHunter = true;
		}
		if (d3GameStatus.flagIsWizard == false && d3GameStatus.flagIsDemonHunter == false && w32gdi.D3Skill04IsSweepingWindReady())
		{
			d3GameStatus.flagSkill04IsReadyToAndNeedAutoPress = true;
			d3GameStatus.flagIsMonk = true;
		}

		if (w32gdi.D3Skill01KeyIs1()) d3GameStatus.skill01Key = '1';
		else if (w32gdi.D3Skill01KeyIsQ()) d3GameStatus.skill01Key = 'Q';

		if (w32gdi.D3Skill03KeyIs2()) d3GameStatus.skill02Key = '2';
		else if (w32gdi.D3Skill02KeyIsW()) d3GameStatus.skill02Key = 'W';

		if (w32gdi.D3Skill03KeyIs3()) d3GameStatus.skill03Key = '3';
		else if (w32gdi.D3Skill03KeyIsE()) d3GameStatus.skill03Key = 'E';

		if (w32gdi.D3Skill04KeyIs4()) d3GameStatus.skill04Key = '4';
		else if (w32gdi.D3Skill04KeyIsR()) d3GameStatus.skill04Key = 'R';


	}
#ifdef _DEBUG
	d3GameStatus.getStatusTime = GetTickCount() - startTime;
#endif
}
void		PreloadSalvageItem(int * preloadSalvageSlot, int preloadSalvageSlotSize)
{
	if (w32gdi.ValidMode())
	{
		w32gdi.CaptureDesktop();
		int			xIventoryArray[60] = { 1428 , 1428 , 1428 , 1428 , 1428 , 1428 , 1478 , 1478 , 1478 , 1478 , 1478 , 1478 , 1529 , 1529 , 1529 , 1529 , 1529 , 1529 , 1579 , 1579 , 1579 , 1579 , 1579 , 1579 , 1630 , 1630 , 1630 , 1630 , 1630 , 1630 , 1680 , 1680 , 1680 , 1680 , 1680 , 1680 , 1731 , 1731 , 1731 , 1731 , 1731 , 1731 , 1781 , 1781 , 1781 , 1781 , 1781 , 1781 , 1831 , 1831 , 1831 , 1831 , 1831 , 1831 , 1881 , 1881 , 1881 , 1881 , 1881 , 1881 };
		int			yIventoryArray[60] = { 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 , 584 , 634 , 684 , 734 , 784 , 833 };
		for (int ip = 0; ip < 60 && ip < preloadSalvageSlotSize; ip++)
		{
			int color1 = w32gdi.GetPixel(xIventoryArray[ip], yIventoryArray[ip]);
			int color2 = w32gdi.GetPixel(xIventoryArray[ip] + 1, yIventoryArray[ip] + 1);
			int color3 = w32gdi.GetPixel(xIventoryArray[ip] + 1, yIventoryArray[ip] - 1);
			int color4 = w32gdi.GetPixel(xIventoryArray[ip] - 1, yIventoryArray[ip] + 1);
			int color5 = w32gdi.GetPixel(xIventoryArray[ip] - 1, yIventoryArray[ip] - 1);

			if ((color1 == 0x80D10/* R16 G13 B8*/ || color1 == 0x80E10/* R16 G14 B8*/ || color1 == 0x80F10/* R16 G15 B8*/)
				&& (color2 == 0x80D10/* R16 G13 B8*/ || color2 == 0x80E10/* R16 G14 B8*/ || color2 == 0x80F10/* R16 G15 B8*/)
				&& (color3 == 0x80D10/* R16 G13 B8*/ || color3 == 0x80E10/* R16 G14 B8*/ || color3 == 0x80F10/* R16 G15 B8*/)
				&& (color4 == 0x80D10/* R16 G13 B8*/ || color4 == 0x80E10/* R16 G14 B8*/ || color4 == 0x80F10/* R16 G15 B8*/)
				&& (color5 == 0x80D10/* R16 G13 B8*/ || color5 == 0x80E10/* R16 G14 B8*/ || color5 == 0x80F10/* R16 G15 B8*/)
				)
			{
				preloadSalvageSlot[ip] = 0;
			}
		}
	}
}

