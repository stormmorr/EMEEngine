/*! \file */
#ifndef PCIRCULARLIST_H
#define PCIRCULARLIST_H

//! Implements a Circular List data structure.
template <class T> 
class P3D_API pCircularList
{
	private:

		int m_size;		//!< total of supported elements
		int m_length;	//!< number of elements in the list
		int m_head;		//!< list head
		int m_tail;		//!< list tail
		T *m_buffer;	//!< buffer of elements

		//! Resets the whole circular list.
		void reset();

	public:

		//! Default and initialization constructor.
		/*!
			@param size total of supported elements
		*/
		pCircularList(const int size = P_LIST_SIZE);

		//! Copy-constructor.
		/*!
			@param in the new circular list
		*/
		pCircularList(const pCircularList<T> &in);

		//! Destructor.
		~pCircularList();

		//! Assignment operator.
		/*!
			@param in the new circular list
		*/
		void operator=(const pCircularList<T> &in);

		//! Add an element at the final of circular list.
		/*!
			@param elem the new element
			@return true if successful and false otherwise
		*/
		bool add(T elem);

		//! Remove the n first elements of the circular list.
		/*!
			@param n number of elements to remove
		*/
		void remove_begin(int n = 1);

		//! Remove the n last elements of the circular list.
		/*!
			@param n number of elements to remove
		*/
		void remove_end(int n = 1);

		//! Clear the whole circular list, but keep the memory space.
		void clear();

		//! Get the number of elements into this list.
		/*!
			@return the number of elements into this list
		*/
		const int length() const;

		//! Indexing operator returning const.
		const T& operator[](const int i) const;

		//! Indexing operator
		T& operator[](const int i);

		//! Resize the circular list.
		/*!
			@param size the new amount of space
		*/
		void resize(const int size);

		//! Tests if circular list is full.
		/*!
			@return true if circular list is full and false otherwise
		*/
		bool is_full() const;
};

template <class T>
void pCircularList<T>::reset()
{
	delete[] m_buffer;
	m_buffer = 0;

	m_head = -1;
	m_tail = -1;
	m_size = 0;
	m_length = 0;
}

//-----------------------------------------------------------------------------

template <class T>
pCircularList<T>::pCircularList(const int size) :
	m_size(size),
	m_length(0),
	m_head(-1),
	m_tail(-1)
{
	m_buffer = new T[m_size];
}

//-----------------------------------------------------------------------------

template <class T>
pCircularList<T>::pCircularList(const pCircularList<T> &in) :
	m_size(in.m_size),
	m_length(in.m_length),
	m_head(in.m_head),
	m_tail(in.m_tail)
{
	m_buffer = new T[m_size];

	for (int i = 0; i < m_size; i++)
		m_buffer[i] = in.m_buffer[i];
}

//-----------------------------------------------------------------------------

template <class T>
pCircularList<T>::~pCircularList()
{
	reset();
}

//-----------------------------------------------------------------------------

template <class T>
void pCircularList<T>::operator=(const pCircularList<T> &in)
{
	reset();

	m_size = in.m_size;
	m_length = in.m_length;
	m_head = in.m_head;
	m_tail = in.m_tail;

	m_buffer = new T[m_size];

	for (int i = 0; i < m_size; i++)
		m_buffer[i] = in.m_buffer[i];
}

//-----------------------------------------------------------------------------

template <class T>
inline bool pCircularList<T>::add(T elem)
{
	if (m_length == m_size)
		return false;

	if (m_head == -1) m_head = 0;
	int pos = (m_tail+1) % m_size;
	m_buffer[pos] = elem;
	m_tail = pos;
	m_length++;

	return true;
}

//-----------------------------------------------------------------------------

template <class T>
inline void pCircularList<T>::remove_begin(int n)
{
	if (m_length == 0)
		return;

	if (n >= m_length)
	{
		m_head = m_tail = -1;
		m_length = 0;
	}
	else
	{
		m_head = (m_head+n) % m_size;
		m_length -= n;
	}
}

//-----------------------------------------------------------------------------

template <class T>
inline void pCircularList<T>::remove_end(int n)
{
	if (m_length == 0)
		return;

	if (n >= m_length)
	{
		m_head = m_tail = -1;
		m_length = 0;
	}
	else
	{
		if (m_tail < n)
			m_tail = m_size - (n - m_tail);
		else
			m_tail -= n;

		m_length -= n;
	}
}

//-----------------------------------------------------------------------------

template <class T>
inline void pCircularList<T>::clear()
{
	m_head = -1;
	m_tail = -1;
	m_length = 0;
}

//-----------------------------------------------------------------------------

template <class T>
inline const int pCircularList<T>::length() const
{
	return m_length;
}

//-----------------------------------------------------------------------------

template <class T>
inline const T& pCircularList<T>::operator[](const int i) const
{
	if (m_head == -1) return m_buffer[0];
	return m_buffer[(m_head+i)%m_size];
}

//-----------------------------------------------------------------------------

template <class T>
inline T& pCircularList<T>::operator[](const int i)
{
	if (m_head == -1) return m_buffer[0];
	return m_buffer[(m_head+i)%m_size];
}

//-----------------------------------------------------------------------------

template <class T>
void pCircularList<T>::resize(const int size)
{
	reset();

	m_size = size;
	m_head = -1;
	m_tail = -1;
	m_buffer = new T[m_size];
}

//-----------------------------------------------------------------------------

template <class T>
inline bool pCircularList<T>::is_full() const
{
	return m_length == m_size;
}

#endif
