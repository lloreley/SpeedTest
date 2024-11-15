#include "../../include/AnimatedTabBar/VAnimatedTabBar.hpp"

VAnimatedTabBar::VAnimatedTabBar(QSize tab_size, int tab_count, double compare_coefficient, QWidget *parent)
    : AnimatedTabBar([]() -> QBoxLayout *
                     { return new QVBoxLayout; }, tab_size, tab_count, compare_coefficient, parent)
{
    layout->setContentsMargins(0, 0, 0, tabSize.rwidth());
    for (int i = 0; i < tabCount; ++i)
    {
        qobject_cast<QVBoxLayout *>(layout)->setAlignment(layout->itemAt(i)->widget(), Qt::AlignLeft);
    }
    side = TabBar::RIGHT_S;
    this->setFixedWidth(tabSize.rwidth() * compareCoefficient);
}

bool VAnimatedTabBar::setSide(side_t side)
{

    Qt::Alignment align;
    switch (side)
    {
    case TabBar::RIGHT_S:
        align = Qt::AlignLeft;
        break;
    case TabBar::LEFT_S:
        align = Qt::AlignRight;
        break;
    default:
        return false;
    }
    this->side = side;
    for (int i = 0; i < tabCount; ++i)
    {
        qobject_cast<QVBoxLayout *>(layout)->setAlignment(layout->itemAt(i)->widget(), align);
    }
    return true;
}