//****************************************************************************//
// mixer.cpp                                                                  //
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
#include "cal3d/mixer.h"
#include "cal3d/coremodel.h"
#include "cal3d/corebone.h"
#include "cal3d/coreanimation.h"
#include "cal3d/coretrack.h"
#include "cal3d/corekeyframe.h"
#include "cal3d/model.h"
#include "cal3d/skeleton.h"
#include "cal3d/bone.h"
#include "cal3d/animation.h"
#include "cal3d/animation_action.h"
#include "cal3d/animation_cycle.h"

 /*****************************************************************************/
/** Constructs the mixer instance.
  *
  * This function is the default constructor of the mixer instance.
  *****************************************************************************/

QunMixer::QunMixer(QunModel* pModel)
{
  assert(pModel);

  m_pModel = pModel;

  // build the animation table
  int coreAnimationCount = m_pModel->getCoreModel()->getCoreAnimationCount();

  m_vectorAnimation.reserve(coreAnimationCount);
  QunAnimation* null = 0;
  m_vectorAnimation.insert(m_vectorAnimation.begin(), coreAnimationCount, null);

  // set the animation time/duration values to default
  m_animationTime = 0.0f;
  m_animationDuration = 0.0f;
  m_timeFactor = 1.0f;

  m_RagSheet = new RagSheet();
}

 /*****************************************************************************/
/** Destructs the mixer instance.
  *
  * This function is the destructor of the mixer instance.
  *****************************************************************************/

QunMixer::~QunMixer()
{
  // destroy all active animation actions
  while(!m_listAnimationAction.empty())
  {
    QunAnimationAction *pAnimationAction = m_listAnimationAction.front();
    m_listAnimationAction.pop_front();

    delete pAnimationAction;
  }

  // destroy all active animation cycles
  while(!m_listAnimationCycle.empty())
  {
    QunAnimationCycle *pAnimationCycle;
    pAnimationCycle = m_listAnimationCycle.front();
    m_listAnimationCycle.pop_front();

    delete pAnimationCycle;
  }

  // clear the animation table
  m_vectorAnimation.clear();

  m_pModel = 0;
}

///
/// Examines the given animation and if the first and last keyframe of a given track
/// do not match up, the first key frame is duplicated and added to the end of the track
/// to ensure smooth looping.
///
static void addExtraKeyframeForLoopedAnim(QunCoreAnimation* pCoreAnimation)
{
	std::list<QunCoreTrack*>& listCoreTrack = pCoreAnimation->getListCoreTrack();

   if(listCoreTrack.size() == 0)
		 return;

	QunCoreTrack *coreTrack = listCoreTrack.front();
  if(coreTrack == 0)
		 return;

	QunCoreKeyframe *lastKeyframe = coreTrack->getCoreKeyframe(coreTrack->getCoreKeyframeCount()-1);
	if(lastKeyframe == 0)
		 return;

	if(lastKeyframe->getTime() < pCoreAnimation->getDuration())
	{
		std::list<QunCoreTrack *>::iterator itr;
    for(itr=listCoreTrack.begin();itr!=listCoreTrack.end();++itr)
		{
			coreTrack = *itr;

			QunCoreKeyframe *firstKeyframe = coreTrack->getCoreKeyframe(0);
      QunCoreKeyframe *newKeyframe = new QunCoreKeyframe();

      newKeyframe->setTranslation(firstKeyframe->getTranslation());
      newKeyframe->setRotation(firstKeyframe->getRotation());
      newKeyframe->setTime(pCoreAnimation->getDuration());

      coreTrack->addCoreKeyframe(newKeyframe);
		}
	}
}

void QunMixer::BeginAnim(void)
{
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  pSkeleton->clearState();
}

void QunMixer::EndAnim(void)
{
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::BlendAnim(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

#if 0	// allocate a new animation cycle instance
  QunAnimationCycle *pAnimationCycle = new(std::nothrow) QunAnimationCycle(pCoreAnimation);

  pAnimationCycle->blend(weight, delay);
#endif

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

#if 0	// clear the skeleton state
  pSkeleton->clearState();
#endif

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
#if 1
	  pBone->blending(i_blendamount, translation, rotation);
#else
	  pBone->blendState(i_blendamount, translation, rotation);
#endif
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();

}

void QunMixer::BlendAnimMin(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
	  pBone->blending(i_blendamount, translation, rotation);
    }
}

void QunMixer::BlendAnimTorque(int i_motion, float i_time, float i_blendamount, int i_Level)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

#if 0	// allocate a new animation cycle instance
  QunAnimationCycle *pAnimationCycle = new(std::nothrow) QunAnimationCycle(pCoreAnimation);

  pAnimationCycle->blend(weight, delay);
#endif

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

#if 0	// clear the skeleton state
  pSkeleton->clearState();
#endif

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
#if 1
	  pBone->blending(i_blendamount, translation, rotation);
#else
	  pBone->blendState(i_blendamount, translation, rotation);
#endif

	  if((*iteratorCoreTrack)->getCoreBoneId() == 12)
		{
		//___ Reduced Qunc ___
		vectorBone[13]->lockState();
		vectorBone[14]->lockState();
		vectorBone[15]->lockState();
		vectorBone[16]->lockState();
		vectorBone[17]->lockState();
		vectorBone[18]->lockState();
		vectorBone[19]->lockState();
		vectorBone[20]->lockState();
		vectorBone[21]->lockState();
		vectorBone[22]->lockState();
		vectorBone[23]->lockState();
		vectorBone[24]->lockState();
		vectorBone[25]->lockState();
		vectorBone[26]->lockState();
		vectorBone[27]->lockState();

		//___ Reduced Qunc ___
		vectorBone[13]->calculateStateTorque();
		vectorBone[14]->calculateStateTorque();
		vectorBone[15]->calculateStateTorque();
		vectorBone[16]->calculateStateTorque();
		vectorBone[17]->calculateStateTorque();
		vectorBone[18]->calculateStateTorque();
		vectorBone[19]->calculateStateTorque();
		vectorBone[20]->calculateStateTorque();
		vectorBone[21]->calculateStateTorque();
		vectorBone[22]->calculateStateTorque();
		vectorBone[23]->calculateStateTorque();
		vectorBone[24]->calculateStateTorque();
		vectorBone[25]->calculateStateTorque();
		vectorBone[26]->calculateStateTorque();
		vectorBone[27]->calculateStateTorque();
		}
	  else
		{
		if((*iteratorCoreTrack)->getCoreBoneId() == 31)
			{
			//___ Reduced Qunc ___
			vectorBone[32]->lockState();
			vectorBone[33]->lockState();
			vectorBone[34]->lockState();
			vectorBone[35]->lockState();
			vectorBone[36]->lockState();
			vectorBone[37]->lockState();
			vectorBone[38]->lockState();
			vectorBone[39]->lockState();
			vectorBone[40]->lockState();
			vectorBone[41]->lockState();
			vectorBone[42]->lockState();
			vectorBone[43]->lockState();
			vectorBone[44]->lockState();
			vectorBone[45]->lockState();
			vectorBone[46]->lockState();

			//___ Reduced Qunc ___
			vectorBone[32]->calculateStateTorque();
			vectorBone[33]->calculateStateTorque();
			vectorBone[34]->calculateStateTorque();
			vectorBone[35]->calculateStateTorque();
			vectorBone[36]->calculateStateTorque();
			vectorBone[37]->calculateStateTorque();
			vectorBone[38]->calculateStateTorque();
			vectorBone[39]->calculateStateTorque();
			vectorBone[40]->calculateStateTorque();
			vectorBone[41]->calculateStateTorque();
			vectorBone[42]->calculateStateTorque();
			vectorBone[43]->calculateStateTorque();
			vectorBone[44]->calculateStateTorque();
			vectorBone[45]->calculateStateTorque();
			vectorBone[46]->calculateStateTorque();
			}
		else
			{
			if((*iteratorCoreTrack)->getCoreBoneId() < 12 || (*iteratorCoreTrack)->getCoreBoneId() > 46 || ((*iteratorCoreTrack)->getCoreBoneId() > 27 && (*iteratorCoreTrack)->getCoreBoneId() < 31))
				{
				pBone->lockState();
				pBone->calculateStateTorque();
				}
			}
		}
    }

  // lock the skeleton state
  //pSkeleton->lockStateTorque();

  // let the skeleton calculate its final state
  //pSkeleton->calculateStateTorque();
}

void QunMixer::BlendAnimPhysics(int i_motion, float i_time, float i_blendamount)
{
  // get the animation for the given id
  //QunAnimation *pAnimation = m_vectorAnimation[i_motion];

  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // allocate a new animation cycle instance
  //QunAnimationCycle *pAnimationCycle = new(std::nothrow) QunAnimationCycle(pCoreAnimation);

  //pAnimationCycle->blend(weight, delay);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // clear the skeleton state
  pSkeleton->clearState();

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

	  m_RagSheet->Quat[(*iteratorCoreTrack)->getCoreBoneId()] = &rotation;
	  m_RagSheet->Vector[(*iteratorCoreTrack)->getCoreBoneId()] = &translation;

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::ApplyAnim(int i_motion, float i_time, float i_blendamount)
{
  // get the animation for the given id
  //QunAnimation *pAnimation = m_vectorAnimation[i_motion];

  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // allocate a new animation cycle instance
  //QunAnimationCycle *pAnimationCycle = new(std::nothrow) QunAnimationCycle(pCoreAnimation);

  //pAnimationCycle->blend(weight, delay);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // clear the skeleton state
  //pSkeleton->clearState();

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::ClearAnim(void)
{
  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // clear the skeleton state
  pSkeleton->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::AnimateLeftLeg(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  pSkeleton->m_isBoundingBoxesComputed = false;

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // clear all bone states of the skeleton
  QunBone *BIP01LTHIGH;
  QunBone *BIP01LCALF;
  QunBone *BIP01LFOOT;
  QunBone *BIP01LTOE0;

  BIP01LTHIGH = vectorBone[47];
  BIP01LCALF = vectorBone[48];
  BIP01LFOOT = vectorBone[49];
  BIP01LTOE0 = vectorBone[50];

  BIP01LTHIGH->clearState();
  BIP01LCALF->clearState();
  BIP01LFOOT->clearState();
  BIP01LTOE0->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::AnimateRightLeg(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // clear all bone states of the skeleton
  QunBone *BIP01RTHIGH;
  QunBone *BIP01RCALF;
  QunBone *BIP01RFOOT;
  QunBone *BIP01RTOE0;

  BIP01RTHIGH = vectorBone[51];
  BIP01RCALF = vectorBone[52];
  BIP01RFOOT = vectorBone[53];
  BIP01RTOE0 = vectorBone[54];

  BIP01RTHIGH->clearState();
  BIP01RCALF->clearState();
  BIP01RFOOT->clearState();
  BIP01RTOE0->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::AnimateLeftArm(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  pSkeleton->m_isBoundingBoxesComputed = false;

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // clear all bone states of the skeleton
  QunBone *BIP01LUPPERARM;
  QunBone *BIP01LFOREARM;
  QunBone *BIP01LHAND;
  QunBone *BIP01LFINGER0;
  QunBone *BIP01LFINGER01;
  QunBone *BIP01LFINGER02;
  QunBone *BIP01LFINGER1;
  QunBone *BIP01LFINGER11;
  QunBone *BIP01LFINGER12;
  QunBone *BIP01LFINGER2;
  QunBone *BIP01LFINGER21;
  QunBone *BIP01LFINGER22;
  QunBone *BIP01LFINGER3;
  QunBone *BIP01LFINGER31;
  QunBone *BIP01LFINGER32;
  QunBone *BIP01LFINGER4;
  QunBone *BIP01LFINGER41;
  QunBone *BIP01LFINGER42;

  BIP01LUPPERARM = vectorBone[10];
  BIP01LFOREARM = vectorBone[11];
  BIP01LHAND = vectorBone[12];
  BIP01LFINGER0 = vectorBone[13];
  BIP01LFINGER01 = vectorBone[14];
  BIP01LFINGER02 = vectorBone[15];
  BIP01LFINGER1 = vectorBone[16];
  BIP01LFINGER11 = vectorBone[17];
  BIP01LFINGER12 = vectorBone[18];
  BIP01LFINGER2 = vectorBone[19];
  BIP01LFINGER21 = vectorBone[20];
  BIP01LFINGER22 = vectorBone[21];
  BIP01LFINGER3 = vectorBone[22];
  BIP01LFINGER31 = vectorBone[23];
  BIP01LFINGER32 = vectorBone[24];
  BIP01LFINGER4 = vectorBone[25];
  BIP01LFINGER41 = vectorBone[26];
  BIP01LFINGER42 = vectorBone[27];

  BIP01LUPPERARM->clearState();
  BIP01LFOREARM->clearState();
  BIP01LHAND->clearState();
  BIP01LFINGER0->clearState();
  BIP01LFINGER01->clearState();
  BIP01LFINGER02->clearState();
  BIP01LFINGER1->clearState();
  BIP01LFINGER11->clearState();
  BIP01LFINGER12->clearState();
  BIP01LFINGER2->clearState();
  BIP01LFINGER21->clearState();
  BIP01LFINGER22->clearState();
  BIP01LFINGER3->clearState();
  BIP01LFINGER31->clearState();
  BIP01LFINGER32->clearState();
  BIP01LFINGER4->clearState();
  BIP01LFINGER41->clearState();
  BIP01LFINGER42->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::AnimateRightArm(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  pSkeleton->m_isBoundingBoxesComputed = false;

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // clear all bone states of the skeleton
  QunBone *BIP01RUPPERARM;
  QunBone *BIP01RFOREARM;
  QunBone *BIP01RHAND;
  QunBone *BIP01RFINGER0;
  QunBone *BIP01RFINGER01;
  QunBone *BIP01RFINGER02;
  QunBone *BIP01RFINGER1;
  QunBone *BIP01RFINGER11;
  QunBone *BIP01RFINGER12;
  QunBone *BIP01RFINGER2;
  QunBone *BIP01RFINGER21;
  QunBone *BIP01RFINGER22;
  QunBone *BIP01RFINGER3;
  QunBone *BIP01RFINGER31;
  QunBone *BIP01RFINGER32;
  QunBone *BIP01RFINGER4;
  QunBone *BIP01RFINGER41;
  QunBone *BIP01RFINGER42;

  BIP01RUPPERARM = vectorBone[29];
  BIP01RFOREARM = vectorBone[30];
  BIP01RHAND = vectorBone[31];
  BIP01RFINGER0 = vectorBone[32];
  BIP01RFINGER01 = vectorBone[33];
  BIP01RFINGER02 = vectorBone[34];
  BIP01RFINGER1 = vectorBone[35];
  BIP01RFINGER11 = vectorBone[36];
  BIP01RFINGER12 = vectorBone[37];
  BIP01RFINGER2 = vectorBone[38];
  BIP01RFINGER21 = vectorBone[39];
  BIP01RFINGER22 = vectorBone[40];
  BIP01RFINGER3 = vectorBone[41];
  BIP01RFINGER31 = vectorBone[42];
  BIP01RFINGER32 = vectorBone[43];
  BIP01RFINGER4 = vectorBone[44];
  BIP01RFINGER41 = vectorBone[45];
  BIP01RFINGER42 = vectorBone[46];

  BIP01RUPPERARM->clearState();
  BIP01RFOREARM->clearState();
  BIP01RHAND->clearState();
  BIP01RFINGER0->clearState();
  BIP01RFINGER01->clearState();
  BIP01RFINGER02->clearState();
  BIP01RFINGER1->clearState();
  BIP01RFINGER11->clearState();
  BIP01RFINGER12->clearState();
  BIP01RFINGER2->clearState();
  BIP01RFINGER21->clearState();
  BIP01RFINGER22->clearState();
  BIP01RFINGER3->clearState();
  BIP01RFINGER31->clearState();
  BIP01RFINGER32->clearState();
  BIP01RFINGER4->clearState();
  BIP01RFINGER41->clearState();
  BIP01RFINGER42->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(i_time, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState(i_blendamount, translation, rotation);
    }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

void QunMixer::AnimatePivot(int i_motion, float i_time, float i_blendamount)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(i_motion);

  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  pSkeleton->m_isBoundingBoxesComputed = false;

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // clear all bone states of the skeleton
  QunBone *BIP01;
  QunBone *BIP02;
  QunBone *BIP03;
  QunBone *BIP04;
  QunBone *BIP05;
  QunBone *BIP06;
  QunBone *BIP07;

  BIP01 = vectorBone[0];
  BIP02 = vectorBone[1];
  BIP03 = vectorBone[2];
  BIP04 = vectorBone[3];
  BIP05 = vectorBone[4];
  BIP06 = vectorBone[5];
  BIP07 = vectorBone[6];

  BIP01->clearState();
  BIP02->clearState();
  BIP03->clearState();
  BIP04->clearState();
  BIP05->clearState();
  BIP06->clearState();
  BIP07->clearState();

  // lock the skeleton state
  pSkeleton->lockState();

  // get the list of core tracks of above core animation
  std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

  // loop through all core tracks of the core animation
  std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
		{
		// get the appropriate bone of the track
		QunBone *pBone;
		int i_boneindex = (*iteratorCoreTrack)->getCoreBoneId();
		if(i_boneindex == 0
			|| i_boneindex == 1
			|| i_boneindex == 2
			|| i_boneindex == 3
			|| i_boneindex == 4
			|| i_boneindex == 5
			|| i_boneindex == 6)
			{
			pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

			// get the current translation and rotation
			QunVector translation;
			QunQuaternion rotation;
			(*iteratorCoreTrack)->getState(i_time, translation, rotation);

			// blend the bone state with the new state
			pBone->blendState(i_blendamount, translation, rotation);
			}
		}

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

 /*****************************************************************************/
/** Interpolates the weight of an animation cycle.
  *
  * This function interpolates the weight of an animation cycle to a new value
  * in a given amount of time. If the specified animation cycle is not active
  * yet, it is activated.
  *
  * @param id The ID of the animation cycle that should be blended.
  * @param weight The weight to interpolate the animation cycle to.
  * @param delay The time in seconds until the new weight should be reached.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunMixer::blendCycle(int id, float weight, float delay)
{
  if((id < 0) || (id >= (int)m_vectorAnimation.size()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the animation for the given id
  QunAnimation *pAnimation = m_vectorAnimation[id];

  // create a new animation instance if it is not active yet
  if(pAnimation == 0)
  {
    // take the fast way out if we are trying to clear an inactive animation
    if(weight == 0.0f) return true;

    // get the core animation
    QunCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
    if(pCoreAnimation == 0) return false;

    // Ensure that the animation's first and last key frame match for proper
    // looping.
    ::addExtraKeyframeForLoopedAnim(pCoreAnimation);

    // allocate a new animation cycle instance
    QunAnimationCycle *pAnimationCycle = new(std::nothrow) QunAnimationCycle(pCoreAnimation);
    if(pAnimationCycle == 0)
    {
      QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
      return false;
    }

    // insert new animation into the tables
    m_vectorAnimation[id] = pAnimationCycle;
    m_listAnimationCycle.push_front(pAnimationCycle);

    // blend the animation
    return pAnimationCycle->blend(weight, delay);
  }

  // check if this is really a animation cycle instance
  if(pAnimation->getType() != QunAnimation::TYPE_CYCLE)
  {
      QunError::setLastError(QunError::INVALID_ANIMATION_TYPE, __FILE__, __LINE__);
      return false;
  }

  // clear the animation cycle from the active vector if the target weight is zero
  if(weight == 0.0f)
  {
      m_vectorAnimation[id] = 0;
  }

  // cast it to an animation cycle
  QunAnimationCycle *pAnimationCycle;
  pAnimationCycle = (QunAnimationCycle *)pAnimation;

  // blend the animation cycle
  pAnimationCycle->blend(weight, delay);
  pAnimationCycle->checkQunlbacks(0,m_pModel);
  return true;
}

 /*****************************************************************************/
/** Fades an animation cycle out.
  *
  * This function fades an animation cycle out in a given amount of time.
  *
  * @param id The ID of the animation cycle that should be faded out.
  * @param delay The time in seconds until the the animation cycle is
  *              completely removed.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunMixer::clearCycle(int id, float delay)
{
  // check if the animation id is valid
  if((id < 0) || (id >= (int)m_vectorAnimation.size()))
  {
    QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the animation for the given id
  QunAnimation *pAnimation;
  pAnimation = m_vectorAnimation[id];

  // we can only clear cycles that are active
  if(pAnimation == 0) return true;

  // check if this is really a animation cycle instance
  if(pAnimation->getType() != QunAnimation::TYPE_CYCLE)
  {
      QunError::setLastError(QunError::INVALID_ANIMATION_TYPE, __FILE__, __LINE__);
      return false;
  }

  // clear the animation cycle from the active vector
  m_vectorAnimation[id] = 0;

  // cast it to an animation cycle
  QunAnimationCycle *pAnimationCycle;
  pAnimationCycle = (QunAnimationCycle *)pAnimation;

  // set animation cycle to async state
  pAnimationCycle->setAsync(m_animationTime, m_animationDuration);

  // blend the animation cycle
  pAnimationCycle->blend(0.0f, delay);
  pAnimationCycle->checkQunlbacks(0, m_pModel);
  return true;
}

/*****************************************************************************/
/** Executes an animation action.
  *
  * This function executes an animation action.
  *
  * @param id The ID of the animation action that should be blended.
  * @param delayIn The time in seconds until the animation action reaches the
  *                full weight from the beginning of its execution.
  * @param delayOut The time in seconds in which the animation action reaches
  *                 zero weight at the end of its execution.
  * @param weightTarget The weight to interpolate the animation action to.
  * @param autoLock     This prevents the Action from being reset and removed
  *                     on the last keyframe if true.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/
bool QunMixer::executeAction(int id, float delayIn, float delayOut, float weightTarget, bool autoLock)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation;
  pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
  if(pCoreAnimation == 0)
  {
    return false;
  }

  // allocate a new animation action instance
  QunAnimationAction *pAnimationAction = new(std::nothrow) QunAnimationAction(pCoreAnimation);
  if(pAnimationAction == 0)
  {
    QunError::setLastError(QunError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return false;
  }

  // insert new animation into the table
  m_listAnimationAction.push_front(pAnimationAction);

  // execute the animation
  pAnimationAction->execute(delayIn, delayOut, weightTarget, autoLock);
  pAnimationAction->checkQunlbacks(0, m_pModel);
  return true;
}

/*****************************************************************************/
/** Clears an active animation action.
  *
  * This function removes an animation action from the blend list.  This is
  * particularly useful with auto-locked actions on their last frame.
  *
  * @param id The ID of the animation action that should be removed.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happened or action was not found
  *****************************************************************************/
bool QunMixer::removeAction(int id)
{
  // get the core animation
  QunCoreAnimation *pCoreAnimation;
  pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
  if(pCoreAnimation == 0)
  {
    return false;
  }

  // update all active animation actions of this model
  std::list<QunAnimationAction *>::iterator iteratorAnimationAction;
  iteratorAnimationAction = m_listAnimationAction.begin();

  while(iteratorAnimationAction != m_listAnimationAction.end())
  {
    // find the specified action and remove it
    if((*iteratorAnimationAction)->getCoreAnimation() == pCoreAnimation )
    {
        // found, so remove
      (*iteratorAnimationAction)->completeQunlbacks(m_pModel);
      delete (*iteratorAnimationAction);
      iteratorAnimationAction = m_listAnimationAction.erase(iteratorAnimationAction);
      return true;
    }
    iteratorAnimationAction++;
  }
  return false;
}

 /*****************************************************************************/
/** Updates all active animations.
  *
  * This function updates all active animations of the mixer instance for a
  * given amount of time.
  *
  * @param deltaTime The elapsed time in seconds since the last update.
  *****************************************************************************/

void QunMixer::updateAnimation(float deltaTime)
{
  // update the current animation time
  if(m_animationDuration == 0.0f)
  {
    m_animationTime = 0.0f;
  }
  else
  {
    m_animationTime += deltaTime * m_timeFactor;
    if(m_animationTime >= m_animationDuration || m_animationTime<0)
    {
      m_animationTime = (float) fmod(m_animationTime, m_animationDuration);
    }
	if (m_animationTime < 0)
      m_animationTime += m_animationDuration;

  }

  // update all active animation actions of this model
  std::list<QunAnimationAction *>::iterator iteratorAnimationAction;
  iteratorAnimationAction = m_listAnimationAction.begin();

  while(iteratorAnimationAction != m_listAnimationAction.end())
  {
    // update and check if animation action is still active
    if((*iteratorAnimationAction)->update(deltaTime))
    {
      (*iteratorAnimationAction)->checkQunlbacks((*iteratorAnimationAction)->getTime(),m_pModel);
      ++iteratorAnimationAction;
    }
    else
    {
      // animation action has ended, destroy and remove it from the animation list
      (*iteratorAnimationAction)->completeQunlbacks(m_pModel);
      delete (*iteratorAnimationAction);
      iteratorAnimationAction = m_listAnimationAction.erase(iteratorAnimationAction);
    }
  }

  // todo: update all active animation poses of this model

  // update the weight of all active animation cycles of this model
  std::list<QunAnimationCycle *>::iterator iteratorAnimationCycle;
  iteratorAnimationCycle = m_listAnimationCycle.begin();

  float accumulatedWeight, accumulatedDuration;
  accumulatedWeight = 0.0f;
  accumulatedDuration = 0.0f;

  while(iteratorAnimationCycle != m_listAnimationCycle.end())
  {
    // update and check if animation cycle is still active
    if((*iteratorAnimationCycle)->update(deltaTime))
    {
      // check if it is in sync. if yes, update accumulated weight and duration
      if((*iteratorAnimationCycle)->getState() == QunAnimation::STATE_SYNC)
      {
        accumulatedWeight += (*iteratorAnimationCycle)->getWeight();
        accumulatedDuration += (*iteratorAnimationCycle)->getWeight() * (*iteratorAnimationCycle)->getCoreAnimation()->getDuration();
      }

      (*iteratorAnimationCycle)->checkQunlbacks(m_animationTime,m_pModel);
      ++iteratorAnimationCycle;
    }
    else
    {
      // animation cycle has ended, destroy and remove it from the animation list
      (*iteratorAnimationCycle)->completeQunlbacks(m_pModel);
      delete (*iteratorAnimationCycle);
      iteratorAnimationCycle = m_listAnimationCycle.erase(iteratorAnimationCycle);
    }
  }

  // adjust the global animation cycle duration
  if(accumulatedWeight > 0.0f)
  {
    m_animationDuration = accumulatedDuration / accumulatedWeight;
  }
  else
  {
    m_animationDuration = 0.0f;
  }
}

void QunMixer::updateSkeleton()
{
  // get the skeleton we need to update
  QunSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  if(pSkeleton == 0) return;

  // clear the skeleton state
  pSkeleton->clearState();

  // get the bone vector of the skeleton
  std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

  // loop through all animation actions
  std::list<QunAnimationAction *>::iterator iteratorAnimationAction;
  for(iteratorAnimationAction = m_listAnimationAction.begin(); iteratorAnimationAction != m_listAnimationAction.end(); ++iteratorAnimationAction)
  {
    // get the core animation instance
    QunCoreAnimation *pCoreAnimation;
    pCoreAnimation = (*iteratorAnimationAction)->getCoreAnimation();

    // get the list of core tracks of above core animation
    std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

    // loop through all core tracks of the core animation
    std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
    for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState((*iteratorAnimationAction)->getTime(), translation, rotation);

      // blend the bone state with the new state
      pBone->blendState((*iteratorAnimationAction)->getWeight(), translation, rotation);
    }
  }

  // lock the skeleton state
  pSkeleton->lockState();

  // loop through all animation cycles
  std::list<QunAnimationCycle *>::iterator iteratorAnimationCycle;
  for(iteratorAnimationCycle = m_listAnimationCycle.begin(); iteratorAnimationCycle != m_listAnimationCycle.end(); ++iteratorAnimationCycle)
  {
    // get the core animation instance
    QunCoreAnimation *pCoreAnimation;
    pCoreAnimation = (*iteratorAnimationCycle)->getCoreAnimation();

    // calculate adjusted time
    float animationTime;
    if((*iteratorAnimationCycle)->getState() == QunAnimation::STATE_SYNC)
    {
      if(m_animationDuration == 0.0f)
      {
        animationTime = 0.0f;
      }
      else
      {
        animationTime = m_animationTime * pCoreAnimation->getDuration() / m_animationDuration;
      }
    }
    else
    {
      animationTime = (*iteratorAnimationCycle)->getTime();
    }

    // get the list of core tracks of above core animation
    std::list<QunCoreTrack *>& listCoreTrack = pCoreAnimation->getListCoreTrack();

    // loop through all core tracks of the core animation
    std::list<QunCoreTrack *>::iterator iteratorCoreTrack;
    for(iteratorCoreTrack = listCoreTrack.begin(); iteratorCoreTrack != listCoreTrack.end(); ++iteratorCoreTrack)
    {
      // get the appropriate bone of the track
      QunBone *pBone;
      pBone = vectorBone[(*iteratorCoreTrack)->getCoreBoneId()];

      // get the current translation and rotation
      QunVector translation;
      QunQuaternion rotation;
      (*iteratorCoreTrack)->getState(animationTime, translation, rotation);

      // blend the bone state with the new state
      pBone->blendState((*iteratorAnimationCycle)->getWeight(), translation, rotation);
    }
  }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

/*****************************************************************************/
/** Returns the animation time.
  *
  * This function returns the animation time of the mixer instance.
  *
  * @return The animation time in seconds.
  *****************************************************************************/

float QunMixer::getAnimationTime() const
{
	return m_animationTime;
}

/*****************************************************************************/
/** Returns the animation duration.
  *
  * This function returns the animation duration of the mixer instance.
  *
  * @return The animation duration in seconds.
  *****************************************************************************/

float QunMixer::getAnimationDuration() const
{
	return m_animationDuration;
}

/*****************************************************************************/
/** Sets the animation time.
  *
  * This function sets the animation time of the mixer instance.
  *
  *****************************************************************************/

void QunMixer::setAnimationTime(float animationTime)
{
	m_animationTime=animationTime;
}

/*****************************************************************************/
/** Set the time factor.
  * 
  * This function sets the time factor of the mixer instance.
  * this time factor affect only sync animation
  *
  *****************************************************************************/

void QunMixer::setTimeFactor(float timeFactor)
{
    m_timeFactor = timeFactor;
}

/*****************************************************************************/
/** Get the time factor.
  * 
  * This function return the time factor of the mixer instance.
  *
  *****************************************************************************/

float QunMixer::getTimeFactor() const 
{
    return m_timeFactor;
}

/*****************************************************************************/
/** Get the model.
  * 
  * This function return the QunModel of the mixer instance.
  *
  *****************************************************************************/

QunModel *QunMixer::getQunModel() 
{ 
    return m_pModel; 
} 

/*****************************************************************************/
/** Get the animation vector.
  * 
  * This function return the animation vector of the mixer instance.
  *
  *****************************************************************************/

std::vector<QunAnimation *> & QunMixer::getAnimationVector() 
{ 
    return m_vectorAnimation; 
} 

/*****************************************************************************/
/** Get the list of the action animation.
  * 
  * This function return the list of the action animation of the mixer instance.
  *
  *****************************************************************************/

std::list<QunAnimationAction *> & QunMixer::getAnimationActionList() 
{ 
    return m_listAnimationAction; 
}

/*****************************************************************************/
/** Get the list of the cycle animation.
  * 
  * This function return the list of the cycle animation of the mixer instance.
  *
  *****************************************************************************/

std::list<QunAnimationCycle *> & QunMixer::getAnimationCycle() 
{ 
    return m_listAnimationCycle; 
} 

//****************************************************************************//
