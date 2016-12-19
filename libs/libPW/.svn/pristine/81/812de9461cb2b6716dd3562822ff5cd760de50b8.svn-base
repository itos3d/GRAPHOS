#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTranslator>
#include <QTextStream>
#include <QTime>
#include <QVector>

#include <stdio.h>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "OpenCVKpM.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(),
//                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    a.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load(":/OpenCV_kpm" + QLocale::system().name());
    app.installTranslator(&appTranslator);

    QTextStream qout(stdout);
    QStringList args = app.arguments();
    if (args.count() < 2)
    {
        cerr <<QObject::tr("Argument required").toStdString()<< endl;
        return 1;
    }

    QTime timeProcess;
    timeProcess.start();
    QString parametersFileName=args[1];

    QString strError;

    PW::OpenCVKpM openCVKpm;

    // Paso 1: Leer el fichero de parámetros
    QString msg=QObject::tr("Step   1: Reading parameters file:\n          %1").arg(parametersFileName);
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.readParameterFile(parametersFileName,strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    qout<<msg<<endl;

    // Paso 2: Leer el fichero de pares de imagenes a procesar
    msg=QObject::tr("Step   2: Reading images files and image pairs");
    qout<<msg<<endl;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.readImagePairsFileName(strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    int numberOfImages=0;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.getNumberOfImages(numberOfImages,strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    int numberOfImagePairs=0;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.getNumberOfImagePairs(numberOfImagePairs,strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    msg=QObject::tr("          ... There are %1 images").arg(numberOfImages);
    msg+="\n";
    msg+=QObject::tr("          ... There are %1 image pairs").arg(numberOfImagePairs);
    msg+="\n";
    msg+=QObject::tr("          ... Successfully completed");

    // Paso 3: Obtener puntos de interés en las imágenes
    qout<<msg<<endl;
    msg=QObject::tr("Step   3: Detecting key points and their descriptors in images:");
    qout<<msg<<endl;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.keyPointsDetections(strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    msg=QObject::tr("          ... Successfully completed");
    qout<<msg<<endl;

    // Paso 4: Obtener puntos de interés en las imágenes
    msg=QObject::tr("Step   4: Matching images:");
    qout<<msg<<endl;
    QMap<QString,QVector<vector<DMatch> > > imagesPairsMatches;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.matching(strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    int imagePairsProcessed=0;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.getNumberOfImagePairsProcessed(imagePairsProcessed,strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    msg=QObject::tr("          ... Successfully completed");
    qout<<msg<<endl;

    int step=5;
    bool applyOutliersDetection=false;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.getApplyOutliersDetection(applyOutliersDetection,strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    if(applyOutliersDetection)
    {
        bool printReport=true;
        msg=QObject::tr("Step   5: Detecting outliers in matches:");
        qout<<msg<<endl;
        if(OPENCV_KPM_NO_ERROR!=openCVKpm.detectOutliersInMatches(printReport,
                                                                  strError))
        {
            cerr<<strError.toStdString()<<endl;
            return 1;
        }
        msg=QObject::tr("          ... Successfully completed");
        qout<<msg<<endl;
        step++;
    }

    msg=QObject::tr("Step   %1: Writing matches files:").arg(step);
    qout<<msg<<endl;
    if(OPENCV_KPM_NO_ERROR!=openCVKpm.writeMatchesFiles(strError))
    {
        cerr<<strError.toStdString()<<endl;
        return 1;
    }
    msg=QObject::tr("          ... Successfully completed");
    qout<<msg<<endl;

    double seconds=timeProcess.elapsed()/1000.0;
    int minutes=0;
    while(seconds>59.0)
    {
        seconds=seconds-60.0;
        minutes++;
    }
    int hours=0;
    while(minutes>59)
    {
       minutes=minutes-60;
       hours++;
    }
    int days=0;
    while(hours>23)
    {
        hours=hours-24;
        days++;
    }

    msg=QObject::tr("processing time for %1 images and %2 image pairs: %3 days, %4 hours, %5 minutes, %6 seconds")
            .arg(numberOfImages)
            .arg(imagePairsProcessed)
            .arg(QString::number(days))
            .arg(QString::number(hours))
            .arg(QString::number(minutes))
            .arg(QString::number(seconds,'f',3));
    qout<<msg<<endl;

    return(1);
    //return app.exec();
}
