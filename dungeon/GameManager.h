#pragma once

#include"GameFunc.h"
#include"Object.h"

using namespace std;




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
	friend class GameManager;
private:
	bool isDoor[4];
	list<Object*> objcetList;
public:
	Room(bool isDoor[4], list<Object*>& objectList);
	Room();
	~Room();
};

class GameManager
{
private:
	static GameManager* singleton;	//하나만 생성된다
	GameManager();					//싱글톤이라 생성자가 private
	void PrintMap(int mapX,int mapY);	//맵출력
	void CreateMap();				//맵생성
public:
	Room* map[9][9];				//맵정보
	list<Object*>* nowObjectList;	//현재 방 오브젝트리스트
	Object* collisionTable[30][50];	//현재 방 충돌 테이블
	int nowMapX, nowMapY;			//현재 방 좌표
	GAMESTATE_TYPE gameState;		//현재 게임 상태
	Object * player;				//플레이어

	static GameManager * GetInstance();	//게임매니저 객체얻기
	void DrawFrame();			//전체 프레임그리기
	void DrawPausePage();		//일시정지 화면 출력
	void DrawStartPage();		//게임 시작 화면 출력
	void DrawGameOverPage();	//게임 오버 화면 출력
	void GameSetting();			//게임 시작전 준비
	void ObjectUpdate();		//nowObjectList의 Object들의 Update()실행
	void ObjectDraw();			//nowObjectList의 Object들의 Draw()실행
	void ChangeMap(DIRECTION_TYPE dir);	//맵변경
	void SetGameState(GAMESTATE_TYPE state);	//게임 상태 변경
	~GameManager();
};