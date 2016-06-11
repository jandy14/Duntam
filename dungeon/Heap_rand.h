#pragma once
#include "Heap.h"

template <class DataType>
class Heap_rand :public Heap<DataType>
{
public:
	Heap_rand(int p_size, int(*p_compare)(DataType, DataType)) : Heap<DataType>(p_size, p_compare)
	{

	}

	virtual void WalkUp(int p_index)
	{
		// set up the parent and child indexes
		int parent = p_index / 2;
		int child = p_index;
		int random = 0;

		// store the item to walk up in a temporary buffer.
		DataType temp = m_array[child];

		while (parent > 0)
		{   // if the node to walk up is more than the parent,
			// then swap nodes.
			if(m_compare(temp, m_array[parent]) == 0)
				random = (rand() % 4) + (rand() % 4);

			if (m_compare(temp, m_array[parent]) > 0 || (2 <= random && random <= 5))
			{
				// swap the parent and child, and go up a level.
				m_array[child] = m_array[parent];
				child = parent;
				parent /= 2;
			}
			else
				break;
		}

		// put the temp variable (the one that was walked up)
		// into the child index.
		m_array[child] = temp;
	}

	virtual void WalkDown(int p_index)
	{
		// calculate the parent and child indexes.
		int parent = p_index;
		int child = p_index * 2;
		int random = 0;

		// store the data to walk down in a temporary buffer.
		DataType temp = m_array[parent];

		// loop through, walking node down heap until both children are
		// smaller than node.
		while (child < m_count)
		{
			// if left child is not the last node in the tree, then
			// find out which of the current node's children is largest.
			if (m_compare(temp, m_array[parent]) == 0)
				random = (rand() % 4) + (rand() % 4);

			if (child < m_count - 1)
			{
				if (m_compare(m_array[child], m_array[child + 1]) < 0 || (2 <= random && random <= 5))
				{   // change the pointer to the right child, since it is larger.
					child++;
				}
			}
			// if the node to walk down is lower than the highest value child,
			// move the child up one level.
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