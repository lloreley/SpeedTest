#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <QFrame>
#include <vector>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

// #define QWERTY

class Keyboard : public QFrame
{

public:
    Keyboard(QWidget *parent) : QFrame(parent)
    {
        int pos = 0;
        keys = {
            "q",
            "w",
            "e",
            "r",
            "t",
            "y",
            "u",
            "i",
            "o",
            "p",
            "[",
            "]",
            "a",
            "s",
            "d",
            "f",
            "g",
            "h",
            "j",
            "k",
            "l",
            ";",
            "'",
            "z",
            "x",
            "c",
            "v",
            "b",
            "n",
            "m",
            ",",
            ".",
            "/",
        };
        cols.push_back(12);
        cols.push_back(11);
        cols.push_back(10);
        rowsLayout = new QVBoxLayout(this);
        for (int i = 0; i < cols.size(); ++i)
        {
            QHBoxLayout *colsLayout = new QHBoxLayout;
            for (int j = 0; j < cols[i]; ++j)
            {
                QPushButton *key = new QPushButton(keys[pos], this);
                key->setFixedSize(QSize(50, 50));
                colsLayout->addWidget(key);
                ++pos;
            }
            rowsLayout->addLayout(colsLayout);
        }
    }

private:
    QVBoxLayout *rowsLayout;
    // size_t rows;
    std::vector<size_t> cols;
    std::vector<QString> keys;
};

#endif