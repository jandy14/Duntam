/***************************************************
		  충돌체크 테이블, 오브텍트 리스트,
		  실제 돌아가는지 확인, 클래스 구현
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
			
			//스페이스바 누르면 게임 시작
			if (GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				//맵생성알고리즘 실행
				//게임 진행중을 true
			}
		}

		if(gameManager->gameState == GAMING/*게임 진행중*/)
		{

			gameManager->ObjectUpdate();	//오브젝트 업데이트

			//키보드 이벤트
			if (GetAsyncKeyState(0x57))//w
			{
				printf("%d\n", GetTickCount());
			}

			gameManager->ObjectDraw();	//오브젝트 그리기

			//맵이 변하면
			if (false/*맵 변환*/)
			{
				DIRECTION_TYPE dir;			//방향값

				gameManager->ChangeMap(dir);//맵변환
				Sleep(300);					//잠시 뜸들임 (0.5초)
			}
		}

		if (gameManager->gameState == PAUSE/*일시 정지*/)
		{
			//일시 정시 화면 출력
			//맵 상태표시도 같이 해줄까

			//키 이벤트 확인 하고 있으면 다시 게임으로 아니면 계속 루프
			if (GetAsyncKeyState(0x50) & 0x0001)
			{
				//다시 게임중 true
			}

		}


		if (gameManager->gameState == GAMEOVER/*게임 오버*/)
		{
			
			//게임오버 화면 출력

			//그리고 다시 게임 시작화면 true
			if (GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				// 게임 시작화면 true
			}
		}


		int wait = (1000/FRAME) - (GetTickCount() - start);
		if(wait >= 0)
			Sleep(wait);
		count++;
		if (timer != time(NULL))
		{
			//cout << count << endl;
			count = 0;
			timer = time(NULL);
		}
	}
	//================================================================================끝나고 정리
	return 0;
}

void UPDATE()
{
	//리스트를 순회하면서 update()메소드를 실행시킨다.
	//각 객체의 update()메소드는 내용이 다르므로 각각 설명한다.
}

void display()
{
	//리스트를 순회하면서    각 오브젝트의 draw()메소드를 실행시킨다
	//draw()도 다르니 각각설명
}

//player의 update()
	//각 상태이상의 카운터를 세어 준다
//enemy의 update()
	//각 상태이상의 카운터를 세어 준다
	//이동이 가능하면 이동해준다
	//AI의 알고리즘을 통해 이동 리스트를 넣어준다
//bullet의 update()
	//이동이 가능하면 이동해준다
//block의 update()
	//가만히 있는다
//thing의 update()
	//몇몇은 할일이 있을지도 모른다


//draw()
	//우선 화면을 지워준다
	//각각의 사이즈가 다르므로 각자의 draw()메소드를 실행 시킨다
