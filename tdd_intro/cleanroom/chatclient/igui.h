#pragma once
#include <string>

class IGui
{
public:
    virtual ~IGui() {}

    // Reads message written by user from the GUI
    virtual std::string Read() = 0;
    // Displays given text in GUI
    virtual void Write(const std::string& text) = 0;
};
