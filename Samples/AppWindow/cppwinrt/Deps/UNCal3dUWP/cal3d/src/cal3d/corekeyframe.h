//****************************************************************************//
// corekeyframe.h                                                             //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREKEYFRAME_H
#define CAL_COREKEYFRAME_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/matrix.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The core keyframe class.
  *****************************************************************************/

class CAL3D_API QunCoreKeyframe
{
// member variables
public:
  float m_time;
  QunVector m_translation;
  QunQuaternion m_rotation;

public:
// constructors/destructor
  QunCoreKeyframe();
  virtual ~QunCoreKeyframe();

// member functions
public:
  bool create();
  void destroy();
  const QunQuaternion& getRotation();

  /*****************************************************************************/
  /** Returns the time.
  *
  * This function returns the time of the core keyframe instance.
  *
  * @return The time in seconds.
  *****************************************************************************/
  inline float getTime() const
  {
	  return m_time;
  }

  const QunVector& getTranslation();
  void setRotation(const QunQuaternion& rotation);
  void setTime(float time);
  void setTranslation(const QunVector& translation);
};

#endif

//****************************************************************************//
