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
* @file icPhysicsObjectsCreator.h
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "NxVec3.h"
#include "icPhysicsObject.h"

class NxTriangleMesh;
class NxActor;
class icObiTerrainCell;
class icTerrainCell;

class icPhysicsObjectCreator
{

public:

  icPhysicsObjectCreator ();
  virtual ~icPhysicsObjectCreator () {;}

  icPhysicsObjectHandle *createTerrainObject (icObiTerrainCell *cell);
  icPhysicsObjectHandle *createTerrainObject (icTerrainCell *cell);
  icPhysicsObjectHandle *createBoxObject (nvmath::Vec3f size, bool dynamic = false);
  static icPhysicsObjectCreator *instance (); 

private:

  // static instance variable
  static icPhysicsObjectCreator *s_instance;

};