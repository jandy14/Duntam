#pragma once

#include "Object.h"
#include "GameFunc.h"

class Player : public Object
{
	friend class GameManager;
	int damageCount;
	int superPower;				//슈퍼파워
	bool iceArrow;				//얼음화살 활성화
public:
	bool isDie;

	Player(int posX, int posY);
	void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual void Damage(int p);
	void SetSuperPower();
	void ToggleIceArrow();
	virtual ~Player();
};

