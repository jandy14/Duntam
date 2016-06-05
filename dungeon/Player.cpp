#include "Player.h"
#include "GameManager.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 3;
	this->moveDelay = 0;
	this->moveDelayMax = 10;
	this->health = 10;
}

Player::~Player()
{

}

void Player::Update()
{
	if (moveDelay)
		moveDelay--;
}
void Player::Draw()		//시작 좌표를 기록하는게 좋을 듯 하다
{
	static int count = 0;
	//이전에 남은 그림 지우기(따로 나눠야 할듯)
	if (prevMove != NONE)
	{
		if (prevMove == UP)
		{
			gotoxy((positionX * 2) + 2, positionY + sizeY + 1);
			for (int i = 0; i < sizeX; i++)
				cout << "  ";
		}
		else if (prevMove == DOWN)
		{
			gotoxy((positionX * 2) + 2, positionY - 1 + 1);
			for (int i = 0; i < sizeX; i++)
				cout << "  ";
		}
		else if (prevMove == LEFT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) + (sizeX * 2) + 2, positionY + 1 + i);
				cout << "  ";
			}
		}
		else if (prevMove == RIGHT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) - 2 + 2, positionY + 1 + i);
				cout << "  ";
			}
		}
		prevMove = NONE;
	}
	//이미지 출력
	if (count < 10)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "○";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "< ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << "ㅅ";
	}
	else
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "○";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << " >";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << "ㅅ";
	}
	count++;
	if (count >= 20)
		count = 0;
}
void Player::Damage(int p)
{

}
void Player::Heal(int p)
{

}
void Player::Move(DIRECTION_TYPE dir)
{
	if (moveDelay != 0)	//움직여도 되는지 확인
		return;
	//이동 물론 그전에 충돌 확인하고
	//이동처리 콜리젼 테이블까지(충돌테이블까지)
	Object * target = NULL;
	
	if (IsWall(dir))
		return;

	if (CheckCollision(dir) == NULL)	//충돌 확인
	{
		SetCollision(dir);	//충돌 테이블 설정
		prevMove = dir;		//움직임 저장(Draw용)

		if (dir == UP)		//좌표 갱신
			positionY -= 1;
		else if (dir == DOWN)
			positionY += 1;
		else if (dir == LEFT)
			positionX -= 1;
		else if (dir == RIGHT)
			positionX += 1;

		moveDelay = moveDelayMax;	//딜레이 리셋
	}
}
Object* Player::CheckCollision(DIRECTION_TYPE dir)
{
	Object * target = NULL;
	//자신이 가야하는 곳 전부 체크해서 하나라도 있으면 target의 주소값 리터 없으면 NULL리턴
	if (dir == UP)
	{
		for (int i = 0; i < sizeX; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY - 1][positionX + i];
			if (target != NULL)
				break;
		}
	}
	else if (dir == DOWN)
	{
		for (int i = 0; i < sizeX; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + sizeY][positionX + i];
			if (target != NULL)
				break;
		}
	}
	else if (dir == LEFT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + i][positionX - 1];
			if (target != NULL)
				break;
		}
	}
	else if (dir == RIGHT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX];
			if (target != NULL)
				break;
		}
	}
	return target;
}
void Player::SetCollision(DIRECTION_TYPE dir)
{
	if (dir == UP)
	{
		for (int i = 0; i < sizeX; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY - 1][positionX + i] = this;
			GameManager::GetInstance()->collisionTable[positionY + sizeY - 1][positionX + i] = NULL;
		}
	}
	else if (dir == DOWN)
	{
		for (int i = 0; i < sizeX; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + sizeY][positionX + i] = this;
			GameManager::GetInstance()->collisionTable[positionY][positionX + i] = NULL;
		}
	}
	else if (dir == LEFT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + i][positionX - 1] = this;
			GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX - 1] = NULL;
		}
	}
	else if (dir == RIGHT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX] = this;
			GameManager::GetInstance()->collisionTable[positionY + i][positionX] = NULL;
		}
	}
	else if (dir == NONE)
	{
		for (int y = 0; y < sizeY; y++)
			for (int x = 0; x < sizeX; x++)
				GameManager::GetInstance()->collisionTable[positionY + y][positionX + x] = this;
	}
}
bool Player::IsWall(DIRECTION_TYPE dir)	//인덱스를 넘어가면 true 안전범위면 false
{
	if (dir == UP)
	{
		if (positionY - 1 >= 0)
			return false;
		else
			return true;
	}
	else if (dir == DOWN)
	{
		if (positionY + sizeY - 1 + 1 < 30)
			return false;
		else
			return true;
	}
	else if (dir == LEFT)
	{
		if (positionX - 1 >= 0)
			return false;
		else
			return true;
	}
	else if (dir == RIGHT)
	{
		if (positionX + sizeX - 1 + 1 < 50)
			return false;
		else
			return true;
	}
}