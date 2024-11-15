#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "LoginSliders.hpp"
#include "../defines.hpp"

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    const MainSlider* getMainSlider();
    const LoginBar* getLoginBar();

private:
    MainSlider *mainSlider;
    LoginBar *logbar;

private slots:


};

#endif