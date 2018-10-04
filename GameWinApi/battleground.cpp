#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
extern INT lev;
extern PAINTSTRUCT ps;
extern HDC hdc;
HPEN hpen1 = CreatePen(PS_SOLID, 16, RGB(0, 128, 128));

INT checky;

TCHAR strlev[] = _T("STAGE       ");
TCHAR strscore[] = _T("SCORE:     ");
TCHAR *strenem[] = { _T("Enemy") ,_T("Left:           ") };
TCHAR *strlife[] = { _T("Lifes if Y:  ") ,_T("Lifes if G:  ") };
TCHAR text[128];
TCHAR mess[512];

HFONT newFont = CreateFont(120, 60, 0, 0, 700, 0, 0, 0,
DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,_T("Arcade"));

HDC hdcmem;
HANDLE  hOld;
HBITMAP hbmmem;

HWND battleground::hWnd;

battleground::battleground(int l,int pl,int sd)
{
	curplaysoundy = 0;
	GameStatus=1;
	level=l; players=pl;
	enemyleft=20; sound=sd;
	mciSendString(TEXT("open music/tankstay.wav  type waveaudio alias tankstay"), NULL, 0, NULL);
	mciSendString(TEXT("open music/tankmove.wav  type waveaudio alias tankmove"), NULL, 0, NULL);

}
void battleground :: setting1()
{
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAME_OVER));
	GetObject(hBitmap, sizeof(bm), &bm);
	hdc = GetDC(hWnd);
	memBit = CreateCompatibleDC(hdc);
	SelectObject(memBit, hBitmap);
	ReleaseDC(hWnd, hdc);//картинка для гамес овер

	brick::load();
	beton::load();
	mask::load();
	iceblock::load();
	waterblock::load();
	bullet::load();
	eagle.load();
	pTank::loadresp();

	FILE *fp;
	switch(level)
	{
		case 1:{fp=fopen("map1.txt","r+"); break;}
		case 2:{fp=fopen("map2.txt","r+"); break;}
		case 3:{fp=fopen("map3.txt","r+"); break;}
		case 4:{fp=fopen("map4.txt","r+"); break;}
		case 5:{fp=fopen("map5.txt","r+"); break;}
		//case 6:{fp=fopen("map6.txt","r+"); break;}
		//case 7:{fp=fopen("map7.txt","r+"); break;}
		case 100: {fp = fopen("mapbonus.txt", "r+"); break;}
		default:{fp=fopen("map1.txt","r+"); level=1; break;}
	}//открытие файла карты
	fscanf(fp,"%d %d",&mapsizex,&mapsizey);//размеры карты
	int tmp1,tmp2,tmp3,tmp4;
	fscanf(fp,"%d %d",&tmp1,&tmp2);//начальная нашего позиция танка
	yellow.getstart(tmp1,tmp2,mapsizex,mapsizey);//передача позиции танка
	fscanf(fp,"%d %d",&tmp1,&tmp2);//начальная нашего позиция танка 2-го игрока
	if(players==2)
		green2.getstart(tmp1,tmp2,mapsizex,mapsizey);
	for(int i=0;i<3;i++){
		fscanf(fp,"%d %d",&tmp3,&tmp4);
		enemy[i].getstart(tmp3,tmp4,mapsizex,mapsizey);
	}//начальная позиция танка компьютера
	//if (Rwall != nullptr)delete Rwall;
	brick **mas1=new brick*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas1[z]=new brick[mapsizex];
	Rwall=mas1;
	//Создание массива под кирпич
	//if (Swall != nullptr)delete Swall;
	beton **mas2=new beton*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas2[z]=new beton[mapsizex];
	Swall=mas2;
	//Создание массива под бетон
	//if (green != nullptr)delete green;
	mask **mas3=new mask*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas3[z]=new mask[mapsizex];
	green=mas3;
	//создание массива под кусты
	//if (ice != nullptr)delete ice;
	iceblock **mas4=new iceblock*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas4[z]=new iceblock[mapsizex];
	ice=mas4;
	//создание массива под лед
	//if (water != nullptr)delete water;
	waterblock **mas5=new waterblock*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas5[z]=new waterblock[mapsizex];
	water=mas5;
	//создание массива под воду
	//if (bullblock != nullptr)delete bullblock;
	bulblock **mas6=new bulblock*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas6[z]=new bulblock[mapsizex];
	bullblock=mas6;
	//создание массива под коллизион пуль
	int **mas=new int*[mapsizey];
	for(int z=0;z<mapsizey;z++)
		mas[z]=new int[mapsizex];
	for(int z=0;z<mapsizey;z++)
		for(int z2=0;z2<mapsizex;z2++)
		{
			char cha;
			fscanf(fp,"%c",&cha);
			if(cha=='\n') fscanf(fp,"%c",&cha);
			mas[z][z2]=cha-'0';
			switch(mas[z][z2])
		    {
				case 2:{green[z][z2].create(); break;}
				case 3:{ice[z][z2].create(); break;}
				case 4:{Rwall[z][z2].create(); break;}
			    case 5:{eagle.create(z2,z); break;}
				case 8:{Swall[z][z2].create(); break;}
				case 9:{water[z][z2].create(); break;}
				
			}
		}
	board=mas;
	pointer=this;
	yellow.setplayer(1);
	yellow.nullenemycount();
	green2.nullenemycount();
	if(players==2)
	{
		green2.setplayer(2);
	}
	fclose(fp);
}
void battleground :: refresh()
{
	hdc = GetDC(hWnd);

	// Создаем off-screen DC для двойной буферизации
	hdcmem = CreateCompatibleDC(hdc);
	hbmmem = CreateCompatibleBitmap(hdc, POINT*mapsizex, POINT*mapsizey);
	hOld = SelectObject(hdcmem, hbmmem);

	// Здесь рисуем в hdcMem
	SelectObject(hdcmem, hpen1);
	MoveToEx(hdcmem, 0, 0, NULL);
	LineTo(hdcmem, 0, POINT*mapsizey);
	LineTo(hdcmem, POINT*mapsizex, POINT*mapsizey);
	LineTo(hdcmem, POINT*mapsizex, 0);
	LineTo(hdcmem, 0, 0);
	for (int i = 0;i<mapsizey;i++)//отрисовка карты
	{
		for (int j = 0;j<mapsizex;j++)
		{
			if (Rwall[i][j].getstatus()>0)Rwall[i][j].show(j, i, hdcmem);
			else if (Swall[i][j].getstatus()>0)Swall[i][j].show(j, i, hdcmem);
			else if (ice[i][j].getstatus()>0)ice[i][j].show(j, i, hdcmem);
			else if (water[i][j].getstatus()>0)water[i][j].show(j, i, hdcmem);
			else if (eagle.getstatus()>0)eagle.show(hdcmem);

		}
	}
	yellow.show(hdcmem);//передача позиции танка
	if (players == 2)
		green2.show(hdcmem);
	for (int i = 0;i < 3;i++)//танк управляемый ии
	{
		enemy[i].show(hdcmem);
	}
	Bonus.refresh(hdcmem);//отрисока бонуса
	for (int i = 0;i < mapsizey;i++)//отрисовка карты
	{
		for (int j = 0;j < mapsizex;j++)
		{
			if (green[i][j].getstatus()>0)green[i][j].show(j, i, hdcmem);
		}
	}
	// Выводим построенное  изображение и памяти на экран
	BitBlt(hdc, 0, 0, POINT*mapsizex, POINT*mapsizey, hdcmem, 0, 0, SRCCOPY);

	// Освобождаем память
	SelectObject(hdcmem, hOld);
	DeleteObject(hbmmem);
	DeleteDC(hdcmem);

	ReleaseDC(hWnd,hdc);

	//	//Место отрисовки таблицы результатов
	hdc = GetDC(hWnd);

	SetBkColor(hdc, RGB(96, 96, 96));
	SetTextColor(hdc,RGB(0,0,0));

	_itow(level, text, 10);  wcscpy(mess,strlev);   wcscat(mess,text);
	TextOut(hdc,POINT*mapsizex+40,40, mess, _tcsclen(mess));

	_itow(yellow.getscore() + green2.getscore(), text, 10); wcscpy(mess, strscore);   wcscat(mess, text);
	TextOut(hdc, POINT*mapsizex + 40, 80, mess, _tcsclen(mess));

	TextOut(hdc, POINT*mapsizex+40, 120, strenem[0], _tcsclen(strenem[0]));
	_itow(enemyleft, text, 10);  wcscpy(mess, strenem[1]);   wcscat(mess, text);
	TextOut(hdc, POINT*mapsizex+40, 140, mess, _tcsclen(mess));

	_itow(yellow.getlifes(), text, 10);  wcscpy(mess, strlife[0]);   wcscat(mess, text);
	TextOut(hdc, POINT*mapsizex + 40, 180, mess, _tcsclen(mess));
	if (players == 2)
	{
		_itow(green2.getlifes(), text, 10);  wcscpy(mess, strlife[1]);   wcscat(mess, text);
		TextOut(hdc, POINT*mapsizex + 40, 210, mess, _tcsclen(mess));
	}
	ReleaseDC(hWnd,hdc);
		/*cout << "LEVEL: " << level<< "   ";
		p.Y+=3;
		setcur();
		cout << "SCORE: " << yellow.getscore()+green2.getscore()<< "   ";
		p.Y+=3;
		setcur();
		cout << "LIFES OF ";  	
		text = 6; background = 0;
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
		cout << 'Y';
		text = 7; background = 0;
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
		cout << " PLAYER: " << yellow.getlifes() << "   ";
		if(players==2)
		{
			p.Y+=3;
			setcur();
			cout << "LIFES OF ";
			text = 10; background = 0;
			SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
			cout << 'G';
			text = 7; background = 0;
			SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
			cout <<" PLAYER: " << green2.getlifes()<< "   ";
		}
		p.Y+=3;
		setcur();
		cout << "ENEMY'S LEFT: " << enemyleft << "   "; */

	//if(Bonus.gettime()>0){Bonus.refresh(); if(Bonus.gettime()==0) Bonus.destroy();}
}
void battleground::events(INT button)
{
		refresh();
		if (button == 72 || button == 75 || button == 80 || button == 77 || button == 48) checky = yellow.move(button);
		else checky = yellow.move(0);
		
		if (!(curplaysoundy == 1 && checky == 2) && !(curplaysoundy == 2 && checky <= 1))
		{
			if (checky == 2){ mciSendString(TEXT("stop tankstay"), NULL, 0, NULL); mciSendString(TEXT("play tankmove"), NULL, 0, NULL);
			 curplaysoundy = 1;	}
			else { mciSendString(TEXT("stop tankmove"), NULL, 0, NULL);	 mciSendString(TEXT("play tankstay"), NULL, 0, NULL);
			curplaysoundy = 2; }
		}

		for (int i = 0;i < 3;i++)//танк управляемый ии
		{
			if (enemy[i].gettlevel() == 2)
			{
				enemy[i].move(II.automat(i));
			}
			enemy[i].move(II.automat(i));
		}
		II.timer();
}
void battleground :: starter(HWND thWnd=nullptr)
{
	if (thWnd != nullptr)
	{
		hWnd = thWnd;
		block::setHWND(thWnd);
		base::setHWND(thWnd);
		bonus::setHWND(thWnd);
		bullet::setHWND(thWnd);
		pTank::setHWND(thWnd);
	}
	setting1();
	hdc = GetDC(hWnd);
	SelectObject(hdc, hpen1);
	MoveToEx(hdc,0,0,NULL);
	LineTo(hdc, 0, POINT*mapsizey);
	LineTo(hdc, POINT*mapsizex, POINT*mapsizey);
	LineTo(hdc, POINT*mapsizex, 0);
	LineTo(hdc, 0, 0);
	/*HRGN hRgn;
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	RECT pRect = { POINT*1,POINT*1, POINT*(mapsizex-1), POINT*(mapsizey-1) };
	hRgn = CreateRectRgnIndirect(&pRect);
	FillRgn(hdc, hRgn, hBrush);*/
	ReleaseDC(hWnd,hdc);
	//отрисовка границ карты

	yellow.show(hdc);//передача позиции танка
	if (players == 2)
		green2.show(hdc);
	for (int i = 0;i < 3;i++)
		enemy[i].getstart(0, 0, mapsizex, mapsizey);
	for(int i=0;i<mapsizey;i++)//отрисовка карты
	{
		for(int j=0;j<mapsizex;j++)
		{
			if(Rwall[i][j].getstatus()>0)Rwall[i][j].show(j,i, hdc);
			else if(Swall[i][j].getstatus()>0)Swall[i][j].show(j,i, hdc);
			else if(green[i][j].getstatus()>0)green[i][j].show(j,i, hdc);
			else if(ice[i][j].getstatus()>0)ice[i][j].show(j,i, hdc);
			else if(water[i][j].getstatus()>0)water[i][j].show(j,i, hdc);
			else if(eagle.getstatus()>0)eagle.show(hdc);

		}
	}
	yellow.nullenemycount();
	if(players==2)
		green2.nullenemycount();
}
void battleground :: stopgame()
{
	GameStatus=0;
	PlaySound(TEXT("music/loose.wav"), NULL, SND_ASYNC | SND_FILENAME);
	Sleep(2000);

 	hdc = GetDC(hWnd);
	TransparentBlt(hdc, POINT*mapsizex/2-16, POINT*mapsizey / 2 - 16, bm.bmWidth, bm.bmHeight, memBit, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 255, 0));
	ReleaseDC(hWnd, hdc);
}
int battleground :: getgame()
{
	return GameStatus;
}
void battleground :: decenemy()
{
	enemyleft--; //уменьшение противника
	if(enemyleft==0)
	{
		scoring();//подсчет очков
		level++;
		setting1(); 
		yellow.setti(); green2.setti();
		II.again();
		for(int i=0;i<3;i++)
			enemy[i].setti(); 
		enemyleft=20; this->starter();
	}//переход на следующий уровень
}
int battleground :: getposboard(int y4,int x4)
{
	if(board[y4][x4]==0)return 1;
	else return 0;
}
void battleground :: scoring()
{
	/*SetConsoleCP(866);
	SetConsoleOutputCP(866);
	text=12; background=0;	
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	setcur(33,3);
	cout << "ЫЫЫЫ ЫЫЫЫ  ЫЫЫ  ЫЫЫЫ Ы  Ы ЫЫЫ ЫЫЫ";p.Y++; setcur();
	cout << "Ы  Ы Ы  Ы  Ы Ы  Ы  Ы Ы  Ы Ы    Ы ";p.Y++; setcur();
	cout << "Ы  Ы Ы  Ы  Ы Ы  Ы    ЫЫЫЫ ЫЫЫ  Ы ";p.Y++; setcur();
	cout << "Ы  Ы Ы  Ы ЫЫЫЫЫ Ы  Ы    Ы Ы    Ы ";p.Y++; setcur();
	cout << "Ы  Ы ЫЫЫЫ Ы   Ы ЫЫЫЫ    Ы ЫЫЫ  Ы ";
	text=11; background=0;
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	setcur(46,15);
	cout << "  TANK   "; p.Y++; setcur();
	cout << "-=FIRST=-"; p.Y++; setcur();
	cout << "  LEVEL   ";
	setcur(46,20);
	cout << "  TANK   ";p.Y++; setcur();
	cout << "<=SECON=>"; p.Y++; setcur();
	cout << "  LEVEL  ";
	setcur(46,25);
	cout << "  TANK   ";p.Y++; setcur();
	cout << "-=THIRD=-"; p.Y++; setcur();
	cout << "  LEVEL  ";
	setcur(46,30);
	cout << "  TANK   ";p.Y++; setcur();
	cout << "<=FOUR =>"; p.Y++; setcur();
	cout << "  LEVEL  ";
	Sleep(350);*/
	//SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	//setcur(38,16);
	//cout << yellow.getenemycount(1);
	//setcur(60,16);
	//cout << green2.getenemycount(1);
	//Sleep(350);
	////танк первого уровня
	//setcur(38,21);
	//cout << yellow.getenemycount(2);
	//setcur(60,21);
	//cout << green2.getenemycount(2);
	//Sleep(350);
	////танк второго уровня
	//setcur(38,26);
	//cout << yellow.getenemycount(3);
	//setcur(60,26);
	//cout << green2.getenemycount(3);
	//Sleep(350);
	////танк третьего уровня
	//setcur(38,31);
	//cout << yellow.getenemycount(4);
	//setcur(60,31);
	//cout << green2.getenemycount(4);
	//Sleep(350);
	////танк четвертого уровня
	//text=11; background=0;	
	//SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	//setcur(40,35);
	//cout << "-----------------------";
	//setcur(46,37);
	//cout << "<= SCORE =>";
	//Sleep(350);
	//text=7; background=0;	
	//SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	//setcur(38,37);
	//cout << yellow.getscore();
	//setcur(60,37);
	//cout << green2.getscore()<< endl << "      ";
}