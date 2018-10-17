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
 *
 * Steps:
 * Implement Start with no check
 * Check IsExpired when is not started
 * Check IsExpired when duration is 0 and started
 * Check IsExpired when duration is not 0 and started
 * Check TimeLeft when not started (expected: 0)
 * Check TimeLeft within the given duration and timer is started
 * Check IsExpired within the given duration and timer is started
 * Check TimeLeft when is expired (expected: 0)
 * Check IsExpired when no time left
 * Check the starting of timer when it is already started
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

class ITime
{
public:
    virtual ~ITime() { }

    virtual TimePoint GetCurrent() = 0;
};

class Timer: public ITimer
{
public:
    Timer(ITime& time, Duration duration)
        : m_time(time), m_duration(duration)
    { }

    virtual void Start() override
    { }

    virtual bool IsExpired() const override
    { return true; }

    virtual Duration TimeLeft() const override
    { return { }; }

private:
    ITime& m_time;
    Duration m_duration;
};

class FakeTime: public ITime
{
public:
    virtual TimePoint GetCurrent() { return { }; }
};

TEST(Timer, StartNoCheck)
{
    FakeTime time;
    Timer timer(time, seconds(0));
    timer.Start();
}

TEST(Timer, IsExpired_NotStarted)
{
    FakeTime time;
    Timer timer(time, seconds(0));
    ASSERT_TRUE(timer.IsExpired());
}

TEST(Timer, IsExpired_0AndStarted)
{
    FakeTime time;
    Timer timer(time, seconds(0));
    timer.Start();
    ASSERT_TRUE(timer.IsExpired());
}

TEST(Timer, IsExpired_Not0AndStarted)
{
    FakeTime time;
    Timer timer(time, seconds(1));
    timer.Start();
    ASSERT_FALSE(timer.IsExpired());
}
