#ifndef VANIMATED_TAB_BAR
#define VANIMATED_TAB_BAR

#include "AnimatedTabBar.hpp"

class VAnimatedTabBar : public TabBar::AnimatedTabBar
{

    Q_OBJECT
public:
    VAnimatedTabBar(QSize tab_size, int tab_count, double compare_coefficient = 1.5, QWidget *parent = nullptr);
    ~VAnimatedTabBar(){};

    bool setSide(side_t side) override;
    private:
};
#endif