#pragma once

class Object
{
protected:
	int positionX, positionY;	//위치좌표
	int sizeX, sizeY;			//object크기
	int moveDelay, moveDelayMax;//움직임 딜레이와 최댓값
	int frozing;				//상태이상(얼음)
	int health;					//체력
	//char image;				//그려질 이미지

	void Die();
public:
	Object(int posX,int posY);
	virtual void Update() = 0;		//매프레임 처리할 일
	virtual void Draw() = 0;		//그려지는 부분 처리
	virtual void Move() = 0;		//이동 부분
	virtual void SetCollision() = 0;//충돌 확인
	virtual void Damage(int p) = 0;	//데미지 받음
	virtual void Heal(int p) = 0;	//치료 받음
	virtual ~Object();
};