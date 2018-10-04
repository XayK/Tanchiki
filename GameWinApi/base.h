#pragma once
#include "battleground.h"

class base
{
	int status;
	int x2;
	int y2;
	static HWND hWnd;
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
public:
	base(void);
	~base(void);
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	void create(int x1, int y1);
	void show(HDC hdc);
	int getstatus();
	void load();
	int checkpos(int x3,int y3);
	void getpos(int &x3,int &y3);
	void decstatus();
};
