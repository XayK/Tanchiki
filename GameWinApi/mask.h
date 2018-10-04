#pragma once
#include "block.h"

class mask : public block
{
	static HDC memBit;
	static HBITMAP hBitmap;
	static BITMAP bm;
public:
	mask(void);
	void show(int x1, int y1, HDC hdc);//вывод блока на экран
	void show(HDC hdc);//вывод блока на экран
	static void load();
};
