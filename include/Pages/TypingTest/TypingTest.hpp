#ifndef TYPING_TEST_HPP
#define TYPING_TEST_HPP

#include <QKeyEvent>
#include <QPainter>
#include <QTextEdit>
#include <QApplication>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include "../Page.hpp"
#include "../../CircularLinkedList.hpp"

class TypingTestEdit : public QTextEdit
{
    Q_OBJECT

    friend class TypingTest;

public:
    TypingTestEdit(QWidget *parent = nullptr) : QTextEdit(parent), nextChar{}, time{}, countMistakes{}
    {
        setAlignment(Qt::AlignHCenter);
        setCursorWidth(3);
        setReadOnly(true);

        blurEffect = new QGraphicsBlurEffect();
        blurEffect->setBlurRadius(TYPING_TEST_MAX_BLUR);
        setGraphicsEffect(blurEffect);

        blurAnimation = new QPropertyAnimation(blurEffect, "blurRadius");
        blurAnimation->setDuration(TYPING_TEST_BLUR_ANIMATION_DURATION);
        blurAnimation->setStartValue(TYPING_TEST_ZERO_BLUR);
        blurAnimation->setEndValue(TYPING_TEST_MAX_BLUR);

        timer = new QTimer(this);
        setFocusPolicy(Qt::FocusPolicy::StrongFocus);

        connect(timer, &QTimer::timeout, [this]()
                { ++time; });
        setObjectName(TYPING_TEST_LINE_OBJECT_NAME);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QTextEdit::paintEvent(event);
        QPainter painter(viewport());
        if (!painter.isActive())
            return;
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addRoundedRect(cursorRect().left() - 2, cursorRect().top(), cursorWidth(), cursorRect().height(), 1.5, 1.5);
        painter.setPen(QPen(QColor(255, 235, 167), 2));
        painter.fillPath(path, QColor(255, 235, 167));
    }
    void mousePressEvent(QMouseEvent *event) override {}
    void mouseReleaseEvent(QMouseEvent *event) override {}
    void mouseMoveEvent(QMouseEvent *event) override {}
    void mouseDoubleClickEvent(QMouseEvent *event) override {}
    void wheelEvent(QWheelEvent *event) override {}
    void enterEvent(QEvent *event) override {}
    void leaveEvent(QEvent *event) override {}

public:
    QString curTime()
    {
        QString curTime = (time / 60 < 10 ? (QString("0") + QString::number(time / 60)) : QString::number(time / 60)) + QString(":") +
                          (time % 60 < 10 ? (QString("0") + QString::number(time % 60)) : QString::number(time % 60));
        return curTime;
    }

    QString curAcc()
    {
        return (QString("%") + QString::number(((float)(countRightSymbol) / (countMistakes + countRightSymbol)) * 100, 'f', 2));
    }

    QString curCpm()
    {
        return QString::number(countRightSymbol * 60 / (time == 0 ? 1 : time));
    }

    void inserRightSymbol()
    {
        ++countRightSymbol;
        if (*nextChar != " ")
        {
            QTextCursor cursor = textCursor();
            if (cursor.position() > 0)
            {
                cursor.movePosition(QTextCursor::Left);
                cursor.deleteChar();
                insertHtml(QString("<span style='color: white;'>%1</span>").arg(*nextChar));
            }
        }
    }

    void insertWrongSymbol()
    {
        if (*nextChar != " ")
        {
            QTextCursor cursor = textCursor();
            cursor.deleteChar();
            insertHtml(QString("<span style='color: red;'>%1</span>").arg(*nextChar));
            moveCursor(QTextCursor::Left);
        }
        ++countMistakes;
    }

    void blurOn()
    {
        if (blurEffect && blurEffect->blurRadius() == TYPING_TEST_ZERO_BLUR)
        {
            blurAnimation->setDirection(QAbstractAnimation::Forward);
            blurAnimation->start();
        }
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (nextChar)
        {
            if (!timer->isActive())
            {

                countMistakes = countRightSymbol = time = 0;
                timer->start(1000);
            }
            if (event->text() == *nextChar || (event->key() == Qt::Key_Space && (*nextChar) == " "))
            {
                moveCursor(QTextCursor::Right);
                inserRightSymbol();
                ++nextChar;
                if (nextChar == plainText.end())
                {
                    timer->stop();
                    emit endOfPlainText();
                }
            }
            else if (event->key() != Qt::Key_Space && event->text() != "")
            {
                insertWrongSymbol();
            }
            else
                QWidget::keyPressEvent(event);
        }
    }

    void blurOff()
    {
        if (blurEffect && blurEffect->blurRadius() == TYPING_TEST_MAX_BLUR)
        {
            blurAnimation->setDirection(QAbstractAnimation::Backward);
            blurAnimation->start();
        }
    }

    void focusInEvent(QFocusEvent *event) override
    {
        blurOff();
        QWidget::focusInEvent(event);
    }

    void focusOutEvent(QFocusEvent *event) override
    {
        blurOn();
        QWidget::focusOutEvent(event);
    }

    bool isBlur()
    {
        return blurEffect->blurRadius() == TYPING_TEST_MAX_BLUR;
    }

private:
    QGraphicsBlurEffect *blurEffect;
    QPropertyAnimation *blurAnimation;

    QString::iterator nextChar;

    QTimer *timer;
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
    TypingTest(QWidget *parent = nullptr) : Page(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        TypingTestEdit *textEdit = new TypingTestEdit(this);
        layout->addWidget(textEdit);

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(createRepeatButton());
        hLayout->addWidget(createTimeLabel());
        hLayout->addWidget(createCpmLabel());
        hLayout->addWidget(createNextButton());

        connect(typingTestEdit(), &TypingTestEdit::endOfPlainText, this, &showResult);
        connect(typingTestEdit()->timer, &QTimer::timeout, this, &isTimeout);

        layout->addLayout(hLayout);
    }

    ButtonWithHover *createRepeatButton()
    {
        ButtonWithHover *btn = Page::createBaseButton(this);
        btn->setIcon(QIcon(REPEAT_ICON_PATH));
        btn->setObjectName(TYPING_TEST_REPEAT_BUTTON_OBJECT_NAME);
        btn->upldateIconColor();
        btn->setIconSize(BASIC_ICON_SIZE);
        connect(btn, QAbstractButton::clicked, this, &repeat);
        return btn;
    }

    ButtonWithHover *createNextButton()
    {
        ButtonWithHover *btn = Page::createBaseButton(this);
        btn->setIcon(QIcon(NEXT_BUTTON_ICON_PATH));
        btn->setObjectName(TYPING_TEST_NEXT_BUTTON_OBJECT_NAME);
        btn->upldateIconColor();
        btn->setIconSize(BASIC_ICON_SIZE);
        return btn;
    }

    void hide()
    {
        Page::hide();
        typingTestEdit()->timer->stop();
    }

    void show()
    {
        Page::show();
        repeat();
    }

    QLabel *createCpmLabel()
    {
        QLabel *label = new QLabel(this);
        label->setObjectName(TYPING_TEST_CPM_LABEL_OBJECT_NAME);

        label->setText("CPM: 0");
        return label;
    }

    QLabel *createTimeLabel()
    {
        QLabel *label = new QLabel(this);
        label->setText(typingTestEdit()->curTime());
        label->setObjectName(TYPING_TEST_TIME_LABEL_OBJECT_NAME);
        return label;
    }

    QLabel *timeLabel()
    {
        return findChild<QLabel *>(TYPING_TEST_TIME_LABEL_OBJECT_NAME);
    }

    QLabel *cpmLabel()
    {
        return findChild<QLabel *>(TYPING_TEST_CPM_LABEL_OBJECT_NAME);
    }

    ButtonWithHover *repeatButton()
    {
        return findChild<ButtonWithHover *>(TYPING_TEST_REPEAT_BUTTON_OBJECT_NAME);
    }
    ButtonWithHover *nextButton()
    {
        return findChild<ButtonWithHover *>(TYPING_TEST_NEXT_BUTTON_OBJECT_NAME);
    }


    TypingTestEdit *typingTestEdit()
    {
        return findChild<TypingTestEdit *>(TYPING_TEST_LINE_OBJECT_NAME);
    }

    void setPlainText(const QString &plainText)
    {
        QString htmlText = "<span style='color:  rgb(109, 120, 135); font-size: 24px;'>" + plainText + "</span>"; // Пример HTML-разметки
        typingTestEdit()->setHtml(htmlText);
        typingTestEdit()->plainText = plainText;
        typingTestEdit()->nextChar = typingTestEdit()->plainText.begin();
    }

    void paintEvent(QPaintEvent *event)
    {
        Page::paintEvent(event);
        if (typingTestEdit()->isBlur())
        {

            QPainter painter(this);
            if (!painter.isActive())
                return;
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(GRAY);
            QFont font("Noto Sans Mono", 14, QFont::Bold);
            painter.setFont(font);
            QRect drect = rect();
            drect.setHeight(typingTestEdit()->height() + 7);
            painter.drawText(drect, Qt::AlignCenter, "Tap to focus in!");
        }
    }

    void reset()
    {
        typingTestEdit()->countMistakes = typingTestEdit()->countRightSymbol = typingTestEdit()->time = 0;
        setPlainText(typingTestEdit()->plainText);
    }

protected slots:

    void repeat()
    {
        typingTestEdit()->timer->stop();
        reset();
        isTimeout();
    }

    void isTimeout()
    {
        if (isVisible())
        {
            cpmLabel()->setText(QString("CPM: ") + typingTestEdit()->curCpm());
            timeLabel()->setText(typingTestEdit()->curTime());
        }
        else
        {
            typingTestEdit()->timer->stop();
            reset();
        }
    }

    void showResult()
    {
        emit newResult(typingTestEdit()->plainText + DELITOR + typingTestEdit()->curCpm() + DELITOR+ typingTestEdit()->curAcc() + DELITOR + QString::number(typingTestEdit()->countMistakes));
        QMessageBox msgBox;
        QString message = QString("Your results:\nCMP: ") + typingTestEdit()->curCpm() + QString("\nAccuracy: ") + typingTestEdit()->curAcc() + QString("\nMistakes: ") + QString::number(typingTestEdit()->countMistakes);
        msgBox.setText(message);
        msgBox.setStyleSheet("QWidget { background-color: #1f2029; color: #333;font-family: Noto Sans Mono;font-size: 28px;font-weight: 500;color: #6d7887; }"
                             "QPushButton { background-color: #0078d7; color: white; border: none; padding: 5px; border-radius: 5px; }");
        msgBox.exec();
        repeat();
    }

    signals:
    void newResult(const QString);
    
};

class RepeatTypingTest : public TypingTest
{
    Q_OBJECT
public:
    RepeatTypingTest(QWidget *parent = nullptr) : TypingTest(parent)
    {
        readFromFile("data/texts.txt");
        next();
        connect(nextButton(), &QAbstractButton::clicked, this, &next);
    }

private:
    void next()
    {
        static auto it = texts.begin();
        setPlainText(*it);
        ++it;
    }

    void readFromFile(const QString &filename)
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            texts.append(line);
        }

        file.close();
    }

    CircularLinkedList<QString> texts;
};

class LessonTypingTest : public TypingTest
{
    Q_OBJECT
public:
    LessonTypingTest(QWidget *parent = nullptr) : TypingTest(parent)
    {
        QHBoxLayout *hLayout = findChild<QHBoxLayout *>();
        if (hLayout)
        {
            hLayout->insertWidget(0, createQuitButton());
        }
    }

    ButtonWithHover *quitButton()
    {
        return findChild<ButtonWithHover *>(TYPING_TEST_QUIT_BUTTON_OBJECT_NAME);
    }
private:
    ButtonWithHover *createQuitButton()
    {
        ButtonWithHover *btn = Page::createBaseButton(this);
        btn->setIcon(QIcon(QUIT_BUTTON_ICON_PATH));
        btn->setObjectName(TYPING_TEST_QUIT_BUTTON_OBJECT_NAME);
        btn->upldateIconColor();
        btn->setIconSize(BASIC_ICON_SIZE);
        connect(btn, &QAbstractButton::clicked, this, &hide);
        return btn;
    }



};

#endif