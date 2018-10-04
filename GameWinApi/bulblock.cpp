#include "header.h"
// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern class battleground *pointer;//указатель на основной объект
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
