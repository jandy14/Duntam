#pragma once
#include "BehaviorTree.h"
#include "PathFinding.h"

using namespace std;

namespace AI
{
	DIRECTION_TYPE& VectorToDirection(int x1, int y1, int x2, int y2);
	bool IsDirect(int x1, int y1, int x2, int y2);

	class CheckStatus: public Node
	{
	private:
		int m_status;
	public:
		CheckStatus(int p_status) : m_status(p_status){}
		virtual bool Run() override
		{
			if (m_status == 0)
			{
				return true;
			}	
			else
			{
				return false;
			}		
		}
	};
	class SearchingWay : public Node
	{
	private:
		int m_x,m_y;
		int m_range;
	public:
		SearchingWay(int p_x, int p_y,int p_range) : m_x(p_x), m_y(p_y), m_range(p_range){}
		virtual bool Run() override
		{
			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			if (m_range > Distance(targetX, targetY, m_x, m_y))
			{
				Astar(MAP, targetX, targetY, m_x, m_y);
				return true;
			}
			else
			{
				return false;
			}		
		}
	};
	class Move : public Node
	{
	private:
		EnemyC* m_this;
	public:
		Move(EnemyC* p_this) : m_this(p_this) {}
		virtual bool Run()
		{
			int lastX, lastY;
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();
			DIRECTION_TYPE dir;

			lastX = MAP.Get(x, y).m_lastX;
			lastY = MAP.Get(x, y).m_lastY;

			// 얻은 좌표를 방향으로 변환
			if (lastX > x)
				dir = RIGHT;
			else if (lastX < x)
				dir = LEFT;
			else if (lastY > y)
				dir = DOWN;
			else if (lastY < y)
				dir = UP;

			if (!m_this->IsWall(dir))
			{
				m_this->Move(dir);
				return true;
			}	
			else
			{
				return false;
			}
		}
	};
	class Attack : public Node
	{
	private:
		EnemyC* m_this;
		int m_range;
		DIRECTION_TYPE dir;
	public:
		Attack(EnemyC* p_this,int p_range) : m_this(p_this),m_range(p_range) {}
		virtual bool Run() override
		{
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			if (Distance(x,y,targetX,targetY) <= m_range && IsDirect(x,y,targetX,targetY))
			{
				dir = VectorToDirection(x, y, targetX, targetY);
				m_this->Attack(dir);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	class Attack_Dynamic : public Node
	{
	private:
		EnemyC* m_this;
		int m_range;
		DIRECTION_TYPE dir;
	public:
		Attack_Dynamic(EnemyC* p_this, int p_range) : m_this(p_this), m_range(p_range) {}
		virtual bool Run() override
		{
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			int lastX = MAP.Get(x, y).m_lastX;
			int lastY = MAP.Get(x, y).m_lastY;

			if (Distance(x, y, targetX, targetY) <= m_range && IsDirect(x, y, targetX, targetY))
			{
				dir = VectorToDirection(x, y, targetX, targetY);
				m_this->Attack(dir);
				dir = VectorToDirection(x, y, lastX, lastY);
				m_this->Move(dir);

				return true;
			}
			else
			{
				return false;
			}
		}
	};

	DIRECTION_TYPE& VectorToDirection(int x1, int y1, int x2, int y2) // 방향 반환
	{
		DIRECTION_TYPE dir;

		if (x2 > x1)
			dir = RIGHT;
		else if (x2 < x1)
			dir = LEFT;
		else if (y2 > y1)
			dir = DOWN;
		else if (y2 < y1)
			dir = UP;
		return dir;
	}
	bool IsDirect(int x1, int y1, int x2, int y2)
	{
		bool isDirect = false;

		if (x2 > x1)
			isDirect = !isDirect;
		else if (x2 < x1)
			isDirect = !isDirect;
		if (y2 > y1)
			isDirect = !isDirect;
		else if (y2 < y1)
			isDirect = !isDirect;

			return isDirect;
	}
}
/*
void EnemyC::AI()
{
	DIRECTION_TYPE dir = NONE;

	if (moveDelay == 0)
	{

		int x = positionX;
		int y = positionY;
		int targetX = GameManager::GetInstance()->player->GetPositionX();
		int targetY = GameManager::GetInstance()->player->GetPositionY();
		int lastX = 0;
		int lastY = 0;

		Astar(MAP, targetX, targetY, x, y);
		lastX = MAP.Get(x, y).m_lastX;
		lastY = MAP.Get(x, y).m_lastY;

		// 얻은 좌표를 방향으로 변환
		if (lastX > x)
			dir = RIGHT;
		else if (lastX < x)
			dir = LEFT;
		else if (lastY > y)
			dir = DOWN;
		else if (lastY < y)
			dir = UP;

		Move(dir);
	}
	if (moveDelay == 0)
	{
		if (!IsWall(dir))
		{
			Object* target = CheckCollision(dir);
			if (target == (Object*)GameManager::GetInstance()->player)
				target->Damage(1);
		}
	}
}
*/