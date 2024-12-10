#include "../include/ButtonWithHover.h"

ButtonWithHover::ButtonWithHover(QWidget *parent = nullptr) : QPushButton(parent),
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
ButtonWithHover::~ButtonWithHover()
{
    animBackColor->deleteLater();
    animBackColor->deleteLater();
}
void ButtonWithHover::setHoverDuration(int hoverDuration) noexcept
{
    this->hoverDuration = hoverDuration;
    animBackColor->setDuration(hoverDuration);
    animTextColor->setDuration(hoverDuration);
}
void ButtonWithHover::setHoverActive(bool value)
{
    hoverActive = value;
}
void ButtonWithHover::setStartTextColor(const QColor &color) noexcept
{
    setTextColor(color);
    startTextColor = color;
}
void ButtonWithHover::setEndTextColor(const QColor &color) noexcept
{
    endTextColor = color;
}
void ButtonWithHover::setStartBackgroundColor(const QColor &color) noexcept
{
    setBackground(color);
    startBackgroundColor = color;
}
void ButtonWithHover::setEndBackgroundColor(const QColor &color) noexcept
{
    endBackgroundColor = color;
}
void ButtonWithHover::setButtonStyle(const QString &style)
{
    buttonStyle = style;
}
void ButtonWithHover::upldateIconColor()
{
    QPixmap pixmap = icon().pixmap(this->size());
    QPixmap coloredPixmap(pixmap.size());
    coloredPixmap.fill(Qt::transparent);
    QPainter painter(&coloredPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0, 0, pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(coloredPixmap.rect(), currentTextColor);
    painter.end();
    this->setIcon(coloredPixmap);
}
void ButtonWithHover::swapText() noexcept
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

QColor ButtonWithHover::getBackground() const
{
    return currentBackground;
}
void ButtonWithHover::setBackground(const QColor backColor)
{
    currentBackground = backColor;
    this->setStyleSheet(buttonStyle.arg(backColor.red()).arg(backColor.green()).arg(backColor.blue()).arg(currentBackground.alpha()).arg(currentTextColor.red()).arg(currentTextColor.green()).arg(currentTextColor.blue()));
}
QColor ButtonWithHover::getTextColor() const
{
    return currentTextColor;
}
void ButtonWithHover::setTextColor(const QColor &tColor)
{
    currentTextColor = tColor;
    if (!icon().isNull())
    {
        this->upldateIconColor();
    }
    this->setStyleSheet(buttonStyle.arg(currentBackground.red()).arg(currentBackground.green()).arg(currentBackground.blue()).arg(currentBackground.alpha()).arg(currentTextColor.red()).arg(currentTextColor.green()).arg(currentTextColor.blue()));
}

void ButtonWithHover::leaveEvent(QEvent *event)
{
    cursorLeave();
    QPushButton::leaveEvent(event);
}
void ButtonWithHover::enterEvent(QEvent *event)
{
    cursorEnter();
    QPushButton::leaveEvent(event);
}
void ButtonWithHover::cursorLeave()
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
void ButtonWithHover::cursorEnter()
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
