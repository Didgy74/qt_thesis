#include <QFile>
#include <QImage>
#include <QApplication>

#include "httpHandling/networkcontroller.h" // Get JSON syle data from Maptiler

#include "tilerenderrules.h"
#include "vectortile.h"
#include "tilerenderer.h"
#include "vector_tile.qpb.h"


const QString url ="https://api.maptiler.com/maps/streets/style.json?key=bWo4cKyYIs8K3SkrLiTk"; // Constant url for testing

const QString url2 ="https://api.maptiler.com/maps/basic-v2/style.json?key=bWo4cKyYIs8K3SkrLiTk"; // Const url for testing against Matthias' example
int main(int argc, char *argv[])
{

    // HTTP Setup
    //
    // Commented away to not make unnecessary requests to MapTiler.
    // It seems to work and return appropriate errors when bad urls are provided
    //
    // Start the application (required to make the network request)
    QApplication a(argc, argv);

    // Set up the httpHandler
    NetworkController networkController;

    // Make http request to get a json stylesheet
    //QByteArray responseData = networkController.sendRequest(url2);
    //qDebug() << "Response: " << responseData;

    QJsonDocument doc;
    QJsonParseError parseError;

    // Loading file from disk
    QFile fStyle(":/testData/tiles.json");
    fStyle.open(QIODevice::ReadOnly);
    doc = QJsonDocument::fromJson(fStyle.readAll(), &parseError);

    // Using data from MapTiler API
    //doc = QJsonDocument::fromJson(responseData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
        return 0;
    }

    TileRenderRules *rules = TileRenderRules::fromJson(doc);

    // Read map vector tile from file
    QFile fTile(":/testData/z12x2170y1190.mvt");
    fTile.open(QIODevice::ReadOnly);
    QByteArray data = fTile.readAll();


    /*TODO: Get map vector tile by making a get request to mapTiler API*/
    // Eimen's code (or maybe Cecilia's) could/should go here.

    // Generate a tile to draw
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

    //image.save("C:\\Users\\cecil\\Desktop\\test3-img.png");
}
