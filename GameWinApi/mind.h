#pragma once
class mind
{
	static int curstate;//текущее состояние
	static int timetillnext;//таймер
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
	int automat(int r3);//основная функция
	int followplayer(int r3,int r4);//поиск игрока
	int followbase(int r3);//поиск базы
	int chaosmove(int r3);//произвольное движение
	void timer();
	void again() { curstate = 1; }
	int shoot(int r3);
	void setsm(int r4, int res) { succesmove[r4] = res; }
};

