#pragma once
#include "block.h"

class brick : public block
{
	static HDC memBit;
	static HBITMAP hBitmap;
	static BITMAP bm;
public:
	brick(void);
	~brick(void);
	static void load();
	void create();
	void show(int x1, int y1, HDC hdc);//вывод блока на экран
	void show(HDC hdc);//вывод блока на экран
	void decstatus(int directi);
	void decstatus();
};
