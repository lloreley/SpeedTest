#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include "LoginSliders.hpp"
#include "../../Accounts/User.hpp"
#include "../Page.hpp"

class LoginPage : public Page
{
    Q_OBJECT
public:
    LoginPage(QWidget *parent) : Page(parent)
    {
        loginSlider = new LoginSlider(this);
        mainSlider = new MainSlider(this);

        CHECK_PTR(loginSlider)
        CHECK_PTR(mainSlider)

        connect(mainSlider, &Slider::sliderMove, loginSlider, &Slider::isSliderMove);
        createUnauthorizedUser();
        connect(loginSlider->notSignButton(), &QAbstractButton::clicked, this, &dontUseAccount);
    }

    ~LoginPage()
    {
        mainSlider->deleteLater();
        loginSlider->deleteLater();
        user->deleteLater();
    }
    void show()
    {
        parentWidget()->setFixedSize(LOGIN_PAGE_WIDTH, LOGIN_PAGE_HEIGHT);
        Page::show();
    }

    void createUnauthorizedUser()
    {
        user = new UnauthorizedUser(parent());
        CHECK_PTR(user);
        connect(user, &BaseUser::accountCreated, this, &isSuccessfulSign);
        connect(user, &BaseUser::loginSuccessful, this, &isSuccessfulSign);

        connect(user, &BaseUser::accountNotCreated, [this]()
                { QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(LP_LS_EL_THIS_NAME_IS_TAKEN), QMessageBox::Ok); });
        connect(user, &BaseUser::passwordIncorrect, [this]()
                { QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(LP_LS_EL_PASSWORD_INCORRECT), QMessageBox::Ok); });
        connect(user, &BaseUser::userNotFound, [this]()
                { QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(LP_LS_EL_USER_NOT_FOUND), QMessageBox::Ok); });
        connect(user, &BaseUser::connectionLost, [this]()
                { loginSlider->errorLabel()->setText(LP_LS_EL_CONNECTION_LOST); });

        connect(loginSlider, &LoginSlider::sliderSignInClicked, user, &ServerClient::sendToServer);
        connect(loginSlider, &LoginSlider::sliderSignUpClicked, user, &ServerClient::sendToServer);
    }

    BaseUser *getUser()
    {
        CHECK_PTR(user);
        return user;
    }

private slots:

    void dontUseAccount()
    {
        disconnect(user->getSocket(), nullptr, nullptr, nullptr);
        user->getSocket()->deleteLater();
        user->setSocket(nullptr);
        hide();
    }
    void isSuccessfulSign()
    {
        User *authorizedUser = new User(user->getSocket(), parent());
        if (!authorizedUser)
        {
            QMessageBox::critical(nullptr, "Error", QString("An error occurred: user was not created"), QMessageBox::Ok);
            return;
        }
        QString userData = user->getUserData();
        disconnect(user, nullptr, nullptr, nullptr);
        user->setSocket(nullptr);
        user->deleteLater();
        authorizedUser->setUserData(userData);
        user = authorizedUser;
        hide();
    }

private:
    MainSlider *mainSlider;
    LoginSlider *loginSlider;
    BaseUser *user;
};

#endif