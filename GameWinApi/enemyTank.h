#pragma once
#include "battleground.h"
#include "bullet.h"
#include "pTank.h"

class enemyTank : public pTank
{
	int bonus;
	int nextround;
	int id;
	static int counter;
	HDC BmemBitUp[2], BmemBitRight[2], BmemBitDown[2], BmemBitLeft[2];
	HBITMAP BhBitmapUp[2], BhBitmapRight[2], BhBitmapDown[2], BhBitmapLeft[2];
	BITMAP BbmUp[2], BbmRight[2], BbmDown[2], BbmLeft[2];
public:
	enemyTank();
	void die();
	void setti();
	int move(int mover);
	void load(int number);
	int gettlevel(){return tanklevel;}
	void showb(HDC hdc);
	void getstart(int z,int z2,int z12, int z22);
	int getlevel(){return tanklevel;}
};


