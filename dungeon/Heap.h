#ifndef HEAP_H
#define HEAP_H

#include "Array.h"

template <class DataType>
class Heap : public Array<DataType>
{
public:
	int m_count;
	int(*m_compare)(DataType, DataType);

	Heap(int p_size, int(*p_compare)(DataType, DataType))
		: Array<DataType>(p_size + 1)
	{
		m_count = 0;
		m_compare = p_compare;
	}
	void Enqueue(DataType p_data)
	{
		m_count++;

		if (m_count >= m_size)
			Resize(m_size * 2);

		m_array[m_count] = p_data;

		WalkUp(m_count);
	}

	void Dequeue()
	{
		if (m_count >= 1)
		{
			m_array[1] = m_array[m_count];
			WalkDown(1);
			m_count--;
		}
	}

	DataType& Item()
	{
		return m_array[1];
	}

	virtual void WalkUp(int p_index)
	{
		int parent = p_index / 2;
		int child = p_index;

		DataType temp = m_array[child];

		while (parent > 0)
		{
			if (m_compare(temp, m_array[parent]) > 0)
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

		DataType temp = m_array[parent];

		while (child < m_count)
		{
			if (child < m_count - 1)
			{
				if (m_compare(m_array[child], m_array[child + 1]) < 0)
				{
					child++;
				}
			}
			if (m_compare(temp, m_array[child]) < 0)
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

#endif