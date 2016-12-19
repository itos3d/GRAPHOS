/********************************************************************************
** Form generated from reading UI file 'AboutCalibrations_Dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTCALIBRATIONS_DIALOG_H
#define UI_ABOUTCALIBRATIONS_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AboutCalibrations_Dialog
{
public:

    void setupUi(QDialog *AboutCalibrations_Dialog)
    {
        if (AboutCalibrations_Dialog->objectName().isEmpty())
            AboutCalibrations_Dialog->setObjectName(QString::fromUtf8("AboutCalibrations_Dialog"));
        AboutCalibrations_Dialog->resize(400, 300);

        retranslateUi(AboutCalibrations_Dialog);

        QMetaObject::connectSlotsByName(AboutCalibrations_Dialog);
    } // setupUi

    void retranslateUi(QDialog *AboutCalibrations_Dialog)
    {
        AboutCalibrations_Dialog->setWindowTitle(QApplication::translate("AboutCalibrations_Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutCalibrations_Dialog: public Ui_AboutCalibrations_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTCALIBRATIONS_DIALOG_H
