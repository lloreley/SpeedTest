#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{



    this->setFixedSize(QSize(MIN_LOGIN_WINDOW_WIDTH, MIN_LOGIN_WINDOW_HEIGHT));
    logbar = new LoginBar(this);
    slider = new LoginWindowSlider(this);
    QObject::connect(slider, &Slider::moveToLeft, logbar, &Slider::isMoveToRight);
    QObject::connect(slider, &Slider::moveToRight, logbar, &Slider::isMoveToLeft);
}

LoginWindow::~LoginWindow(){}

