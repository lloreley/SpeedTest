#include "LoginWindowSlider.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Slider::Slider(QWidget *parent) : QWidget(parent), duration{DURATION_BASIC}, sliderEasingCurve{SLIDER_EASING_CURVE_BASIC}
{
    setGeometry(QRect(0, 0, MIN_SLIDER_WIDTH, MIN_SLIDER_HEIGHT));
    signButton = new SignButton(this);
    QObject::connect(signButton, &QPushButton::clicked, this, &isSliderSignButtonClicked);

    sliderLayout = new QVBoxLayout(this);
    sliderLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    sliderLayout->setSpacing(LAYOUT_SPACING);
    sliderLayout->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &Slider::timeout);
}

Slider::~Slider() {}

void Slider::setDuration(int duration) noexcept
{
    this->duration = duration;
}

int Slider::getDuration() const noexcept
{
    return duration;
}

void Slider::setSliderEasingCurve(QEasingCurve easingCurve)
{
    this->sliderEasingCurve = easingCurve;
}

QEasingCurve Slider::getSliderEasingCurve() const noexcept
{
    return sliderEasingCurve;
}

void Slider::swapSignText() noexcept
{
    if (signButton->text() == SIGN_IN)
    {
        signButton->setText(SIGN_UP);
        return;
    }
    signButton->setText(SIGN_IN);
}

void Slider::timeout()
{
    timer->stop();
}

void Slider::paintEvent(QPaintEvent *pe)
{
    if (timer->isActive())
    {
        this->setUpdatesEnabled(false);
    }
    QStyleOption o;
    o.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    this->setUpdatesEnabled(true);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(BorderRadii)

QVariant myBorderInterpolator(const BorderRadii &start, const BorderRadii &end, qreal progress)
{
    BorderRadii result(
        start.left_top + (end.left_top - start.left_top) * progress,
        start.left_bottom + (end.left_bottom - start.left_bottom) * progress,
        start.right_top + (end.right_top - start.right_top) * progress,
        start.right_bottom + (end.right_bottom - start.right_bottom) * progress);
    return QVariant::fromValue(result);
}

LoginWindowSlider::LoginWindowSlider(QWidget *parent) : Slider(parent), borderRadii{ZERO_BORDER_RADII}
{
    qRegisterAnimationInterpolator<BorderRadii>(myBorderInterpolator);
    move(SLIDER_LEFT_POS);
    greetingLabel = new QLabel(this);
    greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
    greetingLabel->setStyleSheet(GREATING_LABEL_STYLE);
    additionalLabel = new QLabel(this);
    additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
    additionalLabel->setStyleSheet(ADDITIONAL_LABEL_STYLE);
    additionalLabel->setMinimumWidth(ADDITIONAL_LABEL_MIN_WIDTH);
    additionalLabel->setWordWrap(true);
    additionalLabel->setAlignment(Qt::AlignHCenter);

    sliderLayout->addWidget(greetingLabel);
    sliderLayout->addWidget(additionalLabel);
    sliderLayout->addWidget(signButton);
    for (int i = 0; i < sliderLayout->count(); ++i)
    {
        sliderLayout->setAlignment(sliderLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    }
    setBorderRadii(LEFT_BORDER_RADII);
}

LoginWindowSlider::~LoginWindowSlider()
{
}

void LoginWindowSlider::isMoveToLeft()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_LEFT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *sliderBorderAnimation = new QPropertyAnimation(this, "borderRadii");
    sliderBorderAnimation->setDuration(duration);
    sliderBorderAnimation->setEndValue(QVariant::fromValue(LEFT_BORDER_RADII));
    sliderBorderAnimation->setEasingCurve(QEasingCurve::OutQuad);
    sliderBorderAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    swap();

    emit moveToLeft();
}

void LoginWindowSlider::isMoveToRight()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_RIGHT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *sliderBorderAnimation = new QPropertyAnimation(this, "borderRadii");
    sliderBorderAnimation->setDuration(duration);
    sliderBorderAnimation->setEndValue(QVariant::fromValue(RIGHT_BORDER_RADII));
    sliderBorderAnimation->setEasingCurve(QEasingCurve::OutQuad);
    sliderBorderAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    swap();
    emit moveToRight();
}

BorderRadii LoginWindowSlider::getBorderRadii()
{
    return borderRadii;
}

void LoginWindowSlider::setBorderRadii(BorderRadii borRadii)
{
    this->borderRadii = borRadii;
    this->setStyleSheet(QString{SLIDER_STYLE_WITH_BORDER_RADII}.arg(borderRadii.left_top).arg(borderRadii.left_bottom).arg(borderRadii.right_top).arg(borderRadii.right_bottom));
}

void LoginWindowSlider::isSliderSignButtonClicked()
{
    timer->start(duration);
    if (signButton->text() == SIGN_IN)
    {
        isMoveToRight();
        return;
    }
    isMoveToLeft();
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoginBar::LoginBar(QWidget *parent) : Slider(parent)
{
    move(SLIDER_RIGHT_POS);
    mainLabel = new QLabel(this);
    mainLabel->setStyleSheet(MAIN_LABEL_LOGIN_TAB);
    mainLabel->setText(MAIN_LABEL_LOGIN_TAB_TEXT_HELLO);


    name = new QLineEdit(this);
    email = new QLineEdit(this);
    password = new QLineEdit(this);

    signButton->setHoverActive(false);
    swapSignText();
    signButton->setFixedHeight(60);


    name->setPlaceholderText(NAME_PLACEHOLDER_TEXT);
    name->setStyleSheet(LINE_EDIT_STYLE);
    email->setPlaceholderText(EMAIL_PLACEHOLDER_TEXT);
    email->setStyleSheet(LINE_EDIT_STYLE);
    password->setPlaceholderText(PASSWORD_PLACEHOLDER_TEXT);
    password->setStyleSheet(LINE_EDIT_STYLE);
    password->setEchoMode(QLineEdit::Password);


    sliderLayout->setSpacing(LOGIN_TAB_LAYOUT_SPACING);
    sliderLayout->addWidget(mainLabel);
    sliderLayout->addSpacing(LAYOUT_SPACING);
    sliderLayout->addWidget(name);
    sliderLayout->addWidget(email);
    sliderLayout->addWidget(password);
    sliderLayout->addWidget(signButton);
    for (int i = 0; i < sliderLayout->count(); ++i)
    {
        sliderLayout->setAlignment(sliderLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    }
}

void LoginBar::swap()
{

    swapMainLabelText();
    swapSignText();
}
void LoginBar::swapMainLabelText()
{
    if (mainLabel->text() == MAIN_LABEL_LOGIN_TAB_TEXT_BACK)
    {
        mainLabel->setText(MAIN_LABEL_LOGIN_TAB_TEXT_HELLO);
        return;
    }
    mainLabel->setText(MAIN_LABEL_LOGIN_TAB_TEXT_BACK);
}

void LoginBar::isSliderSignButtonClicked()
{
}

void LoginBar::isMoveToLeft()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_LEFT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    swap();
    email->hide();
    emit moveToLeft();
}

void LoginBar::isMoveToRight()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_RIGHT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    swap();
    email->show();
    emit moveToRight();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////