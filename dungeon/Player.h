#pragma once

#include "Object.h"
#include "GameFunc.h"

class Player : public Object
{
public:
	Player(int posX, int posY);
	void Attack();
	virtual void Update();
	virtual void Draw();
	virtual ~Player();
};

