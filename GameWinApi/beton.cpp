#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HDC beton::memBit;
HBITMAP beton::hBitmap;
BITMAP beton::bm;

beton :: beton (void)
{
}
beton :: ~beton ()
{ 
}

void beton::load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BETON));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void beton :: create ()
{
	status=2;//2-полностью целый
}
void beton::show(HDC hdc)
{
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void beton::show(int x2, int y2, HDC hdc)
{
	X = x2;Y = y2;
	TransparentBlt(hdc, X*POINT, Y*POINT, bm.bmWidth, bm.bmHeight, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
void beton :: decstatus(INT directi)
{
	status--;
	if(pointer->Swall[Y+1][X].getstatus()>0 && (directi==4 || directi==2))pointer->Swall[Y+1][X].decstatus();
	if(pointer->Swall[Y-1][X].getstatus()>0 && (directi==4 || directi==2))pointer->Swall[Y-1][X].decstatus();
	if(pointer->Swall[Y][X-1].getstatus()>0 && (directi==1 || directi==3))pointer->Swall[Y][X-1].decstatus();
	if(pointer->Swall[Y][X+1].getstatus()>0 && (directi==1 || directi==3))pointer->Swall[Y][X+1].decstatus();
	PlaySound(TEXT("music/beton.wav"), NULL, SND_ASYNC | SND_FILENAME);
	if(status==0)this->~beton();
}
void beton :: decstatus()
{
	status--;
	if(status==0)this->~beton();
}