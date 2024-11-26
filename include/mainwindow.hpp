#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include "Pages/LoginPage/LoginPage.hpp"
#include "Pages/WelcomePage/WelcomePage.hpp"
#include "Accounts/User.hpp"
#include "Pages/NavigationPage/NavigationPage.hpp"
#include "Pages/LessonsScrollArea.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(const char *windowTitle = nullptr,
               size_t minimumWidth = 0,
               size_t minimumHeight = 0,
               QWidget *parent = nullptr);

    LoginPage *logpage;
    WelcomePage *welcomePage;
    NavigationPanel *navigationPanel;
    LessonsScrollArea *area;
    QGridLayout *layout;

private:
    void isLoginPageHidden();
    void isWelcomePageHidden();
    void createWidgets();
    void setConnections();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif
