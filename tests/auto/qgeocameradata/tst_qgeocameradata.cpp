/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "qgeocameradata_p.h"

QT_USE_NAMESPACE

// For testing the setters and getters of the QGeoCoordinateInterpolator shared pointer
class QGeoCoordinateInterpolatorTest : public QGeoCoordinateInterpolator
{
public:
    QGeoCoordinateInterpolatorTest(){}
    ~QGeoCoordinateInterpolatorTest(){}
    QGeoCoordinate interpolate(const QGeoCoordinate &start, const QGeoCoordinate &end, qreal progress){
        Q_UNUSED(start);
        Q_UNUSED(end);
        Q_UNUSED(progress);
        return QGeoCoordinate();
    }
};


class tst_QGeoCameraData : public QObject
{
    Q_OBJECT

public:
    tst_QGeoCameraData();

private:
    void populateCameraData();

private Q_SLOTS:
    void constructorTest_data();
    void constructorTest();
    void centerTest();
    void bearingTest();
    void tiltTest();
    void rollTest();
    void zoomLevelTest();
    void coordinateInterpolatorTest();
    void operatorsTest_data();
    void operatorsTest();
};

tst_QGeoCameraData::tst_QGeoCameraData()
{
}


void tst_QGeoCameraData::populateCameraData()
{
    QTest::addColumn<QGeoCoordinate>("center");
    QTest::addColumn<double>("bearing");
    QTest::addColumn<double>("tilt");
    QTest::addColumn<double>("roll");
    QTest::addColumn<double>("zoomLevel");
    QTest::newRow("zeros") << QGeoCoordinate() << 0.0 << 0.0 << 0.0 << 0.0;
    QTest::newRow("valid") << QGeoCoordinate(10.0,20.5,30.8) << 0.1 << 0.2 << 0.3 << 2.0;
    QTest::newRow("negative values") << QGeoCoordinate(-50,-20,100) << -0.1 << -0.2 << -0.3 << 1.0;
}

void tst_QGeoCameraData::constructorTest_data(){
    populateCameraData();
}

void tst_QGeoCameraData::constructorTest()
{
    QFETCH(QGeoCoordinate, center);
    QFETCH(double, bearing);
    QFETCH(double, tilt);
    QFETCH(double, roll);
    QFETCH(double, zoomLevel);

    // constructor test with default values
    QGeoCameraData cameraData;
    QGeoCameraData cameraData2(cameraData);
    QCOMPARE(cameraData.center(), cameraData2.center());
    QCOMPARE(cameraData.bearing(), cameraData2.bearing());
    QCOMPARE(cameraData.tilt(), cameraData2.tilt());
    QCOMPARE(cameraData.roll(), cameraData2.roll());
    QCOMPARE(cameraData.zoomLevel(), cameraData2.zoomLevel());

    // constructor test after setting values
    cameraData.setCenter(center);
    cameraData.setBearing(bearing);
    cameraData.setTilt(tilt);
    cameraData.setRoll(roll);
    cameraData.setZoomLevel(zoomLevel);
    QGeoCameraData cameraData3(cameraData);
    // test the correctness of the constructor copy
    QCOMPARE(cameraData3.center(), center);
    QCOMPARE(cameraData3.bearing(), bearing);
    QCOMPARE(cameraData3.tilt(), tilt);
    QCOMPARE(cameraData3.roll(), roll);
    QCOMPARE(cameraData3.zoomLevel(), zoomLevel);
    // verify that values have not changed after a constructor copy
    QCOMPARE(cameraData.center(), cameraData3.center());
    QCOMPARE(cameraData.bearing(), cameraData3.bearing());
    QCOMPARE(cameraData.tilt(), cameraData3.tilt());
    QCOMPARE(cameraData.roll(), cameraData3.roll());
    QCOMPARE(cameraData.zoomLevel(), cameraData3.zoomLevel());
}


void tst_QGeoCameraData::centerTest()
{
    QGeoCameraData cameraData; //center currently default to (-27.5, 153)
    cameraData.setCenter(QGeoCoordinate(10.0,20.4,30.8));
    QCOMPARE(cameraData.center(),QGeoCoordinate(10.0,20.4,30.8));
}

void tst_QGeoCameraData::bearingTest(){
    QGeoCameraData cameraData;
    QCOMPARE(cameraData.bearing(),0.0);
    cameraData.setBearing(0.1);
    QCOMPARE(cameraData.bearing(),0.1);

    QGeoCameraData cameraData2 = cameraData;
    QCOMPARE(cameraData2.bearing(),0.1);
    cameraData.setBearing(0.2);
    QCOMPARE(cameraData2.bearing(),0.1);
}

void tst_QGeoCameraData::tiltTest(){
    QGeoCameraData cameraData;
    QCOMPARE(cameraData.tilt(),0.0);
    cameraData.setTilt(0.4);
    QCOMPARE(cameraData.tilt(),0.4);

    QGeoCameraData cameraData2 = cameraData;
    QCOMPARE(cameraData2.tilt(),0.4);
    cameraData.setTilt(0.5);
    QCOMPARE(cameraData2.tilt(),0.4);
}

void tst_QGeoCameraData::rollTest(){
    QGeoCameraData cameraData;
    QCOMPARE(cameraData.roll(),0.0);
    cameraData.setRoll(0.5);
    QCOMPARE(cameraData.roll(),0.5);

    QGeoCameraData cameraData2 = cameraData;
    QCOMPARE(cameraData2.roll(),0.5);
    cameraData.setRoll(0.6);
    QCOMPARE(cameraData2.roll(),0.5);
}

void tst_QGeoCameraData::zoomLevelTest(){
    QGeoCameraData cameraData; //zoom level currently defaults to 9.0
    cameraData.setZoomLevel(8.0);
    QCOMPARE(cameraData.zoomLevel(),8.0);

    QGeoCameraData cameraData2 = cameraData;
    QCOMPARE(cameraData2.zoomLevel(),8.0);
    cameraData.setZoomLevel(9.0);
    QCOMPARE(cameraData2.zoomLevel(),8.0);
}

void tst_QGeoCameraData::coordinateInterpolatorTest(){
    QGeoCameraData cameraData;
    QVERIFY2(cameraData.coordinateInterpolator().isNull(), "Default coordinate interpolator shared point is not null");
    QSharedPointer<QGeoCoordinateInterpolator> testPointer = QSharedPointer<QGeoCoordinateInterpolator>(new QGeoCoordinateInterpolatorTest());
    cameraData.setCoordinateInterpolator(testPointer);
    QVERIFY2(!cameraData.coordinateInterpolator().isNull(), "Coordinate interpolator shared point is null");
}

void tst_QGeoCameraData::operatorsTest_data(){
    populateCameraData();
}

void tst_QGeoCameraData::operatorsTest(){
    QGeoCameraData cameraData;
    QGeoCameraData cameraData2;
    QVERIFY2(cameraData == cameraData2, "Camera data with default values are not copied correctly");

    QFETCH(QGeoCoordinate, center);
    QFETCH(double, bearing);
    QFETCH(double, tilt);
    QFETCH(double, roll);
    QFETCH(double, zoomLevel);
    cameraData.setCenter(center);
    cameraData.setBearing(bearing);
    cameraData.setTilt(tilt);
    cameraData.setRoll(roll);
    cameraData.setZoomLevel(zoomLevel);

    QGeoCameraData cameraData3;
    cameraData3 = cameraData;
    QVERIFY2(cameraData == cameraData3, "Camera data not copied correctly");

    // test QGeoCameraData pairs where they differ in one field
    QGeoCameraData cameraData4;
    cameraData4 = cameraData;
    cameraData4.setCenter(QGeoCoordinate(10.0,20.0,30.0));
    QVERIFY2(cameraData != cameraData4, "Camera data should be different");
    QGeoCameraData cameraData5;
    cameraData5 = cameraData;
    cameraData5.setBearing(bearing+1.0);
    QVERIFY2(cameraData != cameraData5, "Camera data should be different");
    QGeoCameraData cameraData6;
    cameraData6 = cameraData;
    cameraData6.setTilt(tilt+0.1);
    QVERIFY2(cameraData != cameraData6, "Camera data should be different");
    QGeoCameraData cameraData7;
    cameraData7 = cameraData;
    cameraData7.setRoll(roll+0.1);
    QVERIFY2(cameraData != cameraData7, "Camera data should be different");
    QGeoCameraData cameraData8;
    cameraData8 = cameraData;
    cameraData8.setZoomLevel(zoomLevel+1.0);
    QVERIFY2(cameraData != cameraData8, "Camera data should be different");
}

QTEST_APPLESS_MAIN(tst_QGeoCameraData)

#include "tst_qgeocameradata.moc"