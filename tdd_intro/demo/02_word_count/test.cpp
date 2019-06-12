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

                if (str.size() - 1 == i) {
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

    template <typename UnaryPredicate>
    std::map<std::string_view, std::size_t> count_words(std::string_view str, UnaryPredicate separator_predicate) {
        std::map<std::string_view, std::size_t> result {};

        auto words = util::split(str, separator_predicate);
        for (auto&& word : words) {
            ++result[word];
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

TEST(CountWordTestCase, HasOneWord) {
    auto actual_result = util::count_words("olly", util::is_separator);
    ASSERT_EQ(actual_result.size(), 1);
    EXPECT_EQ(actual_result.at("olly"), 1);
}

TEST(CountWordTestCase, HasTwoDifferentWords) {
    auto actual_result = util::count_words("olly, kolly", util::is_separator);
    ASSERT_EQ(actual_result.size(), 2);
    EXPECT_EQ(actual_result.at("olly"), 1);
    EXPECT_EQ(actual_result.at("kolly"), 1);
}

TEST(CountWordTestCase, HasTwoSameWords) {
    auto actual_result = util::count_words("olly, olly", util::is_separator);
    ASSERT_EQ(actual_result.size(), 1);
    EXPECT_EQ(actual_result.at("olly"), 2);
}

TEST(CountWordTestCase, ExampleTest) {
    auto actual_result = util::count_words("olly olly in come free please please let it be in such manner olly", util::is_separator);
    ASSERT_EQ(actual_result.size(), 10);
    EXPECT_EQ(actual_result.at("olly"), 3);
    EXPECT_EQ(actual_result.at("come"), 1);
    EXPECT_EQ(actual_result.at("free"), 1);
    EXPECT_EQ(actual_result.at("please"), 2);
    EXPECT_EQ(actual_result.at("let"), 1);
    EXPECT_EQ(actual_result.at("it"), 1);
    EXPECT_EQ(actual_result.at("be"), 1);
    EXPECT_EQ(actual_result.at("manner"), 1);
    EXPECT_EQ(actual_result.at("such"), 1);
}
