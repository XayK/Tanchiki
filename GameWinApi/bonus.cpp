#include "header.h"
// ���������� ����������:
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern class battleground *pointer;//��������� �� �������� ������
extern PAINTSTRUCT ps;
extern HDC hdc;

HWND bonus::hWnd;

bonus::bonus(void)
{
	id=0;
	X=0;Y=0;
}
void bonus::load(int id)
{
	switch (id)
	{
		case 1:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_TANK)); break;//����� �����
		case 2:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_TIME)); break;//���������� ����� ����������
		case 3:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_GRENADE)); break;//���������� ���� �����������
		case 4:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_GOD)); break;//������������
		case 5:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_STAR)); break;//��������� �����
		case 6:hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BONUS_LOPATA)); break;//������
	}
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void bonus::destroy(void)
{
	if (id > 0)
	{
		id = 0;
		timeleft = 0;
	}
}
void bonus :: spawnbonus(int x2, int y2)
{	
	mapx=x2; mapy=y2;
	while(true)
	{
		X=rand()%(mapx-6)+3; Y=rand()%(mapy-6)+3;//���������� ������
		if(pointer->getposboard(Y,X)==1)break;
	}
	PlaySound(TEXT("music/bonusshow.wav"), NULL, SND_ASYNC | SND_FILENAME);
	id=rand()%6+1;//��� ������
	load(id);
	timeleft=300;
}
int bonus :: getpos(int x3, int y3)
{
	if(x3==X && y3==Y)return 1;
	else return 0;
}
void bonus :: refresh(HDC hdc)
{
	if(id>0 && timeleft >0)
	{
		TransparentBlt(hdc, X*POINT, Y*POINT, POINT * 3, POINT * 3, memBit, 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0));
		timeleft--;
	}
	
}
void bonus::getbonus()
{
	switch(id)
	{
		case 1:{pointer->yellow.pluslife(); if(pointer->getplayers()==2)pointer->green2.pluslife(); break;}//����� �����
		case 2:{for(int i=0;i<3;i++)pointer->enemy[i].freeze(300); break;}//���������� ����� ����������
		case 3:{for(int i=0;i<3;i++)if(pointer->enemy[i].getRtime()==0)pointer->enemy[i].die(); break;}//���������� ���� �����������
		case 4:{pointer->yellow.godmode(200); pointer->green2.godmode(200); break;}//������������
		case 5:{pointer->yellow.inctlevel();  pointer->green2.inctlevel(); break;}//��������� �����
	    case 6:{
			int xtemp; int ytemp;
			pointer->eagle.getpos(xtemp,ytemp);
			for(int i1=ytemp-3;i1<=ytemp+1;i1++)
			{
				for(int j1=xtemp-4;j1<=xtemp+4;j1++)
				{
					if(!(i1>=ytemp-1 && (j1>=xtemp-2 && j1<=xtemp+2)))
					{
						pointer->Rwall[i1][j1].create(); 
					}
				}
			}
			break;}//������
	}
	PlaySound(TEXT("music/takebonus.wav"), NULL, SND_ASYNC | SND_FILENAME);
}