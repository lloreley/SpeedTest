#include "../include/TypingLessons.h"

Lesson::Lesson(const QString &lessonData, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    CHECK_PTR(layout)
    layout->addWidget(createNameLabel(FileDataBase::extractValueFromStrWithSelector(lessonData, NAME_SELECTOR)), 3);
    layout->addStretch(1);
    layout->addWidget(createStartButton(), 1);
    text = FileDataBase::extractValueFromStrWithSelector(lessonData, TEXT_SELECTOR);
    id = FileDataBase::extractValueFromStrWithSelector(lessonData, ID_SELECTOR).toInt();
    setContentsMargins(20, 20, 20, 20);
    setProperty(TYPING_LESSONS_PROPERTY);
    setStyleSheet("background: #1f2029;");
}
void Lesson::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};
const QString &Lesson::getText() const noexcept
{
    return text;
}
QLabel *Lesson::createNameLabel(const QString &name)
{
    QLabel *label = new QLabel(this);
    CHECK_PTR(label)
    label->setText(name);

    label->setProperty(TYPING_LESSONS_PROPERTY);
    return label;
}
ButtonWithHover *Lesson::createStartButton()
{
    ButtonWithHover *btn = new ButtonWithHover(this);
    CHECK_PTR(btn)
    btn->setButtonStyle(FileDataBase::loadStyleFromFile(DYNAMIC_STYLES_FILE_PATH,
                                                        "QPushButton.TypingLessons"));
    btn->setHoverActive(true);
    btn->setStartBackgroundColor(LIGHT_GRAY);
    btn->setEndBackgroundColor(DARK_BLUE);
    btn->setStartTextColor(GRAY);
    btn->setEndTextColor(GOLD);

    btn->setText("Start");
    btn->setProperty(TYPING_LESSONS_PROPERTY);
    return btn;
}
ButtonWithHover *Lesson::startButton()
{
    ButtonWithHover *startBtn = findChild<ButtonWithHover *>();
    CHECK_PTR(startBtn)
    return startBtn;
}

TypingLessons::TypingLessons(QWidget *parent) : Page(parent), countLessons{}, currentId{}
{
    setup();
    createLessons();
}
void TypingLessons::setup()
{
QVBoxLayout *layout = new QVBoxLayout(this);
    CHECK_PTR(layout)

    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(20);
    setObjectName(TYPING_LESSONS_OBJECT_NAME);
}
TypingLessons::~TypingLessons()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
}
void TypingLessons::isStartLesson()
{
    Lesson *lesson = qobject_cast<Lesson *>(sender()->parent());
    if (lesson)
    {
        currentId = lesson->id;
        emit start(lesson->text);
        this->hide();
    }
}
void TypingLessons::createLessons()
{
    for (int i = 1;; ++i)
    {
        QString filename = DATA_LESSONS_PATH + QString::number(i) + TXT_END;
        QFile file(filename);
        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QString content = in.readAll();
                Lesson *lesson = new Lesson(content, this);
                connect(lesson->startButton(), &QAbstractButton::clicked, this, &isStartLesson);
                findChild<QVBoxLayout *>()->addWidget(lesson);
                file.close();
                ++countLessons;
            }
        }
        else
        {
            break;
        }
    }
}
void TypingLessons::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
};
