#ifndef ADMIN

#define ADMIN

#include "User.hpp"

class Admin : public User
{
private:
    std::vector<User> users;
public:
    void manageUsers(int);
    void viewStatistics(int);
    void editTexts();
};
#endif