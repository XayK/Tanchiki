#pragma once
class mind
{
	static int curstate;//������� ���������
	static int timetillnext;//������
	int etank[4];
	int succesmove[4];
	static int etankcounter;
	int badmovecounter[4];
	int myY;
	int myX;
	int yY;
	int yX;
public:
	mind();
	int automat(int r3);//�������� �������
	int followplayer(int r3,int r4);//����� ������
	int followbase(int r3);//����� ����
	int chaosmove(int r3);//������������ ��������
	void timer();
	void again() { curstate = 1; }
	int shoot(int r3);
	void setsm(int r4, int res) { succesmove[r4] = res; }
};

