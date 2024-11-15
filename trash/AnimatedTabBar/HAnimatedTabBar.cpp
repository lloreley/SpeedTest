#include "../../include/AnimatedTabBar/HAnimatedTabBar.hpp"

HAnimatedTabBar::HAnimatedTabBar(QSize tab_size, int tab_count, double compare_coefficient, QWidget *parent)
    : AnimatedTabBar([]() -> QBoxLayout *
                     { return new QHBoxLayout; }, tab_size, tab_count, compare_coefficient, parent)
{

    layout->setContentsMargins(0, 0, tabSize.rwidth(), 0);

    for (int i = 0; i < tabCount; ++i)
    {
        qobject_cast<QHBoxLayout *>(layout)->setAlignment(layout->itemAt(i)->widget(), Qt::AlignBottom);
    }
    side = TabBar::TOP_S;
    this->setFixedHeight(tabSize.rheight() * compareCoefficient);
}

bool HAnimatedTabBar::setSide(side_t side)
{
    Qt::Alignment align;
    switch (side)
    {
    case TabBar::BOTTOM_S:
        align = Qt::AlignTop;
        break;
    case TabBar::TOP_S:
        align = Qt::AlignBottom;
        break;
    default:
        return false;
    }
    this->side = side;
    for (int i = 0; i < tabCount; ++i)
    {
        qobject_cast<QHBoxLayout *>(layout)->setAlignment(layout->itemAt(i)->widget(), align);
    }
    return true;
}