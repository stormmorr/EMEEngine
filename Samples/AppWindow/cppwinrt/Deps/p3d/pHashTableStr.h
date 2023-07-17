/*! \file */

#ifndef PHASHTABLESTR_H
#define PHASHTABLESTR_H

//! Implements a HashTable data structure.
/*!
	Implements a HashTable data structure whose the first entry is a string
	and the second entry is a template.
*/
template <class T> 
class P3D_API pHashTableStr
{
	//! Hash node struct.
	class pHashNode
	{
		public:
			pString str;	//!< name
			T data;			//!< pointer to an effect

			pHashNode()
			{}

			pHashNode(const pString& s, T in) :
			   str(s)
			{
				data = in;
			}

			void operator=(const pHashNode& in)
			{
				str = in.str;
				data = in.data;
			}
	};

	//! The array that belongs to an entry of HashTable.
	typedef pArray<pHashNode> pHashNodeArray;

	private:

		int m_count;                   //!< number of elements
		pArray<pHashNodeArray> m_hash; //!< hash table

		int m_pos0[P_MAX_THREADS];	//!< first hash entry to the current object
		int m_pos1[P_MAX_THREADS];	//!< second hash entry to the current object

		pString m_last_str[P_MAX_THREADS]; //!< string of the last retrieved object
		int m_last_pos0[P_MAX_THREADS];    //!< first hash entry of the last retrieved object
		int m_last_pos1[P_MAX_THREADS];    //!< second hash entry of the last retrieved object

		//! Given a string, it returns an integer that represents this string.
		/*!
			@param str a string
			@return an integer that represents the str string, -1 if str is NULL
		*/
		int get_pos(const char *str) const;

	public:

		//! Default and initialization constructor.
		/*!
			@param size the number of supported pHashNodeArray
		*/
		pHashTableStr(const int size = P_HASH_SIZE);

		//! Destructor.
		~pHashTableStr();

		//! Resets the whole hash table.
		void reset();

		//! Add an object to the hash table.
		/*!
			@param str name of the new object
			@param data pointer to the new object
			@return i if successful and 0 otherwise
		*/
		int add(const char *str, T data);

		//! Remove an object from the hash table.
		/*!
			@param str name of the object to be removed
			@return a pointer to the removed object
		*/
		T remove(const char *str);

		//! Retrieve an object with the given id.
		/*!
			@param str name of the object
			@return if id is valid returns a pointer to the object with this id, otherwise retunrs 0
		*/
		T get_object(const char *str, const int thread = 0);

		//! Retrieves the next object accordingly to iterator.
		/*!
			If first equals 1 place the iterator in the first object and return it.
			If first equals 0 place the iterator in the next object and return it.
			Moreover, this method returns 0 when the iteration finished.
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
int pHashTableStr<T>::get_pos(const char *str) const
{
	if (!str)
		return -1;

	int i = 0, sum = 0;

	while (str[i])
		sum += (int)str[i++];

	return sum;
}

//-----------------------------------------------------------------------------

template <class T>
pHashTableStr<T>::pHashTableStr(const int size) :
   m_count(0)
{
	for (int i = 0; i < P_MAX_THREADS; i++)
	{
		m_pos0[i] = 0;
		m_pos1[i] = 0;
		m_last_str[i] = "";
		m_last_pos0[i] = -1;
		m_last_pos1[i] = -1;
	}
	m_hash.reserve(size);
	m_hash.num = size;
}

//-----------------------------------------------------------------------------

template <class T>
pHashTableStr<T>::~pHashTableStr()
{
	reset();
}

//-----------------------------------------------------------------------------

template <class T>
void pHashTableStr<T>::reset()
{
	int i;
	m_count = 0;

	for (i = 0; i < P_MAX_THREADS; i++)
	{
		m_pos0[i] = 0;
		m_pos1[i] = 0;
		m_last_str[i] = "";
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
int pHashTableStr<T>::add(const char *str, T data)
{
	int i;
	if (!str || !data)
		return 0;
	// If necessary, resize hash table
	if (m_count == m_hash.num*m_hash.num)
	{
		resize(2*m_hash.num + 1);

		// update optimization parameters
		for (i = 0; i < P_MAX_THREADS; i++)
		{
			m_last_str[i] = "";
			m_last_pos0[i] = -1;
			m_last_pos1[i] = -1;
		}
	}

	int pos = get_pos(str) % m_hash.num;

	// Test if already exists an object with id.
	for (i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].str.compare(str) == 0)
			return 0;

	pHashNode newNode(str, data);
	m_hash.buf[pos].add(newNode);
	m_count++;

	return 1;
}

//-----------------------------------------------------------------------------

template <class T>
T pHashTableStr<T>::remove(const char *str)
{
	if (!str)
		return 0;

	T data = 0;

	int pos = get_pos(str) % m_hash.num;

	for (int i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].str.compare(str) == 0)
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
				if (m_last_str[j].compare(str) == 0)
				{
					m_last_str[j] = "";
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
T pHashTableStr<T>::get_object(const char *str, const int thread)
{
	if (!str)
		return 0;

	if (m_last_str[thread].compare("") != 0 && m_last_str[thread].compare(str) == 0)
		return m_hash.buf[m_last_pos0[thread]].buf[m_last_pos1[thread]].data;

	int pos = get_pos(str) % m_hash.num;

	for (int i = 0; i < m_hash.buf[pos].num; i++)
		if (m_hash.buf[pos].buf[i].str.compare(str) == 0)
		{
			// update optimization parameters
			m_last_str[thread] = "";
			m_last_pos0[thread] = pos;
			m_last_pos1[thread] = i;

			return m_hash.buf[pos].buf[i].data;
		}

	return 0;
}

//-----------------------------------------------------------------------------

template <class T>
T pHashTableStr<T>::get_next_object(const int first, const int thread)
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
void pHashTableStr<T>::resize(const int size)
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
			pos = get_pos(m_hash.buf[i].buf[j].str) % m_hash.num;
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
int pHashTableStr<T>::get_count()
{
	int i,j=0;
	for( i=0;i<arraysize;i++ )
		j+=m_hash.buf[i].num;
	return j;
}

#endif
