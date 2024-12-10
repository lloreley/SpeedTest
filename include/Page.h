#ifndef PAGE_H
#define PAGE_H

#include <QFrame>
#include <QGraphicsOpacityEffect>
#include "ButtonWithHover.h"

class Page : public QFrame
{
    Q_OBJECT
public:
    Page(QWidget *parent = nullptr) : QFrame(parent) { hide(); }
    static ButtonWithHover *createBaseButton(QWidget *parent = nullptr);
    void hide();

private:
    virtual void setup() = 0;
signals:
    void hidden();
};

#endif
