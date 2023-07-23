//****************************************************************************//
// model.h                                                                    //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_MODEL_H
#define CAL_MODEL_H


#include "cal3d/global.h"
#include "cal3d/vector.h"

class QunCoreModel;
class QunSkeleton;
class QunAbstractMixer;
class QunMixer;
class QunMorphTargetMixer;
class QunPhysique;
class QunSpringSystem;
class QunRenderer;
class QunMesh;


class CAL3D_API QunModel : cal3d::noncopyable
{
public: 
  QunModel(QunCoreModel* pCoreModel);
  ~QunModel();

  bool attachMesh(int coreMeshId);
  bool detachMesh(int coreMeshId);
  QunCoreModel *getCoreModel() const;
  QunMesh *getMesh(int coreMeshId) const;
  QunMixer *getMixer() const;
  QunAbstractMixer *getAbstractMixer() const;
  void setAbstractMixer(QunAbstractMixer* pMixer);
  QunMorphTargetMixer *getMorphTargetMixer() const;
  QunPhysique *getPhysique() const;
  void setPhysique( QunPhysique* physique );
  QunRenderer *getRenderer() const;
  QunSkeleton *getSkeleton() const;
  QunSpringSystem *getSpringSystem() const;
  QunBoundingBox & getBoundingBox(bool precision = false);
  Qun::UserData getUserData() const;
  std::vector<QunMesh *>& getVectorMesh();
  void setLodLevel(float lodLevel);
  void setMaterialSet(int setId);
  void setUserData(Qun::UserData userData);
  void update(float deltaTime);
  void disableInternalData();

public:
  QunCoreModel *m_pCoreModel;
  QunSkeleton *m_pSkeleton;
  QunAbstractMixer *m_pMixer;
  QunMorphTargetMixer *m_pMorphTargetMixer;
  QunPhysique *m_pPhysique;
  QunSpringSystem *m_pSpringSystem;
  QunRenderer *m_pRenderer;
  Qun::UserData m_userData;
  std::vector<QunMesh *> m_vectorMesh;
  QunBoundingBox m_boundingBox;
};

#endif

//****************************************************************************//
