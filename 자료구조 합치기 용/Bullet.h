#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~Bullet();
	virtual void Update();		//매프레임 처리할 일
	virtual void Draw();		//그려지는 부분 처리
	virtual void Interact(Object& target);	//상호작용
	virtual void Damage(int p);	//데미지 받음
	virtual void Heal(int p);	//치료 받음
};

class EnemyBullet : public Object
{
	EnemyBullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~EnemyBullet();
	virtual void Update();		//매프레임 처리할 일
	virtual void Draw();		//그려지는 부분 처리
	virtual void Interact(Object& target);	//상호작용
	virtual void Damage(int p);	//데미지 받음
	virtual void Heal(int p);	//치료 받음
};