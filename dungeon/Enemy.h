#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	Enemy(int posX, int posY);
	virtual void Update();
	virtual void Draw();
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~Enemy();
};

