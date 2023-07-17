/*! \file */

#ifndef PARRAY_H
#define PARRAY_H


//! Dynamic array template class
/*!
	This class implements a dynamic array template class.
*/
template <class T> 
class P3D_API pArray
{
	public:
		T *buf;		//!< generic buffer
		int num;	//!< number of entries
		
		int arraysize;	//!< pArray size in bytes

		//! Default constructor.
		pArray() : 
			arraysize(0), buf(0), num(0)
		{ }

		//! Copy-constructor.
		/*!
			@param in the new array
		*/
		pArray(const pArray<T>& in) :
			arraysize(0), buf(0), num(0)
		{ 
			reserve(in.num);
			for( int i=0;i<in.num;i++ )
				add(in[i]);
		}

		//! Destructor.
		~pArray()
		{ delete[] buf; }

		//! Assignment operator.
		/*!
			@param in the new array
		*/
		void operator=(const pArray<T>& in)
		{ 
			clear();
			reserve(in.num);
			for( int i=0;i<in.num;i++ )
				add(in[i]);
		}

		//! Adds another pArray to the end of current pArray.
		/*!
			@param in another pArray
		*/
		virtual void operator+=(const pArray<T>& in)
		{
			if (num+in.num>arraysize)
			{
				arraysize=num+in.num;
				T *tmp=new T[arraysize];
				for( int i=0;i<num;i++ )
					tmp[i]=buf[i];
				delete[] buf;
				buf=tmp;
			}
			for( int i=0;i<in.num;i++ )
				buf[i+num]=in[i];
			num+=in.num;
		}

		//! Reserve the required amount of space for the pArray.
		/*!
			@param n the required amount of space
		*/
		virtual void reserve(int n)
		{
			if (arraysize<n)
			{
				arraysize=n;
				T *tmp=new T[arraysize];
				for( int i=0;i<num;i++ )
					tmp[i]=buf[i];
				delete[] buf;
				buf=tmp;
			}
		}

		//! Free all the space.
		virtual void free()
		{
			delete[] buf;
			buf=0;
			num=0;
			arraysize=0;
		}

		//! Clear the whole pArray, but keep the memory space.
		inline void clear()
		{
			num=0;
		}

		//! Add a new element to the end of the pArray, automatically allocating more space, if needed.
		/*!
			@param elem the new element
		*/
		virtual void add(const T& elem)
		{
			if (num==arraysize)
			{
				if (arraysize<4)
					arraysize=4;
				else
					arraysize+=arraysize>>1;
				T *tmp=new T[arraysize];
				for( int i=0;i<num;i++ )
					tmp[i]=buf[i];
				delete[] buf;
				buf=tmp;
			}
			buf[num++]=elem;
		}

		//! Insert a new element in the given position of the pArray, automatically allocating more space, if needed.
		/*!
			@param elem the new element
			@param i the desired new element position
		*/
        virtual void insert(const T& elem,int i)
        {
			if (num==arraysize)
			{
				   if (arraysize<4)
						   arraysize=4;
				   else
						   arraysize+=arraysize>>1;
				   T *tmp=new T[arraysize];
				   for( int l=0;l<num;l++ )
						   tmp[l]=buf[l];
				   delete[] buf;
				   buf=tmp;
			}
			num++;

			int j;
			for(j=num-1;j>i;j--)
				   buf[j]=buf[j-1];
			buf[j]=elem;
       }


		//! Remove the element in the given position.
		/*!
			@param i i-th entry of the array
		*/
		inline void remove(int i)
		{
			if (i<num)
			{
				int j;
				for (j = i; j < num-1; j++) 
					buf[j] = buf[j+1];
				num--;
			}
		}

		//! Remove 'n' elements in the given position.
		/*!
			@param i initial position to remove
			@param n number of elements to remove
		*/
		inline void remove(int i,int n)
		{
			if (i+n<=num)
			{
				int j;
				for (j = i; j < num-n; j++) 
					buf[j] = buf[j+n];
				num-=n;
			}
		}

		//! Indexing operator returing const
		inline const T& operator[](int i) const 
		{ return(buf[i]); }

		//! Indexing operator
		inline T& operator[](int i) 
		{ return buf[i]; }
};

typedef pArray<pString> pStringArray;
typedef pArray<pStringArray> pStringArray2;
typedef pArray<pVector> pVectorArray;
typedef pArray<pVectorArray> pVectorArray2;
typedef pArray<int> pIntArray;
typedef pArray<pIntArray> pIntArray2;
typedef pArray<unsigned int> pUIntArray;
typedef pArray<pUIntArray> pUIntArray2;
typedef pArray<float> pFloatArray;
typedef pArray<pFloatArray> pFloatArray2;

#endif
