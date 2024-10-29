#ifndef USER
#define USER

#include <vector>
#include "String.hpp"
#include "Editor.hpp"
#include "SpeedTest.hpp"

class User : public Editor, public SpeedTest
{
protected:
    String username;
    static int id;
    std::vector<String> results;

public:
    void addResult(const String &result) ;
    void viewStats();
};

#endif