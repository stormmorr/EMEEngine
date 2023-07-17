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
* @file icPhysicsObject.h
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
// NVSG ---------------------- begin
#pragma once
#include <nvsg/Group.h>
#include <NxRay.h> 
#include <NxUserRaycastReport.h> 

class icSpeedTreeFactory;
class NxActor;

enum
{
  // Cuboid object code 
  OC_PHYSICS_OBJECT = nvsg::OC_CUSTOMOBJECT + 6
};

// A scene graph node, representing speed tree object
class icPhysicsObject : public nvsg::Group
{
  friend class icPhysicsObjectCreator;

protected:
  NxActor *actor;
  nvsg::TransformHandle *transformHdl;

  void setActor (NxActor *actor);

public:

  icPhysicsObject ();
  virtual ~icPhysicsObject ();
  bool raycast (const NxRay& worldRay, NxReal maxDist, NxU32 hintFlags, NxRaycastHit& hit, bool firstHit) const;
  void showRepresentation (bool show = true);
  virtual void setTransform (nvmath::Trafo transform);
  nvmath::Trafo getTransform () const;
  virtual void update (double time);
  size_t addChild (nvsg::NodeHandle *child, size_t position = 0xFFFFFFFF);
  void replaceChild(nvsg::NodeHandle * newChild, size_t position);
  NxActor *getActor () {return actor;}

  // required to assure a seamless traversal
  unsigned int getHigherLevelObjectCode(unsigned int oc) const;
};

typedef nvutil::Handle<icPhysicsObject, nvsg::GroupHandle> icPhysicsObjectHandle;

// NVSG ---------------------- end

