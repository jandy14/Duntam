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
	int m_range;
	int m_attackRange;
	bool m_isAttacked;
	int m_attackDelay;
public:
	explicit EnemyC();
	explicit EnemyC(int posX, int posY);
	virtual void Damage(int p_damage) override;
	virtual void Attack();
	virtual void Attack(DIRECTION_TYPE dir);
	virtual void AI();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyC();
	int GetAttackDelay() { return m_attackDelay; }
	void SetAttackDelay(int p_attackDelay) { m_attackDelay = p_attackDelay; }
	int GetRange() { return m_range; }
	void SetRange(int p_range) { m_range = p_range; }
	bool IsAttacked() { return m_isAttacked; }
	void SetIsAttacked(bool p_isAttacked) { m_isAttacked = p_isAttacked; }
};

class EnemyD : public EnemyC
{
public:
	explicit EnemyD();
	explicit EnemyD(int posX, int posY);
	virtual void AI();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyD();
};

class EnemyE : public EnemyC
{
public:
	explicit EnemyE();
	explicit EnemyE(int posX, int posY);
	virtual void AI();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~EnemyE();
};

class Boss : public EnemyC
{
protected:
	int m_fury;
public:
	explicit Boss();
	explicit Boss(int posX, int posY);
	virtual void Damage(int p_damage) override;
	virtual void Attack();
	virtual void Attack(DIRECTION_TYPE dir);
	virtual void AI();
	virtual void Update();
	virtual void Draw();
	virtual void DrawEye(DIRECTION_TYPE dir, int p_color);
	virtual void DrawArms(float p_delay);
	virtual void Interact(Object& target);
	int GetFury() { return m_fury; }
	void SetFury(int p_fury) { m_fury = p_fury; }
	virtual ~Boss();
};

/*
				   J:
				  J88;
				 JIiii;
		♨		Ji;;;ii;      ♨
		■■	   JIiiiii$$;     ■■
		 ■	  J$$$$$$$$$$;    ■
	  	 ■■■■J$F'_...._':$;■■■■
			J8'.｀JL  :;｀$;
		   JI8b.｀.....'d$$$;
		  Jiii8$$88888$$iii $;
		 Jiiiiiiiiiiiiiiiiiii$;
		""""""""""""""""""""""""


*/