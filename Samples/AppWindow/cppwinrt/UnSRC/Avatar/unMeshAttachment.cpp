/*

    unMeshAttachment
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "unMeshAttachment.h"

#if 0
extern PxCookingInterface *digi_Cooking;
extern PxPhysicsSDK *digi_PhysicsSDK;
extern PxScene *digi_Scene;
#endif

//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

unMeshAttachment::unMeshAttachment(UInt16 i_Type, UInt16 i_BoneID)
{
#if defined(ENABLE_PX_PHYSICS)
	vec_Cloth.push_back(DigiMassCore::instance()->acCreateCloth());
	vec_BoneID.push_back(i_BoneID);
#endif
}

unMeshAttachment::~unMeshAttachment()
{
#if defined(ENABLE_PX_PHYSICS)
	vec_Cloth.clear();
	vec_BoneID.clear();
#endif
}