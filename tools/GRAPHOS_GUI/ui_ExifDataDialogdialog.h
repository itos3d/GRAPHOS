/********************************************************************************
** Form generated from reading UI file 'ExifDataDialogdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXIFDATADIALOGDIALOG_H
#define UI_EXIFDATADIALOGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ExifDataDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelName;
    QLabel *labelFocal;
    QLineEdit *lineEditName;
    QLineEdit *lineEditFocal;
    QLabel *labelScale;
    QLineEdit *lineEditScale;

    void setupUi(QDialog *ExifDataDialog)
    {
        if (ExifDataDialog->objectName().isEmpty())
            ExifDataDialog->setObjectName(QString::fromUtf8("ExifDataDialog"));
        ExifDataDialog->resize(400, 246);
        buttonBox = new QDialogButtonBox(ExifDataDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 200, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelName = new QLabel(ExifDataDialog);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(20, 50, 141, 16));
        labelFocal = new QLabel(ExifDataDialog);
        labelFocal->setObjectName(QString::fromUtf8("labelFocal"));
        labelFocal->setGeometry(QRect(20, 90, 171, 16));
        lineEditName = new QLineEdit(ExifDataDialog);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(150, 50, 221, 23));
        lineEditFocal = new QLineEdit(ExifDataDialog);
        lineEditFocal->setObjectName(QString::fromUtf8("lineEditFocal"));
        lineEditFocal->setGeometry(QRect(150, 90, 221, 23));
        labelScale = new QLabel(ExifDataDialog);
        labelScale->setObjectName(QString::fromUtf8("labelScale"));
        labelScale->setGeometry(QRect(20, 140, 291, 16));
        lineEditScale = new QLineEdit(ExifDataDialog);
        lineEditScale->setObjectName(QString::fromUtf8("lineEditScale"));
        lineEditScale->setGeometry(QRect(322, 130, 51, 23));

        retranslateUi(ExifDataDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExifDataDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExifDataDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExifDataDialog);
    } // setupUi

    void retranslateUi(QDialog *ExifDataDialog)
    {
        ExifDataDialog->setWindowTitle(QApplication::translate("ExifDataDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("ExifDataDialog", "Camera Name:", 0, QApplication::UnicodeUTF8));
        labelFocal->setText(QApplication::translate("ExifDataDialog", "Focal Length (mm):", 0, QApplication::UnicodeUTF8));
        labelScale->setText(QApplication::translate("ExifDataDialog", "Scale factor to 35mm equivalent:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExifDataDialog: public Ui_ExifDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXIFDATADIALOGDIALOG_H
