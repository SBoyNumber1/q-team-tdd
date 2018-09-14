#include <gtest/gtest.h>
#include <string>

/*
 * The program should answer "Fizz" if the input number is multiple of 3, Buzz - if you specify a number which is multiple of 5,
 * and FizzBuzz - if the number is a multiple of 3 and 5. In other cases the program should not answer. So, the conditions are:
 * a multiple of 3 = Fizz
 * a multiple of 5 = Buzz
 * a multiple of 15 = FizzBuzz
 * any other number = <nothing>
*/

std::string FizzBuzz(size_t number)
{
    std::string answer;
    if (number % 3 == 0)
    {
        answer += "Fizz";
    }
    if (number % 5 == 0)
    {
        answer += "Buzz";
    }
    return answer;
}

TEST(FizzBuzzTest, Fizz)
{
    EXPECT_STREQ("Fizz", FizzBuzz(3).c_str());
}

TEST(FizzBuzzTest, Buzz)
{
    EXPECT_STREQ("Buzz", FizzBuzz(5).c_str());
}

TEST(FizzBuzzTest, Empty)
{
    EXPECT_STREQ("", FizzBuzz(1).c_str());
}

TEST(FizzBuzzTest, FizzBuzz)
{
    EXPECT_STREQ("FizzBuzz", FizzBuzz(15).c_str());
}

TEST(FizzBuzzTest, Acceptance)
{
    EXPECT_STREQ("", FizzBuzz(2).c_str());
    EXPECT_STREQ("", FizzBuzz(71).c_str());
    EXPECT_STREQ("", FizzBuzz(1111).c_str());

    EXPECT_STREQ("Fizz", FizzBuzz(6).c_str());
    EXPECT_STREQ("Fizz", FizzBuzz(99).c_str());
    EXPECT_STREQ("Fizz", FizzBuzz(363).c_str());

    EXPECT_STREQ("FizzBuzz", FizzBuzz(30).c_str());
    EXPECT_STREQ("FizzBuzz", FizzBuzz(120).c_str());
    EXPECT_STREQ("FizzBuzz", FizzBuzz(3300).c_str());
}
