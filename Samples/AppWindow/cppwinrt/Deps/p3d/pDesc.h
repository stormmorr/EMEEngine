/*! \file */

#ifndef PDESC_H
#define PDESC_H

//! Class Descriptor class
/*!
	This class implements a base class to a class descriptor. It is used to editor management,
	objects instantiation and referencing. Any object that wants to be recognized and referenced
	by the editor must have a child class from this one, implementing that class' description. It
	consists of three methods: one for creating a new instanmce of the described class; one for
	retrieving the class name; and one for retrieving the integer that represents the class type.
*/
class P3D_API pClassDesc
{
	public:
		//! Instantiate an object of this class.
		/*!
			This is an abstract method and must be implemented by all classes
			that inherit of this class.
			@return a pointer to the new pRenderObject object
		*/
		virtual void *create() const =0;

		//! Get the class' name.
		/*!
			This is an abstract method and must be implemented by all classes
			that inherit of this class.
			@return the name of the associated class
		*/ 
		virtual const char *get_name() const =0;

		//! Get the class' type.
		/*!
			This is an abstract method and must be implemented by all classes
			that inherit of this class.
			@return the type of the associated class
		*/ 
		virtual int get_type() const =0;
};

//!  Parameter Descriptor class
/*!
	This class holds information on object parameters. Each class derived from pRenderObject
	can have any number of parameters. Each parameter must have an associated pParamDesc class
	describing its data. The pParamDesc class encloses the parameter's name, type and value,
	and is very useful in parameter-editing front-ends, like editors.
*/
class P3D_API pParamDesc
{
	public:
		pString name;		//!< parameter name
		int type;			//!< parameter type
		void *data;			//!< parameter value
		pString comment;	//!< parameter comments
	
		//! Retrieves the value of associated parameter in a string-form.
		/*!
			@return the value of associated parameter in a string-form
		*/
		const char *get_string() const;

		//! Stores the value of associated parameter in a binary buffer.
		/*!
			@bin the binary buffer
		*/
		void get_binary(void *bin) const;

		//! Updates the value of associated parameter from the str string.
		/*!
			@param str contains the new value of the associated parameter
		*/
		void set_string(const char *str);

		//! Updates the value of associated parameter from the bin binary buffer.
		/*!
			@param bin contains the new value of the associated parameter
		*/
		void set_binary(const void *bin);
};

#endif
