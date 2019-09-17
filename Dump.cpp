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
extern Win32GDI w32gdi;





#ifdef _DEBUG


bool		HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24)
{
	uint32_t Width = Area.right - Area.left;
	uint32_t Height = Area.bottom - Area.top;
	BITMAPINFO Info;
	BITMAPFILEHEADER Header;
	memset(&Info, 0, sizeof(Info));
	memset(&Header, 0, sizeof(Header));
	Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.bmiHeader.biWidth = Width;
	Info.bmiHeader.biHeight = Height;
	Info.bmiHeader.biPlanes = 1;
	Info.bmiHeader.biBitCount = BitsPerPixel;
	Info.bmiHeader.biCompression = BI_RGB;
	Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
	Header.bfType = 0x4D42;
	Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	char* Pixels = NULL;
	HDC MemDC = CreateCompatibleDC(Context);
	HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
	DeleteObject(SelectObject(MemDC, Section));
	BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
	DeleteDC(MemDC);
	std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
	if (hFile.is_open())
	{
		hFile.write((char*)&Header, sizeof(Header));
		hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
		hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
		hFile.close();
		DeleteObject(Section);
		return true;
	}
	DeleteObject(Section);
	return false;
}




void		StarPactDumpSkill01(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkill01.txt", "wb");
		fprintf(logFile, "bool D3Skill01Is????AndReady(void)\n{\n");


		//skill 01 635  1004 - Half 681 1029 
		const int			xleft = 635;
		const int			ytop = 1004;
		const int			xright = 681;
		const int			ybottom = 1029;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{

						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}




		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpSkill02(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkill02.txt", "wb");
		fprintf(logFile, "bool D3Skill02Is????AndReady(void)\n{\n");


		//skill 02 702  1004 - Half 748 1029 
		const int			xleft = 702;
		const int			ytop = 1004;
		const int			xright = 748;
		const int			ybottom = 1029;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}




		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpSkill03(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkill03.txt", "wb");
		fprintf(logFile, "bool D3Skill03Is????AndReady(void)\n{\n");

		//skill 03 768  1004 - Half 814 1029 
		const int			xleft = 768;
		const int			ytop = 1004;
		const int			xright = 814;
		const int			ybottom = 1029;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}






		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpSkill04(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkill04.txt", "wb");
		fprintf(logFile, "bool D3Skill04Is????AndReady(void)\n{\n");


		//skill 04 834  1003 - Half 881 1029 
		const int			xleft = 834;
		const int			ytop = 1003;
		const int			xright = 881;
		const int			ybottom = 1029;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}




		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpSkillLeft(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkillLeft.txt", "wb");
		fprintf(logFile, "bool D3SkillLeftMouseIs????AndReady(void)\n{\n");


		//left     905  1006 - Half 951 1030
		const int			xleft = 905;
		const int			ytop = 1006;
		const int			xright = 951;
		const int			ybottom = 1030;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}




		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpSkillRight(void)
{
	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);




	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\DumpSkillRight.txt", "wb");
		fprintf(logFile, "bool D3SkillRightMouseIs????AndReady(void)\n{\n");


		//right    970  1006 - Half 1016 1030
		const int			xleft = 970;
		const int			ytop = 1006;
		const int			xright = 1016;
		const int			ybottom = 1030;

		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}
		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						/*soft break*/
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}






		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}
void		StarPactDumpData(void)
{
	//skill 01 635  1004 - Half 681 1029 
	//skill 02 702  1004 - Half 748 1029 
	//skill 03 768  1004 - Half 814 1029 
	//skill 04 835  1004 - Half 881 1029 
	//left     905  1006 - Half 951 1030
	//right    970  1006 - Half 1016 1030

	StarPactDumpSkill01();
	StarPactDumpSkill02();
	StarPactDumpSkill03();
	StarPactDumpSkill04();
	StarPactDumpSkillLeft();
	StarPactDumpSkillRight();

	static HBITMAP		hBmp = NULL;
	static HDC			hMemDC = NULL;
	static RECT			rectDesktop;
	if (hBmp == NULL || hMemDC == NULL)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		if (hdcDesktop != NULL)
		{
			GetWindowRect(hDesktop, &rectDesktop);
			hMemDC = CreateCompatibleDC(hdcDesktop);
			if (hMemDC != NULL)
			{
				HBITMAP		hBmp = CreateCompatibleBitmap(hdcDesktop, rectDesktop.right, rectDesktop.bottom);
				if (hBmp != NULL)
				{
					SelectObject(hMemDC, hBmp);
				}
				else
				{
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}
			}
			ReleaseDC(hDesktop, hdcDesktop);
		}
	}

	HWND	d3Wnd = FindWindowW(L"D3 Main Window Class", L"Diablo III");
	RECT	d3rect;
	GetClientRect(d3Wnd, &d3rect);


	if (hMemDC != NULL
		&& d3rect.top == 0
		&& d3rect.left == 0
		&& d3rect.right == 1920
		&& d3rect.bottom == 1080
		&& rectDesktop.top == 0
		&& rectDesktop.left == 0
		&& rectDesktop.right == 1920
		&& rectDesktop.bottom == 1080
		)
	{
		HWND		hDesktop = GetDesktopWindow();
		HDC			hdcDesktop = GetWindowDC(hDesktop);
		BitBlt(hMemDC, 0, 0, rectDesktop.right, rectDesktop.bottom, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hDesktop, hdcDesktop);

		HDCToFile("D:\\Work\\Dump.bmp", hMemDC, rectDesktop);
		FILE *logFile = NULL;
		fopen_s(&logFile, "D:\\Work\\Dump.txt", "wb");
		fprintf(logFile, "bool D3Is????(void)\n{\n");


		//				fprintf(logFile, "\n\n\n");
		//				int xarr[10] = { 1403,1453,1504,1554,1605,1655,1706,1756,1806,1856 };
		//				int yarr[6] = { 559 , 609, 659, 709, 759, 808 };
		//				//fprintf(logFile, "int			yIventoryArray[60] = { ");
		//				std::set<int> primalColor;
		//				for (int ix = 0; ix < 10; ix++)
		//				{
		//					for (int iy = 0; iy < 6; iy++)
		//					{
		//						int xdata = xarr[ix] + 25;
		//						//fprintf(logFile, "int (%d * d3WidthScale), ", xdata);
		//				
		//						int ydata = yarr[iy] + 25;
		//						//fprintf(logFile, "int (%d * d3HeightScale), ", ydata);
		//				
		//						//fprintf(logFile, "1,");
		//				
		//						primalColor.insert(w32gdi.GetPixel(xdata, ydata));
		//						primalColor.insert(w32gdi.GetPixel(xdata + 1, ydata + 1));
		//						primalColor.insert(w32gdi.GetPixel(xdata + 1, ydata - 1));
		//						primalColor.insert(w32gdi.GetPixel(xdata - 1, ydata + 1));
		//						primalColor.insert(w32gdi.GetPixel(xdata - 1, ydata - 1));
		//					}
		//				}
		//				
		//				
		//				for (auto color : primalColor)
		//				{
		//					fprintf(logFile, "0x%X/* R%d G%d B%d*/\n", color, GetRValue(color), GetGValue(color), GetBValue(color));
		//				}
		//				
		//				fprintf(logFile, " };");
		//				
		//				
		//				fprintf(logFile, "\n\n\n");




	
		// 855 1062
		// 865 1072

		const int			xleft = 855;
		const int			ytop = 1062;
		const int			xright = 865;
		const int			ybottom = 1072;
		static std::set<int>	bitmapArray[xright - xleft][ybottom - ytop];
		for (int ix = xleft; ix < xright; ix++)
		{
			for (int iy = ytop; iy < ybottom; iy++)
			{
				int color = GetPixel(hMemDC, ix, iy);
				bitmapArray[ix - xleft][iy - ytop].insert(color);
			}
		}


		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (bitmapArray[ix - xleft][iy - ytop].size() > 1)
					{
						fprintf(logFile, "int color = 0;\n");
						ix = xright;
						iy = ybottom;
					}
				}
			}
		}

		for (int isize = 1; isize <= 3; isize++)
		{
			for (int ix = xleft; ix < xright; ix++)
			{
				for (int iy = ytop; iy < ybottom; iy++)
				{
					if (isize == 1 && bitmapArray[ix - xleft][iy - ytop].size() == 1)
					{
						fprintf(logFile, "if (GetPixel(%d, %d) != 0X%X) return false;\n", ix, iy, *(bitmapArray[ix - xleft][iy - ytop].begin()));
					}
					else if (isize == 2 && bitmapArray[ix - xleft][iy - ytop].size() == 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (color != 0X%X && color != 0X%X) return false;\n",
							*(bitmapArray[ix - xleft][iy - ytop].begin()),
							*(std::next(bitmapArray[ix - xleft][iy - ytop].begin()))
						);
					}
					else if (bitmapArray[ix - xleft][iy - ytop].size() > 2)
					{
						fprintf(logFile, "color = GetPixel(%d, %d);", ix, iy);
						fprintf(logFile, "if (");
						for (auto icolor = bitmapArray[ix - xleft][iy - ytop].begin(); icolor != bitmapArray[ix - xleft][iy - ytop].end(); icolor++)
						{
							fprintf(logFile, "color != 0X%X", *icolor);
							if (std::next(icolor) != bitmapArray[ix - xleft][iy - ytop].end())
							{
								fprintf(logFile, " && ");
							}
						}
						fprintf(logFile, ") return false;\n");
					}



				}
			}
		}




		fprintf(logFile, "\nreturn true;\n}\n");
		fclose(logFile);

	}

}

#endif


