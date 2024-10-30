#include <QApplication>
#include "include/mainwindow.hpp"
#include "include/Logger.hpp"




int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    MainWindow *w = new MainWindow(MAIN_WINDOW_NAME, MIN_WIDHT, MIN_HEIGHT);
    // QWidget* slider = new QWidget(w);
    // slider->setGeometry(QRect(0, 0, MIN_LOGIN_WINDOW_WIDHT / 2, MIN_LOGIN_WINDOW_HEIGHT));
    // slider->setStyleSheet(LEFT_SLIDER_STYLE);
    // w->login();
    // QWidget* w1 = new QWidget(w);
    // w1->setStyleSheet("background-color: red");
    // QPushButton* button = new QPushButton(w);
    // button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    // button->setFixedSize(w->size());
    // button->setMaximumSize(w->maximumSize());
    

    w->show();
    return app.exec();
}