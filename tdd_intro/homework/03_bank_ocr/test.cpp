/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::vector<std::string> lines;
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::vector<std::string> lines;
};

bool operator==(const Digit& lhs, const Digit& rhs)
{
    return lhs.lines == rhs.lines;
}

const Digit s_digit0  = {{" _ ",
                         "| |",
                         "|_|"
                       }};
const Digit s_digit1 = {{ "   ",
                         "  |",
                         "  |"
                       }};
const Digit s_digit2 = {{ " _ ",
                         " _|",
                         "|_ "
                       }};
const Digit s_digit3 = {{ " _ ",
                         " _|",
                         " _|"
                       }};
const Digit s_digit4 = {{ "   ",
                         "|_|",
                         "  |"
                       }};
const Digit s_digit5 = {{ " _ ",
                         "|_ ",
                         " _|"
                       }};
const Digit s_digit6 = {{ " _ ",
                         "|_ ",
                         "|_|"
                       }};
const Digit s_digit7 = {{ " _ ",
                         "  |",
                         "  |"
                       }};
const Digit s_digit8 = {{ " _ ",
                         "|_|",
                         "|_|"
                       }};
const Digit s_digit9 = {{ " _ ",
                         "|_|",
                         " _|"
                       }};
const Digit s_digit_error = {{"   ",
                              "   ",
                              "   "
                             }};

const Display s_displayAll0 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
}};

const Display s_displayAll1 = {{ "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
}};

const Display s_displayAll2 = {{  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
}};

const Display s_displayAll3 = {{ " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
}};

const Display s_displayAll4 = {{ "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
}};

const Display s_displayAll5 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
}};

const Display s_displayAll6 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
}};

const Display s_displayAll7 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
}};

const Display s_displayAll8 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
}};

const Display s_displayAll9 = {{ " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
}};

const Display s_display123456789 = {{ "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
}};

/*
List of tests:
    0 - done
    1 - done
    2 - done
    3 - done
    4 - done
    5 - done
    6 - done
    7 - done
    8 - done
    9 - done
    display_to_digit - done
    display_to_digit_zero - done
    error - done
    display_to_int - done
    display_to_zero - done

*/

std::vector<Digit> display_to_digits(const Display& input_display)
{
    std::vector<Digit> digits;
    digits.reserve(g_digitsOnDisplay);

    for (size_t i = 0; i < g_digitsOnDisplay * g_linesInDigit; i+=3)
    {
        Digit new_digit = {{"", "", ""}};
        new_digit.lines.at(0) = input_display.lines.at(0).substr(i, 3);
        new_digit.lines.at(1) = input_display.lines.at(1).substr(i, 3);
        new_digit.lines.at(2) = input_display.lines.at(2).substr(i, 3);

        digits.push_back(new_digit);
    }

    return digits;
}

char recognize(const Digit& digit)
{
    if (digit == s_digit0)
    {
        return '0';
    }
    else if (digit == s_digit1)
    {
        return '1';
    }
    else if (digit == s_digit2)
    {
        return '2';
    }
    else if (digit == s_digit3)
    {
        return '3';
    }
    else if (digit == s_digit4)
    {
        return '4';
    }
    else if (digit == s_digit5)
    {
        return '5';
    }
    else if (digit == s_digit6)
    {
        return '6';
    }
    else if (digit == s_digit7)
    {
        return '7';
    }
    else if (digit == s_digit8)
    {
        return '8';
    }
    else if (digit == s_digit9)
    {
        return '9';
    }

    throw std::runtime_error("invalid digit");
}

int display_to_int(const Display& input_display)
{
    auto digits = display_to_digits(input_display);

    std::string str_res;

    for (auto& each: digits)
    {
        str_res.push_back(recognize(each));
    }
    return std::stoi(str_res);
}


TEST(BankOcr, recognize_zero)
{
    EXPECT_EQ('0', recognize(s_digit0));
}

TEST(BankOcr, recognize_one)
{
    EXPECT_EQ('1', recognize(s_digit1));
}

TEST(BankOcr, recognize_two)
{
    EXPECT_EQ('2', recognize(s_digit2));
}

TEST(BankOcr, recognize_three)
{
    EXPECT_EQ('3', recognize(s_digit3));
}

TEST(BankOcr, recognize_four)
{
    EXPECT_EQ('4', recognize(s_digit4));
}

TEST(BankOcr, recognize_five)
{
    EXPECT_EQ('5', recognize(s_digit5));
}

TEST(BankOcr, recognize_six)
{
    EXPECT_EQ('6', recognize(s_digit6));
}

TEST(BankOcr, recognize_seven)
{
    EXPECT_EQ('7', recognize(s_digit7));
}

TEST(BankOcr, recognize_eight)
{
    EXPECT_EQ('8', recognize(s_digit8));
}

TEST(BankOcr, recognize_nine)
{
    EXPECT_EQ('9', recognize(s_digit9));
}

TEST(BankOcr, display_to_digits)
{
    std::vector<Digit> expect = {s_digit1, s_digit2, s_digit3,
                                 s_digit4, s_digit5, s_digit6,
                                 s_digit7, s_digit8, s_digit9};
    EXPECT_EQ(expect, display_to_digits(s_display123456789));
}

TEST(BankOcr, display_to_digits_zero)
{
    std::vector<Digit> expect = {s_digit0, s_digit0, s_digit0,
                                 s_digit0, s_digit0, s_digit0,
                                 s_digit0, s_digit0, s_digit0};
    EXPECT_EQ(expect, display_to_digits(s_displayAll0));
}

TEST(BankOcr, display_to_int)
{
     EXPECT_EQ(123456789, display_to_int(s_display123456789));
}

TEST(BankOcr, display_to_int_zero)
{
     EXPECT_EQ(000000000, display_to_int(s_displayAll0));
}

TEST(BankOcr, recognize_error)
{
    EXPECT_THROW(recognize(s_digit_error), std::runtime_error);
}
