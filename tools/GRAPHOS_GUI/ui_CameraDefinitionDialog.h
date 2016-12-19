/********************************************************************************
** Form generated from reading UI file 'CameraDefinitionDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERADEFINITIONDIALOG_H
#define UI_CAMERADEFINITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraDefinitionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLineEdit *lineEditWidth;
    QLabel *labelCameraName;
    QLabel *labelCamera;
    QLineEdit *lineEditHeight;
    QLabel *labelWidth;
    QLabel *labelHeight;
    QLabel *lbWidthStimated;
    QLabel *lbHeightStimated;
    QLabel *labelScale;
    QLineEdit *lineEditScale;
    QLineEdit *lineEditCameraName;
    QComboBox *comboBoxCamera;
    QFrame *line;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QLabel *labelLens;
    QLabel *labelLensName;
    QLabel *labelLocal;
    QLineEdit *lineEditFocal;
    QLabel *lbFocalStimated;
    QLineEdit *lineEditLensName;
    QComboBox *comboBoxLens;
    QFrame *warningFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lbWarningImg;
    QLabel *label_2;
    QFrame *aspectRatioErrorFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CameraDefinitionDialog)
    {
        if (CameraDefinitionDialog->objectName().isEmpty())
            CameraDefinitionDialog->setObjectName(QString::fromUtf8("CameraDefinitionDialog"));
        CameraDefinitionDialog->resize(544, 346);
        verticalLayout = new QVBoxLayout(CameraDefinitionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(CameraDefinitionDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditWidth = new QLineEdit(frame);
        lineEditWidth->setObjectName(QString::fromUtf8("lineEditWidth"));

        gridLayout->addWidget(lineEditWidth, 2, 1, 1, 1);

        labelCameraName = new QLabel(frame);
        labelCameraName->setObjectName(QString::fromUtf8("labelCameraName"));

        gridLayout->addWidget(labelCameraName, 1, 0, 1, 1);

        labelCamera = new QLabel(frame);
        labelCamera->setObjectName(QString::fromUtf8("labelCamera"));

        gridLayout->addWidget(labelCamera, 0, 0, 1, 1);

        lineEditHeight = new QLineEdit(frame);
        lineEditHeight->setObjectName(QString::fromUtf8("lineEditHeight"));

        gridLayout->addWidget(lineEditHeight, 2, 4, 1, 1);

        labelWidth = new QLabel(frame);
        labelWidth->setObjectName(QString::fromUtf8("labelWidth"));

        gridLayout->addWidget(labelWidth, 2, 0, 1, 1);

        labelHeight = new QLabel(frame);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));

        gridLayout->addWidget(labelHeight, 2, 3, 1, 1);

        lbWidthStimated = new QLabel(frame);
        lbWidthStimated->setObjectName(QString::fromUtf8("lbWidthStimated"));

        gridLayout->addWidget(lbWidthStimated, 2, 2, 1, 1);

        lbHeightStimated = new QLabel(frame);
        lbHeightStimated->setObjectName(QString::fromUtf8("lbHeightStimated"));

        gridLayout->addWidget(lbHeightStimated, 2, 5, 1, 1);

        labelScale = new QLabel(frame);
        labelScale->setObjectName(QString::fromUtf8("labelScale"));

        gridLayout->addWidget(labelScale, 3, 2, 1, 2);

        lineEditScale = new QLineEdit(frame);
        lineEditScale->setObjectName(QString::fromUtf8("lineEditScale"));

        gridLayout->addWidget(lineEditScale, 3, 4, 1, 1);

        lineEditCameraName = new QLineEdit(frame);
        lineEditCameraName->setObjectName(QString::fromUtf8("lineEditCameraName"));

        gridLayout->addWidget(lineEditCameraName, 1, 1, 1, 4);

        comboBoxCamera = new QComboBox(frame);
        comboBoxCamera->setObjectName(QString::fromUtf8("comboBoxCamera"));

        gridLayout->addWidget(comboBoxCamera, 0, 1, 1, 4);


        verticalLayout->addWidget(frame);

        line = new QFrame(CameraDefinitionDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        frame_2 = new QFrame(CameraDefinitionDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelLens = new QLabel(frame_2);
        labelLens->setObjectName(QString::fromUtf8("labelLens"));

        gridLayout_2->addWidget(labelLens, 0, 0, 1, 1);

        labelLensName = new QLabel(frame_2);
        labelLensName->setObjectName(QString::fromUtf8("labelLensName"));

        gridLayout_2->addWidget(labelLensName, 1, 0, 1, 1);

        labelLocal = new QLabel(frame_2);
        labelLocal->setObjectName(QString::fromUtf8("labelLocal"));

        gridLayout_2->addWidget(labelLocal, 2, 0, 1, 1);

        lineEditFocal = new QLineEdit(frame_2);
        lineEditFocal->setObjectName(QString::fromUtf8("lineEditFocal"));

        gridLayout_2->addWidget(lineEditFocal, 2, 1, 1, 1);

        lbFocalStimated = new QLabel(frame_2);
        lbFocalStimated->setObjectName(QString::fromUtf8("lbFocalStimated"));

        gridLayout_2->addWidget(lbFocalStimated, 2, 2, 1, 1);

        lineEditLensName = new QLineEdit(frame_2);
        lineEditLensName->setObjectName(QString::fromUtf8("lineEditLensName"));

        gridLayout_2->addWidget(lineEditLensName, 1, 1, 1, 1);

        comboBoxLens = new QComboBox(frame_2);
        comboBoxLens->setObjectName(QString::fromUtf8("comboBoxLens"));

        gridLayout_2->addWidget(comboBoxLens, 0, 1, 1, 1);

        comboBoxLens->raise();
        lineEditFocal->raise();
        lineEditLensName->raise();
        labelLens->raise();
        labelLocal->raise();
        labelLensName->raise();
        lbFocalStimated->raise();

        verticalLayout->addWidget(frame_2);

        warningFrame = new QFrame(CameraDefinitionDialog);
        warningFrame->setObjectName(QString::fromUtf8("warningFrame"));
        warningFrame->setFrameShape(QFrame::StyledPanel);
        warningFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(warningFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(warningFrame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lbWarningImg = new QLabel(warningFrame);
        lbWarningImg->setObjectName(QString::fromUtf8("lbWarningImg"));

        horizontalLayout->addWidget(lbWarningImg);

        label_2 = new QLabel(warningFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addWidget(warningFrame, 0, Qt::AlignLeft);

        aspectRatioErrorFrame = new QFrame(CameraDefinitionDialog);
        aspectRatioErrorFrame->setObjectName(QString::fromUtf8("aspectRatioErrorFrame"));
        aspectRatioErrorFrame->setFrameShape(QFrame::StyledPanel);
        aspectRatioErrorFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(aspectRatioErrorFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(aspectRatioErrorFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addWidget(aspectRatioErrorFrame);

        buttonBox = new QDialogButtonBox(CameraDefinitionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(comboBoxCamera, lineEditCameraName);
        QWidget::setTabOrder(lineEditCameraName, lineEditWidth);
        QWidget::setTabOrder(lineEditWidth, lineEditHeight);
        QWidget::setTabOrder(lineEditHeight, lineEditScale);
        QWidget::setTabOrder(lineEditScale, comboBoxLens);
        QWidget::setTabOrder(comboBoxLens, lineEditLensName);
        QWidget::setTabOrder(lineEditLensName, lineEditFocal);
        QWidget::setTabOrder(lineEditFocal, buttonBox);

        retranslateUi(CameraDefinitionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CameraDefinitionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CameraDefinitionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraDefinitionDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraDefinitionDialog)
    {
        CameraDefinitionDialog->setWindowTitle(QApplication::translate("CameraDefinitionDialog", "Camera data", 0, QApplication::UnicodeUTF8));
        labelCameraName->setText(QApplication::translate("CameraDefinitionDialog", "Camera name:", 0, QApplication::UnicodeUTF8));
        labelCamera->setText(QApplication::translate("CameraDefinitionDialog", "Camera:", 0, QApplication::UnicodeUTF8));
        labelWidth->setText(QApplication::translate("CameraDefinitionDialog", "Sensor width (mm):", 0, QApplication::UnicodeUTF8));
        labelHeight->setText(QApplication::translate("CameraDefinitionDialog", "Sensor height (mm):", 0, QApplication::UnicodeUTF8));
        lbWidthStimated->setText(QString());
        lbHeightStimated->setText(QString());
        labelScale->setText(QApplication::translate("CameraDefinitionDialog", "Scale factor to 35 (Crop factor) (mm):", 0, QApplication::UnicodeUTF8));
        labelLens->setText(QApplication::translate("CameraDefinitionDialog", "Lens:", 0, QApplication::UnicodeUTF8));
        labelLensName->setText(QApplication::translate("CameraDefinitionDialog", "Lens name:", 0, QApplication::UnicodeUTF8));
        labelLocal->setText(QApplication::translate("CameraDefinitionDialog", "Focal length (Physical) (mm):", 0, QApplication::UnicodeUTF8));
        lbFocalStimated->setText(QString());
        label->setText(QApplication::translate("CameraDefinitionDialog", "Warning: ", 0, QApplication::UnicodeUTF8));
        lbWarningImg->setText(QString());
        label_2->setText(QApplication::translate("CameraDefinitionDialog", "<font color=\"#808000\">Estimated values.</font> Processing results could be invalid. Please check the sensor parameters.", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CameraDefinitionDialog", "Error: <font color=\"red\">Invalid size ratio.</font>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraDefinitionDialog: public Ui_CameraDefinitionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERADEFINITIONDIALOG_H
