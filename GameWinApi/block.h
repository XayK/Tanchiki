#pragma once

class block
{
protected:
	int status;//�������� �����
	int X;//����������x
	int Y;//����������y
	static HWND hWnd;
public:
	block(void){status=0;}
	static void setHWND(HWND thWnd) { hWnd = thWnd; }
	virtual void create();//�������� �����
	int getstatus();//�������� ��������� �����
};
