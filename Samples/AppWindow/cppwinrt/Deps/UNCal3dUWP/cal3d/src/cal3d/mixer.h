//****************************************************************************//
// mixer.h                                                                    //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
// Copyright (C) 2004 Mekensleep <licensing@mekensleep.com>                   //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_MIXER_H
#define CAL_MIXER_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"

#if 1
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"
#endif

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class QunModel;
class QunAnimation;
class QunAnimationAction;
class QunAnimationCycle;

typedef struct RagSheet
{
	QunQuaternion *Quat[55];
	QunVector *Vector[55];
} RagSheet;

/*****************************************************************************/
/** 
 * QunAbstractMixer defines the API that QunModel relies on for
 * blending and scheduling animations. A third party mixer must
 * implement this API in order to register itself with the
 * QunModel::setAbstractMixer method. The default mixer (QunMixer) is
 * an example of such implementation.
 *
 * cal3d expects a mixer to handle two tasks : scheduling and
 * blending. Scheduling refers to everything related to time such
 * as when an animation must run or when it must stop. Blending
 * defines how concurrent animations influence each other: for 
 * instance walking and waving.
 *
 * If QunMixer proves to be insufficient for the applications needs,
 * an alternate mixer can be implemented and used without notifying
 * cal3d in any way. It is not mandatory to subclass
 * QunAbstractMixer. However, when chosing this path, one must also
 * avoid using the QunModel::update method because it would use the
 * default mixer instantiated by the QunModel::create method with
 * undesirable side effects. In addition libraries based on cal3d
 * (think NebulaDevice or OpenSceneGraph adapters) are not aware of
 * these constraints and will keep calling the QunModel::update method of
 * QunModel regardless.
 *
 * Subclassing QunAbstractMixer when implementing an alternate mixer
 * therefore provides a better integration with cal3d and libraries
 * that rely on QunModel. However, an additional effort is required in
 * order to achieve compatibility with libraries or applications that
 * rely on the QunMixer API (i.e. that use methods such as blendCycle
 * or executeAction).  The QunMixer API is not meant to be generic and
 * there is no reason to define an abstract class that specifies
 * it. For historical reasons and because QunMixer is the default
 * mixer, some applications and libraries (think Soya or CrystalSpace)
 * depend on it. If they want to switch to a scheduler with extended
 * capabilities it might be painfull for them to learn a completely
 * different API. A scheduler with the ambition to obsolete QunMixer
 * should therefore provide an API compatible with it to ease the
 * migration process.
 *
 * Short summary, if you want to write a new mixer:
 *
 * 1) An external mixer: ignore QunAbstractMixer and implement a mixer
 * of your own. Avoid calling QunModel::update and any library or
 * application that will call it behind your back. Avoid libraries and
 * applications that rely on the default mixer QunMixer, as returned
 * by QunModel::getMixer.
 *
 * 2) A mixer registered in cal3d : subclass QunAbstractMixer,
 * register it with QunModel::setAbstractMixer.  Avoid libraries and
 * applications that rely on the default mixer QunMixer, as returned
 * by QunModel::getMixer. QunModel::getMixer will return a null
 * pointer if QunModel::setAbstractMixer was called to set
 * a mixer that is not an instance of QunMixer.
 *
 * 3) A QunMixer replacement : same as 2) and provide a subclass of
 * your own mixer that implements the QunMixer API so that existing
 * applications can switch to it by calling QunModel::getAbstractMixer
 * instead of QunModel::getMixer. The existing code using the QunMixer
 * methods will keep working and the developper will be able to 
 * switch to a new API when convenient.
 *
 *****************************************************************************/

class CAL3D_API QunAbstractMixer
{
public:
  QunAbstractMixer() {}
  virtual ~QunAbstractMixer() {}

  /*****************************************************************************/
  /**
   * Is the object an instance of the default mixer (i.e. an instance of QunMixer) ?
   *
   * @return \li \b true if an instance of QunMixer
   *         \li \b false if not an instance of QunMixer
   *
   *****************************************************************************/
  virtual bool isDefaultMixer() const { return false; }

  /*****************************************************************************/
  /** 
   * Notifies the instance that updateAnimation was last called
   * deltaTime seconds ago. The internal scheduler of the instance
   * should terminate animations or update the timing information of
   * active animations accordingly. It should not blend animations
   * together or otherwise modify the QunModel associated to these
   * animations.
   *
   * The QunModel::update method will call updateSkeleton immediately
   * after updateAnimation if the instance was allocated by
   * QunModel::create (in which case it is a QunMixer instance) or if
   * the instance was set via QunModel::setAbstractMixer.
   *
   * @param deltaTime The elapsed time in seconds since the last call.
   *
   *****************************************************************************/
  virtual void updateAnimation(float deltaTime) = 0;

  /*****************************************************************************/
  /**
   * Updates the skeleton of the corresponding QunModel (as provided to
   * the create method) to match the current animation state (as
   * updated by the last call to updateAnimation).  The tracks of each
   * active animation are blended to compute the position and
   * orientation of each bone of the skeleton. The updateAnimation
   * method should be called just before calling updateSkeleton to
   * define the set of active animations.
   *
   * The QunModel::update method will call updateSkeleton immediately
   * after updateAnimation if the instance was allocated by
   * QunModel::create (in which case it is a QunMixer instance) or if
   * the instance was set via QunModel::setAbstractMixer.
   *
   *****************************************************************************/
  virtual void updateSkeleton() = 0;
};


class CAL3D_API QunMixer : public QunAbstractMixer
{
public:
  QunMixer(QunModel* pModel);
  virtual ~QunMixer();

  virtual bool isDefaultMixer() const { return true; }
  void BeginAnim(void);
  void EndAnim(void);
  void BlendAnim(int i_motion, float i_time, float i_blendamount);
  void BlendAnimMin(int i_motion, float i_time, float i_blendamount);
  void BlendAnimTorque(int i_motion, float i_time, float i_blendamount, int i_Level);
  void BlendAnimPhysics(int i_motion, float i_time, float i_blendamount);
  void ApplyAnim(int i_motion, float i_time, float i_blendamount);
  void ClearAnim(void);
  void AnimateLeftLeg(int i_motion, float i_time, float i_blendamount);
  void AnimateRightLeg(int i_motion, float i_time, float i_blendamount);
  void AnimateLeftArm(int i_motion, float i_time, float i_blendamount);
  void AnimateRightArm(int i_motion, float i_time, float i_blendamount);
  void AnimatePivot(int i_motion, float i_time, float i_blendamount);
  bool blendCycle(int id, float weight, float delay);
  bool clearCycle(int id, float delay);
  bool executeAction(int id, float delayIn, float delayOut, float weightTarget = 1.0f, bool autoLock=false);
  bool removeAction(int id);
  virtual void updateAnimation(float deltaTime);
  virtual void updateSkeleton();
  float getAnimationTime() const;
  float getAnimationDuration() const;
  void setAnimationTime(float animationTime);
  void setTimeFactor(float timeFactor);
  float getTimeFactor() const;
  QunModel *getQunModel();  
  std::vector<QunAnimation *> &getAnimationVector();
  std::list<QunAnimationAction *> &getAnimationActionList();
  std::list<QunAnimationCycle *> &getAnimationCycle();
  RagSheet *m_RagSheet;
  
protected:
  QunModel *m_pModel;
  std::vector<QunAnimation *> m_vectorAnimation;
  std::list<QunAnimationAction *> m_listAnimationAction;
  std::list<QunAnimationCycle *> m_listAnimationCycle;
  float m_animationTime;
  float m_animationDuration;
  float m_timeFactor;
};

#endif

//****************************************************************************//
