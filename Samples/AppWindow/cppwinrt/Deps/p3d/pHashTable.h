/*! \file */

#ifndef PHASHTABLE_H
#define PHASHTABLE_H

//! Implements a HashTable data structure.
/*!
	Implements a HashTable data structure whose the first entry is an interger
	and the second entry is a template.
*/
template <class T> 
class P3D_API pHashTable
{
	//! Hash node struct.
	class pHashNode
	{
		public:
			unsigned int id;	//!< effect id
			T data;				//!< pointer to an effect

			pHashNode() :
			   id(0)
			{}

			pHashNode(const int i, T in) :
			   id(i)
			{
				data = in;
			}

			void operator=(const pHashNode& in)
			{
				id = in.id;
				data = in.data;
			}
	};

	//! The array that belongs to an entry of HashTable.
	typedef pArray<pHashNode> pHashNodeArray;

	private:

		int m_count;                   //!< number of elements
		pArray<pHashNodeArray> m_hash; //!< hash table

		int m_pos0[P_MAX_THREADS];	 //!< first hash entry to the current object
		int m_pos1[P_MAX_THREADS];   //!< second hash entry to the current object

		unsigned int m_last_id[P_MAX_THREADS];	//!< id of the last retrieved object
		int m_last_pos0[P_MAX_THREADS];			//!< first hash entry of the last retrieved object
		int m_last_pos1[P_MAX_THREADS];			//!< second hash entry of the last retrieved object

	public:

		//! Default and initialization constructor.
		/*!
			@param size the number of supported pHashNodeArray
		*/
		pHashTable(const int size = P_HASH_SIZE);

		//! Destructor.
		~pHashTable();

		//! Resets the whole hash table.
		void reset();

		//! Add an object to the hash table.
		/*!
			@param id id of the new object
			@param data pointer to the new object
			@return i if successful and 0 otherwise
		*/
		int add(const unsigned int id, T data);

		//! Remove an object from the hash table.
		/*!
			@param id id of the object to be removed
			@return a pointer to the removed object
		*/
		T remove(const unsigned int id);

		//! Retrieve an object with the given id.
		/*!
			@param id id of the object
			@return if id is valid returns a pointer to the object with this id, otherwise retunrs 0
		*/
		T get_object(const unsigned int id, const int thread = 0);

		//! Retrieves the next object accordingly to iterator.
		/*!
			If first equals 1 place the iterator in the first object and return it.
			If first equals 0 place the iterator in the next object and return it.
			Moreover, this method returns 0 when the iteration finished.
			@param first
			@param thread
			@return a pointer to the current object
		*/
		T get_next_object(const int first = 0, const int thread = 0);

		//! Resize the hash table.
		/*!
			@param size the new amount of space
		*/
		void resize(const int size);

		//! Get number of elements in hash table.
		int get_count();
};

template <class T>
pHashTable<T>::pHashTable(const int size) :
   m_count(0)
{
	for (int i = 0; i < P_MAX_THREADS; i++)
	{
		m_pos0[i] = 0;
		m_pos1[i] = 0;
		m_last_id[i] = 0;
		m_last_pos0[i] = -1;
		m_last_pos1[i] = -1;
	}
	m_hash.reserve(size);
	m_hash.num = size;
}

//-----------------------------------------------------------------------------

template <class T>
pHashTable<T>::~pHashTable()
{
	reset();
}

//-----------------------------------------------------------------------------

template <class T>
void pHashTable<T>::reset()
{
	int i;
	m_count = 0;
	
	for (i = 0; i < P_MAX_THREADS; i++)
	{
		m_pos0[i] = 0;
		m_pos1[i] = 0;
		m_last_id[i] = 0;
		m_last_pos0[i] = -1;
		m_last_pos1[i] = -1;
	}

	for (i = 0; i < m_hash.num; i++)
		m_hash.buf[i].free();
	m_hash.free();

	// initial size
	m_hash.reserve(P_HASH_SIZE);
	m_hash.num = P_HASH_SIZE;
}

//-----------------------------------------------------------------------------

template <class T>
int pHashTable<T>::add(const unsigned int id, T data)
{
	int i;
	if (!id || !data)
		return 0;

	// If necessary, resize hash table
	if (m_count == m_hash.num*m_hash.num)
	{
		resize(2*m_hash.num + 1);

		// update optimization parameters
		for (i = 0; i < P_MAX_THREADS; i++)
		{
			m_last_id[i] = 0;
			m_last_pos0[i] = -1;
			m_last_pos1[i] = -1;
		}
	}

	int pos = id % m_hash.num;

	// Test if already exists an object with id.
	for (i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].id == id)
			return 0;

	pHashNode newNode(id, data);
	m_hash.buf[pos].add(newNode);
	m_count++;

	return 1;
}

//-----------------------------------------------------------------------------

template <class T>
T pHashTable<T>::remove(const unsigned int id)
{
	if (!id)
		return 0;

	T data = 0;

	int pos = id % m_hash.num;

	for (int i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].id == id)
		{
			data = m_hash.buf[pos].buf[i].data;
			m_hash.buf[pos].remove(i);
			m_count--;

			for(int j = 0; j < P_MAX_THREADS; j++)
			{
				// update iterator
				if (pos == m_pos0[j] && i < m_pos1[j])
					m_pos1[j]--;

				// update optimization parameters
				if (id == m_last_id[j])
				{
					m_last_id[j] = 0;
					m_last_pos0[j] = -1;
					m_last_pos1[j] = -1;
				}
				else if (pos == m_last_pos0[j] && i < m_last_pos1[j])
					m_last_pos1[j]--;
			}
		}

	return data;
}

//-----------------------------------------------------------------------------

template <class T>
T pHashTable<T>::get_object(const unsigned int id, const int thread)
{
	if (!id)
		return 0;

	if (id == m_last_id[thread])
		return m_hash.buf[m_last_pos0[thread]].buf[m_last_pos1[thread]].data;

	int pos = id % m_hash.num;

	for (int i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].id == id)
		{
			// update optimization parameters
			m_last_id[thread] = id;
			m_last_pos0[thread] = pos;
			m_last_pos1[thread] = i;

			return m_hash.buf[pos].buf[i].data;
		}

	return 0;
}

//-----------------------------------------------------------------------------

template <class T>
T pHashTable<T>::get_next_object(const int first, const int thread)
{
	if (first)
	{
		m_pos0[thread] = 0;
		m_pos1[thread] = 0;
	}

	for (int i = m_pos0[thread]; i < m_hash.num; i++)
	{
		for (int j = m_pos1[thread]; j < m_hash.buf[i].num; j++)
		{
			if (m_hash.buf[i].buf[j].data)
			{
				m_pos0[thread] = i;
				m_pos1[thread] = j+1;
				return m_hash.buf[i].buf[j].data;
			}
		}
		m_pos1[thread] = 0;
	}

	return 0;
}

//-----------------------------------------------------------------------------

template <class T>
void pHashTable<T>::resize(const int size)
{
	if (m_hash.arraysize == size)
		return;

	int empty, pos;
	int old_size = m_hash.arraysize;
	
	if (m_hash.arraysize < size)
		m_hash.reserve(size);
	m_hash.num = size;

	int i;

	for (i = 0; i < old_size; i++)
	{
		empty = 0;
		for (int j = 0; j < m_hash.buf[i].num; j++)
		{
			pos = m_hash.buf[i].buf[j].id % m_hash.num;
			if (pos != i)  // swap between different lines
				m_hash.buf[pos].add(m_hash.buf[i].buf[j]);
			else
			if(empty != j) // swap in same line
			{
				m_hash.buf[i].buf[empty] = m_hash.buf[i].buf[j];
				empty++;
			}
			else           // do not swap
				empty++;
		}
		// update length of line
		m_hash.buf[i].num = empty;
	}

	// if necessary, free memory of no used lines
	for (i = m_hash.num; i < old_size; i++)
		m_hash.buf[i].free();
}

//-----------------------------------------------------------------------------

template <class T>
int pHashTable<T>::get_count()
{
	int i,j=0;
	for( i=0;i<m_hash.num;i++ )
		j+=m_hash.buf[i].num;
	return j;
}

#endif
