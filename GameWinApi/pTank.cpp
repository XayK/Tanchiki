#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC pTank::RmemBit[4];
HBITMAP pTank::RhBitmap[4];
BITMAP pTank::Rbm[4];
HDC pTank::GmemBit[2];
HBITMAP pTank:: GhBitmap[2];
BITMAP pTank:: Gbm[2];

HWND pTank::hWnd;

int pTank::getpos(int x3, int y3)
{
	for (int i1 = 0;i1<3;i1++)
		for (int j1 = 0;j1<3;j1++)
			if (startx + x + i1 == x3 && starty + y + j1 == y3)return 1;
	return 0;
}
void pTank::show(HDC hdc)
{
	if (Rtime == 0)//если танк жив
	{
		if (identy == 'c')
		{
			showb(hdc);
		}
		else
		{
			switch (dir)
			{
			case 1:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitUp[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
			case 2:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitRight[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
			case 3:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitDown[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
			case 4:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitLeft[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
			};

			/*if (bodyshow == 0)bodyshow = 1;
			else bodyshow = 0;*/

			if (godtime > 0)
			{
				if (godtime % 2 == 0)
					TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, GmemBit[0], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
				else
					TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, GmemBit[1], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
			}
		}
	}
	else
	{
		if (deathtime > 0)
		{
			if (deathtime >= 4)loaddeath(1);
			else if (deathtime >= 2)loaddeath(2);
			else loaddeath(3);
			deathtime--;
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBit, 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		}
		if (deathtime == 0)
		{
			x = 0; y = 0;
			respawing(hdc);
		}
	}
	for (int i = 1;i <= 100;i++)
		if (shoot[i].getstate() == 1)shoot[i].show(hdc);
}
void pTank::loaddeath(int id)
{
		switch (id)
		{
		case 0:
			hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DIE1));
			break;
		case 1:
			hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DIE2));
			break;
		case 2:
			hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_DIE3));
			break;
		}
		GetObject(hBitmap, sizeof(bm), &bm);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
}
void pTank::destroy(HDC hdc)
{
	TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBit, 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
}
void pTank::loadresp()
{
	hdc = GetDC(hWnd);
	for (int i = 0;i < 4;i++)
	{
		if (i < 2)
		{
			switch (i)
			{
			case 0: GhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GODTIME1)); break;
			case 1: GhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GODTIME2)); break;
			}
			GetObject(GhBitmap[i], sizeof(Gbm[i]), &Gbm[i]);
			GmemBit[i] = CreateCompatibleDC(hdc);
			SelectObject(GmemBit[i], GhBitmap[i]);
		}
		switch (i)
		{
		case 0: RhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_REVIVE1)); break;
		case 1: RhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_REVIVE2)); break;
		case 2: RhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_REVIVE3)); break;
		case 3: RhBitmap[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_REVIVE4)); break;
		}
		GetObject(RhBitmap[i], sizeof(Rbm[i]), &Rbm[i]);
		RmemBit[i] = CreateCompatibleDC(hdc);
		SelectObject(RmemBit[i], RhBitmap[i]);
	}
	ReleaseDC(hWnd,hdc);
}
void pTank::respawing(HDC hdc)
{
	if (Rtime < 15)
	{
		if ((Rtime >= 13) || (Rtime<7 && Rtime >= 5))
		{
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, RmemBit[0], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		}
		else if ((Rtime < 13 && Rtime >= 11) || (Rtime<7 && Rtime >= 5))
		{
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, RmemBit[1], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		}
		else if ((Rtime < 11 && Rtime >= 9) || (Rtime<5 && Rtime >= 3))
		{
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, RmemBit[2], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		}
		else if ((Rtime < 9 && Rtime >= 7) || (Rtime<3 && Rtime >= 1))
		{
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, RmemBit[3], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		}
	}
}