#include "Enemy.h"



Enemy::Enemy(int posX,int posY) : Object(posX,posY)
{
	this->movingQueue = new list<DIRECTION_TYPE>();
}
Enemy::~Enemy()
{

}

EnemyA::EnemyA(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 1;
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
	cout << "적";

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
	list<DIRECTION_TYPE>* temp = new list<DIRECTION_TYPE>();
	temp->push_front((DIRECTION_TYPE)random(4));
	return temp;
}