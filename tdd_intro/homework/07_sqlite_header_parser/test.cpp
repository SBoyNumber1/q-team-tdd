/*
Implement application for display sqlite header structure of given file.
Application takes path to file and displays header structure
Sqlite header is described here https://www.sqlite.org/fileformat.html
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IGui
{
public:
    ~IGui(){}
    //Add here necessary methods
};

class IDbReader
{
public:
    ~IDbReader(){}
    //Add here necessary methods
};

void DysplayHeaderStructure(IGui* gui, IDbReader* dbReader)
{

}
