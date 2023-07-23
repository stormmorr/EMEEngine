//****************************************************************************//
// coreskeleton.cpp                                                           //
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


#include "cal3d/error.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/corebone.h"
#include "cal3d/coremodel.h"
#include "cal3d/coresubmesh.h"


QunCoreSkeleton::QunCoreSkeleton()
{
}


QunCoreSkeleton::~QunCoreSkeleton()
{
  // destroy all core animations
  std::vector<QunCoreBone *>::iterator iteratorCoreBone;
  for(iteratorCoreBone = m_vectorCoreBone.begin(); iteratorCoreBone != m_vectorCoreBone.end(); ++iteratorCoreBone)
  {
    delete (*iteratorCoreBone);
  }
}

 /*****************************************************************************/
/** Adds a core bone.
  *
  * This function adds a core bone to the core skeleton instance.
  *
  * @param pCoreBone A pointer to the core bone that should be added.
  *
  * @return One of the following values:
  *         \li the assigned bone \b ID of the added core bone
  *         \li \b -1 if an error happend
  *****************************************************************************/

int QunCoreSkeleton::addCoreBone(QunCoreBone *pCoreBone)
{
  // get next bone id
  int boneId;
  boneId = m_vectorCoreBone.size();

  m_vectorCoreBone.push_back(pCoreBone);

  // if necessary, add the core bone to the root bone list
  if(pCoreBone->getParentId() == -1)
  {
    m_vectorRootCoreBoneId.push_back(boneId);
  }

  // add a reference from the bone's name to its id
  mapCoreBoneName( boneId, pCoreBone->getName() );

#if 1
  printf("Trace pCoreBone->getName() %s\n", pCoreBone->getName().c_str());
#endif

  return boneId;
}

 /*****************************************************************************/
/** Qunculates the current state.
  *
  * This function calculates the current state of the core skeleton instance by
  * calculating all the core bone states.
  *****************************************************************************/

void QunCoreSkeleton::calculateState()
{
  // calculate all bone states of the skeleton
  std::vector<int>::iterator iteratorRootCoreBoneId;
  for(iteratorRootCoreBoneId = m_vectorRootCoreBoneId.begin(); iteratorRootCoreBoneId != m_vectorRootCoreBoneId.end(); ++iteratorRootCoreBoneId)
  {
    m_vectorCoreBone[*iteratorRootCoreBoneId]->calculateState();
  }
}

 /*****************************************************************************/
/** Provides access to a core bone.
  *
  * This function returns the core bone with the given ID.
  *
  * @param coreBoneId The ID of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core bone
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunCoreBone *QunCoreSkeleton::getCoreBone(int coreBoneId)
{
  if((coreBoneId < 0) || (coreBoneId >= (int)m_vectorCoreBone.size()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreBone[coreBoneId];
}

 /*****************************************************************************/
/** Provides access to a core bone.
  *
  * This function returns the core bone with the given name.
  *
  * @param strName The name of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core bone
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunCoreBone* QunCoreSkeleton::getCoreBone(const std::string& strName)
{
   return getCoreBone( getCoreBoneId( strName ));
}

 /*****************************************************************************/
/** Returns the ID of a specified core bone.
  *
  * This function returns the ID of a specified core bone.
  *
  * @param strName The name of the core bone that should be returned.
  *
  * @return One of the following values:
  *         \li the \b ID of the core bone
  *         \li \b -1 if an error happend
  *****************************************************************************/

int QunCoreSkeleton::getCoreBoneId(const std::string& strName)
{
  //Check to make sure the mapping exists
  if (m_mapCoreBoneNames.count(strName) <= 0)
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  return m_mapCoreBoneNames[strName];

}

 /*****************************************************************************/
/** Maps the name of a bone to a specific bone id
  *
  * This function returns true or false depending on whether the mapping
  * was successful or not. Note that it is possible to overwrite and existing
  * mapping and no error will be given.
  *
  * @param coreBoneId The id of the core bone to be associated with the name.
  * @param strName The name of the core bone that will be associated with the id.
  *
  * @return One of the following values:
  *         \li true if the mapping was successful
  *         \li false if an invalid ID was given
  *****************************************************************************/

bool QunCoreSkeleton::mapCoreBoneName(int coreBoneId, const std::string& strName)
{
   //Make sure the ID given is a valid corebone ID number
   if ((coreBoneId < 0) || (coreBoneId >= (int)m_vectorCoreBone.size()))
   {
      return false;
   }

   //Add the mapping or overwrite an existing mapping
   m_mapCoreBoneNames[strName] = coreBoneId;

   return true;
}

 /*****************************************************************************/
/** Returns the root core bone id list.
  *
  * This function returns the list that contains all root core bone IDs of the
  * core skeleton instance.
  *
  * @return A reference to the root core bone id list.
  *****************************************************************************/

std::vector<int>& QunCoreSkeleton::getVectorRootCoreBoneId()
{
  return m_vectorRootCoreBoneId;
}

 /*****************************************************************************/
/** Returns the core bone vector.
  *
  * This function returns the vector that contains all core bones of the core
  * skeleton instance.
  *
  * @return A reference to the core bone vector.
  *****************************************************************************/

std::vector<QunCoreBone *>& QunCoreSkeleton::getVectorCoreBone()
{
  return m_vectorCoreBone;
}


 /*****************************************************************************/
/** Qunculates bounding boxes.
  *
  * This function Qunculates the bounding box of every bone in the core Skeleton.
  *
  * @param pCoreModel The coreModel (needed for vertices data).
  *****************************************************************************/


void QunCoreSkeleton::calculateBoundingBoxes(QunCoreModel * pCoreModel)
{
	size_t boneId;
	
	// First, find out whether all the bounding boxes have already been precomputed.
	// If so, we can bail out early.
	bool	alreadyComputed = true;
	for(boneId=0;boneId<m_vectorCoreBone.size();++boneId)
	{
		if (! m_vectorCoreBone[boneId]->isBoundingBoxPrecomputed())
		{
			alreadyComputed = false;
			break;
		}
	}
	if (alreadyComputed)
	{
		return;
	}
	
	// Initialize all bounding boxes empty.
	for(boneId=0;boneId<m_vectorCoreBone.size();++boneId)
	{
		m_vectorCoreBone[boneId]->initBoundingBox();
	}
	
	// Loop over all vertices updating bounding boxes.
	for(int meshId=0; meshId < pCoreModel->getCoreMeshCount(); ++meshId)
	{
		QunCoreMesh * pCoreMesh = pCoreModel->getCoreMesh(meshId);
		
		for(int submeshId=0;submeshId<pCoreMesh->getCoreSubmeshCount();submeshId++)
		{
			QunCoreSubmesh *pCoreSubmesh = pCoreMesh->getCoreSubmesh(submeshId);
			
			if(pCoreSubmesh->getSpringCount()==0)
			{
				std::vector<QunCoreSubmesh::Vertex>& vectorVertex =
					pCoreSubmesh->getVectorVertex();
				
				for(size_t vertexId=0;vertexId <vectorVertex.size(); ++vertexId)
				{
					for(size_t influenceId=0;
						influenceId < vectorVertex[vertexId].vectorInfluence.size();
						++influenceId)
					{
						if (vectorVertex[vertexId].vectorInfluence[influenceId].weight > 0.5f)
						{
							boneId = vectorVertex[vertexId].vectorInfluence[influenceId].boneId;
							
							m_vectorCoreBone[boneId]->updateBoundingBox(
								vectorVertex[vertexId].position );
							
							break;	// there can be at most one bone with majority influence
						}
					}
				}
			}
		}
	}

	// Mark bounding boxes as computed.
	for(boneId=0;boneId<m_vectorCoreBone.size();++boneId)
	{
		m_vectorCoreBone[boneId]->setBoundingBoxPrecomputed( true );
	}
}

 /*****************************************************************************/
/** Scale the core skeleton.
  *
  * This function rescale all the data that are in the core skeleton instance.
  *
  * @param factor A float with the scale factor
  *
  *****************************************************************************/


void QunCoreSkeleton::scale(float factor)
{
  std::vector<int>::iterator iteratorRootCoreBoneId;
  for(iteratorRootCoreBoneId = m_vectorRootCoreBoneId.begin(); iteratorRootCoreBoneId != m_vectorRootCoreBoneId.end(); ++iteratorRootCoreBoneId)
  {
    m_vectorCoreBone[*iteratorRootCoreBoneId]->scale(factor);
  }

}
