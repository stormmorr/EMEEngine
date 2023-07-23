//****************************************************************************//
// skeleton.h                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_SKELETON_H
#define CAL_SKELETON_H

#include "cal3d/global.h"

class QunCoreSkeleton;
class QunCoreModel;
class QunBone;

class CAL3D_API QunSkeleton
{
public:
  QunSkeleton(QunCoreSkeleton* pCoreSkeleton);
  ~QunSkeleton();

  void calculateState();
  void calculateStateTorque();
  void clearState();
  bool create(QunCoreSkeleton *pCoreSkeleton);
  QunBone *getBone(int boneId) const;
  QunCoreSkeleton *getCoreSkeleton() const;
  std::vector<QunBone *>& getVectorBone();
  void lockState();
  void lockStateTorque();
  void getBoneBoundingBox(float *min, float *max);
  void calculateBoundingBoxes();

  // DEBUG-CODE
  int getBonePoints(float *pPoints);
  int getBonePointsStatic(float *pPoints);
  int getBoneLines(float *pLines);
  int getBoneLinesStatic(float *pLines);

  bool m_isBoundingBoxesComputed;

private:
  QunCoreSkeleton *m_pCoreSkeleton;
  std::vector<QunBone *> m_vectorBone;
};

#endif

//****************************************************************************//
