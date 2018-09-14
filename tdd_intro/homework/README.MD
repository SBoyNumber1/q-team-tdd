# Homework

Homework is another core part of course activities. These are the tasks you should solve by yourself or with your pair-programming partner (whatever you like more) outside of a group sessions to fixup some practicies in your mind.

All homework tasks are bound to separate workshop sessions and should be solved in order they are provided, wishfully not earlier than the corresponding workshop occurs.

Solved homework tasks should be published into your public repo where mentor can review results you produced. Prefered way is to create your mainline branch and create pull requests from branches corresponding to the task solved.

All available tasks are listed below in corresponding order:

## Basic practicies training:
### Words Count

Given a phrase -> count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

```
olly: 2
in: 1
come: 1
free: 1
```

Example declaration of function required can be something like this:
std::map<std::string, int> WordsCount(std::string);

### Leap Year

Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

Do not consider the period Before Christ. 

_from http://exercism.io/_

### Trinary

Convert a trinary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

Trinary numbers contain three symbols: 0, 1, and 2.

The last place in a trinary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.
```
# "102012"
    1       0       2       0       1       2    # the number
1*3^5 + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243 +     0 +    54 +     0 +     3 +     2 =  302
```
The program should consider strings specifying an invalid trinary as the value 0.

## Functionality decomposition training:

### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices.
The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification

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

## Mocking & Faking practicies

### Folder copying

Implement a class for recursively copying files from source directory to the destination directory.

A folder hierarchy and file names must be saved.

Empty folders should not be copied at all.

For example it can be something that looks like a

```
class IFileCopier
{
public:
	virtual void Copy(const std::string& src, const std::string& dst) = 0;
};
```

You don't need to test filesystem functions.
To work with a filesystem you should declare an interface and to mock it.

You can start with GMock from https://goo.gl/j7EkQX, good luck!

