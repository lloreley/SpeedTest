#ifndef LOGIN_WINDOW_SLIDER
#define LOGIN_WINDOW_SLIDER

#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPainter>
#include <QLabel>
#include <QStyleOption>
#include <QMetaType>
#include <QTimer>
#include <QLineEdit>

#include "SignButton.hpp"

#define MIN_SLIDER_HEIGHT 600
#define MIN_SLIDER_WIDTH 400
#define ZERO_CONTEXT_MARGINS QMargins(0, 0, 0, 0)
#define ZERO_BORDER_RADII BorderRadii(0, 0, 0, 0)

#define SLIDER_BORDER_RADIUS 150
#define SLIDER_LEFT_POS QPoint(0, 0)
#define SLIDER_RIGHT_POS QPoint(MIN_SLIDER_WIDTH, 0)
#define DURATION_BASIC 1000
#define SLIDER_EASING_CURVE_BASIC QEasingCurve::OutQuart

#define GREETIN_LABEL_TEXT_BACK "Welcome Back!"
#define GREETIN_LABEL_TEXT_HELLO "Hello, Friend!"

#define ADDITIONAL_LABEL_TEXT_BACK "Enter yor personal details to use all of application features"
#define ADDITIONAL_LABEL_TEXT_HELLO "Register with your personal details to use all of application features"
#define ADDITIONAL_LABEL_MIN_WIDTH 350
#define LAYOUT_SPACING 50

#define GREATING_LABEL_STYLE "QLabel {color: rgb(255, 255, 255);font-size: 30px;font-weight: 1000;font-family: 'Montserrat', sans-serif;}"
#define ADDITIONAL_LABEL_STYLE "QLabel {color: rgb(255, 255, 255);font-size: 18px;font-weight: 440;font-family: 'Montserrat', sans-serif;}"
#define SLIDER_STYLE_WITH_BORDER_RADII "LoginWindowSlider {background:rgb(81, 45, 168); border-top-left-radius: %1px;border-bottom-left-radius: %2px;border-top-right-radius: %3px;border-bottom-right-radius: %4px;}"

#define LEFT_BORDER_RADII BorderRadii(0, 0, SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS)
#define RIGHT_BORDER_RADII BorderRadii(SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS, 0, 0)

#define MAIN_LABEL_LOGIN_TAB "QLabel {color: rgb(0, 0, 0);font-size: 36px;font-weight: 1000;font-family: 'Montserrat', sans-serif;}"
#define MAIN_LABEL_LOGIN_TAB_TEXT_BACK "Sign In"
#define MAIN_LABEL_LOGIN_TAB_TEXT_HELLO "Create Account"

#define NAME_PLACEHOLDER_TEXT "Name"
#define EMAIL_PLACEHOLDER_TEXT "Email"
#define PASSWORD_PLACEHOLDER_TEXT "Password"
#define LOGIN_TAB_LAYOUT_SPACING 5

#define LINE_EDIT_STYLE "background-color: rgb(217, 213, 219); border: none; margin: 8px; font-size: 20px; border-radius: 12px;width:320px; height: 44;font-family: 'Montserrat', sans-serif;"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct borderRadii
{
public:
    int left_top;
    int left_bottom;
    int right_top;
    int right_bottom;

    borderRadii(int lt = 0, int lb = 0, int rt = 0, int rb = 0)
        : left_top{lt}, left_bottom{lb}, right_top{rt}, right_bottom{rb} {}
    borderRadii(const struct borderRadii &other)
    {
        this->left_top = other.left_top;
        this->left_bottom = other.left_bottom;
        this->right_top = other.right_top;
        this->right_bottom = other.right_bottom;
    }
} BorderRadii;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Slider : public QWidget
{
    Q_OBJECT
public:
    Slider(QWidget *parent = nullptr);
    ~Slider();
    void setDuration(int duration) noexcept;
    int getDuration() const noexcept;
    void setSliderEasingCurve(QEasingCurve easingCurve);
    QEasingCurve getSliderEasingCurve() const noexcept;
    void swapSignText() noexcept;
    virtual void swap() = 0;

protected:
    QVBoxLayout *sliderLayout;
    SignButton *signButton;
    QEasingCurve sliderEasingCurve;
    int duration;
    QTimer *timer;

    void paintEvent(QPaintEvent *event) override;

public slots:
    void timeout();
    virtual void isSliderSignButtonClicked() = 0;
    virtual void isMoveToRight() = 0;
    virtual void isMoveToLeft() = 0;

signals:
    void sliderSignUpClicked();
    void sliderSignInClicked();
    void moveToRight();
    void moveToLeft();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LoginWindowSlider : public Slider
{
    Q_OBJECT
    Q_PROPERTY(BorderRadii borderRadii READ getBorderRadii WRITE setBorderRadii)
public:
    LoginWindowSlider(QWidget *parent = nullptr);
    ~LoginWindowSlider();

    BorderRadii getBorderRadii();
    void setBorderRadii(BorderRadii borderRadii);

    void swapGreetinLabelText() noexcept;
    void swapAdditionalLabelText() noexcept;
    void swap() override;

private:
    QLabel *greetingLabel;
    QLabel *additionalLabel;
    BorderRadii borderRadii;

public slots:
    void isSliderSignButtonClicked() override;
    void isMoveToLeft() override;
    void isMoveToRight() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LoginBar : public Slider
{
    Q_OBJECT
public:
    LoginBar(QWidget *parent = nullptr);
    ~LoginBar() {}
    void swapMainLabelText();
    void swap() override;

private:
    QLabel *mainLabel;
    QLineEdit *name;
    QLineEdit *email;
    QLineEdit *password;
public slots:

    void isSliderSignButtonClicked() override;
    void isMoveToLeft() override;
    void isMoveToRight() override;
};

#endif