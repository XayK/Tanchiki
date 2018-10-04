#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HWND base::hWnd;

base :: base(void)
{
	status=0;
}
base :: ~base(void)
{
	
}
void base :: create (int x1, int y1)
{
	status=2;//2-полностью целый
	x2=x1; y2=y1;
}
void base :: show (HDC hdc)
{
	TransparentBlt(hdc, (x2 - 1)*POINT, (y2 - 1)*POINT, POINT * 3, POINT * 3, memBit, 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
}
void base::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EAGLE));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
int base :: getstatus()
{
	return status;
}

void base :: decstatus()
{
	status--;
	if (status == 0)
	{
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BASEDIE));
		GetObject(hBitmap, sizeof(bm), &bm);
		hdc = GetDC(hWnd);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
		TransparentBlt(hdc, (x2 - 1)*POINT, (y2 - 1)*POINT, POINT * 3, POINT * 3, memBit, 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		ReleaseDC(hWnd, hdc);
		pointer->stopgame();
	}
}
int base :: checkpos(int x3,int y3)
{
	for(int i=-2;i<=2;i++)
	 for(int j=-1;j<=1;j++)
	 {
	if((x2==x3+i) && (y2==y3+j))return 1;
	 }
	 return 0;
}
void base :: getpos(int &x3,int &y3)
{
	x3=x2; y3=y2;
}