/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QDebug>

#include "MainWindowGRAPHOS.h"

void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
//         QMessageBox::information(0, QString("ASIFT Information"), QString(msg));
//         qDebug() << QString(msg);
         break;
     case QtWarningMsg:
         //QMessageBox::warning(0, QString("ASIFT Warning"), QString(msg));
         break;
     case QtCriticalMsg:
         QMessageBox::critical(0, QString("GRAPHOS Error"), QString(msg));
         break;
     case QtFatalMsg:
         QMessageBox::critical(0, QString("GRAPHOS Error"), QString(msg));
         abort();
     }
 }

int main(int argc, char *argv[])
{
    qInstallMsgHandler(myMessageOutput);
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(":/GRAPHOS_" + QLocale::system().name());
    a.installTranslator(&myappTranslator);

    bool useSpatialDatabase=true;
    MainWindowGRAPHOS w(useSpatialDatabase);
    w.showMaximized();

    return a.exec();
}
