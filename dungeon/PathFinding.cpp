#include "PathFinding.h"

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

			//그 좌표가 적이거나 플레이어일 경우 여기서는 통과가능 하다고 한다.
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

	// clear the cells first.
	ClearCells(p_map, p_x, p_y, p_gx, p_gy);

	// enqueue the starting cell in the queue
	c.x = p_x;
	c.y = p_y;
	c.heuristic = 0.0f;
	queue.Enqueue(c);


	// start the main loop
	while (queue.m_count != 0)
	{
		// pull the first cell off the queue and process it.
		x = queue.Item().x;
		y = queue.Item().y;
		queue.Dequeue();


		// make sure the node isn't already marked. If it is, do
		// nothing.
		if (p_map.Get(x, y).m_marked == false)
		{
			// mark the cell as it is pulled off the queue.
			p_map.Get(x, y).m_marked = true;

			// quit out if the goal has been reached.
			if (x == p_gx && y == p_gy)
				break;


			// loop through each direction.
			for (dir = 0; dir < 4; dir++)
			{
				// retrieve the coordinates of the current adjacent cell
				ax = x + DIRTABLE[dir][0];
				ay = y + DIRTABLE[dir][1];

				// check to see if the adjacent cell is a valid index, 
				// passable, and not marked.
				if (ax >= 0 && ax < 50 &&
					ay >= 0 && ay < 30 &&
					p_map.Get(ax, ay).m_passable == true &&
					p_map.Get(ax, ay).m_marked == false)
				{
					// calculate the distance to get into this cell.
					// this is calulated as:
					// distance of the current cell plus
					// the weight of the adjacent cell times the distance
					// of the cell.
					// diagonal cell's cost is around 1.4 times the cost of
					// a horizontal or vertical cell.
					distance = p_map.Get(x, y).m_distance +
						p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

					// check if the node has already been calculated before
					if (p_map.Get(ax, ay).m_lastX != -1)
					{
						// the node has already been calculated, see if the
						// new distance is shorter. If so, update the links.
						if (distance < p_map.Get(ax, ay).m_distance)
						{
							// the new distance is shorter, update the links
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							// add the cell to the queue.
							c.x = ax;
							c.y = ay;
							c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
							queue.Enqueue(c);
						}
					}
					else
					{
						// set the links and the distance
						p_map.Get(ax, ay).m_lastX = x;
						p_map.Get(ax, ay).m_lastY = y;
						p_map.Get(ax, ay).m_distance = distance;

						// add the cell to the queue.
						c.x = ax;
						c.y = ay;
						c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
						queue.Enqueue(c);
					}
				}
			}
		}
	}
	// 플레이어에게 가는 길이 없을 경우

	if (queue.m_count == 0)
	{
		static Heap_rand<Coordinate> queue1(QUEUESIZE, CompareCoordinatesDescending); // 두번째 큐 사이즈는 줄여도 괜찮은 것 같다
		queue1.m_count = 0;

		ClearCells(p_map, p_x, p_y, p_gx , p_gy);

		c.x = p_x;
		c.y = p_y;
		c.heuristic = 0.0f;
		queue1.Enqueue(c);

		while (queue1.m_count != 0)
		{
			// pull the first cell off the queue and process it.
			x = queue1.Item().x;
			y = queue1.Item().y;
			queue1.Dequeue();


			// make sure the node isn't already marked. If it is, do
			// nothing.
			if (p_map.Get(x, y).m_marked == false)
			{
				// mark the cell as it is pulled off the queue.
				p_map.Get(x, y).m_marked = true;

				// quit out if the goal has been reached.
				if (x == p_gx && y == p_gy)
					break;


				// loop through each direction.
				for (dir = 0; dir < 4; dir++)
				{
					// retrieve the coordinates of the current adjacent cell
					ax = x + DIRTABLE[dir][0];
					ay = y + DIRTABLE[dir][1];

					// check to see if the adjacent cell is a valid index, 
					// passable, and not marked.
					if (ax >= 0 && ax < 50 &&
						ay >= 0 && ay < 30 &&
						p_map.Get(ax, ay).m_marked == false)
					{
						// calculate the distance to get into this cell.
						// this is calulated as:
						// distance of the current cell plus
						// the weight of the adjacent cell times the distance
						// of the cell.
						// diagonal cell's cost is around 1.4 times the cost of
						// a horizontal or vertical cell.
						distance = p_map.Get(x, y).m_distance +
							p_map.Get(ax, ay).m_weight * DISTTABLE[dir];

						// check if the node has already been calculated before
						if (p_map.Get(ax, ay).m_lastX != -1)
						{
							// the node has already been calculated, see if the
							// new distance is shorter. If so, update the links.
							if (distance < p_map.Get(ax, ay).m_distance)
							{
								// the new distance is shorter, update the links
								p_map.Get(ax, ay).m_lastX = x;
								p_map.Get(ax, ay).m_lastY = y;
								p_map.Get(ax, ay).m_distance = distance;

								// add the cell to the queue.
								c.x = ax;
								c.y = ay;
								c.heuristic = ComplexHeuristic(x, y, p_gx, p_gy, dir) + distance;
								queue1.Enqueue(c);
							}
						}
						else
						{
							// set the links and the distance
							p_map.Get(ax, ay).m_lastX = x;
							p_map.Get(ax, ay).m_lastY = y;
							p_map.Get(ax, ay).m_distance = distance;

							// add the cell to the queue.
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