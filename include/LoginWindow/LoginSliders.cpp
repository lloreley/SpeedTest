#include "LoginSliders.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Slider::Slider(QWidget *parent) : QWidget(parent), duration{SLIDER_DURATION}, sliderEasingCurve{SLIDER_EASING_CURVE}, sliderStyle{""}
{
    setGeometry(QRect(0, 0, MIN_SLIDER_WIDTH, MIN_SLIDER_HEIGHT));
    signButton = new SignButton(this);
    QObject::connect(signButton, &QPushButton::clicked, this, &isSliderSignButtonClicked);

    sliderLayout = new QVBoxLayout(this);
    sliderLayout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    sliderLayout->setSpacing(LAYOUT_SPACING);
    sliderLayout->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
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

MainSlider::MainSlider(QWidget *parent) : Slider(parent)
{
    qRegisterAnimationInterpolator<BorderRadii>(myBorderInterpolator);
    move(SLIDER_LEFT_POS);

    setObjectName("MainSlider");
    sliderStyle = StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#MainSlider");

    signButton->setObjectName("SliderButton");
    signButton->setButtonStyle(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#SliderButton"));
    signButton->setHoverActive(true);
    signButton->setStartBackgroundColor(TRANSPARENT);
    signButton->setEndBackgroundColor(WHITE);
    signButton->setText(SIGN_IN);
    signButton->setStartTextColor(WHITE);
    signButton->setEndTextColor(PURPLE);

    greetingLabel = new QLabel(this);
    greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
    greetingLabel->setObjectName("GreatingLabel");
    greetingLabel->setStyleSheet(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#GreatingLabel"));

    additionalLabel = new QLabel(this);
    additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
    additionalLabel->setObjectName("AdditionalLabel");
    additionalLabel->setStyleSheet(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#AdditionalLabel"));
    additionalLabel->setWordWrap(true);
    additionalLabel->setAlignment(Qt::AlignHCenter);

    sliderLayout->addWidget(greetingLabel);
    sliderLayout->addWidget(additionalLabel);
    sliderLayout->addWidget(signButton);
    for (int i = 0; i < sliderLayout->count(); ++i)
    {
        sliderLayout->setAlignment(sliderLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    }

    setBorderRadii(LEFT_POS_BORDER_RADII);

    QObject::connect(timer, &QTimer::timeout, this, &MainSlider::timeout);
}

MainSlider::~MainSlider() {}

void MainSlider::isMoveToLeft()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_LEFT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *sliderBorderAnimation = new QPropertyAnimation(this, "borderRadii");
    sliderBorderAnimation->setDuration(duration);
    sliderBorderAnimation->setEndValue(QVariant::fromValue(LEFT_POS_BORDER_RADII));
    sliderBorderAnimation->setEasingCurve(QEasingCurve::OutQuad);
    sliderBorderAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    swap();
    emit moveToLeft();
}

void MainSlider::isMoveToRight()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_RIGHT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *sliderBorderAnimation = new QPropertyAnimation(this, "borderRadii");
    sliderBorderAnimation->setDuration(duration);
    sliderBorderAnimation->setEndValue(QVariant::fromValue(RIGHT_POS_BORDER_RADII));
    sliderBorderAnimation->setEasingCurve(QEasingCurve::OutQuad);
    sliderBorderAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    swap();
    emit moveToRight();
}

BorderRadii MainSlider::getBorderRadii()
{
    return borderRadii;
}

void MainSlider::setBorderRadii(BorderRadii borRadii)
{
    this->borderRadii = borRadii;
    this->setStyleSheet(sliderStyle.arg(borderRadii.left_top).arg(borderRadii.left_bottom).arg(borderRadii.right_top).arg(borderRadii.right_bottom));
}

void MainSlider::isSliderSignButtonClicked()
{
    timer->start(duration);
    if (signButton->text() == SIGN_IN)
    {
        isMoveToRight();
        return;
    }
    isMoveToLeft();
}

void MainSlider::swapGreetinLabelText() noexcept
{
    if (greetingLabel->text() == GREETIN_LABEL_TEXT_BACK)
    {
        greetingLabel->setText(GREETIN_LABEL_TEXT_HELLO);
        return;
    }
    greetingLabel->setText(GREETIN_LABEL_TEXT_BACK);
}

void MainSlider::swapAdditionalLabelText() noexcept
{
    if (additionalLabel->text() == ADDITIONAL_LABEL_TEXT_BACK)
    {
        additionalLabel->setText(ADDITIONAL_LABEL_TEXT_HELLO);
        return;
    }
    additionalLabel->setText(ADDITIONAL_LABEL_TEXT_BACK);
}

void MainSlider::swap()
{
    signButton->swapText();
    swapGreetinLabelText();
    swapAdditionalLabelText();
}

void MainSlider::timeout()
{
    timer->stop();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LoginBar::LoginBar(QWidget *parent) : Slider(parent)
{
    this->setObjectName("LoginBar");

    label = new QLabel(this);

    QPixmap pixmap(LOGO_PATH);
    label->setPixmap(pixmap.scaled(QSize(300, 180), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label->setFixedHeight(100);
    label->setAlignment(Qt::AlignCenter);
    label->setContentsMargins(0, 0, 0, 0);

    move(SLIDER_RIGHT_POS);
    mainLabel = new QLabel(this);
    mainLabel->setObjectName("MainLabelLoginTab");
    mainLabel->setText(MAIN_LABEL_LOGIN_TAB_TEXT_HELLO);
    mainLabel->setStyleSheet(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#MainLabelLoginTab"));

    signButton->setObjectName("LoginButton");
    signButton->setButtonStyle(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "#LoginButton"));
    signButton->setHoverActive(true);
    signButton->setStartBackgroundColor(PURPLE);
    signButton->setEndBackgroundColor(QColor(92, 107, 192));
    signButton->setText(SIGN_UP);
    signButton->setStartTextColor(WHITE);
    signButton->setEndTextColor(WHITE);

    name = new QLineEdit(this);
    email = new QLineEdit(this);
    password = new QLineEdit(this);

    name->setProperty("class", "loginLineEdit");
    email->setProperty("class", "loginLineEdit");
    password->setProperty("class", "loginLineEdit");

    name->setPlaceholderText(NAME_PLACEHOLDER_TEXT);
    email->setPlaceholderText(EMAIL_PLACEHOLDER_TEXT);
    password->setPlaceholderText(PASSWORD_PLACEHOLDER_TEXT);
    password->setEchoMode(QLineEdit::Password);
    this->setStyleSheet(StyleLoader::loadStyleFromFile(STYLES_FILE_NAME, "QLineEdit.loginLineEdit"));

    sliderLayout->setSpacing(LOGIN_TAB_LAYOUT_SPACING);
    sliderLayout->addWidget(mainLabel);
    sliderLayout->addWidget(label);
    sliderLayout->addWidget(name);
    sliderLayout->addWidget(email);
    sliderLayout->addWidget(password);
    sliderLayout->addWidget(signButton);


    for (int i = 0; i < sliderLayout->count(); ++i)
    {
        sliderLayout->setAlignment(sliderLayout->itemAt(i)->widget(), Qt::AlignHCenter);
    }
    QObject::connect(timer, &QTimer::timeout, this, &LoginBar::timeout);
}

void LoginBar::swap()
{
    swapMainLabelText();
    signButton->swapText();
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

void LoginBar::isSliderSignButtonClicked() {}

void LoginBar::isMoveToLeft()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_LEFT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    
    timer->start(duration / 5.4);
    name->clear();
    email->clear();
    password->clear();
    name->setPlaceholderText(NAME_PLACEHOLDER_TEXT_AND_EMAIL);
    emit moveToLeft();
}

void LoginBar::isMoveToRight()
{
    QPropertyAnimation *sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setDuration(duration);
    sliderPosAnimation->setEndValue(SLIDER_RIGHT_POS);
    sliderPosAnimation->setEasingCurve(sliderEasingCurve);
    sliderPosAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    timer->start(duration / 5.4);


    name->clear();
    email->clear();
    password->clear();

    name->setPlaceholderText(NAME_PLACEHOLDER_TEXT);
    emit moveToRight();
}

void LoginBar::timeout()
{

    timer->stop();
    if (email->isVisible())
    {
        email->hide();
    }
    else
        email->show();
    swap();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////