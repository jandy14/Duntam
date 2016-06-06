#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
//인클루드를 더 해줘야할듯
Room::Room(bool isDoor[4], list<Object*>& objectList)
{
	for (int i = 0; i < 4; i++)	//방의 통로 채워줌
		this->isDoor[i] = isDoor[i];
	this->objcetList.assign(objcetList.begin(), objectList.end());	//리스트값 복사
}
Room::Room()
{
	for (int i = 0; i < 4; i++)	//방의 통로 막음
		this->isDoor[i] = false;
	this->objcetList.clear();	//리스트 비워줌
}

GameManager::GameManager()
{
	this->gameState = STARTMENU;
	//그냥 있는다.
}
void GameManager::PrintMap(int mapX, int mapY)
{	
	//맵출력
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (this->map[y][x]->isDoor[0] || this->map[y][x]->isDoor[1] || this->map[y][x]->isDoor[2] || this->map[y][x]->isDoor[3])
			{
				//그리는 위치
				int drawX = mapX + x * 8;
				int drawY = mapY + y * 4;
				//방 그리기
				gotoxy(drawX, drawY);
				cout << "■■■";
				gotoxy(drawX, drawY + 1);
				cout << "■";
				gotoxy(drawX + 4, drawY + 1);
				cout << "■";
				gotoxy(drawX, drawY + 2);
				cout << "■■■";
				//통로 그리기
				if (this->map[y][x]->isDoor[UP])
				{
					gotoxy(drawX + 2, drawY - 1);
					cout << "□";
				}
				if (this->map[y][x]->isDoor[DOWN])
				{
					gotoxy(drawX + 2, drawY + 3);
					cout << "□";
				}
				if (this->map[y][x]->isDoor[LEFT])
				{
					gotoxy(drawX - 2, drawY + 1);
					cout << "□";
				}
				if (this->map[y][x]->isDoor[RIGHT])
				{
					gotoxy(drawX + 6, drawY + 1);
					cout << "□";
				}
			}
		}
	}
}
void GameManager::CreateMap()		//아직 미완성
{
	//여긴 우째야 할지...
	for (int y = 0; y < 9; y++) 
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();

	map[4][4]->isDoor[UP] = true;
	map[4][4]->objcetList.push_front(new EnemyA(0, 0));
}
GameManager* GameManager::GetInstance()
{
	if (singleton == NULL)
		singleton = new GameManager();
	return singleton;
}
void GameManager::DrawFrame()		//프레임그리기
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
void GameManager::DrawStartPage()
{
	static int count = 0;	//화면 출력카운드 (0에서 50까지)
	static bool isPrint = true;	//화면 출력 여부(press ..)
	
	int titleX = 49, titleY = 15;	//제목 위치
	int explanX = 40, explanY = 22;	//설명문 위치
	//시작화면 출력
	gotoxy(titleX,titleY);		//제목
	cout << "Duntam";

	if (count == 50)	//(press ..)깜박거리게 하기용
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			cout << "                        ";
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			cout << "Press spacebar to start!";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawPausePage()
{
	static int count = 0;	//화면 출력 카운트 (0에서 50까지)
	static bool isPrint = true;	//화면 출력 여부(현재 위치)

	int mapX = 16, mapY = 1;		//맵의 시작 위치
	//일시정지 화면 출력
	//맵출력
	this->PrintMap(mapX, mapY);
	//현재 위치 표시(깜박임)
	if (count == 50)
	{
		if (isPrint)
		{
			gotoxy(mapX + (this->nowMapX * 8) + 2, mapY + (this->nowMapY * 4) + 1);
			cout << "★";
			isPrint = false;
		}
		else
		{
			gotoxy(mapX + (this->nowMapX * 8) + 2, mapY + (this->nowMapY * 4) + 1);
			cout << "  ";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawGameOverPage()
{
	//게임오버 화면 출력
	static int count = 0;	//화면 출력카운드 (0에서 50까지)
	static bool isPrint = true;	//화면 출력 여부(press ..)

	int titleX = 47, titleY = 15;	//제목 위치
	int explanX = 37, explanY = 22;	//설명문 위치
									//시작화면 출력
	gotoxy(titleX, titleY);		//제목
	cout << "Game Over!";

	if (count == 50)	//(press ..)깜박거리게 하기용
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			cout << "                              ";
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			cout << "Press spacebar to go startmenu";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::GameSetting()
{
	//맵생성
	this->CreateMap();
	//플레이어 생성
	player = new Player(24,14);
	//오브젝트 리스트 포인터값 설정
	this->nowObjectList = &(map[4][4]->objcetList);
	this->nowMapX = 4;
	this->nowMapY = 4;
	//콜리젼 테이블 설정
	for (int i = 0; i < 30; i++)	//콜리젼 테이블 값 초기화
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//콜리젼 테이블 세팅
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	player->SetCollision(NONE);
}
void GameManager::ObjectUpdate()		//오브젝트리스트 돌면서 Update()실행
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Update();
	player->Update();
}
void GameManager::ObjectDraw()		//오브젝트리스트 돌면서 Draw()실행
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Draw();
	player->Draw();
}
void GameManager::ChangeMap(DIRECTION_TYPE dir)	//맵이동
{
	
	if (dir == UP)				//현재 맵좌표 변경
		this->nowMapY -= 1;
	else if (dir == DOWN)
		this->nowMapY += 1;
	else if (dir == LEFT)
		this->nowMapX -= 1;
	else if (dir == RIGHT)
		this->nowMapX += 1;

	if ((nowMapX <= 0 || nowMapX >= 9) || (nowMapY <= 0 || nowMapY >= 9))	//맵범위 벋어 날까봐 해둔거
		for (;;)
			cout << "map range_out";

	this->nowObjectList = &(map[nowMapY][nowMapX]->objcetList);	//오브젝트리스트의 포인터값 변경

	for (int i = 0; i < 30; i++)		//콜리젼 테이블 값 초기화
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//콜리젼 테이블 세팅
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
}
void GameManager::SetGameState(GAMESTATE_TYPE state)
{
	system("cls");
	if (state == GAMING)
		this->DrawFrame();
	else if(state == PAUSE)
		this->PrintMap(16, 1);	//맵의 시작위치
	this->gameState = state;
}
GameManager* GameManager::singleton;

//맵생성
//각 행동양식	이건 정말 알아서 해라고해야한다
//드로우
//상호 참조(파일)	아무래도 상속받은 놈들의 파일에 포함시켜주는걸로