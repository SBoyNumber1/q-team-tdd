/*
Timer
Implement a timer class that implements the interface ITimer which is defined below.
Follow this specification:

Timer allows to determine if specific period of time expired or not since Start was called last time
Timer allows to determine how much time left till period is expired
Timer can be started again any time, no metter in what state it is
*/

/*
 * Architecture:
 * Timer gets interface ITime with such functionality:
 *   get current time point
 * Timer gets desired duration and compares it with current time from ITime
 *
 * Desired behavior:
 * IsExpired returns true if is not started
 * Timeleft returns 0 if is not started or expired
*/

#include <gtest/gtest.h>
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef time_point<Clock> TimePoint;

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
    virtual void Start() override;
    virtual bool IsExpired() const override;
    virtual Duration TimeLeft() const override;
};
