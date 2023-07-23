//****************************************************************************//
// saver.h                                                                    //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_SAVER_H
#define CAL_SAVER_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/vector.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class QunCoreModel;
class QunCoreSkeleton;
class QunCoreBone;
class QunCoreAnimation;
class QunCoreMesh;
class QunCoreSubmesh;
class QunCoreMaterial;
class QunCoreKeyframe;
class QunCoreTrack;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The saver class.
  *****************************************************************************/

class QunSaverAnimationOptions {
public:
	bool bCompressKeyframes;

protected:
	QunVector keyframe_min;
	QunVector keyframe_scale;
	float duration;

	friend class QunSaver;
};

class CAL3D_API QunSaver
{
public:
  static bool saveCoreAnimation(const std::string& strFilename, QunCoreAnimation *pCoreAnimation, QunSaverAnimationOptions *pOptions = NULL);
  static bool saveCoreMaterial(const std::string& strFilename, QunCoreMaterial *pCoreMaterial);
  static bool saveCoreMesh(const std::string& strFilename, QunCoreMesh *pCoreMesh);
  static bool saveCoreSkeleton(const std::string& strFilename, QunCoreSkeleton *pCoreSkeleton);

protected:
  static bool saveCoreBones(std::ofstream& file, const std::string& strFilename, QunCoreBone *pCoreBone);
  static bool saveCoreKeyframe(std::ofstream& file, const std::string& strFilename, QunCoreKeyframe *pCoreKeyframe);
  static bool saveCompressedCoreKeyframe(std::ofstream& file, const std::string& strFilename, QunCoreKeyframe *pCoreKeyframe, QunSaverAnimationOptions *pOptions);
  static bool saveCoreSubmesh(std::ofstream& file, const std::string& strFilename, QunCoreSubmesh *pCoreSubmesh);
  static bool saveCoreTrack(std::ofstream& file, const std::string& strFilename, QunCoreTrack *pCoreTrack, QunSaverAnimationOptions *pOptions = NULL);

  static bool saveXmlCoreSkeleton(const std::string& strFilename, QunCoreSkeleton *pCoreSkeleton);
  static bool saveXmlCoreAnimation(const std::string& strFilename, QunCoreAnimation *pCoreAnimation);
  static bool saveXmlCoreMesh(const std::string& strFilename, QunCoreMesh *pCoreMesh);
  static bool saveXmlCoreMaterial(const std::string& strFilename, QunCoreMaterial *pCoreMaterial);  
};

#endif

//****************************************************************************//
