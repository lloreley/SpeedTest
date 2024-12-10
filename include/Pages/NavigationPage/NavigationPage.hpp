#ifndef NOVIGATION_PAGE_HPP
#define NOVIGATION_PAGE_HPP

#include <QGridLayout>
#include "../Page.hpp"
#include "../../ButtonWithHover.hpp"

class NavigationPanel final : public Page
{
public:
    NavigationPanel(QWidget *parent = nullptr) : Page(parent)
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
    ~NavigationPanel()
    {
        for (auto child : children())
        {
            child->deleteLater();
        }
    }

    ButtonWithHover *accountButton()
    {
        ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_ACCOUNT_BUTTON_OBJECT_NAME);
        CHECK_PTR(btn)
        return btn;
    }
    ButtonWithHover *typingTestButton()
    {
        ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_TYPING_TEST_BUTTON_OBJECT_NAME);
        CHECK_PTR(btn)
        return btn;
    }
    ButtonWithHover *typingLessonsButton()
    {
        ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_TYPING_LESSONS_BUTTON_OBJECT_NAME);
        CHECK_PTR(btn)
        return btn;
    }
    ButtonWithHover *logoutButton()
    {
        ButtonWithHover *btn = findChild<ButtonWithHover *>(NP_LOGOUT_BUTTON_OBJECT_NAME);
        CHECK_PTR(btn)
        return btn;
    }

private:
    ButtonWithHover *createAccoutButton()
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
    ButtonWithHover *createLogoutButton()
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
    ButtonWithHover *createTypingTestButton()
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
    ButtonWithHover *createTypingLessonsButton()
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

    void enterEvent(QEvent *event) override
    {
        QPropertyAnimation *anim = new QPropertyAnimation(this, "minimumWidth");
        CHECK_PTR(anim)
        anim->setEndValue(NAVIGATION_PANEL_MAX_WIDTH);
        anim->setDuration(NAVIGATION_PANEL_ANIMATION_DURATION);
        anim->setEasingCurve(NAVIGATION_PANEL_ANIMATION_EASIGN_CURVE);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    void leaveEvent(QEvent *event) override
    {
        QPropertyAnimation *anim = new QPropertyAnimation(this, "minimumWidth");
        CHECK_PTR(anim)
        anim->setEndValue(NAVIGATION_PANEL_MIN_WIDTH);
        anim->setDuration(NAVIGATION_PANEL_ANIMATION_DURATION);
        anim->setEasingCurve(NAVIGATION_PANEL_ANIMATION_EASIGN_CURVE);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
};

#endif
