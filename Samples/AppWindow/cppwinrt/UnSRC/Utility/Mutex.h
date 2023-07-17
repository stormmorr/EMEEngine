#ifndef __TTO_Util_Mutex_h__
#define __TTO_Util_Mutex_h__

#include <cassert>
#include "SDL_mutex.h"

class Mutex
{
public:
    Mutex() :
        mutex(0)
    {
        mutex = SDL_CreateMutex();
        assert(mutex != 0);
    }
    ~Mutex()
    {
        SDL_DestroyMutex(mutex);
    }
    void lock()
    {
        SDL_LockMutex(mutex);
    }
    void unlock()
    {
        SDL_UnlockMutex(mutex);
    }
private:
    SDL_mutex* mutex;
};

#endif
