/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMask;
    QAction *actionSave;
    QAction *actionOpen_Project;
    QAction *actionNew_Project;
    QAction *actionSettings_2;
    QAction *actionExit;
    QAction *actionExport_Sparse_Model;
    QAction *actionExport_Dense_Model;
    QAction *actionExport_Project;
    QAction *actionImport_Project;
    QAction *actionAbout_PW;
    QAction *actionDistance_Tool;
    QAction *actionAngleTool;
    QAction *actionPointTool;
    QAction *actionDefaultTool;
    QAction *actionUndistorted_images;
    QAction *actionExport_Agisoft_model;
    QAction *actionExport_Balanced_distortion;
    QAction *actionExport_GRAPHOS_distortion;
    QAction *actionExport_Photomodeller_distortion;
    QAction *action_ActionPickRotationCenter;
    QAction *actionBatch_process;
    QAction *on_actionGeorreference;
    QAction *actionScale_cloud;
    QAction *actionTop_view;
    QAction *actionBottom_view;
    QAction *actionRight_view;
    QAction *actionLeft_view;
    QAction *actionBack_view;
    QAction *actionFront_view;
    QAction *actionFront_isometric_view;
    QAction *actionBack_isometric_view;
    QAction *actionOpenDialog;
    QAction *actionCalibration_conversion;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuExport;
    QMenu *menuDistortion_model;
    QMenu *menuImport;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuTools;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionMask = new QAction(MainWindow);
        actionMask->setObjectName(QString::fromUtf8("actionMask"));
        actionMask->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/PW/icons/polyline"), QSize(), QIcon::Normal, QIcon::Off);
        actionMask->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        actionSettings_2 = new QAction(MainWindow);
        actionSettings_2->setObjectName(QString::fromUtf8("actionSettings_2"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionExport_Sparse_Model = new QAction(MainWindow);
        actionExport_Sparse_Model->setObjectName(QString::fromUtf8("actionExport_Sparse_Model"));
        actionExport_Dense_Model = new QAction(MainWindow);
        actionExport_Dense_Model->setObjectName(QString::fromUtf8("actionExport_Dense_Model"));
        actionExport_Project = new QAction(MainWindow);
        actionExport_Project->setObjectName(QString::fromUtf8("actionExport_Project"));
        actionImport_Project = new QAction(MainWindow);
        actionImport_Project->setObjectName(QString::fromUtf8("actionImport_Project"));
        actionAbout_PW = new QAction(MainWindow);
        actionAbout_PW->setObjectName(QString::fromUtf8("actionAbout_PW"));
        actionDistance_Tool = new QAction(MainWindow);
        actionDistance_Tool->setObjectName(QString::fromUtf8("actionDistance_Tool"));
        actionDistance_Tool->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/PW/icons/ruler"), QSize(), QIcon::Normal, QIcon::Off);
        actionDistance_Tool->setIcon(icon1);
        actionAngleTool = new QAction(MainWindow);
        actionAngleTool->setObjectName(QString::fromUtf8("actionAngleTool"));
        actionAngleTool->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/PW/icons/angle"), QSize(), QIcon::Normal, QIcon::Off);
        actionAngleTool->setIcon(icon2);
        actionPointTool = new QAction(MainWindow);
        actionPointTool->setObjectName(QString::fromUtf8("actionPointTool"));
        actionPointTool->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/PW/icons/pointTool"), QSize(), QIcon::Normal, QIcon::Off);
        actionPointTool->setIcon(icon3);
        actionDefaultTool = new QAction(MainWindow);
        actionDefaultTool->setObjectName(QString::fromUtf8("actionDefaultTool"));
        actionDefaultTool->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/PW/icons/normalCursor"), QSize(), QIcon::Normal, QIcon::Off);
        actionDefaultTool->setIcon(icon4);
        actionUndistorted_images = new QAction(MainWindow);
        actionUndistorted_images->setObjectName(QString::fromUtf8("actionUndistorted_images"));
        actionExport_Agisoft_model = new QAction(MainWindow);
        actionExport_Agisoft_model->setObjectName(QString::fromUtf8("actionExport_Agisoft_model"));
        actionExport_Balanced_distortion = new QAction(MainWindow);
        actionExport_Balanced_distortion->setObjectName(QString::fromUtf8("actionExport_Balanced_distortion"));
        actionExport_GRAPHOS_distortion = new QAction(MainWindow);
        actionExport_GRAPHOS_distortion->setObjectName(QString::fromUtf8("actionExport_GRAPHOS_distortion"));
        actionExport_Photomodeller_distortion = new QAction(MainWindow);
        actionExport_Photomodeller_distortion->setObjectName(QString::fromUtf8("actionExport_Photomodeller_distortion"));
        action_ActionPickRotationCenter = new QAction(MainWindow);
        action_ActionPickRotationCenter->setObjectName(QString::fromUtf8("action_ActionPickRotationCenter"));
        action_ActionPickRotationCenter->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/CC/images/ccPickCenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_ActionPickRotationCenter->setIcon(icon5);
        actionBatch_process = new QAction(MainWindow);
        actionBatch_process->setObjectName(QString::fromUtf8("actionBatch_process"));
        on_actionGeorreference = new QAction(MainWindow);
        on_actionGeorreference->setObjectName(QString::fromUtf8("on_actionGeorreference"));
        actionScale_cloud = new QAction(MainWindow);
        actionScale_cloud->setObjectName(QString::fromUtf8("actionScale_cloud"));
        actionTop_view = new QAction(MainWindow);
        actionTop_view->setObjectName(QString::fromUtf8("actionTop_view"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/PW/icons/img/viewTop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTop_view->setIcon(icon6);
        actionBottom_view = new QAction(MainWindow);
        actionBottom_view->setObjectName(QString::fromUtf8("actionBottom_view"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/PW/icons/img/viewBottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBottom_view->setIcon(icon7);
        actionRight_view = new QAction(MainWindow);
        actionRight_view->setObjectName(QString::fromUtf8("actionRight_view"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/PW/icons/img/viewRight.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRight_view->setIcon(icon8);
        actionLeft_view = new QAction(MainWindow);
        actionLeft_view->setObjectName(QString::fromUtf8("actionLeft_view"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/PW/icons/img/viewLeft.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLeft_view->setIcon(icon9);
        actionBack_view = new QAction(MainWindow);
        actionBack_view->setObjectName(QString::fromUtf8("actionBack_view"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/PW/icons/img/viewBack.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBack_view->setIcon(icon10);
        actionFront_view = new QAction(MainWindow);
        actionFront_view->setObjectName(QString::fromUtf8("actionFront_view"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/PW/icons/img/viewFront.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFront_view->setIcon(icon11);
        actionFront_isometric_view = new QAction(MainWindow);
        actionFront_isometric_view->setObjectName(QString::fromUtf8("actionFront_isometric_view"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/PW/icons/img/viewIsoFront.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFront_isometric_view->setIcon(icon12);
        actionBack_isometric_view = new QAction(MainWindow);
        actionBack_isometric_view->setObjectName(QString::fromUtf8("actionBack_isometric_view"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/PW/icons/img/viewIsoBack.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBack_isometric_view->setIcon(icon13);
        actionOpenDialog = new QAction(MainWindow);
        actionOpenDialog->setObjectName(QString::fromUtf8("actionOpenDialog"));
        actionCalibration_conversion = new QAction(MainWindow);
        actionCalibration_conversion->setObjectName(QString::fromUtf8("actionCalibration_conversion"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setEnabled(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuExport = new QMenu(menuFile);
        menuExport->setObjectName(QString::fromUtf8("menuExport"));
        menuDistortion_model = new QMenu(menuExport);
        menuDistortion_model->setObjectName(QString::fromUtf8("menuDistortion_model"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        MainWindow->setMenuBar(menuBar);

        toolBar->addAction(actionDefaultTool);
        toolBar->addSeparator();
        toolBar->addAction(actionMask);
        toolBar->addSeparator();
        toolBar->addAction(action_ActionPickRotationCenter);
        toolBar->addAction(actionPointTool);
        toolBar->addAction(actionDistance_Tool);
        toolBar->addAction(actionAngleTool);
        toolBar->addSeparator();
        toolBar->addAction(actionTop_view);
        toolBar->addAction(actionBottom_view);
        toolBar->addAction(actionRight_view);
        toolBar->addAction(actionLeft_view);
        toolBar->addAction(actionBack_view);
        toolBar->addAction(actionFront_view);
        toolBar->addAction(actionFront_isometric_view);
        toolBar->addAction(actionBack_isometric_view);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave);
        menuFile->addAction(menuImport->menuAction());
        menuFile->addAction(menuExport->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuExport->addAction(actionExport_Project);
        menuExport->addSeparator();
        menuExport->addAction(actionUndistorted_images);
        menuExport->addAction(menuDistortion_model->menuAction());
        menuExport->addSeparator();
        menuExport->addAction(actionExport_Sparse_Model);
        menuExport->addAction(actionExport_Dense_Model);
        menuExport->addSeparator();
        menuDistortion_model->addAction(actionExport_Agisoft_model);
        menuDistortion_model->addAction(actionExport_GRAPHOS_distortion);
        menuDistortion_model->addAction(actionExport_Photomodeller_distortion);
        menuDistortion_model->addAction(actionExport_Balanced_distortion);
        menuImport->addAction(actionImport_Project);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout_PW);
        menuView->addAction(actionTop_view);
        menuView->addAction(actionBottom_view);
        menuView->addAction(actionRight_view);
        menuView->addAction(actionLeft_view);
        menuView->addAction(actionBack_view);
        menuView->addAction(actionFront_view);
        menuView->addAction(actionFront_isometric_view);
        menuView->addAction(actionBack_isometric_view);
        menuTools->addAction(actionMask);
        menuTools->addSeparator();
        menuTools->addAction(action_ActionPickRotationCenter);
        menuTools->addAction(actionPointTool);
        menuTools->addAction(actionDistance_Tool);
        menuTools->addAction(actionAngleTool);
        menuTools->addSeparator();
        menuTools->addAction(actionScale_cloud);
        menuTools->addAction(on_actionGeorreference);
        menuTools->addSeparator();
        menuTools->addAction(actionBatch_process);
        menuTools->addSeparator();
        menuTools->addAction(actionCalibration_conversion);
        menuTools->addSeparator();
        menuTools->addAction(actionSettings_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Photogrammetry Workbench", 0, QApplication::UnicodeUTF8));
        actionMask->setText(QApplication::translate("MainWindow", "Mask", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0, QApplication::UnicodeUTF8));
        actionOpen_Project->setText(QApplication::translate("MainWindow", "Open Project", 0, QApplication::UnicodeUTF8));
        actionNew_Project->setText(QApplication::translate("MainWindow", "New Project", 0, QApplication::UnicodeUTF8));
        actionSettings_2->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionExport_Sparse_Model->setText(QApplication::translate("MainWindow", "Sparse Model", 0, QApplication::UnicodeUTF8));
        actionExport_Dense_Model->setText(QApplication::translate("MainWindow", "Dense Model", 0, QApplication::UnicodeUTF8));
        actionExport_Project->setText(QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExport_Project->setToolTip(QApplication::translate("MainWindow", "Export Project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionImport_Project->setText(QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));
        actionAbout_PW->setText(QApplication::translate("MainWindow", "About ...", 0, QApplication::UnicodeUTF8));
        actionDistance_Tool->setText(QApplication::translate("MainWindow", "Distance Tool", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDistance_Tool->setToolTip(QApplication::translate("MainWindow", "Distance measuring tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAngleTool->setText(QApplication::translate("MainWindow", "AngleTool", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAngleTool->setToolTip(QApplication::translate("MainWindow", "Angle measuring tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPointTool->setText(QApplication::translate("MainWindow", "PointTool", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPointTool->setToolTip(QApplication::translate("MainWindow", "Coordinates measuring tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDefaultTool->setText(QApplication::translate("MainWindow", "DefaultTool", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDefaultTool->setToolTip(QApplication::translate("MainWindow", "Deselect tools", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUndistorted_images->setText(QApplication::translate("MainWindow", "Undistorted images", 0, QApplication::UnicodeUTF8));
        actionExport_Agisoft_model->setText(QApplication::translate("MainWindow", "Agisoft distortion", 0, QApplication::UnicodeUTF8));
        actionExport_Balanced_distortion->setText(QApplication::translate("MainWindow", "Balanced distortion", 0, QApplication::UnicodeUTF8));
        actionExport_GRAPHOS_distortion->setText(QApplication::translate("MainWindow", "GRAPHOS distortion", 0, QApplication::UnicodeUTF8));
        actionExport_Photomodeller_distortion->setText(QApplication::translate("MainWindow", "Photomodeller distortion", 0, QApplication::UnicodeUTF8));
        action_ActionPickRotationCenter->setText(QApplication::translate("MainWindow", "Rotation center", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_ActionPickRotationCenter->setToolTip(QApplication::translate("MainWindow", "Pick rotation center", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionBatch_process->setText(QApplication::translate("MainWindow", "Batch process", 0, QApplication::UnicodeUTF8));
        on_actionGeorreference->setText(QApplication::translate("MainWindow", "Georreference", 0, QApplication::UnicodeUTF8));
        actionScale_cloud->setText(QApplication::translate("MainWindow", "Scale cloud", 0, QApplication::UnicodeUTF8));
        actionTop_view->setText(QApplication::translate("MainWindow", "Top view", 0, QApplication::UnicodeUTF8));
        actionBottom_view->setText(QApplication::translate("MainWindow", "Bottom view", 0, QApplication::UnicodeUTF8));
        actionRight_view->setText(QApplication::translate("MainWindow", "Right view", 0, QApplication::UnicodeUTF8));
        actionLeft_view->setText(QApplication::translate("MainWindow", "Left view", 0, QApplication::UnicodeUTF8));
        actionBack_view->setText(QApplication::translate("MainWindow", "Back view", 0, QApplication::UnicodeUTF8));
        actionFront_view->setText(QApplication::translate("MainWindow", "Front view", 0, QApplication::UnicodeUTF8));
        actionFront_isometric_view->setText(QApplication::translate("MainWindow", "Front isometric view", 0, QApplication::UnicodeUTF8));
        actionBack_isometric_view->setText(QApplication::translate("MainWindow", "Back isometric view", 0, QApplication::UnicodeUTF8));
        actionOpenDialog->setText(QApplication::translate("MainWindow", "OpenDialog", 0, QApplication::UnicodeUTF8));
        actionCalibration_conversion->setText(QApplication::translate("MainWindow", "Calibration conversion", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        menuDistortion_model->setTitle(QApplication::translate("MainWindow", "Distortion model", 0, QApplication::UnicodeUTF8));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "3D View", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
