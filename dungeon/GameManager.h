#pragma once

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include<list>
#include"mapinfo.h"
#include "Object.h"

using namespace std;

#define randomize() srand((unsigned)time(NULL))	//매크로 함수
#define random(n) (rand() % (n))

#define FRAME 100	//이론적인 프레임수
#define FPS 60		//실제 돌아가느 프레임수 (실험값)

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;	//커서타입정의
typedef enum { UP, DOWN, LEFT, RIGHT } DIRECTION_TYPE;				//방향타입
typedef enum { STARTMENU, GAMING, PAUSE, GAMEOVER } GAMESTATE_TYPE;	//게임상태타입

void setcursortype(CURSOR_TYPE c);		//커서 모양 지정함수
void gotoxy(int x, int y);				//(옆으로,아래로)
void SetColor(int color, int bgcolor);	//색 지정함수


//==========================================던탐 관련

class gameview
{
	int sx, sy;
	int width, height;
};
class stateview
{

};

class massageview
{

};

class Room
{
	bool isDoor[4];
	list<Object>* objcetList;

	Room(bool isDoor[4], list<Object>& objectList);
	~Room();
};

class GameManager
{
	Room map[9][9];
	list<Object>* nowObjectList;

	GameManager();
	void DrawFrame();			//프레임그리기
	~GameManager();
};