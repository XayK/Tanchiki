#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC brick::memBit;
HBITMAP brick::hBitmap;
BITMAP brick::bm;



brick :: brick ()
{
}
void brick :: create ()
{
	status=1;//полностью целый блок
}
void brick::show(HDC hdc)
{
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void brick::show(int x2, int y2, HDC hdc)
{
	X = x2;Y = y2;
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void brick::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BRICK));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
brick :: ~brick ()
{ 
}
void brick :: decstatus(int directi)
{
	status--;
	if(pointer->Rwall[Y+1][X].getstatus()>0 && (directi==4 || directi==2))pointer->Rwall[Y+1][X].decstatus();
	if(pointer->Rwall[Y-1][X].getstatus()>0 && (directi==4 || directi==2))pointer->Rwall[Y-1][X].decstatus();
	if(pointer->Rwall[Y][X-1].getstatus()>0 && (directi==1 || directi==3))pointer->Rwall[Y][X-1].decstatus();
	if(pointer->Rwall[Y][X+1].getstatus()>0 && (directi==1 || directi==3))pointer->Rwall[Y][X+1].decstatus();
	PlaySound(TEXT("music/brickwall.wav"), NULL, SND_ASYNC | SND_FILENAME);
	if(status==0)this->~brick();
}
void brick :: decstatus()
{
	status--;
	if(status==0)this->~brick();
}