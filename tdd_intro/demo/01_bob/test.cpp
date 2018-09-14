/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

const char* TellToBob(const std::string& question)
{
    return "Fine. Be that way!";
}

TEST(Bob, Empty)
{
    EXPECT_STREQ("Fine. Be that way!", TellToBob(""));
}

TEST(Bob, Ask)
{
    EXPECT_STREQ("Sure.", TellToBob("Are you robot?"));
}
