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


#define MIN_LOGIN_WINDOW_WIDTH 800
#define MIN_LOGIN_WINDOW_HEIGHT 600

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:

    LoginWindowSlider *slider;
    LoginBar* logbar;

};

#endif