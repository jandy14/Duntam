#pragma once

#include "Object.h"

using namespace std;

class Enemy : public Object
{
protected:
	list<DIRECTION_TYPE>* movingQueue;	//움직임 예약
	virtual list<DIRECTION_TYPE>* BehaviorPattern();	//움직임큐 채우기
public:
	Enemy(int posX, int posY);
	virtual void Attack() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Interact(Object& target) = 0;
	virtual ~Enemy();
};

class EnemyA : public Enemy
{
protected:
	virtual list<DIRECTION_TYPE>* BehaviorPattern();
public:
	EnemyA(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyA();
};

class EnemyB : public Enemy
{
protected:
	virtual list<DIRECTION_TYPE>* BehaviorPattern();
public:
	EnemyB(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyB();
};

class EnemyC : public Enemy
{
protected:
	int m_maxAttackDelay;
public:
	int m_attackDelay;
	explicit EnemyC();
	explicit EnemyC(int posX, int posY);
	virtual void Attack();
	virtual void Attack(DIRECTION_TYPE& dir);
	virtual void Move(DIRECTION_TYPE dir);
	virtual void AI();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyC();
};

class EnemyD : public EnemyC
{
protected:
	int m_maxAttackDelay;
public:
	int m_attackDelay;
	explicit EnemyD();
	explicit EnemyD(int posX, int posY);
	virtual void AI();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyD();
};

class EnemyE : public EnemyC
{
protected:
	int m_maxAttackDelay;
public:
	int m_attackDelay;
	explicit EnemyE();
	explicit EnemyE(int posX, int posY);
	virtual void AI();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyE();
};