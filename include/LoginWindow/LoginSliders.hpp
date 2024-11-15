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
#include "../defines.hpp"
#include "../FileLoader/FileLoader.hpp"

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
    void setDuration(int duration) noexcept;
    void setSliderEasingCurve(QEasingCurve easingCurve);
    virtual void swap() = 0;

    const QPushButton *button()const;
    

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
    void sliderSignUpClicked(QString);
    void sliderSignInClicked(QString);
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