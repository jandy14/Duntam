#pragma once

#include "GameFunc.h"

class Object
{
protected:
	int positionX, positionY;	//위치좌표
	int sizeX, sizeY;			//object크기
	int moveDelay, moveDelayMax;//움직임 딜레이와 최댓값
	int frozing;				//상태이상(얼음)
	int health;					//체력
	int drawCount;				//drawCount
	int interactionCount;		//상호작용Count
	DIRECTION_TYPE prevMove;	//이전 이동 방향(Draw용)
	DIRECTION_TYPE lookingDir;	//보는 방향	
	//char image;				//그려질 이미지

	void Die();
public:
	int TypeName;
	Object(int posX,int posY);
	virtual void Update() = 0;		//매프레임 처리할 일
	virtual void Draw() = 0;		//그려지는 부분 처리
	virtual void Interact(Object& target) = 0; //상호작용
	virtual void Move(DIRECTION_TYPE dir);	//이동 부분
	virtual void Move(int p_x, int p_y, DIRECTION_TYPE dir);
	virtual void ClearImage();				//이미지 정리
	virtual void ClearCollision();			//테이블 정리
	virtual void SetCollision(DIRECTION_TYPE dir);	//충돌 테이블 적용
	virtual Object* CheckCollision(DIRECTION_TYPE dir);	//충돌 확인
	virtual Object* CheckCollision(int posX, int posY);	//충돌 확인 좌표로 확인
	virtual bool IsWall(DIRECTION_TYPE dir);	//게임밖으로 나가는지 체크
	virtual bool IsWall(int p_x, int p_y);
	virtual void RemoveAfterimage();	//잔상 제거
	virtual void Damage(int p);	//데미지 받음
	virtual void Heal(int p);	//치료 받음
	virtual int GetPositionX();	//오브젝트 X좌표
	virtual int GetPositionY();	//오브젝트 Y좌표
	virtual void SetDrawCountZero();	//drawcount  = 0;
	virtual void SetPosition(int posX, int posY);	//오브젝트 좌표 설정
	virtual void SetLookingDir(DIRECTION_TYPE dir);	//보는 방향 설정
	virtual DIRECTION_TYPE GetLookingDir();			//보는 방향 값
	virtual ~Object();
};

//메소드 정리 좀 해야겠다 가상 메소든지 동적 바인딩같은 문제도 생각해보고 말이다.