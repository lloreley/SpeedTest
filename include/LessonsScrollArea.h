#ifndef LESSONS_SCROLL_AREA_H
#define LESSONS_SCROLL_AREA_H

#include <QScrollArea>
#include "TypingTest.h"
#include "TypingLessons.h"
#include "AccountPage.h"

class LessonsScrollArea final : public QScrollArea
{
    Q_OBJECT
public:
    LessonsScrollArea(QWidget *parent = nullptr);
    ~LessonsScrollArea();
    void setup();
    QLabel *getNameLabel();
    RepeatTypingTest *getRepeatTypingTest();
    LessonTypingTest *getLessonTypingTest();
    TypingLessons *getTypingLessons();
    AccountPage *getAccountPage();

private slots:
    void setNewConnection() noexcept;
public slots:
    void showRepeatTypingTestPage();
    void showTypingLessonsPage();
    void showAccountPage();
};

#endif
