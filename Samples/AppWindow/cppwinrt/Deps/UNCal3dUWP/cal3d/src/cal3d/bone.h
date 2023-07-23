//****************************************************************************//
// bone.h                                                                     //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_BONE_H
#define CAL_BONE_H


#include "cal3d/global.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"
#include "cal3d/matrix.h"
#include "cal3d/corebone.h"

// NVIDIA Includes
#ifdef ENABLE_PHYSX_RAG
#include "PxMat44.h"
#include "PxVec3.h"

using namespace physx;
#endif

//class QunCoreBone;
class QunSkeleton;
class QunModel;
class QunCoreModel;


class CAL3D_API QunBone
{
public:
  QunBone(QunCoreBone* coreBone);
  ~QunBone() { }

  void blendState(float weight, const QunVector& translation, const QunQuaternion& rotation);
  void blending(float weight, const QunVector& translation, const QunQuaternion& rotation);
  void calculateState();
  void calculateStateTrans();
  void calculateStateTorque();
  void clearState();
  QunCoreBone *getCoreBone();
  void setCoreState();
  void setCoreStateRecursive();
  void setRotation(const QunQuaternion& rotation);
  const QunQuaternion& getRotation() const;
  const QunQuaternion& getRotationAbsolute() const;
  const QunQuaternion& getRotationBoneSpace() const;
  void setTranslation(const QunVector& translation);
#ifdef ENABLE_PHYSX_RAG
  void setTranslationAbsolute(physx::PxVec3 translation, const physx::PxMat33& meshmatrix, const physx::PxMat33& correctmatrix);
#endif
  void setRotationAbs(const QunQuaternion& rotation);
  void setPivotTranslation(const QunVector& translation);
  const QunVector& getTranslation() const;
  const QunVector& getTranslationAbsolute() const;
  const QunVector& getTranslationBoneSpace() const;
  const QunMatrix& getTransformMatrix() const;
  void lockState();
  void setSkeleton(QunSkeleton *pSkeleton);
  void calculateBoundingBox();
  QunBoundingBox & getBoundingBox();

private:
  QunCoreBone *m_pCoreBone;
  QunSkeleton *m_pSkeleton;
  float m_accumulatedWeight;
  float m_accumulatedWeightAbsolute;
  QunVector m_translation;
  QunQuaternion m_rotation;
  QunVector m_translationAbsolute;
  QunQuaternion m_rotationAbsolute;
  QunVector m_translationBoneSpace;
  QunQuaternion m_rotationBoneSpace;
  QunMatrix m_transformMatrix;  
  QunBoundingBox m_boundingBox;
};

#endif

//****************************************************************************//
