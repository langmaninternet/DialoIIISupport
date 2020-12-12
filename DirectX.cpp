#include "stdafx.h"
#include "DirectX.h"
#include <Windows.h>
#include <iostream>

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include "d3d9.h"
#include "d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



wchar_t overlayStr[1000] = L"";
extern  bool				flagOnWizCycle;
IDirect3DDevice9Ex* p_Device = 0;
ID3DXFont* pFont;
//ID3DXLine* p_Line;
HWND overlayhWnd = NULL;


bool				IsD3WindowActive(void);
void				DrawString(const wchar_t* String, int x, int y, int a, int r, int g, int b, ID3DXFont* font)
{
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	font->DrawTextW(0, String, wcslen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}
HWND				GetTargetWindows(void)
{
	return FindWindowW(L"D3 Main Window Class", L"Diablo III");
}
void				Render(HWND targetWnd)
{

	if (overlayStr[0] != NULL)
	{
		p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		p_Device->BeginScene();

		//Drawing Stuff
		DrawString(overlayStr, 0, 10, 255, 255, 255, 0, pFont);


		p_Device->EndScene();
		p_Device->PresentEx(0, 0, 0, 0, 0);
	}
}















/************************************************************************/
/*                                                                      */
/************************************************************************/
int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
int desktopHeight = GetSystemMetrics(SM_CYSCREEN);
void					DirectXInit(HWND hWnd)
{
	IDirect3D9Ex* p_Object = 0;
	if (Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object) == S_OK)
	{
		D3DPRESENT_PARAMETERS	p_Params;
		ZeroMemory(&p_Params, sizeof(p_Params));
		p_Params.Windowed = TRUE;
		p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		p_Params.hDeviceWindow = hWnd;
		p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
		p_Params.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
		p_Params.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
		p_Params.EnableAutoDepthStencil = TRUE;
		p_Params.AutoDepthStencilFormat = D3DFMT_D16;
		p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device);
		D3DXCreateFontW(p_Device, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);

		//if (!p_Line) D3DXCreateLine(p_Device, &p_Line);
	}
}
LRESULT CALLBACK		OverlayWindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	const MARGINS desktopMargin = { 0, 0, desktopWidth, desktopHeight };
	switch (Message)
	{
	case WM_PAINT:
		Render(GetTargetWindows());
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &desktopMargin);
		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void					SetWindowToTarget(HWND* hWnd)
{
	bool		IsEnableArchon(void);
	while (true)
	{
		if (/*overlayhWnd*/ *hWnd != NULL)
		{

			HWND targetWnd = GetTargetWindows();
			if (targetWnd && targetWnd == GetForegroundWindow() /*&& IsEnableArchon() && flagOnWizCycle == false*/)
			{
				ShowWindow(/*overlayhWnd*/ *hWnd, SW_SHOW);
				RECT targetSize;
				GetWindowRect(targetWnd, &targetSize);
				desktopWidth = targetSize.right - targetSize.left;
				desktopHeight = targetSize.bottom - targetSize.top;
				DWORD dwStyle = GetWindowLong(targetWnd, GWL_STYLE);
				if (dwStyle & WS_BORDER)
				{
					targetSize.top += 23;
					desktopHeight -= 23;
				}
				MoveWindow(/*overlayhWnd*/ *hWnd, targetSize.left, targetSize.top, desktopWidth, desktopHeight, true);
			}
			else
			{
				MoveWindow(/*overlayhWnd*/ *hWnd, 0, 0, 0, 0, true);
				ShowWindow(/*overlayhWnd*/ *hWnd, SW_HIDE);
			}
		}
		Sleep(10);
	}
}
void					InitOverlayWindows(void)
{
	HWND targetWnd = GetDesktopWindow();
	if (targetWnd)
	{
		const wchar_t overlayWindowName[256] = L"Overlay";
		WNDCLASSEX wClass;
		wClass.cbClsExtra = NULL;
		wClass.cbSize = sizeof(WNDCLASSEX);
		wClass.cbWndExtra = NULL;
		wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		wClass.hCursor = LoadCursor(0, IDC_ARROW);
		wClass.hIcon = LoadIcon(0, 0);
		wClass.hIconSm = LoadIcon(0, 0);
		wClass.hInstance = /*hInstance*/ 0;
		wClass.lpfnWndProc = OverlayWindowProc;
		wClass.lpszClassName = overlayWindowName;
		wClass.lpszMenuName = overlayWindowName;
		wClass.style = CS_VREDRAW | CS_HREDRAW;

		if (RegisterClassEx(&wClass))
		{
			RECT targetSize;
			GetWindowRect(targetWnd, &targetSize);
			desktopWidth = targetSize.right - targetSize.left;
			desktopHeight = targetSize.bottom - targetSize.top;
			overlayhWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, overlayWindowName, overlayWindowName, WS_POPUP, 1, 1, desktopWidth, desktopHeight, 0, 0, 0, 0);
			SetLayeredWindowAttributes(overlayhWnd, 0, 1, LWA_ALPHA);
			SetLayeredWindowAttributes(overlayhWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
			ShowWindow(overlayhWnd, SW_SHOW);
			DirectXInit(overlayhWnd);


			for (;;)
			{
				MSG Message;
				if (PeekMessage(&Message, overlayhWnd, 0, 0, PM_REMOVE))
				{
					DispatchMessage(&Message);
					TranslateMessage(&Message);
				}
				Sleep(1);
			}
		}
	}
}
void					CreateOverlay(void)
{
	if (overlayhWnd == NULL)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitOverlayWindows, 0, 0, 0);
		static bool startedAim = false;
		if (startedAim == false)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, (LPVOID)&overlayhWnd, 0, 0);
			startedAim = true;
		}
	}
}
void					DestroyOverlay(void)
{
	if (overlayhWnd)
	{
		SendMessage(overlayhWnd, WM_DESTROY, 0, 0);
		overlayhWnd = NULL;
	}

}


