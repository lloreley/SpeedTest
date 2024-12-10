#include "../include/NavigationPage.h"

NavigationPanel::NavigationPanel(QWidget *parent) : Page(parent)
{
    setup();
}
void NavigationPanel::setup()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    CHECK_PTR(layout)
    layout->addStretch();
    layout->addWidget(createTypingTestButton());
    layout->addWidget(createTypingLessonsButton());
    layout->addStretch();
    layout->addWidget(createLogoutButton());
    layout->addWidget(createAccoutButton());
    layout->setContentsMargins(NAVIGATION_PANEL_CONTENTS_MARGINS);
    setObjectName(NAVIGATION_PANEL_OBJECT_NAME);
    for (int i = 0; i < layout->count(); ++i)
    {
        layout->setAlignment(layout->itemAt(i)->widget(), Qt::AlignLeft);
    }
    layout->setAlignment(Qt::AlignLeft);
}
NavigationPanel::~NavigationPanel()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
ButtonWithHover *NavigationPanel::accountButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_ACCOUNT_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}
ButtonWithHover *NavigationPanel::typingTestButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_TYPING_TEST_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}
ButtonWithHover *NavigationPanel::typingLessonsButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_TYPING_LESSONS_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}
ButtonWithHover *NavigationPanel::logoutButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_LOGOUT_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}
ButtonWithHover *NavigationPanel::createAccoutButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    QIcon icon(ACCOUNT_ICON_PATH);
    btn->setObjectName(NP_ACCOUNT_BUTTON_OBJECT_NAME);
    btn->setIcon(icon);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    btn->setText(NP_ACCOUNT_BUTTON_TEXT);
    btn->setFixedWidth(150);
    return btn;
}
ButtonWithHover *NavigationPanel::createLogoutButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    QIcon icon(QUIT_BUTTON_ICON_PATH);
    btn->setObjectName(NP_LOGOUT_BUTTON_OBJECT_NAME);
    btn->setIcon(icon);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    btn->setText(NP_LOGOUT_BUTTON_TEXT);
    btn->setFixedWidth(150);
    return btn;
}
ButtonWithHover *NavigationPanel::createTypingTestButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    QIcon icon(KEYBOARD_ICON_PATH);
    btn->setObjectName(NP_TYPING_TEST_BUTTON_OBJECT_NAME);
    btn->setIcon(icon);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    btn->setText(NP_TYPING_TEST_BUTTON_TEXT);
    btn->setFixedWidth(150);
    return btn;
}
ButtonWithHover *NavigationPanel::createTypingLessonsButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    QIcon icon(BOOK_ICON_PATH);
    btn->setObjectName(NP_TYPING_LESSONS_BUTTON_OBJECT_NAME);
    btn->setIcon(icon);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    btn->setText(NP_TYPING_LESSONS_BUTTON_TEXT);
    btn->setFixedWidth(150);
    return btn;
}
void NavigationPanel::enterEvent(QEvent *event)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "minimumWidth");
    CHECK_PTR(anim)
    anim->setEndValue(NAVIGATION_PANEL_MAX_WIDTH);
    anim->setDuration(NAVIGATION_PANEL_ANIMATION_DURATION);
    anim->setEasingCurve(NAVIGATION_PANEL_ANIMATION_EASIGN_CURVE);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
void NavigationPanel::leaveEvent(QEvent *event)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "minimumWidth");
    CHECK_PTR(anim)
    anim->setEndValue(NAVIGATION_PANEL_MIN_WIDTH);
    anim->setDuration(NAVIGATION_PANEL_ANIMATION_DURATION);
    anim->setEasingCurve(NAVIGATION_PANEL_ANIMATION_EASIGN_CURVE);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}