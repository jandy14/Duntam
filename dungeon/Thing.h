#pragma once
#include "Object.h"
class Thing : public Object
{
public:
	Thing(int posX, int posY);
	virtual void Attack()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Interact(Object& target)=0;
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~Thing();
};

class AltarOfLuck : public Thing
{
private:
	int drawCount;
	int instractionCount;
public:
	AltarOfLuck(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~AltarOfLuck();
};

class BulletTrap : public Thing
{
private:
	int instractionCount;
	DIRECTION_TYPE lookingDir;
	int attackDelay;
	int attackDelayMax;
public:
	BulletTrap(int posX, int posY, DIRECTION_TYPE dir);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~BulletTrap();
};

class Teleporter : public Thing
{
private:
	int instractionCount;
	int drawCount;
	int warpPointX, warpPointY;	//워프되는 위치
public:
	Teleporter(int posX, int posY, int warpX, int warpY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~Teleporter();
};