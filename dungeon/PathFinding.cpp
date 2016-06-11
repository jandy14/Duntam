#include "PathFinding.h"

const int QUEUESIZE = 1024;
const int DIRTABLE[4][2] = {
	{ 0, 1 }, // EAST
	{ 1, 0 }, // SOUTH
	{ 0, -1 },	// WEST
	{ -1, 0 }	// NORTH
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
			}
			else if (GameManager::GetInstance()->collisionTable[y][x] == NULL)
			{
				p_map.Get(x, y).m_passable = true;
			}
			else
			{
				p_map.Get(x, y).m_passable = false;
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
void Astar(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy) // A스타 알고리즘
{
	Coordinate c;
	int x, y;
	int ax, ay;
	int dir;
	float distance = 0;

	static Heap<Coordinate> queue(QUEUESIZE, CompareCoordinatesDescending);
	queue.m_count = 0;

	ClearCells(p_map, p_x, p_y, p_gx, p_gy);

	c.x = p_x;
	c.y = p_y;
	c.heuristic = 0.0f;
	queue.Enqueue(c);

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
							queue.Enqueue(c);
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
		static Heap_rand<Coordinate> queue1(QUEUESIZE, CompareCoordinatesDescending);
		queue1.m_count = 0;

		ClearCells(p_map, p_x, p_y, p_gx, p_gy);

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
	x = x + DIRTABLE[dir][0];
	y = y + DIRTABLE[dir][1];
	return Distance(x, y, gx, gy);
}