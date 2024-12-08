#ifndef PAGE_HPP
#define PAGE_HPP

#include <QFrame>
#include <QGraphicsOpacityEffect>
#include "../ButtonWithHover.hpp"

class Page : public QFrame
{
    Q_OBJECT
public:
    Page(QWidget *parent = nullptr) : QFrame(parent) { hide(); }

    static ButtonWithHover *createBaseButton(QWidget *parent = nullptr)
    {
        ButtonWithHover *btn = new ButtonWithHover(parent);
        CHECK_PTR(btn)
        btn->setProperty(BASE_BUTTONS_PROPERTY);
        btn->setButtonStyle(UserDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH, QString(BASE_BUTTONS_CLASS_NAME)));
        btn->setHoverActive(true);
        btn->setStartBackgroundColor(TRANSPARENT);
        btn->setEndBackgroundColor(TRANSPARENT);
        btn->setStartTextColor(MEDIUM_GRAY);
        btn->setEndTextColor(WHITE);
        return btn;
    }

    void hide()
    {
        QWidget::hide();
        emit hidden();
    }

signals:
    void hidden();
};

#endif