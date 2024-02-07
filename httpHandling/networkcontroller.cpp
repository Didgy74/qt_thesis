#include "networkcontroller.h"

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>

NetworkController::NetworkController(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkController::finished);
}

NetworkController::~NetworkController()
{
    delete manager;
}

QByteArray NetworkController::sendRequest(QString url)
{
    this->url = url;
    request.setUrl(QUrl(url));

    // Perform the GET request
    QNetworkReply *reply = manager->get(request);

    // Create an event loop to wait for the request to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return QByteArray("Error parsing request.");
    }

    // Process the response
    QByteArray responseData = reply->readAll();
    //qDebug() << "Response: " << responseData; Used for debugging

    // Clean up
    reply->deleteLater();

    // Return response
    return responseData;
}
