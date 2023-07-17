/*

pch.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <tuple>

namespace Cube
{

	extern char* ag_ClearChar(int f_Size);

};

// Enable function definitions in the GL headers below
#define GL_GLEXT_PROTOTYPES 1

#define ECOIN_CONSENSUS_ID 6

#define ECOIN_CONSENSUS_FIRST_SANE_ID 6

#if 1 //not recomended or production deploy
#define ECOIN_SECURE_01 1
#endif

#if 1 //osi-memory
#define ECOIN_OSI_MEMORY 1
#endif

#if 0 //temp test normal all memory improvements off
#define OSI_MEM_APP 1
#endif

#if 1 //osi-memory base functions
#define ECOIN_OSI_MEMORY_FUNC 1
#endif

#if 1 //recomended
#define ECOIN_OSI_MEMORY_AUX 1
#endif

#if 0 //not required
#define ECOIN_OSI_MEM_MUSION 1
#endif

#if 0 //not required
#define ESL_LOAD_VARS 1
#endif

#if 0
#define ECOIN_REFLECT_STATUS_LIVE_OVERFLOW 1
#endif

#if 1 // asynchronous by design
#define ECOIN_SUPER_LOCKS 1
#endif

#if 0 // stealth in-close
#define SUPER_SNEAKY 1
#endif

#if 0 // ESL Speed Benchmarking
#define ESL_SPEED_BENCH 1
#endif

#if 1 // max scan range
#define AVATAR_VIEW_RANGE_ON 1
#endif

#if 1 // max scan range
#define AVATAR_VIEW_RANGE 1850.0f
#endif

#if 1 //recommended
#define OSI_MEMORY_BICYCLE_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_HESH_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_BIVECTOR_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_ELEMENT_REF 1
#endif

#if 1 
#define ECOIN_MEMORY_FULL_MUTEX 1
#endif

#if 1
#define QLOGON_SAVE_EACH 1
#endif

#if 1
#define QRENDERER_EDITOR 1
#endif

#if 0
#define ECOIN_PROCEDURE_UPLOAD 1
#endif

#if 1 //important: on production switch off
#define ECOIN_PROCEDURE_RESET 1
#endif

#if 0 //ecoin Experimental Reflection Tests, production code off
#define ECOIN_REFLECTION_EXP 1
#endif

#if 1 //ecoin Experimental Reflection Tests, production code off
#define ECOIN_REFLECTION_EXP_FUNCTION 1
#endif

#if 0 // test loadcom(1), production code off
#define TEST_VERIFY_SCP_BUILD_ECOM 1
#endif

#if 0 //load small, production code mebbe...
#define ECOIN_LOAD_ACKS 1
#endif

#if 0 //not support, production code off
#define ECOIN_OVERRIDE 1
#endif

#if 1 //mebbe ?, ya production code mebbe
#define ECOIN_BALANCE_PEER_EACH_ELEMENT 1
#endif

#if 0
#define ECOIN_WALLET_SAVE_ASYNC 1
#endif

#if 1 //production code off / debug testing on
#define ECOIN_DEBUG_BREAKS 1
#endif

#if 1 //production code off / current testing breaks FULLY off
#define ECOIN_DBG_BREAK 1
#endif

#if 1 //production code off / debug testing ?//TX FULLY off
#define ECOIN_DEBUG_BREAKS_TX 1
#endif

#if 1 //!!!if receiving unexplained exceptions try switching this define off!!!
#define HAS_BOOST_ANY_CAST 1
#endif

#if 0
#define FUNCSIG_ORIGIN_CAST 1
#endif

#if 1
#define REFLECT_LAZY_ECOM_OVERLOAD 1
#endif

#if 0
#define REFLECT_WORK_EXT 1
#endif

#if 1
#define ECOIN_REFLECTED_WALLET 1
#endif

#if 1
#define ECOIN_ASYNC_REFRESH_SECONDS 60
#else
#define ECOIN_ASYNC_REFRESH_SECONDS 10
#endif

#define ECOIN_ASYNC_REFRESH_MILLISECONDS (ECOIN_ASYNC_REFRESH_SECONDS * 1000)

#define AV_START_X 25.0f
#define AV_START_Y 15.0f
#define AV_START_Z 25.0f

#define NOM_LIGHT 4000

#define ECOIN_SHARE_PROTOCOL_LENGTH 3000

#ifndef XAUDIO2_HELPER_FUNCTIONS
#define XAUDIO2_HELPER_FUNCTIONS
#endif

#define g_ref_CurrentPath std::string(":")
#define g_ref_InOut_Var std::string("/")
#define g_ref_Div std::string(":::")
#define g_ref_global_Div std::string(":-:")
#define g_ref_global_start std::string(":G:")
#define g_ref_delegate_start std::string(":E:")
#define g_ref_flow_reset std::string(":F:")
#define g_ref_Path_Div std::string(":|:")
#define g_ref_fun_Div std::string("->>")
#define g_ref_fun_Append std::string("_pach")

#define DEFINE_MY_TYPE_V1(tp) \
typedef (tp)elem_V1;

#define DEFINE_MY_TYPE_V2(tp) \
typedef (tp)elem_V2;

#define DEFINE_MY_TYPE_V3(tp) \
typedef (tp)elem_V3;

#define DEFINE_MY_TYPE_V4(tp) \
typedef (tp)elem_V4;

#define DEFINE_MY_TYPE_V5(tp) \
typedef (tp)elem_V5;

#define DEFINE_MY_TYPE_V6(tp) \
typedef (tp)elem_V6;

#define DEFINE_MY_TYPE_V7(tp) \
typedef (tp)elem_V7;

#define DEFINE_MY_TYPE_V8(tp) \
typedef (tp)elem_V8;

#define DEFINE_MY_TYPE_V9(tp) \
typedef (tp)elem_V9;

#define DEFINE_MY_TYPE_V10(tp) \
typedef (tp)elem_V10;

class PathPosition
{
public:
	PathPosition()
		{
		m_X = -1;
		m_Y = -1;
		}

	PathPosition(int f_X, int f_Y)
		{
		m_X = f_X;
		m_Y = f_Y;
		}

	~PathPosition()
		{
		m_X = -1;
		m_Y = -1;
		}

	int m_X;
	int m_Y;
};

extern PathPosition g_PP;

extern std::vector<std::vector<std::string>> g_vec_Path;
extern std::vector<std::vector<std::string>> g_vec_PathLabel;

extern bool g_MutexLocked;
extern bool g_GameFocusOn;

extern void ag_LockMutex(void);
extern void ag_UnLockMutex(void);

extern std::string ag_AcceptObjectName(void);

extern std::vector<std::vector<std::string>> g_VectorObjectName;
extern std::vector<int> g_Proll;

extern void ag_CentraliseCull(std::string f_CullStringPath);
extern void ag_StatusLive(std::string f_Path, std::string f_Label, bool f_Prepare = false, int f_VecIndex = 0);
extern void ag_StatusSync(std::string f_Path, std::string f_Label, bool f_Prepare = false, int f_VecIndex = 0);

extern void ag_Click(std::string f_ButtonName);

extern std::string ag_Build_Path(PathPosition f_PP);

extern void ag_DeleteMapObject(std::string f_MapNamePath);

#ifdef ECOIN_OSI_MEMORY_AUX
#if _MSC_VER >= 1930
#include "Include\osimemory_v17.h"
#elif _MSC_VER >= 1931
#include "Include\osimemory_v17.h"
#elif _MSC_VER >= 1932
#include "Include\osimemory_v17.h"
#else
#include "Include\osimemory.h"
#endif
#else
#include <memory>
#endif

#include <boost/any/basic_any.hpp>

namespace Cube
{

	extern int ag_min(int f_In, int f_min);
	extern int ag_max(int f_In, int f_max);

	extern float ag_min(float f_In, float f_min);
	extern float ag_max(float f_In, float f_max);

}

#ifndef HAS_BOOST_ANY_CAST
template<class T>
T ag_any_cast(boost::any f_Any)
{
	try
		{
		return boost::any_cast<T>(f_Any);
		}

	catch (boost::bad_any_cast &e)
		{
#if 1
		std::string f_E_What_String = std::string(e.what());
#endif
#if 1
		throw;
#endif
#if 0
		return T(0);
#endif
		}
}
#else
#define ag_any_cast boost::any_cast
#endif

class ecom_base_flap
{
public:
	ecom_base_flap()
		{
		}

	~ecom_base_flap()
		{
		}
};

class ecom_vector_layer1
{
public:
	ecom_vector_layer1()
		{
		}

	~ecom_vector_layer1()
		{
		}

	std::map<std::string, std::vector<bool>*> m_vec_Map_Bool;
	std::map<std::string, std::vector<float>*> m_vec_Map_Float;
	std::map<std::string, std::vector<double>*> m_vec_Map_Double;
	std::map<std::string, std::vector<int>*> m_vec_Map_Int;
	std::map<std::string, std::vector<unsigned int>*> m_vec_Map_UInt;
	std::map<std::string, std::vector<char>*> m_vec_Map_Char;
	std::map<std::string, std::vector<unsigned char>*> m_vec_Map_UChar;
	std::map<std::string, std::vector<std::string>*> m_vec_Map_String;
};

class ecom_vector_layer2
{
public:
	ecom_vector_layer2()
		{
		}

	~ecom_vector_layer2()
		{
		}

	std::map<std::string, std::vector<std::vector<bool>>*> m_vec_vec_Map_Bool;
	std::map<std::string, std::vector<std::vector<float>>*> m_vec_vec_Map_Float;
	std::map<std::string, std::vector<std::vector<double>>*> m_vec_vec_Map_Double;
	std::map<std::string, std::vector<std::vector<int>>*> m_vec_vec_Map_Int;
	std::map<std::string, std::vector<std::vector<unsigned int>>*> m_vec_vec_Map_UInt;
	std::map<std::string, std::vector<std::vector<char>>*> m_vec_vec_Map_Char;
	std::map<std::string, std::vector<std::vector<unsigned char>>*> m_vec_vec_Map_UChar;
	std::map<std::string, std::vector<std::vector<std::string>>*> m_vec_vec_Map_String;
};

class ecom_vector_layer3
{
public:
	ecom_vector_layer3()
		{
		}

	~ecom_vector_layer3()
		{
		}

	std::map<std::string, std::vector<std::vector<std::vector<bool>>>*> m_vec_vec_vec_Map_Bool;
	std::map<std::string, std::vector<std::vector<std::vector<float>>>*> m_vec_vec_vec_Map_Float;
	std::map<std::string, std::vector<std::vector<std::vector<double>>>*> m_vec_vec_vec_Map_Double;
	std::map<std::string, std::vector<std::vector<std::vector<int>>>*> m_vec_vec_vec_Map_Int;
	std::map<std::string, std::vector<std::vector<std::vector<unsigned int>>>*> m_vec_vec_vec_Map_UInt;
	std::map<std::string, std::vector<std::vector<std::vector<char>>>*> m_vec_vec_vec_Map_Char;
	std::map<std::string, std::vector<std::vector<std::vector<unsigned char>>>*> m_vec_vec_vec_Map_UChar;
	std::map<std::string, std::vector<std::vector<std::vector<std::string>>>*> m_vec_vec_vec_Map_String;
};

namespace ecoin
{

class Variable;
class CodeLine;

};

class ecom_base
{
public:
	ecom_base()
		{
		ecomClear();
		}

	~ecom_base()
		{
		ecomClear();
		}

	void ecomClear(void)
		{
		m_Map_Bool.clear();
		m_Map_Float.clear();
		m_Map_Double.clear();
		m_Map_Int.clear();
		m_Map_UInt.clear();
		m_Map_Char.clear();
		m_Map_UChar.clear();
		m_Map_String.clear();

		m_veclayer1 = nullptr;
		m_veclayer2 = nullptr;
		m_veclayer3 = nullptr;

		m_Status = 0;
		m_Valid = false;
		}

	bool acEmptyBase(void)
		{
		if(m_Map_Float.size() > 0)
			{
			return false;
			}

		if(m_Map_Bool.size() > 0)
			{
			return false;
			}

		if(m_Map_Int.size() > 0)
			{
			return false;
			}

		if(m_Map_UInt.size() > 0)
			{
			return false;
			}

		if(m_Map_Char.size() > 0)
			{
			return false;
			}

		if(m_Map_UChar.size() > 0)
			{
			return false;
			}

		if(m_Map_String.size() > 0)
			{
			return false;
			}

		if(m_veclayer1 != nullptr)
			{
			return false;
			}

		if(m_veclayer2 != nullptr)
			{
			return false;
			}

		if(m_veclayer3 != nullptr)
			{
			return false;
			}

		return true;
		}

	// Base Type // ---
	typedef std::shared_ptr<ecom_base> base_type;

	void ac_Attach_Void(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine);

	ecom_base::base_type ac_Attach_Base(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine);

	std::shared_ptr<ecoin::Variable> ac_Attach_Var(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine);

	template<typename... T>
	std::shared_ptr<ecom_base> ac_Invoke(std::string f_Map_Function, T... args);

	template<typename... T>
	void ac_Invoke_void_function(std::string f_Map_Function, T... args);

	template<typename _R, typename _FuncString, typename... T>
	std::shared_ptr<ecoin::Variable> ac_Invoke_Varet(_R f_ReturnTyper, _FuncString f_Map_Function, T... args);

	void ac_Push(bool& f_Var, std::string f_MemberVarName);
	void ac_Push(float& f_Var, std::string f_MemberVarName);
	void ac_Push(double& f_Var, std::string f_MemberVarName);
	void ac_Push(int& f_Var, std::string f_MemberVarName);
	void ac_Push(unsigned int& f_Var, std::string f_MemberVarName);
	void ac_Push(char& f_Var, std::string f_MemberVarName);
	void ac_Push(unsigned char& f_Var, std::string f_MemberVarName);
	void ac_Push(std::string& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<bool>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<float>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<double>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<int>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<unsigned int>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<char>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<unsigned char>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::string>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<bool>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<float>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<double>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<int>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<unsigned int>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<char>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<unsigned char>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::string>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<bool>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<float>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<double>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<int>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<unsigned int>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<char>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<unsigned char>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<std::string>>>& f_Var, std::string f_MemberVarName);

	bool* ac_GetBLT(std::string f_MemberVarName);
	float* ac_GetFLT(std::string f_MemberVarName);
	int* ac_GetINT(std::string f_MemberVarName);
	std::string* ac_GetSTR(std::string f_MemberVarName);

	void* ac_Get(std::string f_MemberVarName, std::string f_TypeName)
		{
		if(f_TypeName == "int")
			{
			return m_Map_Int[f_MemberVarName];
			}
		else if(f_TypeName == "char")
			{
			return m_Map_Char[f_MemberVarName];
			}
		else if(f_TypeName == "float")
			{
			return m_Map_Float[f_MemberVarName];
			}
		else if(f_TypeName == "bool")
			{
			return m_Map_Int[f_MemberVarName];
			}
		else if(f_TypeName == "std::string")
			{
			return m_Map_String[f_MemberVarName];
			}
		}

	std::map<std::string, bool*> m_Map_Bool;
	std::map<std::string, float*> m_Map_Float;
	std::map<std::string, double*> m_Map_Double;
	std::map<std::string, int*> m_Map_Int;
	std::map<std::string, unsigned int*> m_Map_UInt;
	std::map<std::string, char*> m_Map_Char;
	std::map<std::string, unsigned char*> m_Map_UChar;
	std::map<std::string, std::string*> m_Map_String;

	std::shared_ptr<ecom_vector_layer1> m_veclayer1;
	std::shared_ptr<ecom_vector_layer2> m_veclayer2;
	std::shared_ptr<ecom_vector_layer3> m_veclayer3;

	int m_Status;

	//Decoy
	std::string m_PathName;
	int m_StackCount;
	bool m_Valid;
};

class ecom_Marker
{
public:
	ecom_Marker()
		{
		//ecomClear();
		}

	~ecom_Marker()
		{
		//ecomClear();
		}
};

 ///////////////////////////////////////////////////
// Ecom SuperClass 'ecom_base' Main Memory Spire //
extern std::map<std::string, std::shared_ptr<ecom_base>> g_Map_ecomRefBase;
extern std::map<std::string, int> g_Map_ecomRefCount;

 /////////////////////////////////////////////////////////////
// Ecom SuperClass 'ecom_base' Main Function Spire --------//
extern std::map<std::string, boost::any> g_Map_Function;

 ////////////////////////////////////////////////////////////
// Ecom SuperClass 'ecom_base' Main Function Typing Spire //
class FuncHolding;
extern std::map<std::string, std::shared_ptr<FuncHolding>> g_Map_Function_Sig;

 ///////////////////////////////////////////
// Reflection Helper Globalized Function //
extern std::shared_ptr<ecom_base> ag_Produce_base(std::string f_MappingString);

 ////////////////////////////////////////////////
// [GLOBAL] Memory Referencing for reflection //
extern void ag_Push(bool& f_Var, std::string f_GlobalVarName);
extern void ag_Push(float& f_Var, std::string f_GlobalVarName);
extern void ag_Push(double& f_Var, std::string f_GlobalVarName);
extern void ag_Push(int& f_Var, std::string f_GlobalVarName);
extern void ag_Push(unsigned int& f_Var, std::string f_GlobalVarName);
extern void ag_Push(char& f_Var, std::string f_GlobalVarName);
extern void ag_Push(unsigned char& f_Var, std::string f_GlobalVarName);
extern void ag_Push(std::string& f_Var, std::string f_GlobalVarName);

std::map<std::string, bool*> g_Map_Bool;
std::map<std::string, float*> g_Map_Float;
std::map<std::string, double*> g_Map_Double;
std::map<std::string, int*> g_Map_Int;
std::map<std::string, unsigned int*> g_Map_UInt;
std::map<std::string, char*> g_Map_Char;
std::map<std::string, unsigned char*> g_Map_UChar;
std::map<std::string, std::string*> g_Map_String;

//[END] #ifdef ~OSI_MEMORY~

#include <future>
#include <iostream>

#ifdef _RESUMABLE_FUNCTIONS_SUPPORTED
#include <experimental/resumable>
#endif

#include <unknwn.h>
#include "winrt/coroutine.h"
#include "winrt/Windows.ApplicationModel.Store.h"
#include "winrt/Windows.ApplicationModel.Activation.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Graphics.Display.h"
#include "winrt/Windows.Graphics.Imaging.h"
#include "winrt/Windows.Storage.h"
#include "winrt/Windows.Storage.Streams.h"
#include "winrt/Windows.Storage.AccessCache.h"
#include "winrt/Windows.Storage.Pickers.Provider.h"
#include "winrt/Windows.Storage.Pickers.h"
#include "winrt/Windows.Security.Cryptography.h"
#include "winrt/Windows.Security.ExchangeActiveSyncProvisioning.h"
#include "winrt/Windows.System.h"
#include "winrt/Windows.System.Threading.h"
#include "winrt/Windows.UI.Core.h"
#include "winrt/Windows.UI.Input.h"
#include "winrt/Windows.UI.ViewManagement.h"
#include "winrt/Windows.UI.WindowManagement.h"
#include "winrt/Windows.UI.WindowManagement.Preview.h"
#include "winrt/Windows.UI.Composition.h"
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Automation.Peers.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "winrt/Windows.UI.Xaml.Documents.h"
#include "winrt/Windows.UI.Xaml.Hosting.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "winrt/Windows.UI.Xaml.Media.Imaging.h"
#include "winrt/Windows.UI.Xaml.Navigation.h"
#include "winrt/Windows.UI.Xaml.Shapes.h"
#include "winrt/Windows.Devices.Input.h"
#include "winrt/Windows.Media.Audio.h"
#include <windows.ui.xaml.media.dxinterop.h>

//QUANTUM PORTION

// OpenGL ES includes
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <angle_windowsstore.h>

#include "OpenGLES.h"

//QUANTUM PORTION

// index sequence only
template<std::size_t ...>
struct indexSequence
{ };

template<std::size_t N, std::size_t ... Next>
struct indexSequenceHelper : public indexSequenceHelper<N - 1U, N - 1U, Next...>
{ };

template<std::size_t ... Next>
struct indexSequenceHelper<0U, Next ... >
{
	using type = indexSequence<Next ... >;
};

template<std::size_t N>
using makeIndexSequence = typename indexSequenceHelper<N>::type;

template<typename _Function, typename... Types, std::size_t... I>
auto apply_(_Function&& f, const std::tuple<Types...>& t, indexSequence<I...>)->decltype(std::forward<_Function>(f)(std::get<I>(t)...))
{
	return std::forward<_Function>(f)(std::get<I>(t)...);
}

template<typename _Function, typename... Types>
auto apply(_Function&& f, const std::tuple<Types...>& t)->decltype(apply_(f, t, makeIndexSequence<sizeof...(Types)>()))
{
	return apply_(f, t, makeIndexSequence<sizeof...(Types)>());
}

//Include same headers as before
template<bool b, typename T=void>
using EnableIf = typename std::enable_if<b,T>::type;

template<int Index, template<typename T>class Search, int Which, typename, class First, class... Types>
struct get_internal:
    get_internal<Index + 1, Search, Which, void, Types...>
{};

template<int Index, template<typename T>class Search, int Which, class First, class... Types>
struct get_internal<Index, Search, Which, EnableIf<!Search<First>::value>, First, Types...>:
    get_internal<Index + 1, Search, Which, void, Types...>
{};

template<int Index, template<typename T>class Search, int Which, class First, class... Types>
struct get_internal<Index, Search, Which, EnableIf<Search<First>::value>, First, Types...>:
    get_internal<Index + 1, Search, Which-1, void, Types...>
{};

template<int Index, template<typename T>class Search, class First, class... Types>
struct get_internal<Index, Search, 0, EnableIf<Search<First>::value>, First, Types...>:
    std::integral_constant<int, Index>
{};

template<template<typename>class Test, int Which=0, class... Types>
auto get(std::tuple<Types...>& tuple)->
  decltype(std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple))
{
    return std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple);
}

template<template<typename>class Test, int Which=0, class... Types>
auto get(std::tuple<Types...> const& tuple)->
  decltype(std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple))
{
    return std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple);
}

template<template<typename>class Test, int Which=0, class... Types>
auto get(std::tuple<Types...>&& tuple)->
  decltype(std::move(std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple)))
{
    return std::move(std::tuple_element<get_internal<0,Test,Which,void,Types...>::value>(tuple));
}

template<typename T>
struct is_type {
  template<typename U>
  using test = std::is_same<T,U>;
};

template<class T, int Which=0, class... Types>
T& get(std::tuple<Types...>& tuple)
{
    return get<is_type<T>::template test,Which>(tuple);
}

template<class T, int Which=0, class... Types>
T const& get(std::tuple<Types...> const& tuple)
{
    return get<is_type<T>::template test,Which>(tuple);
}

template<class T, int Which=0, class... Types>
T&& get(std::tuple<Types...>&& tuple)
{
    return std::move(get<is_type<T>::template test,Which>(tuple));
}

   /////////////////////////////////////////////////////////////////////////////////////////
  // a template class for converting a member function of the type _R function(T...args) //
 // to be called 'AnyBinder' as a function object                                       //
/////////////////////////////////////////////////////////////////////////////////////////

#if 1
#define BIND_OVERLOAD 1
#endif

template<typename _Ret, typename _Class, typename... Params>
class mem_fun3_t
{
public:
    explicit mem_fun3_t(_Ret(_Class::* _Pm)(Params... args)) : m_Ptr(_Pm)
    {} //okay here we store the member function pointer for later use

    //this operator call comes from the bind method
    _Ret operator()(_Class *_P, Params... args) const //UNPACK?
		{
        return ((_P->*m_Ptr)(std::forward<Params>(args)...));
		}

private:
    _Ret (_Class::* m_Ptr)(Params...);// method pointer signature
};

//OVERLOAD//
#ifdef BIND_OVERLOAD
template<typename _Ret, typename _Class>
class mem_fun3_t_void
{
public:
	explicit mem_fun3_t_void(_Ret(_Class::* _Pm)(void)) : m_Ptr(_Pm)
	{} //okay here we store the member function pointer for later use

	//this operator call comes from the bind method
	_Ret operator()(_Class *_P) const //UNPACK?
		{
		return ((_P->*m_Ptr)());
		}

private:
	_Ret(_Class::* m_Ptr)(void);// method pointer signature
};

template<typename _Class, typename... Params>
class mem_fun3_t_return_void
{
public:
	explicit mem_fun3_t_return_void(void(_Class::* _Pm)(Params... args)) : m_Ptr(_Pm)
	{} //okay here we store the member function pointer for later use

	//this operator call comes from the bind method
	void operator()(_Class *_P, Params... args) const //UNPACK?
		{
		((_P->*m_Ptr)(std::forward<Params>(args)...));
		}

private:
	void(_Class::* m_Ptr)(Params...);// method pointer signature
};

template<typename _Class>
class mem_fun3_t_return_void_void
{
public:
	explicit mem_fun3_t_return_void_void(void(_Class::* _Pm)(void)) : m_Ptr(_Pm)
	{} //okay here we store the member function pointer for later use

	//this operator call comes from the bind method
	void operator()(_Class *_P) const //UNPACK?
		{
		((_P->*m_Ptr)());
		}

private:
	void(_Class::* m_Ptr)(void); // method pointer signature
};
#endif

template<typename _Ret, typename _Class, typename... Params>
mem_fun3_t<_Ret, _Class, Params...> mem_fun3(_Ret(_Class::* _Pm)(Params... args))
{
	return (mem_fun3_t<_Ret, _Class, Params...>(_Pm));
}

//OVERLOAD//
#ifdef BIND_OVERLOAD
template<typename _Ret, typename _Class>
mem_fun3_t_void<_Ret, _Class> mem_fun3_void(_Ret(_Class::* _Pm)(void))
{
	return (mem_fun3_t_void<_Ret, _Class>(_Pm));
}

template<typename _Class, typename... Params>
mem_fun3_t_return_void<_Class, Params...> mem_fun3_return_void(void(_Class::* _Pm)(Params... args))
{
	return (mem_fun3_t_return_void<_Class, Params...>(_Pm));
}

template<typename _Class>
mem_fun3_t_return_void_void<_Class> mem_fun3_return_void_void(void(_Class::* _Pm)(void))
{
	return (mem_fun3_t_return_void_void<_Class>(_Pm));
}
#endif

template<typename _R, typename _Func, typename _Ptr, typename... Params>
class binder3
{
public:
	//This is the constructor that does the binding part
	binder3(_Func fn, _Ptr ptr, Params... args) : m_ptr(ptr), m_fn(fn) { /*...*/ }

	//and this is the function object 
	_R operator()(Params... args) const
		{
		return m_fn(m_ptr, std::forward<Params>(args)...); //that calls the operator
		}

private:
	_Ptr m_ptr;
	_Func m_fn;
};

//OVERLOAD//
#ifdef BIND_OVERLOAD
template<typename _R, typename _Func, typename _Ptr>
class binder3_void
{
public:
	//This is the constructor that does the binding part
	binder3_void(_Func fn, _Ptr ptr) : m_ptr(ptr), m_fn(fn) { /*...*/ }

	//and this is the function object 
	_R operator()()
		{
		return m_fn(m_ptr); //that calls the operator
		}

private:
	_Ptr m_ptr;
	_Func m_fn;
};

template<typename _Func, typename _Ptr, typename... Params>
class binder3_return_void
{
public:
	//This is the constructor that does the binding part
	binder3_return_void(_Func fn, _Ptr ptr, Params... args) : m_ptr(ptr), m_fn(fn) { /*...*/ }

	//and this is the function object 
	void operator()(Params... args) const
		{
		m_fn(m_ptr, std::forward<Params>(args)...); //that calls the operator
		}

private:
	_Ptr m_ptr;
	_Func m_fn;
};

template<typename _Func, typename _Ptr>
class binder3_return_void_void
{
public:
	//This is the constructor that does the binding part
	binder3_return_void_void(_Func fn, _Ptr ptr) : m_ptr(ptr), m_fn(fn) { /*...*/ }

	//and this is the function object 
	void operator()()
		{
		m_fn(m_ptr); //that calls the operator
		}

private:
	_Ptr m_ptr;
	_Func m_fn;
};
#endif

//a helper function to call binder3
template<typename _R, typename _Class, typename _Func, typename _P1, typename... Params>
binder3<_R, _Func, _P1, Params...> bind3(_R(_Class::* _Pm)(Params...), _Func func, _P1 p1, Params... args)
{
	return binder3<_R, _Func, _P1, Params...>(func, p1, std::forward<Params>(args)...);
}

//OVERLOAD//
#ifdef BIND_OVERLOAD
template<typename _R, typename _Class, typename _Func, typename _P1>
binder3_void<_R, _Func, _P1> bind3_void(_R(_Class::* _Pm)(void), _Func func, _P1 p1)
{
	return binder3_void<_R, _Func, _P1>(func, p1);
}

template<typename _Class, typename _Func, typename _P1, typename... Params>
binder3_return_void<_Func, _P1, Params...> bind3_return_void(void(_Class::* _Pm)(Params...), _Func func, _P1 p1, Params... args)
{
	return binder3_return_void<_Func, _P1, Params...>(func, p1, std::forward<Params>(args)...);
}

template<typename _Class, typename _Func, typename _P1>
binder3_return_void_void<_Func, _P1> bind3_return_void_void(void(_Class::* _Pm)(void), _Func func, _P1 p1)
{
	return binder3_return_void_void<_Func, _P1>(func, p1);
}
#endif

class FuncHolding
{
public:
	FuncHolding() : m_name("Default"), m_AnyTypeName("DefaultType"), m_VOIDCNT(0) { }
	FuncHolding(std::string name, std::string type, int f_VOIDCNT) : m_name(name), m_AnyTypeName(type), m_VOIDCNT(f_VOIDCNT) { }

	virtual std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine) = 0;

	virtual std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine) = 0;

	virtual void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine) = 0;

	virtual std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This) = 0;

	virtual std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This) = 0;

	virtual void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This) = 0;

	int m_VOIDCNT;

	std::string m_name;
	std::string m_AnyTypeName;
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV1 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV1(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV1()
		{
		//...
		}

	  ////////////////////////////
	 //###___Ret[VOID...]___###//
	////////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	// Function return ecoin ecom_base //

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V1_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V1_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV2 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV2(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV2()
		{
		//...
		}

	  ////////////////////////////
	 //###___Ret[VOID...]___###//
	////////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V2_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V2_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV3 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV3(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV3()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V3_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V3_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV4 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV4(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV4()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V4_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V4_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV5 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV5(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV5()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////////
	 //###___void[void...]___###//
	/////////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V5_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V5_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV6 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV6(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV6()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V6_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V6_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV7 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV7(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV7()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V7_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V7_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV8 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV8(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV8()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V8_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V8_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV9 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV9(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV9()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V9_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V9_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV10 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV10(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV10()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V10_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V10_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV11 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV11(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV11()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V11_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V11_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV12 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV12(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV12()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V12_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V12_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV13 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV13(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV13()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V13_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V13_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV14 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV14(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV14()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V14_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V14_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV15 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV15(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV15()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V15_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V15_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV16 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV16(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV16()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V16_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V16_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV17 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV17(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV17()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V17_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V17_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV18 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV18(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV18()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V18_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V18_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV19 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV19(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV19()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V19_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V19_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionVV20 : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionVV20(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionVV20()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecoin::Variable> ac_V20_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar20 = f_CodeLine->m_vec_Variable[20];

		auto vr20 = ag_any_cast<std::tuple_element<19, decltype(storedParams)>::type>(f_CVar20->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19, vr20);
		}

	std::shared_ptr<ecoin::Variable> ac_VX_Var(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V20_RequestVar(f_This, f_CodeLine);
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_VX_Var(f_This, f_CodeLine);
		}
};

#ifdef REFLECT_LAZY_ECOM_OVERLOAD
template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV1 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV1(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV1()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	// Function return ecoin ecom_base //

	std::shared_ptr<ecom_base> ac_V1_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V1_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV2 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV2(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV2()
		{
		//...
		}

	  ////////////////////////////
	 //###___Ret[VOID...]___###//
	////////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V2_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1, vr2);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V2_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV3 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV3(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV3()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V3_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1, vr2, vr3);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V3_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV4 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV4(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV4()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<Params>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V4_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[2];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[3];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1, vr2, vr3, vr4);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V4_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV5 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV5(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV5()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////////
	 //###___void[void...]___###//
	/////////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V5_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1, vr2, vr3, vr4, vr5);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V5_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionEV6 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV6(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV6()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V6_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		return ac_Fire_Continuation_Base(f_This, vr1, vr2, vr3, vr4, vr5, vr6);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V6_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV7 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV7(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV7()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecom_base> ac_Fire_Continuation_Base(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V7_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V7_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV8 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV8(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV8()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V8_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V8_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV9 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV9(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV9()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V9_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V9_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV10 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV10(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV10()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V10_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V10_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV11 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV11(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV11()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V11_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V11_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV12 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV12(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV12()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V12_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V12_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV13 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV13(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV13()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V13_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V13_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV14 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV14(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV14()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecom_base> ac_V14_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V14_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV15 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV15(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV15()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V15_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V15_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV16 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV16(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV16()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V16_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V16_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template <typename _Ret, typename _Class, typename _String, typename... Params>
class LazyFunctionEV17 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV17(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV17()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V17_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V17_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV18 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV18(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV18()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	// Function return ecoin CVar Variable //

	std::shared_ptr<ecom_base> ac_V18_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V18_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV19 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV19(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV19()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecom_base> ac_V19_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V19_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};

template<typename _Class, typename _String, typename... Params>
class LazyFunctionEV20 : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionEV20(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionEV20()
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	template<typename _This, typename... _P>
	std::shared_ptr<ecoin::Variable> ac_Fire_Continuation_Var(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc(std::forward<_P>(pargs)...));
		}

	std::shared_ptr<ecoin::Variable> ac_V20_RequestVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar20 = f_CodeLine->m_vec_Variable[20];

		auto vr20 = ag_any_cast<std::tuple_element<19, decltype(storedParams)>::type>(f_CVar20->m_Var);

		return ac_Fire_Continuation_Var(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19, vr20);
		}

	std::shared_ptr<ecom_base> ac_VX_Base(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return ac_V20_RequestBase(f_This, f_CodeLine);
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//new method
		return ac_VX_Base(f_This, f_CodeLine);
		}
};
#endif

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV1 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV1(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV1()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V1_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		ac_Fire_Continuation_Void(f_This, vr1);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V1_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV2 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV2(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV2()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V2_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[1];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		ac_Fire_Continuation_Void(f_This, vr1, vr2);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V2_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV3 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV3(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV3()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V3_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[1];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[2];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V3_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV4 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV4(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV4()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[VOID...]___###//

	 /////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V4_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[1];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[2];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[3];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V4_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV5 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV5(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV5()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////////
	 //###___void[void...]___###//
	/////////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V5_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[1];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[2];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[3];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[4];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5);
		}

	std::shared_ptr<ecom_base> ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V5_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV6 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV6(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV6()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3_return_void(m_Ptr, mem_fun3_return_void(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V6_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[0];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[1];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[2];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[3];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[4];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[5];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V6_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV7 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV7(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV7()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V7_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V7_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV8 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV8(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV8()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V8_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V8_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV9 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV9(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV9()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V9_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V9_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV10 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV10(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV10()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V10_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V10_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV11 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV11(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV11()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V11_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V11_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV12 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV12(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV12()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V12_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V12_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV13 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV13(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(ecom_base::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV13()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	std::shared_ptr<ecom_base> ac_V13_RequestBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V13_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV14 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV14(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV14()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V14_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V14_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV15 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV15(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV15()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V15_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V15_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV16 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV16(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV16()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V16_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V16_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV17 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV17(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV17()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V17_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V17_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV18 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV18(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV18()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V18_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V18_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV19 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV19(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV19()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V19_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V19_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String, typename... Params>
class LazyFunctionRV20 : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(Params...); // method pointer signature
	std::tuple<Params...> storedParams;

public:
	LazyFunctionRV20(_String name, int f_VOIDCNT, void(_Class::* _Pm)(Params...), Params... args) : m_Ptr(_Pm), storedParams(std::move(args)...), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)f_VOIDCNT)
		{
		//...
		}

	~LazyFunctionRV20()
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  /////////////////////////
	 //###___Ret[void]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  //////////////////////////
	 //###___void[void]___###//
	//////////////////////////

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	template<typename _This, typename... _P>
	void ac_Fire_Continuation_Void(_This f_This, _P... pargs)
		{
		auto f_FastMemFunc = bind3(m_Ptr, mem_fun3(m_Ptr), f_This.get(), std::forward<_P>(pargs)...);

		f_FastMemFunc(std::forward<_P>(pargs)...);
		}

	void ac_V20_Request(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		std::shared_ptr<ecoin::Variable> f_CVar1 = f_CodeLine->m_vec_Variable[1];

		auto vr1 = ag_any_cast<std::tuple_element<0, decltype(storedParams)>::type>(f_CVar1->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar2 = f_CodeLine->m_vec_Variable[2];

		auto vr2 = ag_any_cast<std::tuple_element<1, decltype(storedParams)>::type>(f_CVar2->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar3 = f_CodeLine->m_vec_Variable[3];

		auto vr3 = ag_any_cast<std::tuple_element<2, decltype(storedParams)>::type>(f_CVar3->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar4 = f_CodeLine->m_vec_Variable[4];

		auto vr4 = ag_any_cast<std::tuple_element<3, decltype(storedParams)>::type>(f_CVar4->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar5 = f_CodeLine->m_vec_Variable[5];

		auto vr5 = ag_any_cast<std::tuple_element<4, decltype(storedParams)>::type>(f_CVar5->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar6 = f_CodeLine->m_vec_Variable[6];

		auto vr6 = ag_any_cast<std::tuple_element<5, decltype(storedParams)>::type>(f_CVar6->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar7 = f_CodeLine->m_vec_Variable[7];

		auto vr7 = ag_any_cast<std::tuple_element<6, decltype(storedParams)>::type>(f_CVar7->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar8 = f_CodeLine->m_vec_Variable[8];

		auto vr8 = ag_any_cast<std::tuple_element<7, decltype(storedParams)>::type>(f_CVar8->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar9 = f_CodeLine->m_vec_Variable[9];

		auto vr9 = ag_any_cast<std::tuple_element<8, decltype(storedParams)>::type>(f_CVar9->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar10 = f_CodeLine->m_vec_Variable[10];

		auto vr10 = ag_any_cast<std::tuple_element<9, decltype(storedParams)>::type>(f_CVar10->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar11 = f_CodeLine->m_vec_Variable[11];

		auto vr11 = ag_any_cast<std::tuple_element<10, decltype(storedParams)>::type>(f_CVar11->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar12 = f_CodeLine->m_vec_Variable[12];

		auto vr12 = ag_any_cast<std::tuple_element<11, decltype(storedParams)>::type>(f_CVar12->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar13 = f_CodeLine->m_vec_Variable[13];

		auto vr13 = ag_any_cast<std::tuple_element<12, decltype(storedParams)>::type>(f_CVar13->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar14 = f_CodeLine->m_vec_Variable[14];

		auto vr14 = ag_any_cast<std::tuple_element<13, decltype(storedParams)>::type>(f_CVar14->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar15 = f_CodeLine->m_vec_Variable[15];

		auto vr15 = ag_any_cast<std::tuple_element<14, decltype(storedParams)>::type>(f_CVar15->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar16 = f_CodeLine->m_vec_Variable[16];

		auto vr16 = ag_any_cast<std::tuple_element<15, decltype(storedParams)>::type>(f_CVar16->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar17 = f_CodeLine->m_vec_Variable[17];

		auto vr17 = ag_any_cast<std::tuple_element<16, decltype(storedParams)>::type>(f_CVar17->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar18 = f_CodeLine->m_vec_Variable[18];

		auto vr18 = ag_any_cast<std::tuple_element<17, decltype(storedParams)>::type>(f_CVar18->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar19 = f_CodeLine->m_vec_Variable[19];

		auto vr19 = ag_any_cast<std::tuple_element<18, decltype(storedParams)>::type>(f_CVar19->m_Var);

		std::shared_ptr<ecoin::Variable> f_CVar20 = f_CodeLine->m_vec_Variable[20];

		auto vr20 = ag_any_cast<std::tuple_element<19, decltype(storedParams)>::type>(f_CVar20->m_Var);

		return ac_Fire_Continuation_Void(f_This, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12, vr13, vr14, vr15, vr16, vr17, vr18, vr19, vr20);
		}

	void ac_VX_void(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_V20_Request(f_This, f_CodeLine);
		}

	void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		ac_VX_void(f_This, f_CodeLine);
		}
};

template <typename _Class, typename _String>
class LazyFunctionVV : public FuncHolding
{
private:
	void(_Class::* m_Ptr)(void); // method pointer signature

public:
	LazyFunctionVV(_String name, int f_VOIDCNT, void(_Class::* _Pm)(void)) : m_Ptr(_Pm), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)2)
		{
		//...
		}

	~LazyFunctionVV()
		{
		//...
		}

	  ////////////////////////////
	 //###___Ret[VOID...]___###//
	////////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	  ///////////////////////////
	 //###___[Params...]___###//
	///////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	void ac_VV_Request(std::shared_ptr<ecom_base> f_This)
		{
		auto f_FastMemFunc = bind3_return_void_void(m_Ptr, mem_fun3_return_void_void(m_Ptr), f_This.get());

		f_FastMemFunc();
		}

	//void[VOID]
	void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		ac_VV_Request(f_This);
		}
};

template <typename _Class, typename _String>
class LazyFunctionREV : public FuncHolding
{
private:
	std::shared_ptr<ecom_base>(_Class::* m_Ptr)(void); // method pointer signature

public:
	LazyFunctionREV(_String name, int f_VOIDCNT, std::shared_ptr<ecom_base>(_Class::* _Pm)(void)) : m_Ptr(_Pm), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)1)
		{
		//...
		}

	~LazyFunctionREV()
		{
		//...
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	std::shared_ptr<ecom_base> ac_RV_RequestBase(std::shared_ptr<ecom_base> f_This)
		{
		auto f_FastMemFunc = bind3_void(m_Ptr, mem_fun3_void(m_Ptr), f_This.get());

		return f_FastMemFunc();
		}

	std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return ac_RV_RequestBase(f_This);
		}
};

template <typename _Ret, typename _Class, typename _String>
class LazyFunctionRVV : public FuncHolding
{
private:
	_Ret(_Class::* m_Ptr)(void); // method pointer signature

public:
	LazyFunctionRVV(_String name, int f_VOIDCNT, _Ret(_Class::* _Pm)(void)) : m_Ptr(_Pm), FuncHolding((std::string)name, std::string(typeid(_Pm).name()), (int)1)
		{
		//...
		}

	~LazyFunctionRVV()
		{
		//...
		}

	  /////////////////////////
	 //###___[VOID...]___###//
	/////////////////////////

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBase(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecom_base>();
		}

	/*virtual****/ std::shared_ptr<ecoin::Variable> ac_Call_FuncVar(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, 0);
		}

	/*virtual****/ void ac_Call_FuncVoidPrm(std::shared_ptr<ecom_base> f_This, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
		{
		//...
		}

	/*virtual****/ void ac_Call_FuncVoidVoid(std::shared_ptr<ecom_base> f_This)
		{
		//...
		}

	/*virtual****/ std::shared_ptr<ecom_base> ac_Call_FuncBaseVoid(std::shared_ptr<ecom_base> f_This)
		{
		return std::make_shared<ecom_base>();
		}

	std::shared_ptr<ecoin::Variable> ac_RV_RequestVar(std::shared_ptr<ecom_base> f_This)
		{
		auto f_FastMemFunc = bind3_void(m_Ptr, mem_fun3_void(m_Ptr), f_This.get());

		return std::make_shared<ecoin::Variable>("InvokeCaddy", MuCode::MuCode_Var, f_FastMemFunc());
		}

	std::shared_ptr<ecoin::Variable> ac_Call_FuncVarVoid(std::shared_ptr<ecom_base> f_This)
		{
		return ac_RV_RequestVar(f_This);
		}
};

#ifdef REFLECT_LAZY_ECOM_OVERLOAD
template <typename _Class, typename _String, typename _V1>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1), _V1 f_V1);

template <typename _Class, typename _String, typename _V1, typename _V2>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20);
#endif

template <typename _Ret, typename _Class, typename _String, typename _V1>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1), _V1 f_V1);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19);

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20);

template <typename _Class, typename _String, typename _V1>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1), _V1 f_V1);

template <typename _Class, typename _String, typename _V1, typename _V2>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19);

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20);

#ifdef REFLECT_LAZY_ECOM_OVERLOAD
template <typename _Class, typename _String>
extern void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(void));
#endif

template <typename _Ret, typename _Class, typename _String>
extern void make_lazy(_String f_String, _Ret(_Class::* _Pm)(void));

template <typename _Class, typename _String>
extern void make_lazy(_String f_String, void(_Class::* _Pm)(void));

//###___Fresh and Only___###//

template<class f_A>
extern f_A ag_CheckBoth(f_A f_Input);

extern int ag_CheckInteger(std::string f_InputString);
extern float ag_CheckFloat(std::string f_InputString);

template<class f_A>
extern void ag_FreshOn(std::vector<f_A>& f_AS, int f_IDX, f_A f_Resultance);

template<class f_B>
extern void ag_Freshanon(std::vector<f_B>& f_AS, int f_IDX, f_B f_Resultance);

template<class f_C>
extern f_C ag_FreshOnly(std::vector<f_C>& f_AS, int f_IDX, f_C f_Resultance);

template<class f_D>
extern f_D ag_FreshAndOnly(std::vector<f_D>& f_AS, int f_IDX, f_D f_Resultance);

///###___Main EQ Includes___###///

#include "Code/myBO/icSafeL.h"
#include "Wallet/Wallet.h"
#include "Code/Musion/Variable.h"
#include "Code/ICS/ICS_Target.h"
#include "Code/CLS/Target.h"
#include "Code/Cube/qcom.h"
#include "Code/Cube/predator.h"

using namespace Cube;
using namespace ecoin;

extern void ag_PrepareChar(char* f_Char, int f_ArraySize);
extern void FillChar(char* f_Char, int f_Max);
extern char acFileReadChar(std::string f_Buffer, size_t f_Count);
extern char acFileReadChar(std::string f_Buffer, size_t* f_Count);
extern std::string acBufreadCodeString(std::string f_Buffer, uint* f_CHK);
extern winrt::hstring StrFromChar(char char_str[]);
extern winrt::hstring StrUsingStr(std::string f_string);
extern std::string to_string(const std::wstring& wtxt);
extern std::string to_string(winrt::hstring pstring);
extern std::string to_string(wchar_t* wstring);
extern std::string ag_StrUsingFloat(float f_Float);
extern int StringToWString(std::wstring& ws, const std::string& s);
extern int acBufreadValueInteger(const std::string& f_Buffer, uint* f_Chk);
extern float acBufreadValueFloat(const std::string& f_Buffer, uint* f_Chk);
extern unsigned long long acBufreadValueUL(const std::string& f_Buffer, uint* f_Chk);
extern double acBufreadValueDouble(const std::string& f_Buffer, uint* f_Chk);
extern double acBufreadValueDouble(const std::string& f_Buffer, uint* f_Chk);
extern std::string acBufreadValueString(const std::string& f_Buffer, uint* f_Chk);
extern void acBufwriteValueInteger(std::string* f_Buffer, int f_Int);
extern void acBufwriteValueDouble(std::string* f_Buffer, double f_Double);
extern void acBufwriteValueInt(std::string* f_Buffer, int f_Int);
extern void acBufwriteValueFloat(std::string* f_Buffer, float f_Float);
extern void acBufwriteValueUL(std::string* f_Buffer, unsigned long long f_LongLong);

extern float ag_Unsign(float f_Input);

extern bool g_KeepShare;
extern int g_Found_Share;
extern int g_Found_Block;
extern int g_Found_Msg;
extern int g_CoolDown;
extern float g_CoolBoost;
extern int g_PEERCNT;
extern int g_SHARECNT;
extern bool g_Editor_ON;
extern std::vector<std::vector<std::string>> g_CopyStack;
extern int g_CopyStackPageN;
extern float g_BoardPushHeightAdjust;
extern float g_ComPositionToPoint2fFactor;
extern float g_ComICOPositionToComPositionX;
extern float g_ComICOPositionToComPositionY;
extern float g_CarriageReturnX;
extern bool g_TXD_Scan;
extern int g_OCSCP_ThreadCount;
extern int g_Engine_ThreadCount;
extern int g_Divine_ThreadCount;
extern bool g_ConnectedECD;
extern std::vector<std::shared_ptr<Ackent>> g_Ackent;
extern float g_LowtonMark;
extern int g_OCSCP_LowtonMark;
extern std::shared_ptr<Cube::CubeHESH> g_Lowton;
extern std::shared_ptr<Cube::CubeHASH_originstring> g_LowtonHash;
extern bool g_RenderHesh;
extern bool g_LowtonOn;
extern std::string g_Found_Text;
extern int g_espo_ShareOffset;
extern int g_espo_Peer;
extern float g_espo_Score;
extern float g_espo_Amount;
extern float g_espo_ECN_Amount;
extern std::string g_espo_Owner;
extern std::string g_espo_Date;
extern int g_CurrentComID;
extern float g_CurrentSharePrice;
extern int g_CurrentShareID;
extern bool g_Once;
extern int g_ShareCount;
extern int g_CurrentShareOffset;
extern int g_CurrentShareOffsetMAX;
extern int g_PEER;
extern int g_PEERMAX;
extern int g_EventOffset;
extern int g_GUItimer;
extern int g_SaveComplete_ThreadCount;
extern int g_Diviner_ThreadCount;
extern bool g_BoughtCom;
extern bool g_MyOwnCom;
extern float g_TimeDiff;

  /////////////////////////////////////////
 // Main Reflection Function Invoke Var //
/////////////////////////////////////////

template<typename _R, typename _FuncString, typename... T>
std::shared_ptr<ecoin::Variable> ecom_base::ac_Invoke_Varet(_R f_ReturnTyper, _FuncString f_Map_Function, T... args)
{
	std::shared_ptr<ecoin::Variable> f_ReturnVar = nullptr;

#if 0
	std::function<_R(T...)> f_OrdinaryMemFunc = std::bind(ag_any_cast<std::function<_R(ecom_base::*)(T...)>>((boost::any)f_Map_Function), (std::shared_ptr<ecom_base>)this, std::forward<T>(args)...);

	_R f_Return = f_OrdinaryMemFunc(std::forward<T>(args)...);
#else
	auto f1 = ag_any_cast<_R(ecom_base::* )(T...)>(g_Map_Function[f_Map_Function]);

	auto f_FastMemFunc = bind3(f1, mem_fun3(f1), this, std::forward<T>(args)...);

	_R f_Return = f_FastMemFunc(std::forward<T>(args)...);
#endif

	f_ReturnVar->m_Var = f_Return;

	return f_ReturnVar;
}

template<typename... T>
void ecom_base::ac_Invoke_void_function(std::string f_Map_Function, T... args)
{
	auto f1 = ag_any_cast<void(ecom_base::* /**/)(T...)>((boost::any)f_Map_Function);

	auto f_FastMemFunc = bind3(f1, mem_fun3(f1), this, std::forward<T>(args)...);

	f_FastMemFunc(std::forward<T>(args)...);
}

//typedef std::function<int(int, int)> OrdinaryFunc;

//A a;
//OrdinaryFunc ofunc = std::bind(&A::MemberFunc, a, std::placeholders::_1, std::placeholders::_2);

template<typename... T>
std::shared_ptr<ecom_base> ecom_base::ac_Invoke(std::string f_Map_Function, T... args)
{
	auto f1 = ag_any_cast<std::shared_ptr<ecom_base>(ecom_base::* )(T...)>((boost::any)f_Map_Function);

	auto f_FastMemFunc = bind3(f1, mem_fun3(f1), this, std::forward<T>(args)...);

	return f_FastMemFunc(std::forward<T>(args)...);
}

//QUANTUM PORTION

#include "qam.h"
#include "base58.h"

#include "SimpleRenderer.h"

#include "Include/Cube.h"
#include "Code/Cube/VoxelGrid.h"

#include "Contract.h"
#include "Schedular.h"

#define UN_MOUSE_SPIN_MOUSE 0
#define UN_MOUSE_PUSH_MOUSE 1
#define UN_MOUSE_PUSH_KEY 2
#define UN_MOUSE_SPIN_KEY 3

#define UN_MOUSE_IN 1
#define UN_MOUSE_IN_RIGHT 2
#define UN_MOUSE_IN_LEFT 3
#define UN_MOUSE_RIGHT 4
#define UN_MOUSE_LEFT 5
#define UN_MOUSE_OUT 6
#define UN_MOUSE_OUT_RIGHT 7
#define UN_MOUSE_OUT_LEFT 8

#define QNOMPLAYER 5

#define QTEAM_P0 0
#define QTEAM_P1 1

#if 1
#define QTEAM_CAP true
#define QTEAM_SIZE 2
#else
#define QTEAM_CAP false
#endif

#if 1
#define QAGE_SOUND 1
#endif

#if 1
#define QAGE_VOXELS 1
#endif

using namespace Quantum_Angel;

#define _Longlong long long

#define SPEED_OF_LIGHT 50.5f

extern bool ag_GetKey(int f_Key);

extern void ag_Calc_Light(Cube::BiVector f_CalcPos);

extern void ChangeLevel(float f_X, float f_Y, float f_Z);

extern bool acSpawnAvatar(int f_Index, int f_CharID, int f_BDataID, int f_Team, QpoVec3d f_Position, int f_BoneStructure, int f_SpawnPnt, bool level = true);

extern int g_Width;
extern int g_Height;

extern bool klmem_a_dwn[QNOMPLAYER];
extern bool klmem_d_dwn[QNOMPLAYER];
extern bool klmem_w_dwn[QNOMPLAYER];
extern bool klmem_s_dwn[QNOMPLAYER];

extern bool klpress_a_dwn[QNOMPLAYER];
extern bool klpress_d_dwn[QNOMPLAYER];
extern bool klpress_w_dwn[QNOMPLAYER];
extern bool klpress_s_dwn[QNOMPLAYER];

extern bool klpress_a_pul[QNOMPLAYER];
extern bool klpress_d_pul[QNOMPLAYER];
extern bool klpress_w_pul[QNOMPLAYER];
extern bool klpress_s_pul[QNOMPLAYER];

extern int kldirection[QNOMPLAYER];

extern int g_MouseMode[QNOMPLAYER];

extern float g_LevelFactor;

extern float g_Zoom;
extern float g_ZoomFactor;

extern float g_ArenaSize;

extern bool g_FirstStack[QNOMPLAYER];

extern bool m_ButtonDown[QNOMPLAYER][50];

extern int g_Player;
extern int g_PlayerNom;

extern std::vector<int> g_StreamGuide;

extern bool g_UploadedChar;

extern int g_qa_Radar;
extern int g_qa_ClientTime;
extern int g_qa_FrameRateLimiter;

extern int g_QamSpawnInsertCharacterSelect;
extern int g_QamSpawnInsertCharacterDiscovery;

extern int g_QamSpawnInsertCharacterTeam;

extern int g_QamSpawnInsertCharacterBoostHealth;
extern int g_QamSpawnInsertCharacterBoostCon;
extern int g_QamSpawnInsertCharacterBoostDamage;
extern int g_QamSpawnInsertCharacterBoostFocus;
extern int g_QamSpawnInsertCharacterBoostJink;

extern int g_QamSpawnInsertCharacterBoostIndex;

extern bool m_OpenReturn;

extern bool g_AI_ON;
extern bool g_Editor_ON;

extern std::vector<std::string> g_StructureAString;

extern int g_ID;
extern std::shared_mutex g_UpdatingMuti;

extern bool g_Activate;

extern std::string g_FilePath;

extern winrt::Windows::Storage::StorageFile g_File;

extern std::vector<int> g_vec_Cube;

extern float g_Spin;

extern int g_CollideFlagX;
extern int g_CollideFlagZ;

extern Cube::BiVector g_Position;

extern int g_GridX[4];
extern int g_GridY[4];
extern int g_GridZ[4];

extern int g_PlayerShowEnemyIdx;

extern std::vector<Cube::BiVector> g_vec_Spawn;

extern int g_SoundLod;

extern bool g_LoggedOn;
extern bool g_FailedLoggedOn;

extern int g_StreamIndex;

extern bool g_GameLoader;
extern bool g_GameRender;

extern float g_TX;

extern bool g_FileReady;

extern bool g_GameOpen;

extern bool g_Qy[1024];
extern std::vector<int> g_vec_Qy;

//Insert Placement
extern int g_PlaceScale;
extern float g_PlaceInsertPosInc;
extern float g_PlaceInsertAngInc;

extern float g_PlaceInsertX;
extern float g_PlaceInsertY;
extern float g_PlaceInsertZ;

extern float g_PlaceInsertXrot;
extern float g_PlaceInsertYrot;
extern float g_PlaceInsertZrot;

extern bool g_TerrainUpdate;

extern int g_PlaceInsertCharID;

//Terrain Insert
extern int g_TerrainInsertScale;
extern int g_TerrainInsertFillX;
extern int g_TerrainInsertFillY;
extern int g_TerrainInsertFillZ;
extern int g_TerrainInsertMoveX;
extern int g_TerrainInsertMoveY;
extern int g_TerrainInsertMoveZ;
extern int g_TerrainInsertNegatedX;
extern int g_TerrainInsertNegatedY;
extern int g_TerrainInsertNegatedZ;
extern int g_TerrainInsertMaxX;
extern int g_TerrainInsertMaxY;
extern int g_TerrainInsertMaxZ;
extern int g_TerrainInsertFillXres;
extern int g_TerrainInsertFillYres;
extern int g_TerrainInsertFillZres;
extern int g_TerrainInsertMoveXres;
extern int g_TerrainInsertMoveYres;
extern int g_TerrainInsertMoveZres;
extern int g_TerrainInsertNegatedXres;
extern int g_TerrainInsertNegatedYres;
extern int g_TerrainInsertNegatedZres;
extern int g_TerrainInsertMaxXres;
extern int g_TerrainInsertMaxYres;
extern int g_TerrainInsertMaxZres;

extern int g_TerrainInsertUpdateMode;

extern float g_Sp;

#ifdef QAGE_SOUND
extern bool g_Complete;
extern int g_Exists;
extern bool g_Loaded;
extern bool g_Copied;
extern int g_SoundDelay;

#define ECOIN_MAX_SOUND 175

extern QpoSoundPtr g_Stream[ECOIN_MAX_SOUND];
extern WAVEFORMATEX* g_StreamWaveForm[ECOIN_MAX_SOUND];
extern unsigned int g_StreamLength[ECOIN_MAX_SOUND];

extern std::vector<std::shared_ptr<SoundEffect>> g_vec_ActiveSoundEffects;
#endif

extern int g_starttime;
extern int g_curfps;
extern int g_frame_count;

extern int gui_InsertType;
extern int g_Spawn_Finger;

extern std::string g_QA_Username;
extern std::string g_QA_Password;

extern bool g_Un;
extern unsigned char* g_Unn;

extern std::vector<int> g_vec_Qy_ok;

class QINT_InterfaceItem
{
public:
	QINT_InterfaceItem()
		{
		m_Time = 0.0f;
		m_TimeProgression = 1.5f;
		m_TimeLimit = 30.0f;
		};
	~QINT_InterfaceItem() {};

	winrt::hstring m_Text;

	bool m_FadeIn;
	bool m_FadeOut;
	bool m_Flash;
	float m_FlashRed;
	float m_Red;
	float m_FlashGreen;
	float m_Green;
	float m_FlashBlue;
	float m_Blue;
	float m_FlashAlpha;
	float m_Alpha;

	float m_X;
	float m_Y;
	float m_Z;
	float m_flashX;
	float m_flashY;
	float m_flashZ;
	float m_fadeX;
	float m_fadeY;
	float m_fadeZ;

	float m_Time;
	float m_TimeProgression;
	float m_TimeLimit;
};

  /////////////////////////////////
 // Reflect 'Any' Class or type //
/////////////////////////////////
#if 0
template<typename _MT>
class ecoin_Variable
{
public:

	_MT 
};

template<typename _T>
class Reflection_Caddy : public ecom_base
{
public:
	_T m_IN;

	Reflection_Caddy(_T f_IN) : m_IN(f_IN)
		{
		//...
		}

	_T acResult(void)
		{
		return m_IN;
		}
};

#if 1
void ag_Playground(void)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "ag_PlaygroundRule()";

	BiVector f_BiVector(0.0f);

	std::shared_ptr<Reflection_Caddy> f_Caddy<BiVector>(f_BiVector);
	
	//= std::make_shared_reflect<Reflection_Caddy>(f_BiVector);
}
#endif
#endif

extern std::vector<QINT_InterfaceItem*> g_vec_QINT_Input;
extern std::vector<QINT_InterfaceItem*> g_vec_QINT_Control;
extern std::vector<QINT_InterfaceItem*> g_vec_QINT_Output;

#define MAIN_RENDER_THREAD_ID -1
#define ENGINE_MANAGER_THREAD_ID -2

extern EGLSurface g_RenderSurface;
extern angle::OpenGLES g_OpenGLES;

extern std::shared_mutex g_OGL_Muti;
extern int g_Current_ThreadID;

void ag_Lock_OpenGL(int f_ThreadID);
void ag_UnLock_OpenGL(int f_ThreadID);

#include "MathHelper.h"