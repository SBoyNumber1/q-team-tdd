/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

const char* s_answerEmpty = "Fine. Be that way!";
const char* s_answerQuestion = "Sure.";
const char* s_answerYell = "Whoa, chill out!";

const char* TellToBob(const std::string& question)
{
    if (question.empty())
    {
        return s_answerEmpty;
    }
    return s_answerQuestion;
}

TEST(Bob, Empty)
{
    EXPECT_STREQ(s_answerEmpty, TellToBob(""));
}

TEST(Bob, Ask)
{
    EXPECT_STREQ(s_answerQuestion, TellToBob("Are you robot?"));
}

TEST(Bob, Yell)
{
    EXPECT_STREQ(s_answerYell, TellToBob("Bob!"));
}

