//****************************************************************************//
// hardwaremodel.h                                                         //
// Copyright (C) 2004 Desmecht Laurent                                        //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_HARDWAREMODEL_H
#define CAL_HARDWAREMODEL_H


#include "cal3d/global.h"
#include "cal3d/coresubmesh.h"


class QunCoreModel;
class QunSkeleton;
class QunCoreMaterial;


class CAL3D_API QunHardwareModel
{
public:
  struct QunHardwareMesh
  {
    std::vector<int> m_vectorBonesIndices;
    
    int baseVertexIndex;
    int vertexCount;
    int startIndex;
    int faceCount;
    QunCoreMaterial *pCoreMaterial;

    int meshId,submeshId;
  };

public:
  QunHardwareModel(QunCoreModel* pCoreModel);
  ~QunHardwareModel() { }
  
  void setVertexBuffer( char * pVertexBuffer, int stride); 
  void setIndexBuffer( QunIndex * pIndexBuffer); 
  void setNormalBuffer( char * pNormalBuffer, int stride); 
  void setWeightBuffer( char * pWeightBuffer, int stride); 
  void setMatrixIndexBuffer( char * pMatrixIndexBuffer, int stride); 
  void setTextureCoordNum(int textureCoordNum);
  void setTextureCoordBuffer(int mapId, char * pTextureCoordBuffer, int stride);
  void setTangentSpaceBuffer(int mapId, char * pTangentSpaceBuffer, int stride);
  void setCoreMeshIds(const std::vector<int>& coreMeshIds);

  bool load(int baseVertexIndex, int startIndex,int maxBonesPerMesh);
      
  std::vector<QunHardwareMesh> & getVectorHardwareMesh();
  void getAmbientColor(unsigned char *pColorBuffer);
  void getDiffuseColor(unsigned char *pColorBuffer);
  void getSpecularColor(unsigned char *pColorBuffer);
  const QunQuaternion & getRotationBoneSpace(int boneId, QunSkeleton *pSkeleton);
  const QunVector & getTranslationBoneSpace(int boneId, QunSkeleton *pSkeleton);

  float getShininess() const;
  
  int getHardwareMeshCount() const;
  int getFaceCount() const;
  int getVertexCount() const;
  int getBoneCount() const;

  int getBaseVertexIndex() const;
  int getStartIndex() const;

  int getTotalFaceCount() const;
  int getTotalVertexCount() const;

  Qun::UserData getMapUserData(int mapId);
  
  bool selectHardwareMesh(size_t meshId);

  float getLineOffSetX(int i_index) const;

  std::vector<int> m_Line_SetMesh;
  std::vector<float> m_Line_OffSetX;
  std::vector<float> m_Line_OffSetY;
  std::vector<float> m_Line_OffSetZ;

  std::vector<int> m_vectorSetPos;

  std::vector<QunHardwareMesh> m_vectorHardwareMesh;
  
private:
  bool canAddFace(QunHardwareMesh &hardwareMesh, QunCoreSubmesh::Face & face,std::vector<QunCoreSubmesh::Vertex>& vectorVertex, int maxBonesPerMesh);
  int  addVertex(QunHardwareMesh &hardwareMesh, int indice , QunCoreSubmesh *pCoreSubmesh, int maxBonesPerMesh, float i_Xinc = 0, float i_Yinc = 0, float i_Zinc = 0);
  int  addBoneIndice(QunHardwareMesh &hardwareMesh, int Indice, int maxBonesPerMesh);  
    

private:
  
  
  std::vector<QunIndex> m_vectorVertexIndiceUsed;
  int m_selectedHardwareMesh;
  std::vector<int> m_coreMeshIds;
  QunCoreModel *m_pCoreModel;
  
  
  char * m_pVertexBuffer;
  int m_vertexStride;
  char * m_pNormalBuffer;
  int m_normalStride;
  char * m_pWeightBuffer;
  int m_weightStride;
  char * m_pMatrixIndexBuffer;
  int m_matrixIndexStride;
  char * m_pTextureCoordBuffer[8];
  int m_textureCoordStride[8];
  int m_textureCoordNum;  
  char * m_pTangentSpaceBuffer[8];
  int m_tangentSpaceStride[8];
  
  QunIndex * m_pIndexBuffer;

  int m_totalVertexCount;
  int m_totalFaceCount;
};

#endif
