/********************************************************************************
** Form generated from reading UI file 'NewCameraDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCAMERADIALOG_H
#define UI_NEWCAMERADIALOG_H

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

class Ui_NewCameraDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *ModelLineEdit;
    QLineEdit *WidhtLineEdit;
    QLineEdit *HeightLineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *LenslineEdit;
    QLabel *label_4;

    void setupUi(QDialog *NewCameraDialog)
    {
        if (NewCameraDialog->objectName().isEmpty())
            NewCameraDialog->setObjectName(QString::fromUtf8("NewCameraDialog"));
        NewCameraDialog->resize(586, 233);
        buttonBox = new QDialogButtonBox(NewCameraDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(210, 180, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ModelLineEdit = new QLineEdit(NewCameraDialog);
        ModelLineEdit->setObjectName(QString::fromUtf8("ModelLineEdit"));
        ModelLineEdit->setGeometry(QRect(150, 20, 401, 23));
        WidhtLineEdit = new QLineEdit(NewCameraDialog);
        WidhtLineEdit->setObjectName(QString::fromUtf8("WidhtLineEdit"));
        WidhtLineEdit->setGeometry(QRect(150, 110, 113, 23));
        HeightLineEdit = new QLineEdit(NewCameraDialog);
        HeightLineEdit->setObjectName(QString::fromUtf8("HeightLineEdit"));
        HeightLineEdit->setGeometry(QRect(440, 110, 113, 23));
        label = new QLabel(NewCameraDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 111, 16));
        label_2 = new QLabel(NewCameraDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 120, 121, 16));
        label_3 = new QLabel(NewCameraDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(310, 120, 131, 16));
        LenslineEdit = new QLineEdit(NewCameraDialog);
        LenslineEdit->setObjectName(QString::fromUtf8("LenslineEdit"));
        LenslineEdit->setGeometry(QRect(150, 60, 401, 23));
        label_4 = new QLabel(NewCameraDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 60, 111, 16));

        retranslateUi(NewCameraDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewCameraDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewCameraDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewCameraDialog);
    } // setupUi

    void retranslateUi(QDialog *NewCameraDialog)
    {
        NewCameraDialog->setWindowTitle(QApplication::translate("NewCameraDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewCameraDialog", "Camera Model:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewCameraDialog", "Sensor Width (mm.):", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewCameraDialog", "Sensor Height (mm.):", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewCameraDialog", "Lens", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewCameraDialog: public Ui_NewCameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCAMERADIALOG_H
