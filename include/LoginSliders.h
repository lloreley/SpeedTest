#ifndef LOGIN_WINDOW_SLIDER_H
#define LOGIN_WINDOW_SLIDER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QMetaType>
#include <QLineEdit>
#include <QMessageBox>

#include "defines.h"
#include "ButtonWithHover.h"
#include "Exception.h"

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

    virtual void swap() = 0;
    virtual void setup() = 0;

    QPropertyAnimation *SliderPosAnimation();

protected:
    virtual ButtonWithHover *createSignButton() = 0;
    void paintEvent(QPaintEvent *event) override;

    QString sliderStyle;
    QPropertyAnimation *sliderPosAnimation;

public slots:

    virtual void isSignButtonClicked() = 0;
    virtual void isSliderMove() = 0;

signals:
    void sliderSignUpClicked(const QString &);
    void sliderSignInClicked(const QString &);
    void sliderMove();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MainSlider final : public Slider
{
    Q_OBJECT
    Q_PROPERTY(BorderRadii borderRadii READ getBorderRadii WRITE setBorderRadii)
public:
    MainSlider(QWidget *parent = nullptr);
    BorderRadii getBorderRadii();
    void setBorderRadii(BorderRadii borderRadii);
    ButtonWithHover *signButton();
    QLabel *greetingLabel();
    QLabel *additionalLabel();

private:
    void setup() override;
    BorderRadii borderRadii;
    QPropertyAnimation *sliderBorderAnimation;

    ButtonWithHover *createSignButton() override;
    QLabel *createGreetingLabel();
    QLabel *createAdditionalLabel();
    void swapGreetinLabelText();
    void swapAdditionalLabelText();
    void swap() override;

public slots:
    void isSignButtonClicked() override;
    void isSliderMove() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LoginSlider : public Slider
{
    Q_OBJECT
public:
    LoginSlider(QWidget *parent = nullptr);
    void setup() override;
    QLabel *mainLabel();
    QLabel *errorLabel();
    ButtonWithHover *signButton();
    QLineEdit *nameLineEdit();
    QLineEdit *emailLineEdit();
    QLineEdit *passwordLineEdit();
    QPushButton *notSignButton();

private:
    void validateName(const QString &name);
    void validateEmail(const QString &email);
    void validatePassword(const QString &password);
    void swapMainLabelText();
    void swap() override;
    QPushButton *createNotSignButton();
    QLabel *createMainLabel();
    QLineEdit *createNameLineEdit();
    QLineEdit *createEmailLineEdit();
    QLineEdit *createPasswordLineEdit();
    QLabel *createErrorLabel();
    QLabel *createPictureLabel();
    ButtonWithHover *createSignButton() override;
    void clear();

public slots:
    void isSignButtonClicked() override;
    void isSliderMove() override;
};

#endif
