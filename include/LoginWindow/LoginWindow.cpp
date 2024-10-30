#include "LoginWindow.hpp"

LoginWindowSlider::LoginWindowSlider(QWidget *parent) : QWidget(parent), duration{}, sliderEasingCurve{QEasingCurve::Linear}, buttonEasingCurve{sliderEasingCurve}
{
    this->setGeometry(QRect(-SLIDER_BORDER_RADIUS, 0, MIN_LOGIN_WINDOW_WIDHT / 2 + SLIDER_BORDER_RADIUS, MIN_LOGIN_WINDOW_HEIGHT));

    signButton = new QPushButton(this);
    signButton->setStyleSheet(BUTTON_STYLE);
    signButton->setFixedSize(SIGN_BUTTONS_SIZE);
    signButton->setText(SIGN_IN_BUTTON_NAME);
    QObject::connect(signButton, &QPushButton::clicked, this, &isSliderSignButtonClicked);

    centralChildLayout = new QVBoxLayout;
    centralChildLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    centralChildLayout->setSpacing(0);
    centralChildLayout->addWidget(signButton);

    leftSpace = new QWidget(this);
    leftSpace->setFixedWidth(SLIDER_BORDER_RADIUS);
    rigthSpace = new QWidget(this);
    rigthSpace->setFixedWidth(0);

    QObject::connect(this, &buttonSwapTextToSignIn, this, &LoginWindowSlider::isSliderMovingToLeft);
    QObject::connect(this, &buttonSwapTextToSignUp, this, &LoginWindowSlider::isSliderMovingToRight);

    sliderLayout = new QHBoxLayout(this);
    sliderLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    sliderLayout->setSpacing(0);
    sliderLayout->addWidget(leftSpace);
    sliderLayout->addLayout(centralChildLayout);
    sliderLayout->addWidget(rigthSpace);
    sliderLayout->setAlignment(Qt::AlignCenter);
}

LoginWindowSlider::~LoginWindowSlider()
{
}

void LoginWindowSlider::isSliderSignButtonClicked()
{
    if (signButton->text() == SIGN_IN_BUTTON_NAME)
    {
        emit sliderSignInClicked();
        return;
    }
    emit sliderSignUpClicked();
}

void LoginWindowSlider::isSliderMovingToLeft()
{
    QPropertyAnimation *leftSpaceAnimation = new QPropertyAnimation(leftSpace, "minimumWidth");
    leftSpaceAnimation->setDuration(duration);
    leftSpaceAnimation->setEasingCurve(buttonEasingCurve);
    leftSpaceAnimation->setEndValue(SLIDER_BORDER_RADIUS);
    leftSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QPropertyAnimation *rigthSpaceAnimation = new QPropertyAnimation(rigthSpace, "minimumWidth");
    rigthSpaceAnimation->setDuration(duration);
    rigthSpaceAnimation->setEasingCurve(buttonEasingCurve);
    rigthSpaceAnimation->setEndValue(0);
    rigthSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindowSlider::isSliderMovingToRight()
{
    QPropertyAnimation *leftSpaceAnimation = new QPropertyAnimation(leftSpace, "minimumWidth");
    leftSpaceAnimation->setDuration(duration);
    leftSpaceAnimation->setEasingCurve(buttonEasingCurve);
    leftSpaceAnimation->setEndValue(0);
    leftSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QPropertyAnimation *rigthSpaceAnimation = new QPropertyAnimation(rigthSpace, "minimumWidth");
    rigthSpaceAnimation->setDuration(duration);
    rigthSpaceAnimation->setEasingCurve(buttonEasingCurve);
    rigthSpaceAnimation->setEndValue(SLIDER_BORDER_RADIUS);
    rigthSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindowSlider::setDuration(int duration) noexcept
{
    this->duration = duration;
}

int LoginWindowSlider::getDuration() const noexcept
{
    return duration;
}

void LoginWindowSlider::setButtonEasingCurve(QEasingCurve easingCurve)
{
    this->buttonEasingCurve = easingCurve;
}

QEasingCurve LoginWindowSlider::getButtonEasingCurve() const noexcept
{
    return buttonEasingCurve;
}

void LoginWindowSlider::setSliderEasingCurve(QEasingCurve easingCurve)
{
    this->sliderEasingCurve = easingCurve;
}

QEasingCurve LoginWindowSlider::getSliderEasingCurve() const noexcept
{
    return sliderEasingCurve;
}

void LoginWindowSlider::swapSignText() noexcept
{
    if (signButton->text() == SIGN_IN_BUTTON_NAME)
    {
        signButton->setText(SIGN_UP_BUTTON_NAME);
        emit buttonSwapTextToSignUp();
        return;
    }
    signButton->setText(SIGN_IN_BUTTON_NAME);
    emit buttonSwapTextToSignIn();
}

void LoginWindowSlider::paintEvent(QPaintEvent *event)
{
    setUpdatesEnabled(false);
    QRect rect = this->rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(rect, SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS);
    QBrush brush(PURPLE_COLOR);
    painter.setPen(QPen(PURPLE_COLOR));
    painter.fillPath(path, brush);
    painter.drawPath(path);

    setUpdatesEnabled(true);
}

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(QSize(MIN_LOGIN_WINDOW_WIDHT, MIN_LOGIN_WINDOW_HEIGHT));
    slider = new LoginWindowSlider(this);
    slider->setDuration(DURATION_BASIC);
    slider->setSliderEasingCurve(SLIDER_EASING_CURVE_BASIC);
    slider->setButtonEasingCurve(BUTTON_EASING_CURVE_BASIC);
    QObject::connect(slider, &LoginWindowSlider::sliderSignInClicked, this, &isSliderSignInClicked);
    QObject::connect(slider, &LoginWindowSlider::sliderSignUpClicked, this, &isSliderSignUpClicked);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::isSliderSignUpClicked()
{
    QPropertyAnimation *sliderAnimation = new QPropertyAnimation(slider, "pos");
    sliderAnimation->setDuration(slider->getDuration());
    sliderAnimation->setEndValue(QPoint(-SLIDER_BORDER_RADIUS, 0));
    sliderAnimation->setEasingCurve(slider->getSliderEasingCurve());
    sliderAnimation->start();
    slider->swapSignText();
}

void LoginWindow::isSliderSignInClicked()
{
    QPropertyAnimation *sliderAnimation = new QPropertyAnimation(slider, "pos");
    sliderAnimation->setDuration(slider->getDuration());
    sliderAnimation->setEndValue(QPoint(slider->width() - SLIDER_BORDER_RADIUS, 0));
    sliderAnimation->setEasingCurve(slider->getSliderEasingCurve());
    sliderAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    slider->swapSignText();
}
