#ifndef HANIMATED_TAB_BAR
#define HANIMATED_TAB_BAR

#include "AnimatedTabBar.hpp"
class HAnimatedTabBar : public TabBar::AnimatedTabBar
{
    Q_OBJECT

public:
    HAnimatedTabBar(QSize tab_size, int tab_count, double compare_coefficient = 1.5, QWidget *parent = nullptr);
    ~HAnimatedTabBar(){};

    bool setSide(side_t side) override;

private:
};

#endif