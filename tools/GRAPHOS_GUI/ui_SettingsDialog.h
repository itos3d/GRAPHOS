/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelOpenMVG;
    QLineEdit *lineEditOpenMVG;
    QPushButton *pushButtonOpenMVG;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelSURE;
    QLineEdit *lineEditSURE;
    QPushButton *pushButtonSURE;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelASIFT;
    QLineEdit *lineEditASIFTPath;
    QPushButton *pushButtonASIFTPath;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelPMVS;
    QLineEdit *lineEditPMVSPath;
    QPushButton *pushButtonPMVSPath;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QComboBox *comboBoxDefaultAccuracyToleranceForMatches;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBoxDrawOutliers;
    QCheckBox *checkBoxKeepMatchesInMemory;
    QCheckBox *checkBoxCleanProjectWhenClose;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *labelApero;
    QLineEdit *lineEditAperoPath;
    QPushButton *pushButtonAperoPath;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelOpenCV;
    QLineEdit *lineEditOpenCV;
    QPushButton *pushButtonOpenCV;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelTools;
    QLineEdit *lineEditTools;
    QPushButton *pushButtonTools;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(822, 589);
        gridLayout_3 = new QGridLayout(SettingsDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame_5 = new QFrame(SettingsDialog);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, -1, 0, -1);
        labelOpenMVG = new QLabel(frame_5);
        labelOpenMVG->setObjectName(QString::fromUtf8("labelOpenMVG"));

        horizontalLayout_5->addWidget(labelOpenMVG);

        lineEditOpenMVG = new QLineEdit(frame_5);
        lineEditOpenMVG->setObjectName(QString::fromUtf8("lineEditOpenMVG"));

        horizontalLayout_5->addWidget(lineEditOpenMVG);

        pushButtonOpenMVG = new QPushButton(frame_5);
        pushButtonOpenMVG->setObjectName(QString::fromUtf8("pushButtonOpenMVG"));

        horizontalLayout_5->addWidget(pushButtonOpenMVG);


        gridLayout_3->addWidget(frame_5, 6, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelSURE = new QLabel(SettingsDialog);
        labelSURE->setObjectName(QString::fromUtf8("labelSURE"));

        horizontalLayout_9->addWidget(labelSURE);

        lineEditSURE = new QLineEdit(SettingsDialog);
        lineEditSURE->setObjectName(QString::fromUtf8("lineEditSURE"));

        horizontalLayout_9->addWidget(lineEditSURE);

        pushButtonSURE = new QPushButton(SettingsDialog);
        pushButtonSURE->setObjectName(QString::fromUtf8("pushButtonSURE"));

        horizontalLayout_9->addWidget(pushButtonSURE);


        gridLayout_3->addLayout(horizontalLayout_9, 7, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 10, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(SettingsDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        labelASIFT = new QLabel(frame_2);
        labelASIFT->setObjectName(QString::fromUtf8("labelASIFT"));

        horizontalLayout_2->addWidget(labelASIFT);

        lineEditASIFTPath = new QLineEdit(frame_2);
        lineEditASIFTPath->setObjectName(QString::fromUtf8("lineEditASIFTPath"));

        horizontalLayout_2->addWidget(lineEditASIFTPath);

        pushButtonASIFTPath = new QPushButton(frame_2);
        pushButtonASIFTPath->setObjectName(QString::fromUtf8("pushButtonASIFTPath"));

        horizontalLayout_2->addWidget(pushButtonASIFTPath);


        verticalLayout->addWidget(frame_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(50, -1, -1, -1);
        checkBox = new QCheckBox(SettingsDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_7->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout_7);


        gridLayout_3->addLayout(verticalLayout, 1, 0, 1, 1);

        frame_3 = new QFrame(SettingsDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, 0, -1);
        labelPMVS = new QLabel(frame_3);
        labelPMVS->setObjectName(QString::fromUtf8("labelPMVS"));

        horizontalLayout_3->addWidget(labelPMVS);

        lineEditPMVSPath = new QLineEdit(frame_3);
        lineEditPMVSPath->setObjectName(QString::fromUtf8("lineEditPMVSPath"));

        horizontalLayout_3->addWidget(lineEditPMVSPath);

        pushButtonPMVSPath = new QPushButton(frame_3);
        pushButtonPMVSPath->setObjectName(QString::fromUtf8("pushButtonPMVSPath"));

        horizontalLayout_3->addWidget(pushButtonPMVSPath);


        gridLayout_3->addWidget(frame_3, 4, 0, 1, 1);

        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame_7 = new QFrame(groupBox);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_7);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, -1, 0, -1);
        label = new QLabel(frame_7);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        comboBoxDefaultAccuracyToleranceForMatches = new QComboBox(frame_7);
        comboBoxDefaultAccuracyToleranceForMatches->setObjectName(QString::fromUtf8("comboBoxDefaultAccuracyToleranceForMatches"));

        horizontalLayout_6->addWidget(comboBoxDefaultAccuracyToleranceForMatches);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        checkBoxDrawOutliers = new QCheckBox(frame_7);
        checkBoxDrawOutliers->setObjectName(QString::fromUtf8("checkBoxDrawOutliers"));

        horizontalLayout_6->addWidget(checkBoxDrawOutliers);


        gridLayout_2->addWidget(frame_7, 4, 0, 1, 1);

        checkBoxKeepMatchesInMemory = new QCheckBox(groupBox);
        checkBoxKeepMatchesInMemory->setObjectName(QString::fromUtf8("checkBoxKeepMatchesInMemory"));
        checkBoxKeepMatchesInMemory->setChecked(true);

        gridLayout_2->addWidget(checkBoxKeepMatchesInMemory, 0, 0, 1, 1);

        checkBoxCleanProjectWhenClose = new QCheckBox(groupBox);
        checkBoxCleanProjectWhenClose->setObjectName(QString::fromUtf8("checkBoxCleanProjectWhenClose"));
        checkBoxCleanProjectWhenClose->setChecked(false);

        gridLayout_2->addWidget(checkBoxCleanProjectWhenClose, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 9, 0, 1, 1);

        frame = new QFrame(SettingsDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        labelApero = new QLabel(frame);
        labelApero->setObjectName(QString::fromUtf8("labelApero"));

        horizontalLayout->addWidget(labelApero);

        lineEditAperoPath = new QLineEdit(frame);
        lineEditAperoPath->setObjectName(QString::fromUtf8("lineEditAperoPath"));

        horizontalLayout->addWidget(lineEditAperoPath);

        pushButtonAperoPath = new QPushButton(frame);
        pushButtonAperoPath->setObjectName(QString::fromUtf8("pushButtonAperoPath"));

        horizontalLayout->addWidget(pushButtonAperoPath);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        frame_4 = new QFrame(SettingsDialog);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, 0, -1);
        labelOpenCV = new QLabel(frame_4);
        labelOpenCV->setObjectName(QString::fromUtf8("labelOpenCV"));

        horizontalLayout_4->addWidget(labelOpenCV);

        lineEditOpenCV = new QLineEdit(frame_4);
        lineEditOpenCV->setObjectName(QString::fromUtf8("lineEditOpenCV"));

        horizontalLayout_4->addWidget(lineEditOpenCV);

        pushButtonOpenCV = new QPushButton(frame_4);
        pushButtonOpenCV->setObjectName(QString::fromUtf8("pushButtonOpenCV"));

        horizontalLayout_4->addWidget(pushButtonOpenCV);


        gridLayout_3->addWidget(frame_4, 5, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelTools = new QLabel(SettingsDialog);
        labelTools->setObjectName(QString::fromUtf8("labelTools"));

        horizontalLayout_10->addWidget(labelTools);

        lineEditTools = new QLineEdit(SettingsDialog);
        lineEditTools->setObjectName(QString::fromUtf8("lineEditTools"));

        horizontalLayout_10->addWidget(lineEditTools);

        pushButtonTools = new QPushButton(SettingsDialog);
        pushButtonTools->setObjectName(QString::fromUtf8("pushButtonTools"));

        horizontalLayout_10->addWidget(pushButtonTools);


        gridLayout_3->addLayout(horizontalLayout_10, 8, 0, 1, 1);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "PW Settings", 0, QApplication::UnicodeUTF8));
        labelOpenMVG->setText(QApplication::translate("SettingsDialog", "OpenMVG binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonOpenMVG->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        labelSURE->setText(QApplication::translate("SettingsDialog", "SURE binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonSURE->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        labelASIFT->setText(QApplication::translate("SettingsDialog", "ASIFT binaries: ", 0, QApplication::UnicodeUTF8));
        pushButtonASIFTPath->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("SettingsDialog", "Concurrent ASIFT", 0, QApplication::UnicodeUTF8));
        labelPMVS->setText(QApplication::translate("SettingsDialog", "PMVS binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonPMVSPath->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingsDialog", "Operating parameters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingsDialog", "Default accuracy tolerance for matches (pixels):", 0, QApplication::UnicodeUTF8));
        comboBoxDefaultAccuracyToleranceForMatches->clear();
        comboBoxDefaultAccuracyToleranceForMatches->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "0.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "1.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "2.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "3.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "5.0", 0, QApplication::UnicodeUTF8)
        );
        checkBoxDrawOutliers->setText(QApplication::translate("SettingsDialog", "Draw outliers matches", 0, QApplication::UnicodeUTF8));
        checkBoxKeepMatchesInMemory->setText(QApplication::translate("SettingsDialog", "Keep matches in memory", 0, QApplication::UnicodeUTF8));
        checkBoxCleanProjectWhenClose->setText(QApplication::translate("SettingsDialog", "Clean project when it is closed", 0, QApplication::UnicodeUTF8));
        labelApero->setText(QApplication::translate("SettingsDialog", "Apero/MICMAC binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonAperoPath->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        labelOpenCV->setText(QApplication::translate("SettingsDialog", "OpenCV binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonOpenCV->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
        labelTools->setText(QApplication::translate("SettingsDialog", "Tools binaries:", 0, QApplication::UnicodeUTF8));
        pushButtonTools->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
