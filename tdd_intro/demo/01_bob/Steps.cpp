//########################################
// Initial red

#include <string>

const char* TellToBob(const std::string& question)
{
    return {};
}

TEST(Bob, Empty)
{
    EXPECT_STREQ("Fine. Be that way!", TellToBob(""));
}

//########################################

const char* TellToBob(const std::string& question)
{
    return "Fine. Be that way!";
}

//########################################

TEST(Bob, Ask)
{
    EXPECT_STREQ("Sure.", TellToBob("Are you robot?"));
}

//########################################
//Refactoring, added constants:

const char* s_answerEmpty = "Fine. Be that way!";
const char* s_answerQuestion = "Sure.";
const char* s_answerYell = "Whoa, chill out!";
const char* s_answerOther = "Whatever.";

//########################################

const char* TellToBob(const std::string& question)
{
    if (question.empty())
    {
        return s_answerEmpty;
    }
    return s_answerQuestion;
}

//########################################

TEST(Bob, Yell)
{
    EXPECT_STREQ(s_answerYell, TellToBob("Bob!"));
}

//########################################

if (question.empty())
    {
        return s_answerEmpty;
    }
    if (question.back() == '?')
    {
        return s_answerQuestion;
    }
    else
    {
        return s_answerYell;
    }
}

//########################################

const char* TellToBob(const std::string& question)
{
    if (question.empty())
    {
        return s_answerEmpty;
    }
    else if (question.back() == '?')
    {
        return s_answerQuestion;
    }
    else if (question.back() == '!')
    {
        return s_answerYell;
    }
    return s_answerOther;
}
