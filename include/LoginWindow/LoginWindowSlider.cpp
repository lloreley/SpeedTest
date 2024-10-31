#include "LoginWindowSlider.hpp"



Q_DECLARE_METATYPE(BorderRadii)

QVariant myBorderInterpolator(const BorderRadii &start, const BorderRadii &end, qreal progress)
{
    BorderRadii result(
        start.left_top + (end.left_top - start.left_top) * progress,
        start.left_bottom + (end.left_bottom - start.left_bottom) * progress,
        start.right_top + (end.right_top - start.right_top) * progress,
        start.right_bottom + (end.right_bottom - start.right_bottom) * progress
    );
    return QVariant::fromValue(result);
}


LoginWindowSlider::LoginWindowSlider(QWidget *parent) :
QWidget(parent), //, duration{}, sliderEasingCurve{QEasingCurve::Linear}, 
// buttonEasingCurve{sliderEasingCurve}
borderRadii{0, 0, 0, 40}    /////
{
    qRegisterAnimationInterpolator<BorderRadii>(myBorderInterpolator);

    this->setGeometry(QRect(0, 0, MIN_LOGIN_WINDOW_WIDHT / 2 + SLIDER_BORDER_RADIUS, MIN_LOGIN_WINDOW_HEIGHT));
    this->setStyleSheet(QString{SLIDER_STYLE}.arg(borderRadii.left_top).arg(borderRadii.left_bottom).arg(borderRadii.right_top).arg(borderRadii.right_bottom));
    

    // QPropertyAnimation* anim = new QPropertyAnimation(this, "borderRadii");
    // anim->setDuration(10000);
    // anim->setEndValue(QVariant::fromValue(BorderRadii(50, 200, 300, 0)));
    // anim->start();

    // signButton = new SignButton(this);
    // QObject::connect(signButton, &QPushButton::clicked, this, &isSliderSignButtonClicked);
    // signButton->setHoverDuration(SIGN_BUTTON_HOVER_DURATION);

    // greetingLabel = new QLabel(this);
    // greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
    // greetingLabel->setStyleSheet(GREATING_LABEL_STYLE);

    // additionalLabel = new QLabel(this);
    // additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
    // additionalLabel->setStyleSheet(ADDITIONAL_LABEL_STYLE);
    // additionalLabel->setMinimumWidth(ADDITIONAL_LABEL_MIN_WIGTH);
    // additionalLabel->setWordWrap(true);
    // additionalLabel->setAlignment(Qt::AlignHCenter);

    // centralChildLayout = new QVBoxLayout;
    // centralChildLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);

    // centralChildLayout->setSpacing(CENTRAL_LAYOUT_SPACING);
    // centralChildLayout->addWidget(greetingLabel);
    // centralChildLayout->addWidget(additionalLabel);
    // centralChildLayout->addWidget(signButton);
    // for (int i = 0; i < centralChildLayout->count(); ++i)
    // {
    //     centralChildLayout->setAlignment(centralChildLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    // }
    // this->setBorderRadii(BorderRadii(200, 50, 10, 300));

    // leftSpace = new QWidget(this);
    // leftSpace->setFixedWidth(SLIDER_BORDER_RADIUS);
    // rigthSpace = new QWidget(this);
    // rigthSpace->setFixedWidth(0);
    // QObject::connect(this, &buttonSwapTextToSignIn, this, &LoginWindowSlider::isSliderMovingToLeft);
    // QObject::connect(this, &buttonSwapTextToSignUp, this, &LoginWindowSlider::isSliderMovingToRight);

    // sliderLayout = new QHBoxLayout(this);
    // sliderLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    // sliderLayout->setSpacing(0);
    // sliderLayout->addWidget(leftSpace);
    // sliderLayout->addLayout(centralChildLayout);
    // sliderLayout->addWidget(rigthSpace);
    // sliderLayout->setAlignment(Qt::AlignCenter);
}

LoginWindowSlider::~LoginWindowSlider()
{
}

void LoginWindowSlider::isSliderSignButtonClicked()
{
    if (signButton->text() == SIGN_IN)
    {
        emit sliderSignInClicked();
        return;
    }
    emit sliderSignUpClicked();
}

// void LoginWindowSlider::isSliderMovingToLeft()
// {
//     QPropertyAnimation *leftSpaceAnimation = new QPropertyAnimation(leftSpace, "minimumWidth");
//     leftSpaceAnimation->setDuration(duration);

//     leftSpaceAnimation->setEasingCurve(buttonEasingCurve);
//     leftSpaceAnimation->setEndValue(SLIDER_BORDER_RADIUS);
//     leftSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
//     QPropertyAnimation *rigthSpaceAnimation = new QPropertyAnimation(rigthSpace, "minimumWidth");
//     rigthSpaceAnimation->setDuration(duration);
//     rigthSpaceAnimation->setEasingCurve(buttonEasingCurve);
//     rigthSpaceAnimation->setEndValue(0);
//     rigthSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// }

// void LoginWindowSlider::isSliderMovingToRight()
// {
//     QPropertyAnimation *leftSpaceAnimation = new QPropertyAnimation(leftSpace, "minimumWidth");
//     leftSpaceAnimation->setDuration(duration);
//     leftSpaceAnimation->setEasingCurve(buttonEasingCurve);
//     leftSpaceAnimation->setEndValue(0);
//     leftSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
//     QPropertyAnimation *rigthSpaceAnimation = new QPropertyAnimation(rigthSpace, "minimumWidth");
//     rigthSpaceAnimation->setDuration(duration);
//     rigthSpaceAnimation->setEasingCurve(buttonEasingCurve);
//     rigthSpaceAnimation->setEndValue(SLIDER_BORDER_RADIUS);
//     rigthSpaceAnimation->start(QAbstractAnimation::DeleteWhenStopped);
// }

void LoginWindowSlider::setDuration(int duration) noexcept
{
    this->duration = duration;
}

int LoginWindowSlider::getDuration() const noexcept
{
    return duration;
}

// void LoginWindowSlider::setButtonEasingCurve(QEasingCurve easingCurve)
// {
//     this->buttonEasingCurve = easingCurve;
// }
// QEasingCurve LoginWindowSlider::getButtonEasingCurve() const noexcept
// {
//     return buttonEasingCurve;
// }

void LoginWindowSlider::setSliderEasingCurve(QEasingCurve easingCurve)
{
    this->sliderEasingCurve = easingCurve;
}

QEasingCurve LoginWindowSlider::getSliderEasingCurve() const noexcept
{
    return sliderEasingCurve;
}

BorderRadii LoginWindowSlider::getBorderRadii()
{
    return borderRadii;
}
void LoginWindowSlider::setBorderRadii(BorderRadii borRadii)
{
    this->borderRadii = borRadii;
    this->setStyleSheet(QString{SLIDER_STYLE}.arg(borderRadii.left_top).arg(borderRadii.left_bottom).arg(borderRadii.right_top).arg(borderRadii.right_bottom));
}

void LoginWindowSlider::swapSignText() noexcept
{
    if (signButton->text() == SIGN_IN)
    {
        signButton->setText(SIGN_UP);
        // emit buttonSwapTextToSignUp();
        return;
    }
    signButton->setText(SIGN_IN);
    // emit buttonSwapTextToSignIn();
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

void LoginWindowSlider::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(
        QStyle::PE_Widget, &o, &p, this);
};