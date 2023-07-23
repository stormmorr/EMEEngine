//****************************************************************************//
// coremodel.h                                                                //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREMODEL_H
#define CAL_COREMODEL_H


#include "cal3d/coreanimation.h"
#include "cal3d/corematerial.h"
#include "cal3d/coremesh.h"
#include "cal3d/coremorphanimation.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/global.h"

class CAL3D_API QunCoreModel
{
public:
  QunCoreModel(const std::string& name);
  QunCoreModel(const QunCoreModel& inOther);
  ~QunCoreModel();

  Qun::UserData getUserData();

  std::vector<int> m_OffSetMesh;
  std::vector<float> m_OffSetX;
  std::vector<float> m_OffSetY;
  std::vector<float> m_OffSetZ;

  void setOffSetMesh(int i_value);

  void setOffSetX(int i_value);
  void setOffSetY(int i_value);
  void setOffSetZ(int i_value);

  void setUserData(Qun::UserData userData);
  const std::string& getName() const;
  void setName( const char* inName );

  void scale(float factor);

  // animations
  int addCoreAnimation(QunCoreAnimation *pCoreAnimation);
  QunCoreAnimation *getCoreAnimation(int coreAnimationId);
  int getCoreAnimationCount() const;
  int loadCoreAnimation(const std::string& strFilename);
  int loadCoreAnimation(const std::string& strFilename, const std::string& strAnimationName);
  int loadCoreAnimation(void* buffer);
  int unloadCoreAnimation(const std::string& name);
  int unloadCoreAnimation(int coreAnimationId);
  bool saveCoreAnimation(const std::string& strFilename, int coreAnimationId);
  bool addAnimationName(const std::string& strAnimationName, int coreAnimationId);
  int getCoreAnimationId(const std::string& strAnimationName);

  // morph animations
  int addCoreMorphAnimation(QunCoreMorphAnimation *pCoreMorphAnimation);
  QunCoreMorphAnimation *getCoreMorphAnimation(int coreMorphAnimationId);
  int getCoreMorphAnimationCount() const;

  // materials
  int addCoreMaterial(QunCoreMaterial *pCoreMaterial);
  void cloneCoreMaterials();
  bool createCoreMaterialThread(int coreMaterialThreadId);
  QunCoreMaterial *getCoreMaterial(int coreMaterialId);
  int getCoreMaterialCount() const;
  int getCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId);
  int loadCoreMaterial(const std::string& strFilename);
  int loadCoreMaterial(const std::string& strFilename, const std::string& strMaterialName);
  int loadCoreMaterial(void* buffer);
  int unloadCoreMaterial(const std::string& name);
  int unloadCoreMaterial(int coreMaterialId);
  bool saveCoreMaterial(const std::string& strFilename, int coreMaterialId);
  bool setCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId);
  bool addMaterialName(const std::string& strMaterialName, int coreMaterialId);
  int getCoreMaterialId(const std::string& strMaterialName);

  // meshes
  int addCoreMesh(QunCoreMesh *pCoreMesh);
  void replaceCoreMesh( int coreMeshId, QunCoreMesh *pCoreMesh );
  QunCoreMesh *getCoreMesh(int coreMeshId);
  int getCoreMeshCount() const;
  int loadCoreMesh(const std::string& strFilename);
  int loadCoreMesh(const std::string& strFilename, const std::string& strMeshName);
  int loadCoreMesh(void* buffer);
  int unloadCoreMesh(const std::string& name);
  int unloadCoreMesh(int coreMeshId);
  bool saveCoreMesh(const std::string& strFilename, int coreMeshId);
  bool addMeshName(const std::string& strMeshName, int coreMeshId);
  int getCoreMeshId(const std::string& strMeshName);

  // skeleton
  QunCoreSkeleton *getCoreSkeleton();
  bool loadCoreSkeleton(const std::string& strFilename);
  bool loadCoreSkeleton(void* buffer);
  bool saveCoreSkeleton(const std::string& strFilename);
  void setCoreSkeleton(QunCoreSkeleton *pCoreSkeleton);
  void addBoneName(const std::string& strBoneName, int boneId);
  int getBoneId(const std::string& strBoneName) const;

// member variables
public:
  std::string m_strName;
  QunCoreSkeletonPtr m_pCoreSkeleton;
  std::vector<QunCoreAnimationPtr> m_vectorCoreAnimation;
  std::vector<QunCoreMorphAnimationPtr> m_vectorCoreMorphAnimation;
  std::vector<QunCoreMeshPtr> m_vectorCoreMesh;
  std::vector<QunCoreMaterialPtr> m_vectorCoreMaterial;
  std::map<int, std::map<int, int> > m_mapmapCoreMaterialThread;
  Qun::UserData m_userData;
  std::map<std::string, int> m_animationName;
  std::map<std::string, int> m_materialName;
  std::map<std::string, int> m_meshName;
};

#endif

//****************************************************************************//
