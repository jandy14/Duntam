#include "GameManager.h"
#include "ReadMapInfo.h"
#include "Block.h"
#include "Thing.h"

//#include<algorithm>
//인클루드를 더 해줘야할듯
using namespace std;

Room::Room(bool isDoor[4], list<Object*>& objectList)
{
	for (int i = 0; i < 4; i++)	//방의 통로 채워줌
		this->isDoor[i] = isDoor[i];
	this->objectList.assign(objectList.begin(), objectList.end());	//리스트값 복사
}
Room::Room()
{
	for (int i = 0; i < 4; i++)	//방의 통로 막음
		this->isDoor[i] = false;
	this->objectList.clear();	//리스트 비워줌
}
Room::~Room()
{
	//해야한다
	while (objectList.size() != 0)
	{
		delete objectList.front();
		objectList.pop_front();
	}
}
bool Room::IsDoor(DIRECTION_TYPE dir)
{
	return this->isDoor[dir];
}
bool Room::IsUse()
{
	return this->isDoor[UP] || this->isDoor[DOWN] || this->isDoor[LEFT] || this->isDoor[RIGHT];
}

GameManager::GameManager()
{
	this->gameState = STARTMENU;
	//그냥 있는다.
}
GameManager::~GameManager()
{
	/*for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			delete map[y][x];
		}
	}*/
	/*for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 50; x++)
			collisionTable[y][x] = NULL;
	}*/

	//delete nowObjectList;	
	//delete player;			
	//delete singleton;
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
				printf("■■■");
				gotoxy(drawX, drawY + 1);
				printf("■");
				gotoxy(drawX + 4, drawY + 1);
				printf("■");
				gotoxy(drawX, drawY + 2);
				printf("■■■");
				//통로 그리기
				if (this->map[y][x]->isDoor[UP])
				{
					gotoxy(drawX + 2, drawY - 1);
					printf("□");
				}
				if (this->map[y][x]->isDoor[DOWN])
				{
					gotoxy(drawX + 2, drawY + 3);
					printf("□");
				}
				if (this->map[y][x]->isDoor[LEFT])
				{
					gotoxy(drawX - 2, drawY + 1);
					printf("□");
				}
				if (this->map[y][x]->isDoor[RIGHT])
				{
					gotoxy(drawX + 6, drawY + 1);
					printf("□");
				}
			}
		}
	}
}
void GameManager::CreateDebugMap()		//아직 미완성
{
	//여긴 우째야 할지...
	for (int y = 0; y < 9; y++) 
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();

	MapInfo mapInfo;

	//시작방
	map[4][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[4][4], "MapInfo/Debug/02.csv");
	//적 사이즈방
	map[3][4]->isDoor[DOWN] = true;
	map[3][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[3][4], "MapInfo/Debug/04.csv");
	map[3][4]->objectList.push_back(new Boss(1, 1));
	map[3][4]->objectList.push_back(new EnemyA(4, 5));
	map[3][4]->objectList.push_back(new EnemyB(45, 5));
	map[3][4]->objectList.push_back(new EnemyB(47, 5));
	//a*와 그냥의 비교
	map[2][4]->isDoor[DOWN] = true;
	map[2][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[2][4], "MapInfo/Debug/07.csv");
	map[2][4]->objectList.push_back(new EnemyD(1, 25));
	map[2][4]->objectList.push_back(new EnemyB(1, 27));
	//미로푸는 a*
	map[1][4]->isDoor[DOWN] = true;
	map[1][4]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][4], "MapInfo/Debug/00.csv");
	map[1][4]->objectList.push_back(new EnemyD(7,22));
	map[1][4]->objectList.push_back(new EnemyD(1,12));
	map[1][4]->objectList.push_back(new EnemyD(27,12));
	map[1][4]->objectList.push_back(new EnemyD(48,18));
	//워프 일반
	map[1][5]->isDoor[LEFT] = true;
	map[1][5]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][5], "MapInfo/Debug/01.csv");
	map[1][5]->objectList.push_back(new Teleporter(3, 15, 45, 15));
	//포탈
	map[1][6]->isDoor[LEFT] = true;
	map[1][6]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][6], "MapInfo/Debug/10.csv");
	map[1][6]->objectList.push_back(new Teleporter_sounghoo(7, 15, 42, 15));
	map[1][6]->objectList.push_back(new Teleporter_sounghoo(42, 15, 7, 15));
	//포탈이용하는 a*
	map[1][7]->isDoor[LEFT] = true;
	map[1][7]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][7], "MapInfo/Debug/05.csv");
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 4, 46, 13));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 13, 46, 4));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 27, 46, 17));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 17, 46, 27));
	map[1][7]->objectList.push_back(new EnemyD(3, 3));
	map[1][7]->objectList.push_back(new EnemyD(4, 4));
	map[1][7]->objectList.push_back(new EnemyB(3, 27));
	map[1][7]->objectList.push_back(new EnemyB(4, 26));
	//총탄방
	map[1][8]->isDoor[LEFT] = true;
	map[1][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[1][8], "MapInfo/Debug/08.csv");
	map[1][8]->objectList.push_back(new EnemyD(48, 2));
	//힐방
	map[2][8]->isDoor[UP] = true;
	map[2][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[2][8], "MapInfo/Debug/03.csv");
	map[2][8]->objectList.push_back(new AltarOfHeal(20, 2));
	map[2][8]->objectList.push_back(new AltarOfHeal(30, 2));
	map[2][8]->objectList.push_back(new AltarOfHeal(20, 25));
	map[2][8]->objectList.push_back(new AltarOfHeal(30, 25));
	//적C방
	map[3][8]->isDoor[UP] = true;
	map[3][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[3][8], "MapInfo/Debug/09.csv");
	map[3][8]->objectList.push_back(new EnemyE(48, 28));
	//도착
	map[4][8]->isDoor[UP] = true;
	mapInfo.SetRoom(map[4][8], "MapInfo/Debug/06.csv");
	map[4][8]->objectList.push_back(new ClearObject(24, 14));

	map[4][4]->objectList.push_back(new ClearObject(24, 15));

}
void GameManager::CreateMap()
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();
			
	//너비우선
	list<int> nextMake;	//다음에 만들어질 방 번호
	nextMake.push_front(40);
	list<int>::iterator nowMake = nextMake.begin();
	for (int index = 0; nowMake != nextMake.end(); nowMake++, index++)
	{
		list<DIRECTION_TYPE> makeDoor;	//방에서 문이 생길 방향을 넣어둔다.
		do
		{
			for (int i = 0; i < 4; i++)
			{
				if (*nowMake / 9 == 0 && i == 0)	//못가는 곳 미리 차단
					continue;
				if (*nowMake / 9 == 8 && i == 1)
					continue;
				if (*nowMake % 9 == 0 && i == 2)
					continue;
				if (*nowMake % 9 == 8 && i == 3)
					continue;
				if (!(map[*nowMake / 9][*nowMake % 9]->IsDoor((DIRECTION_TYPE)i)))	//문이 없으면
				{
					if (random(100) < 80 - (index*3))	//확률이 점점 낮아진다 80%에서
					{
						if (random(2))
							makeDoor.push_back((DIRECTION_TYPE)i);
						else
							makeDoor.push_front((DIRECTION_TYPE)i);
					}
				}
			}
		}while (makeDoor.size() == 0 && *nowMake == 40);	//do while쓸일이 다있네

		for (; makeDoor.size() != 0;)	//하나씩 꺼내서 문을 만든다
		{
			switch (makeDoor.front())
			{
			case UP:
				if (!(map[(*nowMake / 9) - 1][*nowMake % 9]->IsUse()))	
					nextMake.push_back(*nowMake - 9);					//push_back을 insert로 바꾸면 깊이우선이 된다
				map[*nowMake / 9][*nowMake % 9]->isDoor[UP] = true;
				map[(*nowMake / 9) - 1][*nowMake % 9]->isDoor[DOWN] = true;
				break;
			case DOWN:
				if (!(map[(*nowMake / 9) + 1][*nowMake % 9]->IsUse()))
					nextMake.push_back(*nowMake + 9);
				map[*nowMake / 9][*nowMake % 9]->isDoor[DOWN] = true;
				map[(*nowMake / 9) + 1][*nowMake % 9]->isDoor[UP] = true;
				break;
			case LEFT:
				if (!(map[*nowMake / 9][(*nowMake % 9) - 1]->IsUse()))
					nextMake.push_back(*nowMake - 1);
				map[*nowMake / 9][*nowMake % 9]->isDoor[LEFT] = true;
				map[*nowMake / 9][(*nowMake % 9) - 1]->isDoor[RIGHT] = true;
				break;
			case RIGHT:
				if (!(map[*nowMake / 9][(*nowMake % 9) + 1]->IsUse()))
					nextMake.push_back(*nowMake + 1);
				map[*nowMake / 9][*nowMake % 9]->isDoor[RIGHT] = true;
				map[*nowMake / 9][(*nowMake % 9) + 1]->isDoor[LEFT] = true;
				break;
			}
			makeDoor.pop_front();
		}
	}
	//nextMake를 이용해서 안에 내용도 채워줘야할듯하다
	MapInfo mapInfo;
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (map[y][x]->IsUse())
				mapInfo.SetRoom(map[y][x]);
		}
	}
	while (true)
	{
		int goal = random(81);
		if (map[goal / 9][goal % 9]->IsUse() && goal != 40)
		{
			map[goal / 9][goal % 9]->objectList.push_back(new ClearObject(24, 14));
			gotoxy(0, 0);
			cout << (goal % 9) << (goal / 9);
			Sleep(100);
			break;
		}
	}
}
GameManager* GameManager::GetInstance()
{
	if (singleton == NULL)
		singleton = new GameManager();
	return singleton;
}
void GameManager::KeyEvent()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)//(위)
	{
		this->player->Move(UP);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)//(아래)
	{
		this->player->Move(DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//(왼)
	{
		this->player->Move(LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//(오른)
	{
		this->player->Move(RIGHT);
	}

	if (GetAsyncKeyState(0x57) == (short)0x8001)	//(W)위
		this->player->SetLookingDir(UP);
	if (GetAsyncKeyState(0x53) == (short)0x8001)	//(S)아래
		this->player->SetLookingDir(DOWN);
	if (GetAsyncKeyState(0x41) == (short)0x8001)	//(A)왼
		this->player->SetLookingDir(LEFT);
	if (GetAsyncKeyState(0x44) == (short)0x8001)	//(D)오른
		this->player->SetLookingDir(RIGHT);

	if (GetAsyncKeyState(0x45) == (short)0x8001)	//(E)상호작용
	{
		if (!(this->player->IsWall(this->player->GetLookingDir())))
		{
			Object * target = this->player->CheckCollision(this->player->GetLookingDir());
			if (target != NULL)
				target->Interact(*(this->player));
		}
	}
	if (GetAsyncKeyState(0x4B) == (short)0x8001)	//(K)자살
	{
		player->Damage(999);
	}
	if (GetAsyncKeyState(0x51) == (short)0x8001)	//(Q)슈퍼파워
	{
		player->SetSuperPower(100);
	}
	if (GetAsyncKeyState(0x49) == (short)0x8001)	//(I)얼음화살 토글
	{
		player->ToggleIceArrow();
	}
	if (GetAsyncKeyState(VK_RETURN) == (short)0x8001)	//(엔터) 다음 메세지
	{
		NextMessage();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)//(스페이스)공격
	{
		this->player->Attack();
	}
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		this->player->moveDelay = 0;
	}

	if (GetAsyncKeyState(0x50) & 0x0001)//(P)일시정지
		this->SetGameState(PAUSE);
}
void GameManager::DrawFrame()		//프레임그리기
{
	gotoxy(0, 0);
	for (int i = 0; i < 52; i++)
		printf("▩");
	for (int i = 1; i < 32; i++)
	{
		gotoxy(0, i);
		printf("▩");
		gotoxy(102, i);
		printf("▩");
	}
	gotoxy(0, 31);
	for (int i = 0; i < 52; i++)
		printf("▩");
	for (int i = 32; i < 37; i++)
	{
		gotoxy(0, i);
		printf("▩");
		gotoxy(70, i);
		printf("▩");
		gotoxy(102, i);
		printf("▩");
	}
	gotoxy(0, 37);
	for (int i = 0; i < 52; i++)
		printf("▩");
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
	//this->PrintMap(mapX, mapY);		//없어도 될듯(최적화할때 1순위ㅋ)
	//현재 위치 표시(깜박임)
	if (count == 30)
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
void GameManager::DrawGameClearPage()
{
	//게임오버 화면 출력
	static int count = 0;	//화면 출력카운드 (0에서 50까지)
	static bool isPrint = true;	//화면 출력 여부(press ..)

	int titleX = 47, titleY = 15;	//제목 위치
	int explanX = 37, explanY = 22;	//설명문 위치
									//시작화면 출력
	gotoxy(titleX, titleY);		//제목
	puts("Game Clear!");
	gotoxy(titleX - 2, titleY + 1);
	puts("Congratulation!!");

	if (count == 50)	//(press ..)깜박거리게 하기용
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			puts("                              ");
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			puts("Press spacebar to go startmenu");
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawChangeMap()
{
	for (int y = 0; y < 30; y++)
	{
		gotoxy(2, 1 + y);
		for (int x = 0; x < 50; x++)
			printf("  ");
	}
}
void GameManager::PrintPlayerState()
{
	gotoxy(4, 33);
	if (player->superPower > 50000)
	{
		SetColor((player->superPower % 7) + 9, 16);
		printf("SuperPower : 큰수 ");
		SetColor(7, 16);
	}
	else if (player->superPower > 1)
	{
		SetColor((player->superPower % 7) + 9, 16);
		printf("SuperPower : %5d", player->superPower);
		SetColor(7, 16);
	}
	else if (player->superPower == 1)
	{
		puts("                    ");
	}
	gotoxy(24, 33);
	if (player->frozing > 50000)
	{
		SetColor(11, 16);
		printf("Frozing : 큰수 ");
		SetColor(7, 16);
	}
	else if (player->frozing > 1)
	{
		SetColor(11, 16);
		printf("Frozing : %5d", player->frozing);
		SetColor(7, 16);
	}
	else if (player->frozing == 1)
	{
		puts("                ");
	}
	gotoxy(4, 35);
	cout << "HP : " << to_string(player->health) << "  ";
	if (player->iceArrow)
	{
		SetColor(11, 16);
		puts("IceArrow");
		SetColor(7, 16);
	}
	else
		puts("        ");
}
void GameManager::GameSetting(int mode)
{
	//맵생성
	if (mode == 0)
		this->CreateMap();
	else
		this->CreateDebugMap();
	//플레이어 생성
	player = new Player(24,14);
	//오브젝트 리스트 포인터값 설정
	this->nowObjectList = &(map[4][4]->objectList);
	this->nowMapX = 4;
	this->nowMapY = 4;
	//메세지 정리
	this->message.clear();
	//콜리젼 테이블 설정
	for (int i = 0; i < 30; i++)	//콜리젼 테이블 값 초기화
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;
			

	list<Object*>::iterator iter = this->nowObjectList->begin();	//콜리젼 테이블 세팅
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	player->SetCollision(NONE);
}
void GameManager::ClearRoom()
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			delete map[y][x];
}
void GameManager::ObjectUpdate()		//오브젝트리스트 돌면서 Update()실행
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (;iter != this->nowObjectList->end(); iter++)
		(*iter)->Update();
	player->Update();
	//죽은거 처리
	while (dieObjectList.size() != 0)
	{
		delete dieObjectList.front();
		dieObjectList.pop_front();
	}
}
void GameManager::ObjectDraw()		//오브젝트리스트 돌면서 Draw()실행
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Draw();
	player->Draw();
}
void GameManager::ObjectDrawCountZero()
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetDrawCountZero();
	player->SetDrawCountZero();
}
void GameManager::SetMessage(list<string>& newMessage)
{
	//기존의 메세지 삭제 및 새로 복사
	this->message.clear();

	if (newMessage.size() == 0)
		return;
	this->message.assign(newMessage.begin(), newMessage.end());
	//첫메세지 출력
	gotoxy(72, 34);
	puts("                              ");
	gotoxy(72, 34);
	cout << this->message.front();
	this->message.pop_front();

}
void GameManager::NextMessage()
{
	gotoxy(72, 34);
	puts("                              ");
	gotoxy(72, 34);
	if (this->message.size() != 0)
	{
		//메세지 출력
		cout << this->message.front();
		//리스트에서 삭제
		this->message.pop_front();
	}
}
DIRECTION_TYPE GameManager::IsMapChange()
{
	if (player->GetPositionX() == 24 && player->GetPositionY() == 0)
		return UP;
	else if (player->GetPositionX() == 24 && player->GetPositionY() == 29)
		return DOWN;
	else if (player->GetPositionX() == 0 && player->GetPositionY() == 14)
		return LEFT;
	else if (player->GetPositionX() == 49 && player->GetPositionY() == 14)
		return RIGHT;
	else
		return NONE;
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

	this->player->RemoveAfterimage();	//잔상 미리 제거

	if (dir == UP)				//플레이어 위치 변경
		this->player->SetPosition(25,29);
	else if (dir == DOWN)
		this->player->SetPosition(25, 0);
	else if (dir == LEFT)
		this->player->SetPosition(49, 15);
	else if (dir == RIGHT)
		this->player->SetPosition(0, 15);

	

	if ((nowMapX < 0 || nowMapX >= 9) || (nowMapY < 0 || nowMapY >= 9))	//맵범위 벋어 날까봐 해둔거
		for (;;)
			puts("map range_out");

	this->nowObjectList = &(map[nowMapY][nowMapX]->objectList);	//오브젝트리스트의 포인터값 변경


	for (int i = 0; i < 30; i++)		//콜리젼 테이블 값 초기화
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//콜리젼 테이블 세팅
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	this->player->SetCollision(NONE);

	ObjectDrawCountZero();

	//디스플레이
	DrawChangeMap();
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