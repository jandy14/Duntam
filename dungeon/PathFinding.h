#pragma once
#include "Array2D.h"
#include "Heap_rand.h"
#include "GameManager.h"
#include "Thing.h"

class Coordinate // 트리에 넣을 객체 클래스
{
public:
	int x;
	int y;
	float heuristic;
};

class Cell
{
public:
	int m_x;
	int m_y;
	bool m_marked = false;
	bool m_passable = true;
	float m_distance = 0;
	int m_lastX = -1;
	int m_lastY = -1;
	float m_weight = 0; // 험한 정도 땅과 물의 차이라고 봐도 됨
};

static Array2D<Cell> MAP;
static list<Cell> TELEPORT;

void ClearCells(Array2D<Cell>& MAP, int p_x, int p_y, int p_gx, int p_gy);
void ClearCells2(Array2D<Cell>& p_map, int p_gx, int p_gy, int p_x, int p_y);
float ComplexHeuristic(int x, int y, int targetX, int targetY, int dir);
float AdmissibleHeuristic(int x, int y, int gx, int gy, int dir);
float Distance(int x1, int y1, int x2, int y2);
void Astar(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy);
void Astar_Telepoter(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy);
int CompareCoordinatesDescending(Coordinate left, Coordinate right);
float Min(float a, float b);
