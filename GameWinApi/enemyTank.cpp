#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern INT lev;
extern PAINTSTRUCT ps;
extern HDC hdc;

int enemyTank::counter = 0;

enemyTank::enemyTank()
{
	identy = 'c';
	godtime = 0;
	deathtime = 0;
	x=0; y=0; bonus=0; nextround=0;
	id = counter; counter++;
}
void enemyTank::die()
{
	PlaySound(TEXT("music/destroyed.wav"), NULL, SND_ASYNC | SND_FILENAME);
 	lifes--;
	if(lifes==0)
	{
		if(Rtime==0)
		{
			pointer->decenemy(); 
			deathtime = 5;
			if(bonus>0)
			{
				pointer->Bonus.spawnbonus(MapX,MapY);
			}//спавн бонуса
			if(pointer->getenemy()==19 || pointer->getenemy()==12 || pointer->getenemy()==5) bonus=1;
			else bonus=0;
			if(pointer->getsound()==1)
				//звук
			if(pointer->getenemy()<3)nextround=1;
			//x=0; y=0; 
			Rtime=200;
		}
	}
}
void enemyTank::load(int number)
{
	hdc = GetDC(hWnd);

	switch (number)
	{
	case 1: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EUP));  BhBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EUP_B)); break;
	case 2: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2UP)); BhBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2UP_B)); break;
	case 3: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3UP)); BhBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3UP_B)); break;
	case 4: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4UP)); BhBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4UP_B)); break;
	}
	GetObject(hBitmapUp, sizeof(bmUp[0]), &bmUp[0]);
	memBitUp[0] = CreateCompatibleDC(hdc);
	SelectObject(memBitUp[0], hBitmapUp[0]);
	GetObject(BhBitmapUp[0], sizeof(BbmUp[0]), &BbmUp[0]);
	BmemBitUp[0] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitUp[0], BhBitmapUp[0]);

	switch (number)
	{
	case 1: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ERIGHT)); BhBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ERIGHT_B)); break;
	case 2: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2RIGHT)); BhBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2RIGHT_B)); break;
	case 3: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3RIGHT)); BhBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3RIGHT_B)); break;
	case 4: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4RIGHT)); BhBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4RIGHT_B)); break;
	}
	GetObject(hBitmapRight[0], sizeof(bmRight[0]), &bmRight[0]);
	memBitRight[0] = CreateCompatibleDC(hdc);
	SelectObject(memBitRight[0], hBitmapRight[0]);
	GetObject(BhBitmapRight[0], sizeof(BbmRight[0]), &BbmRight[0]);
	BmemBitRight[0] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitRight[0], BhBitmapRight[0]);

	switch (number)
	{
	case 1: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EDOWN)); BhBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EDOWN_B)); break;
	case 2: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2DOWN)); BhBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2DOWN_B)); break;
	case 3: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3DOWN)); BhBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3DOWN_B)); break;
	case 4: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4DOWN)); BhBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4DOWN_B)); break;
	}
	GetObject(hBitmapDown[0], sizeof(bmDown[0]), &bmDown[0]);
	memBitDown[0] = CreateCompatibleDC(hdc);
	SelectObject(memBitDown[0], hBitmapDown[0]);
	GetObject(BhBitmapDown[0], sizeof(BbmDown[0]), &BbmDown[0]);
	BmemBitDown[0] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitDown[0], BhBitmapDown[0]);

	switch (number)
	{
	case 1: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ELEFT)); BhBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ELEFT_B)); break;
	case 2: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2LEFT)); BhBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2LEFT_B)); break;
	case 3: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3LEFT)); BhBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3LEFT_B)); break;
	case 4: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4LEFT)); BhBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4LEFT_B)); break;
	}
	GetObject(hBitmapLeft[0], sizeof(bmLeft[0]), &bmLeft[0]);
	memBitLeft[0] = CreateCompatibleDC(hdc);
	SelectObject(memBitLeft[0], hBitmapLeft[0]);
	GetObject(BhBitmapLeft[0], sizeof(BbmLeft[0]), &BbmLeft[0]);
	BmemBitLeft[0] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitLeft[0], BhBitmapLeft[0]);


	//подключение второго изорбражения
	switch (number)
	{
	case 1: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EUP2));  BhBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EUP_B2)); break;
	case 2: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2UP2)); BhBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2UP_B2)); break;
	case 3: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3UP2)); BhBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3UP_B2)); break;
	case 4: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4UP2)); BhBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4UP_B2)); break;
	}
	GetObject(hBitmapUp, sizeof(bmUp[1]), &bmUp[1]);
	memBitUp[1] = CreateCompatibleDC(hdc);
	SelectObject(memBitUp[1], hBitmapUp[1]);
	GetObject(BhBitmapUp[1], sizeof(BbmUp[1]), &BbmUp[1]);
	BmemBitUp[1] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitUp[1], BhBitmapUp[1]);

	switch (number)
	{
	case 1: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ERIGHT2)); BhBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ERIGHT_B2)); break;
	case 2: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2RIGHT2)); BhBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2RIGHT_B2)); break;
	case 3: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3RIGHT2)); BhBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3RIGHT_B2)); break;
	case 4: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4RIGHT2)); BhBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4RIGHT_B2)); break;
	}
	GetObject(hBitmapRight[1], sizeof(bmRight[1]), &bmRight[1]);
	memBitRight[1] = CreateCompatibleDC(hdc);
	SelectObject(memBitRight[1], hBitmapRight[1]);
	GetObject(BhBitmapRight[1], sizeof(BbmRight[1]), &BbmRight[1]);
	BmemBitRight[1] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitRight[1], BhBitmapRight[1]);

	switch (number)
	{
	case 1: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EDOWN2)); BhBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EDOWN_B2)); break;
	case 2: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2DOWN2)); BhBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2DOWN_B2)); break;
	case 3: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3DOWN2)); BhBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3DOWN_B2)); break;
	case 4: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4DOWN2)); BhBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4DOWN_B2)); break;
	}
	GetObject(hBitmapDown[1], sizeof(bmDown[1]), &bmDown[1]);
	memBitDown[1] = CreateCompatibleDC(hdc);
	SelectObject(memBitDown[1], hBitmapDown[1]);
	GetObject(BhBitmapDown[1], sizeof(BbmDown[1]), &BbmDown[1]);
	BmemBitDown[1] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitDown[1], BhBitmapDown[1]);

	switch (number)
	{
	case 1: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ELEFT2)); BhBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_ELEFT_B2)); break;
	case 2: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2LEFT2)); BhBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E2LEFT_B2)); break;
	case 3: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3LEFT2)); BhBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E3LEFT_B2)); break;
	case 4: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4LEFT2)); BhBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_E4LEFT_B2)); break;
	}
	GetObject(hBitmapLeft[1], sizeof(bmLeft[1]), &bmLeft[1]);
	memBitLeft[1] = CreateCompatibleDC(hdc);
	SelectObject(memBitLeft[1], hBitmapLeft[1]);
	GetObject(BhBitmapLeft[1], sizeof(BbmLeft[1]), &BbmLeft[1]);
	BmemBitLeft[1] = CreateCompatibleDC(hdc);
	SelectObject(BmemBitLeft[1], BhBitmapLeft[1]);

	ReleaseDC(hWnd, hdc);
}
void enemyTank::showb(HDC hdc)
{
	if (bonus == 1 && rand()%2==0)
	{
		switch (dir)
		{
		case 1:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, BmemBitUp[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 2:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, BmemBitRight[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 3:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, BmemBitDown[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 4:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, BmemBitLeft[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		};
	}
	else
	{
		switch (dir)
		{
		case 1:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitUp[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 2:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitRight[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 3:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitDown[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		case 4:TransparentBlt(hdc, (startx + x)*POINT, (starty + y)*POINT, POINT * 3, POINT * 3, memBitLeft[bodyshow], 0, 0, POINT * 3, POINT * 3, RGB(0, 255, 0)); break;
		};
	}

	//if (bodyshow == 0)bodyshow = 1;
	//else bodyshow = 0;

}
void enemyTank :: setti()
{
	dir=1;
	Rtime=0;
	freezetime=0;
	x=0; y=0;
	nextround=0;
}
void enemyTank :: getstart(int z,int z2,int z12, int z22)
{
	if (z != 0)
	{
		startx = z;
		starty = z2;
		MapX = z12;
		MapY = z22;
	}
	shoottime=0;
	bcount=0; dir=3;
	if (lev == 1)tanklevel = 1;
	else
	{
		tanklevel = rand() % 100 + 1;
		if (tanklevel <= 40) tanklevel = 3;
		else if (tanklevel > 40 && tanklevel <= 80)tanklevel = 1;
		else if (tanklevel >80 && tanklevel <= 90)tanklevel = 2;
		else if (tanklevel >90 && tanklevel <= 100)tanklevel = 4;
	}
	if (tanklevel == 4)lifes = 3;
	else lifes = 1;
	load(tanklevel);
}
int enemyTank :: move(int button)
{
	if(freezetime>0)freezetime--;
	if(bcount>0)
		for(int i=1;i<=100;i++)
			if(shoot[i].getstate()==1 && shoot[i].gettime()==0)shoot[i].moving();
			else if(shoot[i].gettime()> 0)shoot[i].dectime();
			if (Rtime > 0 && nextround == 0)
			{ 
				Rtime--;
				//respawing(); 
				if (Rtime == 0)getstart(startx, starty, MapX, MapY); 
				pointer->II.setsm(id, 1); 
				return 1; }
	if(shoottime>0){shoottime--;}
	if (nextround == 1) {
		pointer->II.setsm(id, 1);
		return 1;
	}
	int ke,dX,dY;
		
		ke=button;
		if(freezetime>0)ke=0;//заморозка танков
			switch(ke)
			{
				case 1:{if(shoottime==0){
					switch(dir)
					{
						case 1:{dX=1; dY=-1; break;}
						case 2:{dX=3; dY=1; break;}
						case 3:{dX=1; dY=3; break;}
						case 4:{dX=-1; dY=1; break;}
					} bcount++;
					shoot[bcount].setting(dir,startx+x+dX,starty+y+dY,MapX,MapY,1,tanklevel,'e');
					if(bcount==100)bcount=0;
					if(tanklevel>=3)shoottime=20;//блокировка стрельбы
					else shoottime=30;
					   }
					break;}//стрельба
			case 2:{dir=1; 
				if(starty+y<=1){ pointer->II.setsm(id, 0); return 0;}
					for(int i=0;i<=2;i++)
					{
							if(pointer->Rwall[starty+y-1][startx+x+i].getstatus()>0 || pointer->Swall[starty+y-1][startx+x+i].getstatus()>0 || pointer->eagle.checkpos(startx+x+1,starty+y-1)==1  || pointer->water[starty+y-1][startx+x+i].getstatus()>0)
							{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+j,starty+y-1)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
							if(pointer->green2.getpos(startx+x+j,starty+y-1)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+j,starty+y-1)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; pointer->II.setsm(id, 0); return 0;}
						if(pointer->ice[starty+y-1][startx+x+i].getstatus()>0)freezetime=5;
					}
					//проверка наличия блоков
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					y--; break;}//вверх
			case 3:{dir=4;
				if(startx+x<=1){ pointer->II.setsm(id, 0); return 0;}
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+i][startx+x-1].getstatus()>0 || pointer->Swall[starty+y+i][startx+x-1].getstatus()>0 || pointer->eagle.checkpos(startx+x-1,starty+y+1)==1 || pointer->eagle.checkpos(startx+x-1,starty+y+2)==1 || pointer->water[starty+y+i][startx+x-1].getstatus()>0)
							{freezetime=0; pointer->II.setsm(id, 0);  return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x-1,starty+y+j)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
							if(pointer->green2.getpos(startx+x-1,starty+y+j)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x-1,starty+y+j)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; pointer->II.setsm(id, 0); return 0;}
						if(pointer->ice[starty+y+i][startx+x-1].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					x--; break;}//влево
			case 4:{dir=2; 
				if(startx+x+4>=MapX){ pointer->II.setsm(id, 0); return 0;}
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+i][startx+x+3].getstatus()>0 || pointer->Swall[starty+y+i][startx+x+3].getstatus()>0 || pointer->eagle.checkpos(startx+x+3,starty+y+1)==1 || pointer->eagle.checkpos(startx+x+3,starty+y+2)==1 || pointer->water[starty+y+i][startx+x+3].getstatus()>0 )
							{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+3,starty+y+j)==1)
								{freezetime=0; pointer->II.setsm(id, 0);  return 0;}
							if(pointer->green2.getpos(startx+x+3,starty+y+j)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+3,starty+y+j)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; pointer->II.setsm(id, 0); return 0;}
						if(pointer->ice[starty+y+i][startx+x+3].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					x++;  break;}//вправо
			case 5:{dir=3; 
				if(starty+y+4>=MapY){ pointer->II.setsm(id, 0); return 0;}
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+3][startx+x+i].getstatus()>0 || pointer->Swall[starty+y+3][startx+x+i].getstatus()>0 || pointer->eagle.checkpos(startx+x+1,starty+y+3)==1 || pointer->eagle.checkpos(startx+x,starty+y+3)==1 || pointer->eagle.checkpos(startx+x+2,starty+y+3)==1 || pointer->water[starty+y+3][startx+x+i].getstatus()>0)
							{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+j,starty+y+3)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
							if(pointer->green2.getpos(startx+x+j,starty+y+3)==1)
								{freezetime=0; pointer->II.setsm(id, 0); return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+j,starty+y+3)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; pointer->II.setsm(id, 0); return 0;}
						if(pointer->ice[starty+y+3][startx+x+i].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					y++;  break;}//вниз
			}


			//?Убрать для компа?
			//for (int i = 0;i < 3;i++)
			//{
			//	for (int j = 0;j < 3;j++)
			//	{
			//		if (pointer->Bonus.getpos(startx + x + j, starty + y + i) == 1 && pointer->Bonus.gettime() > 0)
			//		{
			//			pointer->Bonus.getbonus();
			//			pointer->Bonus.destroy();
			//		}//включение бонуса
			//	}
			//}

	for(int i=1;i<=100;i++)
		if(shoot[i].getstate()==1 && shoot[i].gettime()==0)shoot[i].moving();
		else if(shoot[i].gettime()> 0)shoot[i].dectime();
	pointer->II.setsm(id, 1);
	return 1;
}