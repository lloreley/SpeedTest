#include "../include/LessonsScrollArea.h"

LessonsScrollArea::LessonsScrollArea(QWidget *parent) : QScrollArea(parent)
{
    setup();
    hide();
}

void LessonsScrollArea::setup()
{

    QWidget *viewportWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(viewportWidget);
    QLabel *nameLabel = new QLabel(viewportWidget);
    AccountPage *accountPage = new AccountPage(viewportWidget);
    TypingLessons *typingLessons = new TypingLessons(viewportWidget);
    LessonTypingTest *lessonTypingTest = new LessonTypingTest(viewportWidget);
    RepeatTypingTest *repeatTypingTest = new RepeatTypingTest(viewportWidget);

    CHECK_PTR(viewportWidget)
    CHECK_PTR(layout)
    CHECK_PTR(nameLabel)
    CHECK_PTR(accountPage)
    CHECK_PTR(typingLessons)
    CHECK_PTR(lessonTypingTest)
    CHECK_PTR(repeatTypingTest)

    layout->setContentsMargins(ZERO_CONTENTS_MARGINS);
    nameLabel->setObjectName(SCROLL_AREA_NAME_LABEL_OBJECT_NAME);
    setStyleSheet("background-color: transparent;");

    lessonTypingTest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    repeatTypingTest->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addSpacing(30);
    layout->addWidget(nameLabel);
    layout->addWidget(typingLessons);
    layout->addWidget(lessonTypingTest);
    layout->addWidget(repeatTypingTest);
    layout->addWidget(accountPage);
    layout->setSpacing(50);
    layout->setAlignment(Qt::AlignTop);

    connect(typingLessons, &TypingLessons::start, lessonTypingTest, &TypingTest::setPlainText);
    connect(typingLessons, &TypingLessons::start, lessonTypingTest, &TypingTest::show);
    connect(lessonTypingTest, &TypingTest::hidden, typingLessons, &TypingLessons::show);
    connect(accountPage, &AccountPage::userInstalled, this, &setNewConnection);

    connect(lessonTypingTest->nextButton(), &QAbstractButton::clicked, [lessonTypingTest, typingLessons]()
            {if(typingLessons->currentId < typingLessons->countLessons)
                    ++(typingLessons->currentId);
                else typingLessons->currentId = 1;
                lessonTypingTest->setPlainText(FileDataBase::extractValueFromStrWithSelector
                (FileDataBase::readAllFile(DATA_LESSONS_PATH+QString::number(typingLessons->currentId) + TXT_END), TEXT_SELECTOR) ); });
    setWidget(viewportWidget);
    setWidgetResizable(true);
}
LessonsScrollArea::~LessonsScrollArea()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
QLabel *LessonsScrollArea::getNameLabel()
{
    QLabel *nameLabel = findChild<QLabel *>(SCROLL_AREA_NAME_LABEL_OBJECT_NAME);
    CHECK_PTR(nameLabel)
    return nameLabel;
}
RepeatTypingTest *LessonsScrollArea::getRepeatTypingTest()
{
    RepeatTypingTest *repeatTypinTest = findChild<RepeatTypingTest *>();
    CHECK_PTR(repeatTypinTest)
    return repeatTypinTest;
}
LessonTypingTest *LessonsScrollArea::getLessonTypingTest()
{
    LessonTypingTest *lessonsTypingTest = findChild<LessonTypingTest *>();
    CHECK_PTR(lessonsTypingTest)
    return lessonsTypingTest;
}
TypingLessons *LessonsScrollArea::getTypingLessons()
{
    TypingLessons *typingLessons = findChild<TypingLessons *>();
    CHECK_PTR(typingLessons)
    return typingLessons;
}
AccountPage *LessonsScrollArea::getAccountPage()
{
    AccountPage *accountPage = findChild<AccountPage *>();
    CHECK_PTR(accountPage)
    return accountPage;
}
void LessonsScrollArea::setNewConnection() noexcept
{
    try
    {
        connect(getLessonTypingTest(), &TypingTest::newResult, getAccountPage(), &AccountPage::addResult);
        connect(getRepeatTypingTest(), &TypingTest::newResult, getAccountPage(), &AccountPage::addResult);
        if (getAccountPage()->getUser()->getDateRegistration() != "none")
        {
            connect(getLessonTypingTest(), &TypingTest::newResult, getAccountPage()->getUser(), &BaseUser::addTypingResult);
            connect(getRepeatTypingTest(), &TypingTest::newResult, getAccountPage()->getUser(), &BaseUser::addTypingResult);
        }
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1\nThe result may not be saved").arg(ex.what()), QMessageBox::Ok);
        return;
    }
}
void LessonsScrollArea::showRepeatTypingTestPage()
{
    try
    {
        getNameLabel()->setText("Typing Test");
        getLessonTypingTest()->hide();
        getTypingLessons()->hide();
        getAccountPage()->hide();
        getRepeatTypingTest()->show();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1\n").arg(ex.what()), QMessageBox::Ok);
        return;
    }
}
void LessonsScrollArea::showTypingLessonsPage()
{
    try
    {
        getNameLabel()->setText("Typing Lessons");
        getRepeatTypingTest()->hide();
        getAccountPage()->hide();
        getTypingLessons()->show();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1\n").arg(ex.what()), QMessageBox::Ok);
        return;
    }
}
void LessonsScrollArea::showAccountPage()
{
    try
    {
        getNameLabel()->setText("Account");
        getLessonTypingTest()->hide();
        getTypingLessons()->hide();
        getRepeatTypingTest()->hide();
        getAccountPage()->show();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1\n").arg(ex.what()), QMessageBox::Ok);
        return;
    }
}