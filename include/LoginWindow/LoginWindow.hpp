#ifndef LOGIN_WINDOW
#define LOGIN_WINDOW

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include <iostream>

#define MIN_LOGIN_WINDOW_HEIGHT 600
#define MIN_LOGIN_WINDOW_WIDHT 800
#define SIGN_BUTTONS_SIZE QSize(190, 80)
#define SLIDER_BORDER_RADIUS 150
#define SLIDER_LEFT_POS QPoint(-SLIDER_BORDER_RADIUS, 0)
#define SLIDER_RIGHT_POS QPoint(slider->width() - SLIDER_BORDER_RADIUS, 0)
#define ZERO_CONTEXT_MARGINS QMargins(0, 0, 0, 0)
#define PURPLE_COLOR QColor(81, 45, 168)
#define DURATION_BASIC 700
#define SLIDER_EASING_CURVE_BASIC QEasingCurve::OutQuart
#define BUTTON_EASING_CURVE_BASIC QEasingCurve::OutCubic

#define SIGN_IN_BUTTON_NAME "Sing In"
#define SIGN_UP_BUTTON_NAME "Sing Up"
#define BUTTON_STYLE "background-color:rgb(81, 45, 168);color: #fff;font-size: 24px; border: 2px solid; border-color:white;border-radius: 26px;font-weight: 600;font-family: 'Montserrat', sans-serif;"
// #define RIGHT_SLIDER_STYLE "background-color: rgb(81, 45, 168); border-top-left-radius: 150px; border-bottom-left-radius: 100px;"
// #define LEFT_SLIDER_STYLE "background-color: rgb(81, 45, 168); border-radius: 100px;" // border-bottom-right-radius: 100px;"

class LoginWindowSlider : public QWidget
{
    Q_OBJECT
public:
    LoginWindowSlider(QWidget *parent = nullptr);
    ~LoginWindowSlider();
    void paintEvent(QPaintEvent *event) override;
    void setDuration(int duration) noexcept;
    int getDuration() const noexcept;
    void swapSignText() noexcept;
    QEasingCurve getButtonEasingCurve() const noexcept;
    void setButtonEasingCurve(QEasingCurve easingCurve);
    QEasingCurve getSliderEasingCurve() const noexcept;
    void setSliderEasingCurve(QEasingCurve easingCurve);

private:
    QHBoxLayout *sliderLayout;
    QVBoxLayout *centralChildLayout;
    QWidget *leftSpace;
    QWidget *rigthSpace;
    QPushButton *signButton;
    int duration;
    QEasingCurve sliderEasingCurve;
    QEasingCurve buttonEasingCurve;

public slots:
    void isSliderSignButtonClicked();
    void isSliderMovingToLeft();
    void isSliderMovingToRight();


signals:
    void sliderSignUpClicked();
    void sliderSignInClicked();
    void buttonSwapTextToSignIn();
    void buttonSwapTextToSignUp();

};

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

// signals:
    // void sliderMovingToLeft();
    // void sliderMovingToRight();
};

#endif