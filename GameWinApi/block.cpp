#include "header.h"
// ���������� ����������:
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern class battleground *pointer;//��������� �� �������� ������

HWND block::hWnd;

int block :: getstatus()
{
	return status;
}
void block :: create ()
{
	status=1;
}