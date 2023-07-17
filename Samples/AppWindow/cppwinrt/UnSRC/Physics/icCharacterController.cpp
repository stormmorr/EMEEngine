////////////////////////////////////////////////////////////////////////////////
/**
* Copyright (C) 2007 Ragecomm (http://www.ragecomm.com) and Piotr Obrzut
*
* This source is proprietary, and cannot be used, in part or in full without
* the express permission of Ragecomm and/or the original author. Ragecomm and
* the original author retain the rights to use, modify, and/or relicense this
* code without notice.
*/
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/**
* @file icCharacterController.cpp
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
// NVSG ---------------------- begin
#include "icConstants.h"
#include "icCharacterController.h"
#include "icPhysics.h"
#include <nvsg/Group.h>
#include <nvmath/nvmath.h>
#include <NxActor.h> 
#include <NxBoxShape.h> 
#include <NxCapsuleController.h>
#include "ControllerManager.h"
#include <string>

const NxF32	gInitialRadius = 0.5f;
const NxF32	gInitialHeight = 2.0f;
#define SKINWIDTH	0.1f

using namespace nvmath;
using namespace nvsg;
using namespace nvutil;

ControllerManager icCharacterController::gCM;

icCharacterController::icCharacterController ()
{
  m_objectCode = OC_CHARACTER_CONTROLER;
  linVel = 0.0f;
}
icCharacterController::~icCharacterController ()
{
  gCM.removeController ((Controller*)controller);
}
void icCharacterController::updateControllers ()
{
  gCM.updateControllers ();
}
void icCharacterController::setLinearVelocity (float vel)
{
  linVel = vel;
}

void icCharacterController::setTransform (nvmath::Trafo transform)
{
  WritableObject<Transform> (transformHdl)->setTrafo (transform);
  Vec3f trans = transform.getTranslation ();
  controller->setPosition (NxExtendedVec3(trans[0], trans[1], trans[2]));
  
  //FIXME: requires real calculations
  yAngle = 0.0f;
}
void icCharacterController::update (double time)
{
  NxU32 collisionFlags;
  const NxF32 sharpness = 1.0f;
  
  Vec3f disp = icPhysics::instance ()->getGravity ();
  Quatf rot (Vec3f (0, 1, 0), yAngle);
  actor->setGlobalOrientationQuat (NxQuat (NxVec3 (rot[0], rot[1], rot[2]), rot[3]));

  if (linVel != 0)
  {  
    Vec3f horizontalDisp = (Vec3f (0, 0, 1) * rot) * linVel / 75.0f;
    horizontalDisp[1] = 0.0f;
    disp += horizontalDisp;
  }
  disp *= time;
  //
  controller->move (NxVec3 (disp[0], disp[1], disp[2]), COLLIDABLE_MASK, 0.000001f, collisionFlags, sharpness);
  icPhysicsObject::update (time);
}
void icCharacterController::init (float height, float radius)
{
  NxCapsuleControllerDesc desc;
  desc.interactionFlag	= NXIF_INTERACTION_INCLUDE;
  desc.position.x			= 0;
  desc.position.y			= 0;
  desc.position.z			= 0;
  desc.radius				= radius;
  desc.height				= height;
  desc.upDirection		= NX_Y;
  desc.slopeLimit			= 0.0f;
  desc.slopeLimit			= cosf(NxMath::degToRad(90.0f));
  desc.skinWidth			= SKINWIDTH;
  desc.stepOffset			= gInitialRadius*2.0f;
  controller = (NxCapsuleController*)gCM.createController(icPhysics::instance ()->acGetScene (), desc);
  actor = controller->getActor ();
}
unsigned int icCharacterController::getHigherLevelObjectCode(unsigned int oc) const
{
  return( ( oc == OC_CHARACTER_CONTROLER) ? OC_PHYSICS_OBJECT : OC_INVALID );
}

// NVSG ---------------------- end
