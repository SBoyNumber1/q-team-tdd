/*
Timer
Implement a timer class that implements the interface ITimer which is defined below.
Follow this specification:

Timer allows to determine if specific period of time expired or not since Start was called last time
Timer allows to determine how much time left till period is expired
Timer can be started again any time, no metter in what state it is
*/

#include <gtest/gtest.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef std::chrono::time_point<Clock> TimePoint;

class ITimer {
public:
  virtual ~ITimer() {}

  virtual void Start() = 0;
  virtual bool IsExpired() const = 0;
  virtual Duration TimeLeft() const = 0;
};

class Timer: public ITimer
{
public:
    Timer();

    virtual void Start() = 0;
    virtual bool IsExpired() const = 0;
    virtual Duration TimeLeft() const = 0;
};
