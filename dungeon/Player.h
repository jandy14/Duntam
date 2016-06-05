#pragma once

#include "Object.h"
#include "GameFunc.h"

class Player : public Object
{
public:
	Player(int posX, int posY);
	virtual void Update();
	virtual void Draw();
	virtual void Move(DIRECTION_TYPE dir);
	virtual Object* CheckCollision(DIRECTION_TYPE dir);
	virtual void SetCollision(DIRECTION_TYPE dir);
	virtual bool IsWall(DIRECTION_TYPE dir);
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~Player();
};

