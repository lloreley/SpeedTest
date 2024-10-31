#include <QApplication>
#include "include/mainwindow.hpp"
// #include "include/Logger.hpp"

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    MainWindow *w = new MainWindow(MAIN_WINDOW_NAME, MIN_WIDHT, MIN_HEIGHT);

    w->show();
    return app.exec();
}



// #include <QApplication>
// // #include "test.hpp"

// int main(int argc, char **argv)
// {
//     QApplication app(argc, argv);
//     QWidget *w = new QWidget();
//     ChromeButtom *b = new ChromeButtom(w);
//     w->show();
//     return app.exec();
// }