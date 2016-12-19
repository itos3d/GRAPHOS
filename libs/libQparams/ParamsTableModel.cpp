#include "ParamsTableModel.h"

ParamsTableModel::ParamsTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

ParamsTableModel::~ParamsTableModel()
{
    for (int i=0; i<mParamsMap.values().count();i++){
        delete mParamsMap.values().at(i);
    }

    for (int i=0; i<mParamsMapCopy.values().count();i++){
        delete mParamsMapCopy.values().at(i);
    }
}


int ParamsTableModel::rowCount(const QModelIndex &parent) const
{
    return mParamsMap.count();
}

int ParamsTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant ParamsTableModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()){
        if (role == Qt::TextAlignmentRole){
            if(index.column() == 0)
                return int(Qt::AlignLeft | Qt::AlignVCenter);
            else if(index.column() == 1)
                return int(Qt::AlignRight | Qt::AlignVCenter);
            else if(index.column() == 2)
                return int(Qt::AlignLeft | Qt::AlignVCenter);
            else if(index.column() == 3)
                return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
        else if (role == Qt::DisplayRole || role==Qt::EditRole) {
            QParams::ContinuousParam *param = dynamic_cast<QParams::ContinuousParam*>(mParamsMap.values().at(index.row()));
            if(param){
                if(index.column() == 0)
                    return param->getName();
                else if(index.column() == 1)
                    return param->getValue();
                else if(index.column() == 2)
                    return param->getInternalUnit()->getName();
                else if(index.column() == 3)
                    return param->getDescription();
            }
            else{
                QParams::DiscreteParam *param = dynamic_cast<QParams::DiscreteParam*>(mParamsMap.values().at(index.row()));
                if(index.column() == 0)
                    return param->getName();
                else if(index.column() == 1)
                    return param->getValue();
                else if(index.column() == 2)
                    return "";
                else if(index.column() == 3)
                    return param->getDescription();
            }
        }
        else return QVariant::Invalid;
    }
}

QVariant ParamsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();
    switch (section){
    case 0:
        return (tr("Parameter"));
        break;
    case 1:
        return (tr("Value"));
        break;
    case 2:
        return (tr("Unit"));
        break;
    case 3:
        return (tr("Description"));
        break;
    }
}

bool ParamsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QParams::Param *param = mParamsMap.values().at(index.row());
    QParams::ContinuousParam *continuousParam = dynamic_cast<QParams::ContinuousParam*>(param);
    switch(index.column()){
    case 0:
        break;
    case 1:
        if(continuousParam){
            continuousParam->setValue(value.toDouble());
        }
        else{
            QParams::DiscreteParam *discreteParam = dynamic_cast<QParams::DiscreteParam *>(param);
            if (discreteParam){
                discreteParam->setValue(value.toString());
            }
        }
        mParamsMap.insert(param->getName(), param);
        break;
    case 2:
        break;
    case 3:
        break;
    }
    return true;
}

Qt::ItemFlags ParamsTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.column()==1)
        flags|=Qt::ItemIsEditable;
    return flags;
}

void ParamsTableModel::copyParams()
{
    mValuesCopy.clear();
    QList<QParams::Param*> values = mParamsMap.values();
    for (int i=0; i<values.count(); i++){
        QParams::ContinuousParam* continuousParam = dynamic_cast<QParams::ContinuousParam*>(values.at(i));
        if (continuousParam)
            mValuesCopy.insert(continuousParam->getName(), QVariant(continuousParam->getValue()));
        else{
            QParams::DiscreteParam* discreteParam = dynamic_cast<QParams::DiscreteParam*>(values.at(i));
            mValuesCopy.insert(discreteParam->getName(), QVariant(discreteParam->getValue()));
        }
    }
}

void ParamsTableModel::restoreCopy()
{
    foreach(QString key, mValuesCopy.keys() )
    {
        QParams::Param* param = mParamsMap.value(key);
        QParams::ContinuousParam* continuousParam = dynamic_cast<QParams::ContinuousParam*>(param);
        if(continuousParam)
            continuousParam->setValue(mValuesCopy.value(key).toDouble());
        else{
            QParams::DiscreteParam* discreteParam = dynamic_cast<QParams::DiscreteParam*>(param);
            discreteParam->setValue(mValuesCopy.value(key).toString());
        }
    }
}

void ParamsTableModel::restoreDefaults()
{
    foreach(QString key, mParamsMap.keys() )
    {
        QParams::Param* param = mParamsMap.value(key);
        QParams::ContinuousParam* continuousParam = dynamic_cast<QParams::ContinuousParam*>(param);
        if(continuousParam)
            continuousParam->setValue(continuousParam->getDefaultValue());
        else{
            QParams::DiscreteParam* discreteParam = dynamic_cast<QParams::DiscreteParam*>(param);
            discreteParam->setValue(discreteParam->getDefaultValue());
        }
    }
}

void ParamsTableModel::addParam(QParams::Param *param)
{
    mParamsMap.insert(param->getName(), param);
    reset();
}

QVariant ParamsTableModel::getValue(QString paramName)
{
    QParams::Param *param = mParamsMap.value(paramName);
    QParams::ContinuousParam *continuousParam = dynamic_cast<QParams::ContinuousParam*>(param);
    if (continuousParam)
        return QVariant(continuousParam->getValue());
    else{
        QParams::DiscreteParam *discreteParam = dynamic_cast<QParams::DiscreteParam *>(param);
        if(discreteParam)
            return QVariant(discreteParam->getValue());
    }
    return 0;
}

QMap<QString, QParams::Param *> ParamsTableModel::getParams()
{
    return mParamsMap;
}

void ParamsTableModel::clearParams()
{
    mParamsMap.clear();
}
