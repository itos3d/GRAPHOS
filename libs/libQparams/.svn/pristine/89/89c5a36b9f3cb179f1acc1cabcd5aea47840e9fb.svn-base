#ifndef PARAMSTABLEMODEL_H
#define PARAMSTABLEMODEL_H

#include <QAbstractTableModel>

#include "qparams.h"

class ParamsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ParamsTableModel(QObject *parent = 0);
    ~ParamsTableModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation,int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData (const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    void copyParams();
    void restoreCopy();
    void restoreDefaults();

    void addParam(QParams::Param *param);
    QVariant getValue(QString paramName);
    QMap<QString, QParams::Param *> getParams();

    void clearParams();
    
signals:
    
public slots:

private:
    QMap<QString, QParams::Param*>  mParamsMap;
    QMap<QString, QParams::Param*>  mParamsMapCopy;
    QMap<QString, QVariant>         mValuesCopy;
    
};

#endif // PARAMSTABLEMODEL_H
