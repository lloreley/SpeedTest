#include "../include/WelcomePage.h"

WelcomePage::WelcomePage(QWidget *parent) : Page(parent)
{
    setup();
}
void WelcomePage::setup()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(createGreatingLabel());
    layout->addWidget(createAdditionalLabel());

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(createLeftButton());
    buttonsLayout->addWidget(createRightButton());

    layout->addLayout(buttonsLayout);
    layout->setSpacing(WELCOME_PAGE_LAYOUT_SPACING);
    layout->setAlignment(Qt::AlignVCenter);
    for (int i = 0; i < layout->count(); ++i)
    {
        layout->setAlignment(layout->itemAt(i)->widget(), Qt::AlignCenter);
    }
}
WelcomePage::~WelcomePage()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
QLabel *WelcomePage::createGreatingLabel()
{
    QLabel *label = new QLabel(this);
    label->setText(WELCOME_PAGE_GREATING_LABEL_TEXT);
    label->setObjectName(WELCOME_PAGE_GREATING_OBJECT_NAME);
    return label;
}
QLabel *WelcomePage::createAdditionalLabel()
{
    QLabel *label = new QLabel(this);
    label->setText(WELCOME_PAGE_ADDITIONAL_LABEL_TEXT);
    label->setObjectName(WELCOME_PAGE_ADDITIONAL_OBJECT_NAME);
    label->setAlignment(Qt::AlignHCenter);
    return label;
}
ButtonWithHover *WelcomePage::createLeftButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    btn->setObjectName(WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        QString("#") + QString(WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME)));
    btn->setHoverActive(true);
    btn->setStartBackgroundColor(GOLD);
    btn->setEndBackgroundColor(DARK_BLUE);
    btn->setText(WELCOME_PAGE_LEFT_BUTTON_TEXT);
    btn->setStartTextColor(GRAY);
    btn->setEndTextColor(GOLD);
    connect(btn, &QPushButton::clicked, [this]()
            { emit TypingTest(); hide(); });
    return btn;
}
ButtonWithHover *WelcomePage::createRightButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    btn->setObjectName(WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME);
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        QString("#") + QString(WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME)));
    btn->setHoverActive(true);
    btn->setStartBackgroundColor(LIGHT_GRAY);
    btn->setEndBackgroundColor(DARK_BLUE);
    btn->setText(WELCOME_PAGE_RIGHT_BUTTON_TEXT);
    btn->setStartTextColor(GRAY);
    btn->setEndTextColor(GOLD);
    connect(btn, &QPushButton::clicked, [&]()
            { emit TypingLessons(); hide(); });
    return btn;
}
QLabel *WelcomePage::greatingLabel()
{

    QLabel *label = findChild<QLabel *>(WELCOME_PAGE_GREATING_OBJECT_NAME);
    CHECK_PTR(label)
    return label;
}
QLabel *WelcomePage::additionalLabel()
{
    QLabel *label = findChild<QLabel *>(WELCOME_PAGE_ADDITIONAL_OBJECT_NAME);
    CHECK_PTR(label)
    return label;
}
ButtonWithHover *WelcomePage::leftButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(WELCOME_PAGE_LEFT_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}
ButtonWithHover *WelcomePage::rightButton()
{
    ButtonWithHover *btn = findChild<ButtonWithHover *>(WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME);
    CHECK_PTR(btn)
    return btn;
}