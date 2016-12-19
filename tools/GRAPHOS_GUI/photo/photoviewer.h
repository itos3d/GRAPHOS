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
#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QMainWindow>
#include <QObject>
#include <QtConcurrentRun>
#include <QFutureWatcher>
#include <QTimer>
#include <QProcess>
#include <QFileDialog>
#include <QSignalMapper>
#include <QMenu>
#include <QScrollBar>
#include <QMapIterator>
#include <QPropertyAnimation>
#include <QDockWidget>

#include "image.h"
#include "thumbnail.h"
#include "settings.h"
#include "menu.h"
#include "pixmapitem.h"
#include "PW2dPoint.h"
#include "crosshairgraphicsitem.h"
#include <QMap>
class PhotoViewer : public QObject
{
    Q_OBJECT
public:
    explicit PhotoViewer(QMainWindow * mainWindow, QObject *parent = 0);
    QWidget *getViewWidget();
    QWidget *getThumbsWidget();


    QMainWindow * mainWindow;
    // The main widgets
    Image *view;
    Settings *set;
    Thumbnails *thumbs;
    QGraphicsScene scene;

    // This is responsible for showing the big image
    PixmapItem *pix;

    // That's the currently and previously viewed picture
    QString currentfile;
    QString previousfile;

    // The label at the top left, showing the current position in the directory
//    QLabel *countLabel;
    int counttot;
    int countpos;

    // This integer stores the size of the thumbnails and the thumbnails view
    int thbHeight;
    int scrollbarheight;

    // A button on the top right showing the About information box
    QPushButton *about;

    // A button on the top right, opening the settings window
    QPushButton *setup;

    // This shortcuts are already set up -> no need to change (after closing settings window)
    QStringList alreadySetupShortcuts;

    // These two QMaps hold all the info regarding shortcuts
    QMap<QString,QString> mapAllSh;
    QMap<QString,QShortcut*> listAllSh;

    // All the instances for the menu top right
    QAction *mClose;
    QAction *mToggleThumb;
    QAction *mSettings;
    QAction *mOpen;
    QAction *mAbout;
    QAction *mStopThumb;
    QAction *mReloadThumb;

    // This string holds the current version
    QString version;

    // Some variables for the zooming story
    float absoluteZoomFactor;
    float horScaled;
    float verScaled;
    int zoomSteps;

    // The stuff for the animated menu
    QWidget *m;
    QPropertyAnimation *ani;
    bool mShown;
    QRect menuRectHidden;
    QRect menuRectShown;

    // Function to set up the menu
    void setupPhotoViewerMenu();

    void SetupPhotoViewer();

    // This QMap stores some MenuItems for later access
    QMap<QString,MenuItem*> adjustMenuItems;

    //Mis cosas:

    //Image original size:
    int imgWidth;
    int imgHeight;
    //
    QPolygonF currentMask;
    QVector<QPointF> currentControlPoints;
    QVector<PW::PW2dPoint*> currentControlPointsPW;
    QPointF currentOriginPoint;
    QLineF currentOxLine;
    QLineF currentScaleLine1;
    QLineF currentScaleLine2;
    int scale1PointsCount;
    int scale2PointsCount;
    int oxPointsCount;

    QList<CrosshairGraphicsItem *> controlPointItems;
    QGraphicsPolygonItem *maskItem;
    CrosshairGraphicsItem * originPointItem;
    QGraphicsLineItem *oxLineItem;
    QGraphicsLineItem *scaleLine1Item;
    QGraphicsLineItem *scaleLine2Item;
    QList<QGraphicsItem *> auxiliarItems;

    QList<QGraphicsPolygonItem *> controlPoints; //??????????????????

    bool editingMask;
    bool editingPoints;
    bool addingPoint;
    bool addingOxLine;
    bool addingScaleLine1;
    bool addingScaleLine2;

    bool drawOriginPoint;
    bool drawOriginEdge;
    bool drawScaleLine1;
    bool drawScaleLine2;


public slots:
    // This funtion shows the image (path storred in currentfile)in big
    void drawImg(int big = 0);

    // Get the next/previous image in directory
    void getNext();
    void getPrev();

    // After an image is drawn, the counter top left is updated
    void updateCounter();

    // After click on a thumbnail, the associated image is loaded
    void loadNewImg(QString, int);

    // Show an information box with the "About" info
    void showAbout();

    // Show the settings window
    void showSettings();

    // Loads all shortcuts
    void loadShortcuts();

    // Executes a shortcut
    void executeShortcut();

    // Opens a (new) file
    void openFile();
    void openFile(QStringList imageURLs);

    // Load the thumbnail settings (the thumbnail size can be adjusted by the user)
    void loadSettings();

    // When the settings window is closed, make sure, that the mainwindow regains the focus (that must not be, if the user switched between windows while the settings window was opened)
    void focusThisWindow();

    // Toggle the thumbnails
    void toggleThumbnails(bool alsoRedrawImage = true);

    // Zooming the image
    void zoom(int);

    // Calls drawImg() on startup whenever the scene was correctly setup
    void doDrawImgStartUp();

    // Animate the opening/closing of the menu
    void animateMenu(QPoint p = QPoint(0,0), bool forceClose = false);

    // A click on a menu item
    void menuClicked();

    //Mis cosas:
    void clearAll();
    void onPixmapClick(QPoint point);
    void onPixmapMouseMove(QPoint point);
    void onPixmapRightClick(QPoint point);
    void showPixmapContextMenu(const QPoint& pos);
    void onPixmapPickingPoint (QPoint point);
    void onPixmapPickingOxLinePoint(QPoint point);
    void onPixmapPickingScaleLine1Point(QPoint point);
    void onPixmapPickingScaleLine2Point(QPoint point);

    void setCurrentFile(QString path);
    void setEditingMask(bool editing);
    void setEditingPoints(bool editing);
    void setAddingPoint(bool editing);
    void setAddingOxLine(bool editing);
    void setAddingScaleLine1(bool editing);
    void setAddingScaleLine2(bool editing);
    bool isEditingPoints();
    QGraphicsPolygonItem * getItemMask();
    QGraphicsLineItem * getItemOx();
    QGraphicsLineItem * getScaleLine1Item();
    QGraphicsLineItem * getScaleLine2Item();
    void drawMask();
    void drawControlPoints();
    void drawAuxiliarSceneItems();
    void clearSceneGraphics();
    QList<QGraphicsPolygonItem *> *getPointsContainer();
    void clearControlPoints();
    void onPointItemMouseRelease(PW::PW2dPoint *point, QPointF pos);

    void addAuxiliarItem(QGraphicsItem *item);
    void removeLastAuxiliarItem();
    void clearAuxiliarItems();

protected:
    void closeEvent(QCloseEvent *);

signals:
    void saveMask(QPolygonF polygon);
    void imgDrawn();
    void pointPicked(QPointF point);
    void OxLinePicked(QLineF line);
    void scaleLine1Picked(QLineF line);
    void scaleLine2Picked(QLineF line);
};

#endif // PHOTOVIEWER_H
