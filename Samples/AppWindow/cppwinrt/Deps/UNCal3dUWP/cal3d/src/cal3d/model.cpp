//****************************************************************************//
// model.cpp                                                                  //
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
#include "cal3d/model.h"
#include "cal3d/skeleton.h"
#include "cal3d/bone.h"
#include "cal3d/mixer.h"
#include "cal3d/renderer.h"
#include "cal3d/coremodel.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coremesh.h"
#include "cal3d/coresubmesh.h"
#include "cal3d/mesh.h"
#include "cal3d/morphtargetmixer.h"
#include "cal3d/physique.h"
#include "cal3d/springsystem.h"

 /*****************************************************************************/
/** Constructs the model instance.
  *
  * This function is the default constructor of the model instance.
  *****************************************************************************/

QunModel::QunModel(QunCoreModel* pCoreModel)
  : m_pCoreModel(0)
  , m_pSkeleton(0)
  , m_pMixer(0)
  , m_pMorphTargetMixer(0)
  , m_pPhysique(0)
  , m_pSpringSystem(0)
  , m_pRenderer(0)
  , m_userData(0)
{
  assert(pCoreModel);

  m_pCoreModel = pCoreModel;
  m_pSkeleton = new QunSkeleton(pCoreModel->getCoreSkeleton());
  m_pMixer = new QunMixer(this);
  m_pMorphTargetMixer = new QunMorphTargetMixer(this);
  m_pPhysique = new QunPhysique(this);
  m_pSpringSystem = new QunSpringSystem(this);
  m_pRenderer = new QunRenderer(this);

  m_userData = 0;
}

 /*****************************************************************************/
/** Destructs the model instance.
  *
  * This function is the destructor of the model instance.
  *****************************************************************************/

QunModel::~QunModel()
{
  for(size_t meshId = 0; meshId < m_vectorMesh.size(); ++meshId)
  {
    delete m_vectorMesh[meshId];
  }

  delete m_pRenderer;
  delete m_pSpringSystem;
  delete m_pPhysique;
  delete m_pMixer;
  delete m_pMorphTargetMixer;
  delete m_pSkeleton;
}

 /*****************************************************************************/
/** Attachs a mesh.
  *
  * This function attachs a mesh to the model instance.
  *
  * @param coreMeshId The ID of the mesh that should be attached.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunModel::attachMesh(int coreMeshId)
{
  // check if the id is valid
  if((coreMeshId < 0) ||(coreMeshId >= m_pCoreModel->getCoreMeshCount()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the core mesh
  QunCoreMesh *pCoreMesh;
  pCoreMesh = m_pCoreModel->getCoreMesh(coreMeshId);

  // check if the mesh is already attached
  int meshId;
  for(meshId = 0; meshId < (int)m_vectorMesh.size(); ++meshId)
  {
    // check if we found the matching mesh
    if(m_vectorMesh[meshId]->getCoreMesh() == pCoreMesh)
    {
      // mesh is already active -> do nothing
      return true;
    }
  }

  // allocate a new mesh instance
  QunMesh *pMesh = new(std::nothrow) QunMesh(pCoreMesh);
  if(pMesh == 0)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return false;
  }

  // set model in the mesh instance
  pMesh->setModel(this);

  // insert the new mesh into the active list
  m_vectorMesh.push_back(pMesh);

  return true;
}


 /*****************************************************************************/
/** Detaches a mesh.
  *
  * This function detaches a mesh from the model instance.
  *
  * @param coreMeshId The ID of the mesh that should be detached.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunModel::detachMesh(int coreMeshId)
{
  // check if the id is valid
  if((coreMeshId < 0) ||(coreMeshId >= m_pCoreModel->getCoreMeshCount()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the core mesh
  QunCoreMesh *pCoreMesh;
  pCoreMesh = m_pCoreModel->getCoreMesh(coreMeshId);

  // find the mesh for the given id
  std::vector<QunMesh *>::iterator iteratorMesh;
  for(iteratorMesh = m_vectorMesh.begin(); iteratorMesh != m_vectorMesh.end(); ++iteratorMesh)
  {
    // get the mesh
    QunMesh *pMesh;
    pMesh = *iteratorMesh;

    // check if we found the matching mesh
    if(pMesh->getCoreMesh() == pCoreMesh)
    {
      // destroy the mesh
      delete pMesh;

      // erase the mesh out of the active mesh list
      m_vectorMesh.erase(iteratorMesh);

      return true;
    }
  }

  return false;
}

 /*****************************************************************************/
/** Provides access to the core model.
  *
  * This function returns the core model on which this model instance is based
  * on.
  *
  * @return One of the following values:
  *         \li a pointer to the core model
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunCoreModel *QunModel::getCoreModel() const
{
  return m_pCoreModel;
}

 /*****************************************************************************/
/** Provides access to an attached mesh.
  *
  * This function returns the attached mesh with the given core mesh ID.
  *
  * @param coreMeshId The core mesh ID of the mesh that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the mesh
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunMesh *QunModel::getMesh(int coreMeshId) const
{
  // check if the id is valid
  if((coreMeshId < 0) ||(coreMeshId >= m_pCoreModel->getCoreMeshCount()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  // get the core mesh
  QunCoreMesh *pCoreMesh = m_pCoreModel->getCoreMesh(coreMeshId);

  // search the mesh
  for(int meshId = 0; meshId < (int)m_vectorMesh.size(); ++meshId)
  {
    // check if we found the matching mesh
    if(m_vectorMesh[meshId]->getCoreMesh() == pCoreMesh)
    {
      return m_vectorMesh[meshId];
    }
  }

  return 0;
}

/*****************************************************************************/
/** Returns the mixer.
 *
 * If a mixer that is not an instance of QunMixer was set with the
 * QunModel::setAbstractMixer method, an INVALID_MIXER_TYPE error (see
 * QunError) is set and 0 is returned.
 *
 * @return \li a pointer to the mixer
 *         \li \b 0 if an error happend
 *****************************************************************************/

QunMixer *QunModel::getMixer() const
{
  if(m_pMixer == 0)
    return 0;

  if(m_pMixer->isDefaultMixer() == false) {
    QunError::setLastError(QunError::INVALID_MIXER_TYPE, __FILE__, __LINE__);
    return 0;
  } else {
    return (QunMixer*)(m_pMixer);
  }
}

/*****************************************************************************/
/** Returns the mixer. 
 *
 * @return \li a pointer to the mixer
 *         \li \b 0 if no mixer was set
 *****************************************************************************/

QunAbstractMixer *QunModel::getAbstractMixer() const
{
  return m_pMixer;
}

/*****************************************************************************/
/** Sets the mixer to a QunAbstractMixer subclass instance.
 *
 * If a mixer was already set (with QunModel::setAbstractMixer or
 * because the QunModel::create method created a QunMixer instance),
 * its \b destroy method is called. The existing mixer is not
 * deallocated, it is the responsibility of the caller to call the
 * getAbstractMixer method and deallocate the returned instance if
 * appropriate.
 *
 * \b pMixer will be deallocated by cal3d if and only if the
 * QunModel::destroy function is called.
 *
 * The \b create method of pMixer is called.
 *
 * pMixer may be null. After setting a null pointer, the caller MUST
 * call QunModel::create or QunModel::setAbstractMixer with a non-null
 * pointer before any other method is called.
 *
 * @param pMixer is a pointer to a QunAbstractMixer subclass instance.
 *
 *****************************************************************************/

void QunModel::setAbstractMixer(QunAbstractMixer* pMixer)
{
  m_pMixer = pMixer;
}

/*****************************************************************************/
/** Provides access to the morph target mixer.
  *
  * This function returns the morph target mixer.
  *
  * @return One of the following values:
  *         \li a pointer to the morph target mixer
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunMorphTargetMixer *QunModel::getMorphTargetMixer() const
{
  return m_pMorphTargetMixer;
}

 /*****************************************************************************/
/** Provides access to the physique.
  *
  * This function returns the physique.
  *
  * @return One of the following values:
  *         \li a pointer to the physique
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunPhysique *QunModel::getPhysique() const
{
  return m_pPhysique;
}

 /*****************************************************************************/
/** Sets the physique.
  *
  * This function changes the physique of the model.
  *
  * @param physique The new physique object.
  *****************************************************************************/
void QunModel::setPhysique( QunPhysique* physique )
{
	delete m_pPhysique;
	m_pPhysique = physique;
}

 /*****************************************************************************/
/** Provides access to the renderer.
  *
  * This function returns the renderer.
  *
  * @return One of the following values:
  *         \li a pointer to the renderer
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunRenderer *QunModel::getRenderer() const
{
  return m_pRenderer;
}

 /*****************************************************************************/
/** Provides access to the skeleton.
  *
  * This function returns the skeleton.
  *
  * @return One of the following values:
  *         \li a pointer to the skeleton
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunSkeleton *QunModel::getSkeleton() const
{
  return m_pSkeleton;
}

 /*****************************************************************************/
/** Provides access to the spring system.
  *
  * This function returns the spring system.
  *
  * @return One of the following values:
  *         \li a pointer to the spring system
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunSpringSystem *QunModel::getSpringSystem() const
{
  return m_pSpringSystem;
}

 /*****************************************************************************/
/** Returns the global bounding box of the model.
  *
  * This function returns the global bounding box of the model.
  *
  * @param precision : indicate if the function need to compute a 
  *        correct bounding box
  *
  * @return bounding box.
  *****************************************************************************/


QunBoundingBox & QunModel::getBoundingBox(bool precision)
{
	QunVector v;
	v = QunVector(1.0f,0.0f,0.0f);	
	m_boundingBox.plane[0].setNormal(v);
	v = QunVector(-1.0f,0.0f,0.0f);	
	m_boundingBox.plane[1].setNormal(v);
	v = QunVector(0.0f,1.0f,0.0f);	
	m_boundingBox.plane[2].setNormal(v);
	v = QunVector(0.0f,-1.0f,0.0f);	
	m_boundingBox.plane[3].setNormal(v);
	v = QunVector(0.0f,0.0f,1.0f);	
	m_boundingBox.plane[4].setNormal(v);
	v = QunVector(0.0f,0.0f,-1.0f);	
	m_boundingBox.plane[5].setNormal(v);

	if(precision)
		m_pSkeleton->calculateBoundingBoxes();

	
	std::vector<QunBone *> & vectorBone =  m_pSkeleton->getVectorBone();
		
	std::vector<QunBone *>::iterator iteratorBone;
	for(iteratorBone = vectorBone.begin(); iteratorBone != vectorBone.end(); ++iteratorBone)
	{
		// If it's just an approximation that are needed then
		// we just compute the bounding box from the skeleton

		if(!precision || !(*iteratorBone)->getCoreBone()->isBoundingBoxPrecomputed())
		{
			
			QunVector translation = (*iteratorBone)->getTranslationAbsolute();
			
			int planeId;
			for(planeId = 0; planeId < 6; ++planeId)
			{
				if(m_boundingBox.plane[planeId].eval(translation) < 0.0f)
				{
					m_boundingBox.plane[planeId].setPosition(translation);
				}
			}
		}
		else
		{
			QunBoundingBox localBoundingBox = (*iteratorBone)->getBoundingBox();
			QunVector points[8];
			localBoundingBox.computePoints(points);
			
			for(int i=0; i < 8; i++)
			{				
				int planeId;
				for(planeId = 0; planeId < 6; ++planeId)
				{
					if(m_boundingBox.plane[planeId].eval(points[i]) < 0.0f)
					{
						m_boundingBox.plane[planeId].setPosition(points[i]);
					}
				}
			}				
		}
	}
	
	return m_boundingBox;
}

 /*****************************************************************************/
/** Provides access to the user data.
  *
  * This function returns the user data stored in the model instance.
  *
  * @return The user data stored in the model instance.
  *****************************************************************************/

Qun::UserData QunModel::getUserData() const
{
  return m_userData;
}

 /*****************************************************************************/
/** Returns the mesh vector.
  *
  * This function returns the vector that contains all attached meshes of the
  * model instance.
  *
  * @return A reference to the mesh vector.
  *****************************************************************************/

std::vector<QunMesh *>& QunModel::getVectorMesh()
{
  return m_vectorMesh;
}

 /*****************************************************************************/
/** Sets the LOD level.
  *
  * This function sets the LOD level of all attached meshes.
  *
  * @param lodLevel The LOD level in the range [0.0, 1.0].
  *****************************************************************************/

void QunModel::setLodLevel(float lodLevel)
{
  // set the lod level in all meshes
  std::vector<QunMesh *>::iterator iteratorMesh;
  for(iteratorMesh = m_vectorMesh.begin(); iteratorMesh != m_vectorMesh.end(); ++iteratorMesh)
  {
    // set the lod level in the mesh
    (*iteratorMesh)->setLodLevel(lodLevel);
  }
}

 /*****************************************************************************/
/** Sets the material set.
  *
  * This function sets the material set of all attached meshes.
  *
  * @param setId The ID of the material set.
  *****************************************************************************/

void QunModel::setMaterialSet(int setId)
{
  // set the lod level in all meshes
  std::vector<QunMesh *>::iterator iteratorMesh;
  for(iteratorMesh = m_vectorMesh.begin(); iteratorMesh != m_vectorMesh.end(); ++iteratorMesh)
  {
    // set the material set in the mesh
    (*iteratorMesh)->setMaterialSet(setId);
  }
}

 /*****************************************************************************/
/** Stores user data.
  *
  * This function stores user data in the model instance.
  *
  * @param userData The user data that should be stored.
  *****************************************************************************/

void QunModel::setUserData(Qun::UserData userData)
{
  m_userData = userData;
}

 /*****************************************************************************/
/** Updates the model instance.
  *
  * This function updates the model instance for a given amount of time.
  *
  * @param deltaTime The elapsed time in seconds since the last update.
  *****************************************************************************/

void QunModel::update(float deltaTime)
{
  m_pMixer->updateAnimation(deltaTime);
  m_pMixer->updateSkeleton();
  // m_pMorpher->update(...);
  m_pMorphTargetMixer->update(deltaTime);
  m_pPhysique->update();
  m_pSpringSystem->update(deltaTime);
}

/*****************************************************************************/
/** Disable internal data (and thus springs system)
  *
  *****************************************************************************/

void QunModel::disableInternalData()
{
  // Disable internal data in all meshes
  std::vector<QunMesh *>::iterator iteratorMesh;
  for(iteratorMesh = m_vectorMesh.begin(); iteratorMesh != m_vectorMesh.end(); ++iteratorMesh)
  {
    // Disable internal data in the mesh
    (*iteratorMesh)->disableInternalData();
  }
}

//****************************************************************************//
