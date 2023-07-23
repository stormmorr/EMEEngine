//****************************************************************************//
// cal3d_wrapper.h                                                            //
// Copyright (C) 2002 Bruno 'Beosil' Heidelberger                             //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CAL3D_WRAPPER_H
#define CAL_CAL3D_WRAPPER_H

#ifdef __cplusplus
#include "cal3d/global.h"
#endif

//****************************************************************************//
// Defines for Win32 and MingW32                                              //
//****************************************************************************//

#ifdef _WIN32

#ifdef __MINGW32__

#define CAL3D_WRAPPER_API

#else

#pragma warning(disable : 4251)
#pragma warning(disable : 4786)
#pragma warning(disable : 4099)

#ifdef CAL3D_WRAPPER_EXPORTS
#define CAL3D_WRAPPER_API __declspec(dllexport)
#else
#define CAL3D_WRAPPER_API __declspec(dllimport)
#endif

#endif

#else

//****************************************************************************//
// Defines for Linux, Cygwin, FreeBSD Sun and Mips...                         //
//****************************************************************************//

#define CAL3D_WRAPPER_API

#endif 

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

#ifndef CAL3D_WRAPPER_EXPORTS

struct QunAnimation;
struct QunAnimationAction;
struct QunAnimationCycle;
struct QunBone;
struct QunCoreAnimation;
struct QunCoreMorphAnimation;
struct QunCoreBone;
struct QunCoreKeyframe;
struct QunCoreMaterial;
struct QunCoreMesh;
struct QunCoreModel;
struct QunCoreSkeleton;
struct QunCoreSubmesh;
struct QunCoreTrack;
struct QunLoader;
struct QunMatrix;
struct QunMesh;
struct QunMixer;
struct QunMorphTargetMixer;
struct QunModel;
struct QunPhysique;
struct QunPlatform;
struct QunQuaternion;
struct QunRenderer;
struct QunSaver;
struct QunSkeleton;
struct QunSpringSystem;
struct QunSubmesh;
struct QunVector;
struct QunCoreSubMorphTargetDiffMap;

#ifndef __cplusplus
typedef int QunIndex; 
#endif

#endif



typedef void *QunUserData;

typedef unsigned long QunColorValue;	// r, g, b, a in hi to lo order

//****************************************************************************//
// Substitute for the C++ 'bool' type                                         //
//****************************************************************************//

#undef True
#undef False

enum QunBoolean
{
  False = 0,
  True = 1
};

//****************************************************************************//
// "C" wrapper functions declaration                                          //
//****************************************************************************//

#ifdef __cplusplus
extern "C"
{
#endif

//****************************************************************************//
// QunAnimation wrapper functions declaration                                 //
//****************************************************************************//

  enum QunAnimationType
  {
    ANIMATION_TYPE_NONE = 0,
    ANIMATION_TYPE_CYCLE,
    ANIMATION_TYPE_POSE,
    ANIMATION_TYPE_ACTION
  };

  enum QunAnimationState
  {
    ANIMATION_STATE_NONE = 0,
    ANIMATION_STATE_SYNC,
    ANIMATION_STATE_ASYNC,
    ANIMATION_STATE_IN,
    ANIMATION_STATE_STEADY,
    ANIMATION_STATE_OUT
  };

  CAL3D_WRAPPER_API void QunAnimation_Delete(struct QunAnimation *self);
  CAL3D_WRAPPER_API struct QunCoreAnimation *QunAnimation_GetCoreAnimation(struct QunAnimation *self);
  CAL3D_WRAPPER_API enum QunAnimationState QunAnimation_GetState(struct QunAnimation *self);
  CAL3D_WRAPPER_API float QunAnimation_GetTime(struct QunAnimation *self);
  CAL3D_WRAPPER_API enum QunAnimationType QunAnimation_GetType(struct QunAnimation *self);
  CAL3D_WRAPPER_API float QunAnimation_GetWeight(struct QunAnimation *self);

//****************************************************************************//
// QunAnimationAction wrapper functions declaration                           //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunAnimationAction_Delete(struct QunAnimationAction *self);
  CAL3D_WRAPPER_API enum QunBoolean QunAnimationAction_Execute(struct QunAnimationAction *self, float delayIn, float delayOut);
  CAL3D_WRAPPER_API struct QunAnimationAction *QunAnimationAction_New(struct QunCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API enum QunBoolean QunAnimationAction_Update(struct QunAnimationAction *self, float deltaTime);
 
//****************************************************************************//
// QunAnimationCycle wrapper functions declaration                            //
//****************************************************************************//

  CAL3D_WRAPPER_API enum QunBoolean QunAnimationCycle_Blend(struct QunAnimationCycle *self, float weight, float delay);
  CAL3D_WRAPPER_API void QunAnimationCycle_Delete(struct QunAnimationCycle *self);
  CAL3D_WRAPPER_API struct QunAnimationCycle *QunAnimationCycle_New(struct QunCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API void QunAnimationCycle_SetAsync(struct QunAnimationCycle *self, float time, float duration);
  CAL3D_WRAPPER_API enum QunBoolean QunAnimationCycle_Update(struct QunAnimationCycle *self, float deltaTime);

//****************************************************************************//
// QunBone wrapper functions declaration                                      //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunBone_BlendState(struct QunBone *self, float weight, struct QunVector *pTranslation, struct QunQuaternion *pRotation);
  CAL3D_WRAPPER_API void QunBone_QunculateState(struct QunBone *self);
  CAL3D_WRAPPER_API void QunBone_ClearState(struct QunBone *self);
  CAL3D_WRAPPER_API void QunBone_Delete(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunCoreBone *QunBone_GetCoreBone(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunBone_GetRotation(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunBone_GetRotationAbsolute(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunBone_GetRotationBoneSpace(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunBone_GetTranslation(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunBone_GetTranslationAbsolute(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunBone_GetTranslationBoneSpace(struct QunBone *self);
  CAL3D_WRAPPER_API void QunBone_LockState(struct QunBone *self);
  CAL3D_WRAPPER_API struct QunBone *QunBone_New(struct QunCoreBone* coreBone);
  CAL3D_WRAPPER_API void QunBone_SetSkeleton(struct QunBone *self, struct QunSkeleton *pSkeleton);
  CAL3D_WRAPPER_API void QunBone_SetTranslation(struct QunBone *self, struct QunVector *pTranslation);
  CAL3D_WRAPPER_API void QunBone_SetRotation(struct QunBone *self, struct QunQuaternion *pRotation);
  CAL3D_WRAPPER_API void QunBone_SetCoreState(struct QunBone *self);
  CAL3D_WRAPPER_API void QunBone_SetCoreStateRecursive(struct QunBone *self);
  CAL3D_WRAPPER_API enum QunBoolean QunBone_GetBoundingBox( struct QunBone *self, struct QunCoreModel* model,
  													float* outEightPoints );


//****************************************************************************//
// QunCoreAnimation wrapper functions declaration                             //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunCoreAnimation *QunCoreAnimation_New();
  CAL3D_WRAPPER_API void QunCoreAnimation_Delete(struct QunCoreAnimation* self);

  CAL3D_WRAPPER_API float QunCoreAnimation_GetDuration(struct QunCoreAnimation *self);
  CAL3D_WRAPPER_API void QunCoreAnimation_SetDuration(struct QunCoreAnimation *self, float duration);
  CAL3D_WRAPPER_API void QunCoreAnimation_Scale(struct QunCoreAnimation *self, float factor);

//****************************************************************************//
// QunCoreMorphAnimation wrapper functions declaration                             //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunCoreMorphAnimation *QunCoreMorphAnimation_New();
  CAL3D_WRAPPER_API void QunCoreMorphAnimation_Delete(struct QunCoreMorphAnimation* self);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreMorphAnimation_AddMorphTarget(struct QunCoreMorphAnimation* self, int meshID, int morphID);
  CAL3D_WRAPPER_API const char* QunCoreMorphAnimation_GetName( const struct QunCoreMorphAnimation *self );
  CAL3D_WRAPPER_API void QunCoreMorphAnimation_SetName(struct QunCoreMorphAnimation *self, const char* inName );

//****************************************************************************//
// QunCoreBone wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API enum QunBoolean QunCoreBone_AddChildId(struct QunCoreBone *self, int childId);
  CAL3D_WRAPPER_API void QunCoreBone_QunculateState(struct QunCoreBone *self);
  CAL3D_WRAPPER_API void QunCoreBone_Delete(struct QunCoreBone *self);
//  CAL3D_WRAPPER_API std::list<int>& QunCoreBone_GetListChildId(struct QunCoreBone *self);
  CAL3D_WRAPPER_API int QunCoreBone_GetChildCount( struct QunCoreBone *self );
  CAL3D_WRAPPER_API int QunCoreBone_GetChildId( struct QunCoreBone *self, int childIndex );
  CAL3D_WRAPPER_API const char *QunCoreBone_GetName(struct QunCoreBone *self);
  CAL3D_WRAPPER_API void QunCoreBone_SetName(struct QunCoreBone *self, const char* name );
  CAL3D_WRAPPER_API int QunCoreBone_GetParentId(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunCoreBone_GetRotation(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunCoreBone_GetRotationAbsolute(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunQuaternion *QunCoreBone_GetRotationBoneSpace(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunCoreBone_GetTranslation(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunCoreBone_GetTranslationAbsolute(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunVector *QunCoreBone_GetTranslationBoneSpace(struct QunCoreBone *self);
  CAL3D_WRAPPER_API QunUserData QunCoreBone_GetUserData(struct QunCoreBone *self);
  CAL3D_WRAPPER_API struct QunCoreBone *QunCoreBone_New(const char* name);
  CAL3D_WRAPPER_API void QunCoreBone_SetCoreSkeleton(struct QunCoreBone *self, struct QunCoreSkeleton *pCoreSkeleton);
  CAL3D_WRAPPER_API void QunCoreBone_SetParentId(struct QunCoreBone *self, int parentId);
  CAL3D_WRAPPER_API void QunCoreBone_SetRotation(struct QunCoreBone *self, struct QunQuaternion *pRotation);
  CAL3D_WRAPPER_API void QunCoreBone_SetRotationBoneSpace(struct QunCoreBone *self, struct QunQuaternion *pRotation);
  CAL3D_WRAPPER_API void QunCoreBone_SetTranslation(struct QunCoreBone *self, struct QunVector *pTranslation);
  CAL3D_WRAPPER_API void QunCoreBone_SetTranslationBoneSpace(struct QunCoreBone *self, struct QunVector *pTranslation);
  CAL3D_WRAPPER_API void QunCoreBone_SetUserData(struct QunCoreBone *self, QunUserData userData);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreBone_GetBoundingBox( struct QunCoreBone *self, struct QunCoreModel* model,
  													float* outEightPoints );
//****************************************************************************//
// QunCoreMaterial wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunCoreMaterial *QunCoreMaterial_New();
  CAL3D_WRAPPER_API void QunCoreMaterial_Delete(struct QunCoreMaterial *self);

//  CAL3D_WRAPPER_API QunCoreMaterial::Color *QunCoreMaterial_GetAmbientColor(struct QunCoreMaterial *self);
//  CAL3D_WRAPPER_API QunCoreMaterial::Color *QunCoreMaterial_GetDiffuseColor(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API int QunCoreMaterial_GetMapCount(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API const char *QunCoreMaterial_GetMapFilename(struct QunCoreMaterial *self, int mapId);
  CAL3D_WRAPPER_API QunUserData QunCoreMaterial_GetMapUserData(struct QunCoreMaterial *self, int mapId);
  CAL3D_WRAPPER_API float QunCoreMaterial_GetShininess(struct QunCoreMaterial *self);
//  CAL3D_WRAPPER_API QunCoreMaterial::Color *QunCoreMaterial_GetSpecularColor(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API QunUserData QunCoreMaterial_GetUserData(struct QunCoreMaterial *self);
//  CAL3D_WRAPPER_API std::vector<Map>& QunCoreMaterial_GetVectorMap(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreMaterial_Reserve(struct QunCoreMaterial *self, int mapCount);
//  CAL3D_WRAPPER_API void QunCoreMaterial_SetAmbientColor(struct QunCoreMaterial *self, struct QunCoreMaterial::Color *pAmbientColor);
//  CAL3D_WRAPPER_API void QunCoreMaterial_SetDiffuseColor(struct QunCoreMaterial *self, struct QunCoreMaterial::Color *pDiffuseColor);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreMaterial_SetMap(struct QunCoreMaterial *self, int mapId, struct QunCoreMaterial::Map *pMap);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreMaterial_SetMapUserData(struct QunCoreMaterial *self, int mapId, QunUserData userData);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetShininess(struct QunCoreMaterial *self, float shininess);
//  CAL3D_WRAPPER_API void QunCoreMaterial_SetSpecularColor(struct QunCoreMaterial *self, struct QunCoreMaterial::Color *pSpecularColor);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetUserData(struct QunCoreMaterial *self, QunUserData userData);
  CAL3D_WRAPPER_API const char* QunCoreMaterial_GetName(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetName(struct QunCoreMaterial *self, const char* inName);
  CAL3D_WRAPPER_API QunColorValue QunCoreMaterial_GetAmbientColor(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API QunColorValue QunCoreMaterial_GetDiffuseColor(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API QunColorValue QunCoreMaterial_GetSpecularColor(struct QunCoreMaterial *self);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetAmbientColor(struct QunCoreMaterial *self, QunColorValue pAmbientColor);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetDiffuseColor(struct QunCoreMaterial *self, QunColorValue pDiffuseColor);
  CAL3D_WRAPPER_API void QunCoreMaterial_SetSpecularColor(struct QunCoreMaterial *self, QunColorValue pSpecularColor);


//****************************************************************************//
// QunCoreMesh wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunCoreMesh *QunCoreMesh_New();
  CAL3D_WRAPPER_API void QunCoreMesh_Delete(struct QunCoreMesh *self);

  CAL3D_WRAPPER_API int QunCoreMesh_AddCoreSubmesh(struct QunCoreMesh *self, struct QunCoreSubmesh *pCoreSubmesh);
  CAL3D_WRAPPER_API void QunCoreMesh_RemoveCoreSubmesh( struct QunCoreMesh *self, int coreSubmeshID );
  CAL3D_WRAPPER_API struct QunCoreSubmesh *QunCoreMesh_GetCoreSubmesh(struct QunCoreMesh *self, int id);
  CAL3D_WRAPPER_API int QunCoreMesh_GetCoreSubmeshCount(struct QunCoreMesh *self);
//  CAL3D_WRAPPER_API std::vector<QunCoreSubmesh *>& QunCoreMesh_GetVectorCoreSubmesh(struct QunCoreMesh *self);
  CAL3D_WRAPPER_API const char* QunCoreMesh_GetName(struct QunCoreMesh *self);
  CAL3D_WRAPPER_API void QunCoreMesh_SetName(struct QunCoreMesh *self, const char* inName);
  CAL3D_WRAPPER_API void QunCoreMesh_Scale(struct QunCoreMesh *self,float factor);
  CAL3D_WRAPPER_API int QunCoreMesh_AddAsMorphTarget(struct QunCoreMesh *self, struct QunCoreMesh *target);
  
//****************************************************************************//
// QunCoreModel wrapper functions declaration                                 //
//****************************************************************************//

  CAL3D_WRAPPER_API int QunCoreModel_AddCoreAnimation(struct QunCoreModel *self, struct  QunCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API int QunCoreModel_AddCoreMorphAnimation(struct QunCoreModel *self, struct  QunCoreMorphAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API int QunCoreModel_AddCoreMaterial(struct QunCoreModel *self, struct QunCoreMaterial *pCoreMaterial);
  CAL3D_WRAPPER_API int QunCoreModel_AddCoreMesh(struct QunCoreModel *self, struct QunCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_CreateCoreMaterialThread(struct QunCoreModel *self, int coreMaterialThreadId);
  CAL3D_WRAPPER_API void QunCoreModel_Delete(struct QunCoreModel *self);
  CAL3D_WRAPPER_API const char *QunCoreModel_GetName(struct QunCoreModel *self);
  CAL3D_WRAPPER_API struct QunCoreAnimation *QunCoreModel_GetCoreAnimation(struct QunCoreModel *self, int coreAnimationId);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreAnimationCount(struct QunCoreModel *self);
  CAL3D_WRAPPER_API struct QunCoreMaterial *QunCoreModel_GetCoreMaterial(struct QunCoreModel *self, int coreMaterialId);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreMaterialCount(struct QunCoreModel *self);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreMaterialId(struct QunCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId);
  CAL3D_WRAPPER_API struct QunCoreMesh *QunCoreModel_GetCoreMesh(struct QunCoreModel *self, int coreMeshId);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreMeshCount(struct QunCoreModel *self);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreMeshId(struct QunCoreModel *self, const char* coreMeshName );
  CAL3D_WRAPPER_API struct QunCoreSkeleton *QunCoreModel_GetCoreSkeleton(struct QunCoreModel *self);
  CAL3D_WRAPPER_API QunUserData QunCoreModel_GetUserData(struct QunCoreModel *self);
  CAL3D_WRAPPER_API int QunCoreModel_GetCoreMorphAnimationCount(struct QunCoreModel *self);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreAnimation(struct QunCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreMaterial(struct QunCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreMesh(struct QunCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_LoadCoreSkeleton(struct QunCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreAnimationFromBuffer(struct QunCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreMaterialFromBuffer(struct QunCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API int QunCoreModel_LoadCoreMeshFromBuffer(struct QunCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_LoadCoreSkeletonFromBuffer(struct QunCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API struct QunCoreModel *QunCoreModel_New(const char* name);
  CAL3D_WRAPPER_API struct QunCoreModel *QunCoreModel_NewCopy( struct QunCoreModel* other );
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_SaveCoreAnimation(struct QunCoreModel *self, const char *strFilename, int coreAnimtionId);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_SaveCoreMaterial(struct QunCoreModel *self, const char *strFilename, int coreMaterialId);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_SaveCoreMesh(struct QunCoreModel *self, const char *strFilename, int coreMeshId);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_SaveCoreSkeleton(struct QunCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_SetCoreMaterialId(struct QunCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId);
  CAL3D_WRAPPER_API void QunCoreModel_SetCoreSkeleton(struct QunCoreModel *self, struct QunCoreSkeleton *pCoreSkeleton);
  CAL3D_WRAPPER_API void QunCoreModel_SetUserData(struct QunCoreModel *self, QunUserData userData);
  CAL3D_WRAPPER_API struct QunCoreMorphAnimation* QunCoreModel_GetCoreMorphAnimation( struct QunCoreModel *self, int morphAnimID );
  CAL3D_WRAPPER_API void QunCoreModel_SetName(struct QunCoreModel *self, const char* inName);
  CAL3D_WRAPPER_API void QunCoreModel_ReplaceCoreMesh(struct QunCoreModel *self, int coreMeshId, struct QunCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreModel_AddMeshName(struct QunCoreModel *self, const char* name, int coreMeshId );
  CAL3D_WRAPPER_API void QunCoreModel_CloneCoreMaterials(struct QunCoreModel *self );

//****************************************************************************//
// QunCoreSkeleton wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunCoreSkeleton *QunCoreSkeleton_New();
  CAL3D_WRAPPER_API void QunCoreSkeleton_Delete(struct QunCoreSkeleton* self);

  CAL3D_WRAPPER_API int QunCoreSkeleton_AddCoreBone(struct QunCoreSkeleton *self, struct QunCoreBone *pCoreBone);
  CAL3D_WRAPPER_API void QunCoreSkeleton_QunculateState(struct QunCoreSkeleton *self);
  CAL3D_WRAPPER_API struct QunCoreBone *QunCoreSkeleton_GetCoreBone(struct QunCoreSkeleton *self, int coreBoneId);
  CAL3D_WRAPPER_API int QunCoreSkeleton_GetCoreBoneId(struct QunCoreSkeleton *self, const char *strName);
  CAL3D_WRAPPER_API enum QunBoolean QunCoreSkeleton_MapCoreBoneName( struct QunCoreSkeleton *self, int coreBoneID, const char* name );
  CAL3D_WRAPPER_API int QunCoreSkeleton_GetCoreBoneCount(struct QunCoreSkeleton *self);
  CAL3D_WRAPPER_API int QunCoreSkeleton_GetRootCoreBoneCount(struct QunCoreSkeleton *self);
  CAL3D_WRAPPER_API struct QunCoreBone *QunCoreSkeleton_GetRootCoreBone(struct QunCoreSkeleton *self, int rootBoneIndex);
//  CAL3D_WRAPPER_API std::list<int>& QunCoreSkeleton_GetListRootCoreBoneId(struct QunCoreSkeleton *self);
//  CAL3D_WRAPPER_API std::vector<QunCoreBone *>& QunCoreSkeleton_GetVectorCoreBone(struct QunCoreSkeleton *self);
  CAL3D_WRAPPER_API void QunCoreSkeleton_QunculateBoundingBoxes( struct QunCoreModel* coreModel );
  CAL3D_WRAPPER_API void QunCoreSkeleton_Scale(struct QunCoreSkeleton *self,float factor);

//****************************************************************************//
// QunCoreSubmesh wrapper functions declaration                               //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunCoreSubmesh_Delete(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetCoreMaterialThreadId(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetFaceCount(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetLodCount(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetSpringCount(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API const QunIndex* QunCoreSubmesh_GetFaces( struct QunCoreSubmesh *self );
//  CAL3D_WRAPPER_API std::vector<QunCoreSubmesh::Face>& QunCoreSubmesh_GetVectorFace(struct QunCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<QunCoreSubmesh::PhysicalProperty>& QunCoreSubmesh_GetVectorPhysicalProperty(struct QunCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<QunCoreSubmesh::Spring>& QunCoreSubmesh_GetVectorSpring(struct QunCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<std::vector<QunCoreSubmesh::TextureCoordinate> >& QunCoreSubmesh_GetVectorVectorTextureCoordinate(struct QunCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<QunCoreSubmesh::Vertex>& QunCoreSubmesh_GetVectorVertex(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetVertexCount(struct QunCoreSubmesh *self);
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetVertexInfluenceCount( struct QunCoreSubmesh *self, int vertID );
  CAL3D_WRAPPER_API int QunCoreSubmesh_GetVertexInfluence( struct QunCoreSubmesh *self, int vertID, int influenceID,
  															float* outWeight );
  CAL3D_WRAPPER_API struct QunCoreSubmesh *QunCoreSubmesh_New();
  CAL3D_WRAPPER_API void QunCoreSubmesh_GetVertex( struct QunCoreSubmesh* self, int vertID, float* outPosition, float* outNormal );
  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_Reserve(struct QunCoreSubmesh *self, int vertexCount, int textureCoordinateCount, int faceCount, int springCount);
  CAL3D_WRAPPER_API void QunCoreSubmesh_SetCoreMaterialThreadId(struct QunCoreSubmesh *self, int coreMaterialThreadId);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_SetFace(struct QunCoreSubmesh *self, int faceId, struct QunCoreSubmesh::Face *pFace);
  CAL3D_WRAPPER_API void QunCoreSubmesh_SetLodCount(struct QunCoreSubmesh *self, int lodCount);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_SetPhysicalProperty(struct QunCoreSubmesh *self, int vertexId, struct QunCoreSubmesh::PhysicalProperty *pPhysicalProperty);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_SetSpring(struct QunCoreSubmesh *self, int springId, struct QunCoreSubmesh::Spring *pSpring);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_SetTextureCoordinate(struct QunCoreSubmesh *self, int vertexId, int textureCoordinateId, struct QunCoreSubmesh::TextureCoordinate *pTextureCoordinate);
//  CAL3D_WRAPPER_API enum QunBoolean QunCoreSubmesh_SetVertex(struct QunCoreSubmesh *self, int vertexId, struct QunCoreSubmesh::Vertex *pVertex);
CAL3D_WRAPPER_API enum QunBoolean  QunCoreSubmesh_IsTangentsEnabled(struct QunCoreSubmesh *self, int mapId);
CAL3D_WRAPPER_API enum QunBoolean  QunCoreSubmesh_EnableTangents(struct QunCoreSubmesh *self, int mapId, enum QunBoolean enabled);
CAL3D_WRAPPER_API int QunCoreSubmesh_AddSubMorphTarget( QunCoreSubmesh *self, QunCoreSubMorphTargetDiffMap* inTarget );
  
//****************************************************************************//
// QunCoreSubMorphTargetDiffMap wrapper functions declaration                 //
//****************************************************************************//
CAL3D_WRAPPER_API QunCoreSubMorphTargetDiffMap* QunCoreSubMorphTargetDiffMap_New();
CAL3D_WRAPPER_API QunCoreSubMorphTargetDiffMap* QunCoreSubMorphTargetDiffMap_Clone(
	const QunCoreSubMorphTargetDiffMap* inOther );
CAL3D_WRAPPER_API void QunCoreSubMorphTargetDiffMap_Delete( QunCoreSubMorphTargetDiffMap* inSelf );
CAL3D_WRAPPER_API bool QunCoreSubMorphTargetDiffMap_Reserve( QunCoreSubMorphTargetDiffMap* inSelf,
	int inNumDifferences );
CAL3D_WRAPPER_API bool QunCoreSubMorphTargetDiffMap_AppendVertex( QunCoreSubMorphTargetDiffMap* inSelf,
	int inVertexID, float* inPositionOffset, float* inNormalOffset );

//****************************************************************************//
// QunError wrapper functions declaration                                     //
//****************************************************************************//

  enum QunErrorCode
  {
    ERROR_CODE_OK = 0,
    ERROR_CODE_INTERNAL,
    ERROR_CODE_INVALID_HANDLE,
    ERROR_CODE_MEMORY_ALLOCATION_FAILED,
    ERROR_CODE_FILE_NOT_FOUND,
    ERROR_CODE_INVALID_FILE_FORMAT,
    ERROR_CODE_FILE_PARSER_FAILED,
    ERROR_CODE_INDEX_BUILD_FAILED,
    ERROR_CODE_NO_PARSER_DOCUMENT,
    ERROR_CODE_INVALID_ANIMATION_DURATION,
    ERROR_CODE_BONE_NOT_FOUND,
    ERROR_CODE_INVALID_ATTRIBUTE_VALUE,
    ERROR_CODE_INVALID_KEYFRAME_COUNT,
    ERROR_CODE_INVALID_ANIMATION_TYPE,
    ERROR_CODE_FILE_CREATION_FAILED,
    ERROR_CODE_FILE_WRITING_FAILED,
    ERROR_CODE_INCOMPATIBLE_FILE_VERSION,
    ERROR_CODE_NO_MESH_IN_MODEL,
    ERROR_CODE_MAX_ERROR_CODE
  };

  CAL3D_WRAPPER_API enum QunErrorCode QunError_GetLastErrorCode();
  CAL3D_WRAPPER_API const char *QunError_GetLastErrorDescription();
  CAL3D_WRAPPER_API const char *QunError_GetLastErrorFile();
  CAL3D_WRAPPER_API int QunError_GetLastErrorLine();
  CAL3D_WRAPPER_API const char *QunError_GetLastErrorText();
  CAL3D_WRAPPER_API void QunError_PrintLastError();
//  CAL3D_WRAPPER_API void QunError_SetLastError(enum QunErrorCode code, char *strFile, int line, char *strText);

//****************************************************************************//
// QunLoader wrapper functions declaration                                    //
//****************************************************************************//

  CAL3D_WRAPPER_API struct QunLoader *QunLoader_New();
  CAL3D_WRAPPER_API void QunLoader_Delete(struct QunLoader *self);
  CAL3D_WRAPPER_API struct QunCoreAnimation *QunLoader_LoadCoreAnimation(struct QunLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct QunCoreMaterial *QunLoader_LoadCoreMaterial(struct QunLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct QunCoreMesh *QunLoader_LoadCoreMesh(struct QunLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct QunCoreSkeleton *QunLoader_LoadCoreSkeleton(struct QunLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct QunCoreMesh *QunLoader_LoadCoreMeshFromBuffer(const void *data);
	enum QunLoaderFlags
	{
		CAL_LOADER_ROTATE_X_AXIS = 1,
		CAL_LOADER_INVERT_V_COORD = 2
	};
  CAL3D_WRAPPER_API void QunLoader_SetLoadingMode( int flags );

//****************************************************************************//
// QunMesh wrapper functions declaration                                      //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunMesh_Delete(struct QunMesh *self);
  CAL3D_WRAPPER_API struct QunCoreMesh *QunMesh_GetCoreMesh(struct QunMesh *self);
  CAL3D_WRAPPER_API struct QunSubmesh *QunMesh_GetSubmesh(struct QunMesh *self, int id);
  CAL3D_WRAPPER_API int QunMesh_GetSubmeshCount(struct QunMesh *self);
//  CAL3D_WRAPPER_API std::vector<QunSubmesh *>& QunMesh_GetVectorSubmesh(struct QunMesh *self);
  CAL3D_WRAPPER_API struct QunMesh *QunMesh_New(struct QunCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API void QunMesh_SetLodLevel(struct QunMesh *self, float lodLevel);
  CAL3D_WRAPPER_API void QunMesh_SetMaterialSet(struct QunMesh *self, int setId);
  CAL3D_WRAPPER_API void QunMesh_SetModel(struct QunMesh *self, struct QunModel *pModel);

//****************************************************************************//
// QunMixer wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API enum QunBoolean QunMixer_BlendCycle(struct QunMixer *self, int id, float weight, float delay);
  CAL3D_WRAPPER_API enum QunBoolean QunMixer_ClearCycle(struct QunMixer *self, int id, float delay);
  CAL3D_WRAPPER_API void QunMixer_Delete(struct QunMixer *self);
  CAL3D_WRAPPER_API enum QunBoolean QunMixer_ExecuteAction(struct QunMixer *self, int id, float delayIn, float delayOut, enum QunBoolean autoLock);
  CAL3D_WRAPPER_API struct QunMixer *QunMixer_New(struct QunModel *pModel);
  CAL3D_WRAPPER_API void QunMixer_UpdateAnimation(struct QunMixer *self, float deltaTime);
  CAL3D_WRAPPER_API void QunMixer_UpdateSkeleton(struct QunMixer *self);
  CAL3D_WRAPPER_API void QunMixer_RemoveAction(struct QunMixer *self,int id);

//****************************************************************************//
// QunMorphTargetMixer wrapper functions declaration                          //
//****************************************************************************//
  CAL3D_WRAPPER_API enum QunBoolean QunMorphTargetMixer_Blend( struct QunMorphTargetMixer* self,
  							int morphAnimID, float weight, float delay );
  CAL3D_WRAPPER_API enum QunBoolean QunMorphTargetMixer_Clear(struct QunMorphTargetMixer *self, int id, float delay);
  CAL3D_WRAPPER_API void QunMorphTargetMixer_Delete(struct QunMorphTargetMixer *self);
  CAL3D_WRAPPER_API struct QunMorphTargetMixer *QunMorphTargetMixer_New(struct QunModel *pModel);
  CAL3D_WRAPPER_API void QunMorphTargetMixer_Update( struct QunMorphTargetMixer* self, float deltaTime );
  CAL3D_WRAPPER_API int QunMorphTargetMixer_GetMorphTargetCount( struct QunMorphTargetMixer* self );
  CAL3D_WRAPPER_API enum QunBoolean QunMorphTargetMixer_Copy( struct QunMorphTargetMixer* self,
  															const struct QunMorphTargetMixer* toCopy );
  CAL3D_WRAPPER_API float QunMorphTargetMixer_GetCurrentWeight( struct QunMorphTargetMixer* self, int morphAnimID );

//****************************************************************************//
// QunModel wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API enum QunBoolean QunModel_AttachMesh(struct QunModel *self, int coreMeshId);
  CAL3D_WRAPPER_API void QunModel_Delete(struct QunModel *self);
  CAL3D_WRAPPER_API enum QunBoolean QunModel_DetachMesh(struct QunModel *self, int coreMeshId);
  CAL3D_WRAPPER_API struct QunCoreModel *QunModel_GetCoreModel(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunMesh *QunModel_GetMesh(struct QunModel *self, int coreMeshId);
  CAL3D_WRAPPER_API struct QunMixer *QunModel_GetMixer(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunMorphTargetMixer *QunModel_GetMorphTargetMixer(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunPhysique *QunModel_GetPhysique(struct QunModel *self);
  CAL3D_WRAPPER_API void QunModel_SetPhysique(struct QunModel *self, struct QunPhysique *phys);
  CAL3D_WRAPPER_API struct QunRenderer *QunModel_GetRenderer(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunSkeleton *QunModel_GetSkeleton(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunSpringSystem *QunModel_GetSpringSystem(struct QunModel *self);
  CAL3D_WRAPPER_API QunUserData QunModel_GetUserData(struct QunModel *self);
  CAL3D_WRAPPER_API int QunModel_GetMeshCount(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunMesh *QunModel_GetMeshByMeshID(struct QunModel *self, int meshId);
//  CAL3D_WRAPPER_API std::vector<QunMesh *>& QunModel_GetVectorMesh(struct QunModel *self);
  CAL3D_WRAPPER_API struct QunModel *QunModel_New(struct QunCoreModel* pCoreModel);
  CAL3D_WRAPPER_API void QunModel_SetLodLevel(struct QunModel *self, float lodLevel);
  CAL3D_WRAPPER_API void QunModel_SetMaterialSet(struct QunModel *self, int setId);
  CAL3D_WRAPPER_API void QunModel_SetUserData(struct QunModel *self, QunUserData userData);
  CAL3D_WRAPPER_API void QunModel_Update(struct QunModel *self, float deltaTime);

//****************************************************************************//
// QunPhysique wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API int QunPhysique_QunculateNormals(struct QunPhysique *self, struct QunSubmesh *pSubmesh, float *pNormalBuffer);
  CAL3D_WRAPPER_API int QunPhysique_QunculateVertices(struct QunPhysique *self, struct QunSubmesh *pSubmesh, float *pVertexBuffer);
  CAL3D_WRAPPER_API int QunPhysique_QunculateVerticesAndNormals(struct QunPhysique *self, struct QunSubmesh *pSubmesh, float *pVertexBuffer);
  CAL3D_WRAPPER_API int QunPhysique_QunculateVerticesNormalsAndTexCoords(struct QunPhysique *self, struct QunSubmesh *pSubmesh, float *pVertexBuffer, int NumTexCoords);
  CAL3D_WRAPPER_API int QunPhysique_QunculateTangentSpaces(struct QunPhysique *self, struct QunSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer);
  CAL3D_WRAPPER_API void QunPhysique_Delete(struct QunPhysique *self);
  CAL3D_WRAPPER_API struct QunPhysique *QunPhysique_New(struct QunModel* pModel);
  CAL3D_WRAPPER_API void QunPhysique_Update(struct QunPhysique *self);
  CAL3D_WRAPPER_API struct QunPhysique *QunPhysiqueDualQuat_New(struct QunModel* pModel);

//****************************************************************************//
// QunPlatform wrapper functions declaration                                  //
//****************************************************************************//

//****************************************************************************//
// QunQuaternion wrapper functions declaration                                //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunQuaternion_Blend(struct QunQuaternion *self, float d, const struct QunQuaternion *pQ);
  CAL3D_WRAPPER_API void QunQuaternion_Clear(struct QunQuaternion *self);
  CAL3D_WRAPPER_API void QunQuaternion_Conjugate(struct QunQuaternion *self);
  CAL3D_WRAPPER_API void QunQuaternion_Invert(struct QunQuaternion *self);
  CAL3D_WRAPPER_API void QunQuaternion_Delete(struct QunQuaternion *self);
  CAL3D_WRAPPER_API void QunQuaternion_Equal(struct QunQuaternion *self, const struct QunQuaternion *pQ);
  CAL3D_WRAPPER_API float *QunQuaternion_Get(struct QunQuaternion *self);
  CAL3D_WRAPPER_API void QunQuaternion_Multiply(struct QunQuaternion *self, const struct QunQuaternion *pQ);
  CAL3D_WRAPPER_API void QunQuaternion_MultiplyVector(struct QunQuaternion *self, const struct QunVector *pV);
  CAL3D_WRAPPER_API struct QunQuaternion *QunQuaternion_New();
  CAL3D_WRAPPER_API void QunQuaternion_Op_Multiply(struct QunQuaternion *pResult, const struct QunQuaternion *pQ, const struct QunQuaternion *pR);
  CAL3D_WRAPPER_API void QunQuaternion_Set(struct QunQuaternion *self, float qx, float qy, float qz, float qw);

//****************************************************************************//
// QunRenderer wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API enum QunBoolean QunRenderer_BeginRendering(struct QunRenderer *self);
  CAL3D_WRAPPER_API void QunRenderer_Delete(struct QunRenderer *self);
  CAL3D_WRAPPER_API void QunRenderer_EndRendering(struct QunRenderer *self);
  CAL3D_WRAPPER_API void QunRenderer_GetAmbientColor(struct QunRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API void QunRenderer_GetDiffuseColor(struct QunRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetFaceCount(struct QunRenderer *self);
  CAL3D_WRAPPER_API int QunRenderer_GetFaces(struct QunRenderer *self, QunIndex *pFaceBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetMapCount(struct QunRenderer *self);
  CAL3D_WRAPPER_API QunUserData QunRenderer_GetMapUserData(struct QunRenderer *self, int mapId);
  CAL3D_WRAPPER_API int QunRenderer_GetMeshCount(struct QunRenderer *self);
  CAL3D_WRAPPER_API int QunRenderer_GetNormals(struct QunRenderer *self, float *pNormalBuffer);
  CAL3D_WRAPPER_API float QunRenderer_GetShininess(struct QunRenderer *self);
  CAL3D_WRAPPER_API void QunRenderer_GetSpecularColor(struct QunRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetSubmeshCount(struct QunRenderer *self, int meshId);
  CAL3D_WRAPPER_API int QunRenderer_GetTextureCoordinates(struct QunRenderer *self, int mapId, float *pTextureCoordinateBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetVertexCount(struct QunRenderer *self);
  CAL3D_WRAPPER_API int QunRenderer_GetVertices(struct QunRenderer *self, float *pVertexBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetVerticesAndNormals(struct QunRenderer *self, float *pVertexBuffer);
  CAL3D_WRAPPER_API int QunRenderer_GetVerticesNormalsAndTexCoords(struct QunRenderer *self, float *pVertexBuffer, int NumTexCoords);
  CAL3D_WRAPPER_API int QunRenderer_GetTangentSpaces(struct QunRenderer *self, int mapId, float *pTangentSpaceBuffer);
  CAL3D_WRAPPER_API enum QunBoolean  QunRenderer_IsTangentsEnabled(struct QunRenderer *self, int mapId);
  CAL3D_WRAPPER_API struct QunRenderer *QunRenderer_New(struct QunModel* pModel);
  CAL3D_WRAPPER_API enum QunBoolean QunRenderer_SelectMeshSubmesh(struct QunRenderer *self, int meshId, int submeshId);

//****************************************************************************//
// QunSaver wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunSaver_Delete(struct QunSaver *self);
  CAL3D_WRAPPER_API struct QunSaver *QunSaver_New();
  CAL3D_WRAPPER_API enum QunBoolean QunSaver_SaveCoreAnimation(struct QunSaver *self, const char *strFilename, struct  QunCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API enum QunBoolean QunSaver_SaveCoreMaterial(struct QunSaver *self, const char *strFilename, struct QunCoreMaterial *pCoreMaterial);
  CAL3D_WRAPPER_API enum QunBoolean QunSaver_SaveCoreMesh(struct QunSaver *self, const char *strFilename, struct QunCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum QunBoolean QunSaver_SaveCoreSkeleton(struct QunSaver *self, const char *strFilename, struct QunCoreSkeleton *pCoreSkeleton);

//****************************************************************************//
// QunSkeleton wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunSkeleton_QunculateState(struct QunSkeleton *self);
  CAL3D_WRAPPER_API void QunSkeleton_ClearState(struct QunSkeleton *self);
  CAL3D_WRAPPER_API void QunSkeleton_Delete(struct QunSkeleton *self);
  CAL3D_WRAPPER_API struct QunBone *QunSkeleton_GetBone(struct QunSkeleton *self, int boneId);
  CAL3D_WRAPPER_API int QunSkeleton_GetBoneCount(struct QunSkeleton *self);
  CAL3D_WRAPPER_API struct QunCoreSkeleton *QunSkeleton_GetCoreSkeleton(struct QunSkeleton *self);
//  CAL3D_WRAPPER_API std::vector<QunBone *>& QunSkeleton_GetVectorBone(struct QunSkeleton *self);
  CAL3D_WRAPPER_API void QunSkeleton_LockState(struct QunSkeleton *self);
  CAL3D_WRAPPER_API struct QunSkeleton *QunSkeleton_New(struct QunCoreSkeleton* pCoreSkeleton);
  CAL3D_WRAPPER_API void QunSkeleton_GetBoneBoundingBox(struct QunSkeleton *self, float *min, float *max);
  CAL3D_WRAPPER_API void QunSkeleton_QunculateBoundingBoxes(struct QunSkeleton *self);

  // DEBUG-CODE
  CAL3D_WRAPPER_API int QunSkeleton_GetBonePoints(struct QunSkeleton *self, float *pPoints);
  CAL3D_WRAPPER_API int QunSkeleton_GetBonePointsStatic(struct QunSkeleton *self, float *pPoints);
  CAL3D_WRAPPER_API int QunSkeleton_GetBoneLines(struct QunSkeleton *self, float *pLines);
  CAL3D_WRAPPER_API int QunSkeleton_GetBoneLinesStatic(struct QunSkeleton *self, float *pLines);

//****************************************************************************//
// QunSpringSystem wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunSpringSystem_QunculateForces(struct QunSpringSystem *self, struct QunSubmesh *pSubmesh, float deltaTime);
  CAL3D_WRAPPER_API void QunSpringSystem_QunculateVertices(struct QunSpringSystem *self, struct QunSubmesh *pSubmesh, float deltaTime);
  CAL3D_WRAPPER_API void QunSpringSystem_Delete(struct QunSpringSystem *self);
  CAL3D_WRAPPER_API struct QunSpringSystem *QunSpringSystem_New(struct QunModel *pModel);
  CAL3D_WRAPPER_API void QunSpringSystem_Update(struct QunSpringSystem *self, float deltaTime);
  CAL3D_WRAPPER_API struct QunVector* QunSpringSystem_GetGravityVector(struct QunSpringSystem *self);
  CAL3D_WRAPPER_API struct QunVector* QunSpringSystem_GetForceVector(struct QunSpringSystem *self);
  CAL3D_WRAPPER_API void QunSpringSystem_SetGravityVector(struct QunSpringSystem *self, struct QunVector* grav);
  CAL3D_WRAPPER_API void QunSpringSystem_SetForceVector(struct QunSpringSystem *self, struct QunVector* force);
  CAL3D_WRAPPER_API void QunSpringSystem_ResetPositions(struct QunSpringSystem *self);

//****************************************************************************//
// QunSubmesh wrapper functions declaration                                   //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunSubmesh_Delete(struct QunSubmesh *self);
  CAL3D_WRAPPER_API struct QunCoreSubmesh *QunSubmesh_GetCoreSubmesh(struct QunSubmesh *self);
  CAL3D_WRAPPER_API int QunSubmesh_GetCoreMaterialId(struct QunSubmesh *self);
  CAL3D_WRAPPER_API int QunSubmesh_GetFaceCount(struct QunSubmesh *self);
  CAL3D_WRAPPER_API int QunSubmesh_GetFaces(struct QunSubmesh *self, QunIndex *pFaceBuffer);

//  CAL3D_WRAPPER_API std::vector<QunVector>& QunSubmesh_GetVectorNormal(struct QunSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<QunSubmesh::PhysicalProperty>& QunSubmesh_GetVectorPhysicalProperty(struct QunSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<QunVector>& QunSubmesh_GetVectorVertex(struct QunSubmesh *self);
  CAL3D_WRAPPER_API int QunSubmesh_GetVertexCount(struct QunSubmesh *self);
  CAL3D_WRAPPER_API enum QunBoolean QunSubmesh_HasInternalData(struct QunSubmesh *self);
  CAL3D_WRAPPER_API struct QunSubmesh *QunSubmesh_New(struct QunCoreSubmesh* coreSubmesh);
  CAL3D_WRAPPER_API void QunSubmesh_SetCoreMaterialId(struct QunSubmesh *self, int coreMaterialId);
  CAL3D_WRAPPER_API void QunSubmesh_SetLodLevel(struct QunSubmesh *self, float lodLevel);

//****************************************************************************//
// QunVector wrapper functions declaration                                    //
//****************************************************************************//

  CAL3D_WRAPPER_API void QunVector_Add(struct QunVector *self, struct QunVector *pV);
  CAL3D_WRAPPER_API void QunVector_Blend(struct QunVector *self, float d, struct QunVector *pV);
  CAL3D_WRAPPER_API void QunVector_Clear(struct QunVector *self);
  CAL3D_WRAPPER_API void QunVector_Delete(struct QunVector *self);
  CAL3D_WRAPPER_API void QunVector_Equal(struct QunVector *self, struct QunVector *pV);
  CAL3D_WRAPPER_API void QunVector_InverseScale(struct QunVector *self, float d);
  CAL3D_WRAPPER_API float *QunVector_Get(struct QunVector *self);
  CAL3D_WRAPPER_API float QunVector_Length(struct QunVector *self);
  CAL3D_WRAPPER_API struct QunVector *QunVector_New();
  CAL3D_WRAPPER_API float QunVector_Normalize(struct QunVector *self);
  CAL3D_WRAPPER_API void QunVector_Op_Add(struct QunVector *pResult, struct QunVector *pV, struct QunVector *pU);
  CAL3D_WRAPPER_API void QunVector_Op_Subtract(struct QunVector *pResult, struct QunVector *pV, struct QunVector *pU);
  CAL3D_WRAPPER_API void QunVector_QunVector_Op_Scale(struct QunVector *pResult, struct QunVector *pV, float d);
  CAL3D_WRAPPER_API void QunVector_QunVector_Op_InverseScale(struct QunVector *pResult, struct QunVector *pV, float d);
  CAL3D_WRAPPER_API float QunVector_Op_Scalar(struct QunVector *pV, struct QunVector *pU);
  CAL3D_WRAPPER_API void QunVector_Op_Cross(struct QunVector *pResult, struct QunVector *pV, struct QunVector *pU);
  CAL3D_WRAPPER_API void QunVector_Scale(struct QunVector *self, float d);
  CAL3D_WRAPPER_API void QunVector_Set(struct QunVector *self, float vx, float vy, float vz);
  CAL3D_WRAPPER_API void QunVector_Subtract(struct QunVector *self, struct QunVector *pV);
  CAL3D_WRAPPER_API void QunVector_Transform(struct QunVector *self, struct QunQuaternion *pQ);

#ifdef __cplusplus
}
#endif

#endif

//****************************************************************************//
