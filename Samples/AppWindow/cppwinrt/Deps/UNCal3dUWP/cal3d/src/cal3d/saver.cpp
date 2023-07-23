//****************************************************************************//
// saver.cpp                                                                  //
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

#include "cal3d/saver.h"
#include "cal3d/error.h"
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

#include <float.h>

using namespace cal3d;

 /*****************************************************************************/
/** Saves a core animation instance.
  *
  * This function saves a core animation instance to a file.
  *
  * @param strFilename The name of the file to save the core animation instance
  *                    to.
  * @param pCoreAnimation A pointer to the core animation instance that should
  *                       be saved.
	* param pOptions Optional pointer to save options.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreAnimation(const std::string& strFilename, QunCoreAnimation *pCoreAnimation, QunSaverAnimationOptions *pOptions)
{
  if(strFilename.size()>= 3 && _stricmp(strFilename.substr(strFilename.size()-3,3).c_str(),Qun::ANIMATION_XMLFILE_MAGIC)==0)
	 return saveXmlCoreAnimation(strFilename, pCoreAnimation);	

  // open the file
  std::ofstream file;
  file.open(strFilename.c_str(), std::ios::out | std::ios::binary);
  if(!file)
  {
    QunError::setLastError(QunError::FILE_CREATION_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write magic tag
  if(!QunPlatform::writeBytes(file, &Qun::ANIMATION_FILE_MAGIC, sizeof(Qun::ANIMATION_FILE_MAGIC)))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write version info
  if(!QunPlatform::writeInteger(file, Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the duration of the core animation
  if(!QunPlatform::writeFloat(file, pCoreAnimation->getDuration()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // get core track list
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // write the number of tracks
  if(!QunPlatform::writeInteger(file, listCoreTrack.size()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return 0;
  }

	if (pOptions)
		pOptions->duration = pCoreAnimation->getDuration();

	// write flags
	int flags = 0;
	if (pOptions && pOptions->bCompressKeyframes == true)
		flags |= 1;

  if(!QunPlatform::writeInteger(file, flags))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return 0;
  }

  // write all core bones
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
  {
    // save core track
    if(!saveCoreTrack(file, strFilename, *iteratorCoreTrack, pOptions))
    {
      return false;
    }
  }

  // explicitly close the file
  file.close();

  pCoreAnimation->setFilename(strFilename);

  return true;
}

 /*****************************************************************************/
/** Saves a core bone instance.
  *
  * This function saves a core bone instance to a file stream.
  *
  * @param file The file stream to save the core bone instance to.
  * @param strFilename The name of the file stream.
  * @param pCoreBone A pointer to the core bone instance that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreBones(std::ofstream& file, const std::string& strFilename, QunCoreBone *pCoreBone)
{
  if(!file)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the name of the bone
  if(!QunPlatform::writeString(file, pCoreBone->getName()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the translation of the bone
  const QunVector& translation = pCoreBone->getTranslation();
  QunPlatform::writeFloat(file, translation[0]);
  QunPlatform::writeFloat(file, translation[1]);
  QunPlatform::writeFloat(file, translation[2]);

  // write the rotation of the bone
  const QunQuaternion& rotation = pCoreBone->getRotation();
  QunPlatform::writeFloat(file, rotation[0]);
  QunPlatform::writeFloat(file, rotation[1]);
  QunPlatform::writeFloat(file, rotation[2]);
  QunPlatform::writeFloat(file, rotation[3]);

  // write the translation of the bone
  const QunVector& translationBoneSpace = pCoreBone->getTranslationBoneSpace();
  QunPlatform::writeFloat(file, translationBoneSpace[0]);
  QunPlatform::writeFloat(file, translationBoneSpace[1]);
  QunPlatform::writeFloat(file, translationBoneSpace[2]);

  // write the rotation of the bone
  const QunQuaternion& rotationBoneSpace = pCoreBone->getRotationBoneSpace();
  QunPlatform::writeFloat(file, rotationBoneSpace[0]);
  QunPlatform::writeFloat(file, rotationBoneSpace[1]);
  QunPlatform::writeFloat(file, rotationBoneSpace[2]);
  QunPlatform::writeFloat(file, rotationBoneSpace[3]);

  // write the parent bone id
  if(!QunPlatform::writeInteger(file, pCoreBone->getParentId()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // get children list
  std::list<int>& listChildId = pCoreBone->getListChildId();

  // write the number of children
  if(!QunPlatform::writeInteger(file, listChildId.size()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write all children ids
  std::list<int>::iterator iteratorChildId;
  for(iteratorChildId = listChildId.begin(); iteratorChildId != listChildId.end(); ++iteratorChildId)
  {
    // write the child id
    if(!QunPlatform::writeInteger(file, *iteratorChildId))
    {
      QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
      return false;
    }
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core keyframe instance.
  *
  * This function saves a core keyframe instance to a file stream.
  *
  * @param file The file stream to save the core keyframe instance to.
  * @param strFilename The name of the file stream.
  * @param pCoreKeyframe A pointer to the core keyframe instance that should be
  *                      saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreKeyframe(std::ofstream& file, const std::string& strFilename, QunCoreKeyframe *pCoreKeyframe)
{
  if(!file)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the time of the keyframe
  QunPlatform::writeFloat(file, pCoreKeyframe->getTime());

  // write the translation of the keyframe
  const QunVector& translation = pCoreKeyframe->getTranslation();
  QunPlatform::writeFloat(file, translation[0]);
  QunPlatform::writeFloat(file, translation[1]);
  QunPlatform::writeFloat(file, translation[2]);

  // write the rotation of the keyframe
  const QunQuaternion& rotation = pCoreKeyframe->getRotation();
  QunPlatform::writeFloat(file, rotation[0]);
  QunPlatform::writeFloat(file, rotation[1]);
  QunPlatform::writeFloat(file, rotation[2]);
  QunPlatform::writeFloat(file, rotation[3]);

  // check if an error happend
  if(!file)
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  return true;
}

bool QunSaver::saveCompressedCoreKeyframe(std::ofstream& file, const std::string& strFilename, QunCoreKeyframe* pCoreKeyframe, QunSaverAnimationOptions *pOptions)
{
  if(!file)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the time of the keyframe
	int time = int(pCoreKeyframe->getTime() / pOptions->duration * 65535.0f);
	if(time > 65535)
		time = 65535;
  QunPlatform::writeShort(file, time);

  // write the translation of the keyframe
  const QunVector &translation = pCoreKeyframe->getTranslation();

	const QunVector &minp = pOptions->keyframe_min;
	const QunVector &scale = pOptions->keyframe_scale;

	int px = int((translation.x - minp.x) * scale.x);
	int py = int((translation.y - minp.y) * scale.y);
	int pz = int((translation.z - minp.z) * scale.z);

	if(px > 2047)
		px = 2047;
	if(py > 2047)
		py = 2047;
	if(pz > 1023)
		pz = 1023;

	int towrite = px + (py << 11) + (pz << 22);
  QunPlatform::writeInteger(file, towrite);

  // write the compressed rotation of the keyframe
  QunQuaternion rotation = pCoreKeyframe->getRotation();
	short s0, s1, s2;
	rotation.compress(s0, s1, s2);

	QunPlatform::writeShort(file, s0);
	QunPlatform::writeShort(file, s1);
	QunPlatform::writeShort(file, s2);

  // check if an error happend
  if(!file)
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core material instance.
  *
  * This function saves a core material instance to a file.
  *
  * @param strFilename The name of the file to save the core material instance
  *                    to.
  * @param pCoreMaterial A pointer to the core material instance that should
  *                      be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreMaterial(const std::string& strFilename, QunCoreMaterial *pCoreMaterial)
{
  if(strFilename.size()>= 3 && _stricmp(strFilename.substr(strFilename.size()-3,3).c_str(),Qun::MATERIAL_XMLFILE_MAGIC)==0)
    return saveXmlCoreMaterial(strFilename, pCoreMaterial);	

  // open the file
  std::ofstream file;
  file.open(strFilename.c_str(), std::ios::out | std::ios::binary);
  if(!file)
  {
    QunError::setLastError(QunError::FILE_CREATION_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write magic tag
  if(!QunPlatform::writeBytes(file, &Qun::MATERIAL_FILE_MAGIC, sizeof(Qun::MATERIAL_FILE_MAGIC)))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write version info
  if(!QunPlatform::writeInteger(file, Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the ambient color
  QunCoreMaterial::Color ambientColor;
  ambientColor = pCoreMaterial->getAmbientColor();
  QunPlatform::writeBytes(file, &ambientColor, sizeof(ambientColor));

  // write the diffuse color
  QunCoreMaterial::Color diffusetColor;
  diffusetColor = pCoreMaterial->getDiffuseColor();
  QunPlatform::writeBytes(file, &diffusetColor, sizeof(diffusetColor));

  // write the specular color
  QunCoreMaterial::Color specularColor;
  specularColor = pCoreMaterial->getSpecularColor();
  QunPlatform::writeBytes(file, &specularColor, sizeof(specularColor));

  // write the shininess factor
  QunPlatform::writeFloat(file, pCoreMaterial->getShininess());

  // check if an error happend
  if(!file)
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // get the map vector
  std::vector<QunCoreMaterial::Map>& vectorMap = pCoreMaterial->getVectorMap();

  // write the number of maps
  if(!QunPlatform::writeInteger(file, vectorMap.size()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write all maps
  int mapId;
  for(mapId = 0; mapId < (int)vectorMap.size(); ++mapId)
  {
    QunCoreMaterial::Map& map = vectorMap[mapId];

    // write the filename of the map
    if(!QunPlatform::writeString(file, map.strFilename))
    {
      QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
      return false;
    }
  }

  // explicitly close the file
  file.close();

  pCoreMaterial->setFilename(strFilename);

  return true;
}

 /*****************************************************************************/
/** Saves a core mesh instance.
  *
  * This function saves a core mesh instance to a file.
  *
  * @param strFilename The name of the file to save the core mesh instance to.
  * @param pCoreMesh A pointer to the core mesh instance that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreMesh(const std::string& strFilename, QunCoreMesh *pCoreMesh)
{
  if(strFilename.size()>= 3 && _stricmp(strFilename.substr(strFilename.size()-3,3).c_str(),Qun::MESH_XMLFILE_MAGIC)==0)
    return saveXmlCoreMesh(strFilename, pCoreMesh);

  // open the file
  std::ofstream file;
  file.open(strFilename.c_str(), std::ios::out | std::ios::binary);
  if(!file)
  {
    QunError::setLastError(QunError::FILE_CREATION_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write magic tag
  if(!QunPlatform::writeBytes(file, &Qun::MESH_FILE_MAGIC, sizeof(Qun::MESH_FILE_MAGIC)))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write version info
  if(!QunPlatform::writeInteger(file, Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // get the submesh vector
  std::vector<QunCoreSubmesh *>& vectorCoreSubmesh = pCoreMesh->getVectorCoreSubmesh();

  // write the number of submeshes
  if(!QunPlatform::writeInteger(file, vectorCoreSubmesh.size()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write all core submeshes
  int submeshId;
  for(submeshId = 0; submeshId < (int)vectorCoreSubmesh.size(); ++submeshId)
  {
    // write the core submesh
    if(!saveCoreSubmesh(file, strFilename, vectorCoreSubmesh[submeshId]))
    {
      return false;
    }
  }

  // explicitly close the file
  file.close();

  pCoreMesh->setFilename(strFilename);

  return true;
}

 /*****************************************************************************/
/** Saves a core skeleton instance.
  *
  * This function saves a core skeleton instance to a file.
  *
  * @param strFilename The name of the file to save the core skeleton instance
  *                    to.
  * @param pCoreSkeleton A pointer to the core skeleton instance that should be
  *                      saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreSkeleton(const std::string& strFilename, QunCoreSkeleton *pCoreSkeleton)
{
  if(strFilename.size()>= 3 && _stricmp(strFilename.substr(strFilename.size()-3,3).c_str(),Qun::SKELETON_XMLFILE_MAGIC)==0)
    return saveXmlCoreSkeleton(strFilename, pCoreSkeleton);	

  // open the file
  std::ofstream file;
  file.open(strFilename.c_str(), std::ios::out | std::ios::binary);
  if(!file)
  {
    QunError::setLastError(QunError::FILE_CREATION_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write magic tag
  if(!QunPlatform::writeBytes(file, &Qun::SKELETON_FILE_MAGIC, sizeof(Qun::SKELETON_FILE_MAGIC)))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write version info
  if(!QunPlatform::writeInteger(file, Qun::CURRENT_FILE_VERSION))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the number of bones
  if(!QunPlatform::writeInteger(file, pCoreSkeleton->getVectorCoreBone().size()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write all core bones
  int boneId;
  for(boneId = 0; boneId < (int)pCoreSkeleton->getVectorCoreBone().size(); ++boneId)
  {
    // write the core bone
    if(!saveCoreBones(file, strFilename, pCoreSkeleton->getCoreBone(boneId)))
    {
      return false;
    }
  }

  // explicitly close the file
  file.close();

  return true;
}

 /*****************************************************************************/
/** Saves a core submesh instance.
  *
  * This function saves a core submesh instance to a file stream.
  *
  * @param file The file stream to save the core submesh instance to.
  * @param strFilename The name of the file stream.
  * @param pCoreSubmesh A pointer to the core submesh instance that should be
  *                     saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreSubmesh(std::ofstream& file, const std::string& strFilename, QunCoreSubmesh *pCoreSubmesh)
{
  if(!file)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the core material thread id
  if(!QunPlatform::writeInteger(file, pCoreSubmesh->getCoreMaterialThreadId()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // get the vertex, face, physical property and spring vector
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pCoreSubmesh->getVectorVertex();
  std::vector<QunCoreSubmesh::Face>& vectorFace = pCoreSubmesh->getVectorFace();
  std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pCoreSubmesh->getVectorPhysicalProperty();
  std::vector<QunCoreSubmesh::Spring>& vectorSpring = pCoreSubmesh->getVectorSpring();

  // write the number of vertices, faces, level-of-details and springs
  QunPlatform::writeInteger(file, vectorVertex.size());
  QunPlatform::writeInteger(file, vectorFace.size());
  QunPlatform::writeInteger(file, pCoreSubmesh->getLodCount());
  QunPlatform::writeInteger(file, pCoreSubmesh->getSpringCount());

  // get the texture coordinate vector vector
  std::vector<std::vector<QunCoreSubmesh::TextureCoordinate> >& vectorvectorTextureCoordinate = pCoreSubmesh->getVectorVectorTextureCoordinate();

  // write the number of texture coordinates per vertex
  QunPlatform::writeInteger(file, vectorvectorTextureCoordinate.size());

  // check if an error happend
  if(!file)
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write all vertices
  int vertexId;
  for(vertexId = 0; vertexId < (int)vectorVertex.size(); ++vertexId)
  {
    QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

    // write the vertex data
    QunPlatform::writeFloat(file, vertex.position.x);
    QunPlatform::writeFloat(file, vertex.position.y);
    QunPlatform::writeFloat(file, vertex.position.z);
    QunPlatform::writeFloat(file, vertex.normal.x);
    QunPlatform::writeFloat(file, vertex.normal.y);
    QunPlatform::writeFloat(file, vertex.normal.z);
    QunPlatform::writeInteger(file, vertex.collapseId);
    QunPlatform::writeInteger(file, vertex.faceCollapseCount);

    // write all texture coordinates of this vertex
    int textureCoordinateId;
    for(textureCoordinateId = 0; textureCoordinateId < (int)vectorvectorTextureCoordinate.size(); ++textureCoordinateId)
    {
      QunCoreSubmesh::TextureCoordinate& textureCoordinate = vectorvectorTextureCoordinate[textureCoordinateId][vertexId];

      // write the influence data
      QunPlatform::writeFloat(file, textureCoordinate.u);
      QunPlatform::writeFloat(file, textureCoordinate.v);

      // check if an error happend
      if(!file)
      {
        QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
        return false;
      }
    }

    // write the number of influences
    if(!QunPlatform::writeInteger(file, vertex.vectorInfluence.size()))
    {
      QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
      return false;
    }

     // write all influences of this vertex
    int influenceId;
    for(influenceId = 0; influenceId < (int)vertex.vectorInfluence.size(); ++influenceId)
    {
      QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];

      // write the influence data
      QunPlatform::writeInteger(file, influence.boneId);
      QunPlatform::writeFloat(file, influence.weight);

      // check if an error happend
      if(!file)
      {
        QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
        return false;
      }
    }

    // save the physical property of the vertex if there are springs in the core submesh
    if(pCoreSubmesh->getSpringCount() > 0)
    {
      // write the physical property of this vertex if there are springs in the core submesh
      QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

      // write the physical property data
      QunPlatform::writeFloat(file, physicalProperty.weight);

      // check if an error happend
      if(!file)
      {
        QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
        return false;
      }
    }
  }

  // write all springs
  int springId;
  for(springId = 0; springId < (int)pCoreSubmesh->getSpringCount(); ++springId)
  {
    QunCoreSubmesh::Spring& spring = vectorSpring[springId];

    // write the spring data
    QunPlatform::writeInteger(file, spring.vertexId[0]);
    QunPlatform::writeInteger(file, spring.vertexId[1]);
    QunPlatform::writeFloat(file, spring.springCoefficient);
    QunPlatform::writeFloat(file, spring.idleLength);

    // check if an error happend
    if(!file)
    {
      QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
      return false;
    }
  }

  // write all faces
  int faceId;
  for(faceId = 0; faceId < (int)vectorFace.size(); ++faceId)
  {
    QunCoreSubmesh::Face& face = vectorFace[faceId];

    // write the face data
    QunPlatform::writeInteger(file, face.vertexId[0]);
    QunPlatform::writeInteger(file, face.vertexId[1]);
    QunPlatform::writeInteger(file, face.vertexId[2]);

    // check if an error happend
    if(!file)
    {
      QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
      return false;
    }
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core track instance.
  *
  * This function saves a core track instance to a file stream.
  *
  * @param file The file stream to save the core track instance to.
  * @param strFilename The name of the file stream.
  * @param pCoreTrack A pointer to the core track instance that should be saved.
	* @parAM pOptions Optional pointer to save options.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveCoreTrack(std::ofstream& file, const std::string& strFilename, QunCoreTrack *pCoreTrack, QunSaverAnimationOptions *pOptions)
{
  if(!file)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the bone id
  if(!QunPlatform::writeInteger(file, pCoreTrack->getCoreBoneId()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  // write the number of keyframes
  if(!QunPlatform::writeInteger(file, pCoreTrack->getCoreKeyframeCount()))
  {
    QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

	if(pOptions && pOptions->bCompressKeyframes == true) {

		QunVector minp(FLT_MAX, FLT_MAX, FLT_MAX);
		QunVector maxp(-FLT_MAX, -FLT_MAX, -FLT_MAX);

		int nbKeys = pCoreTrack->getCoreKeyframeCount();
		for(int i = 0; i < nbKeys; i++) {
			QunCoreKeyframe *kf = pCoreTrack->getCoreKeyframe(i);
			const QunVector &pos = kf->getTranslation();

			if(pos.x < minp.x)
				minp.x = pos.x;
			if(pos.x > maxp.x)
				maxp.x = pos.x;

			if(pos.y < minp.y)
				minp.y = pos.y;
			if(pos.y > maxp.y)
				maxp.y = pos.y;

			if(pos.z < minp.z)
				minp.z = pos.z;
			if(pos.z > maxp.z)
				maxp.z = pos.z;
		}

		float dx = maxp.x - minp.x;
		float dy = maxp.y - minp.y;
		float dz = maxp.z - minp.z;

		float factorx = 0, factory = 0, factorz = 0;
		if(dx != 0)
			factorx = 1.0f / dx * 2047.0f;

		if(dy != 0)
			factory = 1.0f / dy * 2047.0f;

		if(dz != 0)
			factorz = 1.0f / dz * 1023.0f;

		pOptions->keyframe_min = minp;
		pOptions->keyframe_scale = QunVector(factorx, factory, factorz);

		QunPlatform::writeFloat(file, minp.x);
		QunPlatform::writeFloat(file, minp.y);
		QunPlatform::writeFloat(file, minp.z);
		QunPlatform::writeFloat(file, 1.0f / 2047 * dx);
		QunPlatform::writeFloat(file, 1.0f / 2047 * dy);
		QunPlatform::writeFloat(file, 1.0f / 1023 * dz);
	}

  // save all core keyframes
  for(int i = 0; i < pCoreTrack->getCoreKeyframeCount(); ++i)
  {
    // save the core keyframe
		bool res;
		if(pOptions && pOptions->bCompressKeyframes)
		{
			res = saveCompressedCoreKeyframe(file, strFilename, pCoreTrack->getCoreKeyframe(i), pOptions);
		}
		else 
		{
			res = saveCoreKeyframe(file, strFilename, pCoreTrack->getCoreKeyframe(i));
		}

		if(!res) {
      return false;
    }
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core skeleton instance to a XML file
  *
  * This function saves a core skeleton instance to a XML file.
  *
  * @param strFilename The name of the file to save the core skeleton instance
  *                    to.
  * @param pCoreSkeleton A pointer to the core skeleton instance that should be
  *                      saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveXmlCoreSkeleton(const std::string& strFilename, QunCoreSkeleton *pCoreSkeleton)
{
  std::stringstream str;

  TiXmlDocument doc(strFilename);  


  TiXmlElement skeleton("SKELETON");
  //skeleton.SetAttribute("MAGIC",Qun::SKELETON_XMLFILE_MAGIC);
  skeleton.SetAttribute("VERSION",Qun::LIBRARY_VERSION);

  skeleton.SetAttribute("NUMBONES",pCoreSkeleton->getVectorCoreBone().size());
  


  int boneId;
  for(boneId = 0; boneId < (int)pCoreSkeleton->getVectorCoreBone().size(); ++boneId)
  {
	  QunCoreBone* pCoreBone=pCoreSkeleton->getCoreBone(boneId);

	  TiXmlElement bone("BONE");	  
	  bone.SetAttribute("ID",boneId);
	  bone.SetAttribute("NAME",pCoreBone->getName());
	  bone.SetAttribute("NUMCHILDS",pCoreBone->getListChildId().size());

	  TiXmlElement translation("TRANSLATION");
	  const QunVector& translationVector = pCoreBone->getTranslation();
      

      str.str("");
      str << translationVector.x << " " 
    	  << translationVector.y << " "
	      << translationVector.z;
  
      TiXmlText translationdata(str.str());  

      translation.InsertEndChild(translationdata);
      bone.InsertEndChild(translation);


	  TiXmlElement rotation("ROTATION");
	  const QunQuaternion& rotationQuad = pCoreBone->getRotation();  
      

      str.str("");
      str << rotationQuad.x << " " 
    	  << rotationQuad.y << " "
		  << rotationQuad.z << " "
	      << rotationQuad.w;
  
      TiXmlText rotationdata(str.str());
      rotation.InsertEndChild(rotationdata);
      bone.InsertEndChild(rotation);


	  TiXmlElement localtranslation("LOCALTRANSLATION");
	  const QunVector& localtranslationVector = pCoreBone->getTranslationBoneSpace();      

      str.str("");
      str << localtranslationVector.x << " " 
    	  << localtranslationVector.y << " "
	      << localtranslationVector.z;
  
      TiXmlText localtranslationdata(str.str()); 

      localtranslation.InsertEndChild(localtranslationdata);
      bone.InsertEndChild(localtranslation);


	  TiXmlElement localrotation("LOCALROTATION");
	  const QunQuaternion& localrotationQuad = pCoreBone->getRotationBoneSpace();        

      str.str("");
      str << localrotationQuad.x << " " 
    	  << localrotationQuad.y << " "
		  << localrotationQuad.z << " "
	      << localrotationQuad.w;
  
      TiXmlText localrotationdata(str.str());
      localrotation.InsertEndChild(localrotationdata);
      bone.InsertEndChild(localrotation);


	  TiXmlElement parent("PARENTID");
	  str.str("");
      str << pCoreBone->getParentId();
	  TiXmlText parentid(str.str());
	  parent.InsertEndChild(parentid);
      bone.InsertEndChild(parent);


	  // get children list
      std::list<int>& listChildId = pCoreBone->getListChildId();


	  // write all children ids
      std::list<int>::iterator iteratorChildId;
      for(iteratorChildId = listChildId.begin(); iteratorChildId != listChildId.end(); ++iteratorChildId)
	  {
		  TiXmlElement child("CHILDID");
		  str.str("");
		  //int id=*iteratorChildId;
          str << *iteratorChildId;
	      TiXmlText childid(str.str());
		  child.InsertEndChild(childid);
          bone.InsertEndChild(child);
	  }
	  skeleton.InsertEndChild(bone);

  }
  doc.InsertEndChild(skeleton);
  
  if(!doc.SaveFile())
  {
	QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }
  return true;
}

 /*****************************************************************************/
/** Saves a core animation instance in a XML file.
  *
  * This function saves a core animation instance to a XML file.
  *
  * @param strFilename The name of the file to save the core animation instance
  *                    to.
  * @param pCoreAnimation A pointer to the core animation instance that should
  *                       be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveXmlCoreAnimation(const std::string& strFilename, QunCoreAnimation *pCoreAnimation)
{
	std::stringstream str;

	TiXmlDocument doc(strFilename);

	TiXmlElement animation("ANIMATION");
	//animation.SetAttribute("MAGIC",Qun::ANIMATION_XMLFILE_MAGIC);
	animation.SetAttribute("VERSION",Qun::LIBRARY_VERSION);

	str.str("");
	str << pCoreAnimation->getDuration();	
	animation.SetAttribute("DURATION",str.str());
	animation.SetAttribute("NUMTRACKS", pCoreAnimation->getTrackCount());

	// get core track list
	std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

	// write all core bones
	std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
	for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
	{
		QunCoreTrack *pCoreTrack=*iteratorCoreTrack;

		TiXmlElement track("TRACK");
		track.SetAttribute("BONEID",pCoreTrack->getCoreBoneId());

		track.SetAttribute("NUMKEYFRAMES",pCoreTrack->getCoreKeyframeCount());

		// save all core keyframes
		for (int i = 0; i < pCoreTrack->getCoreKeyframeCount(); ++i)
		{
			QunCoreKeyframe *pCoreKeyframe=pCoreTrack->getCoreKeyframe(i);

			TiXmlElement keyframe("KEYFRAME");

			str.str("");
			str << pCoreKeyframe->getTime();	        
			keyframe.SetAttribute("TIME",str.str());

			TiXmlElement translation("TRANSLATION");
			const QunVector& translationVector = pCoreKeyframe->getTranslation();

			str.str("");
			str << translationVector.x << " "
				<< translationVector.y << " "
				<< translationVector.z;

			TiXmlText translationdata(str.str());  

			translation.InsertEndChild(translationdata);
			keyframe.InsertEndChild(translation);

			TiXmlElement rotation("ROTATION");
			const QunQuaternion& rotationQuad = pCoreKeyframe->getRotation();  

			str.str("");
			str << rotationQuad.x << " " 
				<< rotationQuad.y << " "
				<< rotationQuad.z << " "
				<< rotationQuad.w;

			TiXmlText rotationdata(str.str());
			rotation.InsertEndChild(rotationdata);
			keyframe.InsertEndChild(rotation);

			track.InsertEndChild(keyframe);
		}

		animation.InsertEndChild(track);
	}

	doc.InsertEndChild(animation);

	if(!doc.SaveFile())
	{
		QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
		return false;
	} 

	return true;
}


 /*****************************************************************************/
/** Saves a core mesh instance in a XML file.
  *
  * This function saves a core mesh instance to a XML file.
  *
  * @param strFilename The name of the file to save the core mesh instance to.
  * @param pCoreMesh A pointer to the core mesh instance that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveXmlCoreMesh(const std::string& strFilename, QunCoreMesh *pCoreMesh)
{

	std::stringstream str;

    TiXmlDocument doc(strFilename);    
	

	TiXmlElement mesh("MESH");
	//mesh.SetAttribute("MAGIC",Qun::MESH_XMLFILE_MAGIC);
	mesh.SetAttribute("VERSION",Qun::LIBRARY_VERSION);
	mesh.SetAttribute("NUMSUBMESH",pCoreMesh->getCoreSubmeshCount());

	// get the submesh vector
	std::vector<QunCoreSubmesh *>& vectorCoreSubmesh = pCoreMesh->getVectorCoreSubmesh();

	// write all core submeshes
	int submeshId;
	for(submeshId = 0; submeshId < (int)vectorCoreSubmesh.size(); ++submeshId)
	{
		QunCoreSubmesh *pCoreSubmesh=vectorCoreSubmesh[submeshId];

		TiXmlElement submesh("SUBMESH");

		submesh.SetAttribute("NUMVERTICES",pCoreSubmesh->getVertexCount());
		submesh.SetAttribute("NUMFACES",pCoreSubmesh->getFaceCount());		
		submesh.SetAttribute("MATERIAL",pCoreSubmesh->getCoreMaterialThreadId());
		submesh.SetAttribute("NUMLODSTEPS",pCoreSubmesh->getLodCount());
		submesh.SetAttribute("NUMSPRINGS",pCoreSubmesh->getSpringCount());
		
		submesh.SetAttribute("NUMTEXCOORDS",pCoreSubmesh->getVectorVectorTextureCoordinate().size());

		
		// get the vertex, face, physical property and spring vector
		std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pCoreSubmesh->getVectorVertex();
		std::vector<QunCoreSubmesh::Face>& vectorFace = pCoreSubmesh->getVectorFace();
		std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pCoreSubmesh->getVectorPhysicalProperty();
		std::vector<QunCoreSubmesh::Spring>& vectorSpring = pCoreSubmesh->getVectorSpring();

		// get the texture coordinate vector vector
        std::vector<std::vector<QunCoreSubmesh::TextureCoordinate> >& vectorvectorTextureCoordinate = pCoreSubmesh->getVectorVectorTextureCoordinate();

		// write all vertices
		int vertexId;
		for(vertexId = 0; vertexId < (int)vectorVertex.size(); ++vertexId)
		{
			QunCoreSubmesh::Vertex& Vertex = vectorVertex[vertexId];

			TiXmlElement vertex("VERTEX");
			vertex.SetAttribute("ID",vertexId);
			vertex.SetAttribute("NUMINFLUENCES",Vertex.vectorInfluence.size());

			// write the vertex data

			TiXmlElement position("POS");
			
			str.str("");
			str << Vertex.position.x << " "
				<< Vertex.position.y << " "
				<< Vertex.position.z;

			TiXmlText positiondata(str.str());  

			position.InsertEndChild(positiondata);
			vertex.InsertEndChild(position);

			TiXmlElement normal("NORM");
			
			str.str("");
			str << Vertex.normal.x << " "
				<< Vertex.normal.y << " "
				<< Vertex.normal.z;

			TiXmlText normaldata(str.str());  

			normal.InsertEndChild(normaldata);
			vertex.InsertEndChild(normal);

			if(Vertex.collapseId!=-1)
			{
				TiXmlElement collapse("COLLAPSEID");
				str.str("");
				str << Vertex.collapseId;
				TiXmlText collapseid(str.str());
				collapse.InsertEndChild(collapseid);
				vertex.InsertEndChild(collapse);

				TiXmlElement collapsecount("COLLAPSECOUNT");
				str.str("");
				str << Vertex.faceCollapseCount;
				TiXmlText collapsecountdata(str.str());
				collapsecount.InsertEndChild(collapsecountdata);
				vertex.InsertEndChild(collapsecount);
			}

			// write all texture coordinates of this vertex
			int textureCoordinateId;
			for(textureCoordinateId = 0; textureCoordinateId < (int)vectorvectorTextureCoordinate.size(); ++textureCoordinateId)
			{
				QunCoreSubmesh::TextureCoordinate& textureCoordinate = vectorvectorTextureCoordinate[textureCoordinateId][vertexId];

				TiXmlElement tex("TEXCOORD");
				
				str.str("");
				str << textureCoordinate.u << " "
					<< textureCoordinate.v;

				TiXmlText texdata(str.str());

				tex.InsertEndChild(texdata);

				vertex.InsertEndChild(tex);
			}

			// write all influences of this vertex
			int influenceId;
			for(influenceId = 0; influenceId < (int)Vertex.vectorInfluence.size(); ++influenceId)
			{
				QunCoreSubmesh::Influence& Influence = Vertex.vectorInfluence[influenceId];

				TiXmlElement influence("INFLUENCE");

				influence.SetAttribute("ID",Influence.boneId);

				str.str("");
				str << Influence.weight;

				TiXmlText influencedata(str.str());

				influence.InsertEndChild(influencedata);
				vertex.InsertEndChild(influence);
			}

			// save the physical property of the vertex if there are springs in the core submesh
			if(pCoreSubmesh->getSpringCount() > 0)
			{
				// write the physical property of this vertex if there are springs in the core submesh
				QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

				TiXmlElement physique("PHYSIQUE");

				str.str("");
				str << physicalProperty.weight;
				TiXmlText physiquedata(str.str());
				physique.InsertEndChild(physiquedata);
				vertex.InsertEndChild(physique);
			}

			submesh.InsertEndChild(vertex);
		}

		// write all springs
        int springId;
        for(springId = 0; springId < (int)pCoreSubmesh->getSpringCount(); ++springId)
		{
            QunCoreSubmesh::Spring& Spring = vectorSpring[springId];
			
			TiXmlElement spring("SPRING");			

			str.str("");
			str << Spring.vertexId[0]<< " "
				<< Spring.vertexId[1];
			spring.SetAttribute("VERTEXID",str.str());

			
			str.str("");
			str << Spring.springCoefficient;
			spring.SetAttribute("COEF",str.str());	
			
			str.str("");
			str << Spring.idleLength;				
			spring.SetAttribute("LENGTH",str.str());
			
			submesh.InsertEndChild(spring);
		}

		// write all faces
		int faceId;
		for(faceId = 0; faceId < (int)vectorFace.size(); ++faceId)
		{
			QunCoreSubmesh::Face& Face = vectorFace[faceId];

			TiXmlElement face("FACE");

			str.str("");
			str << Face.vertexId[0]<< " "
				<< Face.vertexId[1]<< " "
				<< Face.vertexId[2];
			face.SetAttribute("VERTEXID",str.str());
			submesh.InsertEndChild(face);
		}

		mesh.InsertEndChild(submesh);
		
     }
	 doc.InsertEndChild(mesh);


	 if(!doc.SaveFile())
	 {
		 QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
         return false;
	 }

  return true;
}



 /*****************************************************************************/
/** Saves a core material instance to a XML file.
  *
  * This function saves a core material instance to a XML file.
  *
  * @param strFilename The name of the file to save the core material instance
  *                    to.
  * @param pCoreMaterial A pointer to the core material instance that should
  *                      be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunSaver::saveXmlCoreMaterial(const std::string& strFilename, QunCoreMaterial *pCoreMaterial)
{
  std::stringstream str;

  TiXmlDocument doc(strFilename);

  TiXmlElement material("MATERIAL");
  //material.SetAttribute("MAGIC",Qun::MATERIAL_XMLFILE_MAGIC);
  material.SetAttribute("VERSION",Qun::LIBRARY_VERSION);

  material.SetAttribute("NUMMAPS",pCoreMaterial->getVectorMap().size());
  
  TiXmlElement ambient("AMBIENT");

  QunCoreMaterial::Color ambientColor;
  ambientColor = pCoreMaterial->getAmbientColor();


  str.str("");
  str << (int)ambientColor.red << " " 
	  << (int)ambientColor.green << " "
	  << (int)ambientColor.blue << " "
	  << (int)ambientColor.alpha;
  
  TiXmlText ambientdata(str.str());
  

  ambient.InsertEndChild(ambientdata);
  material.InsertEndChild(ambient);

  TiXmlElement diffuse("DIFFUSE");

  QunCoreMaterial::Color diffuseColor;
  diffuseColor = pCoreMaterial->getDiffuseColor();
  
  str.str("");
  str << (int)diffuseColor.red << " " 
	  << (int)diffuseColor.green << " "
	  << (int)diffuseColor.blue << " "
	  << (int)diffuseColor.alpha;
  
  TiXmlText diffusedata(str.str());

  
  diffuse.InsertEndChild(diffusedata);
  material.InsertEndChild(diffuse);

  TiXmlElement specular("SPECULAR");

  QunCoreMaterial::Color specularColor;
  specularColor = pCoreMaterial->getSpecularColor();

  str.str("");
  str << (int)specularColor.red << " " 
	  << (int)specularColor.green << " "
	  << (int)specularColor.blue << " "
	  << (int)specularColor.alpha;
  
  TiXmlText speculardata(str.str());

  specular.InsertEndChild(speculardata);
  material.InsertEndChild(specular);

  TiXmlElement shininess("SHININESS");

  str.str("");
  str << pCoreMaterial->getShininess();    

  TiXmlText shininessdata(str.str());

  shininess.InsertEndChild(shininessdata);
  material.InsertEndChild(shininess);  

  std::vector<QunCoreMaterial::Map>& vectorMap = pCoreMaterial->getVectorMap();
  
  int mapId;
  for(mapId = 0; mapId < (int)vectorMap.size(); ++mapId)
  {
	  TiXmlElement map("MAP");
	  TiXmlText mapdata(vectorMap[mapId].strFilename);
	  map.InsertEndChild(mapdata);
      material.InsertEndChild(map);
  }

  doc.InsertEndChild(material);

  if(!doc.SaveFile())
  {
	QunError::setLastError(QunError::FILE_WRITING_FAILED, __FILE__, __LINE__, strFilename);
    return false;
  }

  return true;

}
//****************************************************************************//
