#ifndef LOGGER
#define LOGGER

#include <ctime> //time() localtime()
#include <QDir>  // exist() mkdir()
#include "Singleton.hpp"
#include "String.hpp"

#define FOLDER_NAME_WITH_LOGS "logs"
#define BEGINNING_COUNTDOWN_OF_YEARS 1900

using std::time_t;
using std::tm;

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

protected:
    String fileName;

    Logger();
    ~Logger();
    String currentTime();

public:
    void operator()(const char *);
    inline void operator()(const char *, std::ostream &) noexcept;
};

#endif