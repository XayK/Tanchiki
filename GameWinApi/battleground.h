#pragma once
#include "Tank.h"
#include "brick.h"
#include "beton.h"
#include "base.h"
#include "enemyTank.h"
#include "mask.h"
#include "bonus.h"
#include "iceblock.h"
#include "waterblock.h"
#include "bulblock.h"
#include "mind.h"

class battleground
{
	int **board;//игрова€ карты
	int mapsizex;//ширина карты
	int mapsizey;//высота карты
	int enemyleft;//кол-во оставшихс€ врагов
	int GameStatus;//состо€ние игры
	int level;//номер карты
	int sound;//вк/выкл звук
	int players;//кол-во игроков
	int curplaysoundy;
	static HWND hWnd;
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
public:
	brick **Rwall;//кирпичные стены
	beton **Swall;//беттоные стены
	mask **green;//ћаскировачные кусты
	iceblock **ice;//лед€нные блоки
	waterblock **water;//вод€ные блоки
	bulblock **bullblock;//коллизион модель пуль
	base eagle;//создание базы
	Tank yellow;//вызов танка
	Tank green2;//2-ой игрок
	enemyTank enemy[3];//танк компьютера
	bonus Bonus;//спавн бонуса
	mind II;//»»
	battleground(int l,int pl,int sd);
	void starter(HWND thWnd);//отрисовка карты
	void refresh();//обновление текстовой информации
	void stopgame();//конец игры
	int getgame();
	int getsound(){return sound;}
	int getplayers(){return players;}
	int getenemy(){return enemyleft;}
	void decenemy();
	void setting1();//загрузка карт
	int getposboard(int y4,int x4);
	void scoring();//подсчет очков
	void events(INT butto);//цикл игры
};
