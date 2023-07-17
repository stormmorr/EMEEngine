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
* @file icPhysicsObject.cpp
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
// NVSG ---------------------- begin
#include "icConstants.h"
#include "icPhysicsObject.h"
#include <nvmath/nvmath.h>
#include <nvsg/Group.h>
#include <nvsg/GeoNode.h>
#include <nvsg/Transform.h>
#include <nvsg/Material.h>
#include <NxActor.h> 
#include <NxBoxShape.h> 
#include <NxCapsuleShape.h> 
#include <string>

#include "Utility/icShapesHelper.h"

using namespace nvmath;
using namespace nvsg;
using namespace nvutil;

icPhysicsObject::icPhysicsObject () : Group ()
{
  m_objectCode = OC_PHYSICS_OBJECT;
  transformHdl = CreateHandle (TransformHandle);
  Group::addChild (transformHdl);
}
icPhysicsObject::~icPhysicsObject ()
{
}
bool icPhysicsObject::raycast (const NxRay& worldRay, NxReal maxDist, NxU32 hintFlags,
                               NxRaycastHit& hit, bool firstHit) const
{
  return actor->getShapes () [0]->raycast (worldRay, maxDist, hintFlags, hit, firstHit);
}
void icPhysicsObject::replaceChild(NodeHandle *newChild, size_t position)
{
  WritableObject<Transform> (transformHdl)->replaceChild (newChild, position);
}
size_t icPhysicsObject::addChild (NodeHandle *child, size_t position)
{
  return WritableObject<Transform> (transformHdl)->addChild (child, position);
}
void icPhysicsObject::update (double time)
{
  Trafo trafo;
  NxVec3 pos = actor->getGlobalPosition ();
  trafo.setTranslation (Vec3f (pos.x, pos.y, pos.z));
  NxQuat rot = actor->getGlobalOrientation ();
  Quatf quat (rot.x, rot.y, rot.z, rot.w);
  quat.normalize ();
  trafo.setOrientation (quat);
  WritableObject<Transform> transform (transformHdl);
  if (transform)
  {
    transform->setTrafo (trafo);
  }
}
void icPhysicsObject::setTransform (Trafo transform)
{
  WritableObject<Transform> (transformHdl)->setTrafo (transform);

  Vec3f pos = transform.getTranslation ();
  actor->setGlobalPosition (NxVec3 (pos[0], pos[1], pos[2]));

  Quatf rot = transform.getOrientation ();
  actor->setGlobalOrientationQuat (NxQuat (NxVec3 (rot[0], rot[1], rot[2]), rot[3]));
}
Trafo icPhysicsObject::getTransform () const
{
  Trafo trans;
  NxVec3 pos = actor->getGlobalPosition ();
  trans.setTranslation (Vec3f (pos.x, pos.y, pos.z));
  NxQuat rot = actor->getGlobalOrientationQuat ();
  trans.setOrientation (Quatf (rot.x, rot.y, rot.z, rot.w));
  return trans;
}
void icPhysicsObject::setActor (NxActor *actor)
{
  icPhysicsObject::actor = actor;
}
void icPhysicsObject::showRepresentation (bool show)
{
  if (show)
  {
    for (NxU32 i = 0; i < actor->getNbShapes (); i++)
    {
      NxShape *shape = actor->getShapes () [i];
      if (shape->isBox ())
      {
        GeoNodeHandle *visRepHdl = CreateHandle (GeoNodeHandle);
        NxBoxShape *boxShape = shape->isBox ();
        NxVec3 size = boxShape->getDimensions () * 2.0f;
        TrianglesHandle *triHdl = icShapesHelper::createBoxGeometry (Vec3f (size.x, size.y, size.z));

        MaterialHandle *materialHdl = CreateHandle(MaterialHandle);
        {
          WritableObject<Material> material (materialHdl);
          material->setAmbientColor (Vec3f (0.f, 0.f, 1.f));
          material->setDiffuseColor (Vec3f (0.9f, 0.4f, 0.4f));
          material->setEmissiveColor (Vec3f (0.f, 0.f, 0.f));
          material->setSpecularColor (Vec3f (1.f, 1.f, 1.f));
          material->setSpecularExponent (10.f);
          material->setOpacity (1.0f);
        }
        StateSetHandle *ssHdl = CreateHandle(StateSetHandle);
        {
          WritableObject<StateSet> ss (ssHdl);
          ss->addAttribute (materialHdl);
        }
        WritableObject<GeoNode> (visRepHdl)->addGeometry (triHdl, ssHdl);
        addChild (visRepHdl);
      }
      else if (shape->isCapsule ())
      {
        GeoNodeHandle *visRepHdl = CreateHandle (GeoNodeHandle);
        NxCapsuleShape *capsuleShape = shape->isCapsule ();
        float radius = capsuleShape->getRadius ();
        float length = capsuleShape->getHeight ();
        TrianglesHandle *triHdl = icShapesHelper::createCapsuleGeometry (length, radius, 10);

        MaterialHandle *materialHdl = CreateHandle(MaterialHandle);
        {
          WritableObject<Material> material (materialHdl);
          material->setAmbientColor (Vec3f (0.f, 0.f, 1.f));
          material->setDiffuseColor (Vec3f (0.9f, 0.4f, 0.4f));
          material->setEmissiveColor (Vec3f (0.f, 0.f, 0.f));
          material->setSpecularColor (Vec3f (1.f, 1.f, 1.f));
          material->setSpecularExponent (10.f);
          material->setOpacity (1.0f);
        }
        StateSetHandle *ssHdl = CreateHandle(StateSetHandle);
        {
          WritableObject<StateSet> ss (ssHdl);
          ss->addAttribute (materialHdl);
        }
        WritableObject<GeoNode> (visRepHdl)->addGeometry (triHdl, ssHdl);
        addChild (visRepHdl);
      }
      
    }
  }
}
unsigned int icPhysicsObject::getHigherLevelObjectCode(unsigned int oc) const
{
  return( ( oc == OC_PHYSICS_OBJECT ) ? OC_GROUP : OC_INVALID );
}

// NVSG ---------------------- end
