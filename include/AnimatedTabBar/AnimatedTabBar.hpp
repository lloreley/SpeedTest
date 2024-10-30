#ifndef ANIMETED_TAB_BAR
#define ANIMETED_TAB_BAR

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QPropertyAnimation>

#define ZERO_SPACING 0

using side_t = int;

namespace TabBar
{

    enum SIDES
    {
        LEFT_S = 0,
        RIGHT_S,
        TOP_S,
        BOTTOM_S
    };

    class AnimatedTabBar : public QWidget
    {
        Q_OBJECT

    public:
        AnimatedTabBar(QBoxLayout *(*childLayoutAllocator)(), QSize tab_size, int tab_count,
                       double compare_coefficient = 1.5, QWidget *parent = nullptr);
        ~AnimatedTabBar();

        int getTabCount() const noexcept;
        QSize getTabSize() const noexcept;
        side_t getSide() const noexcept;
        double getCoeffiient() const noexcept;
        int getDuration() const noexcept;
        void setDuration(int duration) noexcept;
        QEasingCurve getEasingCurve() const noexcept;
        void setEasignCurve(QEasingCurve easignCurve)noexcept;
        virtual bool setSide(side_t side) = 0;

    protected:
        QBoxLayout *layout;
        QSize tabSize;
        int tabCount;
        double compareCoefficient;
        side_t side;
        int duration;
        QEasingCurve easignCurve;

        void isMouseEnterInButton(QWidget *button);
        void isMouseLeaveFromButton(QWidget *button);
        bool eventFilter(QObject *o, QEvent *e);
    };
}

#endif

// bool AnimatedTabBar::eventFilter(QObject *o, QEvent *e)
// {
//     for (int i = 0; i < layout->count(); ++i)
//     {
//         if (o == layout->itemAt(i)->layout()->itemAt(0)->widget())
//         {
//             QVBoxLayout *layout_ = qobject_cast<QVBoxLayout *>(layout->itemAt(i)->layout());
//             QPushButton *button = qobject_cast<QPushButton *>(o);
//             QPropertyAnimation *animation = new QPropertyAnimation(button, "minimumHeight");
//             animation->setEasingCurve(QEasingCurve::OutQuad);
//             animation->setDuration(350);
//             if (e->type() == QEvent::Enter)
//             {
//                 animation->setEndValue(button->maximumHeight());
//                 animation->start(QAbstractAnimation::DeleteWhenStopped);
//                 return true;
//             }
//             if (e->type() == QEvent::Leave)
//             {
//                 animation->setEndValue(50);
//                 animation->start();
//                 return true;
//             }
//         }
//     }
//     return QWidget::eventFilter(o, e);
// }