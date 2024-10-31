#ifndef SIGN_BUTTON
#define SIGN_BUTTON

#include <QPushButton>

#define SIGN_BUTTONS_SIZE QSize(190, 80)
#define SIGN_IN_BUTTON_NAME "Sign In"
#define SIGN_UP_BUTTON_NAME "Sign Up"
#define BUTTON_STYLE "background-color:rgb(%1, %2, %3);color: rgb(%4, %5, %6);font-size: 24px; border: 2px solid; border-color:white;border-radius: 26px;font-weight: 600;font-family: 'Montserrat', sans-serif;"
#define PURPLE QColor(81, 45, 168)
#define WHITE QColor(255, 255, 255)

#include <iostream>

class SignButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
public:
    SignButton(QWidget *parent = nullptr) : QPushButton(parent), duration{}
    {
        this->setFixedSize(SIGN_BUTTONS_SIZE);
        this->setText(SIGN_IN_BUTTON_NAME);
        QObject::connect(this, &QPushButton::clicked,this,  &leave);

        setBackground(QColor(PURPLE));
        setTextColor(QColor(WHITE));

        animBackColor = new QPropertyAnimation(this, "background");
        animTextColor = new QPropertyAnimation(this, "textColor");
    }
    QColor getBackground() const
    {
        return background;
    }
    void setBackground(const QColor backColor)
    {
        background = backColor;
        this->setStyleSheet(QString{BUTTON_STYLE}.arg(backColor.red()).arg(backColor.green()).arg(backColor.blue()).arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()));
    }
    QColor getTextColor() const
    {
        return textColor;
    }
    void setTextColor(const QColor tColor)
    {
        textColor = tColor;
        this->setStyleSheet(QString{BUTTON_STYLE}.arg(background.red()).arg(background.green()).arg(background.blue()).arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()));
    }
    void setDuration(int duration) noexcept
    {
        this->duration = duration;
        animBackColor->setDuration(duration);
        animTextColor->setDuration(duration);
    }
    int getDuration() const noexcept
    {
        return duration;
    }

private:
    QColor background;
    QColor textColor;
    QPropertyAnimation *animBackColor;
    QPropertyAnimation *animTextColor;
    int duration;

    void leaveEvent(QEvent *event)
    {
        leave();
    }
    void enterEvent(QEvent *event)
    {
        enter();
    }

private slots:

    void leave()
    {
        animBackColor->setEndValue(QColor(PURPLE));
        animTextColor->setEndValue(QColor(WHITE));
        animBackColor->start();
        animTextColor->start();
    }

    void enter()
    {
        animBackColor->setEndValue(QColor(WHITE));
        animTextColor->setEndValue(QColor(PURPLE));
        animBackColor->start();
        animTextColor->start();
    }
};
#endif