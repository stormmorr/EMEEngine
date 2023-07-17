/*! \file */

#ifndef PGUIGROUP_H
#define PGUIGROUP_H

//! Graphic User Interface Group class
/*!
	This class implements a base class to graphic user interface objects that
	support window children.		
*/
class P3D_API pGUIGroup : public pGUIObject
{
	public:

		//! Default/Initialization constructor.
		/*!
			@param parent a pointer to parent window
		*/
		pGUIGroup(pGUIObject *parent=0);

		//! Detructor.
		virtual ~pGUIGroup();

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIGroup(*this); };
};

//! GUI Object Group Class Descriptor
/*!
	It is a descriptor to pGUIGroup classes and is used, mainly, in objects
	building process.
*/
class pGUIGroup_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new billboard object
		*/
		void *create()	const { return new pGUIGroup; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "group"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_GROUP; }
};

#endif

