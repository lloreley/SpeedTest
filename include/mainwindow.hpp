#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include "Pages/LoginPage/LoginPage.hpp"
#include "Pages/WelcomePage/WelcomePage.hpp"
#include "Accounts/User.hpp"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(const char *windowTitle = nullptr,
               size_t minimumWidth = 0,
               size_t minimumHeight = 0,
               QWidget *parent = nullptr);

    LoginPage *logwin;
private:
    BaseUser *user;

private slots:
 
signals:
    void loginSuccessful();
    void loginFailed();
    void logout();
};
#endif


