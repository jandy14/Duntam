#pragma once

#include<windows.h>
#include<time.h>
#include<iostream>
#include<list>
#include<string>
#include<math.h>

#define randomize() srand((unsigned)time(NULL))	//매크로 함수
#define random(n) (rand() % (n))

#define FRAME 100	//이론적인 프레임수
#define FPS 60		//실제 돌아가느 프레임수 (실험값)

static const double PI = 3.141592;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;	//커서타입정의
typedef enum { UP, DOWN, LEFT, RIGHT, NONE } DIRECTION_TYPE;		 //방향타입
typedef enum { STARTMENU, GAMING, PAUSE, GAMEOVER, GAMECLEAR } GAMESTATE_TYPE;	//게임상태타입

void setcursortype(CURSOR_TYPE c);		//커서 모양 지정함수
void gotoxy(int x, int y);				//(옆으로,아래로)
void SetColor(int color, int bgcolor);	//색 지정함수
