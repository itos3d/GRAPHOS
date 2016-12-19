/********************************************************************************
** Form generated from reading UI file 'AboutWallis_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWALLIS_DIALOG_H
#define UI_ABOUTWALLIS_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AboutWallis_dialog
{
public:

    void setupUi(QDialog *AboutWallis_dialog)
    {
        if (AboutWallis_dialog->objectName().isEmpty())
            AboutWallis_dialog->setObjectName(QString::fromUtf8("AboutWallis_dialog"));
        AboutWallis_dialog->resize(400, 300);

        retranslateUi(AboutWallis_dialog);

        QMetaObject::connectSlotsByName(AboutWallis_dialog);
    } // setupUi

    void retranslateUi(QDialog *AboutWallis_dialog)
    {
        AboutWallis_dialog->setWindowTitle(QApplication::translate("AboutWallis_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutWallis_dialog: public Ui_AboutWallis_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWALLIS_DIALOG_H
