#ifndef NOVIGATION_PAGE_H
#define NOVIGATION_PAGE_H

#include <QGridLayout>
#include "Page.h"
#include "ButtonWithHover.h"

class NavigationPanel final : public Page
{
public:
    NavigationPanel(QWidget *parent = nullptr);
    ~NavigationPanel();
    ButtonWithHover *accountButton();
    ButtonWithHover *typingTestButton();
    ButtonWithHover *typingLessonsButton();
    ButtonWithHover *logoutButton();

private:
    void setup();
    ButtonWithHover *createAccoutButton();
    ButtonWithHover *createLogoutButton();
    ButtonWithHover *createTypingTestButton();
    ButtonWithHover *createTypingLessonsButton();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif
