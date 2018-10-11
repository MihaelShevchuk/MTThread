//
//  MTThread.hpp
//  MTAudioController
//
//  Created by MihailShevchuk on 8/20/18.
//  Copyright © 2018 Mihail Shevchuk. All rights reserved.
//

#ifndef MTThread_hpp
#define MTThread_hpp

#include <stdio.h>
#include <pthread.h>

class MTThread {
public:
    MTThread() {}
    virtual ~MTThread() {}
    
    /*! Returns true if the thread was successfully started, false if there was an error starting the thread */
    bool StartThread() { return (pthread_create(&mThread, NULL, ThreadEntryFunc, this) == 0); }
    
    /*! Will not return until the internal thread has exited. */
    void WaitForThreadToExit() { (void) pthread_join(mThread, NULL); }
    
protected:
    /*! Implement this method in your subclass with the code you want your thread to run. */
    virtual void ThreadEntry() = 0;
    
private:
    static void* ThreadEntryFunc(void* object) {
        ((MTThread*)object)->ThreadEntry();
        return NULL;
    }
    
    pthread_t mThread;
};

#endif /* MTThread_hpp */
