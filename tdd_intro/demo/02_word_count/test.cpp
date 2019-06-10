/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

/*

  Tests list:
  - HasOneWord
  - HasTwoDifferentWords
  - HasTwoSameWords
  - ExampleTest
  - SplitWordsWithPunctuation
  - SplitWordsWithSpaces

*/

auto is_separator = [](char c) {
    return std::ispunct(c) || std::isspace(c);
};

template <typename UnaryPredicate>
std::vector<std::string_view> split(std::string_view, UnaryPredicate) {
    return { "olly" };
}

TEST(CountWordTestCase, IsSeparator) {
    ASSERT_TRUE(is_separator(','));
}

TEST(CountWordTestCase, IsNotSeparator) {
    ASSERT_FALSE(is_separator('f'));
}

TEST(CountWordTestCase, SpaceIsSeparator) {
    ASSERT_TRUE(is_separator(' '));
}

TEST(CountWordTestCase, SplitOneWord) {
    auto actual_result = split("olly", is_separator);
    ASSERT_EQ(actual_result.size(), 1);
    ASSERT_EQ(actual_result.front(), "olly");
}
