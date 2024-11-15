#include "../include/mainwindow.hpp"

MainWindow::MainWindow(const char *windowTitle,
                       size_t minimumWidth,
                       size_t minimumHeight,
                       QWidget *parent) : QWidget(parent)
{
    if (windowTitle)
    {
        this->setWindowTitle(windowTitle);
    }

    if (minimumHeight && minimumWidth)
    {
        this->setMinimumSize(minimumWidth, minimumHeight);
    }

    logwin = new LoginWindow(this);
    user = new User(this);
    connect(logwin->getLoginBar(), &LoginBar::sliderSignInClicked, user, &ServerClient::sendToServer);
    connect(logwin->getLoginBar(), &LoginBar::sliderSignUpClicked, user, &ServerClient::sendToServer);

    this->setMinimumSize(minimumWidth, minimumHeight);
}