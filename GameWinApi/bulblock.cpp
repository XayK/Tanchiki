#include "header.h"
// ���������� ����������:
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern class battleground *pointer;//��������� �� �������� ������
extern int lev;

bulblock::bulblock(void)
{
}

void bulblock::clear(void)
{
	status=0;
}
void bulblock::create(class bullet *temppoint)
{
	status=1;
	mybul=temppoint;
}
void bulblock::destroy(void)
{
	mybul->destructor();
}
