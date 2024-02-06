#include "httphandler.h"

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>

HTTPHandler::HTTPHandler() {

}

QByteArray HTTPHandler :: HTTPGetData(QNetworkRequest request) {
    // Create the network access manager
    QNetworkAccessManager manager;

    // Perform the GET request
    QNetworkReply *reply = manager.get(request);

    // Create an event loop to wait for the request to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return QByteArray("");
    }

    // Process the response
    QByteArray responseData = reply->readAll();
    qDebug() << "Response:" << responseData;

    // Clean up
    reply->deleteLater();

    // Return response
    return responseData;
}
