/********************************************************************************
** Form generated from reading UI file 'ImagesWizard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESWIZARD_H
#define UI_IMAGESWIZARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagesWizard
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_2;
    QFrame *frame_3;
    QListWidget *localPathList;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pbAddImages;
    QPushButton *pbRemoveImage;
    QPushButton *pbRemoveAllImages;
    QLabel *label;
    QWidget *page_2;
    QPushButton *pbNext;
    QPushButton *pb;

    void setupUi(QDialog *ImagesWizard)
    {
        if (ImagesWizard->objectName().isEmpty())
            ImagesWizard->setObjectName(QString::fromUtf8("ImagesWizard"));
        ImagesWizard->setWindowModality(Qt::ApplicationModal);
        ImagesWizard->resize(640, 480);
        ImagesWizard->setMinimumSize(QSize(640, 480));
        ImagesWizard->setMaximumSize(QSize(640, 480));
        stackedWidget = new QStackedWidget(ImagesWizard);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 641, 421));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        frame_2 = new QFrame(page);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(20, 30, 601, 361));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(10, 30, 581, 251));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        localPathList = new QListWidget(frame_3);
        localPathList->setObjectName(QString::fromUtf8("localPathList"));
        localPathList->setGeometry(QRect(0, 0, 581, 241));
        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(80, 300, 416, 60));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pbAddImages = new QPushButton(frame_5);
        pbAddImages->setObjectName(QString::fromUtf8("pbAddImages"));

        horizontalLayout_2->addWidget(pbAddImages);

        pbRemoveImage = new QPushButton(frame_5);
        pbRemoveImage->setObjectName(QString::fromUtf8("pbRemoveImage"));

        horizontalLayout_2->addWidget(pbRemoveImage);

        pbRemoveAllImages = new QPushButton(frame_5);
        pbRemoveAllImages->setObjectName(QString::fromUtf8("pbRemoveAllImages"));

        horizontalLayout_2->addWidget(pbRemoveAllImages);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 221, 23));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        pbNext = new QPushButton(ImagesWizard);
        pbNext->setObjectName(QString::fromUtf8("pbNext"));
        pbNext->setGeometry(QRect(380, 430, 111, 31));
        pb = new QPushButton(ImagesWizard);
        pb->setObjectName(QString::fromUtf8("pb"));
        pb->setGeometry(QRect(500, 430, 111, 31));

        retranslateUi(ImagesWizard);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImagesWizard);
    } // setupUi

    void retranslateUi(QDialog *ImagesWizard)
    {
        ImagesWizard->setWindowTitle(QApplication::translate("ImagesWizard", "Images", 0, QApplication::UnicodeUTF8));
        pbAddImages->setText(QApplication::translate("ImagesWizard", "Add images", 0, QApplication::UnicodeUTF8));
        pbRemoveImage->setText(QApplication::translate("ImagesWizard", "Remove", 0, QApplication::UnicodeUTF8));
        pbRemoveAllImages->setText(QApplication::translate("ImagesWizard", "Remove All", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImagesWizard", "Add images:", 0, QApplication::UnicodeUTF8));
        pbNext->setText(QApplication::translate("ImagesWizard", "Next", 0, QApplication::UnicodeUTF8));
        pb->setText(QApplication::translate("ImagesWizard", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImagesWizard: public Ui_ImagesWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESWIZARD_H
