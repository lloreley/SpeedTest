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
            parent->setMaximumSize(LOGIN_PAGE_WIDTH, LOGIN_PAGE_HEIGHT);
        }
        loginSlider = new LoginSlider(this);
        mainSlider = new MainSlider(this);
        connect(mainSlider, &Slider::sliderMove, loginSlider, &Slider::isSliderMove);
        createUser();
    }

    void createUser()
    {
        user = new UnauthorizedUser(parent());
        connect(user, &BaseUser::accountCreated, this, &isSuccessfulSign);
        connect(user, &BaseUser::loginSuccessful, this, &isSuccessfulSign);
        connect(user, &BaseUser::accountNotCreated, [this]()
                { loginSlider->errorLabel()->setText(LP_LS_EL_THIS_NAME_IS_TAKEN); });
        connect(user, &BaseUser::passwordIncorrect, [this]()
                { loginSlider->errorLabel()->setText(LP_LS_EL_PASSWORD_INCORRECT); });
        connect(user, &BaseUser::userNotFound, [this]()
                { loginSlider->errorLabel()->setText(LP_LS_EL_USER_NOT_FOUND); });
        connect(user, &BaseUser::connectionLost, [this]()
                { loginSlider->errorLabel()->setText(LP_LS_EL_CONNECTION_LOST); });

        connect(loginSlider->notSignButton(), &QAbstractButton::clicked, this, &dontUseAccount);
        connect(loginSlider, &LoginSlider::sliderSignInClicked, user, &ServerClient::sendToServer);
        connect(loginSlider, &LoginSlider::sliderSignUpClicked, user, &ServerClient::sendToServer);
    }

    BaseUser *getUser()
    {
        return user;
    }

private:
    void dontUseAccount()
    {
        user->getSocket()->disconnect();
        hide();
    }

    void isSuccessfulSign()
    {
        QString userData = user->getUserData();
        qDebug() << userData;
        delete user;
        User *autorizedUser = new User;
        autorizedUser->setUserData(userData);
        user = autorizedUser;
        hide();
    }

    MainSlider *mainSlider;
    LoginSlider *loginSlider;
    BaseUser *user;
};

#endif