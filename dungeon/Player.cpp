#include "Player.h"
#include "GameManager.h"
#include "Bullet.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->damageCount = 0;
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 5;
	this->health = 10;
	this->frozing = 0;
	this->lookingDir = DOWN;
	this->isDie = false;
	this->superPower = 0;
	this->iceArrow = false;
}

Player::~Player()
{

}

void Player::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
	if (superPower)
		superPower--;
}
void Player::Draw()		//시작 좌표를 기록하는게 좋을 듯 하다
{
	//이전에 남은 그림 지우기
	RemoveAfterimage();
	//이미지 출력
	if(frozing)
		SetColor(11, 16);
	if (damageCount)
	{
		SetColor(12, 16);
		damageCount++;
		if (damageCount > 3)
			damageCount = 0;
	}
	if (superPower > 0)
		SetColor((superPower % 7) + 9, 16);

	gotoxy(2 + (positionX * 2), 1 + positionY);
	if (lookingDir == UP)
		puts("▲");
	else if (lookingDir == DOWN)
		puts("▼");
	else if (lookingDir == LEFT)
		puts("◀");
	else if (lookingDir == RIGHT)
		puts("▶");
	else
		puts("★");
	SetColor(7, 16);
}
void Player::Attack()
{
	if (IsWall(lookingDir))
		return;
	
	Object * target;
	
	target = CheckCollision(lookingDir);
	if (superPower != 0)
	{
		if (target == NULL)
		{
			GameManager::GetInstance()->nowObjectList->push_back(new BombBullet(positionX, positionY, lookingDir));
			GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
		}
		else
		{
			target->Damage(1);
		}
	}
	else if (iceArrow)
	{
		if (target == NULL)
		{
			GameManager::GetInstance()->nowObjectList->push_back(new IceArrow(positionX, positionY, lookingDir));
			GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
		}
		else
		{
			target->Frozing(100);
		}
	}
	else
	{
		if (target == NULL)
		{
			GameManager::GetInstance()->nowObjectList->push_back(new Bullet(positionX, positionY, lookingDir));
			GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
		}
		else
		{
			target->Damage(1);
		}
	}
}
void Player::Damage(int p)
{
	if (superPower == 0)
	{
		this->health -= p;
		if (this->health <= 0)
			this->isDie = true;
		this->damageCount = 1;
	}
}
void Player::Interact(Object& target)
{

}
void Player::SetSuperPower()
{
	this->superPower += 100;
}
void Player::ToggleIceArrow()
{
	if (iceArrow)
		iceArrow = false;
	else
		iceArrow = true;
}