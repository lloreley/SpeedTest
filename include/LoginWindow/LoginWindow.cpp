#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(QSize(MIN_LOGIN_WINDOW_WIDHT, MIN_LOGIN_WINDOW_HEIGHT));
    slider = new LoginWindowSlider(this);
    slider->setDuration(DURATION_BASIC);
    slider->setSliderEasingCurve(SLIDER_EASING_CURVE_BASIC);
    slider->setButtonEasingCurve(BUTTON_EASING_CURVE_BASIC);
    QObject::connect(slider, &LoginWindowSlider::sliderSignInClicked, this, &isSliderSignInClicked);
    QObject::connect(slider, &LoginWindowSlider::sliderSignUpClicked, this, &isSliderSignUpClicked);
    slider->update();
}

LoginWindow::~LoginWindow(){}

void LoginWindow::isSliderSignUpClicked()
{
    QPropertyAnimation *sliderAnimation = new QPropertyAnimation(slider, "pos");
    sliderAnimation->setDuration(slider->getDuration());
    sliderAnimation->setEndValue(QPoint(-SLIDER_BORDER_RADIUS, 0));
    sliderAnimation->setEasingCurve(slider->getSliderEasingCurve());
    sliderAnimation->start();
    slider->swap();
}

void LoginWindow::isSliderSignInClicked()
{
    QPropertyAnimation *sliderAnimation = new QPropertyAnimation(slider, "pos");
    sliderAnimation->setDuration(slider->getDuration());
    sliderAnimation->setEndValue(QPoint(slider->width() - SLIDER_BORDER_RADIUS, 0));
    sliderAnimation->setEasingCurve(slider->getSliderEasingCurve());
    sliderAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    slider->swap();
}
