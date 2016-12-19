/********************************************************************************
** Form generated from reading UI file 'AboutDensification_Dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDENSIFICATION_DIALOG_H
#define UI_ABOUTDENSIFICATION_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AboutDensification_Dialog
{
public:

    void setupUi(QDialog *AboutDensification_Dialog)
    {
        if (AboutDensification_Dialog->objectName().isEmpty())
            AboutDensification_Dialog->setObjectName(QString::fromUtf8("AboutDensification_Dialog"));
        AboutDensification_Dialog->resize(400, 300);

        retranslateUi(AboutDensification_Dialog);

        QMetaObject::connectSlotsByName(AboutDensification_Dialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDensification_Dialog)
    {
        AboutDensification_Dialog->setWindowTitle(QApplication::translate("AboutDensification_Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutDensification_Dialog: public Ui_AboutDensification_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDENSIFICATION_DIALOG_H
