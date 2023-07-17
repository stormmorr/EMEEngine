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
* @file icPhysicsObjectCreator.cpp
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
// NVSG ---------------------- begin
//#include "stdafx.h"
#include "icConstants.h"
#include "icPhysicsObjectCreator.h"
#include "icPhysics.h"

#include <nvmath/nvmath.h>
#include <nvsg/Triangles.h>
#include <nvutil/DbgNew.h>
#include <nvsg/Transform.h>
#include <NxTriangleMeshDesc.h> 
#include <NxActor.h> 

#include "Stream.h"
#include "Terrain/icObiTerrainCell.h"
#include "Terrain/icTerrainCell.h"
#include "icPhysicsObject.h"

#include <string>
#include <iostream>

using namespace nvmath;
using namespace nvsg;
using namespace nvutil;

icPhysicsObjectCreator* icPhysicsObjectCreator::s_instance = 0;

icPhysicsObjectCreator::icPhysicsObjectCreator ()
{
  s_instance = this;
}
icPhysicsObjectHandle *icPhysicsObjectCreator::createBoxObject (nvmath::Vec3f size, bool dynamic)
{
  NxBoxShapeDesc BoxDesc;
  BoxDesc.dimensions = NxVec3(size[0], size[1], size[2]);

  NxActorDesc actorDesc;
  actorDesc.shapes.pushBack(&BoxDesc);
  if (dynamic)
  {
    NxBodyDesc bodyDesc;
    actorDesc.body = &bodyDesc;
  }
  actorDesc.density	= 10.0f;
  NxActor *actor = icPhysics::instance ()->acGetScene ()->createActor(actorDesc);

  icPhysicsObjectHandle *physObjHdl = CreateHandle (icPhysicsObjectHandle);
  WritableObject<icPhysicsObject> (physObjHdl)->setActor (actor);

  return physObjHdl;
}
icPhysicsObjectHandle *icPhysicsObjectCreator::createTerrainObject (icTerrainCell *cell)
{
  NxVec3 *testv = new NxVec3 [cell->getVerticesCount ()];
  NxU32 *testf = new NxU32 [cell->getFacesCount (0) * 3];
  for (size_t i = 0; i < cell->getVerticesCount (); i++)
  {
    testv[i] = NxVec3 (cell->getVertices ()[i][0], cell->getVertices ()[i][1], cell->getVertices ()[i][2]);
  }
  for (size_t i = 0; i < cell->getFacesCount (0); i++)
  {
    testf[i * 3 + 0] = cell->getFaces (0)[i][0];
    testf[i * 3 + 1] = cell->getFaces (0)[i][1];
    testf[i * 3 + 2] = cell->getFaces (0)[i][2];
  }

  NxTriangleMeshDesc terrainDesc;
	terrainDesc.numVertices	= cell->getVerticesCount ();
	terrainDesc.numTriangles = cell->getFacesCount (0);
	terrainDesc.pointStrideBytes = sizeof(NxVec3);
	terrainDesc.triangleStrideBytes	= 3*sizeof(NxU32);;
	terrainDesc.points = testv;
	terrainDesc.triangles	= testf;
	terrainDesc.flags	= 0;

  bool status = InitCooking ();
  if (!status) 
  {
    std::cerr << "Unable to initialize the cooking library. Please make sure that you have correctly" <<  
      "installed the latest version of the AGEIA PhysX SDK." << std::endl;
    return 0;
  }

  MemoryWriteBuffer buf;
	status = CookTriangleMesh (terrainDesc, buf);
	if (!status) 
  {
		std::cerr << "Unable to cook a triangle mesh." << std::endl;
		return 0;
	}
  
  MemoryReadBuffer readBuffer (buf.data);
  NxTriangleMesh *terrainMesh = icPhysics::instance ()->getSDK ()->createTriangleMesh (readBuffer);

  NxTriangleMeshShapeDesc terrainShapeDesc;
	terrainShapeDesc.meshData	= terrainMesh;
	terrainShapeDesc.shapeFlags = NX_SF_FEATURE_INDICES;
  terrainShapeDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;

  NxActorDesc ActorDesc;
	ActorDesc.shapes.pushBack(&terrainShapeDesc);
  
  NxActor *terrainActor = icPhysics::instance ()->acGetScene ()->createActor(ActorDesc);
	terrainActor->userData = (void*)0;

	CloseCooking ();

  delete[] testv;
  delete[] testf;

  icPhysicsObjectHandle *physObjHdl = CreateHandle (icPhysicsObjectHandle);
  WritableObject<icPhysicsObject> (physObjHdl)->setActor (terrainActor);

  return physObjHdl;
}
icPhysicsObjectHandle *icPhysicsObjectCreator::createTerrainObject (icObiTerrainCell *cell)
{
  NxVec3 *testv = new NxVec3 [cell->getVerticesCount ()];
  NxU32 *testf = new NxU32 [cell->getFacesCount (0) * 3];
  for (size_t i = 0; i < cell->getVerticesCount (); i++)
  {
    testv[i] = NxVec3 (cell->getVertices ()[i][0], cell->getVertices ()[i][2], cell->getVertices ()[i][1]);
  }
  for (size_t i = 0; i < cell->getFacesCount (0); i++)
  {
    testf[i * 3 + 0] = cell->getFaces (0)[i][0];
    testf[i * 3 + 1] = cell->getFaces (0)[i][1];
    testf[i * 3 + 2] = cell->getFaces (0)[i][2];
  }

  NxTriangleMeshDesc terrainDesc;
	terrainDesc.numVertices	= cell->getVerticesCount ();
	terrainDesc.numTriangles = cell->getFacesCount (0);
	terrainDesc.pointStrideBytes = sizeof(NxVec3);
	terrainDesc.triangleStrideBytes	= 3*sizeof(NxU32);;
	terrainDesc.points = testv;
	terrainDesc.triangles	= testf;
	terrainDesc.flags	= 0;

  bool status = InitCooking ();
  if (!status) 
  {
    std::cerr << "Unable to initialize the cooking library. Please make sure that you have correctly" <<  
      "installed the latest version of the AGEIA PhysX SDK." << std::endl;
    return 0;
  }

  MemoryWriteBuffer buf;
	status = CookTriangleMesh (terrainDesc, buf);
	if (!status) 
  {
		std::cerr << "Unable to cook a triangle mesh." << std::endl;
		return 0;
	}

  MemoryReadBuffer readBuffer (buf.data);
  NxTriangleMesh *terrainMesh = icPhysics::instance ()->getSDK ()->createTriangleMesh (readBuffer);

  NxTriangleMeshShapeDesc terrainShapeDesc;
	terrainShapeDesc.meshData	= terrainMesh;
	terrainShapeDesc.shapeFlags = NX_SF_FEATURE_INDICES;

  NxActorDesc ActorDesc;
	ActorDesc.shapes.pushBack(&terrainShapeDesc);
  
  NxActor *terrainActor = icPhysics::instance ()->acGetScene ()->createActor(ActorDesc);
	terrainActor->userData = (void*)0;

	CloseCooking ();

  icPhysicsObjectHandle *physObjHdl = CreateHandle (icPhysicsObjectHandle);
  WritableObject<icPhysicsObject> (physObjHdl)->setActor (terrainActor);

  return physObjHdl;
}

icPhysicsObjectCreator *icPhysicsObjectCreator::instance ()
{
  return s_instance;
}

// NVSG ---------------------- end
