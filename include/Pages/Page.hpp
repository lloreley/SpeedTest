#ifndef PAGE_HPP
#define PAGE_HPP

#include <QFrame>
#include <QGraphicsOpacityEffect>
class Page : public QFrame
{
    Q_OBJECT
public:
    Page(QWidget *parent = nullptr) : QFrame(parent)
    {
        opacity = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(opacity);
        opacityAnimation = new QPropertyAnimation(this->graphicsEffect(), "opacity");
        opacityAnimation->setDuration(PAGE_OPACITY_ANIMATION_DURATION);
    }

    void fade()
    {
        opacityAnimation->setStartValue(MAX_OPACITY);
        opacityAnimation->setEndValue(ZERO_OPACITY);
        opacityAnimation->start();
        connect(opacityAnimation, &QAbstractAnimation::finished, [this]()
                { emit faded();hide(); });
    }
    void appear()
    {
        this->show();
        opacityAnimation->setStartValue(ZERO_OPACITY);
        opacityAnimation->setEndValue(MAX_OPACITY);
        opacityAnimation->start();
        connect(opacityAnimation, &QAbstractAnimation::finished, [this]()
                { emit faded(); });
    }

protected:
    QPropertyAnimation *opacityAnimation;
    QGraphicsOpacityEffect *opacity;

signals:
    void faded();
    void appeared();
};

#endif