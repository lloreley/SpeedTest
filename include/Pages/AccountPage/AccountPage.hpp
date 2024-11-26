#ifndef ACCOUNT_PAGE_HPP
#define ACCOUNT_PAGE_HPP

#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QWidget>
#include <QScrollArea>
#include "../Page.hpp"
#include "../../Accounts/User.hpp"
#include "../../Exception/Exception.hpp"

class AccountPage : public Page
{
    Q_OBJECT
public:
    AccountPage(QWidget *parent = nullptr) : Page(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 50, 20);
        layout->setSpacing(30);
    }

    QLabel *createNameLabel()
    {
        if (!user)
            throw NullPointerException("user");
        QLabel *label = new QLabel(this);
        label->setText("Name:  " + user->getName());
        label->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
        return label;
    }
    QLabel *createEmailLabel()
    {
        if (!user)
            throw NullPointerException("user");
        QLabel *label = new QLabel(this);
        label->setText("Email:  " + user->getEmail());
        label->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
        return label;
    }
    QLabel *createDateRegistrationLabel()
    {
        if (!user)
            throw NullPointerException("user");
        QLabel *label = new QLabel(this);
        label->setText("Date of registration:  " + user->getDateRegistration());
        label->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
        return label;
    }
    QLabel *createHistoryLabel()
    {
        QLabel *label = new QLabel(this);
        label->setText("Testing history");
        return label;
    }

    void setUser(BaseUser *us) noexcept
    {
        try
        {
            user = us;
            findChild<QVBoxLayout *>()->addWidget(createNameLabel());
            findChild<QVBoxLayout *>()->addWidget(createEmailLabel());
            findChild<QVBoxLayout *>()->addWidget(createDateRegistrationLabel());
            findChild<QVBoxLayout *>()->addWidget(createHistoryLabel());

            emit userInstalled();
        }
        catch (BaseException ex)
        {
            qDebug() << ex.what();
        }
    }

    BaseUser *getUser()
    {
        return user;
    }

public slots:

    void show()
    {
        Page::show();
        QString userData = user->getUserData();
        if (userData != "" && layout()->count() < 5)
        {
            addResultsFromString(userData.mid(userData.indexOf("Typing history")));
            this->setStyleSheet(UserDataBase::readAllFile(STATIC_STYLES_FILE_PATH));
        }
    }

    void addResult(const QString &resultString)
    {
        QStringList fields = resultString.split(DELITOR);
        if (fields.size() == 4)
        {
            QString text = fields[0];
            QString charactersPerMinute = fields[1];
            QString accuracy = fields[2];
            QString countMistakes = fields[3];

            QWidget *resultWidget = new QWidget(this);
            QVBoxLayout *resultLayout = new QVBoxLayout(resultWidget);
            resultWidget->setStyleSheet("font-size: 20px; border-radius: 12px;  padding: 0 25px; background-color: #1f2029; ");
            QLabel *textLabel = new QLabel("Plain text: " + text, resultWidget);
            textLabel->setWordWrap(true);
            resultLayout->addWidget(textLabel);
            resultLayout->addWidget(new QLabel("Char per minutes: " + charactersPerMinute, resultWidget));
            resultLayout->addWidget(new QLabel("Accuracy: " + accuracy, resultWidget));
            resultLayout->addWidget(new QLabel("Count mistakes: " + countMistakes, resultWidget));

            findChild<QVBoxLayout *>()->addWidget(resultWidget);
        }
    }

    void addResultsFromString(const QString &resultsString)
    {
        QStringList results = resultsString.split("\n");
        for (const QString &str : results)
        {
            addResult(str);
        }
    }

private:
    BaseUser *user;

    signals:
    void userInstalled();
};

#endif