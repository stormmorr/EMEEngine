//****************************************************************************//
// loader.h                                                                   //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_LOADER_H
#define CAL_LOADER_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//


#include <string>
#include <istream>
#include "cal3d/global.h"
#include "cal3d/datasource.h"
#include "cal3d/coreanimation.h"
#include "cal3d/corematerial.h"
#include "cal3d/coremesh.h"
#include "cal3d/coreskeleton.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class QunCoreModel;
class QunCoreBone;
class QunCoreSubmesh;
class QunCoreKeyframe;

namespace cal3d
{
	class TiXmlDocument;
}

enum
{
    LOADER_ROTATE_X_AXIS = 1,
    LOADER_INVERT_V_COORD = 2,
    LOADER_FLIP_WINDING = 4
};

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The loader class.
  *****************************************************************************/

class CAL3D_API QunLoader
{
// member functions
public:
  static QunCoreAnimationPtr loadCoreAnimation(const std::string& strFilename, QunCoreSkeleton *skel=NULL);
  static QunCoreMaterialPtr  loadCoreMaterial(const std::string& strFilename);
  static QunCoreMeshPtr      loadCoreMesh(const std::string& strFilename);
  static QunCoreSkeletonPtr  loadCoreSkeleton(const std::string& strFilename);

  static QunCoreAnimationPtr loadCoreAnimation(std::istream& inputStream, QunCoreSkeleton *skel=NULL);
  static QunCoreMaterialPtr  loadCoreMaterial(std::istream& inputStream);
  static QunCoreMeshPtr      loadCoreMesh(std::istream& inputStream);
  static QunCoreSkeletonPtr  loadCoreSkeleton(std::istream& inputStream);

  static QunCoreAnimationPtr loadCoreAnimation(void* inputBuffer, QunCoreSkeleton *skel=NULL);
  static QunCoreMaterialPtr  loadCoreMaterial(void* inputBuffer);
  static QunCoreMeshPtr      loadCoreMesh(void* inputBuffer);
  static QunCoreSkeletonPtr  loadCoreSkeleton(void* inputBuffer);

  static QunCoreAnimationPtr loadCoreAnimation(QunDataSource& inputSrc, QunCoreSkeleton *skel=NULL);
  static QunCoreMaterialPtr  loadCoreMaterial(QunDataSource& inputSrc);
  static QunCoreMeshPtr      loadCoreMesh(QunDataSource& inputSrc);
  static QunCoreSkeletonPtr  loadCoreSkeleton(QunDataSource& inputSrc);

  static void setLoadingMode(int flags);

private:
  static QunCoreBone *loadCoreBones(QunDataSource& dataSrc);
  static QunCoreKeyframe *loadCoreKeyframe(QunDataSource& dataSrc);
  static QunCoreKeyframe *loadCompressedCoreKeyframe(QunDataSource& dataSrc, const QunVector &trackMinPt, const QunVector &trackScale, float trackDuration);
  static QunCoreSubmesh *loadCoreSubmesh(QunDataSource& dataSrc);
  static QunCoreTrack *loadCoreTrack(QunDataSource& dataSrc, QunCoreSkeleton *skel, float duration, int flags);

  static QunCoreAnimationPtr loadXmlCoreAnimation(const std::string& strFilename, QunCoreSkeleton *skel=NULL);
  static QunCoreSkeletonPtr loadXmlCoreSkeleton(const std::string& strFilename);
  static QunCoreMeshPtr loadXmlCoreMesh(const std::string& strFilename);
  static QunCoreMaterialPtr loadXmlCoreMaterial(const std::string& strFilename);

  static QunCoreSkeletonPtr loadXmlCoreSkeleton(cal3d::TiXmlDocument& doc);
  static QunCoreMeshPtr loadXmlCoreMesh(cal3d::TiXmlDocument& doc);
  static QunCoreMaterialPtr loadXmlCoreMaterial(cal3d::TiXmlDocument& doc);

  static int loadingMode;
};

#endif

//****************************************************************************//
