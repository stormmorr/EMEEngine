//****************************************************************************//
// mesh.h                                                                     //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_MESH_H
#define CAL_MESH_H


#include "cal3d/global.h"


class QunModel;
class QunCoreMesh;
class QunSubmesh;


class CAL3D_API QunMesh
{
// constructors/destructor
public:
  QunMesh(QunCoreMesh *pCoreMesh);
  ~QunMesh();

  QunCoreMesh *getCoreMesh();
  QunSubmesh *getSubmesh(int id);
  int getSubmeshCount() const;
  std::vector<QunSubmesh *>& getVectorSubmesh();
  void setLodLevel(float lodLevel);
  void setMaterialSet(int setId);
  void setModel(QunModel *pModel);
  void disableInternalData();

private:
  QunModel *m_pModel;
  QunCoreMesh *m_pCoreMesh;
  std::vector<QunSubmesh *> m_vectorSubmesh;
};

#endif

//****************************************************************************//
