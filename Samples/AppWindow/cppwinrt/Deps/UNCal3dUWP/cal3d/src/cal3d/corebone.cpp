//****************************************************************************//
// corebone.cpp                                                               //
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

#include "cal3d/error.h"
#include "cal3d/corebone.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coremodel.h"
#include "cal3d/coremesh.h"
#include "cal3d/coresubmesh.h"

 /*****************************************************************************/
/** Constructs the core bone instance.
  *
  * This function is the default constructor of the core bone instance.
  *****************************************************************************/

QunCoreBone::QunCoreBone(const std::string& name)
  : m_strName(name)
  , m_pCoreSkeleton(0)
  , m_parentId(-1)
  , m_userData(0)
  , m_boundingBoxPrecomputed(false)
{
}

 /*****************************************************************************/
/** Adds a child ID.
  *
  * This function adds a core bone ID to the child ID list of the core bone
  * instance.
  *
  * @param childId The ID of the core bone ID that shoud be added to the child
  *                ID list.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunCoreBone::addChildId(int childId)
{
  m_listChildId.push_back(childId);

  return true;
}

 /*****************************************************************************/
/** Qunculates the current state.
  *
  * This function calculates the current state (absolute translation and
  * rotation) of the core bone instance and all its children.
  *****************************************************************************/

void QunCoreBone::calculateState()
{
  if(m_parentId == -1)
  {
    // no parent, this means absolute state == relative state
    m_translationAbsolute = m_translation;
    m_rotationAbsolute = m_rotation;
  }
  else
  {
    // get the parent bone
    QunCoreBone *pParent;
    pParent = m_pCoreSkeleton->getCoreBone(m_parentId);

    // transform relative state with the absolute state of the parent
    m_translationAbsolute = m_translation;
    m_translationAbsolute *= pParent->getRotationAbsolute();
    m_translationAbsolute += pParent->getTranslationAbsolute();

	m_rotationAbsolute = m_rotation;
	m_rotationAbsolute *= pParent->getRotationAbsolute();
  }

  // calculate all child bones
  std::list<int>::iterator iteratorChildId;
  for(iteratorChildId = m_listChildId.begin(); iteratorChildId != m_listChildId.end(); ++iteratorChildId)
  {
    m_pCoreSkeleton->getCoreBone(*iteratorChildId)->calculateState();
  }
}

 /*****************************************************************************/
/** Returns the child ID list.
  *
  * This function returns the list that contains all child IDs of the core bone
  * instance.
  *
  * @return A reference to the child ID list.
  *****************************************************************************/

std::list<int>& QunCoreBone::getListChildId()
{
  return m_listChildId;
}

 /*****************************************************************************/
/** Returns the name.
  *
  * This function returns the name of the core bone instance.
  *
  * @return The name as string.
  *****************************************************************************/

const std::string& QunCoreBone::getName() const
{
  return m_strName;
}


 /*****************************************************************************/
/** Sets the name.
  *
  * This function sets the name of the core bone instance.
  *
  * @param strName A string that should be used as the name of the core bone
  *                instance.
  *
  *****************************************************************************/
void QunCoreBone::setName( const std::string& name )
{
	m_strName = name;
}


 /*****************************************************************************/
/** Returns the parent ID.
  *
  * This function returns the parent ID of the core bone instance.
  *
  * @return One of the following values:
  *         \li the \b ID of the parent
  *         \li \b -1 if the core bone instance is a root core bone
  *****************************************************************************/

int QunCoreBone::getParentId() const
{
  return m_parentId;
}

 /*****************************************************************************/
/** Returns the rotation.
  *
  * This function returns the relative rotation of the core bone instance.
  *
  * @return The relative rotation to the parent as quaternion.
  *****************************************************************************/

const QunQuaternion& QunCoreBone::getRotation() const
{
  return m_rotation;
}

 /*****************************************************************************/
/** Returns the absolute rotation.
  *
  * This function returns the absolute rotation of the core bone instance.
  *
  * @return The absolute rotation to the parent as quaternion.
  *****************************************************************************/

const QunQuaternion& QunCoreBone::getRotationAbsolute() const
{
  return m_rotationAbsolute;
}

 /*****************************************************************************/
/** Returns the bone space rotation.
  *
  * This function returns the rotation to bring a point into the core bone
  * instance space.
  *
  * @return The rotation to bring a point into bone space.
  *****************************************************************************/

const QunQuaternion& QunCoreBone::getRotationBoneSpace() const
{
  return m_rotationBoneSpace;
}

 /*****************************************************************************/
/** Returns the translation.
  *
  * This function returns the relative translation of the core bone instance.
  *
  * @return The relative translation to the parent as quaternion.
  *****************************************************************************/

const QunVector& QunCoreBone::getTranslation() const
{
  return m_translation;
}

 /*****************************************************************************/
/** Returns the absolute translation.
  *
  * This function returns the absolute translation of the core bone instance.
  *
  * @return The absolute translation to the parent as quaternion.
  *****************************************************************************/

const QunVector& QunCoreBone::getTranslationAbsolute() const
{
  return m_translationAbsolute;
}

 /*****************************************************************************/
/** Returns the bone space translation.
  *
  * This function returns the translation to bring a point into the core bone
  * instance space.
  *
  * @return The translation to bring a point into bone space.
  *****************************************************************************/

const QunVector& QunCoreBone::getTranslationBoneSpace() const
{
  return m_translationBoneSpace;
}

 /*****************************************************************************/
/** Provides access to the user data.
  *
  * This function returns the user data stored in the core bone instance.
  *
  * @return The user data stored in the core bone instance.
  *****************************************************************************/

Qun::UserData QunCoreBone::getUserData()
{
  return m_userData;
}

 /*****************************************************************************/
/** Sets the core skeleton.
  *
  * This function sets the core skeleton to which the core bone instance is
  * attached to.
  *
  * @param pCoreSkeleton The core skeleton to which the core bone instance
  *                      should be attached to.
  *****************************************************************************/

void QunCoreBone::setCoreSkeleton(QunCoreSkeleton *pCoreSkeleton)
{
  m_pCoreSkeleton = pCoreSkeleton;
}

 /*****************************************************************************/
/** Sets the parent ID.
  *
  * This function sets the parent ID of the core bone instance.
  *
  * @param parentId The ID of the parent that should be set.
  *****************************************************************************/

void QunCoreBone::setParentId(int parentId)
{
  m_parentId = parentId;
}

/*****************************************************************************/
/** Provides access to the core skeleton.
  *
  * This function returns the core skeleton.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunCoreSkeleton *QunCoreBone::getCoreSkeleton()
{
  return m_pCoreSkeleton;
}

 /*****************************************************************************/
/** Sets the rotation.
  *
  * This function sets the relative rotation of the core bone instance.
  *
  * @param rotation The relative rotation to the parent as quaternion.
  *****************************************************************************/

void QunCoreBone::setRotation(const QunQuaternion& rotation)
{
  m_rotation = rotation;
}

 /*****************************************************************************/
/** Sets the bone space rotation.
  *
  * This function sets the rotation that brings a point into the core bone
  * instance space.
  *
  * @param rotation The rotation that brings a point into bone space.
  *****************************************************************************/

void QunCoreBone::setRotationBoneSpace(const QunQuaternion& rotation)
{
  m_rotationBoneSpace = rotation;
}

 /*****************************************************************************/
/** Sets the translation.
  *
  * This function sets the relative translation of the core bone instance.
  *
  * @param translation The relative translation to the parent as vector.
  *****************************************************************************/

void QunCoreBone::setTranslation(const QunVector& translation)
{
  m_translation = translation;
}

 /*****************************************************************************/
/** Sets the bone space translation.
  *
  * This function sets the translation that brings a point into the core bone
  * instance space.
  *
  * @param translation The translation that brings a point into bone space.
  *****************************************************************************/

void QunCoreBone::setTranslationBoneSpace(const QunVector& translation)
{
  m_translationBoneSpace = translation;
}

 /*****************************************************************************/
/** Stores user data.
  *
  * This function stores user data in the core bone instance.
  *
  * @param userData The user data that should be stored.
  *****************************************************************************/

void QunCoreBone::setUserData(Qun::UserData userData)
{
  m_userData = userData;
}
 /*****************************************************************************/
/** Qunculates the bounding box.
  *
  * This function Qunculates the bounding box of the core bone instance.
  *
  * @param pCoreModel The coreModel (needed for vertices data.
  *****************************************************************************/

void QunCoreBone::calculateBoundingBox(QunCoreModel * pCoreModel)
{
   int boneId =  m_pCoreSkeleton->getCoreBoneId(m_strName);
   
   initBoundingBox();
   
   int meshId;
   for(meshId=0; meshId < pCoreModel->getCoreMeshCount(); ++meshId)
   {
       QunCoreMesh * pCoreMesh = pCoreModel->getCoreMesh(meshId);
	   
       int submeshId;
       for(submeshId=0;submeshId<pCoreMesh->getCoreSubmeshCount();submeshId++)
       {
		   QunCoreSubmesh *pCoreSubmesh = pCoreMesh->getCoreSubmesh(submeshId);
		   
		   if(pCoreSubmesh->getSpringCount()==0)
		   {
			   
			   std::vector<QunCoreSubmesh::Vertex>& vectorVertex =  pCoreSubmesh->getVectorVertex();
			   for(size_t vertexId=0;vertexId <vectorVertex.size(); ++vertexId)
			   {
				   for(size_t influenceId=0;influenceId<vectorVertex[vertexId].vectorInfluence.size();++influenceId)
				   {
					   if(vectorVertex[vertexId].vectorInfluence[influenceId].boneId == boneId && vectorVertex[vertexId].vectorInfluence[influenceId].weight > 0.5f)
					   {
						   int planeId;
						   for(planeId = 0; planeId < 6; ++planeId)
						   {
							   if(m_boundingBox.plane[planeId].eval(vectorVertex[vertexId].position) < 0.0f)
							   {
								   m_boundingBox.plane[planeId].setPosition(vectorVertex[vertexId].position);
								   m_boundingPosition[planeId]=vectorVertex[vertexId].position;		          
							   }
						   }
					   }
				   }
			   }	
		   }
	   }
   }
   m_boundingBoxPrecomputed = true;
}

void QunCoreBone::initBoundingBox()
{
   QunQuaternion rot;
   rot=m_rotationBoneSpace;   
  
   rot.invert();
   
   QunVector dir = QunVector(1.0f,0.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[0].setNormal(dir);

   dir = QunVector(-1.0f,0.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[1].setNormal(dir);

   dir = QunVector(0.0f,1.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[2].setNormal(dir);

   dir = QunVector(0.0f,-1.0f,0.0f);
   dir*=rot;
   m_boundingBox.plane[3].setNormal(dir);

   dir = QunVector(0.0f,0.0f,1.0f);
   dir*=rot;
   m_boundingBox.plane[4].setNormal(dir);

   dir = QunVector(0.0f,0.0f,-1.0f);
   dir*=rot;
   m_boundingBox.plane[5].setNormal(dir);
}

void QunCoreBone::updateBoundingBox( const QunVector & position )
{
	for (int planeId = 0; planeId < 6; ++planeId)
	{
	   if (m_boundingBox.plane[planeId].eval(position) < 0.0f)
	   {
		   m_boundingBox.plane[planeId].setPosition(position);
		   m_boundingPosition[planeId] = position;
	   }
	}
}

 /*****************************************************************************/
/** Returns the current bounding box.
  *
  * This function returns the current bounding box of the core bone instance.
  *
  * @return bounding box.
  *****************************************************************************/


QunBoundingBox & QunCoreBone::getBoundingBox()
{
   return m_boundingBox;
}

void QunCoreBone::getBoundingData(int planeId,QunVector & position)
{
   position = m_boundingPosition[planeId];
}

bool QunCoreBone::isBoundingBoxPrecomputed() const
{
	return m_boundingBoxPrecomputed;
}

void QunCoreBone::setBoundingBoxPrecomputed( bool inComputed )
{
	m_boundingBoxPrecomputed = inComputed;
}


 /*****************************************************************************/
/** Scale the core bone.
  *
  * This function rescale all the data that are in the core bone instance and
  * in his childs.
  *
  * @param factor A float with the scale factor
  *
  *****************************************************************************/


void QunCoreBone::scale(float factor)
{
	m_translation*=factor;
	m_translationAbsolute*=factor;
	m_translationBoneSpace*=factor;
	
	// calculate all child bones
	std::list<int>::iterator iteratorChildId;
	for(iteratorChildId = m_listChildId.begin(); iteratorChildId != m_listChildId.end(); ++iteratorChildId)
	{
		m_pCoreSkeleton->getCoreBone(*iteratorChildId)->scale(factor);
	}
}


//****************************************************************************//

