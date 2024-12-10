#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "LoginPage.h"
#include "WelcomePage.h"
#include "User.h"
#include "NavigationPage.h"
#include "LessonsScrollArea.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr);

    LoginPage *logpage;
    WelcomePage *welcomePage;
    NavigationPanel *navigationPanel;
    LessonsScrollArea *area;
    QGridLayout *layout;

private:
    void setup();
    void emergencyExit(const BaseException);
    void isLoginPageHidden();
    void isWelcomePageHidden();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void isLogout();
};

#endif
