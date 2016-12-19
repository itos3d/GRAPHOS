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
#include <QGraphicsEllipseItem>

#include "photoviewer.h"
#include "CrossGraphicItem.h"
#include "crosshairgraphicsitem.h"
#include <QGraphicsItem>
#include <QFrame>

PhotoViewer::PhotoViewer(QMainWindow * mainWindow, QObject *parent) :
    QObject(parent),
    mainWindow(mainWindow),
    drawOriginPoint(false),
    drawOriginEdge(false),
    drawScaleLine1(false),
    drawScaleLine2(false),
    oxPointsCount(0),
    scale1PointsCount(0),
    scale2PointsCount(0),
    oxLineItem(0),
    scaleLine1Item(0),
    scaleLine2Item(0)
{
    SetupPhotoViewer();
}


void PhotoViewer::SetupPhotoViewer(){
    //Create Settings dir and files:
    QDir settingsDir(QDir::homePath() + "/.photo");
    if(!settingsDir.exists())
        settingsDir.mkdir(QDir::homePath() + "/.photo");
    QFile settingsFile(QDir::homePath() + "/.photo/settings");
    if(!settingsFile.exists()){
        settingsFile.open(QIODevice::ReadWrite);
        settingsFile.close();
    }
    QFile shortcutsFile(QDir::homePath() + "/.photo/shortcuts");
    if(!shortcutsFile.exists()){
        shortcutsFile.open(QIODevice::ReadWrite);
        shortcutsFile.close();
    }

    QPixmap screen = QPixmap::grabWindow(QApplication::desktop()->winId());

    // Showing app in fullscreen
    //this->showFullScreen();

    // This string holds the current version
    version = "0.4";

    // The Settings Window (for shortcuts)
    set = new Settings;

    // Set the same version number in the child widgets
    set->general->version = version;
    set->shortcuts->version = version;

    // Settings regarding the size of the thumbnail view. They have to be set after the settings window but before any of the other widgets!
    thbHeight = set->general->thumbSizeSlider->value();
    scrollbarheight = 18;

    // Intialise the main Graphicsview
    view = new Image;
    view->setScene(&scene);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    //    view->horizontalScrollBar()->setStyleSheet("background: black;");
    //    view->verticalScrollBar()->setStyleSheet("background: black;");

    // Disable the scrollbars for settings up window - avoid them from appearing for a split second on startup
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // The Thumbnail view is moved into its own class
    thumbs = new Thumbnails;
    thumbs->height = thbHeight;
    thumbs->setGeometry(0,QApplication::desktop()->height()-(thbHeight+scrollbarheight),QApplication::desktop()->width(),thbHeight+scrollbarheight);
    thumbs->setFixedHeight(thbHeight+scrollbarheight);
//    thumbs->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
    thumbs->setAlignment(Qt::AlignLeft);
    connect(thumbs, SIGNAL(loadImg(QString,int)), this, SLOT(loadNewImg(QString,int)));

    // Some global variables
    counttot = 0;		// Holds the total amount of pictures in current directory
    countpos = 0;		// The currently viewed picture
    currentfile = "";	// The currently viewed file
    previousfile = "";	// The previously viewed file
    horScaled = 1.0;	// The horizontal scaling factor
    verScaled = 1.0;	// The vertical scaling factor
    zoomSteps = 0;		// How many zoom steps in which direction were made

    // Check the settings file, whether composite is enable by the user
    bool usecomposite = false;
    QFile file(QDir::homePath() + "/.photo/settings");
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        if(in.readAll().contains("Composite=1"))
            usecomposite = true;
    }

    // If compositing is enabled, then we'll use it (for the mainwindow background)
    if(usecomposite) {

        //            this->setAttribute(Qt::WA_TranslucentBackground);
        //            central->setStyleSheet("background-color: rgba(0, 0, 0, 190)");
        //            view->setStyleSheet("QGraphicsView { background:transparent; border: none }");
        //            thumbs->setStyleSheet("background:transparent; border: none");

        // If compositing is disabled, then we'll simply take a screenshot and simulate some sort of compositing
    } else {

        // That's the background image
        QPixmap base = screen;
        // We want to overlay it with an half transpatent QPixmap
        QPixmap overlay(QApplication::desktop()->height(),QApplication::desktop()->width());
        overlay.fill(Qt::transparent);
        QPainter overlayPaint(&overlay);
        overlayPaint.setCompositionMode(QPainter::CompositionMode_SourceOver);
        QColor col;
        col.setRgba(qRgba(0,0,0,190));
        overlayPaint.fillRect(overlay.rect(),col);

        // The finished Pixmap
        QPixmap bg = QPixmap(base.size());
        bg.fill(Qt::transparent);

        // Let's start
        QPainter painter(&bg);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(base.rect(), overlay);

        painter.end();

        // Setting the background image as background of label
        QGraphicsPixmapItem *bgp = new QGraphicsPixmapItem;
        bgp->setPixmap(bg);
        //            QLabel *bglabel = new QLabel(central);
        //            bglabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //            bglabel->setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());
        //            bglabel->setPixmap(bg);
        //            bglabel->show();
    }

    // Very important, that'll contain the big image
    pix = new PixmapItem;
//    pix->setFlag(QGraphicsItem::ItemIsMovable);
    scene.addItem(pix);

    QPixmap p = QPixmap(QApplication::desktop()->width()-20,QApplication::desktop()->height()-thbHeight-scrollbarheight-20);
    p.fill(Qt::transparent);
    pix->setPixmap(p);
    pix->setPos(0,0);
    view->adjustSize();

    // Load the Shortcuts
    loadShortcuts();

    //////////////////////////////
    ////////// General SIGNAL/SLOTS
    //////////////////////////////

    // Change of Shortcuts
    connect(set->shortcuts, SIGNAL(updateShortcuts()), this, SLOT(loadShortcuts()));

    // When the settings window is closed, make sure, that this window gets the focus again
    connect(set->shortcuts, SIGNAL(focusParentWindow()), this, SLOT(focusThisWindow()));

    // Enable zooming
    connect(view, SIGNAL(zoom(int)), this, SLOT(zoom(int)));

    // The drawImg() function is called whenever the view is correctly set up
    connect(view->t, SIGNAL(timeout()), this, SLOT(doDrawImgStartUp()));

    // Setup the menu on the top right
    setupPhotoViewerMenu();


    // And at the end re-enable the scrollbars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    //Mis cosas
    editingMask = false;
    editingPoints = false;
    maskItem = NULL;
    originPointItem = new CrosshairGraphicsItem(new PW::PW2dPoint(0,0,"0,0"));
    originPointItem->setCrossColor(Qt::red);
}


// Setup the menu
void PhotoViewer::setupPhotoViewerMenu() {

    // The menu is a sub-widget of the view instance (and thus inheriting the opacity)
    m = new QWidget(view);

    // Set the menu style
    //        m->setStyleSheet("border-radius: 8px; background-color: rgba(0, 0, 0, 210)");

    // All the menu items (are turned into qlabels)
    QStringList items;
    items << "0_::_" + tr("Image Functions") + "_::_t_::_t";
    items << "0_::_Next_::_next_::_next";
    items << "0_::_Zoom_::_zoom_::_zoom";
    items << "0_::_-_::_-_::_-";
    items << "0_::_" + tr("General Functions") + "_::_t_::_t";
    items << "1_::_" + tr("Open File") + "_::_:/img/open.png_::_open";
    items << "1_::_" + tr("Settings") + "_::_:/img/setup.png_::_settings";
    items << "1_::_" + tr("Interrupt Thumbnail Creation") + "_::_:/img/interrupt.png_::_interrupt";
    items << "1_::_" + tr("Reload Thumbnails") + "_::_:/img/reload.png_::_reload";
    items << "0_::_" + tr("Hide Thumbnails") + "_::_:/img/toggle.png_::_toggle";
    items << "1_::_" + tr("About Photo") + "_::_:/img/about.png_::_about";
    items << "1_::_" + tr("Quit") + "_::_:/img/quit.png_::_quit";

    // The layout holding all the labels
    QVBoxLayout *mLay = new QVBoxLayout;

    // Go through all the items
    for(int i = 0; i < items.length(); ++i) {

        // Get all the data of them
        int close = items.at(i).split("_::_").at(0).toInt();
        QString txt = items.at(i).split("_::_").at(1);
        QString icon = items.at(i).split("_::_").at(2);
        QString data = items.at(i).split("_::_").at(3);

        // Treat "zoom" specially
        if(data == "zoom") {

            MenuItem *item1 = new MenuItem(tr("Zoom:"),"","",0,false);
            MenuItem *item2 = new MenuItem(QString(" %1 ").arg(tr("In")),"","zoomIn",0);
            MenuItem *item25 = new MenuItem("|","","",0,false);
            MenuItem *item3 = new MenuItem(QString(" %1 ").arg(tr("Out")),"","zoomOut",0);
            MenuItem *item35 = new MenuItem("|","","",0,false);
            MenuItem *item4 = new MenuItem(QString(" %1 ").arg(tr("Reset")),"","zoomReset",0);

            QHBoxLayout *zLay = new QHBoxLayout;

            zLay->addStretch();
            zLay->addWidget(item1);
            zLay->addSpacing(5);
            zLay->addWidget(item2);
            zLay->addWidget(item25);
            zLay->addWidget(item3);
            zLay->addWidget(item35);
            zLay->addWidget(item4);
            zLay->addStretch();

            connect(item2, SIGNAL(clicked()), this, SLOT(menuClicked()));
            connect(item3, SIGNAL(clicked()), this, SLOT(menuClicked()));
            connect(item4, SIGNAL(clicked()), this, SLOT(menuClicked()));

            mLay->addLayout(zLay);

            // Treat "next" specially
        } else if(data == "next") {

            MenuItem *item1 = new MenuItem(QString("<img src=\":/img/previous.png\" height=\"13\"> %1").arg(tr("Previous")),"","previous",0);
            MenuItem *item15 = new MenuItem("|","","",0,false);
            MenuItem *item2 = new MenuItem(QString("%1 <img src=\":/img/next.png\" height=\"13\">").arg(tr("Next")),"","next",0);

            QHBoxLayout *npLay = new QHBoxLayout;

            npLay->addStretch();
            npLay->addWidget(item1);
            npLay->addWidget(item15);
            npLay->addWidget(item2);
            npLay->addStretch();

            connect(item1,SIGNAL(clicked()), this, SLOT(menuClicked()));
            connect(item2,SIGNAL(clicked()), this, SLOT(menuClicked()));

            mLay->addLayout(npLay);

            // Treat that as a spacer
        } else if(data == "-") {

            MenuItem *item = new MenuItem("","","",0,false);
            mLay->addWidget(item);

            // That's a title
        } else if(data == "t") {

            MenuItem *item = new MenuItem("<center><i>" + txt + "</i></span></center>","","",0,false);
            mLay->addWidget(item);

            // And all the rest
        } else {

            MenuItem *item = new MenuItem(txt,icon,data,close);

            // Keep access to the "toggle" item (change it depending on toggle status)
            if(data == "toggle")
                adjustMenuItems["toggle"] = item;

            mLay->addWidget(item);

            connect(item, SIGNAL(clicked()), this, SLOT(menuClicked()));
        }

    }


    m->setLayout(mLay);

    // This is the dimension of the menu
    menuRectShown = QRect(QApplication::desktop()->width()-350,0,300,items.length()*28);
    menuRectHidden = QRect(menuRectShown.x(),-menuRectShown.height(),menuRectShown.width(),menuRectShown.height());
    m->setGeometry(menuRectHidden);

    // The menu is shown when the user gets near it with his cursor
//    connect(view, SIGNAL(mousePos(QPoint)), this, SLOT(animateMenu(QPoint)));

    // The animation
    ani = new QPropertyAnimation(m,"geometry");

    // Is the menu shown?
    mShown = false;

}

// Displaying the big image
void PhotoViewer::drawImg(int big) {

    // The settings are reloaded when the thumbnail size changed
    if(thbHeight != set->general->thumbSizeSlider->value())
        loadSettings();

    // If no file was passed on to photo
    if(currentfile == "") {

        openFile();

    } else {

        qDebug() << "Drawing image:" << currentfile;

        // At first function call: Collect general data
        if(counttot == 0) {
            thumbs->height = thbHeight;
            thumbs->cacheEnabled = set->general->thumbCache->isChecked();
            thumbs->allImgs();
            counttot = thumbs->counttot;
        }

        // If there is only one image in the directory at all, then the thumbnail view isnot needed and hidden
        if(counttot == 1 && thumbs->isVisible() && big != 500) {
            toggleThumbnails(false);
        }

        // Scaling and adding the image to display (using QImageReader for better performance)
        QImageReader reader(currentfile);

        int readerWidth = reader.size().width();
        int readerHeight = reader.size().height();

        imgWidth = readerWidth;
        imgHeight = readerHeight;

        // If the image was zoomed in and is now bigger than its actual size, then don't do anything, just replace the image
        if(horScaled > 1 && verScaled > 1)
            big = -1;
        // If the image was zoomed out, then we take the normal size and scale the view down
        else if(horScaled < 1 && verScaled < 1)
            big = 2;
        // If the view is normal, just reset the matrixes (just to be on the safe site)
        else if(zoomSteps == 0) {
            view->resetTransform();
            view->resetMatrix();
        }

        // If the image was zoomed in (but not yet beyond its actual size)
        if(big == 1) {

            // Determine the factor by which the view has to be scaled
            int compareHeight1 = mainWindow->height();
            if(reader.size().height() < view->height()-10)
                compareHeight1 = reader.size().height();
            int compareHeight2 = view->height()-10;
            if(reader.size().height() < compareHeight2)
                compareHeight2 = reader.size().height();

            float q = verScaled*(compareHeight1-thbHeight-scrollbarheight)/(readerHeight*1.0);
            if(compareHeight2 > compareHeight1-thbHeight-scrollbarheight-50)
                q = verScaled*compareHeight2/(readerHeight*1.0);

            view->scale(q,q);

            // if the image was either zoomed out or not zoomed at all
        } else if(big != -1) {

            // If not zoomed at all
            if(big != 2) {
                view->resetTransform();
                view->resetMatrix();
            }

            if(readerWidth > QApplication::desktop()->width()-10) {
                float q = (QApplication::desktop()->width()-10)/(readerWidth*1.0);
                readerWidth *= q;
                readerHeight *= q;
            }
            int thb = thbHeight+scrollbarheight;
            if(!thumbs->isVisible())
                thb = 0;
            if(readerHeight > QApplication::desktop()->height()-thb-20) {
                float q = (QApplication::desktop()->height()-thb-20)/(readerHeight*1.0);
                readerWidth *= q;
                readerHeight *= q;
            }

            reader.setScaledSize(QSize(readerWidth,readerHeight));

        }

        // Set Pixmap and adjust position
        pix->setPixmap(QPixmap::fromImage(reader.read()));
        pix->setX((QApplication::desktop()->width()-pix->pixmap().width())/2.0);
        pix->setY((view->height()-pix->pixmap().height())/2.0);

        scene.setSceneRect(scene.itemsBoundingRect());

        // Update the counter top left
        countpos = thumbs->allimgs.indexOf(currentfile);
        updateCounter();
    }

    emit imgDrawn();
}

// Zoom the image
void PhotoViewer::zoom(int z) {

    // Only do it if a file is loaded
    if(currentfile != "") {

        // If the zoom was called from the mouse wheel and ctrl being pressed: Center on mouse
        if(z < 3)
            view->setTransformationAnchor(view->AnchorUnderMouse);
        // If zoom was called per shortcut or from menu: Center on center of screen
        else {
            view->setTransformationAnchor(view->AnchorViewCenter);
            z -= 2;
        }

        // That's the current zoom position
        float currentZoom = view->matrix().m11();

        // Scale by this
        float doZoom = 1.0;

        // If the image currently is still in the normal size (fitting the screen), then draw either the full image scaled down for zooming in or the normal image for zooming out
        if(zoomSteps == 0 && z != 0) {
            if(z == 1)
                drawImg(1);
            else if(z == 2)
                drawImg(3);
        }

        // Zooming in (limited by zoom factor 30)
        if(z == 1 && verScaled < 30) {
            verScaled += 0.25;
            horScaled += 0.25;
            doZoom = (currentZoom+0.25)/currentZoom;
            zoomSteps += 1;
            qDebug() << verScaled;
            // If the user returns through the zooming in step to the normal position, we redraw the image
            if(zoomSteps == 0)
                zoom(0);
            else if(verScaled > 0)
                view->scale(doZoom,doZoom);
            // Zooming out (limited to a fourth of the normal size)
        } else if(z == 2 && verScaled > 0.25) {
            verScaled -= 0.25;
            horScaled -= 0.25;
            doZoom = (currentZoom-0.25)/currentZoom;
            qDebug() << verScaled;
            zoomSteps -= 1;
            if(zoomSteps == 0)
                zoom(0);
            else
                view->scale(doZoom,doZoom);
            // Reset the zooming position
        } else if(z == 0) {
            verScaled = 1.0;
            horScaled = 1.0;
            zoomSteps = 0;
            view->resetMatrix();
            drawImg();
        }

    } else
        qDebug() << "Can't zoom, no file loaded yet";


}

// On startup, the graphicsview check with a timer when the scene is set up correctly and then calls the draw function
void PhotoViewer::doDrawImgStartUp() {

    if(view->height() > QApplication::desktop()->height()-thbHeight-scrollbarheight-50) {

        drawImg();
        view->t->stop();
    }

}

// Load the next image in the directory (if there is one)
void PhotoViewer::getNext() {

    if(countpos < counttot-1) {
        qDebug() << "Getting next image";
        ++countpos;
        previousfile = currentfile;
        setCurrentFile(thumbs->allimgs.at(countpos).absoluteFilePath());
        thumbs->currentfile = currentfile;
        drawImg();
        thumbs->updImgMark(thumbs->allimgs.indexOf(previousfile),thumbs->allimgs.indexOf(currentfile));
    } else
        qDebug() << "No next image available";

}

// Load the previous image in the directory (if there is one)
void PhotoViewer::getPrev() {

    if(countpos > 0) {
        qDebug() << "Getting previous image";
        --countpos;
        previousfile = currentfile;
        setCurrentFile(thumbs->allimgs.at(countpos).absoluteFilePath());
        thumbs->currentfile = currentfile;
        drawImg();
        thumbs->updImgMark(thumbs->allimgs.indexOf(previousfile),thumbs->allimgs.indexOf(currentfile));
    } else
        qDebug() << "No previous image available";

}

// Update the counter in the top left of the window
void PhotoViewer::updateCounter() {

    //        qDebug() << "Updating counter";

    //        countLabel->setText(QString("%1/%2 - %3").arg(countpos+1).arg(counttot).arg(currentfile));
    //        countLabel->adjustSize();

}

// After a click on a thumbnail image
void PhotoViewer::loadNewImg(QString str, int pos) {

    if(str.trimmed() != "") {
        previousfile = currentfile;
        setCurrentFile(str);
        thumbs->currentfile = currentfile;
        countpos = pos;
        drawImg();
    }
}

// Load the thumbnail settings (the thumbnail size can be changed in settings during runtime)
void PhotoViewer::loadSettings() {

    thbHeight = set->general->thumbSizeSlider->value();
    thumbs->height = thbHeight;
    thumbs->setGeometry(0,QApplication::desktop()->height()-(thbHeight+scrollbarheight),QApplication::desktop()->width(),thbHeight+scrollbarheight);
    thumbs->setFixedHeight(thbHeight+scrollbarheight);
    view->setFixedHeight(QApplication::desktop()->height()-(thbHeight+scrollbarheight));

}

// Show a box with some "About" information
void PhotoViewer::showAbout() {

    QDialog *about = new QDialog;

    about->setWindowTitle(tr("About Photo"));

    QScrollArea *scroll = new QScrollArea;
    QWidget *scrollWidget = new QWidget(scroll->widget());
    scroll->setWidgetResizable(true);

    QString txt = "<div style=\"font-size: 8pt\">" + tr("Photo %1, by Lukas Spies, 2012 (photoQt@ymail.com)<br>Licensed under GPL, without any guarantee").arg(version) + "</div><h1>&nbsp;&nbsp;&nbsp;Photo " + version + "</h1>";
    txt += tr("Photo is a <b>simple image viewer</b>, designed to be <b>good looking, highly configureable</b>, yet <b>easy to use</b> and <b>fast</b>.<br><br>");
    txt += tr("I myself was born and raised in Germany and am now a student of Mathematics @ NUI Galway, Ireland. This project simply developed out of my search for something like this, but finding nothing.<br><br>");
    txt += tr("There are a lot of great and amazing image viewers out there, but with Photo I want to go a <b>new way</b>, making it possible to view images <i>\"the nice way\"</i>.<br><br>");
    txt += tr("That said, I hope you find this program <b>useful</b>!<br><br>If you want to <b>contribute</b> to Photo by <b>translating</b> it into another language (currently English, German and Greek available), drop me an email (<b>photoQt@ymail.com</b>) or leave a comment at the <b>qt-apps.org project page</b>.<br><br>");
    txt += tr("Also, if you find a bug or if you have a question or suggestion, tell me. I'm open to any <b>feedback</b> I get :)<br><br>");
    txt += tr("<h3>Translations:</h3><i>Lukas Spies (me)</i>: English, German<br><i>Dimitrios Glentadakis</i>: Greek<br><i>Tomas Bartl</i>: Czech<br>...and <i>you</i>?<br><br><br>");

    QLabel *text = new QLabel(txt);
    text->setWordWrap(true);

    QHBoxLayout *txtLay = new QHBoxLayout;
    txtLay->addWidget(text);

    scrollWidget->setLayout(txtLay);

    scroll->setWidget(scrollWidget);

    QVBoxLayout *centralLay = new QVBoxLayout;
    centralLay->addWidget(scroll);

    QLabel *esc = new QLabel("<i><center>" + tr("(Press Escape to exit)") + "</center></i>");
    centralLay->addWidget(esc);

    about->setLayout(centralLay);

    about->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    about->setFixedSize(about->size());
    about->adjustSize();
    about->exec();


}

// Show the settings window
void PhotoViewer::showSettings() {

    qDebug() << "Showing settings window";

    set->setGeometry(100,50,800,600);
    set->shortcuts->doresizing();

    // Move the settings window into the desktop center
    QRect r = set->frameGeometry();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    set->move(r.topLeft());

    set->exec();

}

// Load the shortcuts (from file)
void PhotoViewer::loadShortcuts() {


    QFile file(QDir::homePath() + "/.photo/shortcuts");

    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::critical(mainWindow,tr("Error loading shortcuts"),tr("Error!<br>No shortcuts could be loaded. Please ensure that you have read and write access to your home directory!<br><br>No shortcuts will be available in the current session of Photo."));
    else {

        // Get the file content
        QTextStream in(&file);
        QStringList all = in.readAll().split("\n");

        // currentSH holds all the once setup shortcuts
        QStringList currentSH;

        for(int i = 0; i < all.length(); ++i) {

            // The first line holds the version -> ignore it
            if(!all.at(i).startsWith("Version=") && all.at(i).trimmed() != "") {

                // Get the values
                QString close = all.at(i).split("::").at(0);
                QString shortcut = all.at(i).split("::").at(1);
                QString command = all.at(i).split("::").at(2);

                // If the shortcut existed already and/or has changed, or if it was first deleted and then reenabled (in the shortcut management), then we just adjust the command, and if their enabled or disabled (this way, any change in the shortcuts settings will take immediate effect!)
                if(mapAllSh.keys().contains(QKeySequence(shortcut).toString())) {
                    mapAllSh[QKeySequence(shortcut).toString()] = QString("%1:::::%2").arg(close).arg(command);
                    listAllSh[QKeySequence(shortcut).toString()]->setEnabled(true);
                    currentSH << QKeySequence(shortcut).toString();
                } else {
                    QShortcut *dyn = new QShortcut(QKeySequence(shortcut),mainWindow);
                    connect(dyn, SIGNAL(activated()), this, SLOT(executeShortcut()));
                    mapAllSh[dyn->key().toString()] = QString("%1:::::%2").arg(close).arg(command);
                    listAllSh[dyn->key().toString()] = dyn;
                    currentSH << dyn->key().toString();
                }

            }
        }

        // Disable all the "deleted" shortcuts (they are kept during runtime in case they are reenabled)
        QMapIterator<QString, QString> map(mapAllSh);
        while (map.hasNext()) {
            map.next();
            if(!currentSH.contains(map.key())) {
                listAllSh[map.key()]->setEnabled(false);
            }
        }

    }

}

// A shortcut was pressed
void PhotoViewer::executeShortcut() {

    // Get the key that was pressed
    QShortcut *keySH = (QShortcut *) sender();
    QString key = mapAllSh[keySH->key().toString()];

    // In case something went wrong (shouldn't happen)
    if(key.split(":::::").length() == 2) {

        // The first part contains the close setting (1=closePhoto)
        int close = key.split(":::::").at(0).toInt();
        // The second part is the actual command
        key = key.split(":::::").at(1);

        // Internal command start with two "_"
        if(key.startsWith("__")) {

            if(key == "__stopThb")
                thumbs->stopThread();
            if(key == "__close")
                mainWindow->close();
            if(key == "__settings")
                showSettings();
            if(key == "__next")
                getNext();
            if(key == "__prev")
                getPrev();
            if(key == "__noThumb")
                toggleThumbnails();
            if(key == "__reloadThb")
                thumbs->loadThumbs();
            if(key == "__about")
                showAbout();
            if(key == "__open")
                openFile();
            if(key == "__zoomIn")
                zoom(3);
            if(key == "__zoomOut")
                zoom(4);
            if(key == "__zoomReset")
                zoom(0);

            // All external commands
        } else {

            QProcess *p = new QProcess;
            key = key.replace("%f",'"' + currentfile + '"');
            key = key.replace("%d",'"' + QFileInfo(currentfile).absoluteDir().absolutePath() + '"');
            qDebug() << "KEY:" << key;
            p->start(key);
            qDebug() << close;
            while(!p->waitForStarted()) { }
            if(close == 1)
                mainWindow->close();

        }

    }
}

// Toggles the thumbnails view
void PhotoViewer::toggleThumbnails(bool alsoRedrawImage) {

    if(currentfile != "") {

        thumbs->toggle();

        // If the function is called manually after an image was loaded, then this is set to false making it possible to manually show thumbnails after they have been automatically hidden for a directory containing only one image
        if(alsoRedrawImage)
            drawImg(500);

        if(thumbs->isVisible()) {
            adjustMenuItems["toggle"]->setText(tr("Hide Thumbnails"));
            adjustMenuItems["toggle"]->setIcon(":/img/toggle.png");
        } else {
            adjustMenuItems["toggle"]->setText(tr("Show Thumbnails"));
            adjustMenuItems["toggle"]->setIcon(":/img/toggle.png");
        }

    }
}

// This function is called for opening a (new) file
void PhotoViewer::openFile() {

    // Stopping a possibly running thread
    thumbs->stopThread();

    qDebug() << "Loading new file.";

    // Open the FileDialog in the dir of last image. If Photo just was started (i.e. no current image), then open in home dir
    QString opendir = QDir::homePath();
    if(currentfile != "")
        opendir = QFileInfo(currentfile).absoluteDir().absolutePath();

    // Get new filename
    QString file = QFileDialog::getOpenFileName(mainWindow,tr("Open image file"),opendir,tr("Images") + " (*.bmp *.gif *.tif *.jpg *.jpeg *.jpeg2000 *.png *.pbm *.pgm *.ppm *.xbm *.xpm *.tiff)");

    // If a file was chosen (cancel returns an empoty string)
    if(file.trimmed() != "") {

        // If thumbnail size was changed -> reload thumbnail settings
        if(thbHeight != set->general->thumbSizeSlider->value())
            loadSettings();

        // Reset all variables
        setCurrentFile(currentfile);
        thumbs->currentfile = currentfile;
        thumbs->cacheEnabled = set->general->thumbCache->isChecked();
        thumbs->allimgs.clear();
        thumbs->allPixHov.clear();
        thumbs->allPixImg.clear();
        thumbs->allPixItem.clear();
        thumbs->allPixSel.clear();

        // And load the image and the directory
        thumbs->allImgs();
        qDebug() << "Cache enabled:" << thumbs->cacheEnabled;
        countpos = thumbs->allimgs.indexOf(currentfile);
        counttot = thumbs->counttot;
        drawImg();
        updateCounter();

    } else
        qDebug() << "No new file selected (cancelled?)";

}

// This function is called for opening (new) files
void PhotoViewer::openFile(QStringList imageURLs) {
    if(!imageURLs.isEmpty()) {
        // If thumbnail size was changed -> reload thumbnail settings
        if(thbHeight != set->general->thumbSizeSlider->value())
            loadSettings();

        // Reset all variables
        setCurrentFile(imageURLs.at(0));
        thumbs->currentfile = currentfile;
        thumbs->cacheEnabled = set->general->thumbCache->isChecked();
        thumbs->allimgs.clear();
        thumbs->allPixHov.clear();
        thumbs->allPixImg.clear();
        thumbs->allPixItem.clear();
        thumbs->allPixSel.clear();

        // And load the image and the directory
        thumbs->allImgs(imageURLs);
        qDebug() << "Cache enabled:" << thumbs->cacheEnabled;
        countpos = thumbs->allimgs.indexOf(currentfile);
        counttot = thumbs->counttot;
        drawImg();
        updateCounter();

    } else
        qDebug() << "No new file selected (cancelled?)";
}

// Animates the opening and closing of the menu
void PhotoViewer::animateMenu(QPoint p, bool forceClose) {

    int x = p.x();
    int y = p.y();

    int ySensitivity = set->general->menu->value()*10;
    int xSensitivity = set->general->menu->value()*3;

    // If the menu is requested to be opened
    if(!forceClose && x >= m->pos().x()-xSensitivity && x <= m->pos().x()+m->width()+xSensitivity && y >= 0 && y <= ySensitivity) {
        ani->setDuration(600);
        if(ani->state() == QPropertyAnimation::Stopped && mShown == false) {
            qDebug() << "Opening Menu";
            mShown = true;
            ani->setStartValue(menuRectHidden);
            ani->setEndValue(menuRectShown);
            ani->setEasingCurve(QEasingCurve::InBack);
            ani->start();
        }
    }

    // if the menu is requested to be closed
    if(forceClose || x < m->pos().x()-xSensitivity || x > m->pos().x()+m->width()+xSensitivity || y > m->pos().y()+m->height()) {
        ani->setDuration(500);
        if(mShown && ani->state() == QPropertyAnimation::Stopped) {
            qDebug() << "Closing Menu";
            mShown = false;
            ani->setStartValue(menuRectShown);
            ani->setEndValue(menuRectHidden);
            ani->setEasingCurve(QEasingCurve::OutBack);
            ani->start();
        }
    }

}

// A click on a menu item
void PhotoViewer::menuClicked() {

    MenuItem *item = (MenuItem*) sender();
    QString txt = item->data;

    // If this item was set up so that the menu closes on executing, then do it before executing the actual command (some commands open a QDialog with exec(), that would hold the menu open until after the function call is finished)
    if(item->close == 1)
        animateMenu(QPoint(m->pos().x()-1,0),true);

    if(txt == "open")
        openFile();
    if(txt == "settings")
        showSettings();
    if(txt == "interrupt")
        thumbs->stopThread();
    if(txt == "reload")
        thumbs->loadThumbs();
    if(txt == "toggle")
        toggleThumbnails();
    if(txt == "about")
        showAbout();
    if(txt == "quit")
        mainWindow->close();
    if(txt == "zoomIn")
        zoom(3);
    if(txt == "zoomOut")
        zoom(4);
    if(txt == "zoomReset")
        zoom(0);
    if(txt == "next")
        getNext();
    if(txt == "previous")
        getPrev();

}

// Set the focus to this window
void PhotoViewer::focusThisWindow() {
    mainWindow->activateWindow();
    mainWindow->setFocus();
}

// The close event cleans up (maybe not needed, added because I had some strange graphic errors on the next start for a split second -> need to investigate that a bit more)
void PhotoViewer::closeEvent(QCloseEvent *) {
    scene.clear();
    thumbs->scene.clear();
    if(thumbs->thread->isRunning()) {
        thumbs->stopThread();
        thumbs->thread->wait(1000);
    }

    // Ensure all windows are closed on exit
    if(set->isVisible())
        set->close();
    if(set->shortcuts->key->isVisible())
        set->shortcuts->key->close();

    qDebug() << "Goodbye.";
}

QWidget *PhotoViewer::getViewWidget()
{
    return view;
}

QWidget *PhotoViewer::getThumbsWidget()
{
    return thumbs;
}

void PhotoViewer::onPixmapClick(QPoint point)
{

//    if(currentMask.count()>0)
//        currentMask.remove(currentMask.count()-1);
    currentMask.append(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                               point.y() * imgHeight/pix->pixmap().height()));
//    currentMask.putPoints(currentMask.count(),1,point.x() * imgWidth/pix->pixmap().width(),
//                          point.y() * imgHeight/pix->pixmap().height());


    drawMask();
}

void PhotoViewer::onPixmapMouseMove(QPoint point){

    if (currentMask.count()>0){
        currentMask.append(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                              point.y() * imgHeight/pix->pixmap().height()));
//        currentMask.putPoints(currentMask.count()-1,1,point.x() * imgWidth/pix->pixmap().width(),
//                              point.y() * imgHeight/pix->pixmap().height());

        QTransform trans;
        trans=trans.scale(pix->pixmap().width()/imgWidth,pix->pixmap().height()/imgHeight);
        trans.translate(pix->sceneBoundingRect().left(),pix->sceneBoundingRect().top());

        QPolygonF transPolygon = trans.map(currentMask);

        QGraphicsPolygonItem *item = new QGraphicsPolygonItem(transPolygon);
        QPen myPen(Qt::red, 0, Qt::SolidLine);
        item->setBrush(QBrush(Qt::green, Qt::CrossPattern));
        item->setPen(myPen);

        scene.removeItem(scene.items().at(scene.items().count()));

        scene.addItem(item);
        scene.invalidate();
    }
}

void PhotoViewer::onPixmapRightClick(QPoint point)
{


}

void PhotoViewer::setCurrentFile(QString path)
{
    currentfile = path;
}

void PhotoViewer::setEditingMask(bool editing)
{
    editingMask = editing;

    if(editing){
        connect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapClick(QPoint)));
        connect(pix,SIGNAL(mouseMoved(QPoint)), this, SLOT(onPixmapMouseMove(QPoint)));
        connect(pix,SIGNAL(mouseRightClick(QPoint)), this, SLOT(onPixmapRightClick(QPoint)));
//        connect(view,SIGNAL(painting()), this, SLOT(onViewPaint()));
        connect(view,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPixmapContextMenu(QPoint)));
        view->setMouseTracking(true);
        scene.invalidate();

        pix->setCursor(Qt::CrossCursor);
    }
    else{
        disconnect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapClick(QPoint)));
        disconnect(pix,SIGNAL(mouseMoved(QPoint)), this, SLOT(onPixmapMouseMove(QPoint)));
        disconnect(pix,SIGNAL(mouseDoubleClick(QPoint)), this, SLOT(onPixmapRightClick(QPoint)));
//        disconnect(view,SIGNAL(painting()), this, SLOT(onViewPaint()));
        connect(view,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPixmapContextMenu(QPoint)));
        view->setMouseTracking(false);
        //Remove Polygon items:
        for (int i = 0; i<scene.items().count(); i++){
            if (scene.items().at(i)->type() == 5)
                scene.removeItem(scene.items().at(i));
        }
        scene.invalidate();

        pix->setCursor(Qt::OpenHandCursor);
    }
}

void PhotoViewer::setAddingPoint(bool editing)
{
    addingPoint = editing;

    if(addingPoint){
        connect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingPoint(QPoint)));
        view->setMouseTracking(true);
        scene.invalidate();

        pix->setCursor(Qt::CrossCursor);
    }
    else{
        disconnect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingPoint(QPoint)));
        view->setMouseTracking(false);
        scene.invalidate();

        pix->setCursor(Qt::OpenHandCursor);
    }
}

void PhotoViewer::setAddingOxLine(bool editing)
{
    addingOxLine = editing;

    if(addingOxLine){
        connect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingOxLinePoint(QPoint)));
        view->setMouseTracking(true);
        scene.invalidate();

        pix->setCursor(Qt::CrossCursor);
    }
    else{
        disconnect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingOxLinePoint(QPoint)));
        view->setMouseTracking(false);
        scene.invalidate();

        pix->setCursor(Qt::OpenHandCursor);
    }
}

void PhotoViewer::setAddingScaleLine1(bool editing)
{
    addingScaleLine1 = editing;

    if(addingScaleLine1){
        connect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingScaleLine1Point(QPoint)));
        view->setMouseTracking(true);
        scene.invalidate();

        pix->setCursor(Qt::CrossCursor);
    }
    else{
        disconnect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingScaleLine1Point(QPoint)));
        view->setMouseTracking(false);
        scene.invalidate();

        pix->setCursor(Qt::OpenHandCursor);
    }
}

void PhotoViewer::setAddingScaleLine2(bool editing)
{
    addingScaleLine2 = editing;

    if(addingScaleLine2){
        connect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingScaleLine2Point(QPoint)));
        view->setMouseTracking(true);
        scene.invalidate();

        pix->setCursor(Qt::CrossCursor);
    }
    else{
        disconnect(pix, SIGNAL(mousePressed(QPoint)),this, SLOT(onPixmapPickingScaleLine2Point(QPoint)));
        view->setMouseTracking(false);
        scene.invalidate();

        pix->setCursor(Qt::OpenHandCursor);
    }
}

void PhotoViewer::drawMask()
{
    if(!editingMask)
        return;

    for (int i = 0; i<scene.items().count(); i++){
        if (scene.items().at(i)->type() == 5)
            scene.removeItem(scene.items().at(i));
    }
    if(currentMask.count()>1){

        QTransform trans;

        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));

        QPolygonF transPolygon = trans.map(currentMask);

        getItemMask()->setPolygon(transPolygon);

        QPen myPen(QColor::fromRgb(95,141,211), 0, Qt::SolidLine);
        getItemMask()->setBrush(QBrush(QColor::fromRgb(119,221,119), Qt::CrossPattern));
        getItemMask()->setPen(myPen);

        scene.addItem(getItemMask());
        scene.invalidate();
    }
}


//void PhotoViewer::drawControlPoints(){

//    if(currentControlPoints.count()>0 && !editingPoints){

//        for (int i = 0; i<scene.items().count(); i++){
//                        if (scene.items().at(i)->type() == 4)
//                scene.removeItem(scene.items().at(i));
//        }

//        QTransform trans;

//        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

//        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
//                          qreal(pix->pixmap().height())/qreal(imgHeight));
//        for (int i=0; i<currentControlPoints.count();i++){
//            QPointF transPoint = trans.map(currentControlPoints.at(i));
//            //            QPen myPen(Qt::red, 0, Qt::SolidLine);
//            //            scene.addEllipse(transPoint.x()-2,transPoint.y()-2,4,4,myPen);

//            PW::PW2dPoint *point = new PW::PW2dPoint(transPoint.x(),transPoint.y(),"Px");
//            CrosshairGraphicsItem *crossItem = new CrosshairGraphicsItem(point);

//            scene.addItem(crossItem);

//        }
//        scene.invalidate();
//    }
//}

void PhotoViewer::drawControlPoints(){

    if(currentControlPointsPW.count()>0 && !editingPoints){
//        for (int i = 0; i<scene.items().count(); i++){
//            if (scene.items().at(i)->type() == 4)
//                scene.removeItem(scene.items().at(i));
//        }
        for (int i = 0; i < controlPointItems.count(); i++){
            scene.removeItem(controlPointItems.at(i));
        }
        controlPointItems.clear();

        QTransform trans;

        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));
        for (int i=0; i<currentControlPointsPW.count();i++){
            QPointF transPoint = trans.map(QPointF(currentControlPointsPW.at(i)->getCoord(0),currentControlPointsPW.at(i)->getCoord(1)));
            //            QPen myPen(Qt::red, 0, Qt::SolidLine);
            //            scene.addEllipse(transPoint.x()-2,transPoint.y()-2,4,4,myPen);

//            PW::PW2dPoint *point = new PW::PW2dPoint(transPoint.x(),transPoint.y(),currentControlPointsPW.at(i)->getName());
//            CrosshairGraphicsItem *crossItem = new CrosshairGraphicsItem(point);

            PW::PW2dPoint *point = new PW::PW2dPoint(transPoint.x(),transPoint.y(),currentControlPointsPW.at(i)->getName());
            CrosshairGraphicsItem *crossItem = new CrosshairGraphicsItem(new PW::PW2dPoint(0,0,currentControlPointsPW.at(i)->getName()));

            controlPointItems.append(crossItem);
            scene.addItem(crossItem);
            crossItem->moveBy(point->x(),point->y());

        }
        scene.invalidate();
    }
}

void PhotoViewer::drawAuxiliarSceneItems()
{  
    scene.removeItem(originPointItem);
    scene.removeItem(getItemOx());
    scene.removeItem(getScaleLine1Item());
    scene.removeItem(getScaleLine2Item());


    if(drawOriginPoint){
        QTransform trans;
        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));
        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));

        QPointF transPoint = trans.map(currentOriginPoint);
        scene.addItem(originPointItem);
        originPointItem->setX(0);
        originPointItem->setY(0);
        originPointItem->moveBy(transPoint.x(),transPoint.y());
    }

    if(drawOriginEdge && oxPointsCount == 2){
        QTransform trans;

        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));

        QLineF transLine = trans.map(currentOxLine);

        getItemOx()->setLine(transLine);

        QPen myPen(Qt::red, 1, Qt::SolidLine);
        //            oxLineItem->setBrush(QBrush(Qt::green, Qt::CrossPattern));
        getItemOx()->setPen(myPen);

        scene.addItem(getItemOx());
    }

    if(drawScaleLine1 && scale1PointsCount == 2){
        QTransform trans;

        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));

        QLineF transLine = trans.map(currentScaleLine1);

        getScaleLine1Item()->setLine(transLine);

        QPen myPen(Qt::green, 1, Qt::SolidLine);
        //            oxLineItem->setBrush(QBrush(Qt::green, Qt::CrossPattern));
        getScaleLine1Item()->setPen(myPen);

        scene.addItem(getScaleLine1Item());
    }

    if(drawScaleLine2 && scale2PointsCount == 2){
        QTransform trans;

        trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

        trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                          qreal(pix->pixmap().height())/qreal(imgHeight));

        QLineF transLine = trans.map(currentScaleLine2);

        getScaleLine2Item()->setLine(transLine);

        QPen myPen(Qt::green, 1, Qt::SolidLine);
        //            oxLineItem->setBrush(QBrush(Qt::green, Qt::CrossPattern));
        getScaleLine2Item()->setPen(myPen);

        scene.addItem(getScaleLine2Item());
    }
    scene.invalidate();
}

void PhotoViewer::showPixmapContextMenu(const QPoint &pos)
{
    QPoint globalPos = view->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction(tr("Delete mask"));
    myMenu.addAction(tr("Save changes"));

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if (selectedItem->text() == tr("Delete mask")){
            //Remove Polygon items:
            clearSceneGraphics();
            currentMask.clear();
            getItemMask()->setPolygon(currentMask);
            scene.invalidate();
        }else if (selectedItem->text() == tr("Save changes")){

            emit saveMask(currentMask);
        }
    }
    myMenu.hide();
}

void PhotoViewer::onPixmapPickingPoint(QPoint point)
{
    emit pointPicked(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                             point.y() * imgHeight/pix->pixmap().height()));
}

void PhotoViewer::onPixmapPickingOxLinePoint(QPoint point)
{
    switch(oxPointsCount){
    case 0:
        currentOxLine.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        oxPointsCount = 1;
        break;
    case 1:
        currentOxLine.setP2(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        oxPointsCount = 2;
        emit OxLinePicked(currentOxLine);
        break;
    case 2:
        currentOxLine.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        oxPointsCount = 1;
        break;
    }

    drawAuxiliarSceneItems();
}

void PhotoViewer::onPixmapPickingScaleLine1Point(QPoint point)
{
    switch(scale1PointsCount){
    case 0:
        currentScaleLine1.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale1PointsCount = 1;
        break;
    case 1:
        currentScaleLine1.setP2(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale1PointsCount = 2;
        emit scaleLine1Picked(currentScaleLine1);
        break;
    case 2:
        currentScaleLine1.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale1PointsCount = 1;
        break;
    }

    drawAuxiliarSceneItems();
}

void PhotoViewer::onPixmapPickingScaleLine2Point(QPoint point)
{
    switch(scale2PointsCount){
    case 0:
        currentScaleLine2.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale2PointsCount = 1;
        break;
    case 1:
        currentScaleLine2.setP2(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale2PointsCount = 2;
        emit scaleLine2Picked(currentScaleLine2);
        break;
    case 2:
        currentScaleLine2.setP1(QPointF(point.x() * imgWidth/pix->pixmap().width(),
                                    point.y() * imgHeight/pix->pixmap().height()));
        scale2PointsCount = 1;
        break;
    }

    drawAuxiliarSceneItems();
}

void PhotoViewer::clearSceneGraphics()
{
//    for (int i = 0; i<scene.items().count(); i++){
//        if (scene.items().at(i)->type() == 5 || scene.items().at(i)->type() == 4)
    //            scene.removeItem(scene.items().at(i));
    //    }

    for (int i = 0; i < controlPointItems.count(); i++){
        scene.removeItem(controlPointItems.at(i));
    }
    controlPointItems.clear();

    QList<QGraphicsItem *> list = scene.items();
    if (list.count()>0){
        QMutableListIterator<QGraphicsItem *> i(list);
        while (i.hasNext()) {
            QGraphicsItem * item = i.next();
            if (item->type() == 5 || item->type() == 4)
                i.remove();
        }
    }
}

QList<QGraphicsPolygonItem *> * PhotoViewer::getPointsContainer()
{
    return &controlPoints;
}

void PhotoViewer::clearControlPoints()
{
    currentControlPointsPW.clear();
    clearSceneGraphics();
    scene.invalidate();
}

void PhotoViewer::setEditingPoints(bool editing)
{
    editingPoints = editing;

    if (editing){
        view->setDragMode(QGraphicsView::NoDrag);
        for (int i = 0; i<scene.items().count(); i++){
            if(scene.items().at(i)->type() == 4){
                CrosshairGraphicsItem *item = (CrosshairGraphicsItem*)scene.items().at(i);
                item->setFlag(QGraphicsItem::ItemIsMovable, true);
                connect(item,SIGNAL(pointChanged(PW::PW2dPoint*,QPointF)),this, SLOT(onPointItemMouseRelease(PW::PW2dPoint*,QPointF)));
            }
        }
    }
    else{
        view->setDragMode(QGraphicsView::ScrollHandDrag);
        for (int i = 0; i<scene.items().count(); i++){
            if(scene.items().at(i)->type() == 4){
                CrosshairGraphicsItem *item = (CrosshairGraphicsItem*)scene.items().at(i);
                item->setFlag(QGraphicsItem::ItemIsMovable, false);
                disconnect(item,SIGNAL(pointChanged(QPointF)),this, SLOT(onPointItemMouseRelease(QPointF)));
            }
        }
        drawControlPoints();
    }
}

void PhotoViewer::clearAll()
{
//    clearSceneGraphics();
    clearControlPoints();
    currentMask = NULL;
    currentfile = "";

    pix->setPixmap(QPixmap());
    scene.invalidate();


    if(thumbs->thread->isRunning()) {
        thumbs->stopThread();
        thumbs->thread->wait(1000);
    }

    thumbs->scene.clear();
    thumbs->allimgs.clear();
    thumbs->allPixHov.clear();
    thumbs->allPixImg.clear();
    thumbs->allPixItem.clear();
    thumbs->allPixSel.clear();
    thumbs->invalidateScene();
}

bool PhotoViewer::isEditingPoints()
{
    return editingPoints;
}

void PhotoViewer::onPointItemMouseRelease(PW::PW2dPoint *point, QPointF pos)
{
    QTransform trans;

    trans.translate(qreal(pix->sceneBoundingRect().left()),qreal(pix->sceneBoundingRect().top()));

    trans=trans.scale(qreal(pix->pixmap().width())/qreal(imgWidth),
                      qreal(pix->pixmap().height())/qreal(imgHeight));

    QPointF transPoint = trans.inverted().map(QPointF(pos.x(),pos.y()));
    point->setCoord(0,transPoint.x());
    point->setCoord(1,transPoint.y());
    for (int i= 0; i<currentControlPointsPW.count();i++){
        if(currentControlPointsPW.at(i)->getName() == point->getName()){
            currentControlPointsPW.at(i)->setCoord(0,transPoint.x());
            currentControlPointsPW.at(i)->setCoord(1,transPoint.y());
        }
    }

    drawControlPoints();
}

void PhotoViewer::addAuxiliarItem(QGraphicsItem *item)
{
    auxiliarItems.append(item);
}

void PhotoViewer::removeLastAuxiliarItem()
{
    scene.removeItem(auxiliarItems.last());
    auxiliarItems.removeLast();
}

void PhotoViewer::clearAuxiliarItems()
{
    for(int i=0; i<auxiliarItems.size(); i++)
        scene.removeItem(auxiliarItems.at(i));
    auxiliarItems.clear();
}

QGraphicsPolygonItem * PhotoViewer::getItemMask()
{
    if (maskItem == NULL)
        maskItem = new QGraphicsPolygonItem();
    return maskItem;
}

QGraphicsLineItem * PhotoViewer::getScaleLine1Item()
{
    if (scaleLine1Item == NULL)
        scaleLine1Item = new QGraphicsLineItem();
    return scaleLine1Item;
}

QGraphicsLineItem * PhotoViewer::getScaleLine2Item()
{
    if (scaleLine2Item == NULL)
        scaleLine2Item = new QGraphicsLineItem();
    return scaleLine2Item;
}

QGraphicsLineItem * PhotoViewer::getItemOx()
{
    if (oxLineItem == NULL)
        oxLineItem = new QGraphicsLineItem();
    return oxLineItem;
}
