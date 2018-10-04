/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>

bool IsAnagrams(const std::string& left, const std::string& right)
{
    return !left.empty() && !right.empty();
}

TEST (IsAnagrams, empty_words)
{
    EXPECT_FALSE(IsAnagrams("", ""));
}
