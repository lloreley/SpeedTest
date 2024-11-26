#include <QApplication>
#include "include/mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    try
    {
        MainWindow *w = new MainWindow(MAIN_WINDOW_NAME, MIN_MAIN_WINDOW_WIDHT, MIN_MAIN_WINDOW_HEIGHT);
        w->show();
    }
    catch (const BaseException &ex)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("An error occurred");
        msgBox.setInformativeText(ex.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        std::exit(0);
    }
    return app.exec();
}
