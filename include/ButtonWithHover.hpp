#ifndef BUTTON_WITH_HOVER_HPP
#define BUTTON_WITH_HOVER_HPP

#include <QPushButton>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QPainter>
#include "DataBase/UserDataBase.hpp"
#include "defines.hpp"

class ButtonWithHover final : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor currentBackground READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor currentTextColor READ getTextColor WRITE setTextColor)
public:
    ButtonWithHover(QWidget *parent = nullptr) : QPushButton(parent),
                                                 hoverDuration{},
                                                 hoverActive{false},
                                                 buttonStyle{""},
                                                 currentBackground{GRAY},
                                                 currentTextColor{QColor(Qt::black)},
                                                 startTextColor{QColor(Qt::black)},
                                                 endTextColor{QColor(Qt::black)},
                                                 startBackgroundColor{GRAY},
                                                 endBackgroundColor{GRAY}
    {
        QObject::connect(this, &QPushButton::clicked, this, &cursorLeave);
        animBackColor = new QPropertyAnimation(this, "currentBackground");
        animTextColor = new QPropertyAnimation(this, "currentTextColor");
        CHECK_PTR(animBackColor)
        CHECK_PTR(animTextColor)
    }

    void setHoverDuration(int hoverDuration) noexcept
    {
        this->hoverDuration = hoverDuration;
        animBackColor->setDuration(hoverDuration);
        animTextColor->setDuration(hoverDuration);
    }

    void setHoverActive(bool value)
    {
        hoverActive = value;
    }

    void setStartTextColor(const QColor &color) noexcept
    {
        setTextColor(color);
        startTextColor = color;
    }

    void setEndTextColor(const QColor &color) noexcept
    {
        endTextColor = color;
    }

    void setStartBackgroundColor(const QColor &color) noexcept
    {
        setBackground(color);
        startBackgroundColor = color;
    }

    void setEndBackgroundColor(const QColor &color) noexcept
    {
        endBackgroundColor = color;
    }

    void setButtonStyle(const QString &style)
    {
        buttonStyle = style;
    }

    void upldateIconColor()
    {
        QPixmap pixmap = icon().pixmap(this->size());
        QPixmap coloredPixmap(pixmap.size());
        coloredPixmap.fill(Qt::transparent); // Заполняем прозрачным цветом
        QPainter painter(&coloredPixmap);
        painter.setCompositionMode(QPainter::CompositionMode_Source);   // Устанавливаем режим наложения
        painter.drawPixmap(0, 0, pixmap);                               // Рисуем оригинальный pixmap
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn); // Устанавливаем режим наложения
        painter.fillRect(coloredPixmap.rect(), currentTextColor);       // Заполняем цветом
        painter.end();
        this->setIcon(coloredPixmap);
    }

    void swapText() noexcept
    {
        if (text() == SIGN_IN)
        {
            setText(SIGN_UP);
            return;
        }
        if (text() == SIGN_UP)
        {
            setText(SIGN_IN);
        }
    }

private:
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
        if (!icon().isNull())
        {
            this->upldateIconColor();
        }
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
};

#endif