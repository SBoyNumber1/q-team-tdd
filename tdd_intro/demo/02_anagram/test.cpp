/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

bool IsAnagrams(std::string left, std::string right)
{
    if (left == right || left.empty() || right.empty())
    {
        return false;
    }
    std::sort (left.begin(), left.end());
    std::sort (right.begin(), right.end());
    return left == right;
}

std::vector<std::string> GetAnagrams(const std::string& word, const std::vector<std::string>& candidates)
{
    return {};
}

TEST (IsAnagrams, empty_words)
{
    EXPECT_FALSE(IsAnagrams("", ""));
}

TEST (IsAnagrams, same_words_return_false)
{
    EXPECT_FALSE(IsAnagrams("word", "word"));
}

TEST (IsAnagrams, non_anagrams_return_false)
{
    EXPECT_FALSE(IsAnagrams("listen", "google"));
}

TEST (IsAnagrams, anagrams_return_true)
{
    EXPECT_TRUE(IsAnagrams("listen", "inlets"));
}

TEST (GetAnagrams, empty_list_empty_word)
{
    EXPECT_EQ(std::vector<std::string>(), GetAnagrams("", std::vector<std::string>()));
}

