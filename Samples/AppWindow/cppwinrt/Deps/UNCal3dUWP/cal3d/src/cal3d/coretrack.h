//****************************************************************************//
// coretrack.h                                                                //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CORETRACK_H
#define CAL_CORETRACK_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/matrix.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class QunCoreBone;
class QunCoreKeyframe;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

//*****************************************************************************/
//** The core track class.
//*****************************************************************************/

class CAL3D_API QunCoreTrack
{
// member variables
protected:
  /// The index of the associated CoreBone in the CoreSkeleton.
  int m_coreBoneId;

// constructors/destructor
public:
  QunCoreTrack();
  virtual ~QunCoreTrack();

  bool create();
  void destroy();

  bool getState(float time, QunVector& translation, QunQuaternion& rotation);

  /// List of keyframes, always sorted by time.
  std::vector<QunCoreKeyframe*> m_keyframes;

  /*****************************************************************************/
  /** Returns the ID of the core bone.
  *
  * This function returns the ID of the core bone to which the core track
  * instance is attached to.
  *
  * @return One of the following values:
  *         \li the \b ID of the core bone
  *         \li \b -1 if an error happend
  *****************************************************************************/
  inline int getCoreBoneId()
  {
	  return m_coreBoneId;
  }

  bool setCoreBoneId(int coreBoneId);
  
  int getCoreKeyframeCount();
  QunCoreKeyframe* getCoreKeyframe(int idx);

  bool addCoreKeyframe(QunCoreKeyframe *pCoreKeyframe);
	void removeCoreKeyFrame(int _i) { m_keyframes.erase( m_keyframes.begin() + _i); }

  void scale(float factor);

private:
  std::vector<QunCoreKeyframe*>::iterator getUpperBound(float time);
};

#endif

//****************************************************************************//
