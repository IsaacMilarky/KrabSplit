#include <boost/thread/pthread/mutex.hpp>
#include <iostream>
#include <chrono>
#include <boost/thread.hpp>
#include <unistd.h>

class SplitTimerCounter 
{
    //Mutex for writing to the values.
    boost::mutex mtx_;
    unsigned long int minutes_;
    unsigned short seconds_;

    public:
        SplitTimerCounter();

        void tick();

        unsigned short readSeconds();;
        unsigned long int readMinutes();;
        
};