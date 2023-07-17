/*

	Command - Osirus Command
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OSICOMMANDS_H
#define OSICOMMANDS_H

#include "../Base/UNbase.h"
#include "../Gui/unGui.h"

namespace OSI
{

enum UnifiedCommand
{
  OSI_COMMAND,
  OSI_TAG,
  OSI_SCALE,
  OSI_RETRIEVAL,
  OSI_RAND,
};

///// Response
class Response
{
public:
	Response(int ButID, int PaneID)
		{ EventID = 0; ButtonID = ButID; m_PaneID = PaneID;
		  m_hover = false;
		  m_click = false;
		  m_select = false; };

	bool m_hover;
	bool m_click;
	bool m_select;

	int m_PaneID;

	int EventID;
	int ButtonID;
};

class unTreeLink
{
public:
	unTreeLink(int D1, int D2) { KX.push_back(D1); KX.push_back(D2); };
	virtual ~unTreeLink() {};

	std::vector<int> KX;
};

class EventArgs
{
public:
	/*************************************************************************
		Construction
	*************************************************************************/
	EventArgs(void) : handled(false) {}
	EventArgs(Response* response) : handled(false) {m_response = response;}
	virtual ~EventArgs(void) {}


	/*************************************************************************
		Data members
	*************************************************************************/
	Response* m_response;
	int m_ID;
	bool handled;		//!< handlers should set this to true if they handled the event, or false otherwise.
};

template<typename T>
struct FunctorReferenceBinder
{
    FunctorReferenceBinder(T& functor) :
        d_functor(functor)
    {}

    T& d_functor;
};

class SlotFunctorBase
{
public:
    virtual ~SlotFunctorBase() {};
    virtual bool operator()(const EventArgs& args) = 0;
};

class FreeFunctionSlot : public SlotFunctorBase
{
public:
    //! Slot function type.
    typedef bool (SlotFunction)(const EventArgs&);

    FreeFunctionSlot(SlotFunction* func) :
        d_function(func)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return d_function(args);
    }

private:
    SlotFunction* d_function;
};

template<typename T>
class FunctorCopySlot : public SlotFunctorBase
{
public:
    FunctorCopySlot(const T& functor) :
        d_functor(functor)
    {}

	/// Temporary Removed
    virtual bool operator()(const EventArgs& args)
    {
        return d_functor(args);
    }

private:
    T d_functor;
};

template<typename T>
class MemberFunctionSlot : public SlotFunctorBase
{
public:
    //! Member function slot type.
    typedef bool(T::*MemberFunctionType)(const EventArgs&);

    MemberFunctionSlot(MemberFunctionType func, T* obj) :
        d_function(func),
        d_object(obj)
    {}

    virtual bool operator()(const EventArgs& args)
    {
        return (d_object->*d_function)(args);
    }

private:
    MemberFunctionType d_function;
    T* d_object;
};

class SubscriberSlot
{
public:
    SubscriberSlot();
	~SubscriberSlot() {};

	/// Main Constructor
    SubscriberSlot(FreeFunctionSlot::SlotFunction* func);

	bool operator()(const EventArgs& args) const
    {
        return (*d_functor_impl)(args);
    }

	/// templatised constructors
    template<typename T>
    SubscriberSlot(bool (T::*function)(const EventArgs&), T* obj) :
        d_functor_impl(new MemberFunctionSlot<T>(function, obj))
    {}

    template<typename T>
    SubscriberSlot(const FunctorReferenceBinder<T>& binder) :
        d_functor_impl(new FunctorReferenceSlot<T>(binder.d_functor))
    {}

    template<typename T>
    SubscriberSlot(const T& functor) :
        d_functor_impl(new FunctorCopySlot<T>(functor))
    {}

    template<typename T>
    SubscriberSlot(T* functor) :
        d_functor_impl(new FunctorPointerSlot<T>(functor))
    {}

private:
    //Internal functor object to which we are bound
    SlotFunctorBase* d_functor_impl;
};

typedef struct Command
{
	std::string m_Text;
	UInt8 m_Level;
	std::vector<SubscriberSlot> Events;
} Command;

typedef struct Tag
{
	std::string m_Text;
} Tag;

typedef struct Expresstext
{
	std::string m_Text;
} Expresstext;

typedef struct Element
{
	UInt16	m_Type;
	unsigned int m_Ptr;
} Element;

typedef struct Expression
{
	std::vector<Element*> vec_Link;
} Expression;

typedef struct ExpressionTotal
{
	std::vector<Command*> vec_Command;
	std::vector<Tag*> vec_Tag;
	UN::UNsheet *vec_Linker;
} ExpressionTotal;

// MSVC Directly Interface with UNprocess
typedef struct Program
{
	std::vector<Expression*> m_Expression;
//	std::vector<trr::trrBinaryCube> m_Linker;	//Linker for expo data trans and storage
} Program;

};

#endif

// Command Scale ???? wtf???? 