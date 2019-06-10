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
 * Empty string: done
 * With punctual symbols:
 * With whitespaces:
 * With whitespaces and pubctual:
 * One word:
 * One word twice:
 *
 */

std::map<std::string, int> count_words(const std::string& input)
{
    return {};
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
