#include "include/mainwindow.h"
int main(int argc, char **argv)
{
    try
    {
        QApplication app(argc, argv);
        MainWindow *w = new MainWindow;
        w->show();
        app.exec();
    }
    catch (const BaseException &ex)
    {
        qDebug() << QString("An error occurred: %1").arg(ex.what());
    }
    return 0;
}
