#include "GameManager.h"

class Room
{
	bool isDoor[4];
	list<Object> objcetList;
};

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void gotoxy(int x, int y)//(옆으로,아래로)가로는 0부터 79까지한줄이다
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetColor(int color, int bgcolor)
{
	bgcolor &= 0xf;
	color &= 0xf;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (bgcolor << 4));
}

void DrawFrame()		//프레임그리기
{
	gotoxy(0, 0);
	for (int i = 0; i < 52; i++)
		cout << "▩";
	for (int i = 1; i < 32; i++)
	{
		gotoxy(0, i);
		cout << "▩";
		gotoxy(102, i);
		cout << "▩";
	}
	gotoxy(0, 31);
	for (int i = 0; i < 52; i++)
		cout << "▩";
	for (int i = 32; i < 37; i++)
	{
		gotoxy(0, i);
		cout << "▩";
		gotoxy(70, i);
		cout << "▩";
		gotoxy(102, i);
		cout << "▩";
	}
	gotoxy(0, 37);
	for (int i = 0; i < 52; i++)
		cout << "▩";
}