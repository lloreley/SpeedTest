#ifndef USER_H
#define USER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include "defines.h"
#include "FileDataBase.h"

class ServerClient : public QObject
{
    Q_OBJECT

public:
    ServerClient(QObject *parent = nullptr);
    ServerClient(QTcpSocket *skt, QObject *parent = nullptr);
    ~ServerClient();
    QTcpSocket *getSocket();
    void setSocket(QTcpSocket *socket);
public slots:
    void sendToServer(const QString &str);
protected slots:
    virtual void processMessage(const QString &message);
private slots:

    void tryConnectToServer();
    void checkConnection();
    void read();

protected:
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize;
    QTimer *keepAliveTimer;
    bool isConnected;

signals:
    void messageReceived(QString message);
    void connectionLost();
    void disconnected();
};

class BaseUser : public ServerClient
{
    Q_OBJECT
public:
    BaseUser(QObject *parent = nullptr);
    BaseUser(QTcpSocket *skt, QObject *parent = nullptr);
    const QString getEmail();
    const QString getName();
    const QString getDateRegistration();
    const QString getUserData();
    void addTypingResult(const QString &newResult);

protected:
    QString userData;
    QString name;
    QString email;
    QString dateRegistration;

signals:
    void accountCreated();
    void accountNotCreated();
    void userNotFound();
    void passwordIncorrect();
    void loginSuccessful();
};

class UnauthorizedUser : public BaseUser
{
    Q_OBJECT
public:
    UnauthorizedUser(QObject *parent = nullptr);
    void processMessage(const QString &message) override;
};

class User : public BaseUser
{
    Q_OBJECT
public:
    User(QObject *parent = nullptr);
    User(QTcpSocket *skt, QObject *parent = nullptr);
    void setUserData(const QString &userData);
};

#endif
