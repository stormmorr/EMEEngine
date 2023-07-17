/*! \file */

#ifndef PFILE_H
#define PFILE_H

class cGerenciadorArquivos;

//! Paralelo3D Render Objects scene data file management class
/*!
	This class implements a manager and interface for paralelo3D render objects' scene data
	files (.pro files). Its members are a pointer to a data buffer containing the file load
	on memory, the current access position in the file and the total length of the file.
	Among the methods available  in this class are: opening and closing a file, seeking a
	position in it, unzipping a zipped file, reading a certain amount of data from the file,
	and more.
*/
class P3D_API pFile
{
	public:
		pString name;			//!< file name
		unsigned char *buf;		//!< the file data buffer
		int pos,				//!< current position in the file
			len,				//!< length of the file
			flag;				//!< general flags
		/*!
			Table with text file itens as an array of array of strings
			Each group (named like '[groupname]') has an array of 
			parameter  strings (in the form 'param=data')
		*/
		pStringArray2 *table;

	//! Default constructor.
	pFile();

	//! Destructor.
	~pFile();

	//! Try to find the formatted string "[groupname]" in this file.
	/*!
		@param groupname name of the group to be found
		@return 1 if find a group whose name is equals to groupname, otherwise returns 0
	*/
	int find_group(const char *groupname) const;
	
	//! Append the contents of this file in a hash table of strings for fast text reads of .pro files.
	void append_table();

	//! Clear the hash table of strings.
	void clear_table();

	//! Seek a position in the file.
	/*!
		@param offset number of positions to move the position pointer
	*/
	void seek(int offset);
	
	//! Open a file by its given file name.
	/*!
		@param filename name of the file to be opened
		@return true if successful and false otherwise
	*/
	bool open(const char *filename);

	//! Allocate buffer for file with given size.
	/*!
		@param size new size of the file buffer
	*/
	void alloc_buf(int size);

	//! Close the file
	void close();

	//! Try to read 'size' bytes from the file (beginning at the current position 'pos') into the 'dest' buffer
	/*!
		@param dest holds 'size' bytes from the file
		@param size number of bytes to read
		@return the number of read bytes
	*/
	int read(void *dest, int size);

	//! Get a string from the profile
	/*!
		Firstly, it try to find the formatted string "[section]" in this file. So,
		into this section it try to find another formatted string "key=". Finally,
		it stores into dest the string after "key=", e.g, if "key=1", dest = "1".
		@param section name of the section
		@param key name of the key
		@param dest holds the value associated with key into section
		@return 1 if successful and 0 otherwise
	*/
	int get_profile_string(const char *section, const char *key,pString& dest);

	//! Get a integer from the profile
	/*!
		Firstly, it try to find the formatted string "[section]" in this file. So,
		into this section it try to find another formatted string "key=". Finally,
		it stores into dest the string after "key=", e.g, if "key=1", dest = 1.
		@param section name of the section
		@param key name of the key
		@param dest holds the value associated with key into section
		@return 1 if successful and 0 otherwise
	*/
	int get_profile_int(const char *section,const char *key,int& dest);

	//! Get a float from the profile
	/*!
		Firstly, it try to find the formatted string "[section]" in this file. So,
		into this section it try to find another formatted string "key=". Finally,
		it stores into dest the string after "key=", e.g, if "key=1", dest = 1.0.
		@param section name of the section
		@param key name of the key
		@param dest holds the value associated with key into section
		@return 1 if successful and 0 otherwise
	*/
	int get_profile_float(const char *section,const char *key,float& dest);

	//! Get a string from the file.
	/*!
		@param dest holds the string
	*/
	void get_string(pString& dest);

	//! Retrives the next integer value into this file.
	/*!
		@return the next integer value into this file
	*/
	int get_int();

	//! Retrives the next floating-point value into this file.
	/*!
		@return the next floating-point value into this file
	*/
	float get_float();
};

#endif
