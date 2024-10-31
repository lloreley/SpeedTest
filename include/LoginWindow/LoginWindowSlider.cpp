#include "LoginWindowSlider.hpp"

LoginWindowSlider::LoginWindowSlider(QWidget *parent) : QWidget(parent), duration{}, sliderEasingCurve{QEasingCurve::Linear}, buttonEasingCurve{sliderEasingCurve}
{
    this->setGeometry(QRect(-SLIDER_BORDER_RADIUS, 0, MIN_LOGIN_WINDOW_WIDHT / 2 + SLIDER_BORDER_RADIUS, MIN_LOGIN_WINDOW_HEIGHT));

    signButton = new SignButton(this);
    QObject::connect(signButton, &QPushButton::clicked, this, &isSliderSignButtonClicked);
    signButton->setDuration(400);

    greetingLabel = new QLabel(this);
    greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
    greetingLabel->setStyleSheet(GREATING_LABEL_STYLE);

    additionalLabel = new QLabel(this);
    additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
    additionalLabel->setStyleSheet(ADDITIONAL_LABEL_STYLE);
    additionalLabel->setMinimumWidth(ADDITIONAL_LABEL_MIN_WIGTH);
    additionalLabel->setWordWrap(true);
    additionalLabel->setAlignment(Qt::AlignHCenter);

    centralChildLayout = new QVBoxLayout;
    centralChildLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);

    centralChildLayout->setSpacing(CENTRAL_LAYOUT_SPACING);
    centralChildLayout->addWidget(greetingLabel);
    centralChildLayout->addWidget(additionalLabel);
    centralChildLayout->addWidget(signButton);
    for (int i = 0; i < centralChildLayout->count(); ++i)
    {
        centralChildLayout->setAlignment(centralChildLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    }

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

void LoginWindowSlider::swapGreetinLabelText() noexcept
{
    if (greetingLabel->text() == GREETIN_LABEL_TEXT_BACK)
    {
        greetingLabel->setText(GREETIN_LABEL_TEXT_HELLO);
        return;
    }
    greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
}

void LoginWindowSlider::swapAdditionalLabelText() noexcept
{
    if (additionalLabel->text() == ADDITIONAL_LABEL_TEXT_BACK)
    {
        additionalLabel->setText(ADDITIONAL_LABEL_TEXT_HELLO);
        return;
    }
    additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
}

void LoginWindowSlider::swap()
{
    swapSignText();
    swapGreetinLabelText();
    swapAdditionalLabelText();
}

void LoginWindowSlider::paintEvent(QPaintEvent *event)
{
    QRect rect = this->rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(rect, SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS);
    QBrush brush(PURPLE_SLIDER_COLOR);
    painter.setPen(QPen(PURPLE_SLIDER_COLOR));
    painter.fillPath(path, brush);
    painter.drawPath(path);
}
