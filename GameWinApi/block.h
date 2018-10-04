#pragma once

class block
{
protected:
	int status;//здоровье блока
	int X;//координатаx
	int Y;//координатаy
	static HWND hWnd;
public:
	block(void){status=0;}
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	virtual void create();//создание блока
	int getstatus();//проверка состояние блока
};
