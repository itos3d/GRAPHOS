#include "ParamsDialog.h"
#include "ui_ParamsDialog.h"
#include "ParamsTableItemDelegate.h"

#include <QShowEvent>

ParamsDialog::ParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamsDialog)
{
    ui->setupUi(this);
    mParamsTableModel = new ParamsTableModel();
    ui->tableView->setModel(mParamsTableModel);
    ParamsTableItemDelegate *itemDelegate = new ParamsTableItemDelegate(mParamsTableModel,this);
    ui->tableView->setItemDelegate(itemDelegate);
}

ParamsDialog::~ParamsDialog()
{
    delete ui;
    delete mParamsTableModel;
}

void ParamsDialog::addParam(QParams::Param *param)
{
    mParamsTableModel->addParam(param);
}

QVariant ParamsDialog::getValue(QString paramName)
{
    return mParamsTableModel->getValue(paramName);
}

QMap<QString, QParams::Param *> ParamsDialog::getParams()
{
    return mParamsTableModel->getParams();
}

void ParamsDialog::clearParams()
{
    mParamsTableModel->clearParams();
}

void ParamsDialog::setDefaultValues()
{
    mParamsTableModel->restoreDefaults();
    ui->tableView->reset();
}

void ParamsDialog::showEvent(QShowEvent * event)
{
    if (!event->spontaneous()){
       mParamsTableModel->copyParams();
    }
    QDialog::showEvent(event);
}

void ParamsDialog::on_buttonBox_accepted()
{

}

void ParamsDialog::on_buttonBox_rejected()
{
    mParamsTableModel->restoreCopy();
}

void ParamsDialog::on_pushButton_clicked()
{
    setDefaultValues();
}
