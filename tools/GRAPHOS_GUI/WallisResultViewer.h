#ifndef WALLISRESULTVIEWER_H
#define WALLISRESULTVIEWER_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
class WallisResultViewer : public QDialog
{
    Q_OBJECT

public:
    explicit WallisResultViewer(QWidget *parent = 0,QString WallisImageURL="",QVector<QString> imageNames =QVector<QString>());
    ~WallisResultViewer();

private:
    QRect mainScreenSize;
    QPushButton *mPbProccess;
    QPushButton *pbCancel;
    QLabel *mLbWallisImage;
    QString mWallisImageURL;
    QVector<QString> mImageNames;
    int mImageToShowPos;
    QLabel *mLbImageToShowNum;
    QLabel *mLbImageName;
private slots:
    void on_pbProccess_clicked();
    void on_pbCancel_clicked();
    void on_leftArrow_clicked();
    void on_rightArrow_clicked();
};

#endif // WALLISRESULTVIEWER_H
