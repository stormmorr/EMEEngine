/*

icPhysics - PhysX Header File
Copyright RageComm/SomptingSOFT/Max Lawlor and Piotr Obrzut (C) 2007
SomptingSOFT Portal www.stss.co.nr

This source is proprietary, and cannot be used, in part or in full without
the express permission of Ragecomm and/or the original author. Ragecomm and
the original author retain the rights to use, modify, and/or relicense this
code without notice.

*/

#pragma once

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include <stdio.h>

#include "nvsg/Face.h"
#include "nvmath/Vec3f.h"
#include "nvsg/nvsg.h"
#include "nvsg/Camera.h"
#include "nvsg/Material.h"
#include "nvsg/TextureImage.h"
#include "nvsg/TextureAttribute.h"
#include "nvsg/PointLight.h"
#include "nvsg/DirectedLight.h"
#include "nvsg/PerspectiveCamera.h"
#include "nvsg/Transform.h"
#include "nvsg/Node.h"
#include "nvsg/Triangles.h"
#include "nvsg/GeoNode.h"
#include "nvsg/FaceAttribute.h"
#include "nvmath/nvmath.h"
#include "nvui/TrackballCameraManipulator.h"
#include "nvsg/StateVariant.h"
#include "nvutil/IOLayer.h"
#include "nvutil/Tools.h"

#include "NxPhysics.h"
#include "NxController.h"
#include "cooking.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "Timing.h"
#include "Stream.h"

#include "nvutil/DbgNew.h" // this must be the last include

//----------------------------------------------------------------------------//
// Defines                                                                    //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// Class Declarations                                                         //
//----------------------------------------------------------------------------//

class icPhysics
{
private:

  UserAllocator*	gMyAllocator;
  ErrorStream		gErrorStream;

  bool			gPause;
  NxPhysicsSDK*	gPhysicsSDK;

  // @@@@@ Not Static
  NxScene*		gScene;

  // @@@@@ Was Static
  NxF32			G;
  NxVec3			gDefaultGravity;
  NxF32			gTimestepMultiplier;
  bool			gApplyGravity;

  // @@@@@ Not Static
  bool gDrawSkinWidth;
  bool gFreeMove;

  bool	gRigidLink;
  bool	gFixedStep;

private:
  NxF32	gSpeedMultiplier;

  NxRay gWorldRay;

  // @@@@@ Not Static
  bool gActive;
  bool firstRun;

public:
  icPhysics();
  virtual ~icPhysics();

  void acInit(void);
  void acInitCCT(void);
  void acCreateScene(void);
  void acReleaseScene(void);
  void acResetScene(void);
  void acNxExit(void);
  void acPassiveMotionCallback(int x, int y);
  void acFrame(void);
  nvmath::Vec3f getGravity () {return nvmath::Vec3f (gDefaultGravity.x, gDefaultGravity.y, gDefaultGravity.z);}

  NxScene* acGetScene(void) const { return gScene; }
  NxPhysicsSDK *getSDK () {return gPhysicsSDK;}	


  static icPhysics* instance(void);

private:
  // static instance variable
  static icPhysics* s_instance;
};