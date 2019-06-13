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
 * List of tests:
 *
 * Empty string:                  done
 * With punctual symbols:         done
 * With whitespaces:              done
 * With whitespaces and pubctual:
 * One word:                      done
 * One word twice:
 *
 */

std::map<std::string, int> count_words(const std::string& input)
{
    if (input.empty())
    {
	return {};
    }

    auto pos_of_whitespace = input.find_first_of(" .,?!;");

    if (pos_of_whitespace == std::string::npos)
    {
        return {{input, 1}};
    }
    std::string result_string(input.begin(), input.begin() + pos_of_whitespace);

    return {{result_string, 1}};
}

TEST(WordCount, empty_string)
{
    EXPECT_TRUE(count_words("").empty());
}

TEST(WordCount, one_word)
{
    std::map<std::string, int> expected = {{"one", 1}};
    EXPECT_EQ(expected, count_words("one"));
}

TEST(WordCount, with_whitespace)
{
    std::map<std::string, int> expected = {{"one", 1}};
    EXPECT_EQ(expected, count_words("one "));
}

TEST(WordCount, with_punctual_symbols)
{
    std::map<std::string, int> expected = {{"one", 1}};
    EXPECT_EQ(expected, count_words("one."));
}

TEST(WordCount, two_different_words)
{
    std::map<std::string, int> expected = {{"one", 1}, {"two", 1}};
    EXPECT_EQ(expected, count_words("one.two"));

}
