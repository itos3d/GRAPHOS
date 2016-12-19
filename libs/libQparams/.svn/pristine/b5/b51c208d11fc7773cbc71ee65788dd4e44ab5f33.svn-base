#ifndef PARAMSDIALOG_H
#define PARAMSDIALOG_H

#include <QDialog>
#include "ParamsTableModel.h"
#include "qparams.h"

namespace Ui {
class ParamsDialog;
}

class ParamsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ParamsDialog(QWidget *parent = 0);
    ~ParamsDialog();

    void addParam(QParams::Param *param);
    QVariant getValue(QString paramName);
    QMap<QString, QParams::Param *> getParams();
    void clearParams();
    void setDefaultValues();

protected:
    void showEvent(QShowEvent * event);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::ParamsDialog *ui;

    ParamsTableModel * mParamsTableModel;
};

#endif // PARAMSDIALOG_H
