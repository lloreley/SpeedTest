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

#include <QDebug>
#include "SignButton.hpp"
#include "../StyleLoader/StyleLoader.hpp"

#define MIN_SLIDER_HEIGHT 600
#define MIN_SLIDER_WIDTH 400
#define ZERO_CONTEXT_MARGINS QMargins(0, 0, 0, 0)
#define SLIDER_BORDER_RADIUS 150
#define SLIDER_LEFT_POS QPoint(0, 0)
#define SLIDER_RIGHT_POS QPoint(MIN_SLIDER_WIDTH, 0)
#define SLIDER_DURATION 1000
#define SLIDER_EASING_CURVE QEasingCurve::OutQuart
#define GREETIN_LABEL_TEXT_BACK "Welcome Back!"
#define GREETIN_LABEL_TEXT_HELLO "Hello, Friend!"
#define ADDITIONAL_LABEL_TEXT_BACK "Enter yor personal details to use all of application features"
#define ADDITIONAL_LABEL_TEXT_HELLO "Register with your personal details to use all of application features"
#define LAYOUT_SPACING 50
#define LEFT_POS_BORDER_RADII BorderRadii(0, 0, SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS)
#define RIGHT_POS_BORDER_RADII BorderRadii(SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS, 0, 0)
#define MAIN_LABEL_LOGIN_TAB_TEXT_BACK "Sign In"
#define MAIN_LABEL_LOGIN_TAB_TEXT_HELLO "Create Account"
#define NAME_PLACEHOLDER_TEXT "Name"
#define NAME_PLACEHOLDER_TEXT_AND_EMAIL "Name/Email"
#define EMAIL_PLACEHOLDER_TEXT "Email"
#define PASSWORD_PLACEHOLDER_TEXT "Password"
#define LOGIN_TAB_LAYOUT_SPACING 5
#define LOGO_PATH "pictures/logo.png"

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
    virtual void swap() = 0;

protected:
    QVBoxLayout *sliderLayout;
    SignButton *signButton;
    QTimer *timer;
    QEasingCurve sliderEasingCurve;
    int duration;
    QString sliderStyle;

    void paintEvent(QPaintEvent *event) override;

public slots:
    virtual void timeout() = 0;
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

class MainSlider : public Slider
{
    Q_OBJECT
    Q_PROPERTY(BorderRadii borderRadii READ getBorderRadii WRITE setBorderRadii)
public:
    MainSlider(QWidget *parent = nullptr);
    ~MainSlider();

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
    void timeout() override;
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
    QLabel *label;
public slots:
    void timeout() override;
    void isSliderSignButtonClicked() override;
    void isMoveToLeft() override;
    void isMoveToRight() override;
};

#endif