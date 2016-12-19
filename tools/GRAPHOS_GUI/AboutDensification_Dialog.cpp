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
#include "AboutDensification_Dialog.h"
#include "ui_AboutDensification_Dialog.h"
#include <QVBoxLayout>
#include <QTextEdit>
AboutDensification_Dialog::AboutDensification_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDensification_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Dense matching info");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QTabWidget *tabWidget = new QTabWidget();

    //MicMac tab
    QFrame *MicMacFrame = new QFrame();
    QVBoxLayout *MicMacFrameLayout = new QVBoxLayout();
    QTextEdit *MicMacTextArea= new QTextEdit();
    MicMacTextArea->setReadOnly(true);
    MicMacTextArea->setText("<font size=\"4\"><br><strong>Micmac</strong> is a collection of open-source tools, released in 2007 by the MATIS laboratory of IGN France, oriented to photogrammetric and Structure from Motion tasks."
                            "<br><strong>\"Object space\"</strong>: Dense matching performed on the object space. The result will be a single dense 3D point cloud covering the whole registered area. This is the most suitable mode for clasical aerial photogrammetric works."
                            "<br><strong>\"Master image\"</strong>: Dense matching performed on the image space. The result will be a dense 3D point cloud per master image.  This is the most useful mode for convergent close-range photogrammetric works."
                            "<br><strong>\"QuickMac\"</strong>: Fast dense matching tool performed at a high piramid level with very low resolution images. Tool suitable for a fast preview of the result through the ispection of a sparse 3D point cloud."
                            "<br><strong>\"BigMac\"</strong>: Dense matchig tool without user interaction. The result will be a single dense 3D point cloud of the object under study."
                            "<br><strong>\"DeZoom\"</strong>: Final pyramid level for the densification process. It ranges from 1 (original resolution) to 64 (1/64th of original resolution; the smaller accepted by the software). Other values are 32, 16, 8, 4 ,2. The higher the value, the higher the time and the computational cost, but better spatial resolution "
                            "<br><strong>\"ZRegul\"</strong>: or regularization factor. It controls the final degree of smoothing of the reconstructed point cloud. It is define in the range 0.01 – 0.2, being by default 0.05. The more geometric changes have the cloud, the smaller should be the value to preserve details."
                            "<br><strong>\"ZPas\"</strong>: It is the variable which control the quantification step in equivalent pixel. It controls the sampling interval of the elevation, or level of quantification, calculated on the basis of the base-to-height ratio. It is defined in the range 0.1-0.6 being by default 0.4. The smaller the Zpas variable, higher the computational cost.</font>");

    MicMacFrameLayout->addWidget(MicMacTextArea);

    MicMacFrame->setLayout(MicMacFrameLayout);
    tabWidget->addTab(MicMacFrame,"MicMac");


    //PMVS tab
    QFrame *PMVSFrame = new QFrame();
    QVBoxLayout *PMVSFrameLayout = new QVBoxLayout();
    QTextEdit *PMVSTextArea= new QTextEdit();
    PMVSTextArea->setReadOnly(true);
    PMVSTextArea->setText("<font size=\"4\"><br><strong>PMVS</strong> is a multi-view stereo software that takes a set of images and camera parameters, then reconstructs 3D structure of an object or a scene visible in the images. Only rigid structure is reconstructed, in other words, the software automatically ignores non-rigid objects such as pedestrians in front of a building. The software outputs a set of oriented points instead of a polygonal (or a mesh) model, where both the 3D coordinate and the surface normal are estimated at each oriented point. "
                          "<br><strong>\"Level\"</strong>: Pyramid level used for the computation. When level is 0, original (full) resolution images are used. When level is 1, images are halved (or 4 times less pixels). When level is 2, images are 4 times smaller (or 16 times less pixels). By default it set as 1, since level 0 is not suggested to use for images from Bayer filter. Note that increasing the value of level significantly speeds-up the whole computation, while reconstructions become significantly sparse. "
                          "<br><strong>\"Min\"</strong>: Minimum number of images where a 3D point should be visible. The minimum value is 2, to obtain a 3d reconstruction, but a high number of blunders could be obtained. It is suggested as default a minimum of 3 images. A higher value (4 or 5) will deliver a lees dense 3D point cloud, but it is recommended for the low texture cases. "
                          "<br><strong>\"Csize\"</strong>: or Cell size, controls the density of reconstructions. The algorithm tries to reconstruct at least one patch in every csize x csize pixel square region in all the target images. Therefore, increasing the value of csize leads to sparser reconstructions. "
                          "<br><strong>\"Threshold\"</strong>: Normalized cross correlation used as a photometric consistency measure, whose value ranges from -1 (bad) to 1 (good), to accept a patch reconstruction as a success and kept it. The algorithm repeats three iterations of the reconstruction pipeline, and this threshold is relaxed (decreased) by 0.05 at the end of each iteration. For example, for the default threshold of 0.7, the values of the threshold are 0.7, 0.65, and 0.6 for the three iterations of the pipeline, respectively</font>");

    PMVSFrameLayout->addWidget(PMVSTextArea);

    PMVSFrame->setLayout(PMVSFrameLayout);
    tabWidget->addTab(PMVSFrame,"PMVS");


    //SURE tab
    QFrame *SUREFrame = new QFrame();
    QVBoxLayout *SUREFrameLayout = new QVBoxLayout();
    QTextEdit *SURETextArea= new QTextEdit();
    SURETextArea->setReadOnly(true);
    SURETextArea->setText("<font size=\"4\"><br><strong>SURE</strong> is a software solution for multi-view stereo, which enables the derivation of dense point clouds from a given set of images and its orientations. Up to one 3D point per pixel is extracted, which enables a high resolution of details. "
                          "<br>SURE can handle image collected by various types of sensors and can be utilized for close range, UAV and large frame aerial datasets. It scales well to datasets with large image numbers and large image resolution (e.g. >200MP aerial imagery). "
                          "Also imagery with high dynamic range (e.g. 16 Bit depth) can be used. Initial depth information of the scene is not required, which enables the use within fixed calibrated camera setups. The efficiency of processing is increased by utilizing parallel processing and hierarchical optimization.</font>"
                          "<br><strong>\"Pyr\"</strong>: Resolution level. 0 for full resolution (default), 1 for quarter resolution (half image width, eight times faster), 2 for sixteenth resolution (quarter width)."
                          "<br><strong>\"Fold\"</strong>: Each point must be observed in n stereo models (n+1 images). Default: 2 For small overlap imagery this fold must be decreased for higher completeness, for highly overlapping imagery it can be increased for accuracy.</font>"
                          "<br><strong>\"Max Models\"</strong>: Amount of stereo models per image. Default 5 – decrease for speed (less runtime since less stereo models to process), increase for accuracy.");

    SUREFrameLayout->addWidget(SURETextArea);

    SUREFrame->setLayout(SUREFrameLayout);
    tabWidget->addTab(SUREFrame,"SURE");


    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    setFixedSize(800,500);
}

AboutDensification_Dialog::~AboutDensification_Dialog()
{
    delete ui;
}
