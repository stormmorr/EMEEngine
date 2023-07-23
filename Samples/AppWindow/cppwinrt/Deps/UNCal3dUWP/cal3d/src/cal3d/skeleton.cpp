//****************************************************************************//
// calskeleton.cpp                                                            //
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

#include "cal3d/skeleton.h"
#include "cal3d/error.h"
#include "cal3d/bone.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coremodel.h"
#include "cal3d/corebone.h" // DEBUG

 /*****************************************************************************/
/** Constructs the skeleton instance.
  *
  * This function is the default constructor of the skeleton instance.
  *****************************************************************************/

QunSkeleton::QunSkeleton(QunCoreSkeleton* pCoreSkeleton)
  : m_pCoreSkeleton(0)
  , m_isBoundingBoxesComputed(false)
{
  assert(pCoreSkeleton);
  m_pCoreSkeleton = pCoreSkeleton;

  // clone the skeleton structure of the core skeleton
  std::vector<QunCoreBone *>& vectorCoreBone = pCoreSkeleton->getVectorCoreBone();

  // get the number of bones
  int boneCount = vectorCoreBone.size();

  // reserve space in the bone vector
  m_vectorBone.reserve(boneCount);

  // clone every core bone
  for(int boneId = 0; boneId < boneCount; ++boneId)
  {
    QunBone *pBone = new QunBone(vectorCoreBone[boneId]);

    // set skeleton in the bone instance
    pBone->setSkeleton(this);

    // insert bone into bone vector
    m_vectorBone.push_back(pBone);
  }
}

 /*****************************************************************************/
/** Destructs the skeleton instance.
  *
  * This function is the destructor of the skeleton instance.
  *****************************************************************************/

QunSkeleton::~QunSkeleton()
{
  // destroy all bones
  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    delete (*iteratorBone);
  }
}

 /*****************************************************************************/
/** Qunculates the state of the skeleton instance.
  *
  * This function calculates the state of the skeleton instance by recursively
  * calculating the states of its bones.
  *****************************************************************************/

void QunSkeleton::calculateState()
{
  // calculate all bone states of the skeleton
  std::vector<int>& listRootCoreBoneId = m_pCoreSkeleton->getVectorRootCoreBoneId();

  std::vector<int>::iterator iteratorRootBoneId;
  for(iteratorRootBoneId = listRootCoreBoneId.begin(); iteratorRootBoneId != listRootCoreBoneId.end(); ++iteratorRootBoneId)
  {
    m_vectorBone[*iteratorRootBoneId]->calculateState();
  }
  m_isBoundingBoxesComputed=false;
}

void QunSkeleton::calculateStateTorque()
{
  //*** Bip01 ***
  m_vectorBone[0]->calculateStateTorque();
  m_vectorBone[2]->calculateStateTorque();

  //*** Spine ***
  m_vectorBone[3]->calculateStateTorque();
  m_vectorBone[4]->calculateStateTorque();
  m_vectorBone[5]->calculateStateTorque();
  m_vectorBone[6]->calculateStateTorque();

  //*** Neck / Head ***
  m_vectorBone[7]->calculateStateTorque();
  m_vectorBone[8]->calculateStateTorque();

  //*** Left Up Side
  m_vectorBone[9]->calculateStateTorque();
  m_vectorBone[10]->calculateStateTorque();
  m_vectorBone[11]->calculateStateTorque();
  m_vectorBone[12]->calculateStateTorque();

  //___ Reduced Qunc ___
  m_vectorBone[13]->calculateStateTrans();
  m_vectorBone[14]->calculateStateTrans();
  m_vectorBone[15]->calculateStateTrans();
  m_vectorBone[16]->calculateStateTrans();
  m_vectorBone[17]->calculateStateTrans();
  m_vectorBone[18]->calculateStateTrans();
  m_vectorBone[19]->calculateStateTrans();
  m_vectorBone[20]->calculateStateTrans();
  m_vectorBone[21]->calculateStateTrans();
  m_vectorBone[22]->calculateStateTrans();
  m_vectorBone[23]->calculateStateTrans();
  m_vectorBone[24]->calculateStateTrans();
  m_vectorBone[25]->calculateStateTrans();
  m_vectorBone[26]->calculateStateTrans();
  m_vectorBone[27]->calculateStateTrans();

  //*** Right Up Side
  m_vectorBone[28]->calculateStateTorque();
  m_vectorBone[29]->calculateStateTorque();
  m_vectorBone[30]->calculateStateTorque();
  m_vectorBone[31]->calculateStateTorque();

  //___ Reduced Qunc ___
  m_vectorBone[32]->calculateStateTrans();
  m_vectorBone[33]->calculateStateTrans();
  m_vectorBone[34]->calculateStateTrans();
  m_vectorBone[35]->calculateStateTrans();
  m_vectorBone[36]->calculateStateTrans();
  m_vectorBone[37]->calculateStateTrans();
  m_vectorBone[38]->calculateStateTrans();
  m_vectorBone[39]->calculateStateTrans();
  m_vectorBone[40]->calculateStateTrans();
  m_vectorBone[41]->calculateStateTrans();
  m_vectorBone[42]->calculateStateTrans();
  m_vectorBone[43]->calculateStateTrans();
  m_vectorBone[44]->calculateStateTrans();
  m_vectorBone[45]->calculateStateTrans();
  m_vectorBone[46]->calculateStateTrans();

  //*** Left Down Side
  m_vectorBone[47]->calculateStateTorque();
  m_vectorBone[48]->calculateStateTorque();
  m_vectorBone[49]->calculateStateTorque();

  //___ Reduced Qunc ___
  m_vectorBone[50]->calculateStateTrans();

  //*** Right Down Side
  m_vectorBone[51]->calculateStateTorque();
  m_vectorBone[52]->calculateStateTorque();
  m_vectorBone[53]->calculateStateTorque();

  //___ Reduced Qunc ___
  m_vectorBone[54]->calculateStateTrans();

  m_isBoundingBoxesComputed=false;
}

 /*****************************************************************************/
/** Clears the state of the skeleton instance.
  *
  * This function clears the state of the skeleton instance by recursively
  * clearing the states of its bones.
  *****************************************************************************/

void QunSkeleton::clearState()
{
  // clear all bone states of the skeleton
  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    (*iteratorBone)->clearState();
  }
  m_isBoundingBoxesComputed=false;
}


 /*****************************************************************************/
/** Provides access to a bone.
  *
  * This function returns the bone with the given ID.
  *
  * @param boneId The ID of the bone that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the bone
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunBone *QunSkeleton::getBone(int boneId) const
{
  return m_vectorBone[boneId];
}

 /*****************************************************************************/
/** Provides access to the core skeleton.
  *
  * This function returns the core skeleton on which this skeleton instance is
  * based on.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happend
  *****************************************************************************/

QunCoreSkeleton *QunSkeleton::getCoreSkeleton() const
{
  return m_pCoreSkeleton;
}

 /*****************************************************************************/
/** Returns the bone vector.
  *
  * This function returns the vector that contains all bones of the skeleton
  * instance.
  *
  * @return A reference to the bone vector.
  *****************************************************************************/

std::vector<QunBone *>& QunSkeleton::getVectorBone()
{
  return m_vectorBone;
}

 /*****************************************************************************/
/** Locks the state of the skeleton instance.
  *
  * This function locks the state of the skeleton instance by recursively
  * locking the states of its bones.
  *****************************************************************************/

void QunSkeleton::lockState()
{
  // lock all bone states of the skeleton
  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    (*iteratorBone)->lockState();
  }
}

void QunSkeleton::lockStateTorque()
{
  //*** Bip01 ***
  m_vectorBone[0]->lockState();
  m_vectorBone[2]->lockState();

  //*** Pelvis ***
  m_vectorBone[2]->lockState();

  //*** Spine ***
  m_vectorBone[3]->lockState();
  m_vectorBone[4]->lockState();
  m_vectorBone[5]->lockState();
  m_vectorBone[6]->lockState();

  //*** Neck / Head ***
  m_vectorBone[7]->lockState();
  m_vectorBone[8]->lockState();

  //*** Left Up Side
  m_vectorBone[9]->lockState();
  m_vectorBone[10]->lockState();
  m_vectorBone[11]->lockState();
  m_vectorBone[12]->lockState();

  //*** Right Up Side
  m_vectorBone[28]->lockState();
  m_vectorBone[29]->lockState();
  m_vectorBone[30]->lockState();
  m_vectorBone[31]->lockState();

  //*** Left Down Side
  m_vectorBone[47]->lockState();
  m_vectorBone[48]->lockState();
  m_vectorBone[49]->lockState();

  //*** Right Down Side
  m_vectorBone[51]->lockState();
  m_vectorBone[52]->lockState();
  m_vectorBone[53]->lockState();
}

/*****************************************************************************/
/** Qunculates axis aligned bounding box of skeleton bones
  *
  * @param min The vector where the min values of bb are stored.
  * @param man The vector where the max values of bb are stored.
  *
  *****************************************************************************/

void QunSkeleton::getBoneBoundingBox(float *min, float *max)
{
  if(!m_isBoundingBoxesComputed)
  {
	  calculateBoundingBoxes();
  }


  std::vector<QunBone *>::iterator iteratorBone;

  if ((iteratorBone = m_vectorBone.begin()) != m_vectorBone.end()) {
    const QunVector& translation = (*iteratorBone)->getTranslationAbsolute();

    min[0] = max[0] = translation[0];
    min[1] = max[1] = translation[1];
    min[2] = max[2] = translation[2];

    ++iteratorBone;
  }

  for(; iteratorBone != m_vectorBone.end(); ++iteratorBone) {
    const QunVector& translation = (*iteratorBone)->getTranslationAbsolute();

    if (translation[0] > max[0])
      max[0] = translation[0];
    else if (translation[0] < min[0])
      min[0] = translation[0];

    if (translation[1] > max[1])
      max[1] = translation[1];
    else if (translation[1] < min[1])
      min[1] = translation[1];

    if (translation[2] > max[2])
      max[2] = translation[2];
    else if (translation[2] < min[2])
      min[2] = translation[2];

  }

}
 /*****************************************************************************/
/** Qunculates bounding boxes.
  *
  * This function Qunculates the bounding box of every bone in the Skeleton.
  *
  *****************************************************************************/


void QunSkeleton::calculateBoundingBoxes()
{
   if(m_isBoundingBoxesComputed) 
	   return;

   for(size_t boneId=0;boneId<m_vectorBone.size();++boneId)
   {
      m_vectorBone[boneId]->calculateBoundingBox();
   }
   m_isBoundingBoxesComputed=true;

}


//****************************************************************************//



//****************************************************************************//
//****************************************************************************//
//****************************************************************************//
// DEBUG-/TEST-CODE                                                           //
//****************************************************************************//
//****************************************************************************//
//****************************************************************************//

int QunSkeleton::getBonePoints(float *pPoints)
{
  int nrPoints;
  nrPoints = 0;

  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    const QunVector& translation = (*iteratorBone)->getTranslationAbsolute();

    *pPoints++ = translation[0];
    *pPoints++ = translation[1];
    *pPoints++ = translation[2];

    nrPoints++;
  }

  return nrPoints;
}

int QunSkeleton::getBonePointsStatic(float *pPoints)
{
  int nrPoints;
  nrPoints = 0;

  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    const QunVector& translation = (*iteratorBone)->getCoreBone()->getTranslationAbsolute();

    *pPoints++ = translation[0];
    *pPoints++ = translation[1];
    *pPoints++ = translation[2];

    nrPoints++;
  }

  return nrPoints;
}

int QunSkeleton::getBoneLines(float *pLines)
{
  int nrLines;
  nrLines = 0;

  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    int parentId;
    parentId = (*iteratorBone)->getCoreBone()->getParentId();

    if(parentId != -1)
    {
      QunBone *pParent;
      pParent = m_vectorBone[parentId];

      const QunVector& translation = (*iteratorBone)->getTranslationAbsolute();
      const QunVector& translationParent = pParent->getTranslationAbsolute();

      *pLines++ = translationParent[0];
      *pLines++ = translationParent[1];
      *pLines++ = translationParent[2];

      *pLines++ = translation[0];
      *pLines++ = translation[1];
      *pLines++ = translation[2];

      nrLines++;
    }
  }

  return nrLines;
}

int QunSkeleton::getBoneLinesStatic(float *pLines)
{
  int nrLines;
  nrLines = 0;

  std::vector<QunBone *>::iterator iteratorBone;
  for(iteratorBone = m_vectorBone.begin(); iteratorBone != m_vectorBone.end(); ++iteratorBone)
  {
    int parentId;
    parentId = (*iteratorBone)->getCoreBone()->getParentId();

    if(parentId != -1)
    {
      QunBone *pParent;
      pParent = m_vectorBone[parentId];

      const QunVector& translation = (*iteratorBone)->getCoreBone()->getTranslationAbsolute();
      const QunVector& translationParent = pParent->getCoreBone()->getTranslationAbsolute();

      *pLines++ = translationParent[0];
      *pLines++ = translationParent[1];
      *pLines++ = translationParent[2];

      *pLines++ = translation[0];
      *pLines++ = translation[1];
      *pLines++ = translation[2];

      nrLines++;
    }
  }

  return nrLines;
}

//****************************************************************************//
//****************************************************************************//
//****************************************************************************//
// END DEBUG-/TEST-CODE                                                       //
//****************************************************************************//
//****************************************************************************//
//****************************************************************************//
