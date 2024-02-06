#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <QNetworkAccessManager>

class HTTPHandler
{
public:
    HTTPHandler();

    QByteArray HTTPGetData(QNetworkRequest request);
};

#endif // HTTPHANDLER_H
