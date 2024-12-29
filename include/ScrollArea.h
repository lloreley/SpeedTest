#ifndef LESSONS_SCROLL_AREA_H
#define LESSONS_SCROLL_AREA_H

#include <QScrollArea>
#include "TypingTest.h"
#include "TypingLessons.h"
#include "AccountPage.h"

class ScrollArea final : public QScrollArea
{
    Q_OBJECT
public:
    ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea();
    QLabel *getNameLabel();
    RepeatTypingTest *getRepeatTypingTest();
    LessonTypingTest *getLessonTypingTest();
    TypingLessons *getTypingLessons();
    AccountPage *getAccountPage();

private slots:
    void setup();
    void setNewConnection() noexcept;
public slots:
    void showRepeatTypingTestPage();
    void showTypingLessonsPage();
    void showAccountPage();
};

#endif
