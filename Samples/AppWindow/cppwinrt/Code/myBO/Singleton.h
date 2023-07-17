#pragma once

#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>
#include <stdlib.h>

template <typename T> 
class unSingleton
{
public:
	static T* Instance()
	{
		if (m_instance == NULL) m_instance = new T;
		//ASSERT(m_instance != NULL);
		//assert(m_instance != NULL);
		return m_instance;
	};
	static void DestroyInstance()
	{
		delete m_instance;
		m_instance = NULL;
	};

protected:
	unSingleton() {};
    virtual ~unSingleton() {};

private:
    unSingleton(const unSingleton& source){};
    static T* m_instance;
};
template <typename T> T* unSingleton<T>::m_instance = NULL;

/*
#include "Singleton.h"

class CMySingleton : public Singleton<CMySingleton>
{
    friend Singleton<CMySingleton>;   
 
       private:      

           CMySingleton();
           ~CMySingleton();
 
    ...
}
#define sSingleton CMySingleton::Instance()

// CMySingleton.cpp
CMySingleton* mySingleton = CMySingleton::Instance();
*/
#endif