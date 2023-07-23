//****************************************************************************//
// physique.cpp                                                               //
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
#include "cal3d/physique.h"
#include "cal3d/coremodel.h"
#include "cal3d/model.h"
#include "cal3d/mesh.h"
#include "cal3d/submesh.h"
#include "cal3d/skeleton.h"
#include "cal3d/bone.h"
#include "cal3d/coresubmesh.h"
#include "cal3d/coresubmorphtarget.h"

#include <cfloat>

 /*****************************************************************************/
/** Constructs the physique instance.
  *
  * This function is the default constructor of the physique instance.
  *****************************************************************************/

QunPhysique::QunPhysique(QunModel* pModel)
  : m_pModel(0)
  , m_Normalize(true)
{
  assert(pModel);
  m_pModel = pModel;
  m_axisFactorX = 1.0f;
  m_axisFactorY = 1.0f;
  m_axisFactorZ = 1.0f;
}

 /*****************************************************************************/
/** Qunculates the transformed vertex data.
  *
  * This function calculates and returns the transformed vertex data of a
  * specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the vertex data should
  *                 be calculated and returned.
  * @param pVertexBuffer A pointer to the user-provided buffer where the vertex
  *                      data is written to.
  *
  * @return The number of vertices written to the buffer.
  *****************************************************************************/

int QunPhysique::calculateVertices(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride)
{
  if(stride <= 0)
  {
	  stride = 3*sizeof(float);
  }

  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();

  // get vertex vector of the core submesh
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pSubmesh->getCoreSubmesh()->getVectorVertex();

  // get physical property vector of the core submesh
  std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pSubmesh->getCoreSubmesh()->getVectorPhysicalProperty();

  // get the number of vertices
  int vertexCount;
  vertexCount = pSubmesh->getVertexCount();
  
  // get the sub morph target vector from the core sub mesh
  std::vector<QunCoreSubMorphTarget*>& vectorSubMorphTarget =
  pSubmesh->getCoreSubmesh()->getVectorCoreSubMorphTarget();

  // calculate the base weight
  float baseWeight = pSubmesh->getBaseWeight();

  // get the number of morph targets
  int morphTargetCount = pSubmesh->getMorphTargetWeightCount();

  // Check for spring case
  bool	hasSpringsAndInternalData =
	(pSubmesh->getCoreSubmesh()->getSpringCount() > 0) &&
	pSubmesh->hasInternalData();

  // calculate all submesh vertices
  int vertexId;
  for(vertexId = 0; vertexId < vertexCount; ++vertexId)
  {
    // get the vertex
    QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];
    
    // blend the morph targets
    QunVector position(0,0,0);
    if(baseWeight == 1.0f)
    {
       position.x = vertex.position.x;
       position.y = vertex.position.y;
       position.z = vertex.position.z;
    }
    else
    {
      position.x = baseWeight*vertex.position.x;
      position.y = baseWeight*vertex.position.y;
      position.z = baseWeight*vertex.position.z;
      int morphTargetId;
      for(morphTargetId=0; morphTargetId < morphTargetCount;++morphTargetId)
      {
        float currentWeight = pSubmesh->getMorphTargetWeight(morphTargetId);
        if (currentWeight > FLT_EPSILON)
        {
	      	QunCoreSubMorphTarget::BlendVertex	blendVertex;
	        vectorSubMorphTarget[morphTargetId]->getBlendVertex(vertexId, blendVertex);
	        position.x += currentWeight*blendVertex.position.x;
	        position.y += currentWeight*blendVertex.position.y;
	        position.z += currentWeight*blendVertex.position.z;
        }
      }
    }

    // initialize vertex
    float x, y, z;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

    // blend together all vertex influences
    size_t influenceCount=vertex.vectorInfluence.size();
    if(influenceCount == 0) 
	{
      x = position.x;
      y = position.y;
      z = position.z;
    } 
	else 
	{
		for(size_t influenceId = 0; influenceId < influenceCount; ++influenceId)
		{
			// get the influence
			QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];
			
			// get the bone of the influence vertex
			QunBone *pBone;
			pBone = vectorBone[influence.boneId];
			
			// transform vertex with current state of the bone
			QunVector v(position);
			v *= pBone->getTransformMatrix();
			v += pBone->getTranslationBoneSpace();
			
			x += influence.weight * v.x;
			y += influence.weight * v.y;
			z += influence.weight * v.z;
		}
	}

    // save vertex position
    if(hasSpringsAndInternalData)
    {
      // get the physical property of the vertex
      QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

      // assign new vertex position if there is no vertex weight
      if(physicalProperty.weight == 0.0f)
      {
        pVertexBuffer[0] = x * m_axisFactorX;
        pVertexBuffer[1] = y * m_axisFactorY;
        pVertexBuffer[2] = z * m_axisFactorZ;
      }
    }
    else
    {
      pVertexBuffer[0] = x * m_axisFactorX;
      pVertexBuffer[1] = y * m_axisFactorY;
      pVertexBuffer[2] = z * m_axisFactorZ;
    }

    // next vertex position in buffer
    pVertexBuffer = (float *)(((char *)pVertexBuffer) + stride) ;
  }

  return vertexCount;
}

 /*****************************************************************************/
/** Qunculates one transformed vertex.
  *
  * This function calculates and returns a transformed vertex of a
  * specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the vertex should
  *                 be calculated and returned.
  * @param vertexId The id of the vertex that should be transformed.
  *
  * @return The number of vertices written to the buffer.
  *****************************************************************************/

QunVector QunPhysique::calculateVertex(QunSubmesh *pSubmesh, int vertexId)
{
  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();

  // get vertex of the core submesh
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pSubmesh->getCoreSubmesh()->getVectorVertex();

  // get physical property vector of the core submesh
  //std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pSubmesh->getCoreSubmesh()->getVectorPhysicalProperty();

  // get the sub morph target vector from the core sub mesh
  std::vector<QunCoreSubMorphTarget*>& vectorSubMorphTarget =
  pSubmesh->getCoreSubmesh()->getVectorCoreSubMorphTarget();

  // calculate the base weight
  float baseWeight = pSubmesh->getBaseWeight();

  // get the number of morph targets
  int morphTargetCount = pSubmesh->getMorphTargetWeightCount();

  // get the vertex
  QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

  // blend the morph targets
  QunVector position(0,0,0);
  if(baseWeight == 1.0f)
  {
    position.x = vertex.position.x;
    position.y = vertex.position.y;
    position.z = vertex.position.z;
  }
  else
  {
    position.x = baseWeight*vertex.position.x;
    position.y = baseWeight*vertex.position.y;
    position.z = baseWeight*vertex.position.z;
    int morphTargetId;
    for(morphTargetId=0; morphTargetId < morphTargetCount;++morphTargetId)
    {
      QunCoreSubMorphTarget::BlendVertex	blendVertex;
	  vectorSubMorphTarget[morphTargetId]->getBlendVertex(vertexId, blendVertex);
      float currentWeight = pSubmesh->getMorphTargetWeight(morphTargetId);
      position.x += currentWeight*blendVertex.position.x;
      position.y += currentWeight*blendVertex.position.y;
      position.z += currentWeight*blendVertex.position.z;
    }
  }

  // initialize vertex
  float x, y, z;
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;

  // blend together all vertex influences
  int influenceId;
  int influenceCount=(int)vertex.vectorInfluence.size();
  if(influenceCount == 0) 
  {
    x = position.x;
    y = position.y;
    z = position.z;
  } 
  else 
  {
	  for(influenceId = 0; influenceId < influenceCount; ++influenceId)
	  {
		  // get the influence
		  QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];
		  
		  // get the bone of the influence vertex
		  QunBone *pBone;
		  pBone = vectorBone[influence.boneId];
		  
		  // transform vertex with current state of the bone
		  QunVector v(position);
		  v *= pBone->getTransformMatrix();
		  v += pBone->getTranslationBoneSpace();
		  
		  x += influence.weight * v.x;
		  y += influence.weight * v.y;
		  z += influence.weight * v.z;
	  }
  }
  /*
  // save vertex position
  if(pSubmesh->getCoreSubmesh()->getSpringCount() > 0 && pSubmesh->hasInternalData())
  {
    // get the pgysical property of the vertex
    QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

    // assign new vertex position if there is no vertex weight
    if(physicalProperty.weight == 0.0f)
    {
      pVertexBuffer[0] = x;
      pVertexBuffer[1] = y;
      pVertexBuffer[2] = z;
    }
  }
  else
  {
    pVertexBuffer[0] = x;
    pVertexBuffer[1] = y;
    pVertexBuffer[2] = z;
  }
  */
  // return the vertex
  //return QunVector(x, y, z);
  return QunVector(x*m_axisFactorX,y*m_axisFactorY,z*m_axisFactorZ);
}
 /*****************************************************************************/
/** Qunculates the transformed tangent space data.
  *
  * This function calculates and returns the transformed tangent space data of a
  * specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the tangent space data 
  *                 should be calculated and returned.
  * @param mapId
  * @param pTangentSpaceBuffer A pointer to the user-provided buffer where the tangent 
  *                 space data is written to.
  *
  * @return The number of tangent spaces written to the buffer.
  *****************************************************************************/

int QunPhysique::calculateTangentSpaces(QunSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer, int stride)
{
  if((mapId < 0) || (mapId >= (int)pSubmesh->getCoreSubmesh()->getVectorVectorTangentSpace().size())) return false;
  if(stride <= 0)
  {
	  stride = 4*sizeof(float);
  }

  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();

  // get vertex vector of the submesh
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pSubmesh->getCoreSubmesh()->getVectorVertex();

  // get tangent space vector of the submesh
  std::vector<QunCoreSubmesh::TangentSpace>& vectorTangentSpace = pSubmesh->getCoreSubmesh()->getVectorVectorTangentSpace()[mapId];
  
  // get the number of vertices
  int vertexCount;
  vertexCount = pSubmesh->getVertexCount();

  // calculate normal for all submesh vertices
  int vertexId;
  for(vertexId = 0; vertexId < vertexCount; vertexId++)
  {
    QunCoreSubmesh::TangentSpace& tangentSpace = vectorTangentSpace[vertexId];

    // get the vertex
    QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

    // initialize tangent
    float tx, ty, tz;
    tx = 0.0f;
    ty = 0.0f;
    tz = 0.0f;

    // blend together all vertex influences
    int influenceId;
    int influenceCount=(int)vertex.vectorInfluence.size();

    for(influenceId = 0; influenceId < influenceCount; influenceId++)
    {
      // get the influence
      QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];

      // get the bone of the influence vertex
      QunBone *pBone;
      pBone = vectorBone[influence.boneId];

      // transform normal with current state of the bone
      QunVector v(tangentSpace.tangent);
      v *= pBone->getTransformMatrix(); 

      tx += influence.weight * v.x;
      ty += influence.weight * v.y;
      tz += influence.weight * v.z;
    }

    // re-normalize tangent if necessary
    if (m_Normalize)
    {
      float scale;
	  tx/= m_axisFactorX;
	  ty/= m_axisFactorY;
	  tz/= m_axisFactorZ;

      scale = (float)( 1.0f / sqrt(tx * tx + ty * ty + tz * tz));

      pTangentSpaceBuffer[0] = tx * scale;
      pTangentSpaceBuffer[1] = ty * scale;
      pTangentSpaceBuffer[2] = tz * scale;	  
    }
    else
    {
      pTangentSpaceBuffer[0] = tx;
      pTangentSpaceBuffer[1] = ty;
      pTangentSpaceBuffer[2] = tz;
    }

    pTangentSpaceBuffer[3] = tangentSpace.crossFactor;
    // next vertex position in buffer
    pTangentSpaceBuffer = (float *)(((char *)pTangentSpaceBuffer) + stride) ;
  }

  return vertexCount;
}


 /*****************************************************************************/
/** Qunculates the transformed normal data.
  *
  * This function calculates and returns the transformed normal data of a
  * specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the normal data should
  *                 be calculated and returned.
  * @param pNormalBuffer A pointer to the user-provided buffer where the normal
  *                      data is written to.
  *
  * @return The number of normals written to the buffer.
  *****************************************************************************/

int QunPhysique::calculateNormals(QunSubmesh *pSubmesh, float *pNormalBuffer, int stride)
{
  if(stride <= 0)
  {
	  stride = 3*sizeof(float);
  }

  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();

  // get vertex vector of the submesh
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pSubmesh->getCoreSubmesh()->getVectorVertex();

  // get the number of vertices
  int vertexCount;
  vertexCount = pSubmesh->getVertexCount();

  // get the sub morph target vector from the core sub mesh
  std::vector<QunCoreSubMorphTarget*>& vectorSubMorphTarget =
  pSubmesh->getCoreSubmesh()->getVectorCoreSubMorphTarget();

  // calculate the base weight
  float baseWeight = pSubmesh->getBaseWeight();

  // get the number of morph targets
  int morphTargetCount = pSubmesh->getMorphTargetWeightCount();

  // calculate normal for all submesh vertices
  int vertexId;
  for(vertexId = 0; vertexId < vertexCount; ++vertexId)
  {
    // get the vertex
    QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

    // blend the morph targets
    QunVector normal(0,0,0);
    if(baseWeight == 1.0f)
    {
      normal.x = vertex.normal.x;
      normal.y = vertex.normal.y;
      normal.z = vertex.normal.z;
    }
    else
    {
      normal.x = baseWeight*vertex.normal.x;
      normal.y = baseWeight*vertex.normal.y;
      normal.z = baseWeight*vertex.normal.z;
      int morphTargetId;
      for(morphTargetId=0; morphTargetId < morphTargetCount;++morphTargetId)
      {
        float currentWeight = pSubmesh->getMorphTargetWeight(morphTargetId);
        if (currentWeight > FLT_EPSILON)
        {
	        QunCoreSubMorphTarget::BlendVertex	blendVertex;
	        vectorSubMorphTarget[morphTargetId]->getBlendVertex(vertexId, blendVertex);
	        normal.x += currentWeight*blendVertex.normal.x;
	        normal.y += currentWeight*blendVertex.normal.y;
	        normal.z += currentWeight*blendVertex.normal.z;
        }
      }
    }

    // initialize normal
    float nx, ny, nz;
    nx = 0.0f;
    ny = 0.0f;
    nz = 0.0f;

    // blend together all vertex influences
    int influenceId;
	int influenceCount=(int)vertex.vectorInfluence.size();
    if(influenceCount == 0) 
	{
      nx = normal.x;
      ny = normal.y;
      nz = normal.z;
    } 
	else 
	{
		for(influenceId = 0; influenceId < influenceCount; ++influenceId)
		{
			// get the influence
			QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];
			
			// get the bone of the influence vertex
			QunBone *pBone;
			pBone = vectorBone[influence.boneId];
			
			// transform normal with current state of the bone
			QunVector v(normal);
			v *= pBone->getTransformMatrix(); 
			
			nx += influence.weight * v.x;
			ny += influence.weight * v.y;
			nz += influence.weight * v.z;
		}
	}

    // re-normalize normal if necessary
    if (m_Normalize)
    {
	  nx/= m_axisFactorX;
	  ny/= m_axisFactorY;
	  nz/= m_axisFactorZ;

      float scale;
      scale = (float)( 1.0f / sqrt(nx * nx + ny * ny + nz * nz));

      pNormalBuffer[0] = nx * scale;
      pNormalBuffer[1] = ny * scale;
      pNormalBuffer[2] = nz * scale;
    }
    else
    {
      pNormalBuffer[0] = nx;
      pNormalBuffer[1] = ny;
      pNormalBuffer[2] = nz;
    } 

    // next vertex position in buffer
    pNormalBuffer = (float *)(((char *)pNormalBuffer) + stride) ;
  }

  return vertexCount;
}

 /*****************************************************************************/
/** Qunculates the transformed vertex data.
  *
  * This function calculates and returns the transformed vertex and the transformed 
  * normal datadata of a specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the vertex data should
  *                 be calculated and returned.
  * @param pVertexBuffer A pointer to the user-provided buffer where the vertex
  *                      data is written to.
  *
  * @return The number of vertices written to the buffer.
  *****************************************************************************/

int QunPhysique::calculateVerticesAndNormals(QunSubmesh *pSubmesh, float *pVertexBuffer, int stride)
{
  if(stride <= 0)
  {
	  stride = 6*sizeof(float);
  }

  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();
  QunBone ** vectorBonePtr = &vectorBone[0];

  // get vertex vector of the core submesh
  const QunCoreSubmesh::Vertex* vectorVertex = &pSubmesh->getCoreSubmesh()->getVectorVertex()[0];

  // get physical property vector of the core submesh
  std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pSubmesh->getCoreSubmesh()->getVectorPhysicalProperty();

  // get the number of vertices
  int vertexCount;
  vertexCount = pSubmesh->getVertexCount();

  // get the sub morph target vector from the core sub mesh
  std::vector<QunCoreSubMorphTarget*>& vectorSubMorphTarget =
	pSubmesh->getCoreSubmesh()->getVectorCoreSubMorphTarget();

  // calculate the base weight
  float baseWeight = pSubmesh->getBaseWeight();

  // get the number of morph targets
  int morphTargetCount = pSubmesh->getMorphTargetWeightCount();
  
  // Check for spring case
  bool	hasSpringsAndInternalData =
	(pSubmesh->getCoreSubmesh()->getSpringCount() > 0) &&
	pSubmesh->hasInternalData();

  // calculate all submesh vertices
  int vertexId;
  QunCoreSubMorphTarget::BlendVertex	blendVertex;
  for(vertexId = 0; vertexId < vertexCount; ++vertexId)
  {
    // get the vertex
    const QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

    // blend the morph targets
    QunVector position(0,0,0);
    QunVector normal(0,0,0);
    if(baseWeight == 1.0f)
    {
      position = vertex.position;
      normal = vertex.normal;
    }
    else
    {
      position = baseWeight * vertex.position;
      normal = baseWeight * vertex.normal;

      int morphTargetId;
      for(morphTargetId=0; morphTargetId < morphTargetCount;++morphTargetId)
      {
        float currentWeight = pSubmesh->getMorphTargetWeight(morphTargetId);
        if (currentWeight > FLT_EPSILON)
        {
			vectorSubMorphTarget[morphTargetId]->getBlendVertex(vertexId, blendVertex);
			position += currentWeight * blendVertex.position;
			normal += currentWeight * blendVertex.normal;
        }
      }
    }

    // initialize vertex
    float x, y, z;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

	// initialize normal
    float nx, ny, nz;
    nx = 0.0f;
    ny = 0.0f;
    nz = 0.0f;

    // blend together all vertex influences
    int influenceId;
	int influenceCount=(int)vertex.vectorInfluence.size();
    if(influenceCount == 0) 
	{
      x = position.x;
      y = position.y;
      z = position.z;
      nx = normal.x;
      ny = normal.y;
      nz = normal.z;
    } 
	else 
	{
		const QunCoreSubmesh::Influence*	influences = &vertex.vectorInfluence[0];
		
		for(influenceId = 0; influenceId < influenceCount; ++influenceId)
		{
			// get the influence
			const QunCoreSubmesh::Influence& influence = influences[influenceId];
			
			// get the bone of the influence vertex
			QunBone *pBone;
			pBone = vectorBonePtr[influence.boneId];
			
			// transform vertex with current state of the bone
			QunVector v(position);
			v *= pBone->getTransformMatrix();
			v += pBone->getTranslationBoneSpace();
			
			x += influence.weight * v.x;
			y += influence.weight * v.y;
			z += influence.weight * v.z;
			
			// transform normal with current state of the bone
			QunVector n(normal);
			n *= pBone->getTransformMatrix();
			
			nx += influence.weight * n.x;
			ny += influence.weight * n.y;
			nz += influence.weight * n.z;
		}
	}

    // save vertex position
    if(hasSpringsAndInternalData)
    {
      // get the physical property of the vertex
      QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

      // assign new vertex position if there is no vertex weight
      if(physicalProperty.weight == 0.0f)
      {
        pVertexBuffer[0] = x * m_axisFactorX;
        pVertexBuffer[1] = y * m_axisFactorY;
        pVertexBuffer[2] = z * m_axisFactorZ;
      }
    }
    else
    {
      pVertexBuffer[0] = x * m_axisFactorX;
      pVertexBuffer[1] = y * m_axisFactorY;
      pVertexBuffer[2] = z * m_axisFactorZ;
    }
    
    // re-normalize normal if necessary
    if (m_Normalize)
    {
	  nx/= m_axisFactorX;
	  ny/= m_axisFactorY;
	  nz/= m_axisFactorZ;

      float scale;
      scale = (float)( 1.0f / sqrt(nx * nx + ny * ny + nz * nz));

      pVertexBuffer[3] = nx * scale;
      pVertexBuffer[4] = ny * scale;
      pVertexBuffer[5] = nz * scale;
    }
    else
    {
      pVertexBuffer[3] = nx;
      pVertexBuffer[4] = ny;
      pVertexBuffer[5] = nz;
    } 


	// next vertex position in buffer	
    pVertexBuffer = (float *)(((char *)pVertexBuffer) + stride) ;
  }

  return vertexCount;
}

 /*****************************************************************************/
/** Qunculates the transformed vertex data.
  *
  * This function calculates and returns the transformed vertex, the transformed 
  * normal data and the texture coords of a specific submesh.
  *
  * @param pSubmesh A pointer to the submesh from which the vertex data should
  *                 be calculated and returned.
  * 
  * @param pVertexBuffer A pointer to the user-provided buffer where the vertex
  *                      data is written to.
  *
  * @param NumTexCoords A integer with the number of texture coords
  *
  * @return The number of vertices written to the buffer.
  *****************************************************************************/


int QunPhysique::calculateVerticesNormalsAndTexCoords(QunSubmesh *pSubmesh, float *pVertexBuffer,int NumTexCoords)
{
  // get bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = m_pModel->getSkeleton()->getVectorBone();

  // get vertex vector of the core submesh
  std::vector<QunCoreSubmesh::Vertex>& vectorVertex = pSubmesh->getCoreSubmesh()->getVectorVertex();

  // get the texture coordinate vector vector
  std::vector<std::vector<QunCoreSubmesh::TextureCoordinate> >& vectorvectorTextureCoordinate = pSubmesh->getCoreSubmesh()->getVectorVectorTextureCoordinate();

  int TextureCoordinateCount=(int)vectorvectorTextureCoordinate.size();

  // check if the map id is valid
  if(((NumTexCoords < 0) || (NumTexCoords > TextureCoordinateCount)))
  {
	 if(TextureCoordinateCount!=0)
	 {    
		 QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
		 return -1;
	 }
  }  

  // get physical property vector of the core submesh
  std::vector<QunCoreSubmesh::PhysicalProperty>& vectorPhysicalProperty = pSubmesh->getCoreSubmesh()->getVectorPhysicalProperty();

  // get the number of vertices
  int vertexCount;
  vertexCount = pSubmesh->getVertexCount();

  // get the sub morph target vector from the core sub mesh
  std::vector<QunCoreSubMorphTarget*>& vectorSubMorphTarget =
  pSubmesh->getCoreSubmesh()->getVectorCoreSubMorphTarget();

  // calculate the base weight
  float baseWeight = pSubmesh->getBaseWeight();

  // get the number of morph targets
  int morphTargetCount = pSubmesh->getMorphTargetWeightCount();

  // Check for spring case
  bool	hasSpringsAndInternalData =
	(pSubmesh->getCoreSubmesh()->getSpringCount() > 0) &&
	pSubmesh->hasInternalData();

  // calculate all submesh vertices
  int vertexId;
  for(vertexId = 0; vertexId < vertexCount; ++vertexId)
  {
    // get the vertex
    QunCoreSubmesh::Vertex& vertex = vectorVertex[vertexId];

    // blend the morph targets
    QunVector position(0,0,0);
    QunVector normal(0,0,0);
    if(baseWeight == 1.0f)
    {
      position.x = vertex.position.x;
      position.y = vertex.position.y;
      position.z = vertex.position.z;
      normal.x = vertex.normal.x;
      normal.y = vertex.normal.y;
      normal.z = vertex.normal.z;
    }
    else
    {
      position.x = baseWeight*vertex.position.x;
      position.y = baseWeight*vertex.position.y;
      position.z = baseWeight*vertex.position.z;
      normal.x = baseWeight*vertex.normal.x;
      normal.y = baseWeight*vertex.normal.y;
      normal.z = baseWeight*vertex.normal.z;
      int morphTargetId;
      for(morphTargetId=0; morphTargetId < morphTargetCount;++morphTargetId)
      {
        QunCoreSubMorphTarget::BlendVertex	blendVertex;
        vectorSubMorphTarget[morphTargetId]->getBlendVertex(vertexId, blendVertex);
        float currentWeight = pSubmesh->getMorphTargetWeight(morphTargetId);
        position.x += currentWeight*blendVertex.position.x;
        position.y += currentWeight*blendVertex.position.y;
        position.z += currentWeight*blendVertex.position.z;
        normal.x += currentWeight*blendVertex.normal.x;
        normal.y += currentWeight*blendVertex.normal.y;
        normal.z += currentWeight*blendVertex.normal.z;
      }
    }

    // initialize vertex
    float x, y, z;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

	// initialize normal
    float nx, ny, nz;
    nx = 0.0f;
    ny = 0.0f;
    nz = 0.0f;

    // blend together all vertex influences
    int influenceId;
	int influenceCount=(int)vertex.vectorInfluence.size();
	if(influenceCount == 0) 
	{
      x = position.x;
      y = position.y;
      z = position.z;
      nx = normal.x;
      ny = normal.y;
      nz = normal.z;
    } 
	else 
	{
		for(influenceId = 0; influenceId < influenceCount; ++influenceId)
		{
			// get the influence
			QunCoreSubmesh::Influence& influence = vertex.vectorInfluence[influenceId];
			
			// get the bone of the influence vertex
			QunBone *pBone;
			pBone = vectorBone[influence.boneId];
			
			// transform vertex with current state of the bone
			QunVector v(position);
			v *= pBone->getTransformMatrix();
			v += pBone->getTranslationBoneSpace();
			
			x += influence.weight * v.x;
			y += influence.weight * v.y;
			z += influence.weight * v.z;
			
			// transform normal with current state of the bone
			QunVector n(normal);	  
			n *= pBone->getTransformMatrix();
			
			nx += influence.weight * n.x;
			ny += influence.weight * n.y;
			nz += influence.weight * n.z;
		}
	}

    // save vertex position
    if(hasSpringsAndInternalData)
    {
      // get the pgysical property of the vertex
      QunCoreSubmesh::PhysicalProperty& physicalProperty = vectorPhysicalProperty[vertexId];

      // assign new vertex position if there is no vertex weight
      if(physicalProperty.weight == 0.0f)
      {
        pVertexBuffer[0] = x * m_axisFactorX;
        pVertexBuffer[1] = y * m_axisFactorY;
        pVertexBuffer[2] = z * m_axisFactorZ;
      }
    }
    else
    {
      pVertexBuffer[0] = x * m_axisFactorX;
      pVertexBuffer[1] = y * m_axisFactorY;
      pVertexBuffer[2] = z * m_axisFactorZ;
    }
    
	 // re-normalize normal if necessary
    if (m_Normalize)
    {
	  nx/= m_axisFactorX;
	  ny/= m_axisFactorY;
	  nz/= m_axisFactorZ;

      float scale;
      scale = (float) (1.0f / sqrt(nx * nx + ny * ny + nz * nz));

      pVertexBuffer[3] = nx * scale;
      pVertexBuffer[4] = ny * scale;
      pVertexBuffer[5] = nz * scale;
    }
    else
    {
      pVertexBuffer[3] = nx;
      pVertexBuffer[4] = ny;
      pVertexBuffer[5] = nz;
    }

	pVertexBuffer += 6;
	
	if(TextureCoordinateCount==0)
	{
		pVertexBuffer+=NumTexCoords*2;
	}
	else
	{
		for(int mapId=0; mapId < NumTexCoords; ++mapId)
		{
			pVertexBuffer[0] = vectorvectorTextureCoordinate[mapId][vertexId].u;
			pVertexBuffer[1] = vectorvectorTextureCoordinate[mapId][vertexId].v;			
			pVertexBuffer += 2;
		}
	}
  }

  return vertexCount;
}


 /*****************************************************************************/
/** Updates all the internally handled attached meshes.
  *
  * This function updates all the attached meshes of the model that are handled
  * internally.
  *****************************************************************************/

void QunPhysique::update()
{
  // get the attached meshes vector
  std::vector<QunMesh *>& vectorMesh = m_pModel->getVectorMesh();

  // loop through all the attached meshes
  std::vector<QunMesh *>::iterator iteratorMesh;
  for(iteratorMesh = vectorMesh.begin(); iteratorMesh != vectorMesh.end(); ++iteratorMesh)
  {
    // get the submesh vector of the mesh
    std::vector<QunSubmesh *>& vectorSubmesh = (*iteratorMesh)->getVectorSubmesh();

    // loop through all the submeshes of the mesh
    std::vector<QunSubmesh *>::iterator iteratorSubmesh;
    for(iteratorSubmesh = vectorSubmesh.begin(); iteratorSubmesh != vectorSubmesh.end(); ++iteratorSubmesh)
    {
      // check if the submesh handles vertex data internally
      if((*iteratorSubmesh)->hasInternalData())
      {
        // calculate the transformed vertices and store them in the submesh
        std::vector<QunVector>& vectorVertex = (*iteratorSubmesh)->getVectorVertex();
        calculateVertices(*iteratorSubmesh, (float *)&vectorVertex[0]);

        // calculate the transformed normals and store them in the submesh
        std::vector<QunVector>& vectorNormal = (*iteratorSubmesh)->getVectorNormal();
        calculateNormals(*iteratorSubmesh, (float *)&vectorNormal[0]);

        unsigned mapId;
        for(mapId=0;mapId< (*iteratorSubmesh)->getVectorVectorTangentSpace().size();mapId++)
        {
          if((*iteratorSubmesh)->isTangentsEnabled(mapId))
          {
            std::vector<QunSubmesh::TangentSpace>& vectorTangentSpace = (*iteratorSubmesh)->getVectorVectorTangentSpace()[mapId];
            calculateTangentSpaces(*iteratorSubmesh, mapId,(float *)&vectorTangentSpace[0]);
          }
        }

      }
    }
  }
}

 /*****************************************************************************/
/** Sets the normalization flag to true or false.
  *
  * This function sets the normalization flag on or off. If off, the normals
  * calculated by Qun3D will not be normalized. Instead, this transform is left
  * up to the user.
  *****************************************************************************/

void QunPhysique::setNormalization(bool normalize)
{
  m_Normalize = normalize;
}


void QunPhysique::setAxisFactorX(float factor)
{
	m_axisFactorX = factor;
	m_Normalize = true;	
}

void QunPhysique::setAxisFactorY(float factor)
{
	m_axisFactorY = factor;
	m_Normalize = true;	
}

void QunPhysique::setAxisFactorZ(float factor)
{
	m_axisFactorZ = factor;
	m_Normalize = true;	
}
//****************************************************************************//
