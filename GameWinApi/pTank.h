#pragma once
#include "battleground.h"
#include "bullet.h"

class pTank
{
protected:
	int lifes;//оставшиеся жизни
	int bcount;//счетчик снарядов
	int dir;//направление движения
	int x;//координатаx
	int y;//координатаy
	int startx;//начальная координатач
	int starty;//начальня координатаy
	int MapX;//границы карты по x и y
	int MapY;
	int godtime;
	char identy;
	int bodyshow;
	int shoottime;//блокировка стрельбы
	int Rtime;//время до возрождения
	int freezetime;//время заморозки управления
	int tanklevel;//уровень танка
	INT deathtime;
	HDC memBitUp[2], memBitRight[2], memBitDown[2], memBitLeft[2];
	HBITMAP hBitmapUp[2], hBitmapRight[2], hBitmapDown[2], hBitmapLeft[2];
	BITMAP bmUp[2], bmRight[2], bmDown[2], bmLeft[2];
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
	static HDC RmemBit[4],GmemBit[2];
	static HBITMAP RhBitmap[4],GhBitmap[2];
	static BITMAP Rbm[4],Gbm[2];
	static HWND hWnd;
public:
	bullet shoot[150];//снаряды танка
	pTank()	{bodyshow = 0;}
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	virtual void die() {}//обработка смерти танка
	void show(HDC hdc);
	void loaddeath(int id);
	virtual void showb(HDC hdc) {}
	virtual void setti() {}//загрузка танка
	virtual int move(int button) { return 0; }//функция по передивижению и отрисовки танка
	int getlifes() { return lifes; }
	void destroy(HDC hdc);//взрыв танка
	virtual void getstart(int z, int z2, int z12, int z22) {}//возрождение танка
	int getpos(int x3, int y3);//запрос координат
	int getRtime() { return Rtime; }
	void decRtime() { Rtime--; }
	virtual void load(int number) {}//загрузка новой внешности танка
	void pluslife() { lifes++; }
	void freeze(int temp) { freezetime = temp; }
	int getdir() { return dir; }
	static void loadresp();
	void respawing(HDC hdc);
	void getposition(int &r1, int &r2) { r1 = x + startx;r2 = y + starty; }
};

