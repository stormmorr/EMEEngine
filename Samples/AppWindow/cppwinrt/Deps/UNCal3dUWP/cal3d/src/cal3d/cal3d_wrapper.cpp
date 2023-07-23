//****************************************************************************//
// cal3d_wrapper.cpp                                                          //
#include "pch.h" // Copyright (C) 2002 Bruno 'Beosil' Heidelberger                             //
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
// Defines                                                                    //
//****************************************************************************//

#define CAL3D_WRAPPER_EXPORTS

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/cal3d.h"
#include "cal3d/cal3d_wrapper.h"
using namespace cal3d;

//****************************************************************************//
// QunAnimation wrapper functions definition                                  //
//****************************************************************************//

void QunAnimation_Delete(QunAnimation *self)
{
  delete self;
}

QunCoreAnimation *QunAnimation_GetCoreAnimation(QunAnimation *self)
{
  return self->getCoreAnimation();
}

QunAnimationState QunAnimation_GetState(QunAnimation *self)
{
  return (QunAnimationState)(self->getState());
}

float QunAnimation_GetTime(QunAnimation *self)
{
  return self->getTime();
}

QunAnimationType QunAnimation_GetType(QunAnimation *self)
{
  return (QunAnimationType)(self->getType());
}

float QunAnimation_GetWeight(QunAnimation *self)
{
  return self->getWeight();
}

//****************************************************************************//
// QunAnimationAction wrapper functions definition                            //
//****************************************************************************//

void QunAnimationAction_Delete(QunAnimationAction *self)
{
  delete self;
}

QunBoolean QunAnimationAction_Execute(QunAnimationAction *self, float delayIn, float delayOut)
{
  return self->execute(delayIn, delayOut) ? True : False;
}

QunAnimationAction *QunAnimationAction_New(QunCoreAnimation *pCoreAnimation)
{
  return new(std::nothrow) QunAnimationAction(pCoreAnimation);
}

QunBoolean QunAnimationAction_Update(QunAnimationAction *self, float deltaTime)
{
  return self->update(deltaTime) ? True : False;
}

void QunCoreAnimation_Scale(QunCoreAnimation *self, float factor)
{
  self->scale(factor);
}


//****************************************************************************//
// QunAnimationCycle wrapper functions definition                             //
//****************************************************************************//

QunBoolean QunAnimationCycle_Blend(QunAnimationCycle *self, float weight, float delay)
{
  return self->blend(weight, delay) ? True : False;
}

void QunAnimationCycle_Delete(QunAnimationCycle *self)
{
  delete self;
}

QunAnimationCycle *QunAnimationCycle_New(QunCoreAnimation *pCoreAnimation)
{
  return new(std::nothrow) QunAnimationCycle(pCoreAnimation);
}

void QunAnimationCycle_SetAsync(QunAnimationCycle *self, float time, float duration)
{
  self->setAsync(time, duration);
}

QunBoolean QunAnimationCycle_Update(QunAnimationCycle *self, float deltaTime)
{
  return self->update(deltaTime) ? True : False;
}

//****************************************************************************//
// QunBone wrapper functions definition                                           //
//****************************************************************************//

void QunBone_BlendState(QunBone *self, float weight, QunVector *pTranslation, QunQuaternion *pRotation)
{
  self->blendState(weight, *pTranslation, *pRotation);
}

void QunBone_QunculateState(QunBone *self)
{
  self->calculateState();
}

void QunBone_ClearState(QunBone *self)
{
  self->clearState();
}

void QunBone_Delete(QunBone *self)
{
  delete self;
}

QunCoreBone *QunBone_GetCoreBone(QunBone *self)
{
  return self->getCoreBone();
}

QunQuaternion *QunBone_GetRotation(QunBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotation()));
}

QunQuaternion *QunBone_GetRotationAbsolute(QunBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotationAbsolute()));
}

QunQuaternion *QunBone_GetRotationBoneSpace(QunBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotationBoneSpace()));
}

QunVector *QunBone_GetTranslation(QunBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslation()));
}

QunVector *QunBone_GetTranslationAbsolute(QunBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslationAbsolute()));
}

QunVector *QunBone_GetTranslationBoneSpace(QunBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslationBoneSpace()));
}

void QunBone_LockState(QunBone *self)
{
  self->lockState();
}

QunBone *QunBone_New(QunCoreBone* coreBone)
{
  return new(std::nothrow) QunBone(coreBone);
}

void QunBone_SetSkeleton(QunBone *self, QunSkeleton *pSkeleton)
{
  self->setSkeleton(pSkeleton);
}

void QunBone_SetRotation(QunBone *self, QunQuaternion *pRotation)
{
  self->setRotation(*pRotation);
}

void QunBone_SetTranslation(QunBone *self, QunVector *pTranslation)
{
  self->setTranslation(*pTranslation);
}

void QunBone_SetCoreState(QunBone *self)
{
  self->setCoreState();
}

void QunBone_SetCoreStateRecursive(QunBone *self)
{
  self->setCoreStateRecursive();
}

QunBoolean QunBone_GetBoundingBox( struct QunBone *self, struct QunCoreModel* model,
  													float* outEightPoints )
{
	QunBoolean	gotBounds = False;
	
	QunCoreBone*	coreBone = self->getCoreBone();
	
	if (!coreBone->isBoundingBoxPrecomputed())
	{
		coreBone->calculateBoundingBox( model );
	}
	
	// If a bone owns no vertices, then the box of the core bone will stay at its initialized value,
	// in which the d members are -1e32.
	QunBoundingBox&	coreBox( coreBone->getBoundingBox() );
	if (fabsf(coreBox.plane[0].d) < 1e7)
	{
		self->calculateBoundingBox();

		QunBoundingBox&	box( self->getBoundingBox() );
		box.computePoints( reinterpret_cast<QunVector*>(outEightPoints) );
		gotBounds = True;
	}
	
	return gotBounds;
}


//****************************************************************************//
// QunCoreAnimation wrapper functions definition                              //
//****************************************************************************//

QunCoreAnimation *QunCoreAnimation_New()
{
    return explicitIncRef(new(std::nothrow) QunCoreAnimation());
}

void QunCoreAnimation_Delete(QunCoreAnimation* self)
{
    explicitDecRef(self);
}

float QunCoreAnimation_GetDuration(QunCoreAnimation *self)
{
  return self->getDuration();
}

void QunCoreAnimation_SetDuration(QunCoreAnimation *self, float duration)
{
  self->setDuration(duration);
}

//****************************************************************************//
// QunCoreBone wrapper functions definition                                   //
//****************************************************************************//

QunBoolean QunCoreBone_AddChildId(QunCoreBone *self, int childId)
{
  return self->addChildId(childId) ? True : False;
}

void QunCoreBone_QunculateState(QunCoreBone *self)
{
  self->calculateState();
}

void QunCoreBone_Delete(QunCoreBone *self)
{
  delete self;
}

/*
std::list<int>& QunCoreBone_GetListChildId(QunCoreBone *self)
{
  return self->getListChildId();
}
*/

const char *QunCoreBone_GetName(QunCoreBone *self)
{
  return self->getName().c_str();
}

void QunCoreBone_SetName(struct QunCoreBone *self, const char* name )
{
	try
	{
		self->setName( name );
	}
	catch (...)
	{
	}
}

int QunCoreBone_GetParentId(QunCoreBone *self)
{
  return self->getParentId();
}

int QunCoreBone_GetChildCount( struct QunCoreBone *self )
{
	return self->getListChildId().size();
}

int QunCoreBone_GetChildId( struct QunCoreBone *self, int childIndex )
{
	int	childBoneID = -1;
	std::list<int>&		childBoneIDs( self->getListChildId() );
	if (childIndex < childBoneIDs.size())
	{
		std::list<int>::iterator i = childBoneIDs.begin();
		while (childIndex > 0)
		{
			++i;
			--childIndex;
		}
		childBoneID = *i;
	}
	return childBoneID;
}

QunQuaternion *QunCoreBone_GetRotation(QunCoreBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotation()));
}

QunQuaternion *QunCoreBone_GetRotationAbsolute(QunCoreBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotationAbsolute()));
}

QunQuaternion *QunCoreBone_GetRotationBoneSpace(QunCoreBone *self)
{
  return &(const_cast<QunQuaternion&>(self->getRotationBoneSpace()));
}

QunVector *QunCoreBone_GetTranslation(QunCoreBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslation()));
}

QunVector *QunCoreBone_GetTranslationAbsolute(QunCoreBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslationAbsolute()));
}

QunVector *QunCoreBone_GetTranslationBoneSpace(QunCoreBone *self)
{
  return &(const_cast<QunVector&>(self->getTranslationBoneSpace()));
}

QunUserData QunCoreBone_GetUserData(QunCoreBone *self)
{
  return self->getUserData();
}

QunCoreBone *QunCoreBone_New(const char* name)
{
  return new(std::nothrow) QunCoreBone(name);
}

void QunCoreBone_SetCoreSkeleton(QunCoreBone *self, QunCoreSkeleton *pCoreSkeleton)
{
  self->setCoreSkeleton(pCoreSkeleton);
}

void QunCoreBone_SetParentId(QunCoreBone *self, int parentId)
{
  self->setParentId(parentId);
}

void QunCoreBone_SetRotation(QunCoreBone *self, QunQuaternion *pRotation)
{
  self->setRotation(*pRotation);
}

void QunCoreBone_SetRotationBoneSpace(QunCoreBone *self, QunQuaternion *pRotation)
{
  self->setRotationBoneSpace(*pRotation);
}

void QunCoreBone_SetTranslation(QunCoreBone *self, QunVector *pTranslation)
{
  self->setTranslation(*pTranslation);
}

void QunCoreBone_SetTranslationBoneSpace(QunCoreBone *self, QunVector *pTranslation)
{
  self->setTranslationBoneSpace(*pTranslation);
}

void QunCoreBone_SetUserData(QunCoreBone *self, QunUserData userData)
{
  self->setUserData(userData);
}

QunBoolean QunCoreBone_GetBoundingBox( struct QunCoreBone *self, struct QunCoreModel* model,
  								float* outEightPoints )
{
	QunBoolean	gotBounds = False;
	
	if (! self->isBoundingBoxPrecomputed())
	{
		self->calculateBoundingBox( model );
	}
	
	QunBoundingBox&	box( self->getBoundingBox() );
	
	// If a bone owns no vertices, then the box will stay at its initialized value,
	// in which the d members are -1e32.
	if (box.plane[0].d > -1e31)
	{
		box.computePoints( reinterpret_cast<QunVector*>(outEightPoints) );
		gotBounds = True;
	}
	
	return gotBounds;
}

//****************************************************************************//
// QunCoreMaterial wrapper functions definition                               //
//****************************************************************************//

QunCoreMaterial *QunCoreMaterial_New()
{
    return explicitIncRef(new(std::nothrow) QunCoreMaterial());
}

void QunCoreMaterial_Delete(QunCoreMaterial *self)
{
    explicitDecRef(self);
}

/*
QunCoreMaterial::Color *QunCoreMaterial_GetAmbientColor(QunCoreMaterial *self)
{
  return &(self->getAmbientColor());
}
*/

/*
QunCoreMaterial::Color *QunCoreMaterial_GetDiffuseColor(QunCoreMaterial *self)
{
  return &(self->getDiffuseColor());
}
*/

static QunColorValue	ColorToValue( const QunCoreMaterial::Color& inColor )
{
	QunColorValue	theValue = (((QunColorValue) inColor.red) << 24) |
		(((QunColorValue) inColor.green) << 16) |
		(((QunColorValue) inColor.blue) << 8) |
		(((QunColorValue) inColor.alpha) << 0);
	return theValue;
}

static QunCoreMaterial::Color ValueToColor( QunColorValue inValue )
{
	QunCoreMaterial::Color	theColor = {
		inValue >> 24,
		(inValue & 0x00FF0000) >> 16,
		(inValue & 0x0000FF00) >> 8,
		(inValue & 0x000000FF)
	};
	return theColor;
}

QunColorValue QunCoreMaterial_GetAmbientColor(struct QunCoreMaterial *self)
{
	return ColorToValue( self->getAmbientColor() );
}

QunColorValue QunCoreMaterial_GetDiffuseColor(struct QunCoreMaterial *self)
{
	return ColorToValue( self->getDiffuseColor() );
}

QunColorValue QunCoreMaterial_GetSpecularColor(struct QunCoreMaterial *self)
{
	return ColorToValue( self->getSpecularColor() );
}

void QunCoreMaterial_SetAmbientColor(struct QunCoreMaterial *self, QunColorValue pAmbientColor)
{
	self->setAmbientColor( ValueToColor( pAmbientColor ) );
}

void QunCoreMaterial_SetDiffuseColor(struct QunCoreMaterial *self, QunColorValue pDiffuseColor)
{
	self->setDiffuseColor( ValueToColor( pDiffuseColor ) );
}

void QunCoreMaterial_SetSpecularColor(struct QunCoreMaterial *self, QunColorValue pSpecularColor)
{
	self->setSpecularColor( ValueToColor( pSpecularColor ) );
}

const char* QunCoreMaterial_GetName(struct QunCoreMaterial *self)
{
	return self->getName().c_str();
}

void QunCoreMaterial_SetName(struct QunCoreMaterial *self, const char* inName)
{
	try
	{
		self->setName( std::string(inName) );
	}
	catch (...)
	{
	}
}

int QunCoreMaterial_GetMapCount(QunCoreMaterial *self)
{
  return self->getMapCount();
}

const char *QunCoreMaterial_GetMapFilename(QunCoreMaterial *self, int mapId)
{
  return self->getMapFilename(mapId).c_str();
}

QunUserData QunCoreMaterial_GetMapUserData(QunCoreMaterial *self, int mapId)
{
  return self->getMapUserData(mapId);
}

float QunCoreMaterial_GetShininess(QunCoreMaterial *self)
{
  return self->getShininess();
}

/*
QunCoreMaterial::Color *QunCoreMaterial_GetSpecularColor(QunCoreMaterial *self)
{
  return &(self->getSpecularColor());
}
*/

QunUserData QunCoreMaterial_GetUserData(QunCoreMaterial *self)
{
  return self->getUserData();
}

/*
std::vector<Map>& QunCoreMaterial_GetVectorMap(QunCoreMaterial *self)
{
  return self->getVectorMap();
}
*/

QunBoolean QunCoreMaterial_Reserve(QunCoreMaterial *self, int mapCount)
{
  return self->reserve(mapCount) ? True : False;
}

/*
void QunCoreMaterial_SetAmbientColor(QunCoreMaterial *self, QunCoreMaterial::Color *pAmbientColor)
{
  return self->setAmbientColor(*pAmbientColor);
}
*/

/*
void QunCoreMaterial_SetDiffuseColor(QunCoreMaterial *self, QunCoreMaterial::Color *pDiffuseColor)
{
  self->setDiffuseColor(*pDiffuseColor);
}
*/

/*
QunBoolean QunCoreMaterial_SetMap(QunCoreMaterial *self, int mapId, QunCoreMaterial::Map *pMap)
{
  return self->setMap(mapId, *pMap) ? True : False;
}
*/

QunBoolean QunCoreMaterial_SetMapUserData(QunCoreMaterial *self, int mapId, QunUserData userData)
{
  return self->setMapUserData(mapId, userData) ? True : False;
}

void QunCoreMaterial_SetShininess(QunCoreMaterial *self, float shininess)
{
  self->setShininess(shininess);
}

/*
void QunCoreMaterial_SetSpecularColor(QunCoreMaterial *self, QunCoreMaterial::Color *pSpecularColor)
{
  self->setSpecularColor(*pSpecularColor);
}
*/

void QunCoreMaterial_SetUserData(QunCoreMaterial *self, QunUserData userData)
{
  self->setUserData(userData);
}

//****************************************************************************//
// QunCoreMesh wrapper functions definition                                   //
//****************************************************************************//

QunCoreMesh *QunCoreMesh_New()
{
    return explicitIncRef(new(std::nothrow) QunCoreMesh());
}

void QunCoreMesh_Delete(QunCoreMesh *self)
{
    explicitDecRef(self);
}

int QunCoreMesh_AddCoreSubmesh(QunCoreMesh *self, QunCoreSubmesh *pCoreSubmesh)
{
	try
	{
		return self->addCoreSubmesh(pCoreSubmesh);
	}
	catch (...)
	{
	}
	return -1;
}

void QunCoreMesh_RemoveCoreSubmesh( struct QunCoreMesh *self, int coreSubmeshID )
{
	self->removeCoreSubmesh( coreSubmeshID );
}

const char* QunCoreMesh_GetName(struct QunCoreMesh *self)
{
	return self->getName().c_str();
}

void QunCoreMesh_SetName(struct QunCoreMesh *self, const char* inName)
{
	try
	{
		self->setName( std::string(inName) );
	}
	catch (...)
	{
	}
}

QunCoreSubmesh *QunCoreMesh_GetCoreSubmesh(QunCoreMesh *self, int id)
{
  return self->getCoreSubmesh(id);
}

int QunCoreMesh_GetCoreSubmeshCount(QunCoreMesh *self)
{
  return self->getCoreSubmeshCount();
}

/*
std::vector<QunCoreSubmesh *>& QunCoreMesh_GetVectorCoreSubmesh(QunCoreMesh *self)
{
  return self->getVectorCoreSubmesh();
}
*/

void QunCoreMesh_Scale(QunCoreMesh *self,float factor)
{
  self->scale(factor);
}

int QunCoreMesh_AddAsMorphTarget(struct QunCoreMesh *self, struct QunCoreMesh *target)
{
	try
	{
		return self->addAsMorphTarget(target);
	}
	catch (...)
	{
	}
	return -1;
}

//****************************************************************************//
// QunCoreModel wrapper functions definition                                  //
//****************************************************************************//

int QunCoreModel_AddCoreAnimation(QunCoreModel *self, QunCoreAnimation *pCoreAnimation)
{
	try
	{
		return self->addCoreAnimation(pCoreAnimation);
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_AddCoreMorphAnimation( struct QunCoreModel *self,
										struct QunCoreMorphAnimation* inAnim )
{
	try
	{
		return self->addCoreMorphAnimation( inAnim );
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_AddCoreMaterial(QunCoreModel *self, QunCoreMaterial *pCoreMaterial)
{
	try
	{
		return self->addCoreMaterial(pCoreMaterial);
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_AddCoreMesh(QunCoreModel *self, QunCoreMesh *pCoreMesh)
{
	try
	{
		return self->addCoreMesh(pCoreMesh);
	}
	catch (...)
	{
	}
	return -1;
}

QunBoolean QunCoreModel_CreateCoreMaterialThread(QunCoreModel *self, int coreMaterialThreadId)
{
	try
	{
		return self->createCoreMaterialThread(coreMaterialThreadId) ? True : False;
	}
	catch (...)
	{
	}
	return False;
}

void QunCoreModel_Delete(QunCoreModel *self)
{
  delete self;
}

QunCoreAnimation *QunCoreModel_GetCoreAnimation(QunCoreModel *self, int coreAnimationId)
{
  return self->getCoreAnimation(coreAnimationId);
}

int QunCoreModel_GetCoreAnimationCount(QunCoreModel *self)
{
  return self->getCoreAnimationCount();
}

QunCoreMaterial *QunCoreModel_GetCoreMaterial(QunCoreModel *self, int coreMaterialId)
{
  return self->getCoreMaterial(coreMaterialId);
}

int QunCoreModel_GetCoreMaterialCount(QunCoreModel *self)
{
  return self->getCoreMaterialCount();
}

int QunCoreModel_GetCoreMaterialId(QunCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId)
{
  return self->getCoreMaterialId(coreMaterialThreadId, coreMaterialSetId);
}

QunCoreMesh *QunCoreModel_GetCoreMesh(QunCoreModel *self, int coreMeshId)
{
  return self->getCoreMesh(coreMeshId);
}

int QunCoreModel_GetCoreMeshCount(QunCoreModel *self)
{
  return self->getCoreMeshCount();
}

int QunCoreModel_GetCoreMeshId(struct QunCoreModel *self, const char* coreMeshName )
{
	int	theID = -1;
	try
	{
		std::string	theName( coreMeshName );
		theID = self->getCoreMeshId( theName );
	}
	catch (...)
	{
	}
	return theID;
}

QunCoreSkeleton *QunCoreModel_GetCoreSkeleton(QunCoreModel *self)
{
  return self->getCoreSkeleton();
}

QunUserData QunCoreModel_GetUserData(QunCoreModel *self)
{
  return self->getUserData();
}

int QunCoreModel_GetCoreMorphAnimationCount(QunCoreModel *self)
{
  return self->getCoreMorphAnimationCount();
}

struct QunCoreMorphAnimation* QunCoreModel_GetCoreMorphAnimation( struct QunCoreModel *self,
																int morphAnimID )
{
	return self->getCoreMorphAnimation( morphAnimID );
}

QunBoolean QunCoreModel_AddMeshName(struct QunCoreModel *self, const char* name, int coreMeshId )
{
	QunBoolean	success = False;
	
	try
	{
		std::string		meshName( name );
		if (self->addMeshName( meshName, coreMeshId ))
		{
			success = True;
		}
	}
	catch (...)
	{
	}
	
	return success;
}

void QunCoreModel_CloneCoreMaterials(struct QunCoreModel *self )
{
	try
	{
		self->cloneCoreMaterials();
	}
	catch (...)
	{
	}
}

int QunCoreModel_LoadCoreAnimation(QunCoreModel *self, const char *strFilename)
{
	try
	{
		return self->loadCoreAnimation(strFilename);
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_LoadCoreAnimationFromBuffer(QunCoreModel *self, const void* buffer)
{
	try
	{
		return self->loadCoreAnimation(const_cast<void*>(buffer));
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_LoadCoreMaterial(QunCoreModel *self, const char *strFilename)
{
	try
	{
		return self->loadCoreMaterial(strFilename);
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_LoadCoreMaterialFromBuffer(QunCoreModel *self, const void* buffer)
{
	try
	{
		return self->loadCoreMaterial(const_cast<void*>(buffer));
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_LoadCoreMesh(QunCoreModel *self, const char *strFilename)
{
	try
	{
		return self->loadCoreMesh(strFilename);
	}
	catch (...)
	{
	}
	return -1;
}

int QunCoreModel_LoadCoreMeshFromBuffer(QunCoreModel *self, const void* buffer)
{
	try
	{
		return self->loadCoreMesh(const_cast<void*>(buffer));
	}
	catch (...)
	{
	}
	return -1;
}

QunBoolean QunCoreModel_LoadCoreSkeleton(QunCoreModel *self, const char *strFilename)
{
	try
	{
		return self->loadCoreSkeleton(strFilename) ? True : False;
	}
	catch (...)
	{
	}
	return False;
}

QunBoolean QunCoreModel_LoadCoreSkeletonFromBuffer(QunCoreModel *self, const void* buffer)
{
	try
	{
		return self->loadCoreSkeleton(const_cast<void*>(buffer)) ? True : False;
	}
	catch (...)
	{
	}
	return False;
}

QunCoreModel *QunCoreModel_New(const char* name)
{
  return new(std::nothrow) QunCoreModel(name);
}

QunCoreModel *QunCoreModel_NewCopy( QunCoreModel* other )
{
  return new(std::nothrow) QunCoreModel(*other);
}

void QunCoreModel_ReplaceCoreMesh(struct QunCoreModel *self, int coreMeshId, struct QunCoreMesh *pCoreMesh)
{
	self->replaceCoreMesh( coreMeshId, pCoreMesh );
}

QunBoolean QunCoreModel_SaveCoreAnimation(QunCoreModel *self, const char *strFilename, int coreAnimationId)
{
  return self->saveCoreAnimation(strFilename, coreAnimationId) ? True : False;
}

QunBoolean QunCoreModel_SaveCoreMaterial(QunCoreModel *self, const char *strFilename, int coreMaterialId)
{
  return self->saveCoreMaterial(strFilename, coreMaterialId) ? True : False;
}

QunBoolean QunCoreModel_SaveCoreMesh(QunCoreModel *self, const char *strFilename, int coreMeshId)
{
  return self->saveCoreMesh(strFilename, coreMeshId) ? True : False;
}

QunBoolean QunCoreModel_SaveCoreSkeleton(QunCoreModel *self, const char *strFilename)
{
  return self->saveCoreSkeleton(strFilename) ? True : False;
}

QunBoolean QunCoreModel_SetCoreMaterialId(QunCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId)
{
  return self->setCoreMaterialId(coreMaterialThreadId, coreMaterialSetId, coreMaterialId) ? True : False;
}

void QunCoreModel_SetCoreSkeleton(QunCoreModel *self, QunCoreSkeleton *pCoreSkeleton)
{
  self->setCoreSkeleton(pCoreSkeleton);
}

void QunCoreModel_SetUserData(QunCoreModel *self, QunUserData userData)
{
  self->setUserData(userData);
}

const char *QunCoreModel_GetName(QunCoreModel *self)
{
  return self->getName().c_str();
}

void QunCoreModel_SetName(struct QunCoreModel *self, const char* inName)
{
	try
	{
		self->setName( inName );
	}
	catch (...)
	{
	}
}

//****************************************************************************//
// QunCoreMorphAnimation wrapper functions definition                         //
//****************************************************************************//

QunCoreMorphAnimation *QunCoreMorphAnimation_New()
{
    return new(std::nothrow) QunCoreMorphAnimation();
}

void QunCoreMorphAnimation_Delete(QunCoreMorphAnimation* self)
{
    delete self;
}

QunBoolean QunCoreMorphAnimation_AddMorphTarget(struct QunCoreMorphAnimation* self, int meshID, int morphID)
{
	QunBoolean	result = False;
	try
	{
		result = self->addMorphTarget( meshID, morphID ) ? True : False;
	}
	catch (...)
	{
	}
	return result;
}

const char* QunCoreMorphAnimation_GetName( const struct QunCoreMorphAnimation *self )
{
	return self->getName().c_str();
}

void QunCoreMorphAnimation_SetName(struct QunCoreMorphAnimation *self, const char* inName )
{
	try
	{
		self->setName( inName );
	}
	catch (...)
	{
	}
}

//****************************************************************************//
// QunCoreSkeleton wrapper functions definition                               //
//****************************************************************************//

int QunCoreSkeleton_AddCoreBone(QunCoreSkeleton *self, QunCoreBone *pCoreBone)
{
	try
	{
		return self->addCoreBone(pCoreBone);
	}
	catch (...)
	{
	}
	return -1;
}

void QunCoreSkeleton_QunculateState(QunCoreSkeleton *self)
{
  self->calculateState();
}


QunCoreSkeleton *QunCoreSkeleton_New()
{
    return explicitIncRef(new(std::nothrow) QunCoreSkeleton());
}

void QunCoreSkeleton_Delete(QunCoreSkeleton *self)
{
    explicitDecRef(self);
}

QunCoreBone *QunCoreSkeleton_GetCoreBone(QunCoreSkeleton *self, int coreBoneId)
{
  return self->getCoreBone(coreBoneId);
}

int QunCoreSkeleton_GetCoreBoneCount(QunCoreSkeleton *self)
{
	return self->getVectorCoreBone().size();
}

int QunCoreSkeleton_GetCoreBoneId(QunCoreSkeleton *self, const char *strName)
{
  return self->getCoreBoneId(strName);
}

/*
std::list<int>& QunCoreSkeleton_GetListRootCoreBoneId(QunCoreSkeleton *self)
{
  return self->getlistRootCoreBoneId();
}
*/


/*
std::vector<QunCoreBone *>& QunCoreSkeleton_GetVectorCoreBone(QunCoreSkeleton *self)
{
  return self->getVectorCoreBone();
}
*/

void QunCoreSkeleton_Scale(QunCoreSkeleton *self,float factor)
{
	self->scale(factor);
}

QunBoolean QunCoreSkeleton_MapCoreBoneName( struct QunCoreSkeleton *self, int coreBoneID,
										const char* name )
{
	return static_cast<QunBoolean>( self->mapCoreBoneName( coreBoneID, name ) );
}

int QunCoreSkeleton_GetRootCoreBoneCount(QunCoreSkeleton *self)
{
	return self->getVectorRootCoreBoneId().size();
}

QunCoreBone *QunCoreSkeleton_GetRootCoreBone(QunCoreSkeleton *self, int rootBoneIndex)
{
	QunCoreBone*	theBone = NULL;
	std::vector<int>&	rootIDs( self->getVectorRootCoreBoneId() );
	if ( (rootBoneIndex >= 0) && (rootBoneIndex < rootIDs.size()) )
	{
		int	boneID = rootIDs[ rootBoneIndex ];
		theBone = QunCoreSkeleton_GetCoreBone( self, boneID );
	}
	return theBone;
}

void QunCoreSkeleton_QunculateBoundingBoxes( struct QunCoreModel* coreModel )
{
	QunCoreSkeleton*	coreSkel = QunCoreModel_GetCoreSkeleton( coreModel );
	coreSkel->calculateBoundingBoxes( coreModel );
}

//****************************************************************************//
// QunCoreSubmesh wrapper functions definition                                //
//****************************************************************************//

void QunCoreSubmesh_Delete(QunCoreSubmesh *self)
{
  delete self;
}

int QunCoreSubmesh_GetCoreMaterialThreadId(QunCoreSubmesh *self)
{
  return self->getCoreMaterialThreadId();
}

int QunCoreSubmesh_GetFaceCount(QunCoreSubmesh *self)
{
  return self->getFaceCount();
}

int QunCoreSubmesh_GetLodCount(QunCoreSubmesh *self)
{
  return self->getLodCount();
}

int QunCoreSubmesh_GetSpringCount(QunCoreSubmesh *self)
{
  return self->getSpringCount();
}

/*
std::vector<QunCoreSubmesh::Face>& QunCoreSubmesh_GetVectorFace(QunCoreSubmesh *self)
{
  return self->getVectorFace();
}
*/

/*
std::vector<QunCoreSubmesh::PhysicalProperty>& QunCoreSubmesh_GetVectorPhysicalProperty(QunCoreSubmesh *self)
{
  return self->getVectorPhysicalProperty();
}
*/

/*
std::vector<QunCoreSubmesh::Spring>& QunCoreSubmesh_GetVectorSpring(QunCoreSubmesh *self)
{
  return self->getVectorSpring();
}
*/

/*
std::vector<std::vector<QunCoreSubmesh::TextureCoordinate> >& QunCoreSubmesh_GetVectorVectorTextureCoordinate(QunCoreSubmesh *self)
{
  return self->getVectorVectorTextureCoordinate();
}
*/

/*
std::vector<QunCoreSubmesh::Vertex>& QunCoreSubmesh_GetVectorVertex(QunCoreSubmesh *self)
{
  return self->getVectorVertex();
}
*/

int QunCoreSubmesh_GetVertexCount(QunCoreSubmesh *self)
{
  return self->getVertexCount();
}

int QunCoreSubmesh_GetVertexInfluenceCount( struct QunCoreSubmesh *self, int vertID )
{
	return self->getVectorVertex()[ vertID ].vectorInfluence.size();
}

int QunCoreSubmesh_GetVertexInfluence( struct QunCoreSubmesh *self, int vertID,
									int influenceID, float* outWeight )
{
	QunCoreSubmesh::Influence&	theInfluence =
		self->getVectorVertex()[ vertID ].vectorInfluence[ influenceID ];
	
	*outWeight = theInfluence.weight;
	return theInfluence.boneId;
}

QunCoreSubmesh *QunCoreSubmesh_New()
{
  return new(std::nothrow) QunCoreSubmesh();
}

void QunCoreSubmesh_GetVertex( struct QunCoreSubmesh* self, int vertID, float* outPosition, float* outNormal )
{
	std::vector<QunCoreSubmesh::Vertex>&	vertices( self->getVectorVertex() );
	if ( (vertID >= 0) && (vertID < vertices.size()) )
	{
		QunCoreSubmesh::Vertex&		theVertex( vertices[ vertID ] );
		
		outPosition[0] = theVertex.position.x;
		outPosition[1] = theVertex.position.y;
		outPosition[2] = theVertex.position.z;

		outNormal[0] = theVertex.normal.x;
		outNormal[1] = theVertex.normal.y;
		outNormal[2] = theVertex.normal.z;
	}
}

QunBoolean QunCoreSubmesh_Reserve(QunCoreSubmesh *self, int vertexCount, int textureCoordinateCount, int faceCount, int springCount)
{
  return self->reserve(vertexCount, textureCoordinateCount, faceCount, springCount) ? True : False;
}

void QunCoreSubmesh_SetCoreMaterialThreadId(QunCoreSubmesh *self, int coreMaterialThreadId)
{
  self->setCoreMaterialThreadId(coreMaterialThreadId);
}

/*
QunBoolean QunCoreSubmesh_SetFace(QunCoreSubmesh *self, int faceId, QunCoreSubmesh::Face *pFace)
{
  return self->setFace(faceId, *pFace) ? True : False;
}
*/

void QunCoreSubmesh_SetLodCount(QunCoreSubmesh *self, int lodCount)
{
  self->setLodCount(lodCount);
}

/*
QunBoolean QunCoreSubmesh_SetPhysicalProperty(QunCoreSubmesh *self, int vertexId, QunCoreSubmesh::PhysicalProperty *pPhysicalProperty)
{
  return self->setPhysicalProperty(vertexId, *pPhysicalProperty) ? True : False;
}
*/

/*
QunBoolean QunCoreSubmesh_SetSpring(QunCoreSubmesh *self, int springId, QunCoreSubmesh::Spring *pSpring)
{
  return self->setSpring(springId, *pSpring) ? True : False;
}
*/

/*
QunBoolean QunCoreSubmesh_SetTextureCoordinate(QunCoreSubmesh *self, int vertexId, int textureCoordinateId, QunCoreSubmesh::TextureCoordinate *pTextureCoordinate)
{
  return self->setTextureCoordinate(vertexId, textureCoordinateId, *pTextureCoordinate) ? True : False;
}
*/

/*
QunBoolean QunCoreSubmesh_SetVertex(QunCoreSubmesh *self, int vertexId, QunCoreSubmesh::Vertex *pVertex)
{
  return self->setVertex(vertexId, *pVertex) ? True : False;
}
*/

QunBoolean QunCoreSubmesh_IsTangentsEnabled(QunCoreSubmesh *self, int mapId)
{
  return self->isTangentsEnabled(mapId) ? True : False;
}

QunBoolean QunCoreSubmesh_EnableTangents(struct QunCoreSubmesh *self, int mapId, enum QunBoolean enabled)
{
  return self->enableTangents(mapId, enabled) ? True : False;
}

int QunCoreSubmesh_AddSubMorphTarget( QunCoreSubmesh *self, QunCoreSubMorphTargetDiffMap* inTarget )
{
	int	morphTargetID = -1;
	try
	{
		morphTargetID = self->addCoreSubMorphTarget( inTarget );
	}
	catch (...)
	{
	}
	return morphTargetID;
}


const QunIndex* QunCoreSubmesh_GetFaces( struct QunCoreSubmesh *self )
{
	return &self->getVectorFace()[0].vertexId[0];
}


//****************************************************************************//
// QunCoreSubMorphTargetDiffMap wrapper functions definition                  //
//****************************************************************************//
QunCoreSubMorphTargetDiffMap* QunCoreSubMorphTargetDiffMap_New()
{
	QunCoreSubMorphTargetDiffMap*	theMap = NULL;
	try
	{
		theMap = new QunCoreSubMorphTargetDiffMap;
	}
	catch (...)
	{
	}
	return theMap;
}

QunCoreSubMorphTargetDiffMap* QunCoreSubMorphTargetDiffMap_Clone(
	const QunCoreSubMorphTargetDiffMap* inOther )
{
	QunCoreSubMorphTargetDiffMap*	theMap = NULL;
	try
	{
		theMap = new QunCoreSubMorphTargetDiffMap( *inOther );
	}
	catch (...)
	{
	}
	return theMap;
}

void QunCoreSubMorphTargetDiffMap_Delete( QunCoreSubMorphTargetDiffMap* inSelf )
{
	delete inSelf;
}

bool QunCoreSubMorphTargetDiffMap_Reserve( QunCoreSubMorphTargetDiffMap* inSelf,
	int inNumDifferences )
{
	return inSelf->reserve( inNumDifferences );
}

bool QunCoreSubMorphTargetDiffMap_AppendVertex( QunCoreSubMorphTargetDiffMap* inSelf,
	int inVertexID, float* inPositionOffset, float* inNormalOffset )
{
	QunCoreSubMorphTarget::BlendVertex	theVertex;
	theVertex.position.set( inPositionOffset[0], inPositionOffset[1], inPositionOffset[2] );
	theVertex.normal.set( inNormalOffset[0], inNormalOffset[1], inNormalOffset[2] );
	
	return inSelf->appendBlendVertex( inVertexID, theVertex );
}


//****************************************************************************//
// QunError wrapper functions definition                                      //
//****************************************************************************//

QunErrorCode QunError_GetLastErrorCode()
{
  return (QunErrorCode)QunError::getLastErrorCode();
}

const char *QunError_GetLastErrorDescription()
{
  static std::string strDescription;
  strDescription = QunError::getLastErrorDescription();

  return strDescription.c_str();
}

const char *QunError_GetLastErrorFile()
{
  return QunError::getLastErrorFile().c_str();
}

int QunError_GetLastErrorLine()
{
  return QunError::getLastErrorLine();
}

const char *QunError_GetLastErrorText()
{
  return QunError::getLastErrorText().c_str();
}

void QunError_PrintLastError()
{
  QunError::printLastError();
}

/*
void QunError_SetLastError(QunErrorCode code, char *strFile, int line, char *strText)
{
  QunError::setLastError((QunError::Code)code, strFile, line, strText);
}
*/

//****************************************************************************//
// QunLoader wrapper functions definition                                     //
//****************************************************************************//

void QunLoader_Delete(QunLoader *self)
{
  delete self;
}

QunCoreAnimation *QunLoader_LoadCoreAnimation(QunLoader *self, const char *strFilename)
{
  return explicitIncRef(self->loadCoreAnimation(strFilename).get());
}

QunCoreMaterial *QunLoader_LoadCoreMaterial(QunLoader *self, const char *strFilename)
{
  return explicitIncRef(self->loadCoreMaterial(strFilename).get());
}

QunCoreMesh *QunLoader_LoadCoreMesh(QunLoader *self, const char *strFilename)
{
  return explicitIncRef(self->loadCoreMesh(strFilename).get());
}

QunCoreMesh *QunLoader_LoadCoreMeshFromBuffer(const void *data)
{
	try
	{
		QunCoreMeshPtr	theMesh( QunLoader::loadCoreMesh(const_cast<void*>(data)) );
		
		if (theMesh.get() != NULL)
		{
			explicitIncRef( theMesh.get() );
		}
		return theMesh.get();
	}
	catch (...)
	{
	}
	return 0;
}

QunCoreSkeleton *QunLoader_LoadCoreSkeleton(QunLoader *self, const char *strFilename)
{
  return explicitIncRef(self->loadCoreSkeleton(strFilename).get());
}

QunLoader *QunLoader_New()
{
  return new QunLoader();
}

void QunLoader_SetLoadingMode( int flags )
{
	QunLoader::setLoadingMode( flags );
}

//****************************************************************************//
// QunMesh wrapper functions definition                                       //
//****************************************************************************//

void QunMesh_Delete(QunMesh *self)
{
  delete self;
}

QunCoreMesh *QunMesh_GetCoreMesh(QunMesh *self)
{
  return self->getCoreMesh();
}

QunSubmesh *QunMesh_GetSubmesh(QunMesh *self, int id)
{
  return self->getSubmesh(id);
}

int QunMesh_GetSubmeshCount(QunMesh *self)
{
  return self->getSubmeshCount();
}

/*
std::vector<QunSubmesh *>& QunMesh_GetVectorSubmesh(QunMesh *self)
{
  return self->getVectorSubmesh();
}
*/

QunMesh *QunMesh_New(QunCoreMesh *pCoreMesh)
{
  return new(std::nothrow) QunMesh(pCoreMesh);
}

void QunMesh_SetLodLevel(QunMesh *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

void QunMesh_SetMaterialSet(QunMesh *self, int setId)
{
  self->setMaterialSet(setId);
}

void QunMesh_SetModel(QunMesh *self, QunModel *pModel)
{
  self->setModel(pModel);
}

//****************************************************************************//
// QunMixer wrapper functions definition                                      //
//****************************************************************************//

QunBoolean QunMixer_BlendCycle(QunMixer *self, int id, float weight, float delay)
{
  return self->blendCycle(id, weight, delay) ? True : False;
}

QunBoolean QunMixer_ClearCycle(QunMixer *self, int id, float delay)
{
  return self->clearCycle(id, delay) ? True : False;
}

void QunMixer_Delete(QunMixer *self)
{
  delete self;
}

QunBoolean QunMixer_ExecuteAction(QunMixer *self, int id, float delayIn, float delayOut, enum QunBoolean autoLock)
{
  return self->executeAction(id, delayIn, delayOut, 1.0f,  autoLock == True ? true : false) ? True : False;
}

QunMixer *QunMixer_New(QunModel* pModel)
{
  return new(std::nothrow) QunMixer(pModel);
}

void QunMixer_UpdateAnimation(QunMixer *self, float deltaTime)
{
  self->updateAnimation(deltaTime);
}

void QunMixer_UpdateSkeleton(QunMixer *self)
{
  self->updateSkeleton();
}

void QunMixer_RemoveAction(QunMixer *self,int id)
{
  self->removeAction(id);
}

//****************************************************************************//
// QunMorphTargetMixer wrapper functions definition                           //
//****************************************************************************//

float QunMorphTargetMixer_GetCurrentWeight( struct QunMorphTargetMixer* self,
											int morphAnimID )
{
	return self->getCurrentWeight( morphAnimID );
}

QunBoolean QunMorphTargetMixer_Blend( struct QunMorphTargetMixer* self,
  							int morphAnimID, float weight, float delay )
{
  return self->blend(morphAnimID, weight, delay) ? True : False;
}

QunBoolean QunMorphTargetMixer_Clear(struct QunMorphTargetMixer *self, int id, float delay)
{
  return self->clear(id, delay) ? True : False;
}

void QunMorphTargetMixer_Delete(struct QunMorphTargetMixer *self)
{
  delete self;
}

struct QunMorphTargetMixer *QunMorphTargetMixer_New(struct QunModel *pModel)
{
  return new(std::nothrow) QunMorphTargetMixer(pModel);
}

void QunMorphTargetMixer_Update(struct QunMorphTargetMixer *self, float deltaTime)
{
  self->update(deltaTime);
}

int QunMorphTargetMixer_GetMorphTargetCount(struct QunMorphTargetMixer *self)
{
  return self->getMorphTargetCount();
}

QunBoolean QunMorphTargetMixer_Copy( struct QunMorphTargetMixer* self,
  										const struct QunMorphTargetMixer* toCopy )
{
	return (QunBoolean) self->copy( *toCopy );
}

//****************************************************************************//
// QunModel wrapper functions definition                                      //
//****************************************************************************//

QunBoolean QunModel_AttachMesh(QunModel *self, int coreMeshId)
{
	try
	{
		return self->attachMesh(coreMeshId) ? True : False;
	}
	catch (...)
	{
	}
	return False;
}

void QunModel_Delete(QunModel *self)
{
  delete self;
}

QunBoolean QunModel_DetachMesh(QunModel *self, int coreMeshId)
{
  return self->detachMesh(coreMeshId) ? True : False;
}

QunCoreModel *QunModel_GetCoreModel(QunModel *self)
{
  return self->getCoreModel();
}

QunMesh *QunModel_GetMesh(QunModel *self, int coreMeshId)
{
  return self->getMesh(coreMeshId);
}

QunMixer *QunModel_GetMixer(QunModel *self)
{
  return self->getMixer();
}

QunMorphTargetMixer *QunModel_GetMorphTargetMixer(QunModel *self)
{
  return self->getMorphTargetMixer();
}

QunPhysique *QunModel_GetPhysique(QunModel *self)
{
  return self->getPhysique();
}

void QunModel_SetPhysique(struct QunModel *self, struct QunPhysique *phys)
{
	self->setPhysique( phys );
}

QunRenderer *QunModel_GetRenderer(QunModel *self)
{
  return self->getRenderer();
}

QunSkeleton *QunModel_GetSkeleton(QunModel *self)
{
  return self->getSkeleton();
}

QunSpringSystem *QunModel_GetSpringSystem(QunModel *self)
{
  return self->getSpringSystem();
}

QunUserData QunModel_GetUserData(QunModel *self)
{
  return self->getUserData();
}

/*
std::vector<QunMesh *>& QunModel_GetVectorMesh(QunModel *self)
{
  return self->getVectorMesh();
}
*/

int QunModel_GetMeshCount(struct QunModel *self)
{
	return self->getVectorMesh().size();
}

struct QunMesh *QunModel_GetMeshByMeshID(struct QunModel *self, int meshId)
{
	QunMesh*	theMesh = 0;
	
	if ( (meshId >= 0) && (meshId < self->getVectorMesh().size()) )
	{
		theMesh = self->getVectorMesh()[ meshId ];
	}
	return theMesh;
}

QunModel *QunModel_New(QunCoreModel* pCoreModel)
{
  return new(std::nothrow) QunModel(pCoreModel);
}

void QunModel_SetLodLevel(QunModel *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

void QunModel_SetMaterialSet(QunModel *self, int setId)
{
  self->setMaterialSet(setId);
}

void QunModel_SetUserData(QunModel *self, QunUserData userData)
{
  self->setUserData(userData);
}

void QunModel_Update(QunModel *self, float deltaTime)
{
  self->update(deltaTime);
}

//****************************************************************************//
// QunPhysique wrapper functions definition                                   //
//****************************************************************************//

int QunPhysique_QunculateNormals(QunPhysique *self, QunSubmesh *pSubmesh, float *pNormalBuffer)
{
  return self->calculateNormals(pSubmesh, pNormalBuffer);
}

int QunPhysique_QunculateVertices(QunPhysique *self, QunSubmesh *pSubmesh, float *pVertexBuffer)
{
  return self->calculateVertices(pSubmesh, pVertexBuffer);
}

int QunPhysique_QunculateVerticesAndNormals(QunPhysique *self, QunSubmesh *pSubmesh, float *pVertexBuffer)
{
  return self->calculateVerticesAndNormals(pSubmesh, pVertexBuffer);
}

int QunPhysique_QunculateVerticesNormalsAndTexCoords(QunPhysique *self, QunSubmesh *pSubmesh, float *pVertexBuffer, int NumTexCoords)
{
  return self->calculateVerticesNormalsAndTexCoords(pSubmesh, pVertexBuffer, NumTexCoords);
}

int QunPhysique_QunculateTangentSpaces(QunPhysique *self, QunSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer)
{
  return self->calculateTangentSpaces(pSubmesh, mapId, pTangentSpaceBuffer);
}

void QunPhysique_Delete(QunPhysique *self)
{
  delete self;
}

QunPhysique *QunPhysique_New(QunModel* pModel)
{
  return new(std::nothrow) QunPhysique(pModel);
}

QunPhysique *QunPhysiqueDualQuat_New(QunModel* pModel)
{
  return new(std::nothrow) QunPhysiqueDualQuat(pModel);
}

void QunPhysique_Update(QunPhysique *self)
{
  self->update();
}

//****************************************************************************//
// QunPlatform wrapper functions definition                                   //
//****************************************************************************//

//****************************************************************************//
// QunQuaternion wrapper functions definition                                 //
//****************************************************************************//

void QunQuaternion_Blend(QunQuaternion *self, float d, const QunQuaternion *pQ)
{
  self->blend(d, *pQ);
}

void QunQuaternion_Clear(QunQuaternion *self)
{
  self->clear();
}

void QunQuaternion_Conjugate(QunQuaternion *self)
{
  self->conjugate();
}

void QunQuaternion_Invert(struct QunQuaternion *self)
{
	self->invert();
}

void QunQuaternion_Delete(QunQuaternion *self)
{
  delete self;
}

void QunQuaternion_Equal(QunQuaternion *self, const QunQuaternion *pQ)
{
  *self = *pQ;
}

float *QunQuaternion_Get(QunQuaternion *self)
{
  return &(self->x);
}

void QunQuaternion_Multiply(QunQuaternion *self, const QunQuaternion *pQ)
{
  *self *= *pQ;
}

void QunQuaternion_MultiplyVector(QunQuaternion *self, const QunVector *pV)
{
  *self *= *pV;
}

QunQuaternion *QunQuaternion_New()
{
  return new(std::nothrow) QunQuaternion();
}

void QunQuaternion_Op_Multiply(QunQuaternion *pResult, const QunQuaternion *pQ, const QunQuaternion *pR)
{
  *pResult = *pQ * *pR;
}

void QunQuaternion_Set(QunQuaternion *self, float qx, float qy, float qz, float qw)
{
  self->set(qx, qy, qz, qw);
}

//****************************************************************************//
// QunRender wrapper functions definition                                         //
//****************************************************************************//

QunBoolean QunRenderer_BeginRendering(QunRenderer *self)
{
  return self->beginRendering() ? True : False;
}

void QunRenderer_Delete(QunRenderer *self)
{
  delete self;
}

void QunRenderer_EndRendering(QunRenderer *self)
{
  self->endRendering();
}

void QunRenderer_GetAmbientColor(QunRenderer *self, unsigned char *pColorBuffer)
{
  self->getAmbientColor(pColorBuffer);
}

void QunRenderer_GetDiffuseColor(QunRenderer *self, unsigned char *pColorBuffer)
{
  self->getDiffuseColor(pColorBuffer);
}

int QunRenderer_GetFaceCount(QunRenderer *self)
{
  return self->getFaceCount();
}

int QunRenderer_GetFaces(QunRenderer *self, QunIndex *pFaceBuffer)
{
  return self->getFaces(pFaceBuffer);
}

int QunRenderer_GetMapCount(QunRenderer *self)
{
  return self->getMapCount();
}

QunUserData QunRenderer_GetMapUserData(QunRenderer *self, int mapId)
{
  return (QunUserData)self->getMapUserData(mapId);
}

int QunRenderer_GetMeshCount(QunRenderer *self)
{
  return self->getMeshCount();
}

int QunRenderer_GetNormals(QunRenderer *self, float *pNormalBuffer)
{
  return self->getNormals(pNormalBuffer);
}

float QunRenderer_GetShininess(QunRenderer *self)
{
  return self->getShininess();
}

void QunRenderer_GetSpecularColor(QunRenderer *self, unsigned char *pColorBuffer)
{
  self->getSpecularColor(pColorBuffer);
}

int QunRenderer_GetSubmeshCount(QunRenderer *self, int meshId)
{
  return self->getSubmeshCount(meshId);
}

int QunRenderer_GetTextureCoordinates(QunRenderer *self, int mapId, float *pTextureCoordinateBuffer)
{
  return self->getTextureCoordinates(mapId, pTextureCoordinateBuffer);
}

int QunRenderer_GetVertexCount(QunRenderer *self)
{
  return self->getVertexCount();
}

int QunRenderer_GetVertices(QunRenderer *self, float *pVertexBuffer)
{
  return self->getVertices(pVertexBuffer);
}

int QunRenderer_GetVerticesAndNormals(QunRenderer *self, float *pVertexBuffer)
{
  return self->getVerticesAndNormals(pVertexBuffer);
}

int QunRenderer_GetVerticesNormalsAndTexCoords(QunRenderer *self, float *pVertexBuffer, int NumTexCoords)
{
  return self->getVerticesNormalsAndTexCoords(pVertexBuffer,NumTexCoords);
}

int QunRenderer_GetTangentSpaces(QunRenderer *self, int mapId, float *pTangentSpaceBuffer)
{
  return self->getTangentSpaces(mapId, pTangentSpaceBuffer);
}

QunBoolean QunRenderer_IsTangentsEnabled(QunRenderer *self, int mapId)
{
  return self->isTangentsEnabled(mapId) ? True : False;
}

QunRenderer *QunRenderer_New(QunModel* pModel)
{
  return new(std::nothrow) QunRenderer(pModel);
}

QunBoolean QunRenderer_SelectMeshSubmesh(QunRenderer *self, int meshId, int submeshId)
{
  return self->selectMeshSubmesh(meshId, submeshId) ? True : False;
}

//****************************************************************************//
// QunPlatform wrapper functions definition                                   //
//****************************************************************************//

void QunSaver_Delete(QunSaver *self)
{
  delete self;
}

QunSaver *QunSaver_New()
{
  return new(std::nothrow) QunSaver();
}

QunBoolean QunSaver_SaveCoreAnimation(QunSaver *self, const char *strFilename, QunCoreAnimation *pCoreAnimation)
{
  return self->saveCoreAnimation(strFilename, pCoreAnimation) ? True : False;
}

QunBoolean QunSaver_SaveCoreMaterial(QunSaver *self, const char *strFilename, QunCoreMaterial *pCoreMaterial)
{
  return self->saveCoreMaterial(strFilename, pCoreMaterial) ? True : False;
}

QunBoolean QunSaver_SaveCoreMesh(QunSaver *self, const char *strFilename, QunCoreMesh *pCoreMesh)
{
  return self->saveCoreMesh(strFilename, pCoreMesh) ? True : False;
}

QunBoolean QunSaver_SaveCoreSkeleton(QunSaver *self, const char *strFilename, QunCoreSkeleton *pCoreSkeleton)
{
  return self->saveCoreSkeleton(strFilename, pCoreSkeleton) ? True : False;
}

//****************************************************************************//
// QunSkeleton wrapper functions definition                                   //
//****************************************************************************//

void QunSkeleton_QunculateState(QunSkeleton *self)
{
  self->calculateState();
}

void QunSkeleton_ClearState(QunSkeleton *self)
{
  self->clearState();
}

void QunSkeleton_Delete(QunSkeleton *self)
{
  delete self;
}

QunBone *QunSkeleton_GetBone(QunSkeleton *self, int boneId)
{
  return self->getBone(boneId);
}

int QunSkeleton_GetBoneCount(QunSkeleton *self)
{
	return self->getVectorBone().size();
}

QunCoreSkeleton *QunSkeleton_GetCoreSkeleton(QunSkeleton *self)
{
  return self->getCoreSkeleton();
}

/*
std::vector<QunBone *>& QunSkeleton_GetVectorBone(QunSkeleton *self)
{
  return self->getVectorBone();
}
*/

void QunSkeleton_LockState(QunSkeleton *self)
{
  self->lockState();
}

QunSkeleton *QunSkeleton_New(QunCoreSkeleton *pCoreSkeleton)
{
  return new(std::nothrow) QunSkeleton(pCoreSkeleton);
}

void QunSkeleton_GetBoneBoundingBox(QunSkeleton *self, float *min, float *max)
{
	self->getBoneBoundingBox(min, max);
}

void QunSkeleton_QunculateBoundingBoxes(QunSkeleton *self)
{
	self->calculateBoundingBoxes();
}

// DEBUG-CODE
int QunSkeleton_GetBonePoints(QunSkeleton *self, float *pPoints)
{
  return self->getBonePoints(pPoints);
}

// DEBUG-CODE
int QunSkeleton_GetBonePointsStatic(QunSkeleton *self, float *pPoints)
{
  return self->getBonePointsStatic(pPoints);
}

// DEBUG-CODE
int QunSkeleton_GetBoneLines(QunSkeleton *self, float *pLines)
{
  return self->getBoneLines(pLines);
}

// DEBUG-CODE
int QunSkeleton_GetBoneLinesStatic(QunSkeleton *self, float *pLines)
{
  return self->getBoneLinesStatic(pLines);
}

//****************************************************************************//
// QunSpringSystem wrapper functions definition                               //
//****************************************************************************//

void QunSpringSystem_QunculateForces(QunSpringSystem *self, QunSubmesh *pSubmesh, float deltaTime)
{
  self->calculateForces(pSubmesh, deltaTime);
}

void QunSpringSystem_QunculateVertices(QunSpringSystem *self, QunSubmesh *pSubmesh, float deltaTime)
{
  self->calculateVertices(pSubmesh, deltaTime);
}

void QunSpringSystem_Delete(QunSpringSystem *self)
{
  delete self;
}

QunSpringSystem *QunSpringSystem_New(QunModel* pModel)
{
  return new(std::nothrow) QunSpringSystem(pModel);
}

void QunSpringSystem_Update(QunSpringSystem *self, float deltaTime)
{
  self->update(deltaTime);
}

QunVector* QunSpringSystem_GetGravityVector(QunSpringSystem *self)
{
	return &self->getGravityVector();
}

QunVector* QunSpringSystem_GetForceVector(QunSpringSystem *self)
{
	return &self->getForceVector();
}

void QunSpringSystem_SetGravityVector(QunSpringSystem *self, QunVector* grav)
{
	self->setGravityVector( *grav );
}

void QunSpringSystem_SetForceVector(QunSpringSystem *self, QunVector* grav)
{
	self->setForceVector( *grav );
}

void QunSpringSystem_ResetPositions(struct QunSpringSystem *self)
{
	self->resetPositions();
}

//****************************************************************************//
// QunSubmesh wrapper functions definition                                    //
//****************************************************************************//

void QunSubmesh_Delete(QunSubmesh *self)
{
  delete self;
}

QunCoreSubmesh *QunSubmesh_GetCoreSubmesh(QunSubmesh *self)
{
  return self->getCoreSubmesh();
}

int QunSubmesh_GetCoreMaterialId(QunSubmesh *self)
{
  return self->getCoreMaterialId();
}

int QunSubmesh_GetFaceCount(QunSubmesh *self)
{
  return self->getFaceCount();
}

int QunSubmesh_GetFaces(QunSubmesh *self, QunIndex *pFaceBuffer)
{
  return self->getFaces(pFaceBuffer);
}

/*
std::vector<QunVector>& QunSubmesh_GetVectorNormal(QunSubmesh *self)
{
  return self->getVectorNormal();
}
*/
/*
std::vector<QunSubmesh::PhysicalProperty>& QunSubmesh_GetVectorPhysicalProperty(QunSubmesh *self)
{
  return self->getVectorPhysicalProperty();
}
*/

/*
std::vector<QunVector>& QunSubmesh_GetVectorVertex(QunSubmesh *self)
{
  return self->getVectorVertex();
}
*/

int QunSubmesh_GetVertexCount(QunSubmesh *self)
{
  return self->getVertexCount();
}

QunBoolean QunSubmesh_HasInternalData(QunSubmesh *self)
{
  return self->hasInternalData() ? True : False;
}

QunSubmesh *QunSubmesh_New(QunCoreSubmesh* coreSubmesh)
{
  return new(std::nothrow) QunSubmesh(coreSubmesh);
}

void QunSubmesh_SetCoreMaterialId(QunSubmesh *self, int coreMaterialId)
{
  self->setCoreMaterialId(coreMaterialId);
}

void QunSubmesh_SetLodLevel(QunSubmesh *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

//****************************************************************************//
// QunVector wrapper functions definition                                     //
//****************************************************************************//

void QunVector_Add(QunVector *self, QunVector *pV)
{
  *self += *pV;
}

void QunVector_Blend(QunVector *self, float d, QunVector *pV)
{
  self->blend(d, *pV);
}

void QunVector_Clear(QunVector *self)
{
  self->clear();
}

void QunVector_Delete(QunVector *self)
{
  delete self;
}

void QunVector_Equal(QunVector *self, QunVector *pV)
{
  *self = *pV;
}

void QunVector_InverseScale(QunVector *self, float d)
{
  *self /= d;
}

float *QunVector_Get(QunVector *self)
{
  return &(self->x);
}

float QunVector_Length(QunVector *self)
{
  return self->length();
}

QunVector *QunVector_New()
{
  return new(std::nothrow) QunVector();
}

float QunVector_Normalize(QunVector *self)
{
  return self->normalize();
}

void QunVector_Op_Add(QunVector *pResult, QunVector *pV, QunVector *pU)
{
  *pResult = *pV + *pU;
}

void QunVector_Op_Subtract(QunVector *pResult, QunVector *pV, QunVector *pU)
{
  *pResult = *pV - *pU;
}

void QunVector_QunVector_Op_Scale(QunVector *pResult, QunVector *pV, float d)
{
  *pResult = *pV * d;
}

void QunVector_QunVector_Op_InverseScale(QunVector *pResult, QunVector *pV, float d)
{
  *pResult = *pV / d;
}

float QunVector_Op_Scalar(QunVector *pV, QunVector *pU)
{
  return *pV * *pU;
}

void QunVector_Op_Cross(QunVector *pResult, QunVector *pV, QunVector *pU)
{
  *pResult = *pV % *pU;
}

void QunVector_Scale(QunVector *self, float d)
{
  *self *= d;
}

void QunVector_Set(QunVector *self, float vx, float vy, float vz)
{
  self->set(vx, vy, vz);
}

void QunVector_Subtract(QunVector *self, QunVector *pV)
{
  *self = *pV;
}

void QunVector_Transform(QunVector *self, QunQuaternion *pQ)
{
  *self *= *pQ;
}

//****************************************************************************//
