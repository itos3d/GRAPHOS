#include "ParamsTableItemDelegate.h"
#include "ParamsTableModel.h"

#include <QSpinBox>
#include <QComboBox>

ParamsTableItemDelegate::ParamsTableItemDelegate(ParamsTableModel *tableModel, QObject *parent) :
    QItemDelegate(parent),
    mTableModel(tableModel)
{
}

QWidget *ParamsTableItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==1){
        QParams::Param *param = mTableModel->getParams().values().at(index.row());
        QParams::ContinuousParam *continuousParam = dynamic_cast<QParams::ContinuousParam *>(param);
        if (continuousParam && continuousParam->isValidDomain()){
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setMinimum(continuousParam->getMinValue());
            editor->setMaximum(continuousParam->getMaxValue());
            return editor;
        }else{
            QParams::DiscreteParam *discreteParam = dynamic_cast<QParams::DiscreteParam *>(param);
            if (discreteParam){
                QComboBox *editor = new QComboBox(parent);
                for (int i=0; i<discreteParam->getValues().values().count(); i++){
                    QParams::Value value = discreteParam->getValues().values().at(i);
                    editor->addItem(value.getValue());
                }
                return editor;
            }
        }
    }
    QItemDelegate::createEditor(parent,option,index);
}

void ParamsTableItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column()==1){
        QParams::Param *param = mTableModel->getParams().values().at(index.row());
        QParams::ContinuousParam *continuousParam = dynamic_cast<QParams::ContinuousParam *>(param);
        if (continuousParam){
            // Get the value via index of the Model
            int value = index.model()->data(index, Qt::EditRole).toInt();

            // Put the value into the SpinBox
            QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
            spinbox->setValue(value);
        }
        else{
            QString value = index.model()->data(index, Qt::EditRole).toString();
            QComboBox *combo = static_cast<QComboBox*>(editor);
            combo->setCurrentIndex(0); //***********************************
        }
    }
    else
        QItemDelegate::setEditorData(editor,index);
}

void ParamsTableItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column()==1){
        if(index.column()==1){
            QParams::Param *param = mTableModel->getParams().values().at(index.row());
            QParams::ContinuousParam *continuousParam = dynamic_cast<QParams::ContinuousParam *>(param);
            if (continuousParam){
                QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
                spinbox->interpretText();
                int value = spinbox->value();
                model->setData(index, value, Qt::EditRole);
            }
            else{
                QComboBox *combo = static_cast<QComboBox*>(editor);
                QString value = combo->currentText();
                model->setData(index,value, Qt::EditRole);
            }
        }
    }
    else
        QItemDelegate::setModelData(editor, model, index);
}

void ParamsTableItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
