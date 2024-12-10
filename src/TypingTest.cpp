#include "../include/TypingTest.h"

TypingTestEdit::TypingTestEdit(QWidget *parent) : QTextEdit(parent), nextChar{}, time{}, countMistakes{}
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
TypingTestEdit::~TypingTestEdit()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
void TypingTestEdit::paintEvent(QPaintEvent *event)
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
QString TypingTestEdit::curTime()
{
    QString curTime = (time / 60 < 10 ? (QString("0") + QString::number(time / 60)) : QString::number(time / 60)) + QString(":") +
                      (time % 60 < 10 ? (QString("0") + QString::number(time % 60)) : QString::number(time % 60));
    return curTime;
}
QString TypingTestEdit::curAcc()
{
    return (QString("%") + QString::number(((float)(countRightSymbol) / (countMistakes + countRightSymbol)) * 100, 'f', 2));
}
QString TypingTestEdit::curCpm()
{
    return QString::number(countRightSymbol * 60 / (time == 0 ? 1 : time));
}
void TypingTestEdit::inserRightSymbol()
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
void TypingTestEdit::insertWrongSymbol()
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
void TypingTestEdit::blurOn()
{
    if (blurEffect && blurEffect->blurRadius() == TYPING_TEST_ZERO_BLUR)
    {
        blurAnimation->setDirection(QAbstractAnimation::Forward);
        blurAnimation->start();
    }
}
void TypingTestEdit::keyPressEvent(QKeyEvent *event)
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
void TypingTestEdit::blurOff()
{
    if (blurEffect && blurEffect->blurRadius() == TYPING_TEST_MAX_BLUR)
    {
        blurAnimation->setDirection(QAbstractAnimation::Backward);
        blurAnimation->start();
    }
}
void TypingTestEdit::focusInEvent(QFocusEvent *event)
{
    blurOff();
    QWidget::focusInEvent(event);
}
void TypingTestEdit::focusOutEvent(QFocusEvent *event)
{
    blurOn();
    QWidget::focusOutEvent(event);
}
bool TypingTestEdit::isBlur()
{
    return blurEffect->blurRadius() == TYPING_TEST_MAX_BLUR;
}

TypingTest::TypingTest(QWidget *parent) : Page(parent)
{
    setup();
}
void TypingTest::setup()
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
TypingTest::~TypingTest()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
void TypingTest::hide()
{
    Page::hide();
    typingTestEdit()->timer->stop();
}
void TypingTest::show()
{
    Page::show();
    repeat();
}
QLabel *TypingTest::timeLabel()
{
    QLabel *timeLbl = findChild<QLabel *>(TYPING_TEST_TIME_LABEL_OBJECT_NAME);
    CHECK_PTR(timeLbl)
    return timeLbl;
}
QLabel *TypingTest::cpmLabel()
{
    QLabel *cmpLbl = findChild<QLabel *>(TYPING_TEST_CPM_LABEL_OBJECT_NAME);
    CHECK_PTR(cmpLbl)
    return cmpLbl;
}
ButtonWithHover *TypingTest::repeatButton()
{
    ButtonWithHover *repeatBtn = findChild<ButtonWithHover *>(TYPING_TEST_REPEAT_BUTTON_OBJECT_NAME);
    CHECK_PTR(repeatBtn)
    return repeatBtn;
}
ButtonWithHover *TypingTest::nextButton()
{
    ButtonWithHover *nextBtn = findChild<ButtonWithHover *>(TYPING_TEST_NEXT_BUTTON_OBJECT_NAME);
    CHECK_PTR(nextBtn)
    return nextBtn;
}
TypingTestEdit *TypingTest::typingTestEdit()
{
    TypingTestEdit *typingTE = findChild<TypingTestEdit *>(TYPING_TEST_LINE_OBJECT_NAME);
    CHECK_PTR(typingTE)
    return typingTE;
}
void TypingTest::setPlainText(const QString &plainText)
{
    QString htmlText = "<span style='color:  rgb(109, 120, 135); font-size: 24px;'>" + plainText + "</span>";
    typingTestEdit()->setHtml(htmlText);
    typingTestEdit()->plainText = plainText;
    typingTestEdit()->nextChar = typingTestEdit()->plainText.begin();
}
void TypingTest::reset()
{
    typingTestEdit()->countMistakes = typingTestEdit()->countRightSymbol = typingTestEdit()->time = 0;
    setPlainText(typingTestEdit()->plainText);
}
void TypingTest::repeat()
{
    typingTestEdit()->timer->stop();
    reset();
    isTimeout();
}
void TypingTest::isTimeout()
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
void TypingTest::showResult()
{
    emit newResult(typingTestEdit()->plainText + DELITOR + typingTestEdit()->curCpm() + DELITOR + typingTestEdit()->curAcc() + DELITOR + QString::number(typingTestEdit()->countMistakes));
    QMessageBox msgBox;
    QString message = QString("Your results:\nCMP: ") + typingTestEdit()->curCpm() + QString("\nAccuracy: ") + typingTestEdit()->curAcc() + QString("\nMistakes: ") + QString::number(typingTestEdit()->countMistakes);
    msgBox.setText(message);
    msgBox.setStyleSheet("QWidget { background-color: #1f2029; color: #333;font-family: Noto Sans Mono;font-size: 28px;font-weight: 500;color: #6d7887; }"
                         "QPushButton { background-color: #0078d7; font-size: 16px;color: white; border: none; padding: 5px; border-radius: 5px; }");
    msgBox.exec();
    repeat();
}
void TypingTest::paintEvent(QPaintEvent *event)
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
ButtonWithHover *TypingTest::createRepeatButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    CHECK_PTR(btn)
    btn->setIcon(QIcon(REPEAT_ICON_PATH));
    btn->setObjectName(TYPING_TEST_REPEAT_BUTTON_OBJECT_NAME);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    connect(btn, QAbstractButton::clicked, this, &repeat);
    return btn;
}
ButtonWithHover *TypingTest::createNextButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    CHECK_PTR(btn)
    btn->setIcon(QIcon(NEXT_BUTTON_ICON_PATH));
    btn->setObjectName(TYPING_TEST_NEXT_BUTTON_OBJECT_NAME);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    return btn;
}
QLabel *TypingTest::createCpmLabel()
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label);
    label->setObjectName(TYPING_TEST_CPM_LABEL_OBJECT_NAME);
    label->setText("CPM: 0");
    return label;
}
QLabel *TypingTest::createTimeLabel()
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label);
    label->setText(typingTestEdit()->curTime());
    label->setObjectName(TYPING_TEST_TIME_LABEL_OBJECT_NAME);
    return label;
}

RepeatTypingTest::RepeatTypingTest(QWidget *parent) : TypingTest(parent)
{
    readFromFile("data/texts.txt");
    next();
    connect(nextButton(), &QAbstractButton::clicked, this, &next);
}
RepeatTypingTest::~RepeatTypingTest()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
void RepeatTypingTest::next()
{
    static auto it = texts.begin();
    setPlainText(*it);
    ++it;
}
void RepeatTypingTest::readFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw FileOpenException(filename);
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        texts.append(line);
    }

    file.close();
}

LessonTypingTest::LessonTypingTest(QWidget *parent) : TypingTest(parent)
{
    QHBoxLayout *hLayout = findChild<QHBoxLayout *>();
    if (hLayout)
    {
        hLayout->insertWidget(0, createQuitButton());
    }
}
LessonTypingTest::~LessonTypingTest()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
ButtonWithHover *LessonTypingTest::quitButton()
{
    return findChild<ButtonWithHover *>(TYPING_TEST_QUIT_BUTTON_OBJECT_NAME);
}
ButtonWithHover *LessonTypingTest::createQuitButton()
{
    ButtonWithHover *btn = Page::createBaseButton(this);
    btn->setIcon(QIcon(QUIT_BUTTON_ICON_PATH));
    btn->setObjectName(TYPING_TEST_QUIT_BUTTON_OBJECT_NAME);
    btn->upldateIconColor();
    btn->setIconSize(BASIC_ICON_SIZE);
    connect(btn, &QAbstractButton::clicked, this, &hide);
    return btn;
}