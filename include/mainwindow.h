#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include "LoginPage.h"
#include "WelcomePage.h"
#include "User.h"
#include "NavigationPage.h"
#include "ScrollArea.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setup();
    void emergencyExit(const BaseException);
    void isLoginPageHidden();
    void isWelcomePageHidden();
    void closeEvent(QCloseEvent *event) override;

    LoginPage *logpage;
    WelcomePage *welcomePage;
    NavigationPanel *navigationPanel;
    ScrollArea *area;
    QGridLayout *layout;

private slots:
    void isLogout();
};

#endif
