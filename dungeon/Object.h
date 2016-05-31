#pragma once

class Object
{
protected:
	int positionX, positionY;	//위치좌표
	int sizeX, sizeY;			//object크기
	int movedelay, movedelaymax;	//움직임 딜레이와 최댓값
	//char image;					//그려질 이미지;

	void Die();
public:
	Object(int posX,int posY);
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Damage(int p)=0;
	virtual void Heal(int p)=0;
	virtual ~Object();
};