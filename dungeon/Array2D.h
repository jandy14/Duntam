#ifndef ARRAY2D_H
#define ARRAY2D_H


template <class Datatype>
class Array2D
{
public:
	Datatype* m_array;
	int m_width;
	int m_height;

	Array2D()
	{
		m_array = new Datatype[50 * 30];
		m_width = 50;
		m_height = 30;
	}
	Array2D(int p_width, int p_height)
	{
		m_array = new Datatype[p_width * p_height];

		m_width = p_width;
		m_height = p_height;
	}
	Array2D(Array2D<Datatype>& other)
	{
		this->m_height = other.Height;
		this->m_width = other.m_width;
		this->m_array = new Datatype[m_width * m_height];
	}

	~Array2D()
	{
		if (m_array != 0)
			delete[] m_array;
		m_array = 0;
	}

	Datatype& Get(int p_x, int p_y)
	{
		return m_array[p_y * m_width + p_x];
	}

	void Resize(int p_width, int p_height)
	{
		Datatype* newarray = new Datatype[p_width * p_height];

		if (newarray == 0)
			return;

		int x, y, t1, t2;

		int minx = (p_width < m_width ? p_width : m_width);
		int miny = (p_height < m_height ? p_height : m_height);

		for (y = 0; y < miny; y++)
		{
			t1 = y * p_width;
			t2 = y * m_width;
			for (x = 0; x < minx; x++)
			{
				newarray[t1 + x] = m_array[t2 + x];
			}
		}

		if (m_array != 0)
			delete[] m_array;

		m_array = newarray;
		m_width = p_width;
		m_height = p_height;
	}

	int Size()
	{
		return m_width * m_height;
	}

	int Width()
	{
		return m_width;
	}

	int Height()
	{
		return m_height;
	}
};
#endif