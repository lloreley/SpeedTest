#include "../include/Logger.hpp"

//make my extension in logger when file is open

Logger::Logger()
{
    if (!QDir(FOLDER_NAME_WITH_LOGS).exists())
    {
        QDir().mkdir(FOLDER_NAME_WITH_LOGS);
    }
    fileName = String(FOLDER_NAME_WITH_LOGS) + String("/") + currentTime() + String(".txt");
}


String Logger::currentTime()
{
    time_t time = std::time(nullptr); // getting time from 1970 in sec
    tm tm = *std::localtime(&time);   // translate to tm-struct
    String stringTime = intToString(tm.tm_mday) + String(".") + intToString(tm.tm_mon) + String(".")
        + intToString(tm.tm_year + BEGINNING_COUNTDOWN_OF_YEARS) + String(" ") + intToString(tm.tm_hour)
        + String(".") + intToString(tm.tm_min) + String(".") + intToString(tm.tm_sec);
    return stringTime;
}

void Logger::operator()(const char* message)
{
    std::ofstream ofs(fileName, std::ios::app);
    if(ofs.is_open())
    {
        ofs<<message;
        ofs.close();
    }
    else throw "open error";
}

inline void Logger::operator()(const char* message, std::ostream& ostr ) noexcept
{
    ostr << message;
}

