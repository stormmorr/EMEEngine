//****************************************************************************//
// corebone.h                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREBONE_H
#define CAL_COREBONE_H


#include "cal3d/global.h"
#include "cal3d/matrix.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"


class QunCoreSkeleton;
class QunCoreModel;


class CAL3D_API QunCoreBone
{
public:
  QunCoreBone(const std::string& name);
  ~QunCoreBone() { }

  bool addChildId(int childId);
  void calculateState();
  std::list<int>& getListChildId();
  const std::string& getName() const;
  void setName( const std::string& name );
  int getParentId() const;
  QunCoreSkeleton *getCoreSkeleton();
  const QunQuaternion& getRotation() const;
  const QunQuaternion& getRotationAbsolute() const;
  const QunQuaternion& getRotationBoneSpace() const;
  const QunVector& getTranslation() const;
  const QunVector& getTranslationAbsolute() const;
  const QunVector& getTranslationBoneSpace() const;
  Qun::UserData getUserData();
  void setCoreSkeleton(QunCoreSkeleton *pCoreSkeleton);
  void setParentId(int parentId);
  void setRotation(const QunQuaternion& rotation);
  void setRotationBoneSpace(const QunQuaternion& rotation);
  void setTranslation(const QunVector& translation);
  void setTranslationBoneSpace(const QunVector& translation);
  void setUserData(Qun::UserData userData);

  void initBoundingBox();
  void calculateBoundingBox(QunCoreModel * pCoreModel);
  QunBoundingBox & getBoundingBox();
  void getBoundingData(int planeId,QunVector & position); 
  bool isBoundingBoxPrecomputed() const;
  void setBoundingBoxPrecomputed( bool inComputed );
  void updateBoundingBox( const QunVector & position );
  void scale(float factor);
  
private:
  std::string m_strName;
  QunCoreSkeleton *m_pCoreSkeleton;
  int m_parentId;
  std::list<int> m_listChildId;
  QunVector m_translation;
  QunQuaternion m_rotation;
  QunVector m_translationAbsolute;
  QunQuaternion m_rotationAbsolute;
  QunVector m_translationBoneSpace;
  QunQuaternion m_rotationBoneSpace;
  Qun::UserData m_userData;

  QunBoundingBox m_boundingBox;
  QunVector m_boundingPosition[6];
  bool m_boundingBoxPrecomputed;
};

#endif

//****************************************************************************//
