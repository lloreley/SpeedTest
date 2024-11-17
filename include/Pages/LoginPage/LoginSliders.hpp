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

#include "../../ButtonWithHover.hpp"
#include "../../defines.hpp"
// #include "../FileLoader/FileLoader.hpp"

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
    virtual void swap() = 0;

    QPropertyAnimation* SliderPosAnimation();


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

    void swapGreetinLabelText() noexcept;
    void swapAdditionalLabelText() noexcept;
    void swap() override;
    ButtonWithHover *signButton();
    QLabel *greetingLabel();
    QLabel *additionalLabel();

private:
    BorderRadii borderRadii;
    QPropertyAnimation *sliderBorderAnimation;

    ButtonWithHover *createSignButton() override;
    QLabel *createGreetingLabel();
    QLabel *createAdditionalLabel();

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
    void swapMainLabelText();
    void swap() override;

    QLabel *mainLabel();
    QLabel *errorLabel();
    ButtonWithHover *signButton();
    QLineEdit *nameLineEdit();
    QLineEdit *emailLineEdit();
    QLineEdit *passwordLineEdit();

private:
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