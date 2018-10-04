#include "header.h"
extern class battleground *pointer;//указатель на основной объект
extern INT lev;

int mind::etankcounter=0;
int mind::timetillnext = 3600;
int mind::curstate = 1;


mind::mind()
{
	for (int o1 = 0;o1 < 4;o1++)
	{
		badmovecounter[o1] = 0;
		succesmove[o1] = 1;
	}
}
int mind::shoot(int r3)
{
	int direction = pointer->enemy[r3].getdir();
	if ((yX == 0 && abs(yY) <= 10) || (abs(yX) == 1 && abs(yY) <= 10) || (yY == 0 && abs(yX) <= 10) || (abs(yY) == 1 && abs(yX) <= 10))
	{
		if (yX>0 && direction != 4)
		{
			return 3;
		}
		if (yX>0 && direction == 4)
		{
			return 1;
		}
		else if (yX<0 && direction != 2)
		{
			return 4;
		}
		else if (yX<0 && direction == 2)
		{
			return 1;
		}
		else if (yY>0 && direction != 1)
		{
			return 2;
		}
		else if (yY>0 && direction == 1)
		{
			return 1;
		}
		else if (yY<0 && direction != 3)
		{
			return 5;
		}
		else if (yY<0 && direction == 3)
		{
			return 1;
		}
		else return 1;
	}
	else return 100;
}
void mind::timer()
{
	timetillnext--;
	if (timetillnext%1200 == 0 && timetillnext>0)
	{
		curstate++;
	}
}
int mind::automat(int r3)
{	
	if(r3==1)timer();
	pointer->enemy[r3].getposition(myX, myY);
	
	if (curstate == 1)
		return chaosmove(r3);
	else if (curstate == 2)
	{
		if (rand() % 10 != 0)
		{
			if (pointer->yellow.getRtime() == 0 && pointer->green2.getRtime() == 0)
			{
				if (rand() % 2 == 0) return followplayer(r3, 1);
				else return followplayer(r3, 2);
			}
			else if (pointer->yellow.getRtime() == 0)
				return followplayer(r3, 1);
			else if (pointer->green2.getRtime() == 0)
				return followplayer(r3, 2);
			else chaosmove(r3);
		}
		else return chaosmove(r3);
	}
	else if (curstate == 3)
	{
		if (rand() % 10 != 0)
		{
			return followbase(r3);
		}
		else return chaosmove(r3);
	}
	else 
	{ 
		curstate = 3; 
		return rand() % 5 + 1; 
	}
}
int mind::chaosmove(int r3)
{
	pointer->enemy[r3].getposition(myX, myY);

	if (pointer->yellow.getRtime() == 0)
	{
		pointer->yellow.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (pointer->green2.getRtime() == 0)
	{
		pointer->green2.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (etankcounter>0) { etankcounter--;}
	if (etankcounter==0)
	{ 
		for (int i = 0;i<3;i++)etank[i] = rand() % 6; 
		etankcounter = 6; 
	}
	return etank[r3];
}
int mind::followbase(int r3)
{
	pointer->enemy[r3].getposition(myX, myY);

	if (pointer->yellow.getRtime() == 0)
	{
		pointer->yellow.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (pointer->green2.getRtime() == 0)
	{
		pointer->green2.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (succesmove[r3] == 0)badmovecounter[r3]++;
	if (succesmove[r3] == 1)badmovecounter[r3] = 0;
	pointer->eagle.getpos(yX,yY);
	pointer->enemy[r3].getposition(myX, myY);
	int direction = pointer->enemy[r3].getdir();
	yX = myX - yX; yY = myY - yY;
	if ((yX == 0 && abs(yY)<=10) || (abs(yX) == 1 && abs(yY) <= 10) || (yY == 0 && abs(yX) <= 10) || (abs(yY)==1 && abs(yX) <= 10))
	{
		if (yX>0 && direction != 4)
		{
			return 3;
		}
		if (yX>0 && direction == 4)
		{
			return 1;
		}
		else if (yX<0 && direction != 2)
		{
			return 4;
		}
		else if (yX<0 && direction == 2)
		{
			return 1;
		}
		else if (yY>0 && direction != 1)
		{
			return 2;
		}
		else if (yY>0 && direction == 1)
		{
			return 1;
		}
		else if (yY<0 && direction != 3)
		{
			return 5;
		}
		else if (yY<0 && direction == 3)
		{
			return 1;
		}
		else return 1;
	}
	if (succesmove[r3] == 1)
	{
		switch (direction)
		{
		case 1: {return 2; break;}
		case 2: {return 4; break;}
		case 3: {return 5; break;}
		case 4: {return 3; break;}
		}
	}
	else
	{
		if (direction % 2 == 1)
		{
			if (yX>0 && badmovecounter[r3]<2)return 3;
			if (yX<0 && badmovecounter[r3]<2)return 4;
		}
		else if (direction % 2 == 0)
		{
			if (yY>0 && badmovecounter[r3]<2)return 2;
			if (yY<0 && badmovecounter[r3]<2)return 5;
		}
		return rand() % 4 + 2;
	}
}
int mind::followplayer(int r3,int r4)
{
	pointer->enemy[r3].getposition(myX, myY);

	if (pointer->yellow.getRtime() == 0)
	{
		pointer->yellow.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (pointer->green2.getRtime() == 0)
	{
		pointer->green2.getposition(yX, yY);
		yX = myX - yX; yY = myY - yY;
		int temp1 = shoot(r3);
		if (temp1 != 100)return temp1;
	}
	if (succesmove[r3] == 0)badmovecounter[r3]++;
	if (succesmove[r3] == 1)badmovecounter[r3] = 0;
	if(r4==1)pointer->yellow.getposition(yX, yY);
	else if(r4==2)pointer->green2.getposition(yX, yY);
	pointer->enemy[r3].getposition(myX, myY);
	int direction = pointer->enemy[r3].getdir();
	yX = myX - yX; yY = myY - yY;
	if (yX == 0 || yY == 0)
	{
		if (yX>0 && direction != 4)
		{
			return 3;
		}
		else if (yX<0 && direction != 2)
		{
			return 4;
		}
		else if (yY>0 && direction != 1)
		{
			return 2;
		}
		else if (yY<0 && direction != 3)
		{
			return 5;
		}
		else return 1;
	}
	if (succesmove[r3] == 1)
	{
		switch (direction)
		{
		case 1: {return 2; break;}
		case 2: {return 4; break;}
		case 3: {return 5; break;}
		case 4: {return 3; break;}
		}
	}
	else
	{
		if (direction % 2 == 1)
		{
			if (yX>0 && badmovecounter[r3]<2)return 3;
			if (yX<0 && badmovecounter[r3]<2)return 4;
		}
		else if (direction % 2 == 0)
		{
			if (yY>0 && badmovecounter[r3]<2)return 2;
			if (yY<0 && badmovecounter[r3]<2)return 5;
		}
		return rand() % 4 + 2;
	}
}