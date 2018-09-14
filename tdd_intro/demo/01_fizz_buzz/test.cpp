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
    if (number % 3 == 0)
    {
        return "Fizz";
    }
    else if (number % 5 == 0)
    {
        return "Buzz";
    }
    return "";
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
