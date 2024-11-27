#include <QApplication>
#include "include/mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    try
    {
        MainWindow *w = new MainWindow(MAIN_WINDOW_NAME, MIN_MAIN_WINDOW_WIDHT, MIN_MAIN_WINDOW_HEIGHT);
        w->show();
        app.exec();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(ex.what()), QMessageBox::Ok);
    }
    return 0;
}
