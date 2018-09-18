/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

static const char* s_whateverAnswer = "Whatever.";
static const char* s_sureAnswer = "Sure.";

const char* TellToBob(const std::string& message)
{
    if (message.back() == '?')
    {
        return s_sureAnswer;
    }
    return s_whateverAnswer;
}

TEST(Bob, Whatever)
{
    ASSERT_STREQ(s_whateverAnswer, TellToBob("My name is Todd"));
}

TEST(Bob, Sure)
{
    ASSERT_STREQ(s_sureAnswer, TellToBob("Are you robot?"));
}

TEST(Bob, Sure2)
{
    ASSERT_STREQ(s_sureAnswer, TellToBob("You Bob?"));
}

TEST(Bob, Fine)
{
    ASSERT_STREQ("Fine. Be that way!", TellToBob(""));
}
