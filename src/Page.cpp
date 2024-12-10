#include "../include/Page.h"

ButtonWithHover *Page::createBaseButton(QWidget *parent)
{
    ButtonWithHover *btn = new ButtonWithHover(parent);
    CHECK_PTR(btn)
    btn->setProperty(BASE_BUTTONS_PROPERTY);
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH, QString(BASE_BUTTONS_CLASS_NAME)));
    btn->setHoverActive(true);
    btn->setStartBackgroundColor(TRANSPARENT);
    btn->setEndBackgroundColor(TRANSPARENT);
    btn->setStartTextColor(MEDIUM_GRAY);
    btn->setEndTextColor(WHITE);
    return btn;
}
void Page::hide()
{
    QWidget::hide();
    emit hidden();
}