#ifndef BUTTON_WITH_HOVER_HPP
#define BUTTON_WITH_HOVER_HPP

#include <QPushButton>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QPainter>
#include "FileDataBase.h"
#include "defines.h"

class ButtonWithHover: public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor currentBackground READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor currentTextColor READ getTextColor WRITE setTextColor)
public:
    ButtonWithHover(QWidget *parent);
    ~ButtonWithHover();
    void setHoverDuration(int hoverDuration) noexcept;
    void setHoverActive(bool value);
    void setStartTextColor(const QColor &color) noexcept;
    void setEndTextColor(const QColor &color) noexcept;
    void setStartBackgroundColor(const QColor &color) noexcept;
    void setEndBackgroundColor(const QColor &color) noexcept;
    void setButtonStyle(const QString &style);
    void upldateIconColor();
    void swapText() noexcept;
    QColor getBackground() const;
    void setBackground(const QColor backColor);
    QColor getTextColor() const;
    void setTextColor(const QColor &tColor);

private:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void cursorLeave();
    void cursorEnter();

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
