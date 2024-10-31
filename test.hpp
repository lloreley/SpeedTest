#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>

class ChromeButtom : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    QColor background;
    QPropertyAnimation anim;

public:
    explicit ChromeButtom(QWidget *parent = nullptr);
    ChromeButtom(const QString &text, QWidget *parent = nullptr);

    QColor getBackground() const;
    void setBackground(const QColor &back);

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
};