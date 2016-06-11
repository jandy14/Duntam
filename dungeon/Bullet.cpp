#include "Bullet.h"
#include "GameManager.h"

using namespace std;

Bullet::Bullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Object(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 3;
	this->moveDelay = 3;
	this->health = 1;
	this->frozing = 0;
	this->lookingDir = lookingDir;
	//위치 재설정
	if (lookingDir == UP)
		this->positionY -= 1;
	else if (lookingDir == DOWN)
		this->positionY += 1;
	else if (lookingDir == LEFT)
		this->positionX -= 1;
	else if (lookingDir == RIGHT)
		this->positionX += 1;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	if (moveDelay == 0)
	{
		Move(lookingDir);
	}
	if (moveDelay == 0)
	{
		if (!IsWall(lookingDir))
		{
			Object* target = CheckCollision(lookingDir);
			if (target != NULL)
				target->Damage(1);
		}
		this->Die();
	}
}
void Bullet::Draw()
{
	//이전에 남은 그림 지우기
	RemoveAfterimage();

	SetColor(14, 16);
	if (lookingDir == UP || lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "∥";
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "＝";
	}
	SetColor(7, 16);
}
void Bullet::Interact(Object& targer)
{
	list<string> message;
	message.push_back("내 살다살다 총알한테");
	message.push_back("말거는 병신이 다있네");
	message.push_back("수고해라 병신아");
	GameManager::GetInstance()->SetMessage(message);
}
void Bullet::Damage(int p){}
void Bullet::Heal(int p){}

//
//	적 총알
//
EnemyBullet::EnemyBullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Object(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 3;
	this->moveDelay = 3;
	this->health = 1;
	this->frozing = 0;
	this->lookingDir = lookingDir;
	//위치 재설정
	if (lookingDir == UP)
		this->positionY -= 1;
	else if (lookingDir == DOWN)
		this->positionY += 1;
	else if (lookingDir == LEFT)
		this->positionX -= 1;
	else if (lookingDir == RIGHT)
		this->positionX += 1;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	if (moveDelay == 0)
	{
		Move(lookingDir);
	}
	if (moveDelay == 0)
	{
		if (!IsWall(lookingDir))
		{
			Object* target = CheckCollision(lookingDir);
			if (target != NULL)
				target->Damage(1);
		}
		this->Die();
	}
}
void EnemyBullet::Draw()
{
	//이전에 남은 그림 지우기
	RemoveAfterimage();

	SetColor(14, 16);
	if (lookingDir == UP || lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "∥";
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "＝";
	}
	SetColor(7, 16);
}
void EnemyBullet::Interact(Object& targer)
{
	list<string> message;
	message.push_back("내 살다살다 총알한테");
	message.push_back("말거는 병신이 다있네");
	message.push_back("수고해라 병신아");
	GameManager::GetInstance()->SetMessage(message);
}
void EnemyBullet::Damage(int p) {}
void EnemyBullet::Heal(int p) {}
