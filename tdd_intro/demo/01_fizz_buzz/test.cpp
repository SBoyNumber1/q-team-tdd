#include <gtest/gtest.h>
#include <sstream>
#include <string>

// 3 = Fizz
// 5 = Buzz
// 15 = FizzBuzz

std::string fizzStr = "FIZZ";
std::string buzzStr = "BUZZ";

std::string FizzBuzz(unsigned short num)
{
    std::string result;

    if(num == 0 || num > 100)
    {
        return result;
    }

    if (num % 3 == 0)
    {
        result += fizzStr;
    }
    if (num % 5 == 0)
    {
        result += buzzStr;
    }

    return result.empty() ? std::to_string(num) : result;
}

TEST(FizzBuzz,FizzBuzz_Input1_Retuns_1)
{
    EXPECT_EQ("1", FizzBuzz(1));
}

TEST(FizzBuzz,FizzBuzz_Input3_Retuns_FIZZ)
{
    EXPECT_EQ("FIZZ", FizzBuzz(3));
}

TEST(FizzBuzz,FizzBuzz_Input6_Retuns_FIZZ)
{
    EXPECT_EQ("FIZZ", FizzBuzz(6));
}

TEST(FizzBuzz,FizzBuzz_Input5_Prints_BUZZ)
{
    EXPECT_EQ("BUZZ", FizzBuzz(5));
}

TEST(FizzBuzz,FizzBuzz_Input66_Prints_FIZZ)
{
    EXPECT_EQ("FIZZ", FizzBuzz(66));
}

TEST(FizzBuzz,FizzBuzz_Input55_Prints_BUZZ)
{
    EXPECT_EQ("BUZZ", FizzBuzz(55));
}

TEST(FizzBuzz,FizzBuzz_Input15_Prints_FIZZBUZZ)
{
    EXPECT_EQ("FIZZBUZZ", FizzBuzz(15));
}

TEST(FizzBuzz,FizzBuzz_Input30_Prints_FIZZBUZZ)
{
    EXPECT_EQ("FIZZBUZZ", FizzBuzz(30));
}

TEST(FizzBuzz,FizzBuzz_Input_0_Prints_Nothing)
{
    EXPECT_EQ("", FizzBuzz(0));
}
TEST(FizzBuzz,FizzBuzz_Input_101_Prints_Nothing)
{
    EXPECT_EQ("", FizzBuzz(101));
}

TEST(FizzBuzz,FizzBuzz_Input_200_Prints_Nothing)
{
    EXPECT_EQ("", FizzBuzz(200));
}