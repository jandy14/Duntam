#include "PathFinding.h"

const int QUEUESIZE = 1024;
static Heap<Coordinate> queue(QUEUESIZE, CompareCoordinatesDescending);
static Heap_rand<Coordinate> queue1(QUEUESIZE / 4, CompareCoordinatesDescending);

const int DIRTABLE[4][2] = {
	{ 0, 1 }, // SOUTH
	{ -1, 0},	// WEST
	{ 0, -1 },	// NORTH
	{ 1, 0 } // EAST
};
const float DISTTABLE[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

void ClearCells(Array2D<Cell>& p_map, int p_gx, int p_gy, int p_x, int p_y)
{
	int x;
	int y;
	for (y = 0; y < 30; y++)
	{
		for (x = 0; x < 50; x++)
		{
			p_map.Get(x, y).m_marked = false;
			p_map.Get(x, y).m_distance = 0.0f;
			p_map.Get(x, y).m_lastX = -1;
			p_map.Get(x, y).m_lastY = -1;
		
			//그 좌표가 자신이거나 플레이어일 경우 여기서는 통과가능 하다고 한다.
			if ((x == p_gx && y == p_gy) || (x == p_x && y == p_y))
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 벽이 아닌경우
			else if (GameManager::GetInstance()->collisionTable[y][x] == NULL)
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 텔레포터인 경우
			else if (GameManager::GetInstance()->collisionTable[y][x]->TypeName == 52)
			{
				p_map.Get(x, y).m_passable = true;
				
				Teleporter_sounghoo* telepoter = (Teleporter_sounghoo*)GameManager::GetInstance()->collisionTable[y][x];

				p_map.Get(x, y).m_x = telepoter->warpPointX;
				p_map.Get(x, y).m_y = telepoter->warpPointY;

				TELEPORT.push_back(p_map.Get(x, y));
			}
			else
			{
				p_map.Get(x, y).m_passable = false;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
		}
	}
}
void ClearCells2(Array2D<Cell>& p_map, int p_gx, int p_gy, int p_x, int p_y)
{
	int x;
	int y;
	for (y = 0; y < 30; y++)
	{
		for (x = 0; x < 50; x++)
		{
			p_map.Get(x, y).m_marked = false;
			p_map.Get(x, y).m_distance = 0.0f;
			p_map.Get(x, y).m_lastX = -1;
			p_map.Get(x, y).m_lastY = -1;

			//그 좌표가 자신이거나 플레이어일 경우 여기서는 통과가능 하다고 한다.
			if ((x == p_gx && y == p_gy) || (x == p_x && y == p_y))
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 벽이 아닌경우
			else if (GameManager::GetInstance()->collisionTable[y][x] == NULL)
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 적인 경우
			else if (GameManager::GetInstance()->collisionTable[y][x]->TypeName == 10)
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 총알인 경우
			else if (GameManager::GetInstance()->collisionTable[y][x]->TypeName == 1)
			{
				p_map.Get(x, y).m_passable = true;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
			// 텔레포터인 경우
			else if (GameManager::GetInstance()->collisionTable[y][x]->TypeName == 52)
			{
				p_map.Get(x, y).m_passable = true;

				Teleporter_sounghoo* telepoter = (Teleporter_sounghoo*)GameManager::GetInstance()->collisionTable[y][x];

				p_map.Get(x, y).m_x = telepoter->warpPointX;
				p_map.Get(x, y).m_y = telepoter->warpPointY;

				TELEPORT.push_back(p_map.Get(x, y));
			}
			else
			{
				p_map.Get(x, y).m_passable = false;
				p_map.Get(x, y).m_x = x;
				p_map.Get(x, y).m_y = y;
			}
		}
	}
}


float Distance(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	
	dx = dx * dx;
	dy = dy * dy;

	return (float)sqrt((double)dx + (double)dy);
}

int CompareCoordinatesDescending(Coordinate left, Coordinate right)
{
	if (left.heuristic < right.heuristic)
		return 1;
	if (left.heuristic > right.heuristic)
		return -1;
	return 0;
}
void Astar(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy)
{
	Coordinate c;
	int x, y;
	int ax, ay;
	int dir;
	float distance = 0;

	queue.m_count = 0;

	ClearCells(p_map, p_x, p_y, p_gx, p_gy);

	c.x = p_x;
	c.y = p_y;
	c.heuristic = 0.0f;
	queue.Enqueue(c);

	dir = rand() % 10;

	while (queue.m_count != 0)
	{
		x = queue.Item().x;
		y = queue.Item().y;
		queue.Dequeue();

		if (p_map.Get(x, y).m_marked == false)
		{
			p_map.Get(x, y).m_marked = true;

			if (x == p_gx && y == p_gy)
				break;

			for (int i = 0; i < 4; i++, dir++)
			{
				dir = dir % 4;
				ax = x + DIRTABLE[dir][0];
				ay = y + DIRTABLE[dir][1];

				if (ax >= 0 && ax < 50 &&
					ay >= 0 && ay < 30 &&
					p_map.Get(ax, ay).m_passable == true &&
					p_map.Get(ax, ay).m_marked == false)
				{
					distance = p_map.Get(x, y).m_distance + p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

					if (p_map.Get(ax, ay).m_lastX != -1)
					{
						if (distance < p_map.Get(ax, ay).m_distance)
						{
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							c.x = p_map.Get(ax, ay).m_x;
							c.y = p_map.Get(ax, ay).m_y;
							c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
							queue.Enqueue(c);
						}
					}
					else
					{
						p_map.Get(ax, ay).m_lastX = x;
						p_map.Get(ax, ay).m_lastY = y;
						p_map.Get(ax, ay).m_distance = distance;

						c.x = p_map.Get(ax, ay).m_x;
						c.y = p_map.Get(ax, ay).m_y;
						c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
						queue.Enqueue(c);
					}
				}
			}
		}
	}
	//
	// 플레이어에게 가는 길이 없을 경우
	//
	if (queue.m_count == 0)
	{
		queue1.m_count = 0;

		ClearCells2(p_map, p_x, p_y, p_gx, p_gy);

		c.x = p_x;
		c.y = p_y;
		c.heuristic = 0.0f;
		queue1.Enqueue(c);

		while (queue1.m_count != 0)
		{
			x = queue1.Item().x;
			y = queue1.Item().y;
			queue1.Dequeue();

			if (p_map.Get(x, y).m_marked == false)
			{
				p_map.Get(x, y).m_marked = true;

				if (x == p_gx && y == p_gy)
					break;

				for (dir = 0; dir < 4; dir++)
				{
					ax = x + DIRTABLE[dir][0];
					ay = y + DIRTABLE[dir][1];

					if (ax >= 0 && ax < 50 &&
						ay >= 0 && ay < 30 &&
						p_map.Get(ax, ay).m_passable == true &&
						p_map.Get(ax, ay).m_marked == false)
					{
						distance = p_map.Get(x, y).m_distance +
							p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

						if (p_map.Get(ax, ay).m_lastX != -1)
						{
							if (distance < p_map.Get(ax, ay).m_distance)
							{
								p_map.Get(ax, ay).m_lastX = x;
								p_map.Get(ax, ay).m_lastY = y;
								p_map.Get(ax, ay).m_distance = distance;

								c.x = ax;
								c.y = ay;
								c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
								queue1.Enqueue(c);
							}
						}
						else
						{
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							c.x = ax;
							c.y = ay;
							c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
							queue1.Enqueue(c);
						}
					}
				}
			}
		}
	}
}
void Astar_Telepoter(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy) // A스타 알고리즘
{
	Coordinate c;
	int x, y;
	int ax, ay;
	int dir;
	float distance = 0;

	queue.m_count = 0;

	ClearCells(p_map, p_x, p_y, p_gx, p_gy);

	c.x = p_x;
	c.y = p_y;
	c.heuristic = 0.0f;
	queue.Enqueue(c);

	dir = rand() % 10;

	while (queue.m_count != 0)
	{
		x = queue.Item().x;
		y = queue.Item().y;
		queue.Dequeue();

		if (p_map.Get(x, y).m_marked == false)
		{
			p_map.Get(x, y).m_marked = true;

			if (x == p_gx && y == p_gy)
				break;

			for (int i = 0; i < 4; i++, dir++)
			{
				dir = dir % 4;
				ax = x + DIRTABLE[dir][0];
				ay = y + DIRTABLE[dir][1];

				if (ax >= 0 && ax < 50 &&
					ay >= 0 && ay < 30 &&
					p_map.Get(ax, ay).m_passable == true &&
					p_map.Get(ax, ay).m_marked == false)
				{
					distance = p_map.Get(x, y).m_distance + p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

					if (p_map.Get(ax, ay).m_lastX != -1)
					{
						if (distance < p_map.Get(ax, ay).m_distance)
						{
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							c.x = p_map.Get(ax, ay).m_x;
							c.y = p_map.Get(ax, ay).m_y;
							c.heuristic = AdmissibleHeuristic(x, y, p_gx, p_gy, dir) + distance;
							queue.Enqueue(c);
						}
					}
					else
					{
						p_map.Get(ax, ay).m_lastX = x;
						p_map.Get(ax, ay).m_lastY = y;
						p_map.Get(ax, ay).m_distance = distance;

						c.x = p_map.Get(ax, ay).m_x;
						c.y = p_map.Get(ax, ay).m_y;
						c.heuristic = AdmissibleHeuristic(x, y, p_gx, p_gy, dir) + distance;
						queue.Enqueue(c);
					}
				}
			}
		}
	}
	//
	// 플레이어에게 가는 길이 없을 경우
	//
	if (queue.m_count == 0)
	{
		queue1.m_count = 0;

		ClearCells2(p_map, p_x, p_y, p_gx, p_gy);

		c.x = p_x;
		c.y = p_y;
		c.heuristic = 0.0f;
		queue1.Enqueue(c);

		while (queue1.m_count != 0)
		{
			x = queue1.Item().x;
			y = queue1.Item().y;
			queue1.Dequeue();

			if (p_map.Get(x, y).m_marked == false)
			{
				p_map.Get(x, y).m_marked = true;

				if (x == p_gx && y == p_gy)
					break;

				for (dir = 0; dir < 4; dir++)
				{
					ax = x + DIRTABLE[dir][0];
					ay = y + DIRTABLE[dir][1];

					if (ax >= 0 && ax < 50 &&
						ay >= 0 && ay < 30 &&
						p_map.Get(ax, ay).m_passable == true &&
						p_map.Get(ax, ay).m_marked == false)
					{
						distance = p_map.Get(x, y).m_distance +
							p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

						if (p_map.Get(ax, ay).m_lastX != -1)
						{
							if (distance < p_map.Get(ax, ay).m_distance)
							{
								p_map.Get(ax, ay).m_lastX = x;
								p_map.Get(ax, ay).m_lastY = y;
								p_map.Get(ax, ay).m_distance = distance;

								c.x = ax;
								c.y = ay;
								c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
								queue1.Enqueue(c);
							}
						}
						else
						{
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							c.x = ax;
							c.y = ay;
							c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
							queue1.Enqueue(c);
						}
					}
				}
			}
		}
	}
}

float ComplexHeuristic(int x, int y, int gx, int gy, int dir)
{
	int TempX = x + DIRTABLE[dir][0];
	int TempY = y + DIRTABLE[dir][1];

	return Distance(TempX, TempY, gx, gy);
}
float AdmissibleHeuristic(int x, int y, int gx, int gy, int dir)
{
	int TempX = x + DIRTABLE[dir][0];
	int TempY = y + DIRTABLE[dir][1];
	float min = 1500;

	if (!TELEPORT.empty())
	{
		list<Cell>::iterator itr = TELEPORT.begin();
		min = Distance(TempX, TempY, itr->m_x, TempY) + Distance(TempX, TempY, TempX, itr->m_y);

		for (itr; itr != TELEPORT.end(); itr++)
		{
			min = Min(min, Distance(TempX, TempY, itr->m_x, TempY) + Distance(TempX, TempY, TempX, itr->m_y));
		}
	}	

	return Min(Distance(TempX, TempY, gx, gy), min);
}
inline float Min(float a, float b)
{
	if (a > b)
		return b;
	else
		return a;
}