#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;

HWND bullet::hWnd;
HDC bullet::memBit;
HBITMAP bullet::hBitmap;
BITMAP bullet::bm;

bullet::bullet()
{
	state = 0;
	y = 0; x = 0;
	startx = 0; starty = 0;
	dopolnx = 0;
	dopolny = 0;
}
bullet::~bullet(void)
{
	
	/*if(pointer->getgame()==1)
	{
		state=0;
		pointer->bullblock[starty+y][startx+x].clear();*/
		//консольный код
		/*if(dopolnx!=0 || dopolny!=0)
		{
			 if(pointer->ice[starty+y+dopolny][startx+x+dopolnx].getstatus()>0)pointer->ice[starty+y+dopolny][startx+x+dopolnx].show(startx+x+dopolnx,starty+y+dopolny);
			 else if (pointer->green[starty + y + dopolny][startx + x + dopolnx].getstatus()>0)pointer->green[starty + y + dopolny][startx + x + dopolnx].show(startx + x + dopolnx, starty + y + dopolny);
			 else if(pointer->water[starty+y+dopolny][startx+x+dopolnx].getstatus()>0)pointer->water[starty+y+dopolny][startx+x+dopolnx].show(startx+x+dopolnx,starty+y+dopolny);
			 else
			 {
				RECT pRect = { (startx + x + dopolnx)*POINT,(starty + y + dopolny)*POINT ,(startx + x + +dopolnx +1 )*POINT , (starty + y + +dopolny + 1)*POINT };
				InvalidateRect(hWnd, &pRect, TRUE);
			 }
		}*/
	//}
}
void bullet :: destructor()
{
	if (pointer->getgame() == 1)
	{
		state = 0;
		pointer->bullblock[starty + y][startx + x].clear();
	}
}
void bullet :: setting(int a,int x1, int y1,int mx, int my, int FF,int blv,char wh)
{
dirr=a; x=0; y=0; startx=x1; starty=y1;
state=1; friendlyfire=FF;
mapX=mx; mapY=my; timer=0; dopolnx=0; dopolny=0;
blevel=blv; whois=wh;
}
void bullet :: load()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BULL));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);
}
void bullet::show(HDC hdc)
{
	if(state==1)
		TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT, POINT, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
}
int bullet :: moving(void)
{
	if (state == 0)return 0;
	if((dopolnx==0 && dopolny==0))
		{
			if(pointer->bullblock[starty+y][startx+x].getstatus()>0)
			{
				destroy();
				return 1;
			}//столкновение пули друг с другом
			else 
			{
				pointer->bullblock[starty+y][startx+x].create(this);
			}//создание коллизион модели
		}
		else
		{
			pointer->bullblock[starty+y+dopolny][startx+x+dopolnx].clear();
			if(pointer->bullblock[starty+y][startx+x].getstatus()>0)
			{
				destroy();
				return 1;
			}//столкновение пули друг с другом
			else 
			{

				pointer->bullblock[starty+y][startx+x].create(this);
			}//создание коллизион модели
		}
	//встреча с препятсвиями
	if(pointer->Swall[starty+y][startx+x].getstatus()>0)
		{ 
			state=0; 
			pointer->bullblock[starty+y][startx+x].clear();
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
				this->destructor(); 
			if(blevel==4)pointer->Swall[starty+y][startx+x].decstatus(dirr); 
			return 1;
		}
	else if(pointer->Rwall[starty+y][startx+x].getstatus()>0)
		{
			state=0; 
			pointer->bullblock[starty+y][startx+x].clear();
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
				this->destructor(); 
			pointer->Rwall[starty+y][startx+x].decstatus(dirr);
			return 1;
		}
	else if(pointer->eagle.getstatus()>0 && pointer->eagle.checkpos(startx+x,starty+y)==1)
		{
			state=0; 
			pointer->bullblock[starty+y][startx+x].clear();
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
				this->destructor();
			pointer->eagle.decstatus();  return 1;}
	else if(pointer->yellow.getpos(startx+x,starty+y)==1)
		{ 
			state=0; 
			pointer->bullblock[starty+y][startx+x].clear();
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
				this->destructor(); 
			if(friendlyfire==1 && pointer->yellow.getgodtime()==0 && pointer->yellow.getRtime()==0)
			{
				pointer->yellow.die();
			}
			else if(pointer->yellow.getgodtime()==0){pointer->yellow.freeze(50);}
		
		return 1;
		}//1 игрок
	else if(pointer->green2.getpos(startx+x,starty+y)==1 && pointer->getplayers()==2)
		{
			state=0; 
			pointer->bullblock[starty+y][startx+x].clear();
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
				this->destructor(); 
			if(friendlyfire==1 && pointer->green2.getgodtime()==0  && pointer->green2.getRtime()==0)
			{
				pointer->green2.die();
			}
			else if(pointer->green2.getgodtime()==0){pointer->green2.freeze(50);}
		
		return 1;
		}//2 игрок
	else 
		for(int i=0;i<3;i++)
			if(pointer->enemy[i].getpos(startx+x,starty+y)==1 && pointer->enemy[i].getRtime()==0)
			{ 
 				int getlevel=pointer->enemy[i].getlevel();
				state=0; 
				if(whois=='y'){pointer->yellow.incscore(100*getlevel); pointer->yellow.incenemycount(getlevel);}
				else if(whois=='g'){pointer->green2.incscore(100*getlevel); pointer->yellow.incenemycount(getlevel);}
				pointer->bullblock[starty+y][startx+x].clear();
				if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
					this->destructor(); 
				if(friendlyfire==0)
				{pointer->enemy[i].die();}
				else{pointer->enemy[i].freeze(50);}
				return 1;
			}//противники	

	if(startx+x<=1 || starty+y<=1 || starty+y+2>mapY-1 ||startx+x+2>mapX-1)
	{ 
		state=0;  
		pointer->bullblock[starty+y+dopolny][startx+x+dopolnx].clear();
		if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
			this->destructor(); 
		return 1;
	}//проверка границ карты

	//прорисовка пули в консоли
	/*if(pointer->green[starty+y][startx+x].getstatus()==0)
		{;
			TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT, POINT, memBit, 0, 0, POINT, POINT, RGB(0, 255, 0));
			setcur(startx+x,starty+y);
			text=7; background=0;
			if(pointer->ice[starty+y][startx+x].getstatus()>0)background=11;
			else if(pointer->water[starty+y][startx+x].getstatus()>0)background=9;
			SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
			cout << 'щ';
		}
		if((dopolnx!=0 || dopolny!=0))
		{
			if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
			{
				if(pointer->ice[starty+y+dopolny][startx+x+dopolnx].getstatus()>0)pointer->ice[starty+y+dopolny][startx+x+dopolnx].show(startx+x+dopolnx,starty+y+dopolny);
				else if(pointer->water[starty+y+dopolny][startx+x+dopolnx].getstatus()>0)pointer->water[starty+y+dopolny][startx+x+dopolnx].show(startx+x+dopolnx,starty+y+dopolny);
				else
				{
					RECT pRect = { (startx + x + dopolnx)*POINT,(starty + y + dopolny)*POINT ,(startx + x + +dopolnx +1 )*POINT , (starty + y + +dopolny + 1)*POINT };
					InvalidateRect(hWnd, &pRect, TRUE);
				}
			}//удаление старой пули
			dopolnx=0; dopolny=0;
		}*/
	if ((dopolnx != 0 || dopolny != 0))
	{
		dopolnx = 0; dopolny = 0;
	}
	switch(dirr)
	{
		case 1:{y--; break;}
		case 2:{x++; break;}
		case 3:{y++; break;}
		case 4:{x--; break;}
	}
	if(timer==0)
	{
		if(blevel==1 && friendlyfire==0)timer=2;
		else if(blevel!=3 && friendlyfire==1)timer=2;
		else timer=1;
	}
	
	switch(dirr)
	{
		case 1:{dopolny++; break;}
		case 2:{dopolnx--; break;}
		case 3:{dopolny--; break;}
		case 4:{dopolnx++; break;}
	}
	return 0;
}
int bullet :: getstate()
{
	return state;
}
int bullet :: gettime()
{
	return timer;
}
void bullet :: destroy()
{
	pointer->bullblock[starty+y][startx+x].destroy();
	pointer->bullblock[starty + y][startx + x].clear();
	state=0; 
	if(pointer->green[starty+y+dopolny][startx+x+dopolnx].getstatus()==0)
		this->destructor(); 

}