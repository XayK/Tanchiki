#pragma once
#include "block.h"

class waterblock : public block
{
	static HDC memBit;
	static HBITMAP hBitmap;
	static BITMAP bm;
public:
	waterblock(void);
	static void load();
	void show(int x1, int y1, HDC hdc);//����� ����� �� �����
	void show(HDC hdc);//����� ����� �� �����
};
