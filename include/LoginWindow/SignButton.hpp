#ifndef SIGN_BUTTON
#define SIGN_BUTTON

#include <QPushButton>
#include "../StyleLoader/StyleLoader.hpp"

#define STYLES_FILE_NAME "styles/Styles.qss"
#define SIGN_IN "Sign In"
#define SIGN_UP "Sign Up"
#define TRANSPARENT QColor(255, 255, 255, 0)
#define PURPLE QColor(81, 45, 168)
#define WHITE QColor(255, 255, 255)
#define WHITE_VISIBLE_BACKGROUND QColor(255, 255, 255, 255)
#define SIGN_BUTTON_HOVER_DURATION 400

class SignButton final : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor currentBackground READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor currentTextColor READ getTextColor WRITE setTextColor)
public:
    SignButton(QWidget *parent = nullptr) : QPushButton(parent),
                                            hoverDuration{SIGN_BUTTON_HOVER_DURATION},
                                            hoverActive{false},
                                            buttonStyle{""},
                                            currentBackground{WHITE},
                                            currentTextColor{QColor(Qt::black)},
                                            startTextColor{QColor(Qt::black)},
                                            endTextColor{QColor(Qt::black)},
                                            startBackgroundColor{QColor(Qt::white)},
                                            endBackgroundColor{QColor(Qt::white)}
    {
        QObject::connect(this, &QPushButton::clicked, this, &cursorLeave);
        animBackColor = new QPropertyAnimation(this, "currentBackground");
        animTextColor = new QPropertyAnimation(this, "currentTextColor");
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

    void swapText() noexcept
    {
        if (text() == SIGN_IN)
        {
            setText(SIGN_UP);
            return;
        }
        if(text() == SIGN_UP)
        {
        setText(SIGN_IN);
        }
    }

    void setStartTextColor(const QColor &color) noexcept
    {
        setTextColor(color);
        startTextColor = color;
    }

    QColor getStartTextColor() const noexcept
    {
        return startTextColor;
    }

    void setEndTextColor(const QColor &color) noexcept
    {
        endTextColor = color;
    }

    QColor getEndTextColor() const noexcept
    {
        return endTextColor;
    }

    void setStartBackgroundColor(const QColor &color) noexcept
    {
        setBackground(color);
        startBackgroundColor = color;
    }

    QColor getStartBackgroundColor() const noexcept
    {
        return startBackgroundColor;
    }

    void setEndBackgroundColor(const QColor &color) noexcept
    {
        endBackgroundColor = color;
    }

    QColor getEndBackgroundColor() const noexcept
    {
        return endBackgroundColor;
    }

    void setButtonStyle(const QString &style)
    {
        buttonStyle = style;
    }

private:
    QString buttonStyle;
    QColor currentBackground;
    QColor currentTextColor;
    QColor startTextColor;
    QColor endTextColor;
    QColor startBackgroundColor;
    QColor endBackgroundColor;
    QPropertyAnimation *animBackColor;
    QPropertyAnimation *animTextColor;
    int hoverDuration;
    bool hoverActive;

    QColor getBackground() const
    {
        return currentBackground;
    }

    void setBackground(const QColor backColor)
    {
        currentBackground = backColor;
        this->setStyleSheet(buttonStyle.arg(backColor.red()).arg(backColor.green()).arg(backColor.blue()).arg(currentBackground.alpha()).arg(currentTextColor.red()).arg(currentTextColor.green()).arg(currentTextColor.blue()));
    }

    QColor getTextColor() const
    {
        return currentTextColor;
    }

    void setTextColor(const QColor &tColor)
    {
        currentTextColor = tColor;
        this->setStyleSheet(buttonStyle.arg(currentBackground.red()).arg(currentBackground.green()).arg(currentBackground.blue()).arg(currentBackground.alpha()).arg(currentTextColor.red()).arg(currentTextColor.green()).arg(currentTextColor.blue()));
    }

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
        setCursor(Qt::ArrowCursor);
        if (hoverActive)
        {
            animBackColor->setEndValue(startBackgroundColor);
            animTextColor->setEndValue(startTextColor);
            animBackColor->start();
            animTextColor->start();
        }
    }

    void cursorEnter()
    {
        setCursor(Qt::PointingHandCursor);
        if (hoverActive)
        {
            animBackColor->setEndValue(endBackgroundColor);
            animTextColor->setEndValue(endTextColor);
            animBackColor->start();
            animTextColor->start();
        }
    }

};

#endif