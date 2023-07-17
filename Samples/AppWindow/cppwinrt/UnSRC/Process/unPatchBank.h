/*

	unPatchBank - Image Overlay
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNPATCHBANK_H
#define UNPATCHBANK_H

#include <windows.h>
#include <tlhelp32.h> // for the process snapshot

	//Cross-plat requirements
#include <vector>
#include <string>

#include "TCTraverse.h"
#include "MemWalk.h"

#include <map>

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-BulletSystem.h"
#include "Q-AI-NNbot.h"

#include "Q-NET-ProtoMap.h"

#include "Q-ShellAProtoTypes.h"
#include "Q-WE-ShellATypes.h"

#include "SDL.h"

using std::string;

namespace Point
{

///// Gui Click Response
class unGuiResponse
{
public:
	unGuiResponse(int ButID, int PaneID)
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
	EventArgs(unGuiResponse* response) : handled(false) {m_response = response;}
	virtual ~EventArgs(void) {}


	/*************************************************************************
		Data members
	*************************************************************************/
	unGuiResponse* m_response;
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

class unPatchFunction
{
public:
	unPatchFunction();
	~unPatchFunction();

	std::string m_StrAdd;
	std::string m_StrID;

	std::vector<std::string> m_Ret;
	std::vector<std::string> m_Arg;

	int m_RetCount;
	int m_ArgCount;

	FARPROC m_Address;

	//int *m_Pointer;
	//int **__w64 m_Address;
	//unsigned int m_Size;
};

/*typedef struct UNspace
{
	unsigned int m_VecPointer;
	unsigned int m_Size;
} UNspace;*/

class unPatch
{
public:
	unPatch();
	~unPatch();

	std::string m_Title;
	std::string m_Author;
	std::string m_Category;
	std::string m_Filename;
	float m_Version;
	int m_Count;

	std::vector<unPatchFunction*> m_Function;
	HMODULE m_hDll;

#if 0
	int *m_Pointer;
	int **__w64 m_Address;
	unsigned int m_Size;

	void realloc(size_t i_Size);
#endif
};

class unPatchBank
{
public:
	unPatchBank();
	~unPatchBank();

	void acPush(std::string i_PatchName);
	void acInfo(const char* i_Filename);

	std::vector<unPatch*> m_Patch;
	std::vector<unPatchFunction*> m_Function;

	std::map<const char *, std::vector<unPatchFunction*>*> map_Function;

	std::string m_Attribute;
};

class unPatchClass
{
public:
#if 0
#if 0
	std::vector<void (*) (int)> vec_Function;
#else
	std::vector<Point::SubscriberSlot> vec_Function;
#endif
#endif
private:
};

	typedef void (CALLBACK* LPFNDLLFUNC1)(void (*i_FunctionPTR)(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone));
	typedef void (CALLBACK* LPFNDLLFUNC2)(void (*i_FunctionPTR)(QpoTransform * transform, QpoVec3d * result));
	typedef void (CALLBACK* LPFNDLLFUNC3)(void (*i_FunctionPTR)(QpoAvatar Avatar, int Motion, float Time, QpoTransform * Transform, float BlendAmount));
	typedef void (CALLBACK* LPFNDLLFUNC4)(void (*i_FunctionPTR)(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir));
	typedef void (*LPFNDLLFUNC5)(void);
	typedef void (CALLBACK* LPFNDLLFUNC6)(void (*i_FunctionPTR)(QpoVec3d * vec1, float scale, QpoVec3d * dir, QpoVec3d * result));
	typedef void (*LPFNDLLFUNC10)(void);
	typedef void (CALLBACK* LPFNDLLFUNC7)(QSharedStruct<struct GVARS::GlobalVariablesStruct> i_Struct);
	typedef void (CALLBACK* LPFNDLLFUNC8)(QSharedStruct<class QpoAvatarFlags> i_Struct);
	typedef void (CALLBACK* LPFNDLLFUNC9)(QSharedStruct<class GVARS::PlayerFlags> i_Struct);

};

#endif