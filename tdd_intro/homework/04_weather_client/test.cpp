/*
Fake Weather Client

You are going to develop a program that gets the statistics about weather in the cities using information from a certain server. Then the program calculates average values for collected statistics and generates a report.

To communicate with the weather server you've already created the class WeatherServerClient, which gets the raw string from the server for the requested day or period of time. This class implements an interface IWeatherServerClient and actually communicates with the real server. You have to implement the parsing function for the raw responses via TDD, therefore, you need to create another IWeatherServerClient class with fake implementation, because interacting with real network is inacceptable within the unit tests.
  
The server answers with text of this format:
    31.08.2018;03:00;20;181:5.1
    31.08.2018;09:00;23;204:4.9
    31.08.2018;15:00;33;193:4.3
    31.08.2018;21:00;46;179:4.5
    Where each line represents the time of the day and contains the next information: "<date>;<time>;<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>". Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

Your program should parse the answers from weather server and collect the average values of temperature, wind direction and speed for the given period of time. For the start, you have to implement the function which collect statistics for a single day for a given city. If you want to make your program more useful, implement the function which collects the statistics for the certain period of time.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class IWeatherServerClient
{
public:
    virtual ~IWeatherServerClient() { }
    // Returns raw statistics for the given day
    std::string GetWeather(const std::string& city, const std::string& date);
    // Returns raw statistics for the given period of time
    std::string GetWeather(const std::string& city, const std::string& startDate, const std::string& endDate);
};

// Stage 1: Get the average weather statistics for the single day
struct Average
{
    // Your fields goes here
};

// Stage 2 (optional): Get the average weather statistics for the given period of time
using Averages = std::map<std::string, Average>; // <date, Average>

