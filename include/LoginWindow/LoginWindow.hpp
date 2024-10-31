#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "LoginWindowSlider.hpp"

// #define RIGHT_SLIDER_STYLE "background-color: rgb(81, 45, 168); border-top-left-radius: 150px; border-bottom-left-radius: 100px;"
// #define LEFT_SLIDER_STYLE "background-color: rgb(81, 45, 168); border-radius: 100px;" // border-bottom-right-radius: 100px;"

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    LoginWindowSlider *slider;

private slots:

    void isSliderSignUpClicked();
    void isSliderSignInClicked();
};

#endif