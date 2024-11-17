#include "LoginSliders.hpp"
#include <QDebug>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Slider::Slider(QWidget *parent) : QWidget(parent), sliderStyle{""}
{
    setGeometry(QRect(0, 0, LOGIN_PAGE_SLIDER_WIDTH, LOGIN_PAGE_SLIDER_HEIGHT));
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(ZERO_CONTEXT_MARGINS);
    layout->setAlignment(Qt::AlignCenter);

    sliderPosAnimation = new QPropertyAnimation(this, "pos");
    sliderPosAnimation->setEasingCurve(LOGIN_PAGE_SLIDER_MOVE_EASIGN_CURVE);
    sliderPosAnimation->setDuration(LOGIN_PAGE_SLIDER_MOVE_DURATION);
}

void Slider::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};

QPropertyAnimation* Slider::SliderPosAnimation()
{
    return sliderPosAnimation;
}

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
    move(LOGIN_PAGE_SLIDER_LEFT_POS);
    setObjectName(LOGIN_PAGE_MAIN_SLIDER_OBJECT_NAME);
    sliderStyle = UserDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                  QString("#") + QString(LOGIN_PAGE_MAIN_SLIDER_OBJECT_NAME));
    layout()->addWidget(createGreetingLabel());
    layout()->addWidget(createAdditionalLabel());
    layout()->addWidget(createSignButton());
    layout()->setSpacing(LOGIN_PAGE_MAIN_SLIDER_LAYOUT_SPACING);

    for (int i = 0; i < layout()->count(); ++i)
    {
        layout()->setAlignment(layout()->itemAt(i)->widget(), Qt::AlignHCenter);
    }
    setBorderRadii(LP_MS_BORDER_RADII_IN_LEFT_POS);
    sliderBorderAnimation = new QPropertyAnimation(this, "borderRadii");
    sliderBorderAnimation->setDuration(LOGIN_PAGE_SLIDER_MOVE_DURATION);
    sliderBorderAnimation->setEasingCurve(LOGIN_PAGE_SLIDER_BORDER_EASIGN_CURVE);
}

ButtonWithHover *MainSlider::createSignButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    btn->setObjectName(LP_MS_SIGN_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(UserDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        QString("#") + QString(LP_MS_SIGN_BUTTON_OBJECT_NAME)));
    btn->setHoverActive(true);
    btn->setHoverDuration(LOGIN_PAGE_SIGN_BUTTON_HOVER_DURATION);
    btn->setStartBackgroundColor(TRANSPARENT);
    btn->setEndBackgroundColor(GOLD);
    btn->setText(SIGN_IN);
    btn->setStartTextColor(GRAY);
    btn->setEndTextColor(DARK_BLUE);
    connect(btn, &QPushButton::clicked, this, &MainSlider::isSignButtonClicked);
    return btn;
}
QLabel *MainSlider::createGreetingLabel()
{
    QLabel *label = new QLabel(this);
    label->setText(LP_MS_GREATING_LABEL_LEFT_POS_TEXT);
    label->setObjectName(LP_MS_GREATING_LABEL_OBJECT_NAME);
    return label;
}
QLabel *MainSlider::createAdditionalLabel()
{
    QLabel *label = new QLabel(this);
    label->setText(LP_MS_ADDITIONAL_LABEL_LEFT_POS_TEXT);
    label->setObjectName(LP_MS_ADDITIONAL_LABEL_OBJECT_NAME);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignHCenter);
    return label;
}

ButtonWithHover *MainSlider::signButton()
{
    return LP_MS_SIGN_BUTTON_IN_LAYOUT;
}
QLabel *MainSlider::greetingLabel()
{
    return LP_MS_GREATING_LABEL_IN_LAYOUT;
}
QLabel *MainSlider::additionalLabel()
{
    return LP_MS_ADDITIONAL_LABEL_IN_LAYOUT;
}

void MainSlider::isSliderMove()
{
    if (sliderBorderAnimation->state() != QAbstractAnimation::Stopped)
    {
        sliderBorderAnimation->stop();
        sliderPosAnimation->stop();
    }
    if (signButton()->text() == SIGN_UP)
    {
        sliderPosAnimation->setEndValue(LOGIN_PAGE_SLIDER_LEFT_POS);
        sliderBorderAnimation->setEndValue(QVARIAN_BORDER_RADII_IN_LEFT_POS);
    }
    else
    {
        sliderPosAnimation->setEndValue(LOGIN_PAGE_SLIDER_RIGHT_POS);
        sliderBorderAnimation->setEndValue(QVARIAN_BORDER_RADII_IN_RIGHT_POS);
    }
    sliderPosAnimation->start();
    sliderBorderAnimation->start();
    emit sliderMove();
    swap();
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
void MainSlider::isSignButtonClicked()
{
    isSliderMove();
}
void MainSlider::swapGreetinLabelText() noexcept
{
    if (greetingLabel()->text() == LP_MS_GREATING_LABEL_LEFT_POS_TEXT)
    {
        greetingLabel()->setText(LP_MS_GREATING_LABEL_RIGHT_POS_TEXT);
        return;
    }
    greetingLabel()->setText(LP_MS_GREATING_LABEL_LEFT_POS_TEXT);
}
void MainSlider::swapAdditionalLabelText() noexcept
{
    if (additionalLabel()->text() == LP_MS_ADDITIONAL_LABEL_LEFT_POS_TEXT)
    {
        additionalLabel()->setText(LP_MS_ADDITIONAL_LABEL_RIGHT_POS_TEXT);
        return;
    }
    additionalLabel()->setText(LP_MS_ADDITIONAL_LABEL_LEFT_POS_TEXT);
}
void MainSlider::swap()
{
    signButton()->swapText();
    swapGreetinLabelText();
    swapAdditionalLabelText();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LoginSlider::LoginSlider(QWidget *parent) : Slider(parent)
{
    move(LOGIN_PAGE_SLIDER_RIGHT_POS);
    layout()->setSpacing(LOGIN_PAGE_LOGIN_SLIDER_LAYOUT_SPACING);
    layout()->addWidget(createMainLabel());
    layout()->addWidget(createPictureLabel());
    layout()->addWidget(createErrorLabel());
    layout()->addWidget(createNameLineEdit());
    layout()->addWidget(createEmailLineEdit());
    layout()->addWidget(createPasswordLineEdit());
    layout()->addWidget(createSignButton());
    for (int i = 0; i < layout()->count(); ++i)
    {
        layout()->setAlignment(layout()->itemAt(i)->widget(), Qt::AlignHCenter);
    }
}

QLabel *LoginSlider::createMainLabel()
{
    QLabel *label = new QLabel(this);
    label->setObjectName(LP_LS_MAIN_LABEL_OBJECT_NAME);
    label->setText(LP_LS_MAIN_LABEL_TEXT_IN_RIGHT_POS);
    return label;
}
ButtonWithHover *LoginSlider::createSignButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    btn->setObjectName(LP_LS_SIGN_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(UserDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        QString("#") + QString(LP_LS_SIGN_BUTTON_OBJECT_NAME)));
    btn->setHoverActive(true);
    // btn->setHoverDuration(LOGIN_PAGE_SIGN_BUTTON_HOVER_DURATION);
    btn->setStartBackgroundColor(GOLD);
    btn->setEndBackgroundColor(DARK_BLUE);
    btn->setText(SIGN_UP);
    btn->setStartTextColor(DARK_BLUE);
    btn->setEndTextColor(GOLD);
    QObject::connect(btn, &QPushButton::clicked, this, &isSignButtonClicked);
    return btn;
}
QLineEdit *LoginSlider::createNameLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setPlaceholderText(LP_LS_NAME_LINE_EDIT_PLACEHOLDER_TEXT);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLineEdit *LoginSlider::createEmailLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setPlaceholderText(LP_LS_EMAIL_LINE_EDIT_PLACEHOLDER_TEXT);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLineEdit *LoginSlider::createPasswordLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setPlaceholderText(LP_LS_PASSWORD_LINE_EDIT_PLACEHOLDER_TEXT);
    lineEdit->setEchoMode(QLineEdit::Password);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLabel *LoginSlider::createErrorLabel()
{
    QLabel *label = new QLabel(this);
    label->setObjectName(LP_LS_ERROR_LABEL_OBJECT_NAME);
    return label;
}
QLabel *LoginSlider::createPictureLabel()
{
    QLabel *picture = new QLabel(this);
    QPixmap pixmap(LOGO_PATH);
    picture->setPixmap(pixmap.scaled(LP_LS_LOGO_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    picture->setAlignment(Qt::AlignCenter);
    picture->setContentsMargins(ZERO_CONTEXT_MARGINS); ////
    return picture;
}

QLabel *LoginSlider::mainLabel()
{
    return LP_LS_MAIN_LABEL_IN_LAYOUT;
}
QLabel *LoginSlider::errorLabel()
{
    return LP_LS_ERROR_LABEL_IN_LAYOUT;
}
QLineEdit *LoginSlider::nameLineEdit()
{
    return LP_LS_NAME_LINE_EDIT_IN_LAYOUT;
}
QLineEdit *LoginSlider::emailLineEdit()
{
    return LP_LS_EMAIL_LINE_EDIT_IN_LAYOUT;
}
QLineEdit *LoginSlider::passwordLineEdit()
{
    return LP_LS_PASSWORD_LINE_EDIT_IN_LAYOUT;
}
ButtonWithHover *LoginSlider::signButton()
{
    return LP_LS_SIGN_BUTTON_IN_LAYOUT;
}

void LoginSlider::swap()
{

    swapMainLabelText();

    if (emailLineEdit()->isVisible())
    {
        emailLineEdit()->hide();
    }
    else
        emailLineEdit()->show();
    signButton()->swapText();
}
void LoginSlider::clear()
{
    nameLineEdit()->clear();
    emailLineEdit()->clear();
    passwordLineEdit()->clear();
    errorLabel()->clear();
}
void LoginSlider::swapMainLabelText()
{
    if (mainLabel()->text() == LP_LS_MAIN_LABEL_TEXT_IN_RIGHT_POS)
    {
        mainLabel()->setText(LP_LS_MAIN_LABEL_TEXT_IN_LEFT_POS);
        return;
    }
    mainLabel()->setText(LP_LS_MAIN_LABEL_TEXT_IN_RIGHT_POS);
}

void LoginSlider::isSignButtonClicked()
{
    if (nameLineEdit()->text() != "" && (!emailLineEdit()->isVisible() || emailLineEdit()->text() != "") && passwordLineEdit()->text() != "")
    {
        QString message;
        message += MESSAGE_TYPE_SELECTOR + LEFT_MESSAGE_BRACKET;
        message += mainLabel()->text() == SIGN_IN ? CHECK_CREDENTIALS_MESSAGE_TYPE : ADD_USER_MESSAGE_TYPE;
        message += RIGHT_MESSAGE_BRACKET;
        message += NAME_SELECTOR + LEFT_MESSAGE_BRACKET + nameLineEdit()->text() + RIGHT_MESSAGE_BRACKET;
        message += PASSWORD_SELECTOR + LEFT_MESSAGE_BRACKET + passwordLineEdit()->text() + RIGHT_MESSAGE_BRACKET;

        if (mainLabel()->text() == SIGN_IN)
        {
            emit sliderSignInClicked(message);
            return;
        }
        message += EMAIL_SELECTOR + LEFT_MESSAGE_BRACKET + emailLineEdit()->text() + RIGHT_MESSAGE_BRACKET;
        emit sliderSignUpClicked(message);
        return;
    }
    errorLabel()->setText(LP_LS_EL_EMTPY_FIELS_TEXT);
}

void LoginSlider::isSliderMove()
{
    if (sliderPosAnimation->state() != QAbstractAnimation::Stopped)
    {
        sliderPosAnimation->stop();
    }
    sliderPosAnimation->setEndValue(signButton()->text() == SIGN_UP ? LOGIN_PAGE_SLIDER_LEFT_POS : LOGIN_PAGE_SLIDER_RIGHT_POS);
    sliderPosAnimation->start();
    clear();
    swap();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////