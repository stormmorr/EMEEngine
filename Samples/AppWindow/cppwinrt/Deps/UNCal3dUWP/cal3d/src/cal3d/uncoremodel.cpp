//****************************************************************************//
// coremodel.cpp                                                              //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
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

#include "cal3d/coremodel.h"
#include "cal3d/error.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coreanimation.h"
#include "cal3d/coremesh.h"
#include "cal3d/corematerial.h"
#include "cal3d/loader.h"
#include "cal3d/saver.h"

 /*****************************************************************************/
/** Constructs the core model instance.
  *
  * This function is the default constructor of the core model instance.
  *****************************************************************************/

UN_CoreModel::UN_CoreModel(const std::string& name)
: m_strName(name)
, m_pCoreSkeleton(0)
, m_userData(0)
{
}

 /*****************************************************************************/
/** Constructs a copy of a core model instance.
  *
  * This function is the copy constructor of the core model instance.
  *****************************************************************************/
UN_CoreModel::UN_CoreModel(const UN_CoreModel& inOther)
	: m_strName( inOther.m_strName )
	, m_pCoreSkeleton( inOther.m_pCoreSkeleton )
	, m_vectorCoreAnimation( inOther.m_vectorCoreAnimation )
	, m_vectorCoreMorphAnimation( inOther.m_vectorCoreMorphAnimation )
	, m_vectorCoreMesh( inOther.m_vectorCoreMesh )
	, m_vectorCoreMaterial( inOther.m_vectorCoreMaterial )
	, m_mapmapCoreMaterialThread( inOther.m_mapmapCoreMaterialThread )
	, m_userData( inOther.m_userData )
	, m_animationName( inOther.m_animationName )
	, m_materialName( inOther.m_materialName )
	, m_meshName( inOther.m_meshName )
{
}

 /*****************************************************************************/
/** Destructs the core model instance.
  *
  * This function is the destructor of the core model instance.
  *****************************************************************************/

UN_CoreModel::~UN_CoreModel()
{
}

void UN_CoreModel::setOffSetMesh(int i_value)
{
	m_OffSetMesh.push_back(i_value);
}

void UN_CoreModel::setOffSetX(int i_value)
{
	m_OffSetX.push_back(i_value);
}

void UN_CoreModel::setOffSetY(int i_value)
{
	m_OffSetY.push_back(i_value);
}

void UN_CoreModel::setOffSetZ(int i_value)
{
	m_OffSetZ.push_back(i_value);
}

 /*****************************************************************************/
/** Adds a core animation.
  *
  * This function adds a core animation to the core model instance.
  *
  * @param pCoreAnimation A pointer to the core animation that should be added.
  *
  * @return \li the assigned animation \b ID of the added core animation
  *****************************************************************************/

int UN_CoreModel::addCoreAnimation(CalCoreAnimation *pCoreAnimation)
{
  int animationId = m_vectorCoreAnimation.size();
  m_vectorCoreAnimation.push_back(pCoreAnimation);
  return animationId;
}

 /*****************************************************************************/
/** Adds a core morph animation.
  *
  * This function adds a core morph animation to the core model instance.
  *
  * @param pCoreMorphAnimation A pointer to the core morph animation that 
  *                            should be added.
  *
  * @return One of the following values:
  *         \li the assigned morph animation \b ID of the added core morph animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::addCoreMorphAnimation(CalCoreMorphAnimation *pCoreMorphAnimation)
{
  // get the id of the core morph animation
  int morphAnimationId;
  morphAnimationId = m_vectorCoreMorphAnimation.size();

  m_vectorCoreMorphAnimation.push_back(pCoreMorphAnimation);

  return morphAnimationId;
}

 /*****************************************************************************/
/** Adds a core material.
  *
  * This function adds a core material to the core model instance.
  *
  * @param pCoreMaterial A pointer to the core material that should be added.
  *
  * @return One of the following values:
  *         \li the assigned material \b ID of the added core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::addCoreMaterial(CalCoreMaterial *pCoreMaterial)
{
  // get the id of the core material
  int materialId = m_vectorCoreMaterial.size();

  m_vectorCoreMaterial.push_back(pCoreMaterial);

  return materialId;
}


 /*****************************************************************************/
/** Replace each core material by a copy.
  *
  *****************************************************************************/
void UN_CoreModel::cloneCoreMaterials()
{
	std::vector<CalCoreMaterialPtr>		cloneVec;
	
	for (std::vector<CalCoreMaterialPtr>::iterator i = m_vectorCoreMaterial.begin();
		i != m_vectorCoreMaterial.end(); ++i)
	{
		cloneVec.push_back( new CalCoreMaterial( **i ) );
	}
	
	m_vectorCoreMaterial.swap( cloneVec );
}

 /*****************************************************************************/
/** Adds a core mesh.
  *
  * This function adds a core mesh to the core model instance.
  *
  * @param pCoreMesh A pointer to the core mesh that should be added.
  *
  * @return One of the following values:
  *         \li the assigned mesh \b ID of the added core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::addCoreMesh(CalCoreMesh *pCoreMesh)
{
  // get the id of the core mesh
  int meshId = m_vectorCoreMesh.size();
  m_vectorCoreMesh.push_back(pCoreMesh);
  return meshId;
}

 /*****************************************************************************/
/** Replaces a core mesh.
  *
  * This function replaces a core mesh in the core model instance. - JWWalker
  *
  * @param coreMeshId  The ID of the core mesh that should be replaced.
  * @param pCoreMesh A pointer to the core mesh that should be added.
  *
  *****************************************************************************/
void UN_CoreModel::replaceCoreMesh( int coreMeshId, CalCoreMesh *pCoreMesh )
{
	m_vectorCoreMesh[ coreMeshId ] = pCoreMesh;
}

 /*****************************************************************************/
/** Returns the name.
  *
  * This function returns the name of the core model instance.
  *
  * @return The name as string.
  *****************************************************************************/

const std::string& UN_CoreModel::getName() const
{
  return m_strName;
}


 /*****************************************************************************/
/** Changes the name.
  *
  * This function sets the name of the core model instance.
  *
  * @param The name as string.
  *****************************************************************************/
void UN_CoreModel::setName( const char* inName )
{
	m_strName.assign( inName );
}


 /*****************************************************************************/
/** Creates a core material thread.
  *
  * This function creates a new core material thread with the given ID.
  *
  * @param coreMaterialThreadId The ID of the core material thread that should
  *                             be created.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::createCoreMaterialThread(int coreMaterialThreadId)
{
  // insert an empty core material thread with a given id
  std::map<int, int> mapCoreMaterialThreadId;
  m_mapmapCoreMaterialThread.insert(std::make_pair(coreMaterialThreadId, mapCoreMaterialThreadId));

  return true;
}

 /*****************************************************************************/
/** Provides access to a core animation.
  *
  * This function returns the core animation with the given ID.
  *
  * @param coreAnimationId The ID of the core animation that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreAnimation *UN_CoreModel::getCoreAnimation(int coreAnimationId)
{
  if((coreAnimationId < 0) || (coreAnimationId >= (int)m_vectorCoreAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreAnimation[coreAnimationId].get();
}

 /*****************************************************************************/
/** Provides access to a core morph animation.
  *
  * This function returns the core morph animation with the given ID.
  *
  * @param coreMorphAnimationId The ID of the core morph animation that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core morph animation
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMorphAnimation *UN_CoreModel::getCoreMorphAnimation(int coreMorphAnimationId)
{
  if((coreMorphAnimationId < 0) || (coreMorphAnimationId >= (int)m_vectorCoreMorphAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMorphAnimation[coreMorphAnimationId].get();
}

 /*****************************************************************************/
/** Returns the number of core animations.
  *
  * This function returns the number of core animations in the core model
  * instance.
  *
  * @return The number of core animations.
  *****************************************************************************/

int UN_CoreModel::getCoreAnimationCount() const
{
  return m_vectorCoreAnimation.size();
}

 /*****************************************************************************/
/** Returns the number of core morph animations.
  *
  * This function returns the number of core morph animations in the core model
  * instance.
  *
  * @return The number of core morph animations.
  *****************************************************************************/

int UN_CoreModel::getCoreMorphAnimationCount() const
{
  return m_vectorCoreMorphAnimation.size();
}


 /*****************************************************************************/
/** Provides access to a core material.
  *
  * This function returns the core material with the given ID.
  *
  * @param coreMaterialId The ID of the core material that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMaterial *UN_CoreModel::getCoreMaterial(int coreMaterialId)
{
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMaterial[coreMaterialId].get();
}

 /*****************************************************************************/
/** Returns the number of core materials.
  *
  * This function returns the number of core materials in the core model
  * instance.
  *
  * @return The number of core materials.
  *****************************************************************************/

int UN_CoreModel::getCoreMaterialCount() const
{
  return m_vectorCoreMaterial.size();
}

 /*****************************************************************************/
/** Returns a specified core material ID.
  *
  * This function returns the core material ID for a specified core material
  * thread / core material set pair.
  *
  * @param coreMaterialThreadId The ID of the core material thread.
  * @param coreMaterialSetId The ID of the core material set.
  *
  * @return One of the following values:
  *         \li the \b ID of the core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::getCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId)
{
  // find the core material thread
  std::map<int, std::map<int, int> >::iterator iteratorCoreMaterialThread;
  iteratorCoreMaterialThread = m_mapmapCoreMaterialThread.find(coreMaterialThreadId);
  if(iteratorCoreMaterialThread == m_mapmapCoreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // get the core material thread
  std::map<int, int>& coreMaterialThread = (*iteratorCoreMaterialThread).second;

  // find the material id for the given set
  std::map<int, int>::iterator iteratorSet;
  iteratorSet = coreMaterialThread.find(coreMaterialSetId);
  if(iteratorSet == coreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  return (*iteratorSet).second;
}

 /*****************************************************************************/
/** Provides access to a core mesh.
  *
  * This function returns the core mesh with the given ID.
  *
  * @param coreMeshId The ID of the core mesh that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMesh *UN_CoreModel::getCoreMesh(int coreMeshId)
{
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMesh[coreMeshId].get();
}

 /*****************************************************************************/
/** Returns the number of core meshes.
  *
  * This function returns the number of core meshes in the core model instance.
  *
  * @return The number of core meshes.
  *****************************************************************************/

int UN_CoreModel::getCoreMeshCount() const
{
  return m_vectorCoreMesh.size();
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

CalCoreSkeleton *UN_CoreModel::getCoreSkeleton()
{
  return m_pCoreSkeleton.get();
}

 /*****************************************************************************/
/** Provides access to the user data.
  *
  * This function returns the user data stored in the core model instance.
  *
  * @return The user data stored in the core model instance.
  *****************************************************************************/

Cal::UserData UN_CoreModel::getUserData()
{
  return m_userData;
}

 /*****************************************************************************/
/** Loads a core animation.
  *
  * This function loads a core animation from a file.
  *
  * @param strFilename The file from which the core animation should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreAnimation(const std::string& strFilename)
{
  // the core skeleton has to be loaded already
  if(!m_pCoreSkeleton)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core animation
  UN_CoreAnimation pCoreAnimation = CalLoader::loadCoreAnimation(strFilename, m_pCoreSkeleton.get());

  //CalCoreAnimationPtr pCoreAnimation = &pCoreAnimation;
  //if(!pCoreAnimation) return -1;
  

  // add core animation to this core model
  return addCoreAnimation(pCoreAnimation.get());
}

 /*****************************************************************************/
/** Loads a core animation and bind it to a name.
  *
  * This function loads a core animation from a file. It is equivalent
  * to calling addAnimName(strAnimationName, loadCoreAnimation(strFilename)).
  * If strAnimationName is already associated to a coreAnimationId because
  * of a previous call to addAnimName, the same coreAnimationId will
  * be used. 
  *
  * @param strFilename The file from which the core animation should be loaded
  *                    from.
  * @param strAnimationName A string that is associated with an anim ID number.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreAnimation(const std::string& strFilename, const std::string& strAnimationName)
{
  int id = -1;
  std::map<std::string, int>::iterator it = m_animationName.find(strAnimationName);
  if (it != m_animationName.end())
  {
    id=(*it).second;

    // the core skeleton has to be loaded already
    if(!m_pCoreSkeleton)
    {
      CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
      return -1;
    }
    if(m_vectorCoreAnimation[id])
    {
      CalError::setLastError(CalError::INDEX_BUILD_FAILED, __FILE__, __LINE__);
      return -1;
    }

    UN_CoreAnimation pCoreAnimation = CalLoader::loadCoreAnimation(strFilename, m_pCoreSkeleton.get());

	CalCoreAnimationPtr &pCoreAnimation;

    if(!pCoreAnimation) return -1;
    pCoreAnimation->setName(strAnimationName);
    m_vectorCoreAnimation[id] = pCoreAnimation;
  }
  else
  {
    id = loadCoreAnimation(strFilename);
    if(id >= 0)
      addAnimationName(strAnimationName, id);
  }

  return id;
}

 /*****************************************************************************/
/** Delete the resources used by the named core animation. The name must 
  * be associated with a valid core animation Id with the function
  * getAnimationId. The caller must ensure that the corresponding is not
  * referenced anywhere otherwise unpredictable results will occur.
  *
  * @param name The symbolic name of the core animation to unload.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::unloadCoreAnimation(const std::string& name)
{
  int id = getCoreAnimationId(name);
  if(id >= 0)
    return unloadCoreAnimation(id);
  else
    return -1;
}

 /*****************************************************************************/
/** Delete the resources used by a core animation. The caller must
  * ensure that the corresponding is not referenced anywhere otherwise
  * unpredictable results will occur.
  *
  * @param coreAnimationId The ID of the core animation that should be unloaded.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/


int UN_CoreModel::unloadCoreAnimation(int coreAnimationId)
{
  if((coreAnimationId < 0) || (coreAnimationId >= (int)m_vectorCoreAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  m_vectorCoreAnimation[coreAnimationId] = CalCoreAnimationPtr (0);

  return coreAnimationId;
}

 /*****************************************************************************/
/** Loads a core animation.
  *
  * This function loads a core animation from a buffer.
  *
  * @param buffer 	The buffer from which the core animation should be loaded.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreAnimation(void* buffer)
{
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core animation
  CalCoreAnimationPtr pCoreAnimation = CalLoader::loadCoreAnimation(buffer);
  if (!pCoreAnimation) return -1;

  // add core animation to this core model
  int animationId = addCoreAnimation(pCoreAnimation.get());
  if(animationId == -1)
  {
    return -1;
  }

  return animationId;
}

 /*****************************************************************************/
/** Loads a core material.
  *
  * This function loads a core material from a file.
  *
  * @param strFilename The file from which the core material should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMaterial(const std::string& strFilename)
{
  // the core skeleton has to be loaded already
  if(!m_pCoreSkeleton)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core material
  CalCoreMaterialPtr pCoreMaterial = CalLoader::loadCoreMaterial(strFilename);
  if(!pCoreMaterial) return -1;

  // add core material to this core model
  return addCoreMaterial(pCoreMaterial.get());
}

 /*****************************************************************************/
/** Loads a core material and bind it to a name.
  *
  * This function loads a core material from a file. It is equivalent
  * to calling addMaterialName(strMaterialName, loadCoreMaterial(strFilename)).
  * If strMaterialName is already associated to a coreMaterialId because
  * of a previous call to addMaterialName, the same coreMaterialId will
  * be used. 
  *
  * @param strFilename The file from which the core material should be loaded
  *                    from.
  * @param strMaterialName A string that is associated with an anim ID number.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMaterial(const std::string& strFilename, const std::string& strMaterialName)
{
  int id = -1;
  std::map<std::string, int>::iterator it = m_materialName.find(strMaterialName);
  if (it != m_materialName.end())
  {
    id=(*it).second;

    // the core skeleton has to be loaded already
    if(!m_pCoreSkeleton)
    {
      CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
      return -1;
    }
    if(m_vectorCoreMaterial[id])
    {
      CalError::setLastError(CalError::INDEX_BUILD_FAILED, __FILE__, __LINE__);
      return -1;
    }
    CalCoreMaterialPtr pCoreMaterial = CalLoader::loadCoreMaterial(strFilename);
    if(!pCoreMaterial) return -1;
    pCoreMaterial->setName(strMaterialName);
    m_vectorCoreMaterial[id] = pCoreMaterial;
  }
  else
  {
    id = loadCoreMaterial(strFilename);
    if(id >= 0)
      addMaterialName(strMaterialName, id);
  }

  return id;
}

 /*****************************************************************************/
/** Loads a core material.
  *
  * This function loads a core material from a buffer.
  *
  * @param buffer 	The buffer from which the core material should be loaded.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMaterial(void* buffer)
{
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core material
  CalCoreMaterialPtr pCoreMaterial = CalLoader::loadCoreMaterial(buffer);
  if(!pCoreMaterial) return -1;

  // add core material to this core model
  int materialId = addCoreMaterial(pCoreMaterial.get());
  if(materialId == -1)
  {
    return -1;
  }

  return materialId;
}

 /*****************************************************************************/
/** Delete the resources used by the named core material. The name must 
  * be associated with a valid core material Id with the function
  * getMaterialId. The caller must ensure that the corresponding is not
  * referenced anywhere otherwise unpredictable results will occur.
  *
  * @param name The symbolic name of the core material to unload.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::unloadCoreMaterial(const std::string& name)
{
  int id = getCoreMaterialId(name);
  if(id >= 0)
    return unloadCoreMaterial(id);
  else
    return -1;
}

 /*****************************************************************************/
/** Delete the resources used by a core material. The caller must
  * ensure that the corresponding is not referenced anywhere otherwise
  * unpredictable results will occur.
  *
  * @param coreMaterialId The ID of the core material that should be unloaded.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/


int UN_CoreModel::unloadCoreMaterial(int coreMaterialId)
{
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  m_vectorCoreMaterial[coreMaterialId] = CalCoreMaterialPtr(0);

  return coreMaterialId;
}

 /*****************************************************************************/
/** Loads a core mesh.
  *
  * This function loads a core mesh from a file.
  *
  * @param strFilename The file from which the core mesh should be loaded from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMesh(const std::string& strFilename)
{
  // the core skeleton has to be loaded already
  if(!m_pCoreSkeleton)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core mesh
  CalCoreMeshPtr pCoreMesh = CalLoader::loadCoreMesh(strFilename);
  if(!pCoreMesh) return -1;

  // add core mesh to this core model
  return addCoreMesh(pCoreMesh.get());
}

 /*****************************************************************************/
/** Loads a core mesh and bind it to a name.
  *
  * This function loads a core mesh from a file. It is equivalent
  * to calling addMeshName(strMeshName, loadCoreMesh(strFilename)).
  * If strMeshName is already associated to a coreMeshId because
  * of a previous call to addMeshName, the same coreMeshId will
  * be used. 
  *
  * @param strFilename The file from which the core mesh should be loaded
  *                    from.
  * @param strMeshName A string that is associated with an anim ID number.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMesh(const std::string& strFilename, const std::string& strMeshName)
{
  int id = -1;
  std::map<std::string, int>::iterator it = m_meshName.find(strMeshName);
  if (it != m_meshName.end())
  {
    id=(*it).second;

    // the core skeleton has to be loaded already
    if(!m_pCoreSkeleton)
    {
      CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
      return -1;
    }
    if(m_vectorCoreMesh[id])
    {
      CalError::setLastError(CalError::INDEX_BUILD_FAILED, __FILE__, __LINE__);
      return -1;
    }
    CalCoreMeshPtr pCoreMesh = CalLoader::loadCoreMesh(strFilename);
    if(!pCoreMesh) return -1;
    pCoreMesh->setName(strMeshName);
    m_vectorCoreMesh[id] = pCoreMesh;
  }
  else
  {
    id = loadCoreMesh(strFilename);
    if(id >= 0)
      addMeshName(strMeshName, id);
  }

  return id;
}

 /*****************************************************************************/
/** Loads a core mesh.
  *
  * This function loads a core mesh from a buffer.
  *
  * @param buffer 	The buffer from which the core mesh should be loaded.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::loadCoreMesh(void* buffer)
{
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core mesh
  CalCoreMeshPtr pCoreMesh = CalLoader::loadCoreMesh(buffer);
  if (!pCoreMesh) return -1;

  // add core mesh to this core model
  int meshId;
  meshId = addCoreMesh(pCoreMesh.get());
  if(meshId == -1)
  {
    return -1;
  }

  return meshId;
}


 /*****************************************************************************/
/** Delete the resources used by the named core mesh. The name must 
  * be associated with a valid core mesh Id with the function
  * getMeshId. The caller must ensure that the corresponding is not
  * referenced anywhere otherwise unpredictable results will occur.
  *
  * @param name The symbolic name of the core mesh to unload.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/

int UN_CoreModel::unloadCoreMesh(const std::string& name)
{
  int id = getCoreMeshId(name);
  if(id >= 0)
    return unloadCoreMesh(id);
  else
    return -1;
}

 /*****************************************************************************/
/** Delete the resources used by a core mesh. The caller must
  * ensure that the corresponding is not referenced anywhere otherwise
  * unpredictable results will occur.
  *
  * @param coreMeshId The ID of the core mesh that should be unloaded.
  *
  * @return One of the following values:
  *         \li the core \b ID of the unloaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/


int UN_CoreModel::unloadCoreMesh(int coreMeshId)
{
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  m_vectorCoreMesh[coreMeshId] = CalCoreMeshPtr(0);

  return coreMeshId;
}


 /*****************************************************************************/
/** Loads the core skeleton.
  *
  * This function loads the core skeleton from a file.
  *
  * @param strFilename The file from which the core skeleton should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::loadCoreSkeleton(const std::string& strFilename)
{
  // load a new core skeleton
  m_pCoreSkeleton = CalLoader::loadCoreSkeleton(strFilename);
  return bool(m_pCoreSkeleton);
}

 /*****************************************************************************/
/** Loads the core skeleton.
  *
  * This function loads the core skeleton from a buffer.
  *
  * @param buffer 	The buffer from which the core skeleton should be loaded.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::loadCoreSkeleton(void* buffer)
{
  // load a new core skeleton
  m_pCoreSkeleton = CalLoader::loadCoreSkeleton(buffer);
  if(!m_pCoreSkeleton) return false;

  return true;
}

 /*****************************************************************************/
/** Saves a core animation.
  *
  * This function saves a core animation to a file.
  *
  * @param strFilename The file to which the core animation should be saved to.
  * @param coreAnimationId The ID of the core animation that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::saveCoreAnimation(const std::string& strFilename, int coreAnimationId)
{
  // check if the core animation id is valid
  if((coreAnimationId < 0) || (coreAnimationId >= (int)m_vectorCoreAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  if(!CalSaver::saveCoreAnimation(strFilename, m_vectorCoreAnimation[coreAnimationId].get()))
  {
    return false;
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core material.
  *
  * This function saves a core material to a file.
  *
  * @param strFilename The file to which the core material should be saved to.
  * @param coreMaterialId The ID of the core material that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::saveCoreMaterial(const std::string& strFilename, int coreMaterialId)
{
  // check if the core material id is valid
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  return CalSaver::saveCoreMaterial(strFilename, m_vectorCoreMaterial[coreMaterialId].get());
}

 /*****************************************************************************/
/** Saves a core mesh.
  *
  * This function saves a core mesh to a file.
  *
  * @param strFilename The file to which the core mesh should be saved to.
  * @param coreMeshId The ID of the core mesh that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::saveCoreMesh(const std::string& strFilename, int coreMeshId)
{
  // check if the core mesh id is valid
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  return CalSaver::saveCoreMesh(strFilename, m_vectorCoreMesh[coreMeshId].get());
}

 /*****************************************************************************/
/** Saves the core skeleton.
  *
  * This function saves the core skeleton to a file.
  *
  * @param strFilename The file to which the core skeleton should be saved to.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::saveCoreSkeleton(const std::string& strFilename)
{
  // check if we have a core skeleton in this code model
  if(!m_pCoreSkeleton)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core skeleton
  return CalSaver::saveCoreSkeleton(strFilename, m_pCoreSkeleton.get());
}

 /*****************************************************************************/
/** Sets a core material ID.
  *
  * This function sets a core material ID for a core material thread / core
  * material set pair.
  *
  * @param coreMaterialThreadId The ID of the core material thread.
  * @param coreMaterialSetId The ID of the core maetrial set.
  * @param coreMaterialId The ID of the core maetrial.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreModel::setCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId)
{
  // find the core material thread
  std::map<int, std::map<int, int> >::iterator iteratorCoreMaterialThread;
  iteratorCoreMaterialThread = m_mapmapCoreMaterialThread.find(coreMaterialThreadId);
  if(iteratorCoreMaterialThread == m_mapmapCoreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the core material thread
  std::map<int, int>& coreMaterialThread = (*iteratorCoreMaterialThread).second;

  // remove a possible entry in the core material thread
  coreMaterialThread.erase(coreMaterialSetId);

  // set the given set id in the core material thread to the given core material id
  coreMaterialThread.insert(std::make_pair(coreMaterialSetId, coreMaterialId));

  return true;
}

 /*****************************************************************************/
/** Sets the core skeleton.
  *
  * This function sets the core skeleton of the core model instance..
  *
  * @param pCoreSkeleton The core skeleton that should be set.
  *****************************************************************************/

void UN_CoreModel::setCoreSkeleton(CalCoreSkeleton *pCoreSkeleton)
{
  if(pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return;
  }
  m_pCoreSkeleton = pCoreSkeleton;  
}

 /*****************************************************************************/
/** Stores user data.
  *
  * This function stores user data in the core model instance.
  *
  * @param userData The user data that should be stored.
  *****************************************************************************/

void UN_CoreModel::setUserData(Cal::UserData userData)
{
  m_userData = userData;
}

 /*****************************************************************************/
/** Creates or overwrites a string-to-boneId mapping
  *
  * This function makes a bone ID reference-able by a string name.
  *
  * @param strBoneName The string that will be associated with the ID.
  * @param boneId The ID number of the bone that will be referenced by the string.
  *****************************************************************************/

void UN_CoreModel::addBoneName(const std::string& strBoneName, int boneId)
{
  //Make sure the skeleton has been loaded first
  if (m_pCoreSkeleton)
  {
    //Map the bone ID to the name
    m_pCoreSkeleton->mapCoreBoneName(boneId, strBoneName);
  }
}

 /*****************************************************************************/
/** Retrieves the ID of the bone referenced by a string
  *
  * This function returns a bone ID
  *
  * @param strBoneName A string that is associated with a bone ID number.
  * @return Returns:
  *         \li \b -1 if there is no bone ID associated with the input string
  *         \li \b the ID number of the bone asssociated with the input string
  *****************************************************************************/

int UN_CoreModel::getBoneId(const std::string& strBoneName) const
{
  if (m_pCoreSkeleton)
  {
    return m_pCoreSkeleton->getCoreBoneId(strBoneName);
  }
  return -1;
}

 /*****************************************************************************/
/** Creates or overwrites a string-to-animation ID mapping
  *
  * This function makes an animation ID reference-able by a string name.
  * Note that we don't verify that the ID is valid because the animation
  * may be added later.
  * Also, if there is already a helper with this name, it will be overwritten
  * without warning.
  *
  * @param strAnimationName The string that will be associated with the ID.
  * @param coreAnimationId The ID number of the animation to be referenced by the string.
  *****************************************************************************/

bool UN_CoreModel::addAnimationName(const std::string& strAnimationName, int coreAnimationId)
{
  // check if the core animation id is valid
  if((coreAnimationId < 0) || (coreAnimationId >= (int)m_vectorCoreAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  m_vectorCoreAnimation[ coreAnimationId ]->setName(strAnimationName);
  m_animationName[ strAnimationName ] = coreAnimationId;
  return true;
}

 /*****************************************************************************/
/** Retrieves the ID of the animation referenced by a string
  *
  * This function returns an animation ID
  *
  * @param strAnimationName A string that is associated with an anim ID number.
  * @return Returns:
  *         \li \b -1 if there is no anim ID associated with the input string
  *         \li \b the ID number of the anim asssociated with the input string
  *****************************************************************************/

int UN_CoreModel::getCoreAnimationId(const std::string& strAnimationName)
{
  if (m_animationName.count( strAnimationName ) < 1)
  {
    return -1;
  }
   
  if (getCoreAnimation(m_animationName[strAnimationName]) == NULL)
  {
    return -1;
  }

  return m_animationName[strAnimationName];
}

 /*****************************************************************************/
/** Creates or overwrites a string-to-core-material ID mapping
  *
  * This function makes a core material ID reference-able by a string name.
  * Note that we don't verify that the ID is valid because the material
  * may be added later.
  * Also, if there is already a helper with this name, it will be overwritten
  * without warning.
  *
  * @param strMaterialName The string that will be associated with the ID.
  * @param coreMaterialId The core ID number of the material to be referenced by the string.
  *****************************************************************************/

bool UN_CoreModel::addMaterialName(const std::string& strMaterialName, int coreMaterialId)
{
  
  // check if the core material id is valid
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  m_vectorCoreMaterial[ coreMaterialId ]->setName(strMaterialName);
  m_materialName[ strMaterialName ] = coreMaterialId;
  return true;
}

 /*****************************************************************************/
/** Retrieves the ID of the core material referenced by a string
  *
  * This function returns a core material ID
  *
  * @param strMaterialName A string that is associated with a core material ID number.
  * @return Returns:
  *         \li \b -1 if there is no core material ID associated with the input string
  *         \li \b the core ID number of the material asssociated with the input string
  *****************************************************************************/

int UN_CoreModel::getCoreMaterialId(const std::string& strMaterialName)
{
  if (m_materialName.count( strMaterialName ) < 1)
  {
    return -1;
  }

  if (getCoreMaterial(m_materialName[strMaterialName]) == NULL) 
  {
    return -1;
  }

  return m_materialName[strMaterialName];
}


 /*****************************************************************************/
/** Creates or overwrites a string-to-core-mesh ID mapping
  *
  * This function makes a core mesh ID reference-able by a string name.
  * Note that we don't verify that the ID is valid because the mesh
  * may be added later.
  * Also, if there is already a helper with this name, it will be overwritten
  * without warning.
  *
  * @param strMeshName The string that will be associated with the ID.
  * @param coreMeshId The core ID number of the mesh to be referenced by the string.
  *****************************************************************************/

bool UN_CoreModel::addMeshName(const std::string& strMeshName, int coreMeshId)
{
  // check if the core mesh id is valid
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  m_vectorCoreMesh[ coreMeshId ]->setName(strMeshName);
  m_meshName[ strMeshName ] = coreMeshId;
  return true;
}

 /*****************************************************************************/
/** Retrieves the ID of the core mesh referenced by a string
  *
  * This function returns a core mesh ID
  *
  * @param strMeshName A string that is associated with a core mesh ID number.
  * @return Returns:
  *         \li \b -1 if there is no core mesh ID associated with the input string
  *         \li \b the core ID number of the mesh asssociated with the input string
  *****************************************************************************/

int UN_CoreModel::getCoreMeshId(const std::string& strMeshName)
{
  if (m_meshName.count( strMeshName ) < 1)
  {
    return -1;
  }

  if (getCoreMesh(m_meshName[strMeshName]) == NULL)
  {
    return -1;
  }

  return m_meshName[strMeshName];
}

 /*****************************************************************************/
/** Scale the core model.
  *
  * This function rescale all data that are in the core model instance
  *
  * @param factor A float with the scale factor
  *
  *****************************************************************************/


void UN_CoreModel::scale(float factor)
{
  m_pCoreSkeleton->scale(factor);

  for(size_t animationId = 0; animationId < m_vectorCoreAnimation.size(); animationId++)
  {
    m_vectorCoreAnimation[animationId]->scale(factor);
  }

  for(size_t meshId = 0; meshId < m_vectorCoreMesh.size(); meshId++)
  {
    m_vectorCoreMesh[meshId]->scale(factor);
  }

}

//****************************************************************************//
