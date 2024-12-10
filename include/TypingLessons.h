#ifndef TYPING_COURSES_H
#define TYPING_COURSES_H

#include <QStyleOption>
#include <QHBoxLayout>
#include <QTextStream>
#include "TypingTest.h"

class Lesson : public QWidget
{
    Q_OBJECT
    friend class TypingLessons;

public:
    Lesson(const QString &lessonData, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *pe);
    const QString &getText() const noexcept;
    QLabel *createNameLabel(const QString &name);
    ButtonWithHover *createStartButton();
    ButtonWithHover *startButton();

private:
    QString name;
    QString text;
    int id;
};

class TypingLessons : public Page
{
    Q_OBJECT
    friend class LessonsScrollArea;

public:
    TypingLessons(QWidget *parent = nullptr);
    ~TypingLessons();
public slots:
    void isStartLesson();

private:
    void setup() override;
    void createLessons();
    void paintEvent(QPaintEvent *pe);

    int countLessons;
    int currentId;

signals:
    void start(const QString &);
};

#endif
