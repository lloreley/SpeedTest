#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include "Logger.hpp"

#define MIN_HEIGHT 480
#define MIN_WIDHT 640
#define MAIN_WINDOW_NAME "Typing speed test"

class MainWindow : public QWidget
{
public:
    MainWindow(const char *windowTitle = nullptr,
               size_t minimumWidth = 0,
               size_t minimumHeight = 0,
               QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *label;

    void keyPressEvent(QKeyEvent *event) override
    {
        label->setText(event->text());
    }
};
#endif // MAINWINDOW_H
