#pragma once
#include "block.h"

class beton : public block
{
	static HDC memBit;
	static HBITMAP hBitmap;
	static BITMAP bm;
public:
	beton(void);
	~beton(void);
	static void load();
	void create();
	void show(int x1, int y1, HDC hdc);//����� ����� �� �����
	void show(HDC hdc);//����� ����� �� �����
	void decstatus();
	void decstatus(INT directi);
};
