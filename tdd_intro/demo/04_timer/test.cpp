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
 * Check IsExpired within the given duration and timer is started:
 *  immediatly
 *  after some waiting
 * Check TimeLeft when is expired (expected: 0)
 * Check IsExpired when no time left
 * Check IsExpired when time is left
 * Check the starting of timer when it is already started
*/

#include <gtest/gtest.h>
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef time_point<Clock> TimePoint;
static const Duration s_zeroDuration(microseconds(0));

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
        : m_time(time), m_duration(duration), m_started(false)
    { }

    virtual void Start() override
    {
        m_started = true;
        m_startTime = m_time.GetCurrent();
    }

    virtual bool IsExpired() const override
    {
        return TimeElapsed() >= m_duration;
    }

    virtual Duration TimeLeft() const override
    {
        if (m_started && !IsExpired())
        {
            return m_duration - TimeElapsed();
        }
        return s_zeroDuration;
    }

private:
    Duration TimeElapsed() const
    {
        if (m_started)
        {
            return m_time.GetCurrent() - m_startTime;
        }
        return s_zeroDuration;
    }

private:
    ITime& m_time;
    Duration m_duration;
    bool m_started;
    TimePoint m_startTime;
};

class FakeTime: public ITime
{
public:
    virtual TimePoint GetCurrent() { return m_current; }

    void Wait(Duration duration) { m_current += duration; }

private:
    TimePoint m_current;
};

TEST(Timer, StartNoCheck)
{
    FakeTime time;
    Timer timer(time, s_zeroDuration);
    timer.Start();
}

TEST(Timer, IsExpired_NotStarted)
{
    FakeTime time;
    Timer timer(time, s_zeroDuration);
    ASSERT_TRUE(timer.IsExpired());
}

TEST(Timer, IsExpired_0AndStarted)
{
    FakeTime time;
    Timer timer(time, s_zeroDuration);
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

TEST(Timer, TimeLeft_NotStarted)
{
    FakeTime time;
    Timer timer(time, seconds(1));
    ASSERT_EQ(seconds(0), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Started)
{
    FakeTime time;
    Timer timer(time, seconds(1));
    timer.Start();
    ASSERT_EQ(seconds(1), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Started2)
{
    FakeTime time;
    Timer timer(time, seconds(2));
    timer.Start();
    ASSERT_EQ(seconds(2), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Started_AfterWaiting)
{
    FakeTime time;
    Timer timer(time, seconds(2));
    timer.Start();
    time.Wait(seconds(1));
    ASSERT_EQ(seconds(1), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Started_AfterWaiting2)
{
    FakeTime time;
    Timer timer(time, seconds(10));
    timer.Start();
    time.Wait(seconds(3));
    ASSERT_EQ(seconds(7), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Wait_Started_AfterWaiting)
{
    FakeTime time;
    time.Wait(seconds(5));
    Timer timer(time, seconds(10));
    timer.Start();
    time.Wait(seconds(3));
    ASSERT_EQ(seconds(7), timer.TimeLeft());
}

TEST(Timer, TimeLeft_Expired)
{
    FakeTime time;
    time.Wait(seconds(2));
    Timer timer(time, seconds(4));
    timer.Start();
    time.Wait(seconds(6));
    ASSERT_EQ(seconds(0), timer.TimeLeft());
}

TEST(Timer, IsExpired_NoTimeLeft)
{
    FakeTime time;
    time.Wait(seconds(2));
    Timer timer(time, seconds(3));
    timer.Start();
    time.Wait(seconds(6));
    ASSERT_TRUE(timer.IsExpired());
}

TEST(Timer, IsExpired_TimeIsLeft)
{
    FakeTime time;
    time.Wait(seconds(2));
    Timer timer(time, seconds(5));
    timer.Start();
    time.Wait(seconds(2));
    ASSERT_FALSE(timer.IsExpired());
}

TEST(Timer, IsExpired_TimeLeaft_AfterTimerRestart)
{
    FakeTime time;
    time.Wait(seconds(1));
    Timer timer(time, seconds(5));
    timer.Start();
    time.Wait(seconds(2));
    ASSERT_EQ(seconds(3), timer.TimeLeft());

    // Restarting the timer
    timer.Start();
    ASSERT_EQ(seconds(5), timer.TimeLeft());
}

