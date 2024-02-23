#include <QTest>

#include "TileURL.h"
#include "Rendering.h"

#include <QObject>

class TestGetTile : public QObject
{
    Q_OBJECT

private slots:
    void readKey_returns_success_when_valid_key();
    void readKey_returns_failure_when_invalid_key();
    void getStyleSheet_returns_success_on_supported_stylesheet();
    void getStyleSheet_returns_failure_on_unsupported_stylesheet();
    //void renderingTests();
};


QTEST_MAIN(TestGetTile)
#include "testgettile.moc"


// Try to get a key that's correct
void TestGetTile::readKey_returns_success_when_valid_key() {
    TileURL tileURL;

    QString keyFromFile = tileURL.readKey("testkey.txt");
    QString keyString ="123*+abcDEF<>";

    QVERIFY(keyFromFile==keyString);
}

// Try to get a key that's wrong
void TestGetTile::readKey_returns_failure_when_invalid_key() {
    TileURL tileURL;

    QString keyFromFile = tileURL.readKey("testkey.txt");
    QString wrongKey ="IAmWrong";       //correct key = 123*+abcDEF<>

    QVERIFY(keyFromFile!=wrongKey);
}

/// Tests of getting styleshehets
// Get a supported stylesheet
// Note that this specific test will fail if an illegal key is provided
void TestGetTile:: getStyleSheet_returns_success_on_supported_stylesheet() {
    TileURL tileURL;
    QString key = tileURL.readKey("key.txt");

    std::pair<QByteArray, TileURL::ErrorCode> styleSheetURL =
        tileURL.getStylesheet(TileURL::styleSheetType::basic_v2, key);

    QVERIFY(styleSheetURL.second == TileURL::ErrorCode::success);
}

// Get a non-supported stylesheet
// Note that this specific test will fail if an illegal key is provided
void TestGetTile:: getStyleSheet_returns_failure_on_unsupported_stylesheet() {
    TileURL tileURL;
    QString key = tileURL.readKey("key.txt");

    std::pair<QByteArray, TileURL::ErrorCode> styleSheetURL =
        tileURL.getStylesheet(TileURL::styleSheetType::bright_v2, key);

    QVERIFY(styleSheetURL.second == TileURL::ErrorCode::unknownError);
}

/// Rendering tests
//  Nils: ?
/*
void TestGetTile::renderingTests() {
    auto result = Bach::CalcVisibleTiles(0.5, 0.5, 0.5, 0, 0);
    auto expected = QVector<TileCoord>{{0, 0, 0}};

    QVERIFY(result == expected);
}
*/