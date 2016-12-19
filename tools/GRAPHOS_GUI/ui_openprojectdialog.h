/********************************************************************************
** Form generated from reading UI file 'openprojectdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENPROJECTDIALOG_H
#define UI_OPENPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OpenProjectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *pushButton;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OpenProjectDialog)
    {
        if (OpenProjectDialog->objectName().isEmpty())
            OpenProjectDialog->setObjectName(QString::fromUtf8("OpenProjectDialog"));
        OpenProjectDialog->resize(598, 365);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OpenProjectDialog->sizePolicy().hasHeightForWidth());
        OpenProjectDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(OpenProjectDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(OpenProjectDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(tableView);

        pushButton = new QPushButton(OpenProjectDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pushButton);

        frame = new QFrame(OpenProjectDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy3);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelName = new QLabel(frame);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        sizePolicy3.setHeightForWidth(labelName->sizePolicy().hasHeightForWidth());
        labelName->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(labelName);

        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEditName->sizePolicy().hasHeightForWidth());
        lineEditName->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(lineEditName);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(OpenProjectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        buttonBox->raise();
        tableView->raise();
        frame->raise();
        pushButton->raise();

        retranslateUi(OpenProjectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OpenProjectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OpenProjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(OpenProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenProjectDialog)
    {
        OpenProjectDialog->setWindowTitle(QApplication::translate("OpenProjectDialog", "Open Project", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("OpenProjectDialog", "Delete", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("OpenProjectDialog", "Name:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenProjectDialog: public Ui_OpenProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENPROJECTDIALOG_H
