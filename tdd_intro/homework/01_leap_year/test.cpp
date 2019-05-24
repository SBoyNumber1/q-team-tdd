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

bool isLeapYear(int year)
{
    if (year % 400 == 0) {
        return true;
    }

    if (year % 100 == 0) {
        return false;
    }

    if (year % 4 == 0) {
        return true;
    }

    return false;
}

TEST(LeapYearTestCase,  DivisibleByFour)
{
    EXPECT_TRUE(isLeapYear(4));
    EXPECT_TRUE(isLeapYear(1024));
    EXPECT_TRUE(isLeapYear(1992));
    EXPECT_TRUE(isLeapYear(1996));
}

TEST(LeapYearTestCase,  DivisibleByHundred)
{
    EXPECT_FALSE(isLeapYear(100));
    EXPECT_FALSE(isLeapYear(1900));
    EXPECT_FALSE(isLeapYear(-1400));
}

TEST(LeapYearTestCase,  DivisibleByFourHundred)
{
    EXPECT_TRUE(isLeapYear(2000));
    EXPECT_TRUE(isLeapYear(400));
    EXPECT_TRUE(isLeapYear(-1600));
}
