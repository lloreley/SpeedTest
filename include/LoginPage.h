#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "LoginSliders.h"
#include "User.h"
#include "Page.h"

class LoginPage : public Page
{
    Q_OBJECT
public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    void show();
    void createUnauthorizedUser();
    BaseUser *getUser();
private slots:
    void dontUseAccount();
    void isSuccessfulSign();

private:
    void setup() override;
    MainSlider *mainSlider;
    LoginSlider *loginSlider;
    BaseUser *user;
};

#endif