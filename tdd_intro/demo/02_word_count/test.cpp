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
 * With whitespaces and pubctual: done
 * With on start punctuals:       done
 * One word:                      done
 * One word twice:
 * Two different words;           done
 */

std::map<std::string, int> count_words(const std::string& input)
{
    if (input.empty())
    {
	return {};
    }

    std::map<std::string, int> result;
    size_t first_index = 0;
    size_t pos_of_whitespace = 0;

    for (;;)
    {
        pos_of_whitespace = input.find_first_of(" .,?!;", first_index);
        auto substr = input.substr(first_index, pos_of_whitespace - first_index);

        first_index = pos_of_whitespace + 1;

        if (substr.size() == 0)
        {
            continue;
        }

        result.insert({substr, 1});


        if (pos_of_whitespace == std::string::npos
                || first_index >= input.size())
        {
            break;
        }
    }

    return result;
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

TEST(WordCount, with_whitespaces_and_punctual)
{
    std::map<std::string, int> expected = {{"one", 1}, {"two", 1}, {"three", 1}, {"four", 1}};
    EXPECT_EQ(expected, count_words(" one.two three? four"));
}

TEST(WordCount, with_punctuals_on_the_start)
{
    std::map<std::string, int> expected = {{"one", 1}, {"two", 1}, {"three", 1}, {"four", 1}};
    EXPECT_EQ(expected, count_words(".?.!one.two three? four"));
}
