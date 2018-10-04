#pragma once
#include "battleground.h"

class bonus
{
	int id;//тип бонуса
	int mapx;
	int mapy;
	int X;
	int Y;
	int timeleft;
	static HWND hWnd;
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
public:
	bonus(void);
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	void destroy();
	void spawnbonus(int x2, int y2);
	int gettime(){return timeleft;}
	void dectime(){timeleft--;}
	int getpos(int x3, int y3);
	void refresh(HDC hdc);
	void load(int id);
	void getbonus();
};
