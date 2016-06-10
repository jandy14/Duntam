#pragma once
#include "Object.h"

class Block : public Object
{
public:
	Block(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~Block();
};

