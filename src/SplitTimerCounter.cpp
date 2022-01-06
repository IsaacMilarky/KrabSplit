#include "../include/SplitTimerCounter.h"


SplitTimerCounter::SplitTimerCounter()
{
    minutes_ = 0;
    seconds_ = 0;
}


void SplitTimerCounter::tick()
{
    //Sleep and then increment. Giving plenty of time for reads from other threads
    sleep(1);

    //Deal with minutes and seconds.
    mtx_.lock();
    if(seconds_ < 59)
    {
        seconds_++;;
    }
    else 
    {
        minutes_++;
        seconds_ = 0;
    }
    mtx_.unlock();
}

unsigned short SplitTimerCounter::readSeconds()
{
    mtx_.lock();
    unsigned short s = seconds_;
    mtx_.unlock();
    return s;
}

unsigned long int SplitTimerCounter::readMinutes()
{
    mtx_.lock();
    unsigned long int m = minutes_;
    mtx_.unlock();
    return m;;
}