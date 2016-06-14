/***************************************************
		  접근 방식, 맵생성, 객체 생성
***************************************************///할일이다 한일이아니라
#pragma warning(disable : 4996)

#include"GameManager.h"

using namespace std;

int main()
{
	//==================================================================================시작 전 작업
	setcursortype(NOCURSOR);				//커서 안보이기
	system("mode con: lines=39 cols=104");	//콘솔창 조절
	
	GameManager *gameManager = GameManager::GetInstance();	//게임매니저 생성

	//===================================================================================프레임워크

	int count = 0;
	int timer = time(NULL);
	while (1)
	{
		//프레임을 유지하기 위해 시작시간과 끝난시간을 구해 빨리 끝났을 경우 딜레이를 준다
		int start = GetTickCount();


		if (gameManager->gameState == STARTMENU/*게임 시작화면*/)
		{
			//시작화면 출력 함수
			gameManager->DrawStartPage();
			//스페이스바 누르면 게임 시작
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)	//게임 세팅(맵생성) 게임상태(게임중)
			{
				randomize();
				gameManager->GameSetting(0);
				gameManager->SetGameState(GAMING);
			}
			else if (GetAsyncKeyState(0x44) == (short)0x8001)
			{
				randomize();
				gameManager->GameSetting(1);
				gameManager->SetGameState(GAMING);
			}
		}

		if(gameManager->gameState == GAMING/*게임 진행중*/)
		{

			gameManager->ObjectUpdate();	//오브젝트 업데이트

			gameManager->ObjectDraw();	//오브젝트 그리기

			gameManager->PrintPlayerState();	//플레이어 상태 출력

			//키보드 이벤트
			gameManager->KeyEvent();
			//상태 정보 그리기

			//맴변환
			DIRECTION_TYPE dir = gameManager->IsMapChange();

			if (dir != NONE)
			{
				if (gameManager->map[gameManager->nowMapY][gameManager->nowMapX]->IsDoor(dir))
				{
					gameManager->ChangeMap(dir);//맵변환
					Sleep(300);					//잠시 뜸들임 (0.5초)
				}
			}
			//플레이어 사망시
			if (gameManager->player->isDie)
			{
				delete gameManager->player;
				gameManager->SetGameState(GAMEOVER);
			}

		}

		if (gameManager->gameState == PAUSE/*일시 정지*/)
		{
			//일시 정시 화면 출력
			gameManager->DrawPausePage();
			//키 이벤트 확인 하고 있으면 다시 게임으로 아니면 계속 루프
			if (GetAsyncKeyState(0x50) == (short)0x8001)
			{
				gameManager->ObjectDrawCountZero();
				gameManager->SetGameState(GAMING);
			}

		}


		if (gameManager->gameState == GAMEOVER/*게임 오버*/)
		{
			//게임오버 화면 출력
			gameManager->DrawGameOverPage();

			//그리고 다시 게임 시작화면 true
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)
			{
				gameManager->ClearRoom();
				gameManager->SetGameState(STARTMENU);
			}
		}

		if (gameManager->gameState == GAMECLEAR/*게임 오버*/)
		{
			//게임오버 화면 출력
			gameManager->DrawGameClearPage();

			//그리고 다시 게임 시작화면 true
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)
			{
				delete gameManager->player;
				gameManager->ClearRoom();
				gameManager->SetGameState(STARTMENU);
			}
		}


		int wait = (1000/FRAME) - (GetTickCount() - start);
		if(wait >= 0)
			Sleep(wait);
		count++;
		if (timer != time(NULL))
		{
			gotoxy(0, 0);
			printf("FPS : %d",count);
			count = 0;
			timer = time(NULL);
		}
	}
	//================================================================================끝나고 정리
	return 0;
}

//bullet의 update()
	//이동이 가능하면 이동해준다
//block의 update()
	//가만히 있는다
//thing의 update()
	//몇몇은 할일이 있을지도 모른다
