/*

    unMeshAttachment
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unMeshAttachment__
#define __unMeshAttachment__

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//
//*#include "../../DigitalMass/Source/Digi/DigiMass.h"

#if defined(ENABLE_PX_PHYSICS)
using namespace Digi;
#include "../../DigitalMass/Source/Digi/Cloth.h"

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
//#include "PxCooking.h"
#endif

#include "../Utility/datatypes.h"
#include <vector>

#define MAXBONESPERMESH 29

typedef unsigned int GLuint;

//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

class unMeshAttachment
{
public:
	unMeshAttachment() {};
	unMeshAttachment(UInt16 i_Type, UInt16 i_BoneID); // copy constructor
	unMeshAttachment(const unMeshAttachment&) {}; // copy constructor
	virtual ~unMeshAttachment();

	UInt16 m_Type;
	std::vector<UInt16> vec_BoneID;

#if defined(ENABLE_PX_PHYSICS)
	std::vector<DigiCloth*> vec_Cloth;
#endif
};

#endif