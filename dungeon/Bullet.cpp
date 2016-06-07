#include "Bullet.h"

using namespace std;

Bullet::Bullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Object(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 3;
	this->health = 1;
	this->frozing = 0;
	this->lookingDir = lookingDir;
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
void Bullet::Damage(int p){}
void Bullet::Heal(int p){}
