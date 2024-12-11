#ifndef TYPING_TEST_H
#define TYPING_TEST_H

#include <QKeyEvent>
#include <QPainter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextStream>

#include "Page.h"
#include "CircularLinkedList.h"

class TypingTestEdit : public QTextEdit
{
    Q_OBJECT

    friend class TypingTest;

public:
    TypingTestEdit(QWidget *parent = nullptr);
    ~TypingTestEdit();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override {}
    void mouseReleaseEvent(QMouseEvent *event) override {}
    void mouseMoveEvent(QMouseEvent *event) override {}
    void mouseDoubleClickEvent(QMouseEvent *event) override {}
    void wheelEvent(QWheelEvent *event) override {}
    void enterEvent(QEvent *event) override {}
    void leaveEvent(QEvent *event) override {}

public:
    QString curTime();
    QString curAcc();
    QString curCpm();
    void inserRightSymbol();
    void insertWrongSymbol();
    void blurOn();
    void keyPressEvent(QKeyEvent *event) override;
    void blurOff();
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    bool isBlur();

private:
    QGraphicsBlurEffect *blurEffect;
    QPropertyAnimation *blurAnimation;
    QTimer *timer;

    QString::iterator nextChar;

    QString plainText;
    int time;
    int countMistakes;
    int countRightSymbol;

signals:

    void endOfPlainText();
};

class TypingTest : public Page
{
    Q_OBJECT
public:
    TypingTest(QWidget *parent = nullptr);
    ~TypingTest();
    void hide();
    void show();
    QLabel *timeLabel();
    QLabel *cpmLabel();
    ButtonWithHover *repeatButton();
    ButtonWithHover *nextButton();
    TypingTestEdit *typingTestEdit();
    void setPlainText(const QString &plainText);
    void reset();

protected slots:

    void repeat();
    void isTimeout();
    void showResult();
    void paintEvent(QPaintEvent *event) override;

private:
    void setup() override;
    ButtonWithHover *createRepeatButton();
    ButtonWithHover *createNextButton();
    QLabel *createCpmLabel();
    QLabel *createTimeLabel();

signals:
    void newResult(const QString);
};

class RepeatTypingTest : public TypingTest
{
    Q_OBJECT
public:
    RepeatTypingTest(QWidget *parent = nullptr);
    ~RepeatTypingTest();

private:
    void next();
    void readFromFile(const QString &filename);
    CircularLinkedList<QString> texts;
};

class LessonTypingTest : public TypingTest
{
    Q_OBJECT
public:
    LessonTypingTest(QWidget *parent = nullptr);
    ~LessonTypingTest();
    ButtonWithHover *quitButton();

private:
    ButtonWithHover *createQuitButton();
};

#endif
