#ifndef SERVER_CLIENT_HPP
#define SERVER_CLIENT_HPP

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include "../defines.hpp"

class ServerClient : public QObject
{
    Q_OBJECT

public:
    ServerClient(QObject *parent = nullptr) : QObject(parent), nextBlockSize{}, isConnected(true)
    {
        socket = new QTcpSocket(this);
        socket->connectToHost(SERVER_IP, SERVER_PORT);
        connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
        connect(this, &ServerClient::messageReceived, this, &ServerClient::processMessage);
        keepAliveTimer = new QTimer(this);
        connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
        keepAliveTimer->start(KEEP_ALIGN_TIME);
    }
    ServerClient(QTcpSocket *s, QObject *parent = nullptr) : QObject(parent)
    {
        socket = s;
        connect(socket, &QTcpSocket::readyRead, this, &ServerClient::read);
        connect(this, &ServerClient::messageReceived, this, &ServerClient::processMessage);
        keepAliveTimer = new QTimer(this);
        connect(keepAliveTimer, &QTimer::timeout, this, &checkConnection);
        keepAliveTimer->start(KEEP_ALIGN_TIME);
    }

    QTcpSocket *getSocket()
    {
        return socket;
    }

public slots:
    void sendToServer(const QString &str)
    {
        if (socket->state() == QAbstractSocket::ConnectedState)
        {
            Data.clear();
            QDataStream out(&Data, QIODevice::WriteOnly);
            out << quint16(str.size());
            out << str;
            socket->write(Data);
            socket->flush();
        }
        else
        {
            emit connectionLost();
        }
    }

private slots:

    void tryConnectToServer()
    {
        if (socket->state() == QAbstractSocket::UnconnectedState)
        {
            socket->connectToHost(SERVER_IP, SERVER_PORT);
        }
    }

    void checkConnection()
    {
        if (isConnected)
        {
            isConnected = false;
        }
        else
        {
            tryConnectToServer();
            emit connectionLost();
        }
    }

    void processMessage(const QString &message)
    {
        qDebug() << "Received message:" << message;

        if (message == CHECK_CONNECTION_MESSAGE)
        {
            isConnected = true;
            sendToServer(CHECK_CONNECTION_MESSAGE);
        }
    }

    void read()
    {
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_14);
        while (socket->bytesAvailable() >= sizeof(quint16))
        {
            if (nextBlockSize == 0)
            {
                in >> nextBlockSize;
            }

            if (socket->bytesAvailable() >= nextBlockSize)
            {
                QString message;
                in >> message;
                nextBlockSize = 0;
                emit messageReceived(message);
            }
            else
                return;
        }
    }

private:
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize;
    QTimer *keepAliveTimer;
    bool isConnected;

signals:
    void messageReceived(QString message);
    void connectionLost();
};

#endif