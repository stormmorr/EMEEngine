//****************************************************************************//
// submesh.h                                                                  //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_SUBMESH_H
#define CAL_SUBMESH_H


#include "cal3d/global.h"
#include "cal3d/vector.h"


class QunCoreSubmesh;


class CAL3D_API QunSubmesh
{
public:
  struct PhysicalProperty
  {
    QunVector position;
    QunVector positionOld;
    QunVector force;
  };

  struct TangentSpace
  {
    QunVector tangent;
    float crossFactor;
  };

  struct Face
  {
    QunIndex vertexId[3];
  };

public:
  QunSubmesh(QunCoreSubmesh* coreSubmesh);
  ~QunSubmesh() { }

  QunCoreSubmesh *getCoreSubmesh();
  int getCoreMaterialId() const;
  int getFaceCount() const;
  int getFaces(QunIndex *pFaceBuffer);
  std::vector<QunVector>& getVectorNormal();
  std::vector<std::vector<TangentSpace> >& getVectorVectorTangentSpace();
  std::vector<PhysicalProperty>& getVectorPhysicalProperty();
  std::vector<QunVector>& getVectorVertex();
  std::vector<QunVector>& getVectorVertexn();
  std::vector<Face>& getVectorFace();
  int getVertexCount() const;
  bool hasInternalData() const;
  void disableInternalData();
  void setCoreMaterialId(int coreMaterialId);
  void setLodLevel(float lodLevel);
  bool isTangentsEnabled(int mapId) const;
  bool enableTangents(int mapId, bool enabled);
  std::vector<float>& getVectorWeight();
  void setMorphTargetWeight(int blendId,float weight);
  float getMorphTargetWeight(int blendId) const;
  float getBaseWeight() const;
  int getMorphTargetWeightCount() const;
  std::vector<float>& getVectorMorphTargetWeight();

private:
  QunCoreSubmesh *m_pCoreSubmesh;
  std::vector<float> m_vectorMorphTargetWeight;
  std::vector<QunVector> m_vectorVertex;
  std::vector<QunVector> m_vectorNormal;
  std::vector<std::vector<TangentSpace> > m_vectorvectorTangentSpace;
  std::vector<Face> m_vectorFace;
  std::vector<PhysicalProperty> m_vectorPhysicalProperty;
  int m_vertexCount;
  int m_faceCount;
  int m_coreMaterialId;
  bool m_bInternalData;
};

#endif
