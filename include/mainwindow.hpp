#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Pages/LoginPage/LoginPage.hpp"
#include "Pages/WelcomePage/WelcomePage.hpp"
#include "Accounts/User.hpp"
#include "Pages/NavigationPage/NavigationPage.hpp"
#include "Pages/LessonsScrollArea.hpp"

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
