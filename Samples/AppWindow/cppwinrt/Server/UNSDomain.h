/*

    UNSDomain.h - Domains
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_DOMAIN_H
#define UNS_DOMAIN_H

#if defined(WIN32)
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#endif

#include "UNSEntity.h"

#include "Thread.h"

#define UNS_DOMAIN_DEFAULT_X 175
#define UNS_DOMAIN_DEFAULT_Y -355
#define UNS_DOMAIN_DEFAULT_Z 0

#define UNS_DOMAIN_DEFAULT_RANGE 1000
#define UNS_DOMAIN_GRANULARITY 0.00135

#define UNS_DOMAIN_REFRESH 17

typedef struct RadMeasure
{
	QpoVec3d m_Pos;
	float m_Range;
} RadMeasure;

typedef struct BoundsMeasure
{
	float m_x;
	float m_y;
	float m_z;
} BoundsMeasure;

typedef struct unTimingEntry
{
	unsigned int m_TickStamp;
	unsigned int m_Index;
} unTimingEntry;

class unAvatarList
{
public:
	unAvatarList() {};
	unAvatarList(unsigned short i_SysIndex)
		{ m_SysIndex = i_SysIndex; };
	~unAvatarList() {};

	int acPushAvatar(int i_Index)
		{
		for(int i_IndexID; i_IndexID < vec_Index.size(); i_IndexID++)
			{
			if(i_Index == vec_Index[i_IndexID])
				{
				return i_IndexID;
				}
			}

		vec_Index.push_back(i_Index);
		}

	bool acFindAvatar(int i_Index)
		{
		for(int i_IndexID; i_IndexID < vec_Index.size(); i_IndexID++)
			{
			if(i_Index == vec_Index[i_IndexID])
				{
				return true;
				}
			}
		return false;
		}

	std::vector<unsigned int> vec_TickStamp;
	std::vector<unsigned int> vec_Index;

	unsigned short m_SysIndex;
};

typedef struct vec_swing_Timing
{
	std::vector<unTimingEntry> m_mars;
	std::vector<unTimingEntry> m_venus;
} vec_swing_Timing;

typedef struct unDomainAddress
{
	unsigned int m_DomainID;
	unsigned int m_ClientID;
} unDomainAddress;

class unRefreshList
{
public:
	unRefreshList() {};
	unRefreshList(unAvatarList* i_List)
		{ m_List = i_List; };

	~unRefreshList() {};

	int acPushAvatar(int i_Index)
		{
		for(int i_IndexID; i_IndexID < vec_AvatarIndex.size(); i_IndexID++)
			{
			if(i_Index == vec_AvatarIndex[i_IndexID])
				{
				return i_IndexID;
				}
			}

		vec_AvatarIndex.push_back(i_Index);
		}

	bool acFindAvatar(int i_Index)
		{
		for(int i_IndexID; i_IndexID < vec_AvatarIndex.size(); i_IndexID++)
			{
			if(i_Index == vec_AvatarIndex[i_IndexID])
				{
				return true;
				}
			}
		return false;
		}

	unsigned short m_SysAddress;
	std::vector<int> vec_AvatarIndex;
	unAvatarList* m_List;

};

#include "UNSDomainStack.h"

class unDomainRadial : public CThread
{
public:
	unDomainRadial(void* pOwnerObject = NULL, icThreadData *pData = 0);

	unDomainRadial(std::vector<unEntAvatar*>* i_vec_entity_Avatar,
		std::vector<unsigned short>* i_vec_entity_SysIndex,
		//*std::vector<SystemAddress*>* i_vec_entity_SysAddress,
		std::vector<unAvatarList*>* i_vec_avatar_Ident,
		std::vector<unRefreshList*>* i_vec_RefreshList,
		SDL_mutex *i_mutex_Dom_Avatar,
		SDL_mutex *i_mutex_Dom_Refresh,
		SDL_mutex *i_mutex_Dom_System,
		unMutexCC* i_mutexcc_Avatar,
		unMutexCC* i_mutexcc_AvatarId,
		unMutexCC* i_mutexcc_Refresh,
		void* pOwnerObject = NULL, icThreadData *pData = 0);

	virtual ~unDomainRadial();

	void acGenStacks(void);

	void Initialize(void);
	void Run(void);

	void acScan(void);
	int acFind(unsigned short i_SysAddress);

	void acAvatarStartClient(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex, int i_BDATID, int CDATID);
	void acAvatarStart(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex, int i_BDATID, int CDATID);

	bool acAvatarShutdownClient(unsigned short i_SysIndex);
	bool acAvatarShutdown(unsigned short i_SysIndex);

public:
	RadMeasure m_Measure;
	std::vector<unEntAvatar*>* vec_entity_Avatar;
	std::vector<unsigned short>* vec_entity_SysIndex;
	//*std::vector<SystemAddress*>* vec_entity_SysAddress;

	std::vector<unAvatarList*>* vec_avatar_Ident;
	std::vector<unRefreshList*>* vec_RefreshList;

	std::vector<unDomainStack*> vec_DomainStack;
	
	SDL_mutex* m_mutex_Dom_Avatar;
	SDL_mutex* m_mutex_Dom_Refresh;
	SDL_mutex* m_mutex_Dom_System;

	unMutexCC* m_mutexcc_Avatar;

	unMutexCC* m_mutexcc_AvatarId;
	unMutexCC* m_mutexcc_Refresh;

	vec_swing_Timing vec_swing_TimeSheet;

	int *m_RefreshCount;

protected:
	unsigned int m_TimeStart;
	unsigned int m_TimeEnd;

	unsigned int m_Tick;
	unsigned int m_LastTick;
	float m_ElapsedSeconds;
	float m_Distance;

	int m_ListID;
	int m_AVID;
	int m_count;
	int m_ListCount;

	int PP_STATE;

	int m_VectorAvatarID;
	int m_SwingIndex;

	unTimingEntry m_IdentList;

	unAvatarList* m_vec_IdentList;
	unRefreshList* m_RefreshList;

	virtual	int ThreadHandler();
};

#endif