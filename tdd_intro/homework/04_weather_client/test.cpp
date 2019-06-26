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

struct RawWeatherForDay
{
    std::string weather_3;
    std::string weather_9;
    std::string weather_15;
    std::string weather_21;
};

struct Weather
{
public:
    int temperature = 0;
    unsigned int wind_direction = 0;
    double wind_speed = 0.0;
};

bool operator==(const Weather& lhs, const Weather& rhs)
{
    return lhs.temperature == rhs.temperature &&
            lhs.wind_direction == rhs.wind_direction &&
            std::abs(lhs.wind_speed - rhs.wind_speed) < 0.01;
}

struct WeatherForDay
{
    Weather weather_3;
    Weather weather_9;
    Weather weather_15;
    Weather weather_21;
};

Weather parse_weather(const std::string& raw_weather)
{
    Weather result;
    const char delimeter = ';';

    auto start = raw_weather.begin();
    size_t finish_of_temperature = raw_weather.find(delimeter);
    if (finish_of_temperature == std::string::npos)
    {
        throw std::runtime_error("failed to parse reply from server");
    }
    result.temperature = std::stoi(std::string(start, start + finish_of_temperature));
    start += ++finish_of_temperature;

    size_t finish_of_wind_direction = raw_weather.find(delimeter, finish_of_temperature);
    if (finish_of_wind_direction == std::string::npos)
    {
        throw std::runtime_error("failed to parse reply from server");
    }
    size_t len_of_wd = finish_of_wind_direction - finish_of_temperature;
    result.wind_direction = std::stoul(std::string(start, start + len_of_wd));
    if (result.wind_direction > 359)
    {
        throw std::runtime_error("invalid wind duration value");
    }
    start += len_of_wd + 1;

    result.wind_speed = std::stod(std::string(start, raw_weather.end()));

    return result;
}

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
        return std::min<int>({weather_for_day.weather_3.temperature,
                                weather_for_day.weather_9.temperature,
                                weather_for_day.weather_15.temperature,
                                weather_for_day.weather_21.temperature});
    }
    double GetMaximumTemperature(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return std::max<int>({weather_for_day.weather_3.temperature,
                                weather_for_day.weather_9.temperature,
                                weather_for_day.weather_15.temperature,
                                weather_for_day.weather_21.temperature});

    }
    double GetAverageWindDirection(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return static_cast<double>(weather_for_day.weather_3.wind_direction +
                                weather_for_day.weather_9.wind_direction +
                                weather_for_day.weather_15.wind_direction +
                                weather_for_day.weather_21.wind_direction) / 4;

    }
    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) override
    {
        auto weather_for_day = get_weather_for_day(server, date);
        return std::max<double>({weather_for_day.weather_3.wind_speed,
                                weather_for_day.weather_9.wind_speed,
                                weather_for_day.weather_15.wind_speed,
                                weather_for_day.weather_21.wind_speed});

        return 1;
    }
private:


    WeatherForDay get_weather_for_day(IWeatherServer& server, const std::string& date)
    {
        auto raw_weather_for_day = get_raw_weather_for_day(server, date);
        WeatherForDay result;
        result.weather_3 = parse_weather(raw_weather_for_day.weather_3);
        result.weather_9 = parse_weather(raw_weather_for_day.weather_9);
        result.weather_15 = parse_weather(raw_weather_for_day.weather_15);
        result.weather_21 = parse_weather(raw_weather_for_day.weather_21);

        return result;
    }

    RawWeatherForDay get_raw_weather_for_day(IWeatherServer& server, const std::string& date)
    {
        RawWeatherForDay weather_for_day;

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

TEST(Weather, GetAverageWindDirection_normal)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_EQ(135.75, client.GetAverageWindDirection(server, "01.09.2018"));
}

TEST(Weather, GetMaximumTemperature_normal)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_EQ(31, client.GetMaximumTemperature(server, "01.09.2018"));
}

TEST(Weather, GetMinimumTemperature_normal)
{
    MockIWeatherServer server;
    WeatherClient client;
    EXPECT_EQ(21, client.GetMinimumTemperature(server, "02.09.2018"));
}


TEST(Weather, parse_weather_no_temperature)
{
    EXPECT_THROW(parse_weather(";359;13.2"), std::exception);
}

TEST(Weather, parse_weather_no_wind_direction)
{
    EXPECT_THROW(parse_weather("-4;;13.2"), std::exception);
}

TEST(Weather, parse_weather_no_wind_speed)
{
    EXPECT_THROW(parse_weather("-4;340;"), std::exception);
}

TEST(Weather, parse_weather_not_enough_delimeters)
{
    EXPECT_THROW(parse_weather("123;124"), std::runtime_error);
}

TEST(Weather, parse_weather_invalid_wind_direction)
{
    EXPECT_THROW(parse_weather("-4.5;360;13.2"), std::runtime_error);
}

TEST(Weather, parse_weather_normal)
{
    Weather expected;
    expected.temperature = -4.5;
    expected.wind_direction = 120;
    expected.wind_speed = 13.2;

    EXPECT_EQ(expected, parse_weather("-4.5;120;13.2"));
}
