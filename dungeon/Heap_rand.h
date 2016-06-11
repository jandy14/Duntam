#pragma once
#include "Heap.h"

template <class DataType>
class Heap_rand :public Heap<DataType>
{
public:
	Heap_rand(int p_size, int(*p_compare)(DataType, DataType)) : Heap<DataType>(p_size, p_compare){}

	virtual void WalkUp(int p_index)
	{
		int parent = p_index / 2;
		int child = p_index;
		int random = 0;

		DataType temp = m_array[child];

		while (parent > 0)
		{
			if (m_compare(temp, m_array[parent]) == 0)
				random = (rand() % 4) + (rand() % 4);

			if (m_compare(temp, m_array[parent]) > 0 || (2 <= random && random <= 5))
			{
				m_array[child] = m_array[parent];
				child = parent;
				parent /= 2;
			}
			else
				break;
		}
		m_array[child] = temp;
	}

	virtual void WalkDown(int p_index)
	{
		int parent = p_index;
		int child = p_index * 2;
		int random = 0;

		DataType temp = m_array[parent];

		while (child < m_count)
		{
			if (m_compare(temp, m_array[parent]) == 0)
				random = (rand() % 4) + (rand() % 4);

			if (child < m_count - 1)
			{
				if (m_compare(m_array[child], m_array[child + 1]) < 0 || (2 <= random && random <= 5))
				{
					child++;
				}
			}
			if (m_compare(temp, m_array[child]) < 0 || (2 <= random && random <= 5))
			{
				m_array[parent] = m_array[child];
				parent = child;
				child *= 2;
			}
			else
				break;
		}
		m_array[parent] = temp;
	}
};