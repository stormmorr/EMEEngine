//****************************************************************************//
// coreanimation.cpp                                                          //
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

#include "cal3d/coreanimation.h"
#include "cal3d/coretrack.h"

UN_CoreAnimation::UN_CoreAnimation()
{
}


UN_CoreAnimation::~UN_CoreAnimation()
{
    ip::list<UN_CoreTrack, Alloc_CoreTrack>::iterator iteratorCoreTrack;
    for (iteratorCoreTrack = (*m_listCoreTrack).begin(); iteratorCoreTrack != (*m_listCoreTrack).end(); ++iteratorCoreTrack)
    {
        UN_CoreTrack pTrack = *iteratorCoreTrack;
        pTrack.destroy();
        //delete pTrack;
    }
}

/*****************************************************************************/
/** Adds a core track.
  *
  * This function adds a core track to the core animation instance.
  *
  * @param pCoreTrack A pointer to the core track that should be added.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool UN_CoreAnimation::addCoreTrack(UN_CoreTrack pCoreTrack)
{
  (*m_listCoreTrack).push_back(pCoreTrack);

  return true;
}

 /*****************************************************************************/
/** Provides access to a core track.
  *
  * This function returns the core track for a given bone ID.
  *
  * @param coreBoneId The core bone ID of the core track that should be
  *                   returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core track
  *         \li \b 0 if an error happend
  *****************************************************************************/

UN_CoreTrack UN_CoreAnimation::getCoreTrack(int coreBoneId)
{
  // loop through all core track
  UN_List_CoreTrack::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = (*m_listCoreTrack).begin(); iteratorCoreTrack != (*m_listCoreTrack).end(); ++iteratorCoreTrack)
  {
    // get the core bone
    UN_CoreTrack pCoreTrack;
    pCoreTrack = *iteratorCoreTrack;

    // check if we found the matching core bone
    if(pCoreTrack.getCoreBoneId() == coreBoneId) return pCoreTrack;
  }

  // no match found
  for(;;) { printf("ERROR:::Cal3d coulkd not find track\n"); }
}

/*****************************************************************************/
/** Gets the number of core tracks for this core animation.
  *
  * This function returns the number of core tracks used for this core animation.
  *
  * @return The number of core tracks
  *****************************************************************************/

unsigned int UN_CoreAnimation::getTrackCount() const
{
	return (*m_listCoreTrack).size();
}

 /*****************************************************************************/
/** Returns the duration.
  *
  * This function returns the duration of the core animation instance.
  *
  * @return The duration in seconds.
  *****************************************************************************/

float UN_CoreAnimation::getDuration() const
{
  return m_duration;
}

 /*****************************************************************************/
/** Sets the duration.
  *
  * This function sets the duration of the core animation instance.
  *
  * @param duration The duration in seconds that should be set.
  *****************************************************************************/

void UN_CoreAnimation::setDuration(float duration)
{
  m_duration = duration;
}

 /*****************************************************************************/
/** Scale the core animation.
  *
  * This function rescale all the skeleton data that are in the core animation instance
  *
  * @param factor A float with the scale factor
  *
  *****************************************************************************/

void UN_CoreAnimation::scale(float factor)
{
  // loop through all core track
  UN_List_CoreTrack::iterator iteratorCoreTrack;
  for(iteratorCoreTrack = (*m_listCoreTrack).begin(); iteratorCoreTrack != (*m_listCoreTrack).end(); ++iteratorCoreTrack)
  {
	  (*iteratorCoreTrack).scale(factor);
  }
}

 /*****************************************************************************/
/** 
  * Set the name of the file in which the core animation is stored, if any.
  *
  * @param filename The path of the file.
  *****************************************************************************/

void UN_CoreAnimation::setFilename(const std::string& filename)
{
  m_filename = filename;
}

 /*****************************************************************************/
/** 
  * Get the name of the file in which the core animation is stored, if any.
  *
  * @return One of the following values:
  *         \li \b empty string if the animation was not stored in a file
  *         \li \b the path of the file
  *
  *****************************************************************************/

const std::string& UN_CoreAnimation::getFilename(void) const
{
  return m_filename;
}

 /*****************************************************************************/
/** 
  * Set the symbolic name of the core animation.
  *
  * @param name A symbolic name.
  *****************************************************************************/

void UN_CoreAnimation::setName(const std::string& name)
{
  m_name = name;
}

 /*****************************************************************************/
/** 
  * Get the symbolic name the core animation.
  *
  * @return One of the following values:
  *         \li \b empty string if the animation was no associated to a symbolic name
  *         \li \b the symbolic name
  *
  *****************************************************************************/

const std::string& UN_CoreAnimation::getName(void) const
{
  return m_name;
}

/*****************************************************************************/
/** 
  * Add a callback to the current list of callbacks for this CoreAnim.
  *
  * @param  callback     Ptr to a subclass of this abstract class implementing the callback function.
  * @param  min_interval Minimum interval (in seconds) between callbacks.  Specifying 0 means call every update().
  *
  *****************************************************************************/

void UN_CoreAnimation::registerCallback(CalAnimationCallback *callback,float min_interval)
{
  CallbackRecord record;
  record.callback     = callback;
  record.min_interval = min_interval;

  m_listCallbacks.push_back(record);
}

/*****************************************************************************/
/** 
  * Remove a callback from the current list of callbacks for this Anim.
  * Callback objects not removed this way will be deleted in the dtor of the Anim.
  *
  * @param  callback     Ptr to a subclass of this abstract class implementing the callback function to remove.
  *
  *****************************************************************************/

void UN_CoreAnimation::removeCallback(CalAnimationCallback *callback)
{
  for (std::vector<CallbackRecord>::iterator i = m_listCallbacks.begin(); i != m_listCallbacks.end(); i++)
  {
    if ((*i).callback == callback)
    {
      m_listCallbacks.erase(i);
      return;
    }
  }
}

/*****************************************************************************/
/** Returns the core track list.
  *
  * This function returns the list that contains all core tracks of the core
  * animation instance.
  *
  * @return A reference to the core track list.
  *****************************************************************************/

UN_List_CoreTrack *UN_CoreAnimation::getListCoreTrack()
{
  return m_listCoreTrack;
}

/*****************************************************************************/
/** Returns the total number of core keyframes used for this animation.
  *
  * This function returns the total number of core keyframes used for this
  * animation instance (i.e.: the sum of all core keyframes of all core tracks).
  *
  * @return A reference to the core track list.
  *****************************************************************************/

unsigned int UN_CoreAnimation::getTotalNumberOfKeyframes() const
{
	unsigned int nbKeys = 0;
	for (UN_List_CoreTrack::const_iterator it = (*m_listCoreTrack).begin(); it != (*m_listCoreTrack).end(); ++it)
	{
		UN_CoreTrack track = *it;
		nbKeys += track.getCoreKeyframeCount();
	}
	return nbKeys;
}

