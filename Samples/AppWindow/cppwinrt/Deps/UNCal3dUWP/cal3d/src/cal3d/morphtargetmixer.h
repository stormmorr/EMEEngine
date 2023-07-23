//****************************************************************************//
// morphtargetmixer.h                                                         //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_MORPHTARGETMIXER_H
#define CAL_MORPHTARGETMIXER_H


#include "cal3d/global.h"


class QunModel;


class CAL3D_API QunMorphTargetMixer
{
public:
  QunMorphTargetMixer(QunModel* model);
  ~QunMorphTargetMixer() { }

  bool blend(int id, float weight, float delay);
  bool clear(int id, float delay);
  bool copy( const QunMorphTargetMixer& inOther );
  float getCurrentWeight(int id) const;
  float getCurrentWeightBase();
  int getMorphTargetCount() const;
  void update(float deltaTime);

private:
  std::vector<float> m_vectorCurrentWeight;
  std::vector<float> m_vectorEndWeight;
  std::vector<float> m_vectorDuration;
  QunModel *m_pModel;
};

#endif

//****************************************************************************//
