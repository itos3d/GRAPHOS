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
#include "AboutWallis_dialog.h"
#include "ui_AboutWallis_dialog.h"
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QDesktopWidget>
AboutWallis_dialog::AboutWallis_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWallis_dialog)
{
    ui->setupUi(this);
    setWindowTitle("Wallis filter info");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QGridLayout *mainLayout = new QGridLayout();
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    //Text area
    QTextEdit *mTextArea= new QTextEdit();
    mTextArea->setReadOnly(true);
    mTextArea->setAlignment(Qt::AlignJustify);
    mTextArea->setText("<h2>Wallis filter information</h2>"
                          "<font size=\"4\">Wallis filter  is generalized variance based image enhancement operator. In spite of Wallis is defined on the basis of 5 variables, the main ones are \"Contrast\" and \"Brightness\", which controls the dynamic range (or amount of enhancement) of an image to fit the target values of mean and standard deviation. It both are equal to zero, no improvement is applied to the original images.</br>"
                       "<strong>Contrast (a)</strong>: It is the parameter which controls the increase or decrease the amount of enhancement (variance gain). It is a dimensionless variable defined in the range [0-1], and being suggested to be lower than 0,5. If a=1 is chosen the final filtered image will have contrast gray values, while for a=0, the aimed contrast (\"Standard deviation\" variable) is forced. Please note, that this value is inverse that the \"Wallis\" original.<br>"
                       "<strong>Brightness (b)</strong>: Or mean proportionality factor, it is the parameter which controls the degree of brightness forcing. It is a dimensionless variable defined in the range [0-1], meaning b=1 that the target brightness (\"Average\" variable) is fulfill in the kernel, while b=0 implies no brightness changes in the kernel.<br>"
                       "<strong>Kernel size</strong>: or windows size of the convolution kernel. This parameter, expressed in pixel units, is linked to the image size. So an initial suggestion is computed automatically by GRAPHOS, established it as percentage  of image max radius, but setting a minimum value to avoid inefficient kernels.<br>"
                       "<strong>Standard deviation</strong>: Target value for the intensity standard deviation in the kernel image. It is suggested to be in the range of 50 to 80 levels (in the range 0-255). However, this variable is affected by the kernel size, so it must be decrease as the kernel size decreases to avoid any increment of noise.<br>"
                       "<strong>Average</strong>: Target value for the intensity average in the kernel image. It is suggested to be in the range of 127 to 140 levels (in the range 0-255). By default, it is set as 127.</font>");

    mainLayout->addWidget(mTextArea,0,0,1,4);

    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());

    QPixmap image(":/img/WallisImages/1-a0b0w1m127ds40.jpg");
    QLabel *imageLabel=new QLabel();
    imageLabel->setPixmap(image.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
    mainLayout->addWidget(imageLabel,1,0);
    mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0  b=0 Kernell size=1 Std deviation= 40  Average=127</strong></font>"),2,0,Qt::AlignCenter);


    QPixmap image2(":/img/WallisImages/2-a0b0w11m127ds40.jpg");
    QLabel *imageLabel2=new QLabel();
    imageLabel2->setPixmap(image2.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
    mainLayout->addWidget(imageLabel2,1,1);
    mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0  b=0 Kernell size=11 Std deviation= 40  Average=127</strong></font>"),2,1,Qt::AlignCenter);


    QPixmap image3(":/img/WallisImages/3-a0b0w41m127ds40.jpg");
    QLabel *imageLabel3=new QLabel();
    imageLabel3->setPixmap(image3.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
        mainLayout->addWidget(imageLabel3,1,2);
        mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0  b=0 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),2,2,Qt::AlignCenter);


    QPixmap image4(":/img/WallisImages/4-a0.1b0w41m127ds40.jpg");
    QLabel *imageLabel4=new QLabel();
    imageLabel4->setPixmap(image4.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
        mainLayout->addWidget(imageLabel4,1,3);
        mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0.1  b=0 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),2,3,Qt::AlignCenter);


    QPixmap image5(":/img/WallisImages/5-a0.2b0w41m127ds40.jpg");
    QLabel *imageLabel5=new QLabel();
    imageLabel5->setPixmap(image5.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
        mainLayout->addWidget(imageLabel5,3,0);
        mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0.2  b=0 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),4,0,Qt::AlignCenter);


    QPixmap image6(":/img/WallisImages/6-a0.5b0w41m127ds40.jpg");
    QLabel *imageLabel6=new QLabel();
    imageLabel6->setPixmap(image6.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
    mainLayout->addWidget(imageLabel6,3,1);
    mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0.5  b=0 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),4,1,Qt::AlignCenter);


    QPixmap image7(":/img/WallisImages/7-a0b0.5w41m127ds40.jpg");
    QLabel *imageLabel7=new QLabel();
    imageLabel7->setPixmap(image7.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
    mainLayout->addWidget(imageLabel7,3,2);
    mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0  b=0.5 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),4,2,Qt::AlignCenter);


    QPixmap image8(":/img/WallisImages/8-a0.5b0.5w41m127ds40.jpg");
    QLabel *imageLabel8=new QLabel();
    imageLabel8->setPixmap(image8.scaledToWidth((mainScreenSize.width()-20)/4,Qt::SmoothTransformation));
    mainLayout->addWidget(imageLabel8,3,3);
    mainLayout->addWidget(new QLabel("<font size=\"4\"><strong>a=0.5  b=0.5 Kernell size=41 Std deviation= 40  Average=127</strong></font>"),4,3,Qt::AlignCenter);




    setLayout(mainLayout);
    this->showMaximized();

}

AboutWallis_dialog::~AboutWallis_dialog()
{
    delete ui;
}
