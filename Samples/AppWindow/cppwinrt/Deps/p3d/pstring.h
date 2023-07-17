/*! \file */

#ifndef PSTRING_H
#define PSTRING_H

#define STR_MINSIZE 16	//!< pString's minimum size in bytes

//! Paralelo3D in-house string class
/*!
	This class implements variable-size strings, and auto-manages its memory space, expanding the buffer 
	whenever necessary. The class supplies methods for constructing a pString from a char pointer, 
	concatenating, copying and comparing strings, indexing a specific character and finding a sub-string.
*/
class P3D_API pString
{
	private:
		char* buf;	//!< buffer of characters
		int size;	//!< number of characters supported by the buffer
		int len;	//!< number of characters in the buffer

	public:

	//! Default constructor.
#ifdef QAGE_POINT
		pString() {};
#else
		pString();
#endif

	//! Construct a string from a char pointer.
	/*!
		@param in a c string
	*/
	pString(const char* in);

	//! Copy-constructor.
	/*!
		@param in the new string
	*/
	pString(const pString& in);

	//! Construct a string of length 'n' from a char pointer, beginning at position 'p'.
	/*!
		@param in a c string
		@param p initial position
		@param n number of characters to consider
	*/
	pString(const char* in,int p,int n);
		
	//! Destructor.
#ifdef QAGE_POINT
	~pString() {};
#else
	~pString();
#endif


	//! Type cast to char pointer.
	/*!
		@return the pString like a c string
	*/
	operator const char *() const
	{ return buf; }

	//! Indexing operator.
	/*!
		@param i an index
		@return i-th character of the string
	*/
	char operator[](int i) const
	{ return buf[i]; }

	//! Char pointer atribuition operator.
	/*!
		@param in a c string
	*/
	void operator=(const char* in);

	//! Atribuition operator.
	/*!
		@param in a pString
	*/
#ifdef QAGE_POINT
	void operator=(const pString& in) {};
#else
	void operator=(const pString& in);
#endif

	//! Self-concatenation operator with a char pointer.
	/*!
		@param in a c string
	*/
	void operator+=(const char* in);

	//! Self-concatenation operator.
	/*!
		@param in a pString
	*/
	void operator+=(const pString& in);

	//! Concatenation operator with a char pointer.
	/*!
		@param in a c string
		@return the result of concatenation between this string and a c string
	*/
	pString operator+(const char* in) const;

	//! Concatenation operator.
	/*!
		@param in a pString
		@return the result of concatenation between this string and a pString
	*/
	pString operator+(const pString& in) const;

	//! Copy the 'n'-sized contents of a char pointer beginning at position 'p'.
	/*!
		@param in a c string
		@param p initial position
		@param n number of characters to copy
	*/
	void copy(const char* in,int p,int n);

	//! Find a sub-string in the string.
	/*!
		@param str a c string
		@return the position of the initial character of the sub-string or -1 if the sub-string was not found
	*/
	int find(const char *str) const;

	//! Find the first occurrence of a character in the string.
	/*!
		@param c a character
		@return the position of the character or -1 if the character was not found
	*/
	int find(char c) const;

	//! Find the last occurrence of a character in the string.
	/*!
		@param c a character
		@return the position of the character or -1 if the character was not found
	*/
	int find_reverse(char c) const;

	//! Change the 'i'-th character of the string.
	/*!
		@param i the position of the i-th character
		@param c the new value of the i-th character
	*/
	void set_char(int i,char c);

	//! Crop the first 'n' characters of the string.
	/*!
		@param n the number of characters to crop
	*/
	void crop_begin(int n);

	//! Return a string consisting of the first 'n' characters of the original one.
	/*!
		@param n the number of characters to consider
		@return a string consisting of the first 'n' characters of the original one
	*/
	pString left(int n) const;

	//! Return a string consisting of the last 'n' characters of the original one.
	/*!
		@param n the number of characters to consider
		@return a string consisting of the last 'n' characters of the original one
	*/
	pString right(int n) const;

	//! Return a string consisting of the 'n' characters of the original one that follow position 'p', inclusive.
	/*!
		@param p initial position
		@param n the number of characters to consider
		@return a string consisting of the 'n' characters of the original one that follow position 'p', inclusive
	*/
	pString mid(int p,int n) const;

	//! Format the string using a format template.
	/*!
		@param fmt the template string
	*/
	void format(const char *fmt, ...);
	
	//! Equal compare operator.
	/*!
		@param str a c string
		@return 1 if strings are equals and 0 otherwise
	*/
	int operator==(const char *str) const 
	{ return strcmp(buf,str)==0; }

	//! Different compare operator.
	/*!
		@param str a c string
		@return 1 if strings are not equal and 0 otherwise
	*/
	int operator!=(const char *str) const 
	{ return strcmp(buf,str)!=0; }

	//! Greater than compare operator.
	/*!
		@param str a c string
		@return 1 if the original string is greater than str
	*/
	int operator>(const char *str) const 
	{ return strcmp(buf,str)>0; }

	//! Less than compare operator.
	/*!
		@param str a c string
		@return 1 if the original string is less than str
	*/
	int operator<(const char *str) const 
	{ return strcmp(buf,str)<0; }

	//! Greater than or equals to compare operator.
	/*!
		@param str a c string
		@return 1 if the original string is greater than or equals to str
	*/
	int operator>=(const char *str) const 
	{ return strcmp(buf,str)>=0; }

	//! Less than or equals to compare operator.
	/*!
		@param str a c string
		@return 1 if the original string is less than or equals to str
	*/
	int operator<=(const char *str) const 
	{ return strcmp(buf,str)<=0; }

	//! Compare with a char pointer.
	/*!
		@param str a c string
		@return <0 if original string less than str, 0 if original string identical to str and >0 if original string greater than str
	*/
	int compare(const char *str) const
	{ return strcmp(buf,str); }

	//! Compare the first 'n' characters of the string with a char pointer.
	/*!
		@param str a c string
		@param n the number of characters to consider
		@return <0 if original string less than str, 0 if original string identical to str and >0 if original string greater than str
	*/
	int compare(const char *str,int n) const
	{ return strncmp(buf,str,n); }

	//! Compare with a char pointer, case-insensitive flavour.
	/*!
		@param str a c string
		@return <0 if original string less than str, 0 if original string identical to str and >0 if original string greater than str
	*/
	int compare_nocase(const char *str) const
	{
		 return _stricmp(buf,str);
    }

	//! Change all characters to lower-case.
	void lower()
	{  
	   _strlwr(buf);
	}

	//! Change all characters to upper-case.
	void upper()
	{ 
	     _strupr(buf);
	}

	//! Return the length of the string in bytes.
	/*!
		@return number of characters in the buffer
	*/
	int length() const
	{ return len; }

	//! Allocs a fixed length string of s bytes.
	/*!
		@param s the quantity of bytes to alloc
	*/
	void reserve(int s);
	
	//! Writes the string bytes to a file.
	/*!
		@param fp a file
		@return the position of the last character written in the file
	*/
	int write(FILE *fp) const;
	
	//! Reads the string bytes from a file.
	/*!
		@param fp a file
		@return the length (in bytes) of the string
	*/
	int read(pFile& fp);

	//! Gets const pointer to internal string
	/*!
		@return the internal char[] string
	*/
	const char *getbuf() 
	{ return buf; }

};


#endif
