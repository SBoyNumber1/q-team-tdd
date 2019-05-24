/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>
#include <exception>

bool isLeapYear(int year)
{
    if (0 == year)
    {
        throw std::invalid_argument("Year can't be 0");
    }

    if (0 == year % 400 || (0 != year % 100 && 0 == year % 4))
    {
        return true;
    }

    return false;
}

TEST(LeapYearTestCase, DivisibleByFour)
{
    EXPECT_TRUE(isLeapYear(4));
    EXPECT_TRUE(isLeapYear(1024));
    EXPECT_TRUE(isLeapYear(1992));
    EXPECT_TRUE(isLeapYear(1996));
}

TEST(LeapYearTestCase, DivisibleByHundred)
{
    EXPECT_FALSE(isLeapYear(100));
    EXPECT_FALSE(isLeapYear(1900));
    EXPECT_FALSE(isLeapYear(-1400));
}

TEST(LeapYearTestCase, DivisibleByFourHundred)
{
    EXPECT_TRUE(isLeapYear(2000));
    EXPECT_TRUE(isLeapYear(400));
    EXPECT_TRUE(isLeapYear(-1600));
}

TEST(LeapYearTestCase, NotLeapYear)
{
    EXPECT_FALSE(isLeapYear(1997));
    EXPECT_FALSE(isLeapYear(1));
    EXPECT_FALSE(isLeapYear(1700));
    EXPECT_FALSE(isLeapYear(-1401));
}

TEST(LeapYearTestCase, ZeroYearDoesNotExist)
{
    EXPECT_THROW(isLeapYear(0), std::invalid_argument);
}

