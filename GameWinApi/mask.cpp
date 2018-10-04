#include "header.h"
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern class battleground *pointer;//��������� �� �������� ������
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC mask::memBit;
HBITMAP mask::hBitmap;
BITMAP mask::bm;

mask :: mask (void)
{
}
void mask::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BRUSH));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void mask::show(HDC hdc)
{
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void mask::show(int x2, int y2,HDC hdc)
{
	X = x2;Y = y2;
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}