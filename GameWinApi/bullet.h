#pragma once
#include "battleground.h"

class bullet
{
	int dirr;
	int state;
	int startx;
	int starty;
	int x;
	int y;
	char whois;
	int *bcount;
	int mapX;
	int mapY;
	int timer;
	int dopolnx;
	int dopolny;
	int friendlyfire;
	int blevel;
	static HWND hWnd;
	static HDC memBit;
	static HBITMAP hBitmap;
	static BITMAP bm;
public:
	bullet();
	~bullet(void);
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	static void load();
	int moving();
	void show(HDC hdc);
	void destructor();
	void setting(int a,int x1, int y1,int mx, int my, int FF,int blv,char wh);
	int getstate();
	int gettime();
	void destroy();
	void zerostate(){state=0; timer=0;}
	void dectime(){timer--;}
};
