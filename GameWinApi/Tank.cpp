#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern PAINTSTRUCT ps;
extern HDC hdc;
//#pragma comment(lib, "msimg32.lib")
int Tank::players = 0;

Tank::Tank()
{
	players++; numberplayer=players;
	identy = 'p';
	deathtime = 0;
	zeroscore();
	setti(); 
	x=0; y=0; lifes=4; startx=500; starty=500;
}
void Tank :: die()
{
	PlaySound(TEXT("music/die.wav"), NULL, SND_ASYNC | SND_FILENAME);
	lifes--;
	if(lifes==0){//Конце игры
		pointer->stopgame();
	}
	else{
	//возрождение
	deathtime = 5;
	//x=0; y=0;
	Rtime=100;
	tanklevel=1;
	}
}
void Tank::load(int number)
{
	hdc = GetDC(hWnd);
	if (numberplayer == 1)
	{
		switch (number)
		{
		case 1: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YUP)); break;
		case 2: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2UP)); break;
		case 3: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3UP)); break;
		case 4: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4UP)); break;
		}
		GetObject(hBitmapUp[0], sizeof(bmUp[0]), &bmUp[0]);
		memBitUp[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitUp[0], hBitmapUp[0]);


		switch (number)
		{
		case 1: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YRIGHT)); break;
		case 2: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2RIGHT)); break;
		case 3: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3RIGHT)); break;
		case 4: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4RIGHT)); break;
		}
		GetObject(hBitmapRight[0], sizeof(bmRight[0]), &bmRight[0]);
		memBitRight[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitRight[0], hBitmapRight[0]);

		switch (number)
		{
		case 1: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YDOWN)); break;
		case 2: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2DOWN)); break;
		case 3: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3DOWN)); break;
		case 4: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4DOWN)); break;
		}
		GetObject(hBitmapDown[0], sizeof(bmDown[0]), &bmDown[0]);
		memBitDown[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitDown[0], hBitmapDown[0]);

		switch (number)
		{
		case 1: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YLEFT)); break;
		case 2: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2LEFT)); break;
		case 3: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3LEFT)); break;
		case 4: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4LEFT)); break;
		}
		GetObject(hBitmapLeft[0], sizeof(bmLeft[0]), &bmLeft[0]);
		memBitLeft[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitLeft[0], hBitmapLeft[0]);

		//подключение второго изорбражения
		switch (number)
		{
		case 1: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YUP2)); break;
		case 2: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2UP2)); break;
		case 3: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3UP2)); break;
		case 4: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4UP2)); break;
		}
		GetObject(hBitmapUp[1], sizeof(bmUp[1]), &bmUp[1]);
		memBitUp[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitUp[1], hBitmapUp[1]);


		switch (number)
		{
		case 1: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YRIGHT2)); break;
		case 2: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2RIGHT2)); break;
		case 3: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3RIGHT2)); break;
		case 4: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4RIGHT2)); break;
		}
		GetObject(hBitmapRight[1], sizeof(bmRight[1]), &bmRight[1]);
		memBitRight[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitRight[1], hBitmapRight[1]);

		switch (number)
		{
		case 1: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YDOWN2)); break;
		case 2: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2DOWN2)); break;
		case 3: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3DOWN2)); break;
		case 4: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4DOWN2)); break;
		}
		GetObject(hBitmapDown[1], sizeof(bmDown[1]), &bmDown[1]);
		memBitDown[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitDown[1], hBitmapDown[1]);

		switch (number)
		{
		case 1: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YLEFT2)); break;
		case 2: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y2LEFT2)); break;
		case 3: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y3LEFT2)); break;
		case 4: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Y4LEFT2)); break;
		}
		GetObject(hBitmapLeft[1], sizeof(bmLeft[1]), &bmLeft[1]);
		memBitLeft[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitLeft[1], hBitmapLeft[1]);
	}
	else
	{
		switch (number)
		{
		case 1: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GUP)); break;
		case 2: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2UP)); break;
		case 3: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3UP)); break;
		case 4: hBitmapUp[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4UP)); break;
		}
		GetObject(hBitmapUp[0], sizeof(bmUp[0]), &bmUp[0]);
		memBitUp[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitUp[0], hBitmapUp[0]);


		switch (number)
		{
		case 1: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GRIGHT)); break;
		case 2: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2RIGHT)); break;
		case 3: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3RIGHT)); break;
		case 4: hBitmapRight[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4RIGHT)); break;
		}
		GetObject(hBitmapRight[0], sizeof(bmRight[0]), &bmRight[0]);
		memBitRight[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitRight[0], hBitmapRight[0]);

		switch (number)
		{
		case 1: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GDOWN)); break;
		case 2: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2DOWN)); break;
		case 3: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3DOWN)); break;
		case 4: hBitmapDown[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4DOWN)); break;
		}
		GetObject(hBitmapDown[0], sizeof(bmDown[0]), &bmDown[0]);
		memBitDown[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitDown[0], hBitmapDown[0]);

		switch (number)
		{
		case 1: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GLEFT)); break;
		case 2: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2LEFT)); break;
		case 3: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3LEFT)); break;
		case 4: hBitmapLeft[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4LEFT)); break;
		}
		GetObject(hBitmapLeft[0], sizeof(bmLeft[0]), &bmLeft[0]);
		memBitLeft[0] = CreateCompatibleDC(hdc);
		SelectObject(memBitLeft[0], hBitmapLeft[0]);

		//подключение второго изорбражения
		switch (number)
		{
		case 1: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GUP2)); break;
		case 2: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2UP2)); break;
		case 3: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3UP2)); break;
		case 4: hBitmapUp[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4UP2)); break;
		}
		GetObject(hBitmapUp[1], sizeof(bmUp[1]), &bmUp[1]);
		memBitUp[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitUp[1], hBitmapUp[1]);


		switch (number)
		{
		case 1: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GRIGHT2)); break;
		case 2: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2RIGHT2)); break;
		case 3: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3RIGHT2)); break;
		case 4: hBitmapRight[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4RIGHT2)); break;
		}
		GetObject(hBitmapRight[1], sizeof(bmRight[1]), &bmRight[1]);
		memBitRight[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitRight[1], hBitmapRight[1]);

		switch (number)
		{
		case 1: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GDOWN2)); break;
		case 2: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2DOWN2)); break;
		case 3: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3DOWN2)); break;
		case 4: hBitmapDown[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4DOWN2)); break;
		}
		GetObject(hBitmapDown[1], sizeof(bmDown[1]), &bmDown[1]);
		memBitDown[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitDown[1], hBitmapDown[1]);

		switch (number)
		{
		case 1: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GLEFT2)); break;
		case 2: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G2LEFT2)); break;
		case 3: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G3LEFT2)); break;
		case 4: hBitmapLeft[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_G4LEFT2)); break;
		}
		GetObject(hBitmapLeft[1], sizeof(bmLeft[1]), &bmLeft[1]);
		memBitLeft[1] = CreateCompatibleDC(hdc);
		SelectObject(memBitLeft[1], hBitmapLeft[1]);
	}
	ReleaseDC(hWnd, hdc);
}
void Tank :: setti()
{
	dir=1;
	freezetime=0;
	Rtime = 0;
	godtime=0;
	score = score;
	tanklevel=1;
	x=0; y=0;
}
void Tank :: getstart(int z,int z2,int z12, int z22)
{
	godtime=50;
	if (z != 0)
	{
		startx = z;
		starty = z2;
		MapX = z12;
		MapY = z22;
	}
	shoottime=0;
	bcount=0;
	Rtime = 0;
	dir = 1;
	load(tanklevel);
}
int Tank :: move(int button)
{
	int Temp = 0;
	if(pointer->getplayers()==1 && player==2)return 0;//проверка разных таймеров и условий
	if(freezetime>0)freezetime--;
	if(godtime>0)godtime--;
	if(bcount>0)
		for(int i=1;i<=100;i++)
			if(shoot[i].getstate()==1 && shoot[i].gettime()==0)shoot[i].moving();
			else if(shoot[i].gettime()> 0)shoot[i].dectime();
			if(Rtime>0)
			{
				Rtime--; 
				if(Rtime==0)getstart(startx,starty,MapX,MapY);  
				if(Rtime==1)godtime=50;
				button=0;
			}
	int dX,dY;
	if(shoottime>0){shoottime--;}
	/*show();*/
	if(button!=0)//проверка наличия нажатых клавишь
	{
		if(button==72 || button==75 || button==80 || button==77 || button==48)
		{
			if(freezetime>0)button=0;
			switch(button)
			{
			case 48:{ if(shoottime==0){
					switch(dir)
					{
						case 1:{dX=1; dY=-1; break;}
						case 2:{dX=3; dY=1; break;}
						case 3:{dX=1; dY=3; break;}
						case 4:{dX=-1; dY=1; break;}
					} bcount++;
					if(player==1)
						shoot[bcount].setting(dir,startx+x+dX,starty+y+dY,MapX,MapY,0,tanklevel,'y');
					else
						shoot[bcount].setting(dir,startx+x+dX,starty+y+dY,MapX,MapY,0,tanklevel,'g');
					if(bcount==100)bcount=0;
					if(tanklevel>=3) shoottime=6;
					else shoottime=10;//блокировка стрельбы
					}
					break;}//стрельба на нум0
			case 72:{dir=1;  
				if(starty+y<=1){return 0;}	
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y-1][startx+x+i].getstatus()>0 || pointer->Swall[starty+y-1][startx+x+i].getstatus()>0 || pointer->eagle.checkpos(startx+x+1,starty+y-1)==1  || pointer->water[starty+y-1][startx+x+i].getstatus()>0)
							{freezetime=0; return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+j,starty+y-1)==1)
								{freezetime=0; return 0;}
							if(pointer->green2.getpos(startx+x+j,starty+y-1)==1)
								{freezetime=0; return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+j,starty+y-1)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; return 0;}
						if(pointer->ice[starty+y-1][startx+x+i].getstatus()>0)freezetime=5;
					}//проверка наличия блоков
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					y--; Temp++; break;}//вверх
			case 75:{dir=4; 
				if(startx+x<=1){return 0;}	 
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+i][startx+x-1].getstatus()>0 || pointer->Swall[starty+y+i][startx+x-1].getstatus()>0 || pointer->eagle.checkpos(startx+x-1,starty+y+1)==1 || pointer->eagle.checkpos(startx+x-1,starty+y+2)==1 || pointer->water[starty+y+i][startx+x-1].getstatus()>0)
							{freezetime=0; return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x-1,starty+y+j)==1)
								{freezetime=0; return 0;}
							if(pointer->green2.getpos(startx+x-1,starty+y+j)==1)
								{freezetime=0; return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x-1,starty+y+j)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; return 0;}
						if(pointer->ice[starty+y+i][startx+x-1].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					 x--; Temp++; break;}//влево
			case 77:{dir=2; 
				if(startx+x+4>=MapX){return 0;}
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+i][startx+x+3].getstatus()>0 || pointer->Swall[starty+y+i][startx+x+3].getstatus()>0 || pointer->eagle.checkpos(startx+x+3,starty+y+1)==1 || pointer->eagle.checkpos(startx+x+3,starty+y+2)==1 || pointer->water[starty+y+i][startx+x+3].getstatus()>0 )
							{freezetime=0; return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+3,starty+y+j)==1)
								{freezetime=0; return 0;}
							if(pointer->green2.getpos(startx+x+3,starty+y+j)==1)
								{freezetime=0; return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+3,starty+y+j)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; return 0;}
						if(pointer->ice[starty+y+i][startx+x+3].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					 x++; Temp++; break;}//вправо
			case 80:{dir=3; 
				if(starty+y+4>=MapY){return 0;} 
					for(int i=0;i<=2;i++)
					{
						if(pointer->Rwall[starty+y+3][startx+x+i].getstatus()>0 || pointer->Swall[starty+y+3][startx+x+i].getstatus()>0 || pointer->eagle.checkpos(startx+x+1,starty+y+3)==1 || pointer->eagle.checkpos(startx+x,starty+y+3)==1 || pointer->eagle.checkpos(startx+x+2,starty+y+3)==1 || pointer->water[starty+y+3][startx+x+i].getstatus()>0)
							{freezetime=0; return 0;}
						for(int j=0;j<3;j++)
						{
							if(pointer->yellow.getpos(startx+x+j,starty+y+3)==1)
								{freezetime=0; return 0;}
							if(pointer->green2.getpos(startx+x+j,starty+y+3)==1)
								{freezetime=0; return 0;}
						}
						for(int b=0;b<3;b++)
							for(int j=0;j<3;j++)
								if(pointer->enemy[b].getpos(startx+x+j,starty+y+3)==1 && pointer->enemy[b].getRtime()==0){freezetime=0; return 0;}
						if(pointer->ice[starty+y+3][startx+x+i].getstatus()>0)freezetime=5;
					}
					if (bodyshow == 0)bodyshow = 1;
					else bodyshow = 0;
					y++; Temp++; break;}//вниз
			}
		}		
	}



	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (pointer->Bonus.getpos(startx + x + j, starty + y + i) == 1 && pointer->Bonus.gettime()>0)
			{
				pointer->Bonus.getbonus();
				pointer->Bonus.destroy();
			}//включение бонуса
		}
	}
	///
	for(int i=1;i<=100;i++)
			if(shoot[i].getstate()==1 && shoot[i].gettime()==0)shoot[i].moving();
			else if(shoot[i].gettime()> 0)shoot[i].dectime();
	return 1+Temp;
}
void Tank :: nullenemycount()
{
	for(int r=1;r<=4;r++)
		enemycounter[r]=0;
}