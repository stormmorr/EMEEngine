//****************************************************************************//
// physiquedualquaternion.h                                                   //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_PHYSIQUE_DUAL_QUATERNION_H
#define CAL_PHYSIQUE_DUAL_QUATERNION_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/physique.h"

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

class QunPhysiqueDualQuat : public QunPhysique
{
public:
	QunPhysiqueDualQuat(QunModel* pModel)
		: QunPhysique( pModel ) {}
	
  virtual	int calculateNormals(QunSubmesh *pSubmesh, float *pNormalBuffer, int stride=0);
  virtual	int calculateVertices(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride=0);
  virtual int calculateVerticesAndNormals(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride=0);
  virtual int calculateVerticesNormalsAndTexCoords(QunSubmesh *pSubmesh, float *pVertexBuffer,int NumTexCoords=1);  
};


#endif	// CAL_PHYSIQUE_DUAL_QUATERNION_H

//****************************************************************************//
