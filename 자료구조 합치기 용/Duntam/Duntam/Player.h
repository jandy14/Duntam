#pragma once

#include "Object.h"
#include "GameFunc.h"

class Player : public Object
{
public:
	bool isDie;

	Player(int posX, int posY);
	void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual void Damage(int p);
	virtual ~Player();
};

