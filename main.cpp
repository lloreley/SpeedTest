#include <QApplication>
#include "include/mainwindow.hpp"
#include "include/Logger.hpp"

#include <iostream>

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    MainWindow *w = new MainWindow(MAIN_WINDOW_NAME, MIN_WIDHT, MIN_HEIGHT);
    w->show();
    return app.exec();
}