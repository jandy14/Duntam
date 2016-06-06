#pragma once

#include "Object.h"

using namespace std;

class Enemy : public Object
{
protected:
	list<DIRECTION_TYPE>* movingQueue;	//움직임 예약
	virtual list<DIRECTION_TYPE>* BehaviorPattern() = 0;	//움직임큐 채우기
public:
	Enemy(int posX, int posY);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Damage(int p) = 0;
	virtual void Heal(int p) = 0;
	virtual ~Enemy();
};

class EnemyA : public Enemy
{
protected:
	virtual list<DIRECTION_TYPE>* BehaviorPattern();
public:
	EnemyA(int posX, int posY);
	virtual void Update();
	virtual void Draw();
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~EnemyA();
};

class EnemyB : public Enemy
{

};