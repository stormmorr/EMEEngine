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
* @file icCharacterController.h
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "icPhysicsObject.h"

enum
{
  OC_CHARACTER_CONTROLER = nvsg::OC_CUSTOMOBJECT + 15
};

class NxController;
class ControllerManager;

class icCharacterController : public icPhysicsObject
{
  NxController *controller;
  float linVel;
  static ControllerManager gCM;
  float yAngle;

public:

  icCharacterController ();
  virtual ~icCharacterController ();
  void init (float height, float radius);
  virtual void update (double time);
  void setLinearVelocity (float vel);
  static void updateControllers ();
  void setTransform (nvmath::Trafo transform);
  void setYAngle (float angle);
  float &getYAngle () {return yAngle;}

  unsigned int getHigherLevelObjectCode(unsigned int oc) const;
};

typedef nvutil::Handle<icCharacterController, icPhysicsObjectHandle> icCharacterControllerHandle;