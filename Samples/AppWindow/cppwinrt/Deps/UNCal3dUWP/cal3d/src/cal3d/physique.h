//****************************************************************************//
// physique.h                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_PHYSIQUE_H
#define CAL_PHYSIQUE_H

#include "cal3d/global.h"


class QunModel;
class QunSubmesh;
class QunVector;


class CAL3D_API QunPhysique
{
public:
  QunPhysique(QunModel* pModel);
  virtual ~QunPhysique() { }

  int calculateTangentSpaces(QunSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer, int stride=0);
  virtual int calculateNormals(QunSubmesh *pSubmesh, float *pNormalBuffer, int stride=0);
  virtual int calculateVertices(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride=0);
  QunVector calculateVertex(QunSubmesh *pSubmesh, int vertexId);
  virtual int calculateVerticesAndNormals(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride=0);
  virtual int calculateVerticesNormalsAndTexCoords(QunSubmesh *pSubmesh, float *pVertexBuffer,int NumTexCoords=1);  
  void update();
  void setNormalization(bool normalize);
  void setAxisFactorX(float factor);
  void setAxisFactorY(float factor);
  void setAxisFactorZ(float factor);

protected:
  QunModel *m_pModel;
  bool m_Normalize;
  float m_axisFactorX;
  float m_axisFactorY;
  float m_axisFactorZ;
};

#endif

//****************************************************************************//
