//****************************************************************************//
// coresubmesh.h                                                              //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CORESUBMESH_H
#define CAL_CORESUBMESH_H


#include "cal3d/global.h"
#include "cal3d/vector.h"


class QunCoreSubMorphTarget;


class CAL3D_API QunCoreSubmesh
{
public:
  struct TextureCoordinate
  {
    float u, v;
  };

  struct TangentSpace
  {
    QunVector tangent;
    float crossFactor;  // To get the binormal, use ((N x T) * crossFactor)
  };

  struct Influence
  {
    int boneId;
    float weight;
  };

  struct PhysicalProperty
  {
    float weight;
  };

  struct Vertex
  {
    QunVector position;
    QunVector normal;
    std::vector<Influence> vectorInfluence;
    int collapseId;
    int faceCollapseCount;
  };

  struct Face
  {
    QunIndex vertexId[3];
  };
  
  /// The core submesh Spring.
  struct Spring
  {
    int vertexId[2];
    float springCoefficient;
    float idleLength;
  };

public:
  QunCoreSubmesh();
  ~QunCoreSubmesh();

  int getCoreMaterialThreadId() const;
  int getFaceCount() const;
  int getLodCount() const;
  int getSpringCount() const;
  std::vector<Face>& getVectorFace();
  std::vector<PhysicalProperty>& getVectorPhysicalProperty();
  std::vector<Spring>& getVectorSpring();
  std::vector<std::vector<TangentSpace> >& getVectorVectorTangentSpace();
  std::vector<std::vector<TextureCoordinate> >& getVectorVectorTextureCoordinate();
  std::vector<Vertex>& getVectorVertex();
  int getVertexCount() const;
  bool isTangentsEnabled(int mapId) const;
  bool enableTangents(int mapId, bool enabled);
  bool reserve(int vertexCount, int textureCoordinateCount, int faceCount, int springCount);
  void setCoreMaterialThreadId(int coreMaterialThreadId);
  bool setFace(int faceId, const Face& face);
  void setLodCount(int lodCount);
  bool setPhysicalProperty(int vertexId, const PhysicalProperty& physicalProperty);
  bool setSpring(int springId, const Spring& spring);
  bool setTangentSpace(int vertexId, int textureCoordinateId, const QunVector& tangent, float crossFactor);
  bool setTextureCoordinate(int vertexId, int textureCoordinateId, const TextureCoordinate& textureCoordinate);
  bool setVertex(int vertexId, const Vertex& vertex);
  int addCoreSubMorphTarget(QunCoreSubMorphTarget *pCoreSubMorphTarget);
  QunCoreSubMorphTarget *getCoreSubMorphTarget(int id);
  int getCoreSubMorphTargetCount() const;
  std::vector<QunCoreSubMorphTarget *>& getVectorCoreSubMorphTarget();
  void scale(float factor);

private:
  void UpdateTangentVector(int v0, int v1, int v2, int channel);

private:
  std::vector<Vertex> m_vectorVertex;
  std::vector<bool> m_vectorTangentsEnabled;
  std::vector<std::vector<TangentSpace> > m_vectorvectorTangentSpace;
  std::vector<std::vector<TextureCoordinate> > m_vectorvectorTextureCoordinate;
  std::vector<PhysicalProperty> m_vectorPhysicalProperty;
  std::vector<Face> m_vectorFace;
  std::vector<Spring> m_vectorSpring;
  std::vector<QunCoreSubMorphTarget *> m_vectorCoreSubMorphTarget;
  int m_coreMaterialThreadId;
  int m_lodCount;
};

#endif

//****************************************************************************//
