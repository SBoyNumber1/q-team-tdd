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

namespace util {
    auto is_separator = [](char c) {
        return std::ispunct(c) || std::isspace(c);
    };

    // TODO: Refactor using state pattern
    template <typename UnaryPredicate>
    std::vector<std::string_view> split(std::string_view str, UnaryPredicate separator_predicate) {
        enum State {
            ReadingSeparator,
            ReadingWord
        } current_state = ReadingSeparator;

        // State machine context
        std::vector<std::string_view> result;
        std::size_t word_start = 0;

        for (std::size_t i = 0; i < str.size(); ++i) {
            switch (current_state) {
            case ReadingWord:
                if (separator_predicate(str[i])){
                    result.push_back(str.substr(word_start, i - word_start));
                    current_state = ReadingSeparator;
                }

                if (str.size() - 1 == i && 0 != word_start) {
                    result.push_back(str.substr(word_start, str.size()));
                }

                break;
            case ReadingSeparator:
                if (!separator_predicate(str[i])){
                    word_start = i;
                    current_state = ReadingWord;
                }
                break;
            }
        }

        return result;
    }
}

TEST(CountWordTestCase, IsSeparator) {
    ASSERT_TRUE(util::is_separator(','));
}

TEST(CountWordTestCase, IsNotSeparator) {
    ASSERT_FALSE(util::is_separator('f'));
}

TEST(CountWordTestCase, SpaceIsSeparator) {
    ASSERT_TRUE(util::is_separator(' '));
}

TEST(CountWordTestCase, SplitOneWord) {
    auto actual_result = util::split(" olly", util::is_separator);
    ASSERT_EQ(actual_result.size(), 1);
    EXPECT_EQ(actual_result.front(), "olly");
}

TEST(CountWordTestCase, SplitWordsWithSeparators) {
    auto actual_result = util::split(" ,olly , olly.   ", util::is_separator);
    ASSERT_EQ(actual_result.size(), 2);
    EXPECT_EQ(actual_result.front(), "olly");
    EXPECT_EQ(actual_result.back(), "olly");
}
