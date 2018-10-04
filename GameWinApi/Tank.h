#pragma once
#include "battleground.h"
#include "bullet.h"
#include "pTank.h"

class Tank : public pTank
{
	int enemycounter[5];
	int score;
	int player;
	int numberplayer;
	static int players;
public:
	Tank();
	void die();
	void setti();
	void setplayer(int pla){player=pla;}
	int move(int button);
	void getstart(int z,int z2,int z12, int z22);
	void inctlevel(){if(tanklevel<4)tanklevel++; load(tanklevel);}
	void load(int number);
	void godmode(int temp2){godtime=temp2;}
	int getgodtime(){return godtime;}
	int getscore(){return score;}
	void incscore(int scor){score+=scor;}
	void incenemycount(int r){enemycounter[r]++;}
	int getenemycount(int r){return enemycounter[r];}
	void nullenemycount();
	void zeroscore(){score=0;}
};
