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
	int **board;//������� �����
	int mapsizex;//������ �����
	int mapsizey;//������ �����
	int enemyleft;//���-�� ���������� ������
	int GameStatus;//��������� ����
	int level;//����� �����
	int sound;//��/���� ����
	int players;//���-�� �������
	int curplaysoundy;
	static HWND hWnd;
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
public:
	brick **Rwall;//��������� �����
	beton **Swall;//�������� �����
	mask **green;//������������� �����
	iceblock **ice;//�������� �����
	waterblock **water;//������� �����
	bulblock **bullblock;//��������� ������ ����
	base eagle;//�������� ����
	Tank yellow;//����� �����
	Tank green2;//2-�� �����
	enemyTank enemy[3];//���� ����������
	bonus Bonus;//����� ������
	mind II;//��
	battleground(int l,int pl,int sd);
	void starter(HWND thWnd);//��������� �����
	void refresh();//���������� ��������� ����������
	void stopgame();//����� ����
	int getgame();
	int getsound(){return sound;}
	int getplayers(){return players;}
	int getenemy(){return enemyleft;}
	void decenemy();
	void setting1();//�������� ����
	int getposboard(int y4,int x4);
	void scoring();//������� �����
	void events(INT butto);//���� ����
};
