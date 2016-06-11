#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

template<class Datatype>
class Array
{
public:
	Datatype* m_array;
	int m_size;
	Array(int p_size)
	{
		m_array = new Datatype[p_size];

		m_size = p_size;
	}

	~Array()
	{
		if (m_array != 0)
			delete[] m_array;

		m_array = 0;
	}

	void Resize(int p_size)
	{
		Datatype* newarray = new Datatype[p_size];

		if (newarray == 0)
			return;

		int min;
		if (p_size < m_size)
			min = p_size;
		else
			min = m_size;

		int index;
		for (index = 0; index < min; index++)
			newarray[index] = m_array[index];

		m_size = p_size;

		if (m_array != 0)
			delete[] m_array;

		m_array = newarray;
	}

	Datatype& operator[] (int p_index)
	{
		return m_array[p_index];
	}

	void Insert(Datatype p_item, int p_index)
	{
		int index;

		for (index = m_size - 1; index > p_index; index--)
			m_array[index] = m_array[index - 1];

		m_array[p_index] = p_item;
	}

	void Remove(int p_index)
	{
		int index;

		for (index = p_index + 1; index < m_size; index++)
			m_array[index - 1] = m_array[index];
	}

	int Size()
	{
		return m_size;
	}

	operator Datatype* ()
	{
		return m_array;
	}
};

#endif