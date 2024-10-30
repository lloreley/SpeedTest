#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include "LoginWindow/LoginWindow.hpp"

#define MIN_HEIGHT 600
#define MIN_WIDHT 800
#define MAIN_WINDOW_NAME "Typing speed test"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(const char *windowTitle = nullptr,
               size_t minimumWidth = 0,
               size_t minimumHeight = 0,
               QWidget *parent = nullptr);
    ~MainWindow();

private:

    LoginWindow* logwin;
public slots:
    void login();

private slots:
    // void isLoginSuccessful();
    // void isLoginFailed();
    // void isLogout();
    
signals:
    void loginSuccessful();
    void loginFailed();
    void logout();
};
#endif // MAINWINDOW_H
