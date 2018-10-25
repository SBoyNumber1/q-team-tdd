/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.

Example:
When pos is specified, the search only includes sequences of characters that begin at or before position pos,
ignoring any possible match beginning after pos

"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
*/

#include <gtest/gtest.h>
#include <cctype>

// empty string
// string shorter than wrap number
// word longer than wrap number
// word much longer than wrap number (more than 2 strings)
// string longer than wrap number

// string wrapped by several whitespaces (less than wrapLength)
// string wrapped by several whitespaces (more than wrapLength)
// only whitespaces in string

using WrappedStrings = std::vector<std::string>;

WrappedStrings WrapString(const std::string& str, size_t wrapLength)
{
    WrappedStrings result;
    for(size_t i = 0; i < str.length(); i += wrapLength)
    {
        std::string cur = str.substr(i, wrapLength);
        if (cur.back() == ' ')
        {
            cur.pop_back();
        }

        if(!cur.empty() && cur.front() == ' ')
        {
            cur = cur.substr(1);
        }

        if(!cur.empty())
        {
            result.push_back(cur);
        }
    }

    return result;
}

TEST(WrapString, EmptyString)
{
    ASSERT_EQ(WrappedStrings(), WrapString("", 25));
}

TEST(WrapString, StringShorterWrapNumber)
{
    ASSERT_EQ(WrappedStrings{"asdf"}, WrapString("asdf", 8));
}

TEST(WrapString, StringLongerThanWrapNumber)
{
    WrappedStrings expected = {"asd", "f"};
    ASSERT_EQ(expected, WrapString("asdf", 3));
}

TEST(WrapString, StringLongerThanWrapNumberSeveralParts)
{
    WrappedStrings expected = {"12", "34", "56"};
    ASSERT_EQ(expected, WrapString("123456", 2));
}

TEST(WrapString, MultipleWordsLonger)
{
    WrappedStrings expected = {"1", "2"};
    ASSERT_EQ(expected, WrapString("1 2", 1));
}

TEST(WrapString, SpaceStringEnd)
{
    WrappedStrings expected = {"1", "2"};
    ASSERT_EQ(expected, WrapString("1 2", 2));
}

TEST(WrapString, StringWrappedBySeveralWhitespace)
{
    WrappedStrings expected = {"12", "34"};
    ASSERT_EQ(expected, WrapString("12  34", 3));
}
