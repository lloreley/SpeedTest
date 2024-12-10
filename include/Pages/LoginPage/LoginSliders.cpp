#include "LoginSliders.hpp"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Slider::Slider(QWidget *parent) : QWidget(parent), sliderStyle{""}
{
    setGeometry(QRect(0, 0, LOGIN_PAGE_SLIDER_WIDTH, LOGIN_PAGE_SLIDER_HEIGHT));
    QVBoxLayout *layout = new QVBoxLayout(this);
    sliderPosAnimation = new QPropertyAnimation(this, "pos");
    CHECK_PTR(layout)
    CHECK_PTR(sliderPosAnimation)
    layout->setContentsMargins(ZERO_CONTENTS_MARGINS);
    layout->setAlignment(Qt::AlignCenter);
    sliderPosAnimation->setEasingCurve(LOGIN_PAGE_SLIDER_MOVE_EASIGN_CURVE);
    sliderPosAnimation->setDuration(LOGIN_PAGE_SLIDER_MOVE_DURATION);
}
Slider::~Slider()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
void Slider::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};

QPropertyAnimation *Slider::SliderPosAnimation()
{
    CHECK_PTR(sliderPosAnimation)
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
    sliderStyle = FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
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
    CHECK_PTR(sliderBorderAnimation)
    sliderBorderAnimation->setDuration(LOGIN_PAGE_SLIDER_MOVE_DURATION);
    sliderBorderAnimation->setEasingCurve(LOGIN_PAGE_SLIDER_BORDER_EASIGN_CURVE);
}

ButtonWithHover *MainSlider::createSignButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    CHECK_PTR(btn)
    btn->setObjectName(LP_MS_SIGN_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
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
    CHECK_PTR(label)
    label->setText(LP_MS_GREATING_LABEL_LEFT_POS_TEXT);
    label->setObjectName(LP_MS_GREATING_LABEL_OBJECT_NAME);
    return label;
}
QLabel *MainSlider::createAdditionalLabel()
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label)
    label->setText(LP_MS_ADDITIONAL_LABEL_LEFT_POS_TEXT);
    label->setObjectName(LP_MS_ADDITIONAL_LABEL_OBJECT_NAME);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignHCenter);
    return label;
}

ButtonWithHover *MainSlider::signButton()
{
    ButtonWithHover *signBtn = findChild<ButtonWithHover *>(LP_MS_SIGN_BUTTON_OBJECT_NAME);
    CHECK_PTR(signBtn)
    return signBtn;
}
QLabel *MainSlider::greetingLabel()
{
    QLabel *greatingLbl = findChild<QLabel *>(LP_MS_GREATING_LABEL_OBJECT_NAME);
    CHECK_PTR(greatingLbl)
    return greatingLbl;
}
QLabel *MainSlider::additionalLabel()
{
    QLabel *additionalLbl = findChild<QLabel *>(LP_MS_ADDITIONAL_LABEL_OBJECT_NAME);
    CHECK_PTR(additionalLbl)
    return additionalLbl;
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
void MainSlider::swapGreetinLabelText()
{
    if (greetingLabel()->text() == LP_MS_GREATING_LABEL_LEFT_POS_TEXT)
    {
        greetingLabel()->setText(LP_MS_GREATING_LABEL_RIGHT_POS_TEXT);
        return;
    }
    greetingLabel()->setText(LP_MS_GREATING_LABEL_LEFT_POS_TEXT);
}
void MainSlider::swapAdditionalLabelText()
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
    layout()->addWidget(createNotSignButton());
    layout()->addWidget(createSignButton());
    for (int i = 0; i < layout()->count(); ++i)
    {
        layout()->setAlignment(layout()->itemAt(i)->widget(), Qt::AlignHCenter);
    }
    connect(nameLineEdit(), &QLineEdit::returnPressed, [this]()
            { if (emailLineEdit()->isVisible()){
                emailLineEdit()->setFocus();
            }else passwordLineEdit()->setFocus(); });
    connect(emailLineEdit(), &QLineEdit::returnPressed, [this]()
            { passwordLineEdit()->setFocus(); });
    connect(passwordLineEdit(), &QLineEdit::returnPressed, [this]()
            { this->isSignButtonClicked(); });
}

void LoginSlider::validateName(const QString &name)
{
    if (name.isEmpty() || !QRegularExpression("^[A-Za-z][A-Za-z0-9_]{2,29}$").match(name).hasMatch())
    {
        throw InvalidNameException(name);
    }
}
void LoginSlider::validateEmail(const QString &email)
{
    if (email.isEmpty() || !QRegularExpression(R"((^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,})$)").match(email).hasMatch())
    {
        throw InvalidEmailException(email);
    }
}
void LoginSlider::validatePassword(const QString &password)
{
    if (password.length() < 8 ||
        !QRegularExpression("[A-Z]").match(password).hasMatch() ||
        !QRegularExpression("[a-z]").match(password).hasMatch() ||
        !QRegularExpression("[0-9]").match(password).hasMatch() ||
        !QRegularExpression("[^A-Za-z0-9]").match(password).hasMatch())
    {
        throw InvalidPasswordException(password);
    }
}

QLabel *LoginSlider::createMainLabel()
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label)
    label->setObjectName(LP_LS_MAIN_LABEL_OBJECT_NAME);
    label->setText(LP_LS_MAIN_LABEL_TEXT_IN_RIGHT_POS);
    return label;
}
QPushButton *LoginSlider::createNotSignButton()
{
    QPushButton *btn = new QPushButton(this);
    CHECK_PTR(btn)
    btn->setText(LP_LS_NOT_SIGN_BUTTON_TEXT);
    btn->setObjectName(LP_LS_NOT_SIGN_BUTTON_OBJECT_NAME);
    return btn;
}
ButtonWithHover *LoginSlider::createSignButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    CHECK_PTR(btn)
    btn->setObjectName(LP_LS_SIGN_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        QString("#") + QString(LP_LS_SIGN_BUTTON_OBJECT_NAME)));
    btn->setHoverActive(true);
    btn->setStartBackgroundColor(GOLD);
    btn->setEndBackgroundColor(DARK_BLUE);
    btn->setText(SIGN_UP);
    btn->setStartTextColor(DARK_BLUE);
    btn->setEndTextColor(GOLD);
    connect(btn, &QPushButton::clicked, this, &isSignButtonClicked);
    return btn;
}
QLineEdit *LoginSlider::createNameLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    CHECK_PTR(lineEdit)
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setObjectName(LP_LS_NAME_LE_OBJECT_NAME);
    lineEdit->setPlaceholderText(LP_LS_NAME_LINE_EDIT_PLACEHOLDER_TEXT);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLineEdit *LoginSlider::createEmailLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    CHECK_PTR(lineEdit)
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setObjectName(LP_LS_EMAIL_LE_OBJECT_NAME);
    lineEdit->setPlaceholderText(LP_LS_EMAIL_LINE_EDIT_PLACEHOLDER_TEXT);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLineEdit *LoginSlider::createPasswordLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    CHECK_PTR(lineEdit)
    lineEdit->setProperty(LP_LS_LINE_EDIT_PROPERTY);
    lineEdit->setObjectName(LP_LS_PASSWORD_LE_OBJECT_NAME);
    lineEdit->setPlaceholderText(LP_LS_PASSWORD_LINE_EDIT_PLACEHOLDER_TEXT);
    lineEdit->setEchoMode(QLineEdit::Password);
    connect(lineEdit, &QLineEdit::textChanged, errorLabel(), &QLabel::clear);
    return lineEdit;
}
QLabel *LoginSlider::createErrorLabel()
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label)
    label->setObjectName(LP_LS_ERROR_LABEL_OBJECT_NAME);
    return label;
}
QLabel *LoginSlider::createPictureLabel()
{
    QLabel *picture = new QLabel(this);
    CHECK_PTR(picture)
    QPixmap pixmap(LOGO_PATH);
    picture->setPixmap(pixmap.scaled(LP_LS_LOGO_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    picture->setAlignment(Qt::AlignCenter);
    picture->setContentsMargins(ZERO_CONTENTS_MARGINS);
    return picture;
}

QPushButton *LoginSlider::notSignButton()
{
    QPushButton *notUseAccountBtn = findChild<QPushButton *>(LP_LS_NOT_SIGN_BUTTON_OBJECT_NAME);
    CHECK_PTR(notUseAccountBtn)
    return notUseAccountBtn;
}
QLabel *LoginSlider::mainLabel()
{
    QLabel *mnLabel = findChild<QLabel *>(LP_LS_MAIN_LABEL_OBJECT_NAME);
    CHECK_PTR(mnLabel)
    return mnLabel;
}
QLabel *LoginSlider::errorLabel()
{
    QLabel *errLabel = findChild<QLabel *>(LP_LS_ERROR_LABEL_OBJECT_NAME);
    CHECK_PTR(errLabel)
    return errLabel;
}
QLineEdit *LoginSlider::nameLineEdit()
{
    QLineEdit *nmLineEdit = findChild<QLineEdit *>(LP_LS_NAME_LE_OBJECT_NAME);
    CHECK_PTR(nmLineEdit)
    return nmLineEdit;
}
QLineEdit *LoginSlider::emailLineEdit()
{
    QLineEdit *emLineEdit = findChild<QLineEdit *>(LP_LS_EMAIL_LE_OBJECT_NAME);
    CHECK_PTR(emLineEdit)
    return emLineEdit;
}
QLineEdit *LoginSlider::passwordLineEdit()
{
    QLineEdit *passLineEdit = findChild<QLineEdit *>(LP_LS_PASSWORD_LE_OBJECT_NAME);
    CHECK_PTR(passLineEdit)
    return passLineEdit;
}
ButtonWithHover *LoginSlider::signButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(LP_LS_SIGN_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}

void LoginSlider::swap()
{
    swapMainLabelText();
    if (emailLineEdit()->isVisible())
        emailLineEdit()->hide();
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
    try
    {
        validateName(nameLineEdit()->text());
        if (emailLineEdit()->isVisible())
            validateEmail(emailLineEdit()->text());
        validatePassword(passwordLineEdit()->text());
    }
    catch (BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(ex.what()), QMessageBox::Ok);
        return;
    }

    QString message;
    message += MESSAGE_TYPE_SELECTOR + LEFT_MESSAGE_BRACKET;
    message += mainLabel()->text() == SIGN_IN ? CHECK_CREDENTIALS_MESSAGE_TYPE : ADD_USER_MESSAGE_TYPE;
    message += RIGHT_MESSAGE_BRACKET;
    message += NAME_SELECTOR + LEFT_MESSAGE_BRACKET + nameLineEdit()->text() + RIGHT_MESSAGE_BRACKET;
    message += PASSWORD_SELECTOR + LEFT_MESSAGE_BRACKET + passwordLineEdit()->text() + RIGHT_MESSAGE_BRACKET;

    passwordLineEdit()->clear();
    if (mainLabel()->text() == SIGN_IN)
    {
        emit sliderSignInClicked(message);
        return;
    }
    message += EMAIL_SELECTOR + LEFT_MESSAGE_BRACKET + emailLineEdit()->text() + RIGHT_MESSAGE_BRACKET;
    emit sliderSignUpClicked(message);
}
void LoginSlider::isSliderMove()
{
    if (sliderPosAnimation->state() != QAbstractAnimation::Stopped)
        sliderPosAnimation->stop();
    sliderPosAnimation->setEndValue(signButton()->text() == SIGN_UP ? LOGIN_PAGE_SLIDER_LEFT_POS : LOGIN_PAGE_SLIDER_RIGHT_POS);
    sliderPosAnimation->start();
    clear();
    swap();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////