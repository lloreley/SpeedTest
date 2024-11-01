#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "LoginSliders.hpp"


#define MIN_LOGIN_WINDOW_WIDTH 800
#define MIN_LOGIN_WINDOW_HEIGHT 600

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:

    MainSlider *slider;
    LoginBar* logbar;

};

#endif