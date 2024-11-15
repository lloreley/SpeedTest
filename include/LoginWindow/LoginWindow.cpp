#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(QSize(MIN_LOGIN_WINDOW_WIDTH, MIN_LOGIN_WINDOW_HEIGHT));

    logbar = new LoginBar(this);
    mainSlider = new MainSlider(this);
    QObject::connect(mainSlider, &Slider::moveToLeft, logbar, &Slider::isMoveToRight);
    QObject::connect(mainSlider, &Slider::moveToRight, logbar, &Slider::isMoveToLeft);
}

LoginWindow::~LoginWindow() {}

const MainSlider *LoginWindow::getMainSlider()
{
    return mainSlider;
}

const LoginBar *LoginWindow::getLoginBar()
{
    return logbar;
}
