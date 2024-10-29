#ifndef SPEED_TEST
#define SPEED_TEST

#include <chrono>
#include "Text.hpp"

class SpeedTest : public Text
{
    Text referenceText;
    Text userInput;
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> startTime;
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> endTime;
    void startTest();
    void endTest();
};

#endif