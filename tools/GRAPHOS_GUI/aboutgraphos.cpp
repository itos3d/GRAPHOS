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
#include "aboutgraphos.h"
#include "MainWindowGRAPHOS.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QProxyStyle>
#include "DependencyInfoWidget.h"

AboutGraphos::AboutGraphos(QWidget *parent) :
    QDialog(parent)
{

    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(linuxCodec);
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    drawUI();
}

AboutGraphos::~AboutGraphos()
{
}

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab)
            s.transpose();
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel)
        {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
            {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};

void AboutGraphos::drawUI(){
    setWindowTitle(tr("About GRAPHOS"));
    setMinimumSize(800,500);
    setMaximumSize(800,500);

    //About GRAPHOS TAB

    QVBoxLayout *mainFrameLayout = new QVBoxLayout();
    QLabel *lbLogoGRAPHOS = new QLabel();
    QPixmap pix(":/PW/icons/img/graphos.PNG");
    lbLogoGRAPHOS->setPixmap(pix);
    lbLogoGRAPHOS->setStyleSheet("background:transparent;");
    mainFrameLayout->addWidget(lbLogoGRAPHOS);
    QTabWidget *tabWidget = new QTabWidget();

    QFrame *infoGraphosFrame = new QFrame();
    QVBoxLayout *infoGraphosFrameLayout = new QVBoxLayout();
    QTextEdit *textArea= new QTextEdit();
    textArea->setReadOnly(true);
    textArea->setText("<h2>GRAPHOS v " + QString( MAINWINDOWGRAPHOS_VERSION) +" build number "+
                                                                      QString(MAINWINDOWGRAPHOS_BUILD_NUMBER)  +
                                                                      QString(MAINWINDOWGRAPHOS_RELEASE_TYPE) + "</h2>"
                          "<font size=\"4\">An Open Source photogrammetric platform for 3d reconstruction from multiple images. "
                          "The photographic dream of modeling the world in 3D at scale only using photographs comes true. "
                          "GRAPHOS has been conceived as a platform that integrates the best and most robust algorithms in "
                          "photogrammetry and computer vision for achieving flexibility (coping with any type of images and camera), "
                          "automation (passing from 2D to 3D with one click) and quality (guaranteeing high resolution and accuracy).</font>"
                          );

    infoGraphosFrameLayout->addWidget(textArea);

    QLabel *authorsLabel= new QLabel("<h2>Authors</h2>");
    infoGraphosFrameLayout->addWidget(authorsLabel);

    QFrame *authorsFrame = new QFrame();
    QGridLayout *authorsFrameLayout = new QGridLayout();
    QLabel *lbLogoUSAL = new QLabel();
    QPixmap pixUsal(":/PW/icons/img/usal.png");
    lbLogoUSAL->setPixmap(pixUsal);
    lbLogoUSAL->setStyleSheet("background:transparent;");

    QLabel *lbLogoUCLM = new QLabel();
    QPixmap pixUCLM(":/PW/icons/img/uclm.png");
    lbLogoUCLM->setPixmap(pixUCLM);
    lbLogoUCLM->setStyleSheet("background:transparent;");

    QLabel *lbLogoFBK = new QLabel();
    QPixmap pixFBK(":/PW/icons/img/fbk.png");
    lbLogoFBK->setPixmap(pixFBK);
    lbLogoFBK->setStyleSheet("background:transparent;");

    QLabel *lbLogoUNIBO = new QLabel();
    QPixmap pixUNIBO(":/PW/icons/img/unibo.png");
    lbLogoUNIBO->setPixmap(pixUNIBO);
    lbLogoUNIBO->setStyleSheet("background:transparent;");

    authorsFrameLayout->addWidget(lbLogoUSAL,0,1);
    authorsFrameLayout->addWidget(lbLogoUCLM,0,2);
    authorsFrameLayout->addWidget(lbLogoFBK,0,3);
    authorsFrameLayout->addWidget(lbLogoUNIBO,0,4);

    QLabel *usalAuthors = new QLabel("<strong>  Diego Gonz&#0225;lez Aguilera</strong><br/>daguilera@usal.es<br/>"
                                     "<strong>  Luis L&#0243;pez Fern&#0225;ndez</strong><br/>luisloez89@usal.es<br/>"
                                        "<strong>  Pablo Rodr&#0237;guez Gonz&#0225;lvez</strong><br/>pablorgsf@usal.es<br/>");
    usalAuthors->setContentsMargins(20,0,0,0);

    QLabel *uclmAuthors = new QLabel("<strong>David Hern&#0225;ndez L&#0243;pez</strong><br/>david.hernandez@uclm.es<br/>"
                                     "<strong>Diego Guerrero Sevilla</strong><br/>dguerrero@uclm.es");
    uclmAuthors->setContentsMargins(20,0,0,0);
    QLabel *fbkAuthors = new QLabel("<strong>Fabio Remondino</strong><br/>remondino@fbk.eu<br/>"
                                     "<strong>Fabio Menna</strong><br/>fmenna@fbk.eu<br/>"
                                     "<strong>Erica Nocerino</strong><br/>nocerino@fbk.eu<br/>"
                                     "<strong>Isabella Toschi</strong><br/>toschi@fbk.eu");
    fbkAuthors->setContentsMargins(20,0,0,0);
    QLabel *uniboAuthors = new QLabel("<strong>Marco Gaiani</strong><br/>marco.gaiani@unibo.it<br/>"
                                     "<strong>Andrea Ballabeni</strong><br/>andrea.ballabeni@unibo.it");
    uniboAuthors->setContentsMargins(20,0,0,0);


    authorsFrameLayout->addWidget(usalAuthors,1,1, Qt::AlignTop);
    authorsFrameLayout->addWidget(uclmAuthors,1,2, Qt::AlignTop);
    authorsFrameLayout->addWidget(fbkAuthors,1,3, Qt::AlignTop);
    authorsFrameLayout->addWidget(uniboAuthors,1,4, Qt::AlignTop);

    authorsFrame->setLayout(authorsFrameLayout);
    infoGraphosFrameLayout->addWidget(authorsFrame);
    infoGraphosFrame->setLayout(infoGraphosFrameLayout);
    tabWidget->addTab(infoGraphosFrame,"About GRAPHOS");
    //Dependencies Tab

    QFrame *infoDependenciesFrame = new QFrame();
    QHBoxLayout *infoDependenciesFrameLayout = new QHBoxLayout();

    QFrame *infoLibrariesFrame = new QFrame();
    QVBoxLayout *infoLibrariesFrameLayout = new QVBoxLayout();

    infoLibrariesFrameLayout->addWidget(new QLabel("<h2>Libraries</h2>"));

    QTabWidget *tabWidgetLibraries = new QTabWidget;
    tabWidgetLibraries->setMaximumWidth(350);
    tabWidgetLibraries->setTabPosition(QTabWidget::West);
    tabWidgetLibraries->setStyle(new CustomTabStyle);

    tabWidgetLibraries->addTab(new DependencyInfoWidget("GNU GPLv3","MSD propose a novel interest point detector stemming from the intuition that image patches which are highly dissimilar over a relatively large extent of their surroundings hold the property of being repeatable and distinctive. This concept of contextual self-dissimilarity reverses the key paradigm of recent successful techniques such as the Local Self-Similarity descriptor and the Non-Local Means filter, which build upon the presence of similar - rather than dissimilar - patches. Moreover, our approach extends to contextual information the local selfdissimilarity notion embedded in established detectors of corner-like interest points, thereby achieving enhanced repeatability, distinctiveness and localization accuracy","https://github.com/fedassa/msdDetector"), "MSD");
    tabWidgetLibraries->addTab(new DependencyInfoWidget("BSD","OpenCV is released under a BSD license and hence it’s free for both academic and commercial use. It has C++, C, Python and Java interfaces and supports Windows, Linux, Mac OS, iOS and Android. OpenCV was designed for computational efficiency and with a strong focus on real-time applications. Written in optimized C/C++, the library can take advantage of multi-core processing. Enabled with OpenCL, it can take advantage of the hardware acceleration of the underlying heterogeneous compute platform. Adopted all around the world, OpenCV has more than 47 thousand people of user community and estimated number of downloads exceeding 9 million. Usage ranges from interactive art, to mines inspection, stitching maps on the web or through advanced robotics.","http://opencv.org/"), "OpenCV");
    tabWidgetLibraries->addTab(new DependencyInfoWidget("GPL","PMVS is a multi-view stereo software that takes a set of images and camera parameters, then reconstructs 3D structure of an object or a scene visible in the images. Only rigid structure is reconstructed, in other words, the software automatically ignores non-rigid objects such as pedestrians in front of a building. The software outputs a set of oriented points instead of a polygonal (or a mesh) model, where both the 3D coordinate and the surface normal are estimated at each oriented point.","http://www.di.ens.fr/pmvs/"), "PMVS");
    tabWidgetLibraries->addTab(new DependencyInfoWidget("GNU GPLv2","QuaZIP is a simple C++ wrapper over Gilles Vollant's ZIP/UNZIP package that can be used to access ZIP archives.","http://quazip.sourceforge.net/"), "QuaZIP");
//    tabWidgetLibraries->addTab(new DependencyInfoWidget("GPL","A Generic Sparse Bundle Adjustment C/C++ Package Based on the Levenberg-Marquardt Algorithm","http://users.ics.forth.gr/~lourakis/sba/index.html"), "sba");
    tabWidgetLibraries->addTab(new DependencyInfoWidget("BSD","The Scale-Invariant Feature Transform (SIFT) bundles a feature detector and a feature descriptor. The detector extracts from an image a number of frames (attributed regions) in a way which is consistent with (some) variations of the illumination, viewpoint and other viewing conditions. The descriptor associates to the regions a signature which identifies their appearance compactly and robustly","http://www.vlfeat.org/overview/sift.html"), "VLFeat");

    infoLibrariesFrameLayout->addWidget(tabWidgetLibraries);
    infoLibrariesFrame->setLayout(infoLibrariesFrameLayout);

    infoDependenciesFrameLayout->addWidget(infoLibrariesFrame);


    QFrame *infoToolsFrame = new QFrame();
    QVBoxLayout *infoToolsFrameLayout = new QVBoxLayout();

    infoToolsFrameLayout->addWidget(new QLabel("<h2>Tools</h2>"));

    QTabWidget *tabWidgetTools = new QTabWidget;
    tabWidgetTools->setMaximumWidth(350);
    tabWidgetTools->setTabPosition(QTabWidget::West);
    tabWidgetTools->setStyle(new CustomTabStyle);
    tabWidgetTools->addTab(new DependencyInfoWidget("Libraries: LGPL. Applications: GPL v2","CloudCompare is a 3D point cloud (and triangular mesh) processing software. "
                                                                       "It has been originally designed to perform comparison between two 3D points clouds (such as the ones "
                                                                                            "obtained with a laser scanner) or between a point cloud and a triangular mesh. "
                                                                                            "It relies on a specific octree structure that enables great performances1 in this "
                                                                                            "particular function.","http://www.danielgm.net/cc/"), "CloudCompare");
    tabWidgetTools->addTab(new DependencyInfoWidget("GPL v2","A complete, cross-platform solution to record, convert and stream audio and video.","https://www.ffmpeg.org/"), "FFmpeg");



    tabWidgetTools->addTab(new DependencyInfoWidget("LGPL","We provide an easy-to-use, ultra-light-weight, very efficient C++ programming API called LASlib (with LASzip DLL) "
                                                           "that implements reading and writing of LiDAR points from and to the ASPRS LAS format (version 1.0-1.3) as well as "
                                                           "its --- losslessly compressed, but otherwise identical twin --- the LAZ format.","http://www.cs.unc.edu/~isenburg/lastools/"), "LAStols");

    tabWidgetTools->addTab(new DependencyInfoWidget("CeCILL-B (L-GPL)","Software for automatic mapping in the geographic context. "
                                                                       "Automatic calculation of matches between two similar images is a "
                                                                       "problem that comes under many conditions, in the geometric image processing. "
                                                                       "This is particularly the case in the field of mapping where the image has value "
                                                                       "from the moment where you can geo-reference the information it contains. The "
                                                                       "objective of the Micmac software is to provide a unified solution to meet most "
                                                                       "of these problems. The general strategy used by Micmac is: multi-resolution "
                                                                       "approach and, at a given resolution, minimization approach of combining an energy "
                                                                       "function attaches to data and prior knowledge about the pattern. Beyond these general "
                                                                       "characteristics, a setup XML file system can offer the user fine control of the entire "
                                                                       "mapping process.","http://logiciels.ign.fr/?-Micmac,3-"), "MicMac");

    tabWidgetTools->addTab(new DependencyInfoWidget("Free for research and non-commercial use","Photogrammetric Surface Reconstruction from Imagery. SURE is a software solution for multi-view stereo, which enables the derivation of dense point clouds from a given set of images and its orientations. Up to one 3D point per pixel is extracted, which enables a high resolution of details. It is based on libtsgm, which implements the core functionality for image rectification, dense matching and multi-view triangulation, and provides a C/C++ API.","http://www.ifp.uni-stuttgart.de/publications/software/sure/index.en.html"), "SURE");


    infoToolsFrameLayout->addWidget(tabWidgetTools);
    infoToolsFrame->setLayout(infoToolsFrameLayout);

    infoDependenciesFrameLayout->addWidget(infoToolsFrame);
    infoDependenciesFrame->setLayout(infoDependenciesFrameLayout);

    tabWidget->addTab(infoDependenciesFrame,"Dependencies");
    mainFrameLayout->addWidget(tabWidget);

    setLayout(mainFrameLayout);
}
