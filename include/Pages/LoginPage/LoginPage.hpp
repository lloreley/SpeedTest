#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <QFrame>
#include "LoginSliders.hpp"
#include "../../Accounts/User.hpp"
#include "../Page.hpp"

class LoginPage : public Page
{
    Q_OBJECT
public:
    LoginPage(QWidget *parent = nullptr) : Page(parent)
    {
        if (parent)
        {
            parent->setFixedSize(LOGIN_PAGE_WIDTH, LOGIN_PAGE_HEIGHT);
        }
        logbar = new LoginSlider(this);
        mainSlider = new MainSlider(this);
        connect(mainSlider, &Slider::sliderMove, logbar, &Slider::isSliderMove);
    }

    void setUser(BaseUser *user)
    {
        this->user = user;

        connect(user, &BaseUser::accountCreated, [this](){ fade(); });
        connect(user, &BaseUser::loginSuccessful, [this](){ fade(); });
        connect(user, &BaseUser::accountNotCreated, [this]()
                { logbar->errorLabel()->setText("This name is taken!"); });
        connect(user, &BaseUser::passwordIncorrect, [this]()
                { logbar->errorLabel()->setText("Passord incorrect!"); });
        connect(user, &BaseUser::userNotFound, [this]()
                { logbar->errorLabel()->setText("User not found!"); });
        connect(user, &BaseUser::connectionLost, [this]()
                { logbar->errorLabel()->setText("Connection lost!"); });

        connect(logbar, &LoginSlider::sliderSignInClicked, user, &ServerClient::sendToServer);
        connect(logbar, &LoginSlider::sliderSignUpClicked, user, &ServerClient::sendToServer);
    }

private:
    MainSlider *mainSlider;
    LoginSlider *logbar;
    BaseUser *user;
};

#endif