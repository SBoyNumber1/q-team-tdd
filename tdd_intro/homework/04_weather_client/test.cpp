/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

struct WeatherForDay
{
    std::string weather_3;
    std::string weather_9;
    std::string weather_15;
    std::string weather_21;
};

class WeatherClient: public IWeatherClient
{
public:
    double GetAverageTemperature(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return 1;
    }
    double GetMinimumTemperature(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return 1;
    }
    double GetMaximumTemperature(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return 1;
    }
    double GetAverageWindDirection(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return 1;
    }
    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return 1;
    }
private:
    WeatherForDay get_weather_for_day(IWeatherServer& server, const std::string& date)
    {
        WeatherForDay weather_for_day;

        weather_for_day.weather_3 = server.GetWeather(date + ";03:00");
        weather_for_day.weather_9 = server.GetWeather(date + ";09:00");
        weather_for_day.weather_15 = server.GetWeather(date + ";15:00");
        weather_for_day.weather_21 = server.GetWeather(date + ";21:00");

        if (weather_for_day.weather_3.empty()
            || weather_for_day.weather_9.empty()
            || weather_for_day.weather_15.empty()
            || weather_for_day.weather_21.empty())
        {
            throw std::runtime_error("invalid data");
        }

        return weather_for_day;
    }
};

struct Weather
{
public:
    int temperature = 0;
    unsigned int wind_duration = 0;
    double wind_speed = 0.0;
};

class MockIWeatherServer: public IWeatherServer
{
public:
    std::string GetWeather(const std::string &request) override
    {
        if (request == "31.08.2018;03:00")
        {
            return "20;181;5.1";
        }
        else if (request == "31.08.2018;09:00")
        {
            return "23;204;4.9";
        }
        else if (request == "31.08.2018;15:00")
        {
            return "33;193;4.3";
        }
        else if (request == "31.08.2018;21:00")
        {
            return "26;179;4.5";
        }
        else if (request == "01.09.2018;03:00")
        {
            return "19;176;4.2";
        }
        else if (request == "01.09.2018;09:00")
        {
            return "22;131;4.1";
        }
        else if (request == "01.09.2018;15:00")
        {
            return "31;109;4.0";
        }
        else if (request == "01.09.2018;21:00")
        {
            return "24;127;4.1";
        }
        else if (request == "02.09.2018;03:00")
        {
            return "21;158;3.8";
        }
        else if (request == "02.09.2018;09:00")
        {
            return "25;201;3.5";
        }
        else if (request == "02.09.2018;15:00")
        {
            return "34;258;3.7";
        }
        else if (request == "02.09.2018;21:00")
        {
            return "27;299;4.0";
        }

        return "";
    }
};

TEST(Weather, GetMaximumWindSpeed_invalid_date)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_THROW(client.GetMaximumWindSpeed(server, "lalala"), std::runtime_error);
}

TEST(Weather, GetAverageWindDirection_invalid_data)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_THROW(client.GetAverageWindDirection(server, "lalala"), std::runtime_error);
}

TEST(Weather, GetMaximumTemperature_invalid_data)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_THROW(client.GetMaximumTemperature(server, "lalala"), std::runtime_error);
}

TEST(Weather, GetMinimumTemperature_invalid_data)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_THROW(client.GetMinimumTemperature(server, "lalala"), std::runtime_error);
}

TEST(Weather, GetAverageTemperature_invalid_data)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_THROW(client.GetAverageTemperature(server, "lalala"), std::runtime_error);
}

TEST(Weather, GetMaximumWindSpeed_normal)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_EQ(5.1, client.GetMaximumWindSpeed(server, "31.08.2018"));
}
