#include "header.h"
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC iceblock::memBit;
HBITMAP iceblock::hBitmap;
BITMAP iceblock::bm;

iceblock::iceblock(void)
{
}
void iceblock::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ICE));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void iceblock::show(HDC hdc)
{
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void iceblock::show(int x2, int y2, HDC hdc)
{
	X = x2;Y = y2;
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}