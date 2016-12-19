/********************************************************************************
** Form generated from reading UI file 'aboutFeatures_Dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTFEATURES_DIALOG_H
#define UI_ABOUTFEATURES_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_aboutFeatures_Dialog
{
public:

    void setupUi(QDialog *aboutFeatures_Dialog)
    {
        if (aboutFeatures_Dialog->objectName().isEmpty())
            aboutFeatures_Dialog->setObjectName(QString::fromUtf8("aboutFeatures_Dialog"));
        aboutFeatures_Dialog->resize(400, 300);

        retranslateUi(aboutFeatures_Dialog);

        QMetaObject::connectSlotsByName(aboutFeatures_Dialog);
    } // setupUi

    void retranslateUi(QDialog *aboutFeatures_Dialog)
    {
        aboutFeatures_Dialog->setWindowTitle(QApplication::translate("aboutFeatures_Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutFeatures_Dialog: public Ui_aboutFeatures_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTFEATURES_DIALOG_H
