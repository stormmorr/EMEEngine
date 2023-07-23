//****************************************************************************//
// loader.cpp                                                                 //
#include "pch.h" // Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/loader.h"
#include "cal3d/error.h"
#include "cal3d/matrix.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"
#include "cal3d/coremodel.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/corebone.h"
#include "cal3d/coreanimation.h"
#include "cal3d/coremesh.h"
#include "cal3d/coresubmesh.h"
#include "cal3d/corematerial.h"
#include "cal3d/corekeyframe.h"
#include "cal3d/coretrack.h"
#include "cal3d/tinyxml.h"
#include "cal3d/streamsource.h"
#include "cal3d/buffersource.h"

//*#include "E:/Projects Base/Unification/UWP/UnSRC/Memory/unSegment.h"
//*#include "E:/Projects Base/Unification/UWP/UnSRC/Memory/unIdentManager.h"

using namespace cal3d;

int QunLoader::loadingMode;

//std::string m_FilePath = "Avatar//";
std::string m_FilePath = "";

 /*****************************************************************************/
/** Sets optional flags which affect how the model is loaded into memory.
  *
  * This function sets the loading mode for all future loader calls.
  *
  * @param flags A boolean OR of any of the following flags
  *         \li LOADER_ROTATE_X_AXIS will rotate the mesh 90 degrees about the X axis,
  *             which has the effect of swapping Y/Z coordinates.
  *         \li LOADER_INVERT_V_COORD will substitute (1-v) for any v texture coordinate
  *             to eliminate the need for texture inversion after export.
  *
  *****************************************************************************/
void QunLoader::setLoadingMode(int flags)
{
    loadingMode = flags;
}

 /*****************************************************************************/
/** Loads a core animation instance.
  *
  * This function loads a core animation instance from a file.
  *
  * @param strFilename The file to load the core animation instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreAnimationPtr QunLoader::loadCoreAnimation(const std::string& strFilename, QunCoreSkeleton *skel)
{
  std::string i_FullFilename = m_FilePath + strFilename;

  if(i_FullFilename.size()>= 3 && _stricmp(i_FullFilename.substr(i_FullFilename.size()-3,3).c_str(),Qun::ANIMATION_XMLFILE_MAGIC)==0)
    return loadXmlCoreAnimation(i_FullFilename, skel);

  // open the file
  std::ifstream file(i_FullFilename.c_str(), std::ios::in | std::ios::binary);

  //make sure it was opened properly
  if(!file)
  {
    QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, i_FullFilename);
    return 0;
  }

  //make a new stream data source and use it to load the animation
  QunStreamSource streamSrc( file );
  
  QunCoreAnimationPtr coreanim = loadCoreAnimation( streamSrc,skel );
  if(coreanim) coreanim->setFilename( i_FullFilename );

  //close the file
  file.close();

  return coreanim;
}

 /*****************************************************************************/
/** Loads a core material instance.
  *
  * This function loads a core material instance from a file.
  *
  * @param strFilename The file to load the core material instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMaterialPtr QunLoader::loadCoreMaterial(const std::string& strFilename)
{
  std::string i_FullFilename = m_FilePath + strFilename;

  if(i_FullFilename.size()>= 3 && _stricmp(i_FullFilename.substr(i_FullFilename.size()-3,3).c_str(),Qun::MATERIAL_XMLFILE_MAGIC)==0)
    return loadXmlCoreMaterial(i_FullFilename);

  // open the file
  std::ifstream file;
  file.open(i_FullFilename.c_str(), std::ios::in | std::ios::binary);

  // make sure it opened properly
  if(!file)
  {
    QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, i_FullFilename);
    return 0;
  }

  //make a new stream data source and use it to load the material
  QunStreamSource streamSrc( file );
  
  QunCoreMaterialPtr coremat = loadCoreMaterial( streamSrc );

  if(coremat) coremat->setFilename( i_FullFilename );

  //close the file
  file.close();

  return coremat;

}

 /*****************************************************************************/
/** Loads a core mesh instance.
  *
  * This function loads a core mesh instance from a file.
  *
  * @param strFilename The file to load the core mesh instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMeshPtr QunLoader::loadCoreMesh(const std::string& strFilename)
{

  if(strFilename.size()>= 3 && _stricmp(strFilename.substr(strFilename.size()-3,3).c_str(),Qun::MESH_XMLFILE_MAGIC)==0)
    return loadXmlCoreMesh(strFilename);

  // open the file
  std::ifstream file;
  file.open(strFilename.c_str(), std::ios::in | std::ios::binary);

  // make sure it opened properly
  if(!file)
  {
    QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, strFilename);
    return 0;
  }

  //make a new stream data source and use it to load the mesh
  QunStreamSource streamSrc( file );
  
  QunCoreMeshPtr coremesh = loadCoreMesh( streamSrc );

  if(coremesh) coremesh->setFilename( strFilename );


  //close the file
  file.close();

  return coremesh;

}

 /*****************************************************************************/
/** Loads a core skeleton instance.
  *
  * This function loads a core skeleton instance from a file.
  *
  * @param strFilename The file to load the core skeleton instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSkeletonPtr QunLoader::loadCoreSkeleton(const std::string& strFilename)
{
  std::string i_FullFilename = m_FilePath + strFilename;

  if(i_FullFilename.size()>= 3 && _stricmp(i_FullFilename.substr(i_FullFilename.size()-3,3).c_str(),Qun::SKELETON_XMLFILE_MAGIC)==0)
    return loadXmlCoreSkeleton(i_FullFilename);

  // open the file
  std::ifstream file;
  file.open(i_FullFilename.c_str(), std::ios::in | std::ios::binary);

  //make sure it opened properly
  if(!file)
  {
    QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, i_FullFilename);
    return 0;
  }

  //make a new stream data source and use it to load the skeleton
  QunStreamSource streamSrc( file );
  
  QunCoreSkeletonPtr coreskeleton = loadCoreSkeleton( streamSrc );

  //close the file
  file.close();

  return coreskeleton;

}


 /*****************************************************************************/
/** Loads a core animation instance.
  *
  * This function loads a core animation instance from an input stream.
  *
  * @param inputStream The stream to load the core animation instance from. This
  *                    stream should be initialized and ready to be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreAnimationPtr QunLoader::loadCoreAnimation(std::istream& inputStream, QunCoreSkeleton *skel )
{
   //Create a new istream data source and pass it on
   QunStreamSource streamSrc(inputStream);
   return loadCoreAnimation(streamSrc, skel);
}

 /*****************************************************************************/
/** Loads a core material instance.
  *
  * This function loads a core material instance from an input stream.
  *
  * @param inputStream The stream to load the core material instance from. This
  *                    stream should be initialized and ready to be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMaterialPtr QunLoader::loadCoreMaterial(std::istream& inputStream)
{
   //Create a new istream data source and pass it on
   QunStreamSource streamSrc(inputStream);
   return loadCoreMaterial(streamSrc);
}

 /*****************************************************************************/
/** Loads a core mesh instance.
  *
  * This function loads a core mesh instance from an input stream.
  *
  * @param inputStream The stream to load the core mesh instance from. This
  *                    stream should be initialized and ready to be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMeshPtr QunLoader::loadCoreMesh(std::istream& inputStream)
{
   //Create a new istream data source and pass it on
   QunStreamSource streamSrc(inputStream);
   return loadCoreMesh(streamSrc);
}

 /*****************************************************************************/
/** Loads a core skeleton instance.
  *
  * This function loads a core skeleton instance from an input stream.
  *
  * @param inputStream The stream to load the core skeleton instance from. This
  *                    stream should be initialized and ready to be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSkeletonPtr QunLoader::loadCoreSkeleton(std::istream& inputStream)
{
   //Create a new istream data source and pass it on
   QunStreamSource streamSrc(inputStream);
   return loadCoreSkeleton(streamSrc);
}




 /*****************************************************************************/
/** Loads a core animation instance.
  *
  * This function loads a core animation instance from a memory buffer.
  *
  * @param inputBuffer The memory buffer to load the core animation instance 
  *                    from. This buffer should be initialized and ready to 
  *                    be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreAnimationPtr QunLoader::loadCoreAnimation(void* inputBuffer, QunCoreSkeleton *skel)
{
   //Create a new buffer data source and pass it on
   QunBufferSource bufferSrc(inputBuffer);
   return loadCoreAnimation(bufferSrc,skel);
}

 /*****************************************************************************/
/** Loads a core material instance.
  *
  * This function loads a core material instance from a memory buffer.
  *
  * @param inputBuffer The memory buffer to load the core material instance 
  *                    from. This buffer should be initialized and ready to 
  *                    be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMaterialPtr QunLoader::loadCoreMaterial(void* inputBuffer)
{
	if ( (memcmp( inputBuffer, "<HEADER", 7 ) == 0) || (memcmp( inputBuffer, "<MATERIAL", 9 ) == 0) )
	{
		cal3d::TiXmlDocument	doc;
		doc.Parse( static_cast<const char*>(inputBuffer) );
		if (doc.Error())
		{
		    QunError::setLastError(QunError::FILE_PARSER_FAILED, __FILE__, __LINE__ );
 		   return 0;
		}
		return loadXmlCoreMaterial( doc );
	}
	
   //Create a new buffer data source and pass it on
   QunBufferSource bufferSrc(inputBuffer);
   return loadCoreMaterial(bufferSrc);
}

 /*****************************************************************************/
/** Loads a core mesh instance.
  *
  * This function loads a core mesh instance from a memory buffer.
  *
  * @param inputBuffer The memory buffer to load the core mesh instance from. 
  *                    This buffer should be initialized and ready to be 
  *                    read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMeshPtr QunLoader::loadCoreMesh(void* inputBuffer)
{
	if ( (memcmp( inputBuffer, "<HEADER", 7 ) == 0) || (memcmp( inputBuffer, "<MESH", 5 ) == 0) )
	{
		TiXmlDocument	doc;
		doc.Parse( static_cast<const char*>(inputBuffer) );
		if (doc.Error())
		{
		    QunError::setLastError(QunError::FILE_PARSER_FAILED, __FILE__, __LINE__ );
 		   return 0;
		}
		return loadXmlCoreMesh( doc );
	}

   //Create a new buffer data source and pass it on
   QunBufferSource bufferSrc(inputBuffer);
   return loadCoreMesh(bufferSrc);
}

 /*****************************************************************************/
/** Loads a core skeleton instance.
  *
  * This function loads a core skeleton instance from a memory buffer.
  *
  * @param inputBuffer The memory buffer to load the core skeleton instance 
  *                    from. This buffer should be initialized and ready to 
  *                    be read from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSkeletonPtr QunLoader::loadCoreSkeleton(void* inputBuffer)
{
	if ( (memcmp( inputBuffer, "<HEADER", 7 ) == 0) || (memcmp( inputBuffer, "<SKELETON", 9 ) == 0) )
	{
		TiXmlDocument	doc;
		doc.Parse( static_cast<const char*>(inputBuffer) );
		if (doc.Error())
		{
		    QunError::setLastError(QunError::FILE_PARSER_FAILED, __FILE__, __LINE__ );
 		   return 0;
		}
		return loadXmlCoreSkeleton( doc );
	}

   //Create a new buffer data source and pass it on
   QunBufferSource bufferSrc(inputBuffer);
   return loadCoreSkeleton(bufferSrc);
}

 /*****************************************************************************/
/** Loads a core animation instance.
  *
  * This function loads a core animation instance from a data source.
  *
  * @param dataSrc The data source to load the core animation instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreAnimationPtr QunLoader::loadCoreAnimation(QunDataSource& dataSrc, QunCoreSkeleton *skel)
{
  // check if this is a valid file
  char magic[4];
  if(!dataSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::ANIMATION_FILE_MAGIC, 4) != 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // check if the version is compatible with the library
  int version;
  if(!dataSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__);
    return 0;
  }

  // allocate a new core animation instance
  QunCoreAnimationPtr pCoreAnimation(new(std::nothrow) QunCoreAnimation);
  if(!pCoreAnimation)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // get the duration of the core animation
  float duration;
  if(!dataSrc.readFloat(duration))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // check for a valid duration
  if(duration <= 0.0f)
  {
    QunError::setLastError(QunError::INVALID_ANIMATION_DURATION, __FILE__, __LINE__);
    return 0;
  }

  // set the duration in the core animation instance
  pCoreAnimation->setDuration(duration);

  // read the number of tracks
  int trackCount;
  if(!dataSrc.readInteger(trackCount) || (trackCount <= 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

	// read flags
	int flags = 0;
	if(version >= LIBRARY_VERSION)
		{
		if(!dataSrc.readInteger(flags))
			{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
			return 0;
			}
		}

  // load all core bones
  int trackId;
  for(trackId = 0; trackId < trackCount; ++trackId)
  {
    // load the core track
    QunCoreTrack *pCoreTrack;
    pCoreTrack = loadCoreTrack(dataSrc, skel, duration, flags);
    if(pCoreTrack == 0)
    {
      QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
      return 0;
    }

    // add the core track to the core animation instance
    pCoreAnimation->addCoreTrack(pCoreTrack);
  }

  return pCoreAnimation;
}

/////// Load UN Animation ///////
#if 0
QunCoreAnimationPtr QunLoader::loadCoreAnimation(QunDataSource& dataSrc, QunCoreSkeleton *skel)
{
	// check if this is a valid file
	char magic[4];
	if(!dataSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::ANIMATION_FILE_MAGIC, 4) != 0))
		{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
		printf("ERROR:::Qun3d file not found\n");
		for(;;) {}
		}

	// check if the version is compatible with the library
	int version;
	if(!dataSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
		{
		QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__);
		printf("ERROR:::Qun3d file not found\n");
		for(;;) {}
		}

	// Create Animation Instance
	UN_CoreAnimation pCoreAnimation;

	const Alloc_CoreTrack alloc_coretrack (m_unSegFrame->m_unSegment.get_segment_manager());
	std::string i_ObjIdent = acIdentGen("UNCoreTrack");
	pCoreAnimation.m_listCoreTrack = m_unSegFrame->m_unSegment.construct<UN_List_CoreTrack>(i_ObjIdent.c_str())(alloc_coretrack);

	// get the duration of the core animation
	float duration;
	if(!dataSrc.readFloat(duration))
		{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
		printf("ERROR:::Qun3d file not found\n");
		for(;;) {}
		}

	// check for a valid duration
	if(duration <= 0.0f)
		{
		QunError::setLastError(QunError::INVALID_ANIMATION_DURATION, __FILE__, __LINE__);
		printf("ERROR:::Qun3d file not found\n");
		for(;;) {}
		}

	// set the duration in the core animation instance
	pCoreAnimation.setDuration(duration);

	// read the number of tracks
	int trackCount;
	if(!dataSrc.readInteger(trackCount) || (trackCount <= 0))
		{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
		printf("ERROR:::Qun3d file not found\n");
		for(;;) {}
		}

	// read flags
	int flags = 0;
	if(version >= LIBRARY_VERSION)
		{
		if(!dataSrc.readInteger(flags))
			{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
			printf("ERROR:::Qun3d file not found\n");
			for(;;) {}
			}
		}

	// load all core bones
	int trackId;
	for(trackId = 0; trackId < trackCount; ++trackId)
		{
		// load the core track
		UN_CoreTrack pCoreTrack;

		pCoreTrack = loadCoreTrack(dataSrc, skel, duration, flags);

		// add the core track to the core animation instance
		pCoreAnimation.addCoreTrack(pCoreTrack);
		}

	return pCoreAnimation;
}
#endif

 /*****************************************************************************/
/** Loads a core material instance.
  *
  * This function loads a core material instance from a data source.
  *
  * @param dataSrc The data source to load the core material instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMaterialPtr QunLoader::loadCoreMaterial(QunDataSource& dataSrc)
{
  // check if this is a valid file
  char magic[4];
  if(!dataSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::MATERIAL_FILE_MAGIC, 4) != 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // check if the version is compatible with the library
  int version;
  if(!dataSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__);
    return 0;
  }

  // allocate a new core material instance
  QunCoreMaterialPtr pCoreMaterial = new(std::nothrow) QunCoreMaterial();
  if(!pCoreMaterial)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // get the ambient color of the core material
  QunCoreMaterial::Color ambientColor;
  dataSrc.readBytes(&ambientColor, sizeof(ambientColor));

  // get the diffuse color of the core material
  QunCoreMaterial::Color diffuseColor;
  dataSrc.readBytes(&diffuseColor, sizeof(diffuseColor));

  // get the specular color of the core material
  QunCoreMaterial::Color specularColor;
  dataSrc.readBytes(&specularColor, sizeof(specularColor));

  // get the shininess factor of the core material
  float shininess;
  dataSrc.readFloat(shininess);

  // check if an error happened
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // set the colors and the shininess
  pCoreMaterial->setAmbientColor(ambientColor);
  pCoreMaterial->setDiffuseColor(diffuseColor);
  pCoreMaterial->setSpecularColor(specularColor);
  pCoreMaterial->setShininess(shininess);

  // read the number of maps
  int mapCount;
  if(!dataSrc.readInteger(mapCount) || (mapCount < 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // reserve memory for all the material data
  if(!pCoreMaterial->reserve(mapCount))
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // load all maps
  int mapId;
  for(mapId = 0; mapId < mapCount; ++mapId)
  {
    QunCoreMaterial::Map map;

    // read the filename of the map
    std::string strName;
    dataSrc.readString(map.strFilename);

    // initialize the user data
    map.userData = 0;

    // check if an error happened
    if(!dataSrc.ok())
    {
      QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
      return 0;
    }

    // set map in the core material instance
    pCoreMaterial->setMap(mapId, map);
  }

  return pCoreMaterial;
}

 /*****************************************************************************/
/** Loads a core mesh instance.
  *
  * This function loads a core mesh instance from a data source.
  *
  * @param dataSrc The data source to load the core mesh instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMeshPtr QunLoader::loadCoreMesh(QunDataSource& dataSrc)
{

  // check if this is a valid file
  char magic[4];
  if(!dataSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::MESH_FILE_MAGIC, 4) != 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // check if the version is compatible with the library
  int version;
  if(!dataSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__);
    return 0;
  }

  // get the number of submeshes
  int submeshCount;
  if(!dataSrc.readInteger(submeshCount))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // allocate a new core mesh instance
  QunCoreMeshPtr pCoreMesh = new(std::nothrow) QunCoreMesh();
  if(!pCoreMesh)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // load all core submeshes
  for(int submeshId = 0; submeshId < submeshCount; ++submeshId)
  {
    // load the core submesh
    QunCoreSubmesh *pCoreSubmesh = loadCoreSubmesh(dataSrc);
    if(pCoreSubmesh == 0)
    {
      return 0;
    }

    // add the core submesh to the core mesh instance
    pCoreMesh->addCoreSubmesh(pCoreSubmesh);
  }

  return pCoreMesh;
}

 /*****************************************************************************/
/** Loads a core skeleton instance.
  *
  * This function loads a core skeleton instance from a data source.
  *
  * @param dataSrc The data source to load the core skeleton instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSkeletonPtr QunLoader::loadCoreSkeleton(QunDataSource& dataSrc)
{

  // check if this is a valid file
  char magic[4];
  if(!dataSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::SKELETON_FILE_MAGIC, 4) != 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // check if the version is compatible with the library
  int version;
  if(!dataSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__);
    return 0;
  }

  // read the number of bones
  int boneCount;
  if(!dataSrc.readInteger(boneCount) || (boneCount <= 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  printf("TRACE:::___BoneCount %i\n", boneCount);

  // allocate a new core skeleton instance
  QunCoreSkeletonPtr pCoreSkeleton = new(std::nothrow) QunCoreSkeleton();
  if(!pCoreSkeleton)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // load all core bones
  for(int boneId = 0; boneId < boneCount; ++boneId)
  {
    // load the core bone
    QunCoreBone *pCoreBone = loadCoreBones(dataSrc);
    if(pCoreBone == 0)
    {
      return 0;
    }

    // set the core skeleton of the core bone instance
    pCoreBone->setCoreSkeleton(pCoreSkeleton.get());

    // add the core bone to the core skeleton instance
    pCoreSkeleton->addCoreBone(pCoreBone);

    // add a core skeleton mapping of the bone's name for quick reference later
    pCoreSkeleton->mapCoreBoneName(boneId, pCoreBone->getName());

  }

  // calculate state of the core skeleton
  pCoreSkeleton->calculateState();

  return pCoreSkeleton;
}

 /*****************************************************************************/
/** Loads a core bone instance.
  *
  * This function loads a core bone instance from a data source.
  *
  * @param dataSrc The data source to load the core bone instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core bone
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreBone *QunLoader::loadCoreBones(QunDataSource& dataSrc)
{
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // read the name of the bone
  std::string strName;
  dataSrc.readString(strName);

  // get the translation of the bone
  float tx, ty, tz;
  dataSrc.readFloat(tx);
  dataSrc.readFloat(ty);
  dataSrc.readFloat(tz);

  // get the rotation of the bone
  float rx, ry, rz, rw;
  dataSrc.readFloat(rx);
  dataSrc.readFloat(ry);
  dataSrc.readFloat(rz);
  dataSrc.readFloat(rw);

  // get the bone space translation of the bone
  float txBoneSpace, tyBoneSpace, tzBoneSpace;
  dataSrc.readFloat(txBoneSpace);
  dataSrc.readFloat(tyBoneSpace);
  dataSrc.readFloat(tzBoneSpace);

  // get the bone space rotation of the bone
  float rxBoneSpace, ryBoneSpace, rzBoneSpace, rwBoneSpace;
  dataSrc.readFloat(rxBoneSpace);
  dataSrc.readFloat(ryBoneSpace);
  dataSrc.readFloat(rzBoneSpace);
  dataSrc.readFloat(rwBoneSpace);

  // get the parent bone id
  int parentId;
  dataSrc.readInteger(parentId);

  QunQuaternion rot(rx,ry,rz,rw);
  QunQuaternion rotbs(rxBoneSpace, ryBoneSpace, rzBoneSpace, rwBoneSpace);
  QunVector trans(tx,ty,tz);

  if (loadingMode & LOADER_ROTATE_X_AXIS)
  {
    if (parentId == -1) // only root bone necessary
    {
      // Root bone must have quaternion rotated
      QunQuaternion x_axis_90(0.7071067811f,0.0f,0.0f,0.7071067811f);
      rot *= x_axis_90;
      // Root bone must have translation rotated also
      trans *= x_axis_90;
    }
  }
  

  // check if an error happened
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // allocate a new core bone instance
  QunCoreBone* pCoreBone = new QunCoreBone(strName);

  // set the parent of the bone
  pCoreBone->setParentId(parentId);

  // set all attributes of the bone
  pCoreBone->setTranslation(trans);
  pCoreBone->setRotation(rot);
  pCoreBone->setTranslationBoneSpace(QunVector(txBoneSpace, tyBoneSpace, tzBoneSpace));
  pCoreBone->setRotationBoneSpace(rotbs);

  // read the number of children
  int childCount;
  if(!dataSrc.readInteger(childCount) || (childCount < 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // load all children ids
  for(; childCount > 0; childCount--)
  {
    int childId;
    if(!dataSrc.readInteger(childId) || (childId < 0))
    {
      QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
      return 0;
    }

    pCoreBone->addChildId(childId);
  }

  return pCoreBone;
}

 /*****************************************************************************/
/** Loads a core keyframe instance.
  *
  * This function loads a core keyframe instance from a data source.
  *
  * @param dataSrc The data source to load the core keyframe instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core keyframe
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreKeyframe* QunLoader::loadCoreKeyframe(QunDataSource& dataSrc)
{
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // get the time of the keyframe
  float time;
  dataSrc.readFloat(time);

  // get the translation of the bone
  float tx, ty, tz;
  dataSrc.readFloat(tx);
  dataSrc.readFloat(ty);
  dataSrc.readFloat(tz);

  // get the rotation of the bone
  float rx, ry, rz, rw;
  dataSrc.readFloat(rx);
  dataSrc.readFloat(ry);
  dataSrc.readFloat(rz);
  dataSrc.readFloat(rw);

  // check if an error happened
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return false;
  }

  // allocate a new core keyframe instance
  QunCoreKeyframe *pCoreKeyframe = new(std::nothrow) QunCoreKeyframe();

  if(pCoreKeyframe == 0)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // create the core keyframe instance
  if(!pCoreKeyframe->create())
  {
    delete pCoreKeyframe;
    return 0;
  }
  // set all attributes of the keyframe
  pCoreKeyframe->setTime(time);
  pCoreKeyframe->setTranslation(QunVector(tx, ty, tz));
  pCoreKeyframe->setRotation(QunQuaternion(rx, ry, rz, rw));

  return pCoreKeyframe;
}

/////// Load UN Keyframe ////////
#if 0
QunCoreKeyframe *QunLoader::loadCoreKeyframe(QunDataSource& dataSrc)
{
	if(!dataSrc.ok())
		{
		dataSrc.setError();
		printf("ERROR::: Qun3d Error\n");
		}

	// get the time of the keyframe
	float time;
	dataSrc.readFloat(time);

	// get the translation of the bone
	float tx, ty, tz;
	dataSrc.readFloat(tx);
	dataSrc.readFloat(ty);
	dataSrc.readFloat(tz);

	// get the rotation of the bone
	float rx, ry, rz, rw;
	dataSrc.readFloat(rx);
	dataSrc.readFloat(ry);
	dataSrc.readFloat(rz);
	dataSrc.readFloat(rw);

	// check if an error happened
	if(!dataSrc.ok())
		{
		dataSrc.setError();
		printf("ERROR::: Qun3d Error\n");
		}

	// allocate a new core keyframe instance
	QunCoreKeyframe pCoreKeyframe;

	// create the core keyframe instance
	if(!pCoreKeyframe.create())
		{
		printf("ERROR::: Qun3d Error\n");
		}

	// set all attributes of the keyframe
	pCoreKeyframe.setTime(time);
	pCoreKeyframe.setTranslation(QunVector(tx, ty, tz));
	pCoreKeyframe.setRotation(QunQuaternion(rx, ry, rz, rw));

	return pCoreKeyframe;
}
#endif
 /*****************************************************************************/
/** Loads a core compressed keyframe instance.
  *
  * This function loads a core compressed keyframe instance from a data source.
  *
  * @param dataSrc The data source to load the core compressed keyframe instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core keyframe
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreKeyframe *QunLoader::loadCompressedCoreKeyframe(QunDataSource& dataSrc, const QunVector& trackMinPt, const QunVector& trackScale, float trackDuration)
{
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // get the time of the keyframe
	unsigned short itime;
  dataSrc.readShort((short&)itime);
	float time = (itime / 65535.0f) * trackDuration;

  // get the translation of the bone
  float tx, ty, tz;

	unsigned pt;
	dataSrc.readInteger((int&)pt);

	unsigned ptx = pt & 0x7ff;
	unsigned pty = (pt >> 11) & 0x7ff;
	unsigned ptz = pt >> 22;

	tx = ptx * trackScale.x + trackMinPt.x;
	ty = pty * trackScale.y + trackMinPt.y;
	tz = ptz * trackScale.z + trackMinPt.z;

  // get the rotation of the bone
	short s0, s1, s2;
	dataSrc.readShort(s0);
	dataSrc.readShort(s1);
	dataSrc.readShort(s2);
	QunQuaternion quat;
	quat.decompress(s0, s1, s2);

  // check if an error happened
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // allocate a new core keyframe instance
  QunCoreKeyframe *pCoreKeyframe = new(std::nothrow) QunCoreKeyframe();

  if(pCoreKeyframe == 0)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  // create the core keyframe instance
  if(!pCoreKeyframe->create())
  {
    delete pCoreKeyframe;
    return 0;
  }
  // set all attributes of the keyframe
  pCoreKeyframe->setTime(time);
  pCoreKeyframe->setTranslation(QunVector(tx, ty, tz));
	pCoreKeyframe->setRotation(quat);

  return pCoreKeyframe;
}

///////// Load UN Keyframe /////////
#if 0
QunCoreKeyframe QunLoader::loadCompressedCoreKeyframe(QunDataSource& dataSrc, const QunVector& trackMinPt, const QunVector& trackScale, float trackDuration)
{
	if(!dataSrc.ok())
		{
		dataSrc.setError();
		printf("ERROR::: Qun3d Error\n");
		}

	// get the time of the keyframe
	unsigned short itime;
	dataSrc.readShort((short&)itime);
	float time = (itime / 65535.0f) * trackDuration;

	  // get the translation of the bone
	float tx, ty, tz;

	unsigned pt;
	dataSrc.readInteger((int&)pt);

	unsigned ptx = pt & 0x7ff;
	unsigned pty = (pt >> 11) & 0x7ff;
	unsigned ptz = pt >> 22;

	tx = ptx * trackScale.x + trackMinPt.x;
	ty = pty * trackScale.y + trackMinPt.y;
	tz = ptz * trackScale.z + trackMinPt.z;

	// get the rotation of the bone
	short s0, s1, s2;
	dataSrc.readShort(s0);
	dataSrc.readShort(s1);
	dataSrc.readShort(s2);
	QunQuaternion quat;
	quat.decompress(s0, s1, s2);

	// check if an error happened
	if(!dataSrc.ok())
		{
		dataSrc.setError();
		printf("ERROR::: Qun3d Error\n");
		}

	// allocate a new core keyframe instance
	QunCoreKeyframe pCoreKeyframe;

	// create the core keyframe instance
	if(!pCoreKeyframe.create())
		{
		printf("ERROR:::Qun3d error\n");
		}

	// set all attributes of the keyframe
	pCoreKeyframe.setTime(time);
	pCoreKeyframe.setTranslation(QunVector(tx, ty, tz));
	pCoreKeyframe.setRotation(quat);

	return pCoreKeyframe;
}
#endif
 /*****************************************************************************/
/** Loads a core submesh instance.
  *
  * This function loads a core submesh instance from a data source.
  *
  * @param dataSrc The data source to load the core submesh instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core submesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSubmesh *QunLoader::loadCoreSubmesh(QunDataSource& dataSrc)
{
#if 0
	if(!dataSrc.ok())
	{
		dataSrc.setError();
		return 0;
	}

	// get the material thread id of the submesh
	int coreMaterialThreadId;
	dataSrc.readInteger(coreMaterialThreadId);

	// get the number of vertices, faces, level-of-details and springs
	int vertexCount;
	dataSrc.readInteger(vertexCount);

	int faceCount;
	dataSrc.readInteger(faceCount);

	int lodCount;
	dataSrc.readInteger(lodCount);

	int springCount;
	dataSrc.readInteger(springCount);

	// get the number of texture coordinates per vertex
	int textureCoordinateCount;
	dataSrc.readInteger(textureCoordinateCount);

	// check if an error happened
	if(!dataSrc.ok())
	{
		dataSrc.setError();
		return 0;
	}

	// allocate a new core submesh instance
	std::auto_ptr<QunCoreSubmesh> pCoreSubmesh( new(std::nothrow) QunCoreSubmesh() );
	if(pCoreSubmesh.get() == 0)
	{
		QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
		return 0;
	}
	
	// set the LOD step count
	pCoreSubmesh->setLodCount(lodCount);

	// set the core material id
	pCoreSubmesh->setCoreMaterialThreadId(coreMaterialThreadId);

	// reserve memory for all the submesh data
	if(!pCoreSubmesh->reserve(vertexCount, textureCoordinateCount, faceCount, springCount))
	{
		QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
		return 0;
	}

	// load the tangent space enable flags.
	int textureCoordinateId;
	for (textureCoordinateId = 0; textureCoordinateId < textureCoordinateCount; textureCoordinateId++)
	{
		pCoreSubmesh->enableTangents(textureCoordinateId, false);
	}

	// load all vertices and their influences
	int vertexId;
	std::vector<QunCoreSubmesh::Vertex>&	vertexVector( pCoreSubmesh->getVectorVertex() );
	for(vertexId = 0; vertexId < vertexCount; ++vertexId)
	{
		QunCoreSubmesh::Vertex& vertex( vertexVector[ vertexId ] );

		// load data of the vertex
		dataSrc.readFloat(vertex.position.x);
		dataSrc.readFloat(vertex.position.y);
		dataSrc.readFloat(vertex.position.z);
		dataSrc.readFloat(vertex.normal.x);
		dataSrc.readFloat(vertex.normal.y);
		dataSrc.readFloat(vertex.normal.z);
		dataSrc.readInteger(vertex.collapseId);
		dataSrc.readInteger(vertex.faceCollapseCount);

		// check if an error happened
		if(!dataSrc.ok())
		{
			dataSrc.setError();
			return 0;
		}

		// load all texture coordinates of the vertex
		int textureCoordinateId;
		for(textureCoordinateId = 0; textureCoordinateId < textureCoordinateCount; ++textureCoordinateId)
		{
			QunCoreSubmesh::TextureCoordinate textureCoordinate;

			// load data of the influence
			dataSrc.readFloat(textureCoordinate.u);
			dataSrc.readFloat(textureCoordinate.v);

			if (loadingMode & LOADER_INVERT_V_COORD)
			{
				textureCoordinate.v = 1.0f - textureCoordinate.v;
			}

			// check if an error happened
			if(!dataSrc.ok())
			{
				dataSrc.setError();
				return 0;
			}

			// set texture coordinate in the core submesh instance
			pCoreSubmesh->setTextureCoordinate(vertexId, textureCoordinateId, textureCoordinate);
		}

		// get the number of influences
		int influenceCount;
		if(!dataSrc.readInteger(influenceCount) || (influenceCount < 0))
		{
			dataSrc.setError();
			return 0;
		}

		// reserve memory for the influences in the vertex
		vertex.vectorInfluence.resize(influenceCount);

		// load all influences of the vertex
		int influenceId;
		for(influenceId = 0; influenceId < influenceCount; ++influenceId)
		{
			// load data of the influence
			dataSrc.readInteger(vertex.vectorInfluence[influenceId].boneId),
			dataSrc.readFloat(vertex.vectorInfluence[influenceId].weight);

			// check if an error happened
			if(!dataSrc.ok())
			{
				dataSrc.setError();
				return 0;
			}
		}

		// load the physical property of the vertex if there are springs in the core submesh
		if(springCount > 0)
		{
			QunCoreSubmesh::PhysicalProperty physicalProperty;

			// load data of the physical property
			dataSrc.readFloat(physicalProperty.weight);

			// check if an error happened
			if(!dataSrc.ok())
			{
				dataSrc.setError();
				return 0;
			}

			// set the physical property in the core submesh instance
			pCoreSubmesh->setPhysicalProperty(vertexId, physicalProperty);
		}
	}

	// load all springs
	int springId;
	for(springId = 0; springId < springCount; ++springId)
	{
		QunCoreSubmesh::Spring spring;

		// load data of the spring
		dataSrc.readInteger(spring.vertexId[0]);
		dataSrc.readInteger(spring.vertexId[1]);
		dataSrc.readFloat(spring.springCoefficient);
		dataSrc.readFloat(spring.idleLength);

		// check if an error happened
		if(!dataSrc.ok())
		{
			dataSrc.setError();
			return 0;
		}

		// set spring in the core submesh instance
		pCoreSubmesh->setSpring(springId, spring);
	}


	// load all faces
	int faceId;
	int justOnce = 0;
	bool flipModel = false;
	for(faceId = 0; faceId < faceCount; ++faceId)
	{
		QunCoreSubmesh::Face face;

		// load data of the face

		int tmp[4];
		dataSrc.readInteger(tmp[0]);
		dataSrc.readInteger(tmp[1]);
		dataSrc.readInteger(tmp[2]);

		if(sizeof(QunIndex)==2)
		{
			if(tmp[0]>65535 || tmp[1]>65535 || tmp[2]>65535)
			{      
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
				return 0;
			}
		}
		face.vertexId[0]=tmp[0];
		face.vertexId[1]=tmp[1];
		face.vertexId[2]=tmp[2];

		// check if an error happened
		if(!dataSrc.ok())
		{
			dataSrc.setError();
			return 0;
		}

		// check if left-handed coord system is used by the object
		// can be done only once since the object has one system for all faces
		if (justOnce==0)
		{
			// get vertexes of first face
			std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pCoreSubmesh->getVectorVertex();
			QunCoreSubmesh::Vertex& v1 = vectorVertex[tmp[0]];
			QunCoreSubmesh::Vertex& v2 = vectorVertex[tmp[1]];
			QunCoreSubmesh::Vertex& v3 = vectorVertex[tmp[2]];

			QunVector point1 = QunVector(v1.position.x, v1.position.y, v1.position.z);
			QunVector point2 = QunVector(v2.position.x, v2.position.y, v2.position.z);
			QunVector point3 = QunVector(v3.position.x, v3.position.y, v3.position.z);

			// gets vectors (v1-v2) and (v3-v2)
			QunVector vect1 = point1 - point2;
			QunVector vect2 = point3 - point2;

			// calculates normal of face
			QunVector cross = vect1 % vect2;
			float	crossLength = cross.length();
			if (crossLength == 0.0f)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
				return 0;
			}
			QunVector faceNormal = cross / crossLength;

			// compare the calculated normal with the normal of a vertex
			QunVector maxNorm = v1.normal;

			// if the two vectors point to the same direction then the poly needs flipping
			// so if the dot product > 0 it needs flipping
			if (faceNormal*maxNorm>0)
				flipModel = true;

			// flip the winding order if the loading flags request it
			if (loadingMode & LOADER_FLIP_WINDING)
				flipModel = !flipModel;

			justOnce = 1;
		}


		// flip if needed
		if (flipModel) 
		{
			tmp[3] = face.vertexId[1];
			face.vertexId[1]=face.vertexId[2];
			face.vertexId[2]=tmp[3];
		}

		// set face in the core submesh instance
		pCoreSubmesh->setFace(faceId, face);
	}

	return pCoreSubmesh.release();
#endif
	QunCoreSubmesh *pCoreSubmesh = nullptr;

	return pCoreSubmesh;
}

 /*****************************************************************************/
/** Loads a core track instance.
  *
  * This function loads a core track instance from a data source.
  *
  * @param dataSrc The data source to load the core track instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core track
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreTrack *QunLoader::loadCoreTrack(QunDataSource& dataSrc, QunCoreSkeleton *skel, float duration, int flags)
{
  if(!dataSrc.ok())
  {
    dataSrc.setError();
    return 0;
  }

  // read the bone id
  int coreBoneId;
  if(!dataSrc.readInteger(coreBoneId) || (coreBoneId < 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

  // allocate a new core track instance
  QunCoreTrack* pCoreTrack = new QunCoreTrack();

  // create the core track instance
  if(!pCoreTrack->create())
  {
    return 0;
  }

  // link the core track to the appropriate core bone instance
  pCoreTrack->setCoreBoneId(coreBoneId);

  // read the number of keyframes
  int keyframeCount;
  if(!dataSrc.readInteger(keyframeCount) || (keyframeCount <= 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    return 0;
  }

	QunVector minpt, scale;
	if(flags & 1)
	{
		dataSrc.readFloat(minpt.x);
		dataSrc.readFloat(minpt.y);
		dataSrc.readFloat(minpt.z);
		dataSrc.readFloat(scale.x);
		dataSrc.readFloat(scale.y);
		dataSrc.readFloat(scale.z);
	}

  // load all core keyframes
  int keyframeId;
  for(keyframeId = 0; keyframeId < keyframeCount; ++keyframeId)
  {
    // load the core keyframe
    QunCoreKeyframe *pCoreKeyframe;

		if(flags & 1)
		{
			pCoreKeyframe = loadCompressedCoreKeyframe(dataSrc, minpt, scale, duration);
		}
		else
		{
			pCoreKeyframe = loadCoreKeyframe(dataSrc);
		}

    if(pCoreKeyframe == 0)
    {
      pCoreTrack->destroy();
      return 0;
    }
    if(loadingMode & LOADER_ROTATE_X_AXIS)
    {
      // Check for anim rotation
      if (skel && skel->getCoreBone(coreBoneId)->getParentId() == -1)  // root bone
      {
        // rotate root bone quaternion
        QunQuaternion rot = pCoreKeyframe->getRotation();
        QunQuaternion x_axis_90(0.7071067811f,0.0f,0.0f,0.7071067811f);
        rot *= x_axis_90;
        pCoreKeyframe->setRotation(rot);
        // rotate root bone displacement
        QunVector vec = pCoreKeyframe->getTranslation();
				vec *= x_axis_90;
        pCoreKeyframe->setTranslation(vec);
      }
    }    

    // add the core keyframe to the core track instance
    pCoreTrack->addCoreKeyframe(pCoreKeyframe);
  }

  return pCoreTrack;
}

//////// Load UN Core Track ////////
#if 0
UN_CoreTrack QunLoader::loadCoreTrack(QunDataSource& dataSrc, QunCoreSkeleton *skel, float duration, int flags)
{
  if(!dataSrc.ok())
    {
    dataSrc.setError();
	for(;;) {}
    }

  // read the bone id
  int coreBoneId;
  if(!dataSrc.readInteger(coreBoneId) || (coreBoneId < 0))
    {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    for(;;) {}
    }

  // Create Animation Instance
  UN_CoreTrack pCoreTrack;

  // create the core track instance
  if(!pCoreTrack.create())
    {
    for(;;) {}
    }

  // link the core track to the appropriate core bone instance
  pCoreTrack.setCoreBoneId(coreBoneId);

  // read the number of keyframes
  int keyframeCount;
  if(!dataSrc.readInteger(keyframeCount) || (keyframeCount <= 0))
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__);
    for(;;) {}
  }

	QunVector minpt, scale;
	if(flags & 1)
	{
		dataSrc.readFloat(minpt.x);
		dataSrc.readFloat(minpt.y);
		dataSrc.readFloat(minpt.z);
		dataSrc.readFloat(scale.x);
		dataSrc.readFloat(scale.y);
		dataSrc.readFloat(scale.z);
	}

  const Alloc_KeyFrame alloc_keyframe (m_unSegFrame->m_unSegment.get_segment_manager());
  std::string i_ObjIdent = acIdentGen("UNKeyframe", true);
  pCoreTrack.m_keyframes = m_unSegFrame->m_unSegment.construct<UN_Vector_KeyFrame>(i_ObjIdent.c_str())(alloc_keyframe);

  // load all core keyframes
  int keyframeId;
  for(keyframeId = 0; keyframeId < keyframeCount; ++keyframeId)
  {
    // load the core keyframe
    QunCoreKeyframe pCoreKeyframe;

	if(flags & 1)
		{
		pCoreKeyframe = loadCompressedCoreKeyframe(dataSrc, minpt, scale, duration);
		}
	else
		{
		pCoreKeyframe = loadCoreKeyframe(dataSrc);
		}

    if(loadingMode & LOADER_ROTATE_X_AXIS)
      {
      // Check for anim rotation
      if (skel && skel->getCoreBone(coreBoneId)->getParentId() == -1)  // root bone
        {
        // rotate root bone quaternion
        QunQuaternion rot = pCoreKeyframe.getRotation();
        QunQuaternion x_axis_90(0.7071067811f,0.0f,0.0f,0.7071067811f);
        rot *= x_axis_90;
        pCoreKeyframe.setRotation(rot);
        // rotate root bone displacement
        QunVector vec = pCoreKeyframe.getTranslation();
				vec *= x_axis_90;
        pCoreKeyframe.setTranslation(vec);
        }
      }    

	// add the core keyframe to the core track instance
	pCoreTrack.addCoreKeyframe(pCoreKeyframe);
	}

  return pCoreTrack;
}
#endif


 /*****************************************************************************/
/** Loads a core animation instance from a XML file.
  *
  * This function loads a core animation instance from a XML file.
  *
  * @param strFilename The name of the file to load the core animation instance
  *                    from.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreAnimationPtr QunLoader::loadXmlCoreAnimation(const std::string& strFilename, QunCoreSkeleton *skel)
{
	std::stringstream str;
	TiXmlDocument doc(strFilename);
	if(!doc.LoadFile())
	{
		QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, strFilename);
		return 0;
	}

	TiXmlNode* node;

	TiXmlElement*animation = doc.FirstChildElement();
	if(!animation)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
		return false;
	}

	if(_stricmp(animation->Value(),"HEADER")==0)
	{
		if(_stricmp(animation->Attribute("MAGIC"),Qun::ANIMATION_XMLFILE_MAGIC)!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
			return false;
		}

		if(atoi(animation->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
		{
			QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, strFilename);
			return false;
		}

		animation = animation->NextSiblingElement();
	}

	if(!animation || _stricmp(animation->Value(),"ANIMATION")!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
		return false;
	}

	if(animation->Attribute("MAGIC") !=NULL && _stricmp(animation->Attribute("MAGIC"),Qun::ANIMATION_XMLFILE_MAGIC)!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
		return false;
	}

	if(animation->Attribute("VERSION")!=NULL && atoi(animation->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
	{
		QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, strFilename);
		return false;
	}

	int trackCount= atoi(animation->Attribute("NUMTRACKS"));
	float duration= (float) atof(animation->Attribute("DURATION"));

	// allocate a new core animation instance
	QunCoreAnimation *pCoreAnimation;
	pCoreAnimation = new(std::nothrow) QunCoreAnimation();
	if(pCoreAnimation == 0)
	{
		QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
		return 0;
	}

	// check for a valid duration
	if(duration <= 0.0f)
	{
		QunError::setLastError(QunError::INVALID_ANIMATION_DURATION, __FILE__, __LINE__, strFilename);
		return 0;
	}

	// set the duration in the core animation instance
	pCoreAnimation->setDuration(duration);
	TiXmlElement* track=animation->FirstChildElement();

	// load all core bones
	int trackId;
	for(trackId = 0; trackId < trackCount; ++trackId)
	{
		if(!track || _stricmp(track->Value(),"TRACK")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
			return 0;
		}

		QunCoreTrack *pCoreTrack;

		pCoreTrack = new(std::nothrow) QunCoreTrack();
		if(pCoreTrack == 0)
		{
			QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
			return 0;
		}

		// create the core track instance
		if(!pCoreTrack->create())
		{
			delete pCoreTrack;
			return 0;
		}

		int coreBoneId = atoi(track->Attribute("BONEID"));

		// link the core track to the appropriate core bone instance
		pCoreTrack->setCoreBoneId(coreBoneId);

		// read the number of keyframes
		int keyframeCount= atoi(track->Attribute("NUMKEYFRAMES"));

		if(keyframeCount <= 0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
			return 0;
		}

		TiXmlElement* keyframe= track->FirstChildElement();

		// load all core keyframes
		int keyframeId;
		for(keyframeId = 0; keyframeId < keyframeCount; ++keyframeId)
		{
			// load the core keyframe
			if(!keyframe|| _stricmp(keyframe->Value(),"KEYFRAME")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}

			float time= (float) atof(keyframe->Attribute("TIME"));

			TiXmlElement* translation = keyframe->FirstChildElement();
			if(!translation || _stricmp(translation->Value(),"TRANSLATION")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}

			float tx, ty, tz;

			node = translation->FirstChild();
			if(!node)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}

			TiXmlText* translationdata = node->ToText();
			if(!translationdata)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}
			str.clear();
			str << translationdata->Value();
			str >> tx >> ty >> tz;  

			TiXmlElement* rotation = translation->NextSiblingElement();
			if(!rotation || _stricmp(rotation->Value(),"ROTATION")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}

			float rx, ry, rz, rw;

			node = rotation->FirstChild();
			if(!node)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}
			TiXmlText* rotationdata = node->ToText();
			if(!rotationdata)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, strFilename);
				return 0;
			}
			str.clear();
			str << rotationdata->Value();
			str >> rx >> ry >> rz >> rw;  

			// allocate a new core keyframe instance

			QunCoreKeyframe *pCoreKeyframe;
			pCoreKeyframe = new(std::nothrow) QunCoreKeyframe();
			if(pCoreKeyframe == 0)
			{
				QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
				return 0;
			}

			// create the core keyframe instance
			if(!pCoreKeyframe->create())
			{
				return 0;			  
			}
			// set all attributes of the keyframe
			pCoreKeyframe->setTime(time);
			pCoreKeyframe->setTranslation(QunVector(tx, ty, tz));
			pCoreKeyframe->setRotation(QunQuaternion(rx, ry, rz, rw));

			if (loadingMode & LOADER_ROTATE_X_AXIS)
			{
				// Check for anim rotation
				if (skel && skel->getCoreBone(coreBoneId)->getParentId() == -1)  // root bone
				{
					// rotate root bone quaternion
					QunQuaternion rot = pCoreKeyframe->getRotation();
					QunQuaternion x_axis_90(0.7071067811f,0.0f,0.0f,0.7071067811f);
					rot *= x_axis_90;
					pCoreKeyframe->setRotation(rot);
					// rotate root bone displacement
					QunVector trans = pCoreKeyframe->getTranslation();
					trans *= x_axis_90;
					pCoreKeyframe->setTranslation(trans);
				}
			}    

			// add the core keyframe to the core track instance
			pCoreTrack->addCoreKeyframe(pCoreKeyframe);
			keyframe = keyframe->NextSiblingElement();
		}

		pCoreAnimation->addCoreTrack(pCoreTrack);	  
		track=track->NextSiblingElement();
	}

	// explicitly close the file
	doc.Clear();

	return pCoreAnimation;
}

 /*****************************************************************************/
/** Loads a core material instance from a XML file.
  *
  * This function loads a core material instance from a XML file.
  *
  * @param strFilename The name of the file to load the core material instance
  *                    from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/


QunCoreMaterialPtr QunLoader::loadXmlCoreMaterial(const std::string& strFilename)
{
  std::stringstream str;
  TiXmlDocument doc(strFilename);
  if(!doc.LoadFile())
  {
    QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, strFilename);
    return 0;
  }

  return loadXmlCoreMaterial( doc );
}

 /*****************************************************************************/
/** Loads a core mesh instance from a Xml file.
  *
  * This function loads a core mesh instance from a Xml file.
  *
  * @param strFilename The name of the file to load the core mesh instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreMeshPtr QunLoader::loadXmlCoreMesh(const std::string& strFilename)
{
	std::string i_FullFilename = m_FilePath + strFilename;

	std::stringstream str;
	TiXmlDocument doc(i_FullFilename);
	if(!doc.LoadFile())
	{
		QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, i_FullFilename);
		return 0;
	}

	return loadXmlCoreMesh( doc );
}

 /*****************************************************************************/
/** Loads a core skeleton instance from a XML file.
  *
  * This function loads a core skeleton instance from a XML file.
  *
  * @param strFilename The name of the file to load the core skeleton instance
  *                    from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/

QunCoreSkeletonPtr QunLoader::loadXmlCoreSkeleton(const std::string& strFilename)
{
	TiXmlDocument doc(strFilename);
	if(!doc.LoadFile())
	{
		QunError::setLastError(QunError::FILE_NOT_FOUND, __FILE__, __LINE__, strFilename);
		return 0;
	}

	return loadXmlCoreSkeleton( doc );
}

 /*****************************************************************************/
/** Loads a core material instance from an XML document.
  *
  * This function loads a core material instance from an XML document.
  *
  * @param doc			The document to load the core material instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happened
  *****************************************************************************/
QunCoreMaterialPtr QunLoader::loadXmlCoreMaterial(TiXmlDocument& doc)
{
  std::stringstream str;
  int r,g,b,a;

  TiXmlNode* node;

  TiXmlElement*material = doc.FirstChildElement();
  if(!material)
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  if(_stricmp(material->Value(),"HEADER")==0)
  {
    if(_stricmp(material->Attribute("MAGIC"),Qun::MATERIAL_XMLFILE_MAGIC)!=0)
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
          return false;
    }

    if(atoi(material->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
    {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
          return false;
    }

    material = material->NextSiblingElement();
  }

  if(!material||_stricmp(material->Value(),"MATERIAL")!=0)
  {
	  QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
      return false;
  }

  if(material->Attribute("MAGIC")!=NULL && _stricmp(material->Attribute("MAGIC"),Qun::MATERIAL_XMLFILE_MAGIC)!=0)
  {
    QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  if(material->Attribute("VERSION") != NULL && atoi(material->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
  {
    QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
        return false;
  }

  QunCoreMaterialPtr pCoreMaterial( new(std::nothrow) QunCoreMaterial() );
  if(pCoreMaterial.get() == 0)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return 0;
  }

  TiXmlElement* ambient = material->FirstChildElement();
  if(!ambient ||_stricmp(ambient->Value(),"AMBIENT")!=0)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  QunCoreMaterial::Color ambientColor; 
  node = ambient->FirstChild();
  if(!node)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  TiXmlText* ambientdata = node->ToText();
  if(!ambientdata)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  str << ambientdata->Value();
  str >> r >> g >> b >> a;
  ambientColor.red = (unsigned char)r;
  ambientColor.green = (unsigned char)g;
  ambientColor.blue = (unsigned char)b;
  ambientColor.alpha = (unsigned char)a; 

  TiXmlElement* diffuse = ambient->NextSiblingElement();
  if(!diffuse || _stricmp(diffuse->Value(),"DIFFUSE")!=0)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  QunCoreMaterial::Color diffuseColor; 
  node = diffuse->FirstChild();
  if(!node)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  TiXmlText* diffusedata = node->ToText();
  if(!diffusedata)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  str.clear();
  str << diffusedata->Value();
  str >> r >> g >> b >> a;
  diffuseColor.red = (unsigned char)r;
  diffuseColor.green = (unsigned char)g;
  diffuseColor.blue = (unsigned char)b;
  diffuseColor.alpha = (unsigned char)a;
  

  TiXmlElement* specular = diffuse->NextSiblingElement();
  if(!specular||_stricmp(specular->Value(),"SPECULAR")!=0)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  QunCoreMaterial::Color specularColor; 
  node = specular->FirstChild();
  if(!node)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  TiXmlText* speculardata = node->ToText();
  if(!speculardata)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  str.clear();
  str << speculardata->Value();
  str >> r >> g >> b >> a;
  specularColor.red = (unsigned char)r;
  specularColor.green = (unsigned char)g;
  specularColor.blue = (unsigned char)b;
  specularColor.alpha = (unsigned char)a;


  TiXmlElement* shininess = specular->NextSiblingElement();
  if(!shininess||_stricmp(shininess->Value(),"SHININESS")!=0)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }

  float fshininess;
  node = shininess->FirstChild();
  if(!node)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
  }
  TiXmlText* shininessdata = node->ToText();
  if(!shininessdata)
  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
         return false;
  }
  fshininess = (float)atof(shininessdata->Value());

  // set the colors and the shininess
  pCoreMaterial->setAmbientColor(ambientColor);
  pCoreMaterial->setDiffuseColor(diffuseColor);
  pCoreMaterial->setSpecularColor(specularColor);
  pCoreMaterial->setShininess(fshininess);
  
  std::vector<std::string> MatFileName;

  TiXmlElement* map;

  for( map = shininess->NextSiblingElement();map;map = map->NextSiblingElement() )
  {
	  if(!map||_stricmp(map->Value(),"MAP")!=0)
	  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
	  }
	  

	  node= map->FirstChild();
	  if(!node)
	  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
	  }

	  TiXmlText* mapfile = node->ToText();
	  if(!mapfile)
	  {
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
        return false;
	  }

	  MatFileName.push_back(mapfile->Value());
  }

  pCoreMaterial->reserve(MatFileName.size());



  for (unsigned int mapId=0; mapId < MatFileName.size(); ++mapId)
  {
	  QunCoreMaterial::Map Map;
	  // initialize the user data
	  Map.userData = 0;

	  Map.strFilename= MatFileName[mapId];	  

	  // set map in the core material instance
	  pCoreMaterial->setMap(mapId, Map);
  }

  doc.Clear();
  
  return pCoreMaterial;
}


 /*****************************************************************************/
/** Loads a core mesh instance from a Xml file.
  *
  * This function loads a core mesh instance from a Xml document.
  *
  * @param doc The document to load the core mesh instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happened
  *****************************************************************************/
QunCoreMeshPtr QunLoader::loadXmlCoreMesh(TiXmlDocument& doc)
{
   std::stringstream str;

	TiXmlNode* node;

	TiXmlElement*mesh = doc.FirstChildElement();
	if(!mesh)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return false;
	}

	if(_stricmp(mesh->Value(),"HEADER")==0)
	{
		if(_stricmp(mesh->Attribute("MAGIC"),Qun::MESH_XMLFILE_MAGIC)!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		if(atoi(mesh->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
		{
			QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
			return false;
		}

		mesh = mesh->NextSiblingElement();
	}
	if(!mesh || _stricmp(mesh->Value(),"MESH")!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return false;
	}

	if(mesh->Attribute("MAGIC")!=NULL && _stricmp(mesh->Attribute("MAGIC"),Qun::MESH_XMLFILE_MAGIC)!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return false;
	}

	if(mesh->Attribute("VERSION")!=NULL && atoi(mesh->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
	{
		QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
		return false;
	}

	// get the number of submeshes
	int submeshCount = atoi(mesh->Attribute("NUMSUBMESH"));

	// allocate a new core mesh instance
	QunCoreMeshPtr pCoreMesh = new(std::nothrow) QunCoreMesh;
	if(!pCoreMesh)
	{
		QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
		return 0;
	}

	TiXmlElement*submesh = mesh->FirstChildElement();

	// load all core submeshes
	int submeshId;
	for(submeshId = 0; submeshId < submeshCount; ++submeshId)
	{
		if(!submesh || _stricmp(submesh->Value(),"SUBMESH")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		// get the material thread id of the submesh
		int coreMaterialThreadId = atoi(submesh->Attribute("MATERIAL"));

		// get the number of vertices, faces, level-of-details and springs
		int vertexCount = atoi(submesh->Attribute("NUMVERTICES"));

		int faceCount = atoi(submesh->Attribute("NUMFACES"));

		int lodCount = atoi(submesh->Attribute("NUMLODSTEPS"));

		int springCount = atoi(submesh->Attribute("NUMSPRINGS"));

		int textureCoordinateCount = atoi(submesh->Attribute("NUMTEXCOORDS"));

		// allocate a new core submesh instance
		QunCoreSubmesh* pCoreSubmesh = new QunCoreSubmesh();

		// set the LOD step count
		pCoreSubmesh->setLodCount(lodCount);

		// set the core material id
		pCoreSubmesh->setCoreMaterialThreadId(coreMaterialThreadId);

		// reserve memory for all the submesh data
		if(!pCoreSubmesh->reserve(vertexCount, textureCoordinateCount, faceCount, springCount))
		{
			QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__, doc.Value());
			return 0;
		}

		TiXmlElement *vertex = submesh->FirstChildElement();

		// load all vertices and their influences
		int vertexId;
		for(vertexId = 0; vertexId < vertexCount; ++vertexId)
		{
			if(!vertex || _stricmp(vertex->Value(),"VERTEX")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}      

			QunCoreSubmesh::Vertex Vertex;

			TiXmlElement *pos= vertex->FirstChildElement();
			if(!pos || _stricmp(pos->Value(),"POS")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}

			node = pos->FirstChild();
			if(!node)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}      
			TiXmlText* posdata = node->ToText();
			if(!posdata)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}
			str.clear();
			str << posdata->Value();
			str >> Vertex.position.x >> Vertex.position.y >> Vertex.position.z;  

			TiXmlElement *norm= pos->NextSiblingElement();
			if(!norm||_stricmp(norm->Value(),"NORM")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}

			node = norm->FirstChild();
			if(!norm)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}
			TiXmlText* normdata = node->ToText();
			if(!normdata)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}
			str.clear();
			str << normdata->Value();
			str >> Vertex.normal.x >> Vertex.normal.y >> Vertex.normal.z;

			TiXmlElement *collapse= norm->NextSiblingElement();
			if(collapse && _stricmp(collapse->Value(),"COLLAPSEID")==0)
			{
				node = collapse->FirstChild();
				if(!node)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				TiXmlText* collapseid = node->ToText();
				if(!collapseid)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				Vertex.collapseId = atoi(collapseid->Value());

				TiXmlElement *collapseCount= collapse->NextSiblingElement();
				if(!collapseCount|| _stricmp(collapseCount->Value(),"COLLAPSECOUNT")!=0)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}

				node = collapseCount->FirstChild();
				if(!node)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				TiXmlText* collapseCountdata = node->ToText();
				if(!collapseCountdata)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				Vertex.faceCollapseCount= atoi(collapseCountdata->Value());
				collapse = collapseCount->NextSiblingElement();        
			}
			else
			{
				Vertex.collapseId=-1;
				Vertex.faceCollapseCount=0;
			}


			TiXmlElement *texcoord = collapse;

			// load all texture coordinates of the vertex
			int textureCoordinateId;
			for(textureCoordinateId = 0; textureCoordinateId < textureCoordinateCount; ++textureCoordinateId)
			{
				QunCoreSubmesh::TextureCoordinate textureCoordinate;
				// load data of the influence
				if(!texcoord || _stricmp(texcoord->Value(),"TEXCOORD")!=0)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}

				node = texcoord->FirstChild();
				if(!node)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				TiXmlText* texcoorddata = node->ToText();
				if(!texcoorddata)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				str.clear();
				str << texcoorddata->Value();
				str >> textureCoordinate.u >> textureCoordinate.v;

				if (loadingMode & LOADER_INVERT_V_COORD)
				{
					textureCoordinate.v = 1.0f - textureCoordinate.v;
				}

				// set texture coordinate in the core submesh instance
				pCoreSubmesh->setTextureCoordinate(vertexId, textureCoordinateId, textureCoordinate);
				texcoord = texcoord->NextSiblingElement();
			}

			// get the number of influences
			int influenceCount= atoi(vertex->Attribute("NUMINFLUENCES"));

			if(influenceCount < 0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return 0;
			}

			// reserve memory for the influences in the vertex
			Vertex.vectorInfluence.reserve(influenceCount);
			Vertex.vectorInfluence.resize(influenceCount);

			TiXmlElement *influence = texcoord;

			// load all influences of the vertex
			int influenceId;
			for(influenceId = 0; influenceId < influenceCount; ++influenceId)
			{
				if(!influence ||_stricmp(influence->Value(),"INFLUENCE")!=0)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}

				node = influence->FirstChild();
				if(!node)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				TiXmlText* influencedata = node->ToText();
				if(!influencedata)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}

				Vertex.vectorInfluence[influenceId].boneId = atoi(influence->Attribute("ID"));

				Vertex.vectorInfluence[influenceId].weight = (float) atof(influencedata->Value());

				influence=influence->NextSiblingElement();    
			}

			// set vertex in the core submesh instance

#if 0
			Vertex.position.x *= 0.3919;
			Vertex.position.y *= 0.3919;
			Vertex.position.z *= 0.3919;
#endif

			pCoreSubmesh->setVertex(vertexId, Vertex);

			TiXmlElement *physique = influence;



			// load the physical property of the vertex if there are springs in the core submesh
			if(springCount > 0)
			{
				QunCoreSubmesh::PhysicalProperty physicalProperty;

				if(!physique || _stricmp(physique->Value(),"PHYSIQUE")!=0)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				node = physique->FirstChild();
				if(!node)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}
				TiXmlText* physiquedata = node->ToText();
				if(!physiquedata)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return false;
				}

				physicalProperty.weight = (float) atof(physiquedata->Value());

				// set the physical property in the core submesh instance
				pCoreSubmesh->setPhysicalProperty(vertexId, physicalProperty);          

			}


			vertex = vertex->NextSiblingElement();
		}

		TiXmlElement *spring= vertex;

		// load all springs
		int springId;
		for(springId = 0; springId < springCount; ++springId)
		{
			QunCoreSubmesh::Spring Spring;
			if(!spring ||_stricmp(spring->Value(),"SPRING")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}
			str.clear();
			str << spring->Attribute("VERTEXID");
			str >> Spring.vertexId[0] >> Spring.vertexId[1];
			Spring.springCoefficient = (float) atof(spring->Attribute("COEF"));
			Spring.idleLength = (float) atof(spring->Attribute("LENGTH"));

			// set spring in the core submesh instance
			pCoreSubmesh->setSpring(springId, Spring);
			spring = spring->NextSiblingElement();
		}

		TiXmlElement *face = spring;

		// load all faces
		int faceId;
		for(faceId = 0; faceId < faceCount; ++faceId)
		{
			QunCoreSubmesh::Face Face;

			if(!face || _stricmp(face->Value(),"FACE")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}

			int tmp[3];

			// load data of the face

			str.clear();
			str << face->Attribute("VERTEXID");
			str >> tmp[0] >> tmp [1] >> tmp[2];

			if(sizeof(QunIndex)==2)
			{
				if(tmp[0]>65535 || tmp[1]>65535 || tmp[2]>65535)
				{
					QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
					return 0;
				}
			}
			Face.vertexId[0]=tmp[0];
			Face.vertexId[1]=tmp[1];
			Face.vertexId[2]=tmp[2];

			pCoreSubmesh->setFace(faceId, Face);

			face=face->NextSiblingElement();
		}
		submesh=submesh->NextSiblingElement();

		// add the core submesh to the core mesh instance
		pCoreMesh->addCoreSubmesh(pCoreSubmesh);
	}

	// explicitly close the file
	doc.Clear();
	return pCoreMesh;
}

 /*****************************************************************************/
/** Loads a core skeleton instance from a XML document.
  *
  * This function loads a core skeleton instance from a XML document.
  *
  * @param doc		The document to load the core skeleton instance from.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happened
  *****************************************************************************/
QunCoreSkeletonPtr QunLoader::loadXmlCoreSkeleton(cal3d::TiXmlDocument& doc)
{
	std::stringstream str;

	TiXmlNode* node;
	TiXmlElement*skeleton = doc.FirstChildElement();
	if(!skeleton)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return 0;
	}

	if(_stricmp(skeleton->Value(),"HEADER")==0)
	{
		if(_stricmp(skeleton->Attribute("MAGIC"),Qun::SKELETON_XMLFILE_MAGIC)!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		if(atoi(skeleton->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
		{
			QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
			return false;
		}

		skeleton = skeleton->NextSiblingElement();
	}

	if(!skeleton || _stricmp(skeleton->Value(),"SKELETON")!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return false;
	}

	if(skeleton->Attribute("MAGIC")!=NULL && _stricmp(skeleton->Attribute("MAGIC"),Qun::SKELETON_XMLFILE_MAGIC)!=0)
	{
		QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
		return false;
	}

	if(skeleton->Attribute("VERSION")!=NULL && atoi(skeleton->Attribute("VERSION")) < Qun::EARLIEST_COMPATIBLE_FILE_VERSION )
	{
		QunError::setLastError(QunError::INCOMPATIBLE_FILE_VERSION, __FILE__, __LINE__, doc.Value());
		return false;
	}


	// allocate a new core skeleton instance
	QunCoreSkeletonPtr pCoreSkeleton = new(std::nothrow) QunCoreSkeleton();
	if(!pCoreSkeleton)
	{
		QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
		return 0;
	}

	TiXmlElement* bone;
	for( bone = skeleton->FirstChildElement();bone;bone = bone->NextSiblingElement() )
	{
		if(_stricmp(bone->Value(),"BONE")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}    

		std::string strName=bone->Attribute("NAME");


		// get the translation of the bone

		TiXmlElement* translation = bone->FirstChildElement();
		if(!translation || _stricmp( translation->Value(),"TRANSLATION")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		float tx, ty, tz;

		node = translation->FirstChild();
		if(!node)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}    
		TiXmlText* translationdata = node->ToText();
		if(!translationdata)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}    
		str.clear();
		str << translationdata->Value();
		str >> tx >> ty >> tz;

		// get the rotation of the bone

		TiXmlElement* rotation = translation->NextSiblingElement();
		if(!rotation || _stricmp(rotation->Value(),"ROTATION")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		float rx, ry, rz, rw;

		node = rotation->FirstChild();
		if(!node)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		TiXmlText* rotationdata = node->ToText();
		if(!rotationdata)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		str.clear();
		str << rotationdata->Value();
		str >> rx >> ry >> rz >> rw;    

		// get the bone space translation of the bone


		TiXmlElement* translationBoneSpace = rotation->NextSiblingElement();
		if(!rotation || _stricmp(translationBoneSpace->Value(),"LOCALTRANSLATION")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		float txBoneSpace, tyBoneSpace, tzBoneSpace;

		node = translationBoneSpace->FirstChild();
		if(!node)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		TiXmlText* translationBoneSpacedata = node->ToText();
		if(!translationBoneSpacedata)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		str.clear();
		str << translationBoneSpacedata->Value();
		str >> txBoneSpace >> tyBoneSpace >> tzBoneSpace;

		// get the bone space rotation of the bone

		TiXmlElement* rotationBoneSpace = translationBoneSpace->NextSiblingElement();
		if(!rotationBoneSpace || _stricmp(rotationBoneSpace->Value(),"LOCALROTATION")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}

		float rxBoneSpace, ryBoneSpace, rzBoneSpace, rwBoneSpace;

		node = rotationBoneSpace->FirstChild();
		if(!node)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		TiXmlText* rotationBoneSpacedata = node->ToText();
		if(!rotationBoneSpacedata)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		str.clear();
		str << rotationBoneSpacedata->Value();
		str >> rxBoneSpace >> ryBoneSpace >> rzBoneSpace >> rwBoneSpace;

		// get the parent bone id

		TiXmlElement* parent = rotationBoneSpace->NextSiblingElement();
		if(!parent ||_stricmp(parent->Value(),"PARENTID")!=0)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}


		int parentId;

		node = parent->FirstChild();
		if(!node)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		TiXmlText* parentid = node->ToText();
		if(!parentid)
		{
			QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
			return false;
		}
		parentId = atoi(parentid->Value());

		// allocate a new core bone instance
		QunCoreBone* pCoreBone = new QunCoreBone(strName);

		// set the parent of the bone
		pCoreBone->setParentId(parentId);

		// set all attributes of the bone

		QunVector trans = QunVector(tx, ty, tz);
		QunQuaternion rot = QunQuaternion(rx, ry, rz, rw);

		if (loadingMode & LOADER_ROTATE_X_AXIS)
		{
			if (parentId == -1) // only root bone necessary
			{
				// Root bone must have quaternion rotated
				QunQuaternion x_axis_90(0.7071067811f,0.0f,0.0f,0.7071067811f);
				rot *= x_axis_90;
				// Root bone must have translation rotated also
				trans *= x_axis_90;
			}
		}    


		pCoreBone->setTranslation(trans);
		pCoreBone->setRotation(rot);
		pCoreBone->setTranslationBoneSpace(QunVector(txBoneSpace, tyBoneSpace, tzBoneSpace));
		pCoreBone->setRotationBoneSpace(QunQuaternion(rxBoneSpace, ryBoneSpace, rzBoneSpace, rwBoneSpace));


		TiXmlElement* child;
		for( child = parent->NextSiblingElement();child;child = child->NextSiblingElement() )
		{
			if(_stricmp(child->Value(),"CHILDID")!=0)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}

			TiXmlNode *node= child->FirstChild();
			if(!node)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}
			TiXmlText* childid = node->ToText();
			if(!childid)
			{
				QunError::setLastError(QunError::INVALID_FILE_FORMAT, __FILE__, __LINE__, doc.Value());
				return false;
			}

			int childId = atoi(childid->Value());

			pCoreBone->addChildId(childId);
		}

		// set the core skeleton of the core bone instance
		pCoreBone->setCoreSkeleton(pCoreSkeleton.get());

		// add the core bone to the core skeleton instance
		pCoreSkeleton->addCoreBone(pCoreBone);

	}

	doc.Clear();

	pCoreSkeleton->calculateState();

	return pCoreSkeleton;
}


//****************************************************************************//
