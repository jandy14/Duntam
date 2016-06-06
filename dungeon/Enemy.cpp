#include "Enemy.h"
#include "GameManager.h"


Enemy::Enemy(int posX,int posY) : Object(posX,posY)
{
	this->movingQueue = new list<DIRECTION_TYPE>();
}
Enemy::~Enemy()
{

}

EnemyA::EnemyA(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 2;
	this->sizeY = 1;
	this->moveDelayMax = 20;
	this->health = 10;
	this->frozing = 200;
}
EnemyA::~EnemyA()
{
	 
}
void EnemyA::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
	
	if (moveDelay == 0)
	{
		if (movingQueue->size() == 0)	//움직임큐가 비면 다시 채워준다
		{
			delete movingQueue;
			movingQueue = BehaviorPattern();
		}
		if (movingQueue->size() != 0)
		{
			Move(movingQueue->front());
			movingQueue->pop_front();
		}
	}
}
void EnemyA::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "저억";

	SetColor(7, 16);
}
void EnemyA::Damage(int p)
{

}
void EnemyA::Heal(int p)
{

}
list<DIRECTION_TYPE>* EnemyA::BehaviorPattern()
{
	list<DIRECTION_TYPE>* movingQueue = new list<DIRECTION_TYPE>();
	movingQueue->push_front((DIRECTION_TYPE)random(4));
	return movingQueue;
}

EnemyB::EnemyB(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 2;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
}
void EnemyB::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	if (moveDelay == 0)
	{
		if (movingQueue->size() == 0)	//움직임큐가 비면 다시 채워준다
		{
			delete movingQueue;
			movingQueue = BehaviorPattern();
		}
		if (movingQueue->size() != 0)
		{
			Move(movingQueue->front());
			movingQueue->pop_front();
		}
	}
}
void EnemyB::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "저";
	gotoxy(2 + (positionX * 2), 1 + positionY + 1);
	cout << "억";

	SetColor(7, 16);
}
void EnemyB::Damage(int p)
{

}
void EnemyB::Heal(int p)
{

}
list<DIRECTION_TYPE>* EnemyB::BehaviorPattern()
{
	list<DIRECTION_TYPE>* movingQueue = new list<DIRECTION_TYPE>();
	int pX = GameManager::GetInstance()->player->GetPositionX();
	int pY = GameManager::GetInstance()->player->GetPositionY();

	bool flag[4] = { false,false,false,false };
	if ((this->positionX - pX) > 0)
		flag[2] = true;
	else if ((this->positionX - pX) < 0)
		flag[3] = true;
	if ((this->positionY - pY) > 0)
		flag[0] = true;
	else if ((this->positionY - pY) < 0)
		flag[1] = true;

	if (random(2))
	{
		if(flag[0] == true)
			movingQueue->push_front(UP);
		else if(flag[1] == true)
			movingQueue->push_front(DOWN);
	}
	else
	{
		if (flag[2] == true)
			movingQueue->push_front(LEFT);
		else if(flag[3] == true)
			movingQueue->push_front(RIGHT);
	}

	if(movingQueue->size() == 0)
		movingQueue->push_front((DIRECTION_TYPE)random(4));

	return movingQueue;
}
EnemyB::~EnemyB()
{

}