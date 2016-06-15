#include "Object.h"
#include "GameManager.h"

Object::Object(int posX, int posY)
{
	this->positionX = posX;
	this->positionY = posY;
	this->lookingDir = NONE;
	this->prevMove = NONE;
	this->moveDelay = 0;
	this->frozing = 0;
	this->TypeName = 0;
	this->interactionCount = 0;
	this->drawCount = 0;
}

Object::~Object()
{

	if(GameManager::GetInstance()->gameState == GAMING)
		GameManager::GetInstance()->nowObjectList->remove(this);

}
void Object::Move(DIRECTION_TYPE dir)
{
	if (moveDelay > 0)	//움직여도 되는지 확인
		return;
	if (health <= 0)	//피는 있는지
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

		lookingDir = dir;

		if (frozing)		//딜레이 리셋
			moveDelay = moveDelayMax * 3; //frozing 상태일땐 3배 느려짐
		else
			moveDelay = moveDelayMax;
	}
	else if (CheckCollision(dir)->TypeName == 52)
	{
		CheckCollision(dir)->Interact(*this);
	}
}
// Object::Move(int p_x, int p_y,DIRECTION_TYPE dir)
//{
//	if (moveDelay > 0)	//움직여도 되는지 확인
//		return;
//	//이동 물론 그전에 충돌 확인하고
//	//이동처리 콜리젼 테이블까지(충돌테이블까지)
//	Object * target = NULL;
//
//	if (IsWall(p_x,p_y))
//		return;
//
//	if (CheckCollision(p_x,p_y) == NULL)	//충돌 확인
//	{
//		SetPosition(p_x, p_y);
//		SetCollision(NONE);	//충돌 테이블 설정
//		prevMove = dir;		//움직임 저장(Draw용)
//
//		lookingDir = dir;
//
//		if (frozing)		//딜레이 리셋
//			moveDelay = moveDelayMax * 3; //frozing 상태일땐 2배 느려짐
//		else
//			moveDelay = moveDelayMax;
//	}
//}
Object* Object::CheckCollision(DIRECTION_TYPE dir)
{
	Object * target = NULL;
	//자신이 가야하는 곳 전부 체크해서 하나라도 있으면 target의 주소값 리턴 없으면 NULL리턴
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
Object* Object::CheckCollision(int posX, int posY)
{
	Object* target = NULL;
	target = GameManager::GetInstance()->collisionTable[posY][posX];
	return target;
}
void Object::ClearImage()
{
	for (int y = 0; y < sizeY; y++)
	{
		gotoxy((positionX * 2) + 2, positionY + y + 1);
		for (int x = 0; x < sizeX; x++)
			printf("  ");
	}
}
void Object::ClearCollision()
{
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
			GameManager::GetInstance()->collisionTable[positionY + y][positionX + x] = NULL;
}
void Object::SetCollision(DIRECTION_TYPE dir)
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
bool Object::IsWall(DIRECTION_TYPE dir)	//인덱스를 넘어가면 true 안전범위면 false
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
bool Object::IsWall(int p_x, int p_y)	//인덱스를 넘어가면 false 안전범위면 true
{
	if ((0 <= p_x && p_x + sizeX - 1 < 50) && (0 <= p_y && p_y + sizeY - 1 < 30))
		return true;
	else
		return false;
}
void Object::RemoveAfterimage()
{
	if (prevMove != NONE)
	{
		if (prevMove == UP)
		{
			gotoxy((positionX * 2) + 2, positionY + sizeY + 1);
			for (int i = 0; i < sizeX; i++)
				printf("  ");
		}
		else if (prevMove == DOWN)
		{
			gotoxy((positionX * 2) + 2, positionY - 1 + 1);
			for (int i = 0; i < sizeX; i++)
				printf("  ");
		}
		else if (prevMove == LEFT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) + (sizeX * 2) + 2, positionY + 1 + i);
				printf("  ");
			}
		}
		else if (prevMove == RIGHT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) - 2 + 2, positionY + 1 + i);
				printf("  ");
			}
		}
		prevMove = NONE;
	}
}
int Object::GetPositionX()
{
	return this->positionX;
}
int Object::GetPositionY()
{
	return this->positionY;
}
int Object::GetSizeX()
{
	return sizeX;
}
void Object::SetSizeX(int p_size)
{
	sizeX = p_size;
}
int Object::GetSizeY()
{
	return sizeY;
}
void Object::SetSizeY(int p_size)
{
	sizeY = p_size;
}
void Object::SetDrawCountZero()
{
	this->drawCount = 0;
}
void Object::SetPosition(int posX, int posY)
{
	this->ClearCollision();
	this->ClearImage();
	if (posX + sizeX - 1 < 50 && posX >= 0)
		this->positionX = posX;
	else if (posX < 0)
		this->positionX = 0;
	else
		this->positionX = 49 - sizeX + 1;
	
	if (posY + sizeY - 1 < 30 && posY >= 0)
		this->positionY = posY;
	else if (posY < 0)
		this->positionY = 0;
	else
		this->positionY = 29 - sizeY + 1;
	this->SetCollision(NONE);
}
void Object::Damage(int p)
{
	this->health -= p;
	if (this->health <= 0)
		this->Die();
}
void Object::Heal(int p)
{
	this->health += p;
	if (health > 100000000)
		health = 100000000;
}
void Object::Frozing(int p)
{
	this->frozing += p;
	if (frozing > 100000000)
		frozing = 100000000;
}
void Object::SetLookingDir(DIRECTION_TYPE dir)
{
	if (dir != NONE)
		lookingDir = dir;
}
DIRECTION_TYPE Object::GetLookingDir()
{
	return lookingDir;
}
void Object::Die()
{
	//dieObjectList에 넣고
	GameManager::GetInstance()->dieObjectList.push_back(this);
	//콜리전테이블에서 지우고
	this->ClearCollision();
	//화면에 그려진것도 지운다
	this->ClearImage();
	this->RemoveAfterimage();
}