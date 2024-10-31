#ifndef LOGIN_WINDOW_SLIDER
#define LOGIN_WINDOW_SLIDER

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include <QStyleOption>
#include <cmath>
#include "SignButton.hpp"

#define MIN_LOGIN_WINDOW_HEIGHT 600
#define MIN_LOGIN_WINDOW_WIDHT 800
#define ZERO_CONTEXT_MARGINS QMargins(0, 0, 0, 0)

#define SLIDER_BORDER_RADIUS 150
#define SLIDER_LEFT_POS QPoint(-SLIDER_BORDER_RADIUS, 0)
#define SLIDER_RIGHT_POS QPoint(slider->width() - SLIDER_BORDER_RADIUS, 0)
#define PURPLE_SLIDER_COLOR QColor(81, 45, 168)
#define DURATION_BASIC 700
#define SLIDER_EASING_CURVE_BASIC QEasingCurve::OutQuart
#define BUTTON_EASING_CURVE_BASIC QEasingCurve::OutCubic

#define GREETIN_LABEL_TEXT_BACK "Welcome Back!"
#define GREETIN_LABEL_TEXT_HELLO "Hello, Friend!"

#define ADDITIONAL_LABEL_TEXT_BACK "Enter yor personal details to use all of application features"
#define ADDITIONAL_LABEL_TEXT_HELLO "Register with your personal details to use all of application features"
#define ADDITIONAL_LABEL_MIN_WIGTH 350
#define CENTRAL_LAYOUT_SPACING 50

#define GREATING_LABEL_STYLE "color: rgb(255, 255, 255);font-size: 30px;font-weight: 1000;font-family: 'Montserrat', sans-serif;"
#define ADDITIONAL_LABEL_STYLE "color: rgb(255, 255, 255);font-size: 18px;font-weight: 460;font-family: 'Montserrat', sans-serif;"

#define SLIDER_STYLE "background:rgb(81, 45, 168); border-top-left-radius: %1px;border-bottom-left-radius: %2px;border-top-right-radius: %3px;border-bottom-right-radius: %4px;"

#include <QVariant>
#include <QMetaType>

class BorderRadii
{
public:
    int left_top;
    int left_bottom;
    int right_top;
    int right_bottom;

    BorderRadii(int lt = 0, int lb = 0, int rt = 0, int rb = 0)
        : left_top{lt}, left_bottom{lb}, right_top{rt}, right_bottom{rb} {}
    BorderRadii(const BorderRadii &other)
    {
        this->left_top = other.left_top;
        this->left_bottom = other.left_bottom;
        this->right_top = other.right_top;
        this->right_bottom = other.right_bottom;
    }
};

class LoginWindowSlider : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(BorderRadii borderRadii READ getBorderRadii WRITE setBorderRadii)
public:
    LoginWindowSlider(QWidget *parent = nullptr);
    ~LoginWindowSlider();
    void paintEvent(QPaintEvent *event) override;
    void setDuration(int duration) noexcept;
    int getDuration() const noexcept;

    // QEasingCurve getButtonEasingCurve() const noexcept;
    // void setButtonEasingCurve(QEasingCurve easingCurve);
    QEasingCurve getSliderEasingCurve() const noexcept;
    void setSliderEasingCurve(QEasingCurve easingCurve);
    BorderRadii getBorderRadii();
    void setBorderRadii(BorderRadii borderRadii);

    void swapSignText() noexcept;
    void swapGreetinLabelText() noexcept;
    void swapAdditionalLabelText() noexcept;
    void swap();

private:
    // QHBoxLayout *sliderLayout;
    QVBoxLayout *centralChildLayout;
    // QWidget *leftSpace;
    // QWidget *rigthSpace;
    SignButton *signButton;
    QLabel *greetingLabel;
    QLabel *additionalLabel;
    int duration;
    BorderRadii borderRadii;
    QEasingCurve sliderEasingCurve;
    // QEasingCurve buttonEasingCurve;

// public slots:
    void isSliderSignButtonClicked();
    // void isSliderMovingToLeft();
    // void isSliderMovingToRight();

signals:
    void sliderSignUpClicked();
    void sliderSignInClicked();
    // void buttonSwapTextToSignIn();
    // void buttonSwapTextToSignUp();
};

#endif