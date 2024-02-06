#include <QFile>
#include <QImage>
#include <QApplication>

//#include "httpHandling/httphandler.h" // Get JSON data from Maptiler

#include "tilerenderrules.h"
#include "vectortile.h"
#include "tilerenderer.h"
#include "vector_tile.qpb.h"


const QUrl url =QUrl("https://api.maptiler.com/maps/streets/style.json?key=bWo4cKyYIs8K3SkrLiTk"); // Constant url for testing

int main(int argc, char *argv[])
{
    /* HTTP Setup
     *
     * Commented away to not make unnecessary requests to MapTiler.
     * It seems to work and return appropriate errors when bad urls are provided
     *
    // Start the application (required to make the network request)
    QApplication a(argc, argv);

    // Set up the httpHandler
    HTTPHandler httpHandler;

    // Set up request to httpHandler
    QNetworkRequest request(url);

    // Make http request to get a json stylesheet
    httpHandler.HTTPGetData(request);
    */

    QJsonDocument doc;
    QJsonParseError parseError;

    QFile fStyle(":/testData/tiles.json");
    fStyle.open(QIODevice::ReadOnly);
    doc = QJsonDocument::fromJson(fStyle.readAll(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
        return 0;
    }

    TileRenderRules *rules = TileRenderRules::fromJson(doc);

    QFile fTile(":/testData/z12x2170y1190.mvt");
    fTile.open(QIODevice::ReadOnly);
    QByteArray data = fTile.readAll();

    VectorTile tile;
    tile.load(data);

//    QRect br = tile.boundingRect();
//    qDebug() << br;

    QImage image(QSize(4096, 4096), QImage::Format_RGBA8888);
    QPainter p(&image);

    TileRenderer renderer;
    renderer.m_rules = *rules;
    renderer.m_zoomLevel = 12;
    renderer.render(&p, tile);

    image.save("C:\\Users\\cecil\\Desktop\\z12x2170y1190.png");
}
