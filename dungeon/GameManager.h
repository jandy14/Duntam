#pragma once

#include"GameFunc.h"
#include"Player.h"


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
	friend class MapInfo;
private:
	bool isDoor[4];
	list<Object*> objectList;
public:
	Room(bool isDoor[4], list<Object*>& objectList);
	Room();
	bool IsDoor(DIRECTION_TYPE dir);	//이쪽에 문이 있는지
	bool IsUse();	//사용되는 방인지 확인
	~Room();
};

class GameManager
{
private:
	static GameManager* singleton;	//하나만 생성된다
	GameManager();					//싱글톤이라 생성자가 private
	void PrintMap(int mapX,int mapY);	//맵출력
	void CreateDebugMap();				//디버그용맵생성
	void CreateMap();
public:
	Room* map[9][9];				//맵정보
	list<Object*>* nowObjectList;	//현재 방 오브젝트리스트
	Object* collisionTable[30][50];	//현재 방 충돌 테이블
	list<string> message;			//메세지리스트
	int nowMapX, nowMapY;			//현재 방 좌표
	GAMESTATE_TYPE gameState;		//현재 게임 상태
	Player * player;				//플레이어

	static GameManager * GetInstance();	//게임매니저 객체얻기
	void KeyEvent();			//키입력
	void DrawFrame();			//전체 프레임그리기
	void DrawPausePage();		//일시정지 화면 출력
	void DrawStartPage();		//게임 시작 화면 출력
	void DrawGameOverPage();	//게임 오버 화면 출력
	void DrawChangeMap();		//맵변환시 보이는 화면
	void PrintPlayerState();	//플레이어 상태 출력
	void GameSetting();			//게임 시작전 준비
	void ObjectUpdate();		//nowObjectList의 Object들의 Update()실행
	void ObjectDraw();			//nowObjectList의 Object들의 Draw()실행
	void SetMessage(list<string>& newMessage);	//메세지 내용 고침
	void NextMessage();			//메세지리스트의 다음내용 출력
	DIRECTION_TYPE IsMapChange();	//맵변경상황인지 확인
	void ChangeMap(DIRECTION_TYPE dir);	//맵변경
	void SetGameState(GAMESTATE_TYPE state);	//게임 상태 변경
	~GameManager();
};