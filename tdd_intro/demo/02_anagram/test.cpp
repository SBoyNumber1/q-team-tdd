/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

using Anagrams = std::set<std::string>;

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

Anagrams GetAnagrams(const std::string& word, const std::vector<std::string>& candidates)
{
    Anagrams anagrams;
    std::copy_if(candidates.begin(), candidates.end(), std::inserter(anagrams, anagrams.end()),
                         [&](const std::string& candidate) {return IsAnagrams(word, candidate);});

    return anagrams;
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
    EXPECT_EQ(Anagrams(), GetAnagrams("", std::vector<std::string>()));
}

TEST (GetAnagrams, anagrams_single_word_in_list)
{
    EXPECT_EQ(Anagrams({"inlets"}), GetAnagrams("listen", {"inlets"}));
}

TEST (GetAnagrams, two_anagrams_in_list)
{
    EXPECT_EQ(Anagrams({"acb", "cba"}), GetAnagrams("abc", {"acb", "cba"}));
}

TEST (GetAnagrams, two_anagrams_in_list_different_sequence)
{
    EXPECT_EQ(Anagrams({"acb", "cba"}), GetAnagrams("abc", {"cba", "acb"}));
}

TEST (GetAnagrams, acceptance)
{
    EXPECT_EQ(Anagrams({"inlets"}), GetAnagrams("listen", {"enlists", "google", "inlets", "banana"}));
}
