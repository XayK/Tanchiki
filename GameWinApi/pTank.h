#pragma once
#include "battleground.h"
#include "bullet.h"

class pTank
{
protected:
	int lifes;//���������� �����
	int bcount;//������� ��������
	int dir;//����������� ��������
	int x;//����������x
	int y;//����������y
	int startx;//��������� �����������
	int starty;//�������� ����������y
	int MapX;//������� ����� �� x � y
	int MapY;
	int godtime;
	char identy;
	int bodyshow;
	int shoottime;//���������� ��������
	int Rtime;//����� �� �����������
	int freezetime;//����� ��������� ����������
	int tanklevel;//������� �����
	INT deathtime;
	HDC memBitUp[2], memBitRight[2], memBitDown[2], memBitLeft[2];
	HBITMAP hBitmapUp[2], hBitmapRight[2], hBitmapDown[2], hBitmapLeft[2];
	BITMAP bmUp[2], bmRight[2], bmDown[2], bmLeft[2];
	HDC memBit;
	HBITMAP hBitmap;
	BITMAP bm;
	static HDC RmemBit[4],GmemBit[2];
	static HBITMAP RhBitmap[4],GhBitmap[2];
	static BITMAP Rbm[4],Gbm[2];
	static HWND hWnd;
public:
	bullet shoot[150];//������� �����
	pTank()	{bodyshow = 0;}
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	virtual void die() {}//��������� ������ �����
	void show(HDC hdc);
	void loaddeath(int id);
	virtual void showb(HDC hdc) {}
	virtual void setti() {}//�������� �����
	virtual int move(int button) { return 0; }//������� �� ������������� � ��������� �����
	int getlifes() { return lifes; }
	void destroy(HDC hdc);//����� �����
	virtual void getstart(int z, int z2, int z12, int z22) {}//����������� �����
	int getpos(int x3, int y3);//������ ���������
	int getRtime() { return Rtime; }
	void decRtime() { Rtime--; }
	virtual void load(int number) {}//�������� ����� ��������� �����
	void pluslife() { lifes++; }
	void freeze(int temp) { freezetime = temp; }
	int getdir() { return dir; }
	static void loadresp();
	void respawing(HDC hdc);
	void getposition(int &r1, int &r2) { r1 = x + startx;r2 = y + starty; }
};

