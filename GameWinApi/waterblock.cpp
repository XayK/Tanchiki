#include "header.h"
// ���������� ����������:
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern class battleground *pointer;//��������� �� �������� ������
extern INT lev;
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC waterblock::memBit;
HBITMAP waterblock::hBitmap;
BITMAP waterblock::bm;

waterblock::waterblock(void)
{
}
void waterblock::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WATER1));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void waterblock::show(HDC hdc)
{
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void waterblock::show(int x2, int y2, HDC hdc)
{
	X = x2;Y = y2;
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}