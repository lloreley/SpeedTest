#include "../../include/AnimatedTabBar/AnimatedTabBar.hpp"

// use my exception in 27 line
using namespace TabBar;

AnimatedTabBar::AnimatedTabBar(QBoxLayout *(*childLayoutAllocator)(), QSize tab_size, int tab_count, double compare_coefficient, QWidget *parent)
    : QWidget(parent), tabCount{tab_count}, tabSize{tab_size}, compareCoefficient{compare_coefficient}, duration{0}, easignCurve{QEasingCurve::Linear}
{
    layout = childLayoutAllocator();
    layout->setSpacing(ZERO_SPACING);

    for (int i = 0; i < tabCount; ++i)
    {
        QPushButton *btn = new QPushButton(this);
        btn->setFixedSize(tabSize);
        btn->installEventFilter(this);
        layout->addWidget(btn);
    }
    this->setLayout(layout);
}

AnimatedTabBar::~AnimatedTabBar()
{
    for(int i = 0; i < tabCount; ++i)
    {
        delete(layout->itemAt(i)->widget());
    }
    delete layout;
}

int AnimatedTabBar::getTabCount() const noexcept
{
    return this->tabCount;
}

QSize AnimatedTabBar::getTabSize() const noexcept
{
    return tabSize;
}

double AnimatedTabBar::getCoeffiient() const noexcept
{
    return compareCoefficient;
}

side_t AnimatedTabBar::getSide() const noexcept
{
    return side;
}

void AnimatedTabBar::setDuration(int duration) noexcept
{
    this->duration = duration;
}

int AnimatedTabBar::getDuration() const noexcept
{
    return duration;
}

QEasingCurve AnimatedTabBar::getEasingCurve() const noexcept
{
    return easignCurve;
}

void AnimatedTabBar::setEasignCurve(QEasingCurve easignCurve) noexcept
{
    this->easignCurve = easignCurve;
}

bool AnimatedTabBar::eventFilter(QObject *o, QEvent *e)
{
    for (int i = 0; i < tabCount; ++i)
    {
        if (qobject_cast<QWidget *>(o))
        {
            if (o == layout->itemAt(i)->widget())
            {
                if (e->type() == QEvent::Enter)
                {
                    isMouseEnterInButton(qobject_cast<QWidget *>(o));
                    return true;
                }
                if (e->type() == QEvent::Leave)
                {
                    isMouseLeaveFromButton(qobject_cast<QWidget *>(o));
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(o, e);
}

void AnimatedTabBar::isMouseEnterInButton(QWidget *button)
{

    QPropertyAnimation *animation = new QPropertyAnimation(button, side == TOP_S || side == BOTTOM_S ? "minimumHeight" : "minimumWidth");
    animation->setDuration(duration);
    animation->setEasingCurve(easignCurve);
    animation->setEndValue((side == TOP_S || side == BOTTOM_S ? tabSize.rheight() : tabSize.rwidth()) * compareCoefficient);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void AnimatedTabBar::isMouseLeaveFromButton(QWidget *button)
{
    QPropertyAnimation *animation = new QPropertyAnimation(button, side == TOP_S || side == BOTTOM_S ? "minimumHeight" : "minimumWidth");
    animation->setDuration(duration);
    animation->setEasingCurve(easignCurve);
    animation->setEndValue(side == TOP_S || side == BOTTOM_S ? tabSize.rheight() : tabSize.rwidth());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
