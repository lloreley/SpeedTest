#include "test.hpp"

QColor ChromeButtom::getBackground() const
{
    return background;
}

void ChromeButtom::setBackground(const QColor &back)
{
    background = back;
    // установка цвета фона через qss (таблица стилей qt)
    this->setStyleSheet(QString{"background-color: rgb(%1, %2, %3);"}.arg(back.red()).arg(back.green()).arg(back.blue()));
}

ChromeButtom::ChromeButtom(QWidget *parent) : QPushButton(parent)
{
    // setText("hello");
    this->setFixedSize(100, 100);
    setBackground(QColor(Qt::gray));      // текущий цвет фона
    anim.setPropertyName("background");   // свойство для анимации
    anim.setTargetObject(this);           // свойство какого объекта
    anim.setDuration(200);                // продолжительность смены
    anim.setStartValue(QColor(Qt::gray)); // из какого цвета
    anim.setEndValue(QColor(Qt::white));  // в какой
}

void ChromeButtom::enterEvent(QEvent *)
{
    // начать анимированную смену свойства background
    anim.setDirection(QAbstractAnimation::Forward);
    anim.start();
}

void ChromeButtom::leaveEvent(QEvent *)
{
    // начать анимированную смену свойства background в обратном направлении
    anim.setDirection(QAbstractAnimation::Backward);
    anim.start();
}
