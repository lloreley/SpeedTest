
#ifndef LESSONS_SCROLL_AREA_HPP
#define LESSONS_SCROLL_AREA_HPP

#include <QScrollArea>
#include <QVBoxLayout>
#include "TypingTest/TypingTest.hpp"
#include "TypingLessons/TypingLessons.hpp"
#include "AccountPage/AccountPage.hpp"

class LessonsScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    LessonsScrollArea(QWidget *parent = nullptr) : QScrollArea(parent)
    {
        QWidget *viewportWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(viewportWidget);
        QLabel *nameLabel = new QLabel(viewportWidget);
        AccountPage *accountPage = new AccountPage(viewportWidget);
        TypingLessons *typingLessons = new TypingLessons(viewportWidget);
        LessonTypingTest *lessonTypingTest = new LessonTypingTest(viewportWidget);
        RepeatTypingTest *repeatTypingTest = new RepeatTypingTest(viewportWidget);

        if(!viewportWidget || !layout || !nameLabel || !accountPage || !typingLessons || !lessonTypingTest || !repeatTypingTest)
        {
            throw NullPointerException("LessonsScrollAreaWidget");
        }

        layout->setContentsMargins(ZERO_CONTENTS_MARGINS);
        nameLabel->setObjectName(SCROLL_AREA_NAME_LABEL_OBJECT_NAME);


        this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

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

        connect(lessonTypingTest->nextButton(), &QAbstractButton::clicked, [lessonTypingTest, typingLessons]()
                {if(typingLessons->currentId < typingLessons->countLessons)
                    ++(typingLessons->currentId);
                else typingLessons->currentId = 1;
        lessonTypingTest->setPlainText(FileDataBase::extractValueFromStrWithSelector(FileDataBase::readAllFile(DATA_LESSONS_PATH+QString::number(typingLessons->currentId) + TXT_END), TEXT_SELECTOR) ); });
        this->setWidget(viewportWidget);
        connect(accountPage, &AccountPage::userInstalled, this, &setNewConnection);
    }

    QLabel *getNameLabel()
    {
        QLabel* label = findChild<QLabel *>(SCROLL_AREA_NAME_LABEL_OBJECT_NAME);
        if(!label)
        {
            throw NullPointerException("NameLabelScrollArea");
        }
        return label;
    }

    RepeatTypingTest *getRepeatTypingTest()
    {
        RepeatTypingTest* test = findChild<RepeatTypingTest *>();
        if(!test)
        {
            throw NullPointerException("RepeatTypingTest");
        }
        return test;
    }

    LessonTypingTest *getLessonTypingTest()
    {
        LessonTypingTest* test = findChild<LessonTypingTest *>();
        if(!test)
        {
            throw NullPointerException("LessonTypingTest");
        }
        return test;
    }

    TypingLessons *getTypingLessons()
    {
        TypingLessons* lessons = findChild<TypingLessons *>();
        if(!lessons)
        {
            throw NullPointerException("TypingLessons");
        }
        return lessons;
    }

    AccountPage *getAccountPage()
    {
        return findChild<AccountPage *>();
    }

    void setNewConnection()
    {
        connect(getLessonTypingTest(), &TypingTest::newResult, getAccountPage(), &AccountPage::addResult);
        connect(getRepeatTypingTest(), &TypingTest::newResult, getAccountPage(), &AccountPage::addResult);
        if (getAccountPage()->getUser()->getDateRegistration() != "none")
        {
            connect(getLessonTypingTest(), &TypingTest::newResult, getAccountPage()->getUser(), &BaseUser::addTypingResult);
            connect(getRepeatTypingTest(), &TypingTest::newResult, getAccountPage()->getUser(), &BaseUser::addTypingResult);
        }
    }

    void showRepeatTypingTestPage()
    {
        getNameLabel()->setText("Typing Test");
        getLessonTypingTest()->hide();
        getTypingLessons()->hide();
        getAccountPage()->hide();
        getRepeatTypingTest()->show();
    }

    void showTypingLessonsPage()
    {
        getNameLabel()->setText("Typing Lessons");
        getRepeatTypingTest()->hide();
        getAccountPage()->hide();
        getTypingLessons()->show();
    }
    void showAccountPage()
    {
        getNameLabel()->setText("Account");
        getLessonTypingTest()->hide();
        getTypingLessons()->hide();
        getRepeatTypingTest()->hide();
        getAccountPage()->show();
    }
};

#endif