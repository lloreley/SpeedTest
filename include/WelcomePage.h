#ifndef WELCOME_PAGE_H
#define WELCOME_PAGE_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include "defines.h"
#include "ButtonWithHover.h"
#include "Page.h"
class WelcomePage : public Page
{
    Q_OBJECT
public:
    WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();
    QLabel *greatingLabel();
    QLabel *additionalLabel();
    ButtonWithHover *leftButton();
    ButtonWithHover *rightButton();

private:
    void setup() override;
    QLabel *createGreatingLabel();
    QLabel *createAdditionalLabel();
    ButtonWithHover *createLeftButton();
    ButtonWithHover *createRightButton();

signals:
    void TypingTest();
    void TypingLessons();
};

#endif