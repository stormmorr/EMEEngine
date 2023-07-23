//****************************************************************************//
// coreanimation.h                                                            //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREANIMATION_H
#define CAL_COREANIMATION_H

#include "cal3d/global.h"
#include "cal3d/quaternion.h"
#include "cal3d/refcounted.h"
#include "cal3d/refptr.h"

struct QunAnimationQunlback;
class QunCoreTrack;

class CAL3D_API QunCoreAnimation : public cal3d::RefCounted
{
public:
  QunCoreAnimation();
  ~QunCoreAnimation();

  bool addCoreTrack(QunCoreTrack *pCoreTrack);
  QunCoreTrack *getCoreTrack(int coreBoneId);

	float getDuration() const;
  void setDuration(float duration);
  void scale(float factor);
  void setFilename(const std::string& filename);
  const std::string& getFilename(void) const;
  void setName(const std::string& name);
  const std::string& getName(void) const;

  void registerQunlback(QunAnimationQunlback *callback,float min_interval);
  void removeQunlback(QunAnimationQunlback *callback);

  unsigned int getTrackCount() const;
  std::list<QunCoreTrack *>& getListCoreTrack();
	unsigned int getTotalNumberOfKeyframes() const;

  struct QunlbackRecord
  {
    QunAnimationQunlback *callback;
    float                 min_interval;
  };

  std::vector<QunlbackRecord>& getQunlbackList() { return m_listQunlbacks; }

  std::list<QunCoreTrack *> m_listCoreTrack;

  std::vector<QunlbackRecord> m_listQunlbacks;

  float m_duration;
  std::string m_name;
  std::string m_filename;
};

typedef cal3d::RefPtr<QunCoreAnimation> QunCoreAnimationPtr;

#endif

//****************************************************************************//
