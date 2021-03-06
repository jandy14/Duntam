#pragma once
#include "Object.h"
#include "GameManager.h"

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
public:
	EnemyBullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~EnemyBullet();
	virtual void Update();		//¸???·¹?? ?³¸®?? ??
	virtual void Draw();		//±×·???´? º?ºÐ ?³¸®
	virtual void Interact(Object& target);	//??????¿?
	virtual void Damage(int p);	//??¹??? ¹Þ?½
	virtual void Heal(int p);	//?¡·? ¹Þ?½
};

class HomingBullet : public EnemyBullet
{
public:
	HomingBullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~HomingBullet();
	virtual void Update();
	virtual void AI();
};

class BombBullet : public Bullet
{
protected:
	bool isExplosion;		//터질지 확인
public:
	BombBullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~BombBullet();
	virtual void Update();		//매프레임 처리할 일
	virtual void Draw();		//그려지는 부분 처리
	virtual void Interact(Object& target);	//상호작용
};

class IceArrow : public Bullet
{
protected:
public:
	IceArrow(int posX, int posY, DIRECTION_TYPE lookingDir);
	~IceArrow();
	virtual void Update();		//매프레임 처리할 일
	virtual void Draw();		//그려지는 부분 처리
	virtual void Interact(Object& target);	//상호작용
	virtual void Frozing(int p);		//얼음 면역이라 오버라이딩
};