#include "Block.h"
#include "GameManager.h"

using namespace std;

Block::Block(int posX, int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 1;
	this->health = 1;
	this->frozing = 0;
}


Block::~Block(){}
void Block::Attack(){}
void Block::Update(){}
void Block::Draw()
{
	if (drawCount == 0)
	{
		RemoveAfterimage();

		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "■";
		drawCount++;
	}
}
void Block::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("이봐 날 건들지마");
		message.push_back("나를 귀찮게 하면");
		message.push_back("혼날줄 알아");
		GameManager::GetInstance()->SetMessage(message);
		interactionCount++;
	}
	else
	{
		target.Damage(2);
		message.push_back("날 건들지 말라고 한거같은데");
		message.push_back("이건 그 대가야");
		GameManager::GetInstance()->SetMessage(message);
	}
}
void Block::Damage(int p){}
void Block::Heal(int p){}

BreakableBlock::BreakableBlock(int posX, int posY) : Block(posX, posY)
{
	this->interactionCount = 0;
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 1;
	this->health = 1;
	this->frozing = 0;
}
void BreakableBlock::Draw()
{
	RemoveAfterimage();

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "□";
}
void BreakableBlock::Damage(int p)
{
	this->health -= p;
	if (this->health <= 0)
		this->Die();
}
void BreakableBlock::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("이봐 날 건들지마");
		message.push_back("나를 귀찮게 하면");
		message.push_back("혼날줄 알아");
		GameManager::GetInstance()->SetMessage(message);
		interactionCount++;
	}
	else
	{
		message.push_back("미안 잘못했어");
		message.push_back("살려줘...");
		GameManager::GetInstance()->SetMessage(message);
	}
}
BreakableBlock::~BreakableBlock() {}