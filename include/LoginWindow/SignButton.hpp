#ifndef SIGN_BUTTON
#define SIGN_BUTTON

#include <QPushButton>

#define SIGN_BUTTONS_SIZE QSize(190, 80)
#define SIGN_IN "Sign In"
#define SIGN_UP "Sign Up"
#define SIGN_BUTTON_STYLE "background-color:rgb(%1, %2, %3);color: rgb(%4, %5, %6);font-size: 24px; border: 2px solid; border-color:white;border-radius: 26px;font-weight: 600;font-family: 'Montserrat', sans-serif;"
#define PURPLE QColor(81, 45, 168)
#define WHITE QColor(255, 255, 255)
#define SIGN_BUTTON_HOVER_DURATION 400

class SignButton final : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
public:
    SignButton(QWidget *parent = nullptr) : QPushButton(parent), hoverDuration{SIGN_BUTTON_HOVER_DURATION}, hoverActive{true}
    {
        this->setFixedSize(SIGN_BUTTONS_SIZE);
        this->setText(SIGN_IN);
        QObject::connect(this, &QPushButton::clicked, this, &cursorLeave);

        setBackground(PURPLE);
        setTextColor(WHITE);

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
        this->setStyleSheet(QString{SIGN_BUTTON_STYLE}.arg(backColor.red()).arg(backColor.green()).arg(backColor.blue()).arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()));
    }

    QColor getTextColor() const
    {
        return textColor;
    }

    void setTextColor(const QColor tColor)
    {
        textColor = tColor;
        this->setStyleSheet(QString{SIGN_BUTTON_STYLE}.arg(background.red()).arg(background.green()).arg(background.blue()).arg(textColor.red()).arg(textColor.green()).arg(textColor.blue()));
    }

    void setHoverDuration(int hoverDuration) noexcept
    {
        this->hoverDuration = hoverDuration;
        animBackColor->setDuration(hoverDuration);
        animTextColor->setDuration(hoverDuration);
    }

    int getHoverDuration() const noexcept
    {
        return hoverDuration;
    }

    bool getHoverActive()
    {
        return hoverActive;
    }

    void setHoverActive(bool value)
    {
        hoverActive = value;
    }

private:
    QColor background;
    QColor textColor;
    QPropertyAnimation *animBackColor;
    QPropertyAnimation *animTextColor;
    int hoverDuration;
    bool hoverActive;

    void leaveEvent(QEvent *event)
    {
        cursorLeave();
    }
    void enterEvent(QEvent *event)
    {
        cursorEnter();
    }

private slots:

    void cursorLeave()
    {
        if (hoverActive)
        {
            animBackColor->setEndValue(PURPLE);
            animTextColor->setEndValue(WHITE);
            animBackColor->start();
            animTextColor->start();
        }
    }

    void cursorEnter()
    {
        if (hoverActive)
        {
            animBackColor->setEndValue(WHITE);
            animTextColor->setEndValue(PURPLE);
            animBackColor->start();
            animTextColor->start();
        }
    }
};
#endif